#include "Framework/Data/Core/LesFightSaveManager.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/BufferReader.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void ULesFightSaveManager::Initialize()
{
	BaseSaveDirectory = FPaths::ProjectSavedDir() / TEXT("SaveData");
	bInitialized = CreateSlotDirectory(CurrentSlotIndex);
}

void ULesFightSaveManager::Shutdown()
{
	bInitialized = false;
}

FString ULesFightSaveManager::GetSaveDirectory() const
{
	return BaseSaveDirectory / FString::Printf(TEXT("Slot%d"), CurrentSlotIndex) / TEXT("");
}

bool ULesFightSaveManager::CreateSlotDirectory(int32 SlotIndex) const
{
	FString SlotDir = BaseSaveDirectory / FString::Printf(TEXT("Slot%d"), SlotIndex);
	if (!IFileManager::Get().DirectoryExists(*SlotDir))
	{
		return IFileManager::Get().MakeDirectory(*SlotDir, true);
	}
	return true;
}

FString ULesFightSaveManager::GetCategoryFileName(EDataCategory Category, const FName& Identifier) const
{
	const UEnum* EnumPtr = StaticEnum<EDataCategory>();
	FString CategoryName = EnumPtr ? EnumPtr->GetNameStringByValue((int64)Category) : TEXT("Unknown");
	return GetSaveDirectory() / CategoryName + TEXT("_") + Identifier.ToString() + TEXT(".sav");
}

ESaveResult ULesFightSaveManager::SaveDataToFile(EDataCategory Category, const FName& Identifier, const TArray<uint8>& Data)
{
	if (!bInitialized)
	{
		return ESaveResult::Failed;
	}

	FString FilePath = GetCategoryFileName(Category, Identifier);

	if (FFileHelper::SaveArrayToFile(Data, *FilePath))
	{
		OnSaveCompleted.Broadcast(Category, Identifier);
		return ESaveResult::Success;
	}

	OnSaveFailed.Broadcast(Category, Identifier);
	return ESaveResult::Failed;
}

bool ULesFightSaveManager::LoadDataFromFile(EDataCategory Category, const FName& Identifier, TArray<uint8>& OutData) const
{
	if (!bInitialized)
	{
		return false;
	}

	FString FilePath = GetCategoryFileName(Category, Identifier);
	return FFileHelper::LoadFileToArray(OutData, *FilePath);
}

void ULesFightSaveManager::SetSaveSlot(int32 SlotIndex)
{
	if (SlotIndex >= 0 && SlotIndex < MaxSlots)
	{
		CurrentSlotIndex = SlotIndex;
		CreateSlotDirectory(CurrentSlotIndex);
	}
}

TArray<int32> ULesFightSaveManager::GetAvailableSlots() const
{
	TArray<int32> Available;
	for (int32 i = 0; i < MaxSlots; ++i)
	{
		FString SlotDir = BaseSaveDirectory / FString::Printf(TEXT("Slot%d"), i);
		if (IFileManager::Get().DirectoryExists(*SlotDir))
		{
			Available.Add(i);
		}
	}
	return Available;
}

bool ULesFightSaveManager::DoesSaveExist(EDataCategory Category, const FName& Identifier)
{
	FString FilePath = GetCategoryFileName(Category, Identifier);
	return IFileManager::Get().FileExists(*FilePath);
}

bool ULesFightSaveManager::DeleteSave(EDataCategory Category, const FName& Identifier)
{
	FString FilePath = GetCategoryFileName(Category, Identifier);
	return IFileManager::Get().Delete(*FilePath, true, false);
}

ESaveResult ULesFightSaveManager::SaveProfile(const FPlayerProfileData& ProfileData)
{
	FBufferArchive Archive;
	Archive << const_cast<FPlayerProfileData&>(ProfileData);
	return SaveDataToFile(EDataCategory::Profile, ProfileData.ProfileID, Archive);
}

ESaveResult ULesFightSaveManager::SaveCharacter(const FCharacterSaveData& CharacterData)
{
	FBufferArchive Archive;
	Archive << const_cast<FCharacterSaveData&>(CharacterData);
	return SaveDataToFile(EDataCategory::Character, CharacterData.CharacterID, Archive);
}

ESaveResult ULesFightSaveManager::SaveSettings(const FSettingsData& Settings)
{
	FBufferArchive Archive;
	Archive << const_cast<FSettingsData&>(Settings);
	return SaveDataToFile(EDataCategory::Settings, FName(TEXT("Global")), Archive);
}

ESaveResult ULesFightSaveManager::SaveStatistics(const FMatchStatisticsData& Stats)
{
	FBufferArchive Archive;
	Archive << const_cast<FMatchStatisticsData&>(Stats);
	return SaveDataToFile(EDataCategory::Statistics, FName(TEXT("Global")), Archive);
}

