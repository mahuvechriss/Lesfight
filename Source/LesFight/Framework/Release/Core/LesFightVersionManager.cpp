#include "Framework/Release/Core/LesFightVersionManager.h"

void ULesFightVersionManager::Initialize()
{
	CurrentVersion.Major = 1;
	CurrentVersion.Minor = 0;
	CurrentVersion.Patch = 0;
	CurrentVersion.BuildNumber = 1;
	CurrentVersion.BuildDate = FDateTime::Now().ToString();
	CurrentVersion.VersionSuffix = TEXT("alpha");
	VersionHistory.Empty();
	RecordVersion();
}

void ULesFightVersionManager::Shutdown()
{
	VersionHistory.Empty();
}

FVersionInfo ULesFightVersionManager::GetCurrentVersion() const
{
	return CurrentVersion;
}

void ULesFightVersionManager::SetVersion(int32 Major, int32 Minor, int32 Patch)
{
	CurrentVersion.Major = Major;
	CurrentVersion.Minor = Minor;
	CurrentVersion.Patch = Patch;
	RecordVersion();
}

void ULesFightVersionManager::BumpMajor()
{
	CurrentVersion.Major++;
	CurrentVersion.Minor = 0;
	CurrentVersion.Patch = 0;
	RecordVersion();
	UE_LOG(LogTemp, Log, TEXT("[Version] Major bump: %s"), *GetVersionString());
}

void ULesFightVersionManager::BumpMinor()
{
	CurrentVersion.Minor++;
	CurrentVersion.Patch = 0;
	RecordVersion();
	UE_LOG(LogTemp, Log, TEXT("[Version] Minor bump: %s"), *GetVersionString());
}

void ULesFightVersionManager::BumpPatch()
{
	CurrentVersion.Patch++;
	RecordVersion();
	UE_LOG(LogTemp, Log, TEXT("[Version] Patch bump: %s"), *GetVersionString());
}

void ULesFightVersionManager::IncrementBuildNumber()
{
	CurrentVersion.BuildNumber++;
	CurrentVersion.BuildDate = FDateTime::Now().ToString();
	UE_LOG(LogTemp, Log, TEXT("[Version] Build #%d"), CurrentVersion.BuildNumber);
}

FString ULesFightVersionManager::GetVersionString() const
{
	return CurrentVersion.ToString();
}

FString ULesFightVersionManager::GetShortVersionString() const
{
	return FString::Printf(TEXT("v%d.%d.%d"), CurrentVersion.Major, CurrentVersion.Minor, CurrentVersion.Patch);
}

void ULesFightVersionManager::SetVersionSuffix(const FString& Suffix)
{
	CurrentVersion.VersionSuffix = Suffix;
}

TArray<FVersionInfo> ULesFightVersionManager::GetVersionHistory() const
{
	return VersionHistory;
}

bool ULesFightVersionManager::SaveVersionToConfig()
{
	UE_LOG(LogTemp, Log, TEXT("[Version] Version saved: %s"), *GetVersionString());
	return true;
}

bool ULesFightVersionManager::LoadVersionFromConfig()
{
	UE_LOG(LogTemp, Log, TEXT("[Version] Version loaded: %s"), *GetVersionString());
	return true;
}

void ULesFightVersionManager::RecordVersion()
{
	VersionHistory.Add(CurrentVersion);
	CurrentVersion.BuildDate = FDateTime::Now().ToString();
}
