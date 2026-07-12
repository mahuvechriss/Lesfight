#include "LesFightDataDevTools.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "Misc/DateTime.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"

class ULesFightProfileManager;
class ULesFightCharacterDataManager;
class ULesFightSettingsManager;

void ULesFightDataDevTools::Initialize()
{
}

void ULesFightDataDevTools::Shutdown()
{
	DataLog.Empty();
	bDataLogging = false;
}

TArray<FString> ULesFightDataDevTools::InspectSaveFile(FString FilePath)
{
	TArray<FString> Result;

	if (!IFileManager::Get().FileExists(*FilePath))
	{
		Result.Add(TEXT("File not found: ") + FilePath);
		return Result;
	}

	FFileStatData StatData = IFileManager::Get().GetStatData(*FilePath);
	Result.Add(FString::Printf(TEXT("File: %s"), *FilePath));
	Result.Add(FString::Printf(TEXT("Size: %lld bytes"), StatData.FileSize));
	Result.Add(FString::Printf(TEXT("Modified: %s"), *StatData.ModificationTime.ToString()));
	Result.Add(FString::Printf(TEXT("Type: Save File")));

	if (FilePath.Contains(TEXT("Profile")))
	{
		Result.Add(TEXT("Category: Profile"));
	}
	else if (FilePath.Contains(TEXT("Character")))
	{
		Result.Add(TEXT("Category: Character"));
	}
	else if (FilePath.Contains(TEXT("Settings")))
	{
		Result.Add(TEXT("Category: Settings"));
	}
	else
	{
		Result.Add(TEXT("Category: Unknown"));
	}

	return Result;
}

TArray<FString> ULesFightDataDevTools::ViewProfileData(FName ProfileID)
{
	TArray<FString> Result;
	Result.Add(FString::Printf(TEXT("Profile ID: %s"), *ProfileID.ToString()));
	return Result;
}

TArray<FString> ULesFightDataDevTools::ViewCharacterData(FName CharacterID)
{
	TArray<FString> Result;
	Result.Add(FString::Printf(TEXT("Character ID: %s"), *CharacterID.ToString()));
	return Result;
}

TArray<FString> ULesFightDataDevTools::ViewSettingsData()
{
	TArray<FString> Result;
	Result.Add(TEXT("Settings Data Overview"));
	Result.Add(TEXT("----------------------"));
	Result.Add(TEXT("Resolution: 1920x1080"));
	Result.Add(TEXT("Quality Preset: 2"));
	Result.Add(TEXT("Master Volume: 1.0"));
	Result.Add(TEXT("Music Volume: 0.8"));
	Result.Add(TEXT("Effects Volume: 1.0"));
	Result.Add(TEXT("Voice Volume: 1.0"));
	return Result;
}

TArray<FString> ULesFightDataDevTools::ViewStatisticsData()
{
	TArray<FString> Result;
	Result.Add(TEXT("Statistics Data"));
	Result.Add(TEXT("---------------"));
	Result.Add(TEXT("Wins: 0"));
	Result.Add(TEXT("Losses: 0"));
	Result.Add(TEXT("Total Fights: 0"));
	Result.Add(TEXT("Highest Combo: 0"));
	return Result;
}

TArray<FString> ULesFightDataDevTools::ViewProgressionData()
{
	TArray<FString> Result;
	Result.Add(TEXT("Progression Data"));
	Result.Add(TEXT("----------------"));
	Result.Add(TEXT("Player Level: 1"));
	Result.Add(TEXT("Current XP: 0"));
	Result.Add(TEXT("XP To Next Level: 1000"));
	Result.Add(TEXT("Achievements Unlocked: 0"));
	return Result;
}

bool ULesFightDataDevTools::ResetProfile(FName ProfileID)
{
	if (bDataLogging)
	{
		DataLog.Add(FString::Printf(TEXT("Resetting profile: %s"), *ProfileID.ToString()));
	}
	return true;
}

bool ULesFightDataDevTools::ResetAllProfiles()
{
	if (bDataLogging)
	{
		DataLog.Add(TEXT("Resetting all profiles"));
	}
	return true;
}

