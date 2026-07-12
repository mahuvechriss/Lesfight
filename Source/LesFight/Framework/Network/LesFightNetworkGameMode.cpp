#include "LesFightNetworkGameMode.h"
#include "LesFightNetworkGameState.h"
#include "LesFightNetworkPlayerController.h"
#include "LesFightNetworkPlayerState.h"
#include "LesFightMatchManager.h"
#include "LesFightMultiplayerManager.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"

ALesFightNetworkGameMode::ALesFightNetworkGameMode()
    : MaxPlayers(2)
    , CurrentMatchState(ENetworkMatchState::None)
    , MatchManager(nullptr)
    , MultiplayerManager(nullptr)
    , RoundTimeLimit(99.0f)
    , MaxRounds(3)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.1f;

    GameStateClass = ALesFightNetworkGameState::StaticClass();
    PlayerStateClass = ALesFightNetworkPlayerState::StaticClass();
    PlayerControllerClass = ALesFightNetworkPlayerController::StaticClass();
}

void ALesFightNetworkGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkGameMode started"));
}

void ALesFightNetworkGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (MatchManager && CurrentMatchState == ENetworkMatchState::RoundInProgress)
    {
        MatchManager->TickRoundTimer(DeltaTime);
    }
}

void ALesFightNetworkGameMode::PreInitializeComponents()
{
    Super::PreInitializeComponents();

    if (ALesFightNetworkGameState* GS = GetGameState<ALesFightNetworkGameState>())
    {
        GS->SetMaxRounds(MaxRounds);
        GS->SetRoundTimeLimit(RoundTimeLimit);
    }
}

void ALesFightNetworkGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (NewPlayer)
    {
        ConnectedPlayers.Add(NewPlayer);
        UE_LOG(LogLesFightNetwork, Log, TEXT("Player logged in. Total: %d"), ConnectedPlayers.Num());

        if (ALesFightNetworkPlayerState* PS = NewPlayer->GetPlayerState<ALesFightNetworkPlayerState>())
        {
            PS->SetPlayerIndex(ConnectedPlayers.Num() - 1);
        }

        if (ALesFightNetworkPlayerController* PC = Cast<ALesFightNetworkPlayerController>(NewPlayer))
        {
            PlayerControllers.Add(ConnectedPlayers.Num() - 1, PC);
        }
    }
}

void ALesFightNetworkGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);

    ConnectedPlayers.Remove(Cast<APlayerController>(Exiting));
    UE_LOG(LogLesFightNetwork, Warning, TEXT("Player logged out. Total: %d"), ConnectedPlayers.Num());
}

void ALesFightNetworkGameMode::StartNetworkMatch()
{
    if (CurrentMatchState != ENetworkMatchState::None) return;

    CurrentMatchState = ENetworkMatchState::WaitingForPlayers;
    BroadcastMatchStateToAll(CurrentMatchState);

    if (ALesFightNetworkGameState* GS = GetNetworkGameState())
    {
        GS->OnMatchStarted();
    }

    SpawnPlayerCharacters();
    StartNetworkRound(1);
}

void ALesFightNetworkGameMode::EndNetworkMatch(int32 WinnerPlayerIndex)
{
    CurrentMatchState = ENetworkMatchState::MatchEnd;
    BroadcastMatchStateToAll(CurrentMatchState);

    if (ALesFightNetworkGameState* GS = GetNetworkGameState())
    {
        GS->OnMatchEnded(WinnerPlayerIndex);
    }

    UE_LOG(LogLesFightNetwork, Log, TEXT("Network match ended. Winner: %d"), WinnerPlayerIndex);
}

void ALesFightNetworkGameMode::StartNetworkRound(int32 RoundNumber)
{
    CurrentMatchState = ENetworkMatchState::Countdown;
    BroadcastMatchStateToAll(CurrentMatchState);

    if (ALesFightNetworkGameState* GS = GetNetworkGameState())
    {
        GS->OnRoundStarted(RoundNumber);
    }

    FTimerHandle UnusedHandle;
    GetWorldTimerManager().SetTimer(UnusedHandle, FTimerDelegate::CreateWeakLambda(this, [this, RoundNumber]()
    {
        CurrentMatchState = ENetworkMatchState::RoundInProgress;
        BroadcastMatchStateToAll(CurrentMatchState);
    }), 3.0f, false);
}

