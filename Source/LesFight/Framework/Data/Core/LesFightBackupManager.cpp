#include "Framework/Data/Core/LesFightBackupManager.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/BufferReader.h"

void ULesFightBackupManager::Initialize()
{
	LoadBackupMetadata();
}

void ULesFightBackupManager::Shutdown()
{
	SaveBackupMetadata();
	Backups.Empty();
}

FString ULesFightBackupManager::GetBackupDirectory() const
{
	ULesFightSaveManager* SaveMgr = Cast<ULesFightSaveManager>(GetOuter());
	FString BasePath;
	if (SaveMgr)
	{
		BasePath = SaveMgr->GetSaveDirectory();
	}
	else
	{
		BasePath = FPaths::ProjectSavedDir() / TEXT("SaveData") / TEXT("Slot0") / TEXT("");
	}
	return BasePath / TEXT("Backups") / TEXT("");
}

FString ULesFightBackupManager::GetBackupFilePath(int32 BackupIndex, EDataCategory Category, const FName& Identifier) const
{
	const UEnum* EnumPtr = StaticEnum<EDataCategory>();
	FString CategoryName = EnumPtr ? EnumPtr->GetNameStringByValue((int64)Category) : TEXT("Unknown");
	return GetBackupDirectory() / FString::Printf(TEXT("Backup_%d_%s_%s.bak"), BackupIndex, *CategoryName, *Identifier.ToString());
}

FString ULesFightBackupManager::GetBackupMetaFilePath() const
{
	return GetBackupDirectory() / TEXT("BackupMetadata.json");
}

int32 ULesFightBackupManager::GetNextBackupIndex()
{
	int32 Highest = -1;
	for (const FBackupEntry& Entry : Backups)
	{
		if (Entry.BackupIndex > Highest)
		{
			Highest = Entry.BackupIndex;
		}
	}
	return Highest + 1;
}

void ULesFightBackupManager::EnforceMaxBackups()
{
	while (Backups.Num() > MaxBackups)
	{
		FBackupEntry Oldest = Backups[0];
		int32 OldestIdx = 0;
		for (int32 i = 1; i < Backups.Num(); ++i)
		{
			if (Backups[i].Timestamp < Oldest.Timestamp)
			{
				Oldest = Backups[i];
				OldestIdx = i;
			}
		}
		FString FilePath = GetBackupFilePath(Oldest.BackupIndex, Oldest.Category, Oldest.Identifier);
		IFileManager::Get().Delete(*FilePath, true, false);
		Backups.RemoveAt(OldestIdx);
	}
}

void ULesFightBackupManager::SaveBackupMetadata()
{
	FString BackupDir = GetBackupDirectory();
	if (!IFileManager::Get().DirectoryExists(*BackupDir))
	{
		IFileManager::Get().MakeDirectory(*BackupDir, true);
	}

	FBufferArchive Archive;
	int32 NumBackups = Backups.Num();
	Archive << NumBackups;
	for (const FBackupEntry& Entry : Backups)
	{
		Archive << Entry.BackupIndex;
		Archive << Entry.Timestamp;
		uint8 Cat = (uint8)Entry.Category;
		Archive << Cat;
		Archive << const_cast<FName&>(Entry.Identifier);
		Archive << Entry.FileSize;
		Archive << const_cast<FString&>(Entry.Checksum);
	}

	FFileHelper::SaveArrayToFile(Archive, *GetBackupMetaFilePath());
}

void ULesFightBackupManager::LoadBackupMetadata()
{
	Backups.Empty();
	FString MetaPath = GetBackupMetaFilePath();
	if (!IFileManager::Get().FileExists(*MetaPath))
	{
		return;
	}

	TArray<uint8> Buffer;
	if (!FFileHelper::LoadFileToArray(Buffer, *MetaPath))
	{
		return;
	}

	FMemoryReader Reader(Buffer);
	int32 NumBackups = 0;
	Reader << NumBackups;

	for (int32 i = 0; i < NumBackups && i < MaxBackupEntries && !Reader.IsError(); ++i)
	{
		FBackupEntry Entry;
		Reader << Entry.BackupIndex;
		Reader << Entry.Timestamp;
		uint8 Cat = 0;
		Reader << Cat;
		Entry.Category = (EDataCategory)Cat;
		Reader << Entry.Identifier;
		Reader << Entry.FileSize;
		Reader << Entry.Checksum;
		Backups.Add(Entry);
	}
}

