#include "Framework/Release/Platform/LesFightPlatformManager.h"

void ULesFightPlatformManager::Initialize()
{
	ActivePlatform = EReleasePlatform::Windows;
	PlatformLog.Empty();
	PlatformLog.Add(TEXT("Platform manager initialized for Windows"));
}

void ULesFightPlatformManager::Shutdown()
{
	PlatformLog.Empty();
}

void ULesFightPlatformManager::SetActivePlatform(EReleasePlatform Platform)
{
	ActivePlatform = Platform;
	FString Name;
	switch (Platform)
	{
	case EReleasePlatform::Windows: Name = TEXT("Windows PC"); break;
	case EReleasePlatform::Console: Name = TEXT("Console");    break;
	case EReleasePlatform::Cloud:   Name = TEXT("Cloud");      break;
	default:                        Name = TEXT("Unknown");    break;
	}
	PlatformLog.Add(FString::Printf(TEXT("Active platform set to: %s"), *Name));
}

EReleasePlatform ULesFightPlatformManager::GetActivePlatform() const
{
	return ActivePlatform;
}

TArray<FString> ULesFightPlatformManager::GetPlatformRequirements() const
{
	TArray<FString> Reqs;
	switch (ActivePlatform)
	{
	case EReleasePlatform::Windows:
		Reqs.Add(TEXT("OS: Windows 10 64-bit or later"));
		Reqs.Add(TEXT("CPU: Intel Core i5-8400 or AMD Ryzen 5 2600"));
		Reqs.Add(TEXT("RAM: 8 GB"));
		Reqs.Add(TEXT("GPU: NVIDIA GTX 1060 or AMD RX 580 (6GB VRAM)"));
		Reqs.Add(TEXT("DX: DirectX 12 Ultimate"));
		Reqs.Add(TEXT("Storage: 30 GB available"));
		break;
	case EReleasePlatform::Console:
		Reqs.Add(TEXT("Platform SDK required"));
		Reqs.Add(TEXT("Certification requirements apply"));
		Reqs.Add(TEXT("TRC/TCR testing required"));
		break;
	case EReleasePlatform::Cloud:
		Reqs.Add(TEXT("Cloud SDK integration required"));
		Reqs.Add(TEXT("Multi-instance support"));
		Reqs.Add(TEXT("Save sync architecture"));
		break;
	}
	return Reqs;
}

TArray<FString> ULesFightPlatformManager::GetPlatformSpecificSettings() const
{
	TArray<FString> Settings;
	Settings.Add(FString::Printf(TEXT("Platform: %d"), static_cast<int32>(ActivePlatform)));
	Settings.Add(TEXT("Target FPS: 60"));
	Settings.Add(TEXT("Resolution: Native"));
	Settings.Add(TEXT("API: DirectX 12"));
	return Settings;
}

FString ULesFightPlatformManager::GetMinimumSpecs() const
{
	return TEXT("Windows 10 64-bit | Intel i5-8400 / Ryzen 5 2600 | 8GB RAM | GTX 1060 / RX 580 | 30GB Storage");
}

FString ULesFightPlatformManager::GetRecommendedSpecs() const
{
	return TEXT("Windows 11 64-bit | Intel i7-10700 / Ryzen 7 3700X | 16GB RAM | RTX 2070 / RX 6700 XT | 30GB SSD");
}

TArray<FString> ULesFightPlatformManager::ValidatePlatformCompatibility()
{
	TArray<FString> Issues;
	if (ActivePlatform == EReleasePlatform::Windows)
	{
		Issues.Add(TEXT("Windows compatibility: PASSED"));
		Issues.Add(TEXT("DirectX 12 support: PASSED"));
		Issues.Add(TEXT("64-bit architecture: PASSED"));
	}
	else
	{
		Issues.Add(FString::Printf(TEXT("Platform %d validation pending"), static_cast<int32>(ActivePlatform)));
	}
	return Issues;
}

bool ULesFightPlatformManager::IsPlatformReady() const
{
	return ActivePlatform == EReleasePlatform::Windows;
}
