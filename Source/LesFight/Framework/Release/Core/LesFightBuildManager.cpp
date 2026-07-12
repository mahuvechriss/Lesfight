#include "Framework/Release/Core/LesFightBuildManager.h"

void ULesFightBuildManager::Initialize()
{
	BuildLog.Empty();
	bBuildInProgress = false;
	ActiveConfig.BuildType = EBuildType::Development;
	ActiveConfig.TargetPlatform = EReleasePlatform::Windows;
	ActiveConfig.bEnableDebugSymbols = true;
	ActiveConfig.bEnableOptimization = false;
	ActiveConfig.bCookContent = false;
	ActiveConfig.bCompressPackages = false;
	ActiveConfig.BuildNumber = 0;
}

void ULesFightBuildManager::Shutdown()
{
	BuildLog.Empty();
	bBuildInProgress = false;
}

FBuildConfiguration ULesFightBuildManager::GetActiveConfiguration() const
{
	return ActiveConfig;
}

void ULesFightBuildManager::SetBuildType(EBuildType Type)
{
	ActiveConfig.BuildType = Type;
	BuildLog.Add(FString::Printf(TEXT("Build type set to: %d"), static_cast<int32>(Type)));
}

void ULesFightBuildManager::SetTargetPlatform(EReleasePlatform Platform)
{
	ActiveConfig.TargetPlatform = Platform;
	BuildLog.Add(FString::Printf(TEXT("Target platform set to: %d"), static_cast<int32>(Platform)));
}

void ULesFightBuildManager::ConfigureDevelopmentBuild()
{
	ActiveConfig.BuildType = EBuildType::Development;
	ActiveConfig.bEnableDebugSymbols = true;
	ActiveConfig.bEnableOptimization = false;
	ActiveConfig.bCookContent = false;
	ActiveConfig.bCompressPackages = false;
	BuildLog.Add(TEXT("Configured: Development build"));
}

void ULesFightBuildManager::ConfigureQABuild()
{
	ActiveConfig.BuildType = EBuildType::QA;
	ActiveConfig.bEnableDebugSymbols = true;
	ActiveConfig.bEnableOptimization = true;
	ActiveConfig.bCookContent = true;
	ActiveConfig.bCompressPackages = false;
	BuildLog.Add(TEXT("Configured: QA build"));
}

void ULesFightBuildManager::ConfigureReleaseBuild()
{
	ActiveConfig.BuildType = EBuildType::Release;
	ActiveConfig.bEnableDebugSymbols = false;
	ActiveConfig.bEnableOptimization = true;
	ActiveConfig.bCookContent = true;
	ActiveConfig.bCompressPackages = true;
	BuildLog.Add(TEXT("Configured: Release build"));
}

void ULesFightBuildManager::ConfigureShippingBuild()
{
	ActiveConfig.BuildType = EBuildType::Shipping;
	ActiveConfig.bEnableDebugSymbols = false;
	ActiveConfig.bEnableOptimization = true;
	ActiveConfig.bCookContent = true;
	ActiveConfig.bCompressPackages = true;
	BuildLog.Add(TEXT("Configured: Shipping build (final)"));
}

TArray<FString> ULesFightBuildManager::GenerateBuildCommands()
{
	TArray<FString> Commands;
	FString PlatformArg;
	switch (ActiveConfig.TargetPlatform)
	{
	case EReleasePlatform::Windows: PlatformArg = TEXT("Win64"); break;
	case EReleasePlatform::Console: PlatformArg = TEXT("Console"); break;
	case EReleasePlatform::Cloud:   PlatformArg = TEXT("Cloud"); break;
	default:                        PlatformArg = TEXT("Win64"); break;
	}

	FString ConfigArg;
	switch (ActiveConfig.BuildType)
	{
	case EBuildType::Development: ConfigArg = TEXT("Development"); break;
	case EBuildType::QA:           ConfigArg = TEXT("DebugGame");  break;
	case EBuildType::Release:      ConfigArg = TEXT("Shipping");   break;
	case EBuildType::Shipping:     ConfigArg = TEXT("Shipping");   break;
	default:                       ConfigArg = TEXT("Development"); break;
	}

	Commands.Add(FString::Printf(TEXT("BuildTarget: LesFight_%s"), *ConfigArg));
	Commands.Add(FString::Printf(TEXT("Platform: %s"), *PlatformArg));
	Commands.Add(FString::Printf(TEXT("Cook: %s"), ActiveConfig.bCookContent ? TEXT("Yes") : TEXT("No")));
	Commands.Add(FString::Printf(TEXT("Compress: %s"), ActiveConfig.bCompressPackages ? TEXT("Yes") : TEXT("No")));
	Commands.Add(FString::Printf(TEXT("Debug Symbols: %s"), ActiveConfig.bEnableDebugSymbols ? TEXT("Yes") : TEXT("No")));

	return Commands;
}

bool ULesFightBuildManager::ValidateConfiguration()
{
	if (ActiveConfig.BuildDirectory.IsEmpty() || ActiveConfig.OutputDirectory.IsEmpty())
	{
		BuildLog.Add(TEXT("Validation ERROR: Build or Output directory not set"));
		return false;
	}

	if (ActiveConfig.BuildType == EBuildType::Shipping && ActiveConfig.bEnableDebugSymbols)
	{
		BuildLog.Add(TEXT("Validation WARNING: Shipping build with debug symbols enabled"));
	}

	BuildLog.Add(TEXT("Configuration validated successfully"));
	return true;
}

TArray<FString> ULesFightBuildManager::GetBuildLog() const
{
	return BuildLog;
}

FString ULesFightBuildManager::GetBuildStatus() const
{
	FString TypeStr;
	switch (ActiveConfig.BuildType)
	{
	case EBuildType::Development: TypeStr = TEXT("Development"); break;
	case EBuildType::QA:           TypeStr = TEXT("QA");         break;
	case EBuildType::Release:      TypeStr = TEXT("Release");    break;
	case EBuildType::Shipping:     TypeStr = TEXT("Shipping");   break;
	}

	return FString::Printf(TEXT("Build #%d [%s] - %s"),
		ActiveConfig.BuildNumber, *TypeStr,
		bBuildInProgress ? TEXT("In Progress") : TEXT("Idle"));
}