ESaveResult ULesFightBackupManager::CreateBackup(EDataCategory Category, FName Identifier)
{
	ULesFightSaveManager* SaveMgr = Cast<ULesFightSaveManager>(GetOuter());
	if (!SaveMgr)
	{
		return ESaveResult::Failed;
	}

	FString SourcePath;
	{
		const UEnum* EnumPtr = StaticEnum<EDataCategory>();
		FString CategoryName = EnumPtr ? EnumPtr->GetNameStringByValue((int64)Category) : TEXT("Unknown");
		SourcePath = SaveMgr->GetSaveDirectory() / CategoryName + TEXT("_") + Identifier.ToString() + TEXT(".sav");
	}

	if (!IFileManager::Get().FileExists(*SourcePath))
	{
		return ESaveResult::NotFound;
	}

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *SourcePath))
	{
		return ESaveResult::Failed;
	}

	int32 BackupIndex = GetNextBackupIndex();
	FString BackupPath = GetBackupFilePath(BackupIndex, Category, Identifier);

	FString BackupDir = GetBackupDirectory();
	if (!IFileManager::Get().DirectoryExists(*BackupDir))
	{
		IFileManager::Get().MakeDirectory(*BackupDir, true);
	}

	if (!FFileHelper::SaveArrayToFile(FileData, *BackupPath))
	{
		return ESaveResult::Failed;
	}

	FBackupEntry NewEntry;
	NewEntry.BackupIndex = BackupIndex;
	NewEntry.Timestamp = FDateTime::Now();
	NewEntry.Category = Category;
	NewEntry.Identifier = Identifier;
	NewEntry.FileSize = FileData.Num();
	NewEntry.Checksum = FString::Printf(TEXT("%08X"), FCrc::MemCrc32(FileData.GetData(), FileData.Num()));

	Backups.Add(NewEntry);
	EnforceMaxBackups();
	SaveBackupMetadata();

	OnBackupCreated.Broadcast(BackupIndex);
	return ESaveResult::Success;
}

ESaveResult ULesFightBackupManager::CreateFullBackup()
{
	ULesFightSaveManager* SaveMgr = Cast<ULesFightSaveManager>(GetOuter());
	if (!SaveMgr)
	{
		return ESaveResult::Failed;
	}

	TArray<EDataCategory> Categories = {
		EDataCategory::Profile,
		EDataCategory::Character,
		EDataCategory::Settings,
		EDataCategory::Statistics,
		EDataCategory::Progression,
		EDataCategory::MatchHistory,
		EDataCategory::Achievement
	};

	bool bAllSucceeded = true;
	for (EDataCategory Cat : Categories)
	{
		const UEnum* EnumPtr = StaticEnum<EDataCategory>();
		FString CategoryName = EnumPtr ? EnumPtr->GetNameStringByValue((int64)Cat) : TEXT("Unknown");
		FString SearchPattern = SaveMgr->GetSaveDirectory() / CategoryName + TEXT("_*.sav");

		TArray<FString> FoundFiles;
		IFileManager::Get().FindFiles(FoundFiles, *SearchPattern, true, false);

		for (const FString& FileName : FoundFiles)
		{
			FString Stripped = FileName.Replace(TEXT(".sav"), TEXT(""));
			FString IdentifierPart = Stripped.RightChop(CategoryName.Len() + 1);

			ESaveResult Result = CreateBackup(Cat, FName(*IdentifierPart));
			if (Result != ESaveResult::Success)
			{
				bAllSucceeded = false;
			}
		}
	}

	return bAllSucceeded ? ESaveResult::Success : ESaveResult::Failed;
}

ESaveResult ULesFightBackupManager::RestoreFromBackup(EDataCategory Category, FName Identifier, int32 BackupIndex)
{
	ULesFightSaveManager* SaveMgr = Cast<ULesFightSaveManager>(GetOuter());
	if (!SaveMgr)
	{
		return ESaveResult::Failed;
	}

	FString BackupPath = GetBackupFilePath(BackupIndex, Category, Identifier);
	if (!IFileManager::Get().FileExists(*BackupPath))
	{
		return ESaveResult::NotFound;
	}

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *BackupPath))
	{
		return ESaveResult::Failed;
	}

	const UEnum* EnumPtr = StaticEnum<EDataCategory>();
	FString CategoryName = EnumPtr ? EnumPtr->GetNameStringByValue((int64)Category) : TEXT("Unknown");
	FString DestPath = SaveMgr->GetSaveDirectory() / CategoryName + TEXT("_") + Identifier.ToString() + TEXT(".sav");

	if (!FFileHelper::SaveArrayToFile(FileData, *DestPath))
	{
		return ESaveResult::Failed;
	}

	OnBackupRestored.Broadcast(BackupIndex);
	return ESaveResult::Success;
}

