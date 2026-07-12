#include "LesFightNetworkUI.h"
#include "LesFightMultiplayerManager.h"
#include "Engine/World.h"

ULesFightNetworkUI::ULesFightNetworkUI()
    : bUIVisible(false)
    , CurrentScreen(TEXT("None"))
{
}

void ULesFightNetworkUI::Initialize(ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
}

void ULesFightNetworkUI::ShowHostScreen()
{
    bUIVisible = true;
    CurrentScreen = TEXT("Host");
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkUI: Show Host Screen"));
}

void ULesFightNetworkUI::ShowJoinScreen()
{
    bUIVisible = true;
    CurrentScreen = TEXT("Join");
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkUI: Show Join Screen"));

    if (MultiplayerManager.IsValid())
    {
        MultiplayerManager->FindLANGames();
    }
}

void ULesFightNetworkUI::ShowLobbyScreen()
{
    bUIVisible = true;
    CurrentScreen = TEXT("Lobby");
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkUI: Show Lobby Screen"));
}

void ULesFightNetworkUI::ShowMatchCountdown(int32 Seconds)
{
    OnMatchCountdown.Broadcast(Seconds);
    UE_LOG(LogLesFightNetwork, Log, TEXT("Match countdown: %d"), Seconds);
}

void ULesFightNetworkUI::ShowMatchSummary(int32 WinnerIndex)
{
    TArray<FNetworkPlayerInfo> Players;
    if (MultiplayerManager.IsValid())
    {
        Players = MultiplayerManager->GetPlayerList();
    }
    OnMatchSummary.Broadcast(WinnerIndex, Players);
}

void ULesFightNetworkUI::ShowLoadingScreen(const FString& LoadMessage)
{
    bUIVisible = true;
    CurrentScreen = TEXT("Loading");
}

void ULesFightNetworkUI::ShowError(const FString& ErrorMessage)
{
    UE_LOG(LogLesFightNetwork, Error, TEXT("UI Error: %s"), *ErrorMessage);
}

void ULesFightNetworkUI::ShowConnectionStatus(
    const FString& Status, EConnectionQuality Quality)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("Connection: %s (Quality: %d)"),
        *Status, static_cast<int32>(Quality));
}

void ULesFightNetworkUI::UpdatePingDisplay(int32 PingMs)
{
}

void ULesFightNetworkUI::UpdatePlayerList(const TArray<FNetworkPlayerInfo>& Players)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("Player list updated: %d players"), Players.Num());
}

void ULesFightNetworkUI::HideAllNetworkUI()
{
    bUIVisible = false;
    CurrentScreen = TEXT("None");
}

void ULesFightNetworkUI::OnSessionsFound(const TArray<FLANSessionInfo>& Sessions)
{
    OnLANGamesFound.Broadcast(Sessions);
}

void ULesFightNetworkUI::OnConnectionStateChanged(ENetworkSessionState NewState)
{
    OnConnectionStatusChanged.Broadcast(static_cast<int32>(NewState));
}

void ULesFightNetworkUI::OnMatchStateChanged(ENetworkMatchState NewState)
{
    switch (NewState)
    {
    case ENetworkMatchState::Countdown:
        ShowMatchCountdown(3);
        break;
    case ENetworkMatchState::RoundInProgress:
        ShowLoadingScreen(TEXT(""));
        break;
    case ENetworkMatchState::MatchEnd:
        break;
    }
}

void ULesFightNetworkUI::NotifyRoundStart(int32 RoundNumber)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("Round %d started"), RoundNumber);
}

void ULesFightNetworkUI::NotifyRoundEnd(int32 WinnerIndex, EWinCondition WinCondition)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("Round ended. Winner: %d"), WinnerIndex);
}

void ULesFightNetworkUI::NotifyMatchEnd(int32 WinnerIndex)
{
    ShowMatchSummary(WinnerIndex);
}

void ULesFightNetworkUI::NotifyPlayerDisconnected(int32 PlayerIndex)
{
    OnPlayerLeftLobby.Broadcast(PlayerIndex);
}

void ULesFightNetworkUI::SetUIEnabled(bool bEnabled)
{
    if (!bEnabled)
    {
        HideAllNetworkUI();
    }
}
