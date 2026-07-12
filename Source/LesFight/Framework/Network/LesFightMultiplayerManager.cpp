#include "LesFightMultiplayerManager.h"
#include "LesFightSessionManager.h"
#include "LesFightConnectionManager.h"
#include "LesFightMatchManager.h"
#include "LesFightNetworkSyncManager.h"
#include "LesFightReplicationManager.h"
#include "LesFightNetworkPrediction.h"
#include "LesFightNetworkOptimizer.h"
#include "LesFightLagCompensation.h"
#include "LesFightNetworkSecurity.h"
#include "LesFightNetworkDebugger.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ULesFightMultiplayerManager::ULesFightMultiplayerManager()
    : bMultiplayerActive(false)
    , bInitialized(false)
    , LocalPlayerIndex(0)
    , LocalPlayerName(TEXT("Player"))
    , NetworkSettings(nullptr)
{
}

void ULesFightMultiplayerManager::Initialize()
{
    if (bInitialized) return;

    CreateSubManagers();
    ConfigureNetworkSettings();
    bInitialized = true;

    UE_LOG(LogLesFightNetwork, Log, TEXT("MultiplayerManager initialized"));
}

void ULesFightMultiplayerManager::Shutdown()
{
    if (!bInitialized) return;

    if (SessionManager) SessionManager->DestroySession();
    if (ConnectionManager) ConnectionManager->Reset();
    if (MatchManager) MatchManager->Reset();

    bMultiplayerActive = false;
    bInitialized = false;

    UE_LOG(LogLesFightNetwork, Log, TEXT("MultiplayerManager shutdown"));
}

void ULesFightMultiplayerManager::Tick(float DeltaTime)
{
    if (!bInitialized) return;

    if (ConnectionManager) ConnectionManager->Tick(DeltaTime);
    if (MatchManager) MatchManager->TickRoundTimer(DeltaTime);
    if (LagCompensation) LagCompensation->Tick(DeltaTime);
    if (NetworkPrediction) NetworkPrediction->Tick(DeltaTime);
    if (NetworkOptimizer) NetworkOptimizer->Tick(DeltaTime);
    if (NetworkDebugger) NetworkDebugger->Tick(DeltaTime);
    if (SyncManager) SyncManager->Tick(DeltaTime);
}

bool ULesFightMultiplayerManager::HostGame(const FString& SessionName, int32 MaxPlayers)
{
    if (!SessionManager) return false;

    if (!SessionManager->HostSession(SessionName, MaxPlayers, true))
    {
        UE_LOG(LogLesFightNetwork, Warning, TEXT("Failed to host session"));
        return false;
    }

    bMultiplayerActive = true;
    LocalPlayerIndex = 0;
    return true;
}

bool ULesFightMultiplayerManager::FindLANGames()
{
    if (!SessionManager) return false;
    return SessionManager->SearchForSessions(true);
}

bool ULesFightMultiplayerManager::JoinGame(int32 SessionIndex)
{
    if (!SessionManager) return false;

    if (!SessionManager->JoinSession(SessionIndex))
    {
        UE_LOG(LogLesFightNetwork, Warning, TEXT("Failed to join session %d"), SessionIndex);
        return false;
    }

    bMultiplayerActive = true;
    LocalPlayerIndex = 1;
    return true;
}

bool ULesFightMultiplayerManager::LeaveGame()
{
    if (!SessionManager) return false;

    bool bResult = SessionManager->LeaveSession();
    bMultiplayerActive = false;
    return bResult;
}

bool ULesFightMultiplayerManager::ReturnToLobby()
{
    if (!SessionManager) return false;
    if (MatchManager) MatchManager->Reset();
    return true;
}

void ULesFightMultiplayerManager::RequestStartMatch()
{
    if (!MatchManager) return;
    if (!IsHosting()) return;
    MatchManager->StartMatch();
}

void ULesFightMultiplayerManager::RequestRoundEnd(int32 WinnerIndex)
{
    if (!MatchManager) return;
    if (!IsHosting()) return;
    MatchManager->EndRound(WinnerIndex, EWinCondition::None);
}

void ULesFightMultiplayerManager::SetPlayerReady(bool bReady)
{
    if (!MatchManager) return;
    MatchManager->SetPlayerReady(LocalPlayerIndex, bReady);
}

void ULesFightMultiplayerManager::OnPlayerInput(const FName& InputAction, float InputValue)
{
    if (NetworkPrediction)
    {
        NetworkPrediction->QueueInput(InputAction, InputValue);
    }
}

void ULesFightMultiplayerManager::OnCombatAction(const FNetworkCombatAction& Action)
{
    if (SyncManager)
    {
        SyncManager->SendCombatAction(LocalPlayerIndex, Action);
    }
}

