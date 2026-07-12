#include "LesFightHostGameUI.h"
#include "Framework/UI/Data/LesFightUIData.h"

void ULesFightHostGameUI::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    SessionName = FText::FromString(TEXT("My Session"));
    MaxPlayers = 4;
    bPrivateMatch = false;
}

void ULesFightHostGameUI::SetSessionName(FText Name)
{
    SessionName = Name;
}

FText ULesFightHostGameUI::GetSessionName() const
{
    return SessionName;
}

void ULesFightHostGameUI::SetMaxPlayers(int32 Count)
{
    MaxPlayers = FMath::Clamp(Count, 2, 16);
}

int32 ULesFightHostGameUI::GetMaxPlayers() const
{
    return MaxPlayers;
}

void ULesFightHostGameUI::SelectArena(FName ArenaID)
{
    SelectedArenaID = ArenaID;
}

FName ULesFightHostGameUI::GetSelectedArena() const
{
    return SelectedArenaID;
}

void ULesFightHostGameUI::SetGameMode(FText Mode)
{
    GameModeText = Mode;
}

FText ULesFightHostGameUI::GetGameMode() const
{
    return GameModeText;
}

void ULesFightHostGameUI::SetPrivateMatch(bool bPrivate)
{
    bPrivateMatch = bPrivate;
}

bool ULesFightHostGameUI::IsPrivateMatch() const
{
    return bPrivateMatch;
}

void ULesFightHostGameUI::SetAvailableArenas_Implementation(TArray<FText> ArenaNames)
{
}

void ULesFightHostGameUI::StartHosting()
{
    if (SessionName.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot host: session name is empty"));
        return;
    }
    FName SessionID = FName(*SessionName.ToString());
    OnHostStarted.ExecuteIfBound(SessionID, GameModeText);
}

void ULesFightHostGameUI::CancelHosting()
{
    OnHostCancelled.Broadcast();
}

void ULesFightHostGameUI::SetHostingStatus(FText Status, bool bSuccess)
{
}
