#include "Framework/Release/Support/LesFightLaunchManager.h"

void ULesFightLaunchManager::Initialize()
{
	LaunchChecklist.Empty();
	LaunchLog.Empty();
	GetFinalReleaseChecklist();
}

void ULesFightLaunchManager::Shutdown()
{
	LaunchChecklist.Empty();
	LaunchLog.Empty();
}

TArray<FString> ULesFightLaunchManager::GetFinalReleaseChecklist()
{
	LaunchChecklist.Empty();
	TArray<FString> Items;

	auto AddItem = [this](const FString& Name)
	{
		FReleaseChecklist Item;
		Item.Item = Name;
		Item.bCompleted = false;
		LaunchChecklist.Add(Item);
	};

	AddItem(TEXT("Game launches successfully"));
	AddItem(TEXT("Complete gameplay loop works"));
	AddItem(TEXT("Characters function correctly"));
	AddItem(TEXT("AI opponents work"));
	AddItem(TEXT("LAN multiplayer works"));
	AddItem(TEXT("AI photo character generation works"));
	AddItem(TEXT("Audio and VFX work correctly"));
	AddItem(TEXT("Save system works"));
	AddItem(TEXT("Performance targets achieved (60 FPS)"));
	AddItem(TEXT("No critical bugs remain"));
	AddItem(TEXT("Build packaging completed"));
	AddItem(TEXT("Installer created and tested"));
	AddItem(TEXT("Documentation complete"));
	AddItem(TEXT("Credits and legal reviewed"));
	AddItem(TEXT("Version number finalized"));

	for (const FReleaseChecklist& Item : LaunchChecklist)
	{
		Items.Add(FString::Printf(TEXT("[%s] %s"), Item.bCompleted ? TEXT("X") : TEXT(" "), *Item.Item));
	}

	return Items;
}

int32 ULesFightLaunchManager::GetChecklistCompletion() const
{
	int32 Completed = 0;
	for (const FReleaseChecklist& Item : LaunchChecklist)
	{
		if (Item.bCompleted) Completed++;
	}
	return LaunchChecklist.Num() > 0 ? (Completed * 100 / LaunchChecklist.Num()) : 0;
}

bool ULesFightLaunchManager::IsReadyForLaunch() const
{
	for (const FReleaseChecklist& Item : LaunchChecklist)
	{
		if (!Item.bCompleted)
		{
			return false;
		}
	}
	return true;
}

TArray<FString> ULesFightLaunchManager::GetMarketingInfo() const
{
	TArray<FString> Info;
	Info.Add(TEXT("Title: LesFight"));
	Info.Add(TEXT("Genre: Fighting / Martial Arts"));
	Info.Add(TEXT("Platform: Windows PC"));
	Info.Add(TEXT("Engine: Unreal Engine 5"));
	Info.Add(TEXT("Players: 1-2 (LAN Multiplayer)"));
	Info.Add(TEXT("Price: Free"));
	Info.Add(TEXT("Key Features: AI Photo-to-Character, Dynamic Combat, Multiple Fighting Styles"));
	return Info;
}

TArray<FString> ULesFightLaunchManager::GetPressBuildInfo() const
{
	TArray<FString> Info;
	Info.Add(TEXT("Press Build v1.0"));
	Info.Add(TEXT("Includes: Full game + all modes"));
	Info.Add(TEXT("Screenshots: /Screenshots/"));
	Info.Add(TEXT("Trailer: /Trailer/"));
	Info.Add(TEXT("Contact: press@lesfight.com"));
	return Info;
}

void ULesFightLaunchManager::GenerateScreenshotList()
{
	LaunchLog.Add(TEXT("Screenshots to capture:"));
	LaunchLog.Add(TEXT("  1. Main Menu"));
	LaunchLog.Add(TEXT("  2. Character Select Screen"));
	LaunchLog.Add(TEXT("  3. Character Creator"));
	LaunchLog.Add(TEXT("  4. In-game Combat (two characters)"));
	LaunchLog.Add(TEXT("  5. Special Move Action Shot"));
	LaunchLog.Add(TEXT("  6. Ultimate Move Cinematic"));
	LaunchLog.Add(TEXT("  7. Arena Environment"));
	LaunchLog.Add(TEXT("  8. Victory Screen"));
	LaunchLog.Add(TEXT("  9. Multiplayer Lobby"));
	LaunchLog.Add(TEXT("  10. Settings Menu"));
}

void ULesFightLaunchManager::PreparePressBuild()
{
	LaunchLog.Add(TEXT("Preparing press build..."));
	LaunchLog.Add(TEXT("  Build type: Shipping"));
	LaunchLog.Add(TEXT("  Features: All game modes unlocked"));
	LaunchLog.Add(TEXT("  Debug: Disabled"));
	LaunchLog.Add(TEXT("Press build ready"));
}

void ULesFightLaunchManager::PrepareReviewBuild()
{
	LaunchLog.Add(TEXT("Preparing review build..."));
	LaunchLog.Add(TEXT("  Build type: QA"));
	LaunchLog.Add(TEXT("  Features: Full game"));
	LaunchLog.Add(TEXT("  Review notes included"));
	LaunchLog.Add(TEXT("Review build ready"));
}

TArray<FString> ULesFightLaunchManager::GetLaunchLog() const
{
	return LaunchLog;
}