void ULesFightMultiplayerManager::SyncAnimationState(const FNetworkAnimSyncData& AnimData)
{
    if (SyncManager)
    {
        SyncManager->SendAnimationState(LocalPlayerIndex, AnimData);
    }
}

void ULesFightMultiplayerManager::RequestFullStateSync()
{
    if (SyncManager)
    {
        SyncManager->RequestFullStateSync();
    }
}

void ULesFightMultiplayerManager::ReplicateCombatAction(int32 PlayerIndex, const FNetworkCombatAction& Action)
{
    if (ReplicationManager)
    {
        ReplicationManager->ReplicateCombatAction(PlayerIndex, Action);
    }
}

void ULesFightMultiplayerManager::BroadcastChatMessage(const FString& Message)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("Chat: %s"), *Message);
}

void ULesFightMultiplayerManager::SendSystemMessage(const FString& Message)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("System: %s"), *Message);
}

bool ULesFightMultiplayerManager::IsHosting() const
{
    return SessionManager ? SessionManager->IsHosting() : false;
}

ENetworkSessionState ULesFightMultiplayerManager::GetSessionState() const
{
    return SessionManager ? SessionManager->GetSessionState() : ENetworkSessionState::None;
}

ENetworkMatchState ULesFightMultiplayerManager::GetMatchState() const
{
    return MatchManager ? MatchManager->GetMatchState() : ENetworkMatchState::None;
}

TArray<FLANSessionInfo> ULesFightMultiplayerManager::GetFoundSessions() const
{
    return SessionManager ? SessionManager->GetFoundSessions() : TArray<FLANSessionInfo>();
}

TArray<FNetworkPlayerInfo> ULesFightMultiplayerManager::GetPlayerList() const
{
    return TArray<FNetworkPlayerInfo>();
}

FNetworkMatchData ULesFightMultiplayerManager::GetCurrentMatchData() const
{
    return MatchManager ? MatchManager->GetMatchData() : FNetworkMatchData();
}

void ULesFightMultiplayerManager::SetMaxRounds(int32 Count)
{
    if (MatchManager) MatchManager->SetMaxRounds(Count);
}

void ULesFightMultiplayerManager::SetRoundTimeLimit(float Seconds)
{
    if (MatchManager) MatchManager->SetRoundTimeLimit(Seconds);
}

void ULesFightMultiplayerManager::CreateSubManagers()
{
    SessionManager = NewObject<ULesFightSessionManager>(this);
    SessionManager->Initialize();

    ConnectionManager = NewObject<ULesFightConnectionManager>(this);
    ConnectionManager->Initialize(this);

    MatchManager = NewObject<ULesFightMatchManager>(this);

    SyncManager = NewObject<ULesFightNetworkSyncManager>(this);
    SyncManager->Initialize(this);

    ReplicationManager = NewObject<ULesFightReplicationManager>(this);
    ReplicationManager->Initialize(this);

    NetworkPrediction = NewObject<ULesFightNetworkPrediction>(this);
    NetworkPrediction->Initialize(this);

    LagCompensation = NewObject<ULesFightLagCompensation>(this);
    LagCompensation->Initialize(this);

    NetworkOptimizer = NewObject<ULesFightNetworkOptimizer>(this);
    NetworkOptimizer->Initialize(this);

    NetworkSecurity = NewObject<ULesFightNetworkSecurity>(this);
    NetworkSecurity->Initialize();

    NetworkDebugger = NewObject<ULesFightNetworkDebugger>(this);
    NetworkDebugger->Initialize();

    UE_LOG(LogLesFightNetwork, Log, TEXT("All sub-managers created"));
}

void ULesFightMultiplayerManager::ConfigureNetworkSettings()
{
    if (!NetworkSettings) return;

    if (MatchManager)
    {
        MatchManager->SetMaxRounds(NetworkSettings->MaxRounds);
        MatchManager->SetRoundTimeLimit(NetworkSettings->RoundTimeLimit);
    }

    if (ConnectionManager)
    {
        ConnectionManager->SetConnectionTimeout(NetworkSettings->ConnectionTimeout);
    }

    if (NetworkOptimizer)
    {
        NetworkOptimizer->SetBandwidthLimit(NetworkSettings->MaxBandwidthKbps);
        NetworkOptimizer->SetReplicationRate(NetworkSettings->ReplicationRate);
    }

    if (NetworkPrediction)
    {
        NetworkPrediction->SetPredictionEnabled(NetworkSettings->bEnableClientPrediction);
    }

    if (LagCompensation)
    {
        LagCompensation->SetEnabled(NetworkSettings->bEnableLagCompensation);
    }
}
