#include "LesFightCharacterDataManager.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "Misc/DateTime.h"

void ULesFightCharacterDataManager::Initialize()
{
}

void ULesFightCharacterDataManager::Shutdown()
{
	SavedCharacters.Empty();
	bLoaded = false;
}

ESaveResult ULesFightCharacterDataManager::SaveCharacter(FCharacterSaveData CharacterData)
{
	if (CharacterData.CharacterID == NAME_None)
	{
		return ESaveResult::Invalid;
	}

	CharacterData.LastModified = FDateTime::Now();

	for (int32 i = 0; i < SavedCharacters.Num(); i++)
	{
		if (SavedCharacters[i].CharacterID == CharacterData.CharacterID)
		{
			SavedCharacters[i] = CharacterData;
			OnCharacterSaved.Broadcast(CharacterData.CharacterID);
			return ESaveResult::Success;
		}
	}

	if (SavedCharacters.Num() >= MaxCharacters)
	{
		return ESaveResult::SlotFull;
	}

	SavedCharacters.Add(CharacterData);
	OnCharacterSaved.Broadcast(CharacterData.CharacterID);
	return ESaveResult::Success;
}

FCharacterSaveData ULesFightCharacterDataManager::LoadCharacter(FName CharacterID)
{
	for (const FCharacterSaveData& Data : SavedCharacters)
	{
		if (Data.CharacterID == CharacterID)
		{
			return Data;
		}
	}

	return FCharacterSaveData();
}

bool ULesFightCharacterDataManager::DeleteCharacter(FName CharacterID)
{
	for (int32 i = 0; i < SavedCharacters.Num(); i++)
	{
		if (SavedCharacters[i].CharacterID == CharacterID)
		{
			SavedCharacters.RemoveAt(i);
			OnCharacterDeleted.Broadcast(CharacterID);
			return true;
		}
	}
	return false;
}

TArray<FCharacterSaveData> ULesFightCharacterDataManager::GetAllSavedCharacters()
{
	return SavedCharacters;
}

FCharacterSaveData ULesFightCharacterDataManager::GetCharacter(FName CharacterID)
{
	for (const FCharacterSaveData& Data : SavedCharacters)
	{
		if (Data.CharacterID == CharacterID)
		{
			return Data;
		}
	}
	return FCharacterSaveData();
}

int32 ULesFightCharacterDataManager::GetCharacterCount()
{
	return SavedCharacters.Num();
}

bool ULesFightCharacterDataManager::CharacterExists(FName CharacterID)
{
	for (const FCharacterSaveData& Data : SavedCharacters)
	{
		if (Data.CharacterID == CharacterID)
		{
			return true;
		}
	}
	return false;
}

FName ULesFightCharacterDataManager::DuplicateCharacter(FName SourceCharacterID, FText NewName)
{
	FCharacterSaveData Source = LoadCharacter(SourceCharacterID);

	if (Source.CharacterID == NAME_None)
	{
		return NAME_None;
	}

	FName NewID = FName(*FString::Printf(TEXT("Char_%lld"), FDateTime::Now().Ticks()));

	FCharacterSaveData Duplicate;
	Duplicate.CharacterID = NewID;
	Duplicate.CharacterName = NewName;
	Duplicate.Appearance = Source.Appearance;
	Duplicate.Gameplay = Source.Gameplay;
	Duplicate.CreatedDate = FDateTime::Now();
	Duplicate.LastModified = FDateTime::Now();

	SavedCharacters.Add(Duplicate);
	OnCharacterSaved.Broadcast(NewID);

	return NewID;
}

TArray<FCharacterSaveData> ULesFightCharacterDataManager::GetCharactersByStyle(EFightingStyle Style)
{
	TArray<FCharacterSaveData> Results;

	for (const FCharacterSaveData& Data : SavedCharacters)
	{
		if (Data.Gameplay.Style == Style)
		{
			Results.Add(Data);
		}
	}

	return Results;
}

TArray<FCharacterSaveData> ULesFightCharacterDataManager::GetCharactersByType(bool bAIGenerated)
{
	TArray<FCharacterSaveData> Results;

	for (const FCharacterSaveData& Data : SavedCharacters)
	{
		if (Data.Appearance.bIsAIGenerated == bAIGenerated)
		{
			Results.Add(Data);
		}
	}

	return Results;
}

bool ULesFightCharacterDataManager::UpdateCharacterAppearance(FName CharacterID, FCharacterAppearanceData Appearance)
{
	for (int32 i = 0; i < SavedCharacters.Num(); i++)
	{
		if (SavedCharacters[i].CharacterID == CharacterID)
		{
			SavedCharacters[i].Appearance = Appearance;
			SavedCharacters[i].LastModified = FDateTime::Now();
			OnCharacterUpdated.Broadcast(CharacterID);
			return true;
		}
	}
	return false;
}

bool ULesFightCharacterDataManager::UpdateCharacterGameplay(FName CharacterID, FCharacterGameplayData Gameplay)
{
	for (int32 i = 0; i < SavedCharacters.Num(); i++)
	{
		if (SavedCharacters[i].CharacterID == CharacterID)
		{
			SavedCharacters[i].Gameplay = Gameplay;
			SavedCharacters[i].LastModified = FDateTime::Now();
			OnCharacterUpdated.Broadcast(CharacterID);
			return true;
		}
	}
	return false;
}

int32 ULesFightCharacterDataManager::GetMaxCharacters()
{
	return MaxCharacters;
}