void ALesFightNetworkGameMode::EndNetworkRound(int32 WinnerPlayerIndex)
{
    CurrentMatchState = ENetworkMatchState::RoundEnd;
    BroadcastMatchStateToAll(CurrentMatchState);

    if (ALesFightNetworkGameState* GS = GetNetworkGameState())
    {
        GS->OnRoundEnded(WinnerPlayerIndex);
    }

    int32 MaxWins = (MaxRounds / 2) + 1;
    TArray<APlayerState*> AllPlayers = GameState ? GameState->PlayerArray : TArray<APlayerState*>();
    TMap<int32, int32> RoundWins;

    for (APlayerState* PS : AllPlayers)
    {
        if (ALesFightNetworkPlayerState* NFPS = Cast<ALesFightNetworkPlayerState>(PS))
        {
            int32 CurrentWins = NFPS->GetRoundWins();
            if (NFPS->GetPlayerIndex() == WinnerPlayerIndex)
            {
                NFPS->IncrementRoundWins();
                CurrentWins++;
            }
            RoundWins.Add(NFPS->GetPlayerIndex(), CurrentWins);
        }
    }

    int32 WinnerTotalWins = RoundWins.FindRef(WinnerPlayerIndex);
    if (WinnerTotalWins >= MaxWins)
    {
        EndNetworkMatch(WinnerPlayerIndex);
    }
    else
    {
        StartNetworkRound(CurrentMatchData.RoundNumber + 1);
    }
}

void ALesFightNetworkGameMode::HandleCombatActionFromPlayer(
    int32 PlayerIndex, const FNetworkCombatAction& Action)
{
    for (auto& Pair : PlayerControllers)
    {
        if (Pair.Key != PlayerIndex && Pair.Value)
        {
            Pair.Value->ClientReceiveCombatAction(PlayerIndex, Action);
        }
    }
}

void ALesFightNetworkGameMode::SetMaxPlayers(int32 Count)
{
    MaxPlayers = FMath::Clamp(Count, 2, 8);
}

int32 ALesFightNetworkGameMode::GetConnectedPlayerCount() const
{
    return ConnectedPlayers.Num();
}

bool ALesFightNetworkGameMode::AreMinPlayersConnected() const
{
    return ConnectedPlayers.Num() >= 2;
}

void ALesFightNetworkGameMode::OnPlayerReady(int32 PlayerIndex, bool bReady)
{
    PlayerReadyMap.Add(PlayerIndex, bReady);

    bool bAllReady = true;
    for (int32 i = 0; i < ConnectedPlayers.Num(); i++)
    {
        if (!PlayerReadyMap.FindRef(i))
        {
            bAllReady = false;
            break;
        }
    }

    if (bAllReady && ConnectedPlayers.Num() >= 2)
    {
        StartNetworkMatch();
    }
}

void ALesFightNetworkGameMode::RequestFullStateSync()
{
    if (ALesFightNetworkGameState* GS = GetNetworkGameState())
    {
        GS->OnFullStateSyncRequested();
    }
}

void ALesFightNetworkGameMode::SetMatchManager(ULesFightMatchManager* InMatchManager)
{
    MatchManager = InMatchManager;
}

void ALesFightNetworkGameMode::SetMultiplayerManager(ULesFightMultiplayerManager* InMultiplayerManager)
{
    MultiplayerManager = InMultiplayerManager;
}

void ALesFightNetworkGameMode::BroadcastMatchStateToAll(ENetworkMatchState NewState)
{
    for (auto& Pair : PlayerControllers)
    {
        if (Pair.Value)
        {
            Pair.Value->ClientUpdateMatchState(NewState);
        }
    }
}

void ALesFightNetworkGameMode::SpawnPlayerCharacters()
{
}

ALesFightNetworkGameState* ALesFightNetworkGameMode::GetNetworkGameState() const
{
    return GetGameState<ALesFightNetworkGameState>();
}
