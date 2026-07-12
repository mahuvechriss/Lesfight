#include "Framework/Release/Updates/LesFightUpdateManager.h"

void ULesFightUpdateManager::Initialize()
{
	UpdateNotes.Empty();
	UpdateHistory.Empty();
	bUpdateAvailable = false;
	bUpdateDownloaded = false;
	LatestVersion.Major = 1;
	LatestVersion.Minor = 0;
	LatestVersion.Patch = 0;
}

void ULesFightUpdateManager::Shutdown()
{
	UpdateNotes.Empty();
	UpdateHistory.Empty();
}

bool ULesFightUpdateManager::CheckForUpdate()
{
	bUpdateAvailable = false;
	UE_LOG(LogTemp, Log, TEXT("[Update] Checking for updates..."));
	bUpdateAvailable = false;
	return bUpdateAvailable;
}

FVersionInfo ULesFightUpdateManager::GetLatestAvailableVersion() const
{
	return LatestVersion;
}

TArray<FString> ULesFightUpdateManager::GetUpdateNotes() const
{
	return UpdateNotes;
}

int64 ULesFightUpdateManager::GetUpdateSizeBytes() const
{
	return 0;
}

bool ULesFightUpdateManager::DownloadUpdate()
{
	if (!bUpdateAvailable) return false;
	bUpdateDownloaded = false;
	UE_LOG(LogTemp, Log, TEXT("[Update] Downloading update..."));
	bUpdateDownloaded = true;
	return true;
}

bool ULesFightUpdateManager::ApplyUpdate()
{
	if (!bUpdateDownloaded) return false;
	UE_LOG(LogTemp, Log, TEXT("[Update] Applying update..."));
	UpdateHistory.Add(LatestVersion);
	bUpdateAvailable = false;
	bUpdateDownloaded = false;
	return true;
}

bool ULesFightUpdateManager::VerifyUpdateIntegrity()
{
	return bUpdateDownloaded;
}

void ULesFightUpdateManager::RollbackUpdate()
{
	if (UpdateHistory.Num() > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("[Update] Rolling back to previous version"));
		UpdateHistory.Pop();
	}
}

TArray<FVersionInfo> ULesFightUpdateManager::GetUpdateHistory() const
{
	return UpdateHistory;
}

FString ULesFightUpdateManager::GetUpdateStatus() const
{
	if (bUpdateAvailable)
	{
		return FString::Printf(TEXT("Update available: v%d.%d.%d"), LatestVersion.Major, LatestVersion.Minor, LatestVersion.Patch);
	}
	return TEXT("Game is up to date");
}
