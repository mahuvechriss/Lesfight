#include "LesFightJoinGameUI.h"
#include "Framework/UI/Data/LesFightUIData.h"

void ULesFightJoinGameUI::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SelectedIndex = -1;
    bSearching = false;
}

void ULesFightJoinGameUI::AddGameSession(FName SessionID, FText SessionName, int32 PlayerCount, int32 MaxPlayers, float Ping)
{
    FGameSessionEntry* Existing = AvailableSessions.FindByPredicate([SessionID](const FGameSessionEntry& Entry)
    {
        return Entry.SessionID == SessionID;
    });

    if (Existing)
    {
        Existing->SessionName = SessionName;
        Existing->PlayerCount = PlayerCount;
        Existing->MaxPlayers = MaxPlayers;
        Existing->Ping = Ping;
    }
    else
    {
        FGameSessionEntry NewEntry;
        NewEntry.SessionID = SessionID;
        NewEntry.SessionName = SessionName;
        NewEntry.PlayerCount = PlayerCount;
        NewEntry.MaxPlayers = MaxPlayers;
        NewEntry.Ping = Ping;
        AvailableSessions.Add(NewEntry);
    }
}

void ULesFightJoinGameUI::RemoveGameSession(FName SessionID)
{
    AvailableSessions.RemoveAll([SessionID](const FGameSessionEntry& Entry)
    {
        return Entry.SessionID == SessionID;
    });

    if (SelectedIndex >= AvailableSessions.Num())
    {
        SelectedIndex = -1;
    }
}

void ULesFightJoinGameUI::ClearGameSessions()
{
    AvailableSessions.Empty();
    SelectedIndex = -1;
    SelectedSessionID = NAME_None;
}

void ULesFightJoinGameUI::SelectSession(int32 Index)
{
    if (AvailableSessions.IsValidIndex(Index))
    {
        SelectedIndex = Index;
        SelectedSessionID = AvailableSessions[Index].SessionID;
    }
}

FName ULesFightJoinGameUI::GetSelectedSession() const
{
    return SelectedSessionID;
}

void ULesFightJoinGameUI::SearchForGames()
{
    bSearching = true;
    ClearGameSessions();
    OnSearchStarted.Broadcast();
}

void ULesFightJoinGameUI::RefreshList()
{
    ClearGameSessions();
    SearchForGames();
}

void ULesFightJoinGameUI::StopSearch()
{
    bSearching = false;
    OnSearchComplete.Broadcast();
}

void ULesFightJoinGameUI::SetSearchStatus(FText Status, bool bInSearching)
{
    bSearching = bInSearching;
}

void ULesFightJoinGameUI::JoinSelectedGame()
{
    if (SelectedSessionID == NAME_None)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot join: no session selected"));
        return;
    }
    OnGameJoined.Broadcast(SelectedSessionID);
}

void ULesFightJoinGameUI::CancelJoin()
{
    OnJoinCancelled.Broadcast();
}