ESaveResult ULesFightBackupManager::RestoreFullBackup(int32 BackupIndex)
{
	TArray<FBackupEntry> MatchingBackups;
	for (const FBackupEntry& Entry : Backups)
	{
		if (Entry.BackupIndex == BackupIndex)
		{
			MatchingBackups.Add(Entry);
		}
	}

	if (MatchingBackups.Num() == 0)
	{
		return ESaveResult::NotFound;
	}

	bool bAllSucceeded = true;
	for (const FBackupEntry& Entry : MatchingBackups)
	{
		ESaveResult Result = RestoreFromBackup(Entry.Category, Entry.Identifier, Entry.BackupIndex);
		if (Result != ESaveResult::Success)
		{
			bAllSucceeded = false;
		}
	}

	return bAllSucceeded ? ESaveResult::Success : ESaveResult::Failed;
}

TArray<FBackupEntry> ULesFightBackupManager::ListBackups(EDataCategory Category) const
{
	TArray<FBackupEntry> Filtered;
	for (const FBackupEntry& Entry : Backups)
	{
		if (Entry.Category == Category)
		{
			Filtered.Add(Entry);
		}
	}
	return Filtered;
}

bool ULesFightBackupManager::DeleteBackup(int32 BackupIndex)
{
	bool bRemovedAny = false;
	for (int32 i = Backups.Num() - 1; i >= 0; --i)
	{
		if (Backups[i].BackupIndex == BackupIndex)
		{
			FString FilePath = GetBackupFilePath(Backups[i].BackupIndex, Backups[i].Category, Backups[i].Identifier);
			IFileManager::Get().Delete(*FilePath, true, false);
			Backups.RemoveAt(i);
			bRemovedAny = true;
		}
	}

	if (bRemovedAny)
	{
		SaveBackupMetadata();
	}

	return bRemovedAny;
}

int32 ULesFightBackupManager::GetLatestBackup(EDataCategory Category, FName Identifier) const
{
	int32 LatestIndex = -1;
	FDateTime LatestTime = FDateTime::MinValue();

	for (const FBackupEntry& Entry : Backups)
	{
		if (Entry.Category == Category && Entry.Identifier == Identifier)
		{
			if (Entry.Timestamp > LatestTime)
			{
				LatestTime = Entry.Timestamp;
				LatestIndex = Entry.BackupIndex;
			}
		}
	}

	return LatestIndex;
}

bool ULesFightBackupManager::DetectCorruption(FName Identifier) const
{
	ULesFightSaveManager* SaveMgr = Cast<ULesFightSaveManager>(GetOuter());
	if (!SaveMgr)
	{
		return true;
	}

	EDataCategory Categories[] = {
		EDataCategory::Profile,
		EDataCategory::Settings,
		EDataCategory::Statistics,
		EDataCategory::Progression,
		EDataCategory::MatchHistory
	};

	for (EDataCategory Cat : Categories)
	{
		TArray<uint8> FileData;
		const UEnum* EnumPtr = StaticEnum<EDataCategory>();
		FString CategoryName = EnumPtr ? EnumPtr->GetNameStringByValue((int64)Cat) : TEXT("Unknown");
		FString FilePath = SaveMgr->GetSaveDirectory() / CategoryName + TEXT("_") + Identifier.ToString() + TEXT(".sav");

		if (IFileManager::Get().FileExists(*FilePath))
		{
			if (!FFileHelper::LoadFileToArray(FileData, *FilePath))
			{
				return true;
			}

			if (FileData.Num() == 0)
			{
				return true;
			}
		}
	}

	return false;
}

ESaveResult ULesFightBackupManager::AttemptRecovery(FName Identifier)
{
	if (!DetectCorruption(Identifier))
	{
		return ESaveResult::Success;
	}

	EDataCategory Categories[] = {
		EDataCategory::Profile,
		EDataCategory::Settings,
		EDataCategory::Statistics,
		EDataCategory::Progression,
		EDataCategory::MatchHistory
	};

	bool bAnyRestored = false;
	for (EDataCategory Cat : Categories)
	{
		int32 LatestIdx = GetLatestBackup(Cat, Identifier);
		if (LatestIdx >= 0)
		{
			ESaveResult Result = RestoreFromBackup(Cat, Identifier, LatestIdx);
			if (Result == ESaveResult::Success)
			{
				bAnyRestored = true;
			}
		}
	}

	return bAnyRestored ? ESaveResult::Success : ESaveResult::NotFound;
}
