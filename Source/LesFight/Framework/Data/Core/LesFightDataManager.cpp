#include "Framework/Data/Core/LesFightDataManager.h"
#include "Framework/Data/Core/LesFightSaveManager.h"
#include "Framework/Data/Core/LesFightBackupManager.h"
#include "Framework/Data/Core/LesFightDataSecurity.h"

void ULesFightDataManager::Initialize()
{
	if (bInitialized)
	{
		return;
	}

	SaveManager = CreateSubsystem<ULesFightSaveManager>(SaveManagerClass, this);
	BackupManager = CreateSubsystem<ULesFightBackupManager>(BackupManagerClass, this);
	DataSecurity = CreateSubsystem<ULesFightDataSecurity>(DataSecurityClass, this);
	ProfileManager = CreateSubsystem<UObject>(ProfileManagerClass, this);
	CharacterDataManager = CreateSubsystem<UObject>(CharacterDataManagerClass, this);
	ProgressionManager = CreateSubsystem<UObject>(ProgressionManagerClass, this);
	UnlockManager = CreateSubsystem<UObject>(UnlockManagerClass, this);
	AchievementManager = CreateSubsystem<UObject>(AchievementManagerClass, this);
	StatisticsManager = CreateSubsystem<UObject>(StatisticsManagerClass, this);
	MatchHistoryManager = CreateSubsystem<UObject>(MatchHistoryManagerClass, this);
	SettingsManager = CreateSubsystem<UObject>(SettingsManagerClass, this);
	DataDevTools = CreateSubsystem<UObject>(DataDevToolsClass, this);

	if (SaveManager)
	{
		SaveManager->Initialize();
	}
	if (BackupManager)
	{
		BackupManager->Initialize();
	}
	if (DataSecurity)
	{
		DataSecurity->Initialize();
	}

	bInitialized = true;
}

void ULesFightDataManager::Shutdown()
{
	if (!bInitialized)
	{
		return;
	}

	SaveAllData();

	if (DataSecurity)
	{
		DataSecurity->Shutdown();
	}
	if (BackupManager)
	{
		BackupManager->Shutdown();
	}
	if (SaveManager)
	{
		SaveManager->Shutdown();
	}

	bInitialized = false;
}

void ULesFightDataManager::Tick(float DeltaTime)
{
}

ESaveResult ULesFightDataManager::SaveAllData()
{
	if (!SaveManager)
	{
		return ESaveResult::Failed;
	}

	FPlayerProfileData Profile;
	TArray<FCharacterSaveData> Characters;
	FSettingsData Settings;

	return SaveManager->SaveAll(Profile, Characters, Settings);
}

ESaveResult ULesFightDataManager::LoadAllData(const FName& ProfileID)
{
	if (!SaveManager)
	{
		return ESaveResult::Failed;
	}

	FPlayerProfileData Profile = SaveManager->LoadProfile(ProfileID);
	if (Profile.ProfileID.IsNone())
	{
		OnDataLoaded.Broadcast(false);
		return ESaveResult::NotFound;
	}

	FSettingsData Settings = SaveManager->LoadSettings();
	FMatchStatisticsData Stats = SaveManager->LoadStatistics();
	FProgressionData Progression = SaveManager->LoadProgression();
	TArray<FMatchHistoryEntry> History = SaveManager->LoadMatchHistory();

	for (const FName& CharID : Profile.SavedCharacterIDs)
	{
		FCharacterSaveData Character = SaveManager->LoadCharacter(CharID);
		Characters.Add(Character);
	}

	OnDataLoaded.Broadcast(true);
	return ESaveResult::Success;
}

bool ULesFightDataManager::ResetAllData()
{
	if (!SaveManager)
	{
		return false;
	}

	FString SaveDir = SaveManager->GetSaveDirectory();
	return IFileManager::Get().DeleteDirectory(*SaveDir, true, true);
}
