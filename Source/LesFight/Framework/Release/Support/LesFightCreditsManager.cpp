#include "Framework/Release/Support/LesFightCreditsManager.h"
#include "Misc/FileHelper.h"

void ULesFightCreditsManager::Initialize()
{
	DeveloperCredits.Empty();
	ThirdPartyCredits.Empty();
	LicenseInfo.Empty();
	SpecialThanks.Empty();

	DeveloperCredits.Add(TEXT("LesFight Development Team"));
	DeveloperCredits.Add(TEXT(""));
	DeveloperCredits.Add(TEXT("Lead Developer: LesFight Team"));
	DeveloperCredits.Add(TEXT("Gameplay Programmers: Core Development Team"));
	DeveloperCredits.Add(TEXT("AI Engineers: AI Systems Team"));
	DeveloperCredits.Add(TEXT("UI/UX Designers: UI Team"));
	DeveloperCredits.Add(TEXT("Audio Engineers: Audio Team"));
	DeveloperCredits.Add(TEXT("VFX Artists: Visual Effects Team"));
	DeveloperCredits.Add(TEXT("Animation Team: Animation Department"));
	DeveloperCredits.Add(TEXT("QA Testers: Quality Assurance Team"));
	DeveloperCredits.Add(TEXT("Producers: Production Team"));

	ThirdPartyCredits.Add(TEXT("Powered by Unreal Engine 5"));
	ThirdPartyCredits.Add(TEXT("Copyright Epic Games, Inc."));
	ThirdPartyCredits.Add(TEXT(""));
	ThirdPartyCredits.Add(TEXT("FMOD Studio - Audio Middleware"));
	ThirdPartyCredits.Add(TEXT("SpeedTree - Vegetation Rendering"));

	LicenseInfo.Add(TEXT("LesFight (c) 2026 LesFight Studios"));
	LicenseInfo.Add(TEXT("All rights reserved."));
	LicenseInfo.Add(TEXT(""));
	LicenseInfo.Add(TEXT("This software is provided 'as-is' without any"));
	LicenseInfo.Add(TEXT("express or implied warranty."));

	SpecialThanks.Add(TEXT("Beta Testers"));
	SpecialThanks.Add(TEXT("Community Support"));
	SpecialThanks.Add(TEXT("Fighting Game Community"));
}

TArray<FString> ULesFightCreditsManager::GetDeveloperCredits() const
{
	return DeveloperCredits;
}

TArray<FString> ULesFightCreditsManager::GetThirdPartyCredits() const
{
	return ThirdPartyCredits;
}

TArray<FString> ULesFightCreditsManager::GetLicenseInfo() const
{
	return LicenseInfo;
}

TArray<FString> ULesFightCreditsManager::GetSpecialThanks() const
{
	return SpecialThanks;
}

TArray<FString> ULesFightCreditsManager::GetFullCreditsText() const
{
	TArray<FString> Full;
	Full.Add(TEXT("=== CREDITS ==="));
	Full.Add(TEXT(""));
	Full.Add(TEXT("--- Development Team ---"));
	Full.Append(DeveloperCredits);
	Full.Add(TEXT(""));
	Full.Add(TEXT("--- Third-Party Assets ---"));
	Full.Append(ThirdPartyCredits);
	Full.Add(TEXT(""));
	Full.Add(TEXT("--- License ---"));
	Full.Append(LicenseInfo);
	Full.Add(TEXT(""));
	Full.Add(TEXT("--- Special Thanks ---"));
	Full.Append(SpecialThanks);
	return Full;
}

bool ULesFightCreditsManager::ExportCredits(const FString& FilePath)
{
	TArray<FString> Credits = GetFullCreditsText();
	FString Output;
	for (const FString& Line : Credits)
	{
		Output += Line + TEXT("\n");
	}
	return FFileHelper::SaveStringToFile(Output, *FilePath);
}
