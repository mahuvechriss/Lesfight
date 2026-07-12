#include "LesFightMultiplayerLobbyUI.h"
#include "Framework/UI/Data/LesFightUIData.h"

void ULesFightMultiplayerLobbyUI::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    CurrentArenaName = FText::FromString(TEXT("Training Room"));
    RoundLimit = 3;
    RoundTimeLimit = 99;
    bStageHazardsEnabled = true;
}

void ULesFightMultiplayerLobbyUI::SetLocalPlayerInfo(FText PlayerName, UTexture2D* Avatar, class USkeletalMesh* FighterMesh)
{
    LocalPlayerName = PlayerName;
}

void ULesFightMultiplayerLobbyUI::AddRemotePlayer(int32 PlayerIndex, FText PlayerName, UTexture2D* Avatar, bool bReady, float Ping)
{
    FLobbyPlayerEntry* Existing = Players.FindByPredicate([PlayerIndex](const FLobbyPlayerEntry& Entry)
    {
        return Entry.PlayerIndex == PlayerIndex;
    });

    if (Existing)
    {
        Existing->PlayerName = PlayerName;
        Existing->Avatar = Avatar;
        Existing->bReady = bReady;
        Existing->Ping = Ping;
    }
    else
    {
        FLobbyPlayerEntry NewEntry;
        NewEntry.PlayerIndex = PlayerIndex;
        NewEntry.PlayerName = PlayerName;
        NewEntry.Avatar = Avatar;
        NewEntry.bReady = bReady;
        NewEntry.Ping = Ping;
        Players.Add(NewEntry);
    }
}

void ULesFightMultiplayerLobbyUI::RemoveRemotePlayer(int32 PlayerIndex)
{
    Players.RemoveAll([PlayerIndex](const FLobbyPlayerEntry& Entry)
    {
        return Entry.PlayerIndex == PlayerIndex;
    });
}

void ULesFightMultiplayerLobbyUI::UpdatePlayerReady(int32 PlayerIndex, bool bReady)
{
    FLobbyPlayerEntry* Entry = Players.FindByPredicate([PlayerIndex](const FLobbyPlayerEntry& E)
    {
        return E.PlayerIndex == PlayerIndex;
    });
    if (Entry)
    {
        Entry->bReady = bReady;
    }
}

void ULesFightMultiplayerLobbyUI::UpdatePlayerPing(int32 PlayerIndex, float PingMs)
{
    FLobbyPlayerEntry* Entry = Players.FindByPredicate([PlayerIndex](const FLobbyPlayerEntry& E)
    {
        return E.PlayerIndex == PlayerIndex;
    });
    if (Entry)
    {
        Entry->Ping = PingMs;
    }
}

void ULesFightMultiplayerLobbyUI::SetArenaSelection(FText ArenaName, UTexture2D* ArenaPreviewImage)
{
    CurrentArenaName = ArenaName;
    ArenaPreview = ArenaPreviewImage;
    OnArenaChanged.Broadcast(ArenaName);
}

void ULesFightMultiplayerLobbyUI::SetMatchRules(int32 RoundCount, float RoundDuration, bool bStageHazards)
{
    RoundLimit = RoundCount;
    RoundTimeLimit = FMath::FloorToInt(RoundDuration);
    bStageHazardsEnabled = bStageHazards;
}

void ULesFightMultiplayerLobbyUI::SetLobbyStatus(FText Status)
{
}

void ULesFightMultiplayerLobbyUI::StartMatchCountdown_Implementation(int32 Seconds)
{
    UE_LOG(LogTemp, Log, TEXT("Match countdown: %d seconds"), Seconds);
}