ESaveResult ULesFightSaveManager::SaveProgression(const FProgressionData& Progression)
{
	FBufferArchive Archive;
	Archive << const_cast<FProgressionData&>(Progression);
	return SaveDataToFile(EDataCategory::Progression, FName(TEXT("Global")), Archive);
}

ESaveResult ULesFightSaveManager::SaveMatchHistory(const TArray<FMatchHistoryEntry>& History)
{
	FBufferArchive Archive;
	Archive << const_cast<TArray<FMatchHistoryEntry>&>(History);
	return SaveDataToFile(EDataCategory::MatchHistory, FName(TEXT("Global")), Archive);
}

ESaveResult ULesFightSaveManager::SaveAll(const FPlayerProfileData& Profile, const TArray<FCharacterSaveData>& Characters, const FSettingsData& Settings)
{
	ESaveResult Result = SaveProfile(Profile);
	if (Result != ESaveResult::Success) return Result;

	Result = SaveSettings(Settings);
	if (Result != ESaveResult::Success) return Result;

	for (const FCharacterSaveData& Character : Characters)
	{
		Result = SaveCharacter(Character);
		if (Result != ESaveResult::Success) return Result;
	}

	return ESaveResult::Success;
}

FPlayerProfileData ULesFightSaveManager::LoadProfile(const FName& ProfileID)
{
	FPlayerProfileData Data;
	TArray<uint8> Buffer;
	if (LoadDataFromFile(EDataCategory::Profile, ProfileID, Buffer))
	{
		FMemoryReader Reader(Buffer);
		Reader << Data;
		OnLoadCompleted.Broadcast(EDataCategory::Profile, ProfileID);
	}
	else
	{
		OnLoadFailed.Broadcast(EDataCategory::Profile, ProfileID);
	}
	return Data;
}

FCharacterSaveData ULesFightSaveManager::LoadCharacter(const FName& CharacterID)
{
	FCharacterSaveData Data;
	TArray<uint8> Buffer;
	if (LoadDataFromFile(EDataCategory::Character, CharacterID, Buffer))
	{
		FMemoryReader Reader(Buffer);
		Reader << Data;
		OnLoadCompleted.Broadcast(EDataCategory::Character, CharacterID);
	}
	else
	{
		OnLoadFailed.Broadcast(EDataCategory::Character, CharacterID);
	}
	return Data;
}

FSettingsData ULesFightSaveManager::LoadSettings()
{
	FSettingsData Data;
	TArray<uint8> Buffer;
	if (LoadDataFromFile(EDataCategory::Settings, FName(TEXT("Global")), Buffer))
	{
		FMemoryReader Reader(Buffer);
		Reader << Data;
		OnLoadCompleted.Broadcast(EDataCategory::Settings, FName(TEXT("Global")));
	}
	else
	{
		OnLoadFailed.Broadcast(EDataCategory::Settings, FName(TEXT("Global")));
	}
	return Data;
}

FMatchStatisticsData ULesFightSaveManager::LoadStatistics()
{
	FMatchStatisticsData Data;
	TArray<uint8> Buffer;
	if (LoadDataFromFile(EDataCategory::Statistics, FName(TEXT("Global")), Buffer))
	{
		FMemoryReader Reader(Buffer);
		Reader << Data;
		OnLoadCompleted.Broadcast(EDataCategory::Statistics, FName(TEXT("Global")));
	}
	else
	{
		OnLoadFailed.Broadcast(EDataCategory::Statistics, FName(TEXT("Global")));
	}
	return Data;
}

FProgressionData ULesFightSaveManager::LoadProgression()
{
	FProgressionData Data;
	TArray<uint8> Buffer;
	if (LoadDataFromFile(EDataCategory::Progression, FName(TEXT("Global")), Buffer))
	{
		FMemoryReader Reader(Buffer);
		Reader << Data;
		OnLoadCompleted.Broadcast(EDataCategory::Progression, FName(TEXT("Global")));
	}
	else
	{
		OnLoadFailed.Broadcast(EDataCategory::Progression, FName(TEXT("Global")));
	}
	return Data;
}

TArray<FMatchHistoryEntry> ULesFightSaveManager::LoadMatchHistory()
{
	TArray<FMatchHistoryEntry> Data;
	TArray<uint8> Buffer;
	if (LoadDataFromFile(EDataCategory::MatchHistory, FName(TEXT("Global")), Buffer))
	{
		FMemoryReader Reader(Buffer);
		Reader << Data;
		OnLoadCompleted.Broadcast(EDataCategory::MatchHistory, FName(TEXT("Global")));
	}
	else
	{
		OnLoadFailed.Broadcast(EDataCategory::MatchHistory, FName(TEXT("Global")));
	}
	return Data;
}
