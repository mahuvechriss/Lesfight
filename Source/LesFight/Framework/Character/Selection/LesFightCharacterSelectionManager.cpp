#include "LesFightCharacterSelectionManager.h"
#include "LesFight.h"

ULesFightCharacterSelectionManager::ULesFightCharacterSelectionManager()
{
}

void ULesFightCharacterSelectionManager::Initialize()
{
    UE_LOG(LogLesFight, Log, TEXT("CharacterSelectionManager initialized"));
}

void ULesFightCharacterSelectionManager::PopulateCharacterList(const TArray<FCharacterTableRow>& CharacterDataList)
{
    AvailableCharacters.Empty();

    for (const FCharacterTableRow& Data : CharacterDataList)
    {
        FCharacterSelectionEntry Entry;
        Entry.CharacterID = Data.Identity.CharacterID;
        Entry.DisplayName = Data.Identity.Nickname.IsEmpty()
            ? Data.Identity.CharacterName : Data.Identity.Nickname;
        Entry.bIsUnlocked = Data.bIsUnlockedByDefault;
        Entry.UnlockCondition = Data.UnlockCondition;

        AvailableCharacters.Add(Entry);
    }

    UE_LOG(LogLesFight, Log, TEXT("Populated %d characters in selection list"), AvailableCharacters.Num());
}

bool ULesFightCharacterSelectionManager::SelectCharacter(int32 PlayerIndex, FName CharacterID)
{
    if (!IsCharacterUnlocked(CharacterID))
    {
        UE_LOG(LogLesFight, Warning, TEXT("Character %s is locked"), *CharacterID.ToString());
        return false;
    }

    for (auto& Entry : AvailableCharacters)
    {
        if (Entry.CharacterID == CharacterID && Entry.SelectedByPlayer >= 0 && Entry.SelectedByPlayer != PlayerIndex)
        {
            UE_LOG(LogLesFight, Warning, TEXT("Character %s already selected by player %d"),
                *CharacterID.ToString(), Entry.SelectedByPlayer);
            return false;
        }
    }

    if (PlayerSelections.Contains(PlayerIndex))
    {
        FName PreviousID = PlayerSelections[PlayerIndex];
        for (auto& Entry : AvailableCharacters)
        {
            if (Entry.CharacterID == PreviousID)
            {
                Entry.bIsSelected = false;
                Entry.SelectedByPlayer = -1;
                break;
            }
        }
    }

    PlayerSelections.Add(PlayerIndex, CharacterID);

    for (auto& Entry : AvailableCharacters)
    {
        if (Entry.CharacterID == CharacterID)
        {
            Entry.bIsSelected = true;
            Entry.SelectedByPlayer = PlayerIndex;
            break;
        }
    }

    OnCharacterSelectionChanged.Broadcast(PlayerIndex);
    return true;
}

void ULesFightCharacterSelectionManager::DeselectCharacter(int32 PlayerIndex)
{
    if (!PlayerSelections.Contains(PlayerIndex)) return;

    FName CharacterID = PlayerSelections[PlayerIndex];
    PlayerSelections.Remove(PlayerIndex);

    for (auto& Entry : AvailableCharacters)
    {
        if (Entry.CharacterID == CharacterID)
        {
            Entry.bIsSelected = false;
            Entry.SelectedByPlayer = -1;
            break;
        }
    }

    OnCharacterSelectionChanged.Broadcast(PlayerIndex);
}

void ULesFightCharacterSelectionManager::ConfirmSelection(int32 PlayerIndex)
{
    if (PlayerSelections.Contains(PlayerIndex))
    {
        PlayersReady.Add(PlayerIndex);
    }
}

void ULesFightCharacterSelectionManager::UnlockCharacter(FName CharacterID)
{
    LockedCharacters.Remove(CharacterID);

    for (auto& Entry : AvailableCharacters)
    {
        if (Entry.CharacterID == CharacterID)
        {
            Entry.bIsUnlocked = true;
            OnCharacterLockedChanged.Broadcast(CharacterID, false);
            break;
        }
    }
}

void ULesFightCharacterSelectionManager::LockCharacter(FName CharacterID)
{
    LockedCharacters.Add(CharacterID);

    for (auto& Entry : AvailableCharacters)
    {
        if (Entry.CharacterID == CharacterID)
        {
            Entry.bIsUnlocked = false;
            OnCharacterLockedChanged.Broadcast(CharacterID, true);
            break;
        }
    }
}

void ULesFightCharacterSelectionManager::ResetSelections()
{
    PlayerSelections.Empty();
    PlayersReady.Empty();

    for (auto& Entry : AvailableCharacters)
    {
        Entry.bIsSelected = false;
        Entry.SelectedByPlayer = -1;
    }
}

TArray<FCharacterSelectionEntry> ULesFightCharacterSelectionManager::GetUnlockedCharacters() const
{
    TArray<FCharacterSelectionEntry> Unlocked;
    for (const auto& Entry : AvailableCharacters)
    {
        if (Entry.bIsUnlocked)
        {
            Unlocked.Add(Entry);
        }
    }
    return Unlocked;
}

FCharacterSelectionEntry ULesFightCharacterSelectionManager::GetCharacterEntry(FName CharacterID) const
{
    for (const auto& Entry : AvailableCharacters)
    {
        if (Entry.CharacterID == CharacterID)
            return Entry;
    }
    return FCharacterSelectionEntry();
}

FName ULesFightCharacterSelectionManager::GetSelectedCharacter(int32 PlayerIndex) const
{
    if (PlayerSelections.Contains(PlayerIndex))
        return PlayerSelections[PlayerIndex];
    return NAME_None;
}

bool ULesFightCharacterSelectionManager::IsCharacterUnlocked(FName CharacterID) const
{
    return !LockedCharacters.Contains(CharacterID);
}

bool ULesFightCharacterSelectionManager::AreAllPlayersReady() const
{
    return PlayersReady.Num() >= 2;
}
