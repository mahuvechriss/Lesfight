#include "Framework/Release/Platform/LesFightInstallerSystem.h"

void ULesFightInstallerSystem::Initialize()
{
	InstallPath = TEXT("C:/Program Files/LesFight/");
	RequiredDirectories.Empty();
	RequiredDirectories.Add(TEXT("Binaries"));
	RequiredDirectories.Add(TEXT("Content"));
	RequiredDirectories.Add(TEXT("Config"));
	RequiredDirectories.Add(TEXT("Plugins"));
	RequiredDirectories.Add(TEXT("Saved"));
	bInstalled = false;
}

void ULesFightInstallerSystem::Shutdown()
{
	RequiredDirectories.Empty();
}

void ULesFightInstallerSystem::SetInstallPath(const FString& Path)
{
	InstallPath = Path;
}

FString ULesFightInstallerSystem::GetInstallPath() const
{
	return InstallPath;
}

TArray<FString> ULesFightInstallerSystem::GenerateInstallSteps()
{
	TArray<FString> Steps;
	Steps.Add(TEXT("1. Welcome screen - Display EULA and system requirements"));
	Steps.Add(TEXT("2. Destination selection - Choose install directory"));
	Steps.Add(TEXT("3. Component selection - Choose optional components"));
	Steps.Add(TEXT("4. Installation - Copy files to destination"));
	Steps.Add(TEXT("5. Configuration - Set initial settings"));
	Steps.Add(TEXT("6. Shortcut creation - Desktop and Start Menu shortcuts"));
	Steps.Add(TEXT("7. Completion - Launch option and finish"));
	return Steps;
}

TArray<FString> ULesFightInstallerSystem::GenerateUninstallSteps()
{
	TArray<FString> Steps;
	Steps.Add(TEXT("1. Remove game files from install directory"));
	Steps.Add(TEXT("2. Remove saved data (optional)"));
	Steps.Add(TEXT("3. Remove shortcuts"));
	Steps.Add(TEXT("4. Remove registry entries"));
	Steps.Add(TEXT("5. Clean up temporary files"));
	return Steps;
}

bool ULesFightInstallerSystem::ValidateInstallation()
{
	return VerifyRequiredFiles();
}

bool ULesFightInstallerSystem::VerifyRequiredFiles()
{
	bool bAllFound = true;
	TArray<FString> RequiredFiles = {
		TEXT("LesFight.exe"),
		TEXT("Content/Paks/LesFight.pak"),
		TEXT("Config/DefaultEngine.ini"),
		TEXT("Config/DefaultGame.ini")
	};

	for (const FString& File : RequiredFiles)
	{
		FString FullPath = InstallPath / File;
		if (!FPaths::FileExists(FullPath))
		{
			UE_LOG(LogTemp, Warning, TEXT("[Installer] Missing required file: %s"), *FullPath);
			bAllFound = false;
		}
	}

	bInstalled = bAllFound;
	return bAllFound;
}

void ULesFightInstallerSystem::CreateShortcuts()
{
	UE_LOG(LogTemp, Log, TEXT("[Installer] Creating shortcuts for LesFight"));
	UE_LOG(LogTemp, Log, TEXT("  Desktop: %sLesFight.lnk"), *InstallPath);
	UE_LOG(LogTemp, Log, TEXT("  Start Menu: LesFight/LesFight.lnk"));
}

int64 ULesFightInstallerSystem::GetInstallSizeBytes() const
{
	return 15LL * 1024 * 1024 * 1024;
}

FString ULesFightInstallerSystem::GetInstallSummary() const
{
	return FString::Printf(TEXT("Installation at: %s - %s - %.1f GB"),
		*InstallPath,
		bInstalled ? TEXT("Installed") : TEXT("Not Installed"),
		GetInstallSizeBytes() / (1024.0 * 1024.0 * 1024.0));
}