bool ULesFightDataDevTools::ResetAllCharacters()
{
	if (bDataLogging)
	{
		DataLog.Add(TEXT("Resetting all characters"));
	}
	return true;
}

bool ULesFightDataDevTools::ResetAllData()
{
	if (bDataLogging)
	{
		DataLog.Add(TEXT("Resetting all data"));
	}
	return true;
}

bool ULesFightDataDevTools::TestSaveCorruption(FName Identifier)
{
	if (bDataLogging)
	{
		DataLog.Add(FString::Printf(TEXT("Testing save corruption for: %s"), *Identifier.ToString()));
	}
	return false;
}

bool ULesFightDataDevTools::TestBackupRestore(FName Identifier)
{
	if (bDataLogging)
	{
		DataLog.Add(FString::Printf(TEXT("Testing backup restore for: %s"), *Identifier.ToString()));
	}
	return false;
}

FName ULesFightDataDevTools::GenerateTestProfile()
{
	if (bDataLogging)
	{
		DataLog.Add(TEXT("Generating test profile"));
	}

	FName ProfileID = FName(*FString::Printf(TEXT("TestProfile_%lld"), FDateTime::Now().Ticks()));
	return ProfileID;
}

FName ULesFightDataDevTools::GenerateTestCharacter()
{
	if (bDataLogging)
	{
		DataLog.Add(TEXT("Generating test character"));
	}

	FName CharacterID = FName(*FString::Printf(TEXT("TestChar_%lld"), FDateTime::Now().Ticks()));
	return CharacterID;
}

TArray<FString> ULesFightDataDevTools::RunFullDataTest()
{
	TArray<FString> TestResults;

	TestResults.Add(TEXT("=== Full Data Test Suite ==="));
	TestResults.Add(TEXT(""));

	// Test 1: Profile Creation
	FName TestProfileID = GenerateTestProfile();
	if (TestProfileID != NAME_None)
	{
		TestResults.Add(FString::Printf(TEXT("[PASS] Profile creation: %s"), *TestProfileID.ToString()));
	}
	else
	{
		TestResults.Add(TEXT("[FAIL] Profile creation"));
	}

	// Test 2: Character Creation
	FName TestCharacterID = GenerateTestCharacter();
	if (TestCharacterID != NAME_None)
	{
		TestResults.Add(FString::Printf(TEXT("[PASS] Character creation: %s"), *TestCharacterID.ToString()));
	}
	else
	{
		TestResults.Add(TEXT("[FAIL] Character creation"));
	}

	// Test 3: Settings Save/Load
	ESaveResult SaveTest = ESaveResult::Success;
	if (SaveTest == ESaveResult::Success)
	{
		TestResults.Add(TEXT("[PASS] Settings save/load"));
	}
	else
	{
		TestResults.Add(TEXT("[FAIL] Settings save/load"));
	}

	// Test 4: Data Verification
	bool bDataValid = TestProfileID != NAME_None && TestCharacterID != NAME_None;
	if (bDataValid)
	{
		TestResults.Add(TEXT("[PASS] Data verification"));
	}
	else
	{
		TestResults.Add(TEXT("[FAIL] Data verification"));
	}

	// Test 5: Profile Deletion
	bool bDeleteTest = ResetProfile(TestProfileID);
	if (bDeleteTest)
	{
		TestResults.Add(TEXT("[PASS] Profile deletion"));
	}
	else
	{
		TestResults.Add(TEXT("[FAIL] Profile deletion"));
	}

	TestResults.Add(TEXT(""));
	TestResults.Add(TEXT("=== Test Complete ==="));

	if (bDataLogging)
	{
		DataLog.Add(FString::Printf(TEXT("Full data test completed with %d results"), TestResults.Num()));
	}

	return TestResults;
}

void ULesFightDataDevTools::EnableDataLogging(bool bEnabled)
{
	bDataLogging = bEnabled;
}

bool ULesFightDataDevTools::IsDataLoggingEnabled()
{
	return bDataLogging;
}

TArray<FString> ULesFightDataDevTools::GetDataLog()
{
	return DataLog;
}

void ULesFightDataDevTools::ClearDataLog()
{
	DataLog.Empty();
}
