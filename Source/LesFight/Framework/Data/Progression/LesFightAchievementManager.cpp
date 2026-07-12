#include "Framework/Data/Progression/LesFightAchievementManager.h"

void ULesFightAchievementManager::Initialize()
{
	AchievementRegistry.Empty();
	UnlockedAchievements.Empty();
	AchievementProgress.Empty();

	auto Register = [&](EAchievementId ID, FText Title, FText Description, bool bHidden = false)
	{
		RegisterAchievement(ID, Title, Description, bHidden);
	};

	Register(EAchievementId::FirstFight, FText::FromString("First Bout"), FText::FromString("Complete your first fight"), false);
	Register(EAchievementId::FirstWin, FText::FromString("First Victory"), FText::FromString("Win your first match"), false);
	Register(EAchievementId::WinStreak5, FText::FromString("5 Win Streak"), FText::FromString("Win 5 matches in a row"), false);
	Register(EAchievementId::WinStreak10, FText::FromString("10 Win Streak"), FText::FromString("Win 10 matches in a row"), true);
	Register(EAchievementId::ComboMaster, FText::FromString("Combo Master"), FText::FromString("Land a 20+ hit combo"), false);
	Register(EAchievementId::UltimateFinisher, FText::FromString("Ultimate Finisher"), FText::FromString("Finish a match with an ultimate move"), false);
	Register(EAchievementId::CompleteTutorial, FText::FromString("Student No More"), FText::FromString("Complete the tutorial"), false);
	Register(EAchievementId::CreateCharacter, FText::FromString("Creator"), FText::FromString("Create your first character"), false);
	Register(EAchievementId::AIGeneration, FText::FromString("AI Artist"), FText::FromString("Generate a character with AI"), false);
	Register(EAchievementId::ReachLevel10, FText::FromString("Getting Started"), FText::FromString("Reach player level 10"), false);
	Register(EAchievementId::ReachLevel25, FText::FromString("Mid Tier"), FText::FromString("Reach player level 25"), false);
	Register(EAchievementId::ReachLevel50, FText::FromString("Veteran Warrior"), FText::FromString("Reach player level 50"), true);
	Register(EAchievementId::PlayOnline, FText::FromString("Online Warrior"), FText::FromString("Play your first online match"), false);
	Register(EAchievementId::WinOnline, FText::FromString("Online Champion"), FText::FromString("Win an online match"), false);
	Register(EAchievementId::UnlockAllStyles, FText::FromString("Style Master"), FText::FromString("Unlock all fighting styles"), true);
	Register(EAchievementId::UnlockAllArenas, FText::FromString("World Traveler"), FText::FromString("Unlock all arenas"), true);
	Register(EAchievementId::MaxDamage, FText::FromString("One Punch"), FText::FromString("Deal 500+ damage in a single hit"), false);
	Register(EAchievementId::PerfectRound, FText::FromString("Perfect Round"), FText::FromString("Win a round without taking damage"), false);
	Register(EAchievementId::ComebackVictory, FText::FromString("Comeback Victory"), FText::FromString("Win from 10% health or less"), true);
	Register(EAchievementId::VeteranPlayer, FText::FromString("Veteran"), FText::FromString("Play 100 matches total"), true);
}

void ULesFightAchievementManager::Shutdown()
{
}

void ULesFightAchievementManager::RegisterAchievement(EAchievementId ID, FText Title, FText Description, bool bHidden)
{
	FAchievementDef Def;
	Def.ID = ID;
	Def.Title = Title;
	Def.Description = Description;
	Def.bHidden = bHidden;

	AchievementRegistry.Add(ID, Def);
	AchievementProgress.Add(ID, 0.0f);
}

bool ULesFightAchievementManager::UnlockAchievement(EAchievementId ID)
{
	if (ID == EAchievementId::MAX)
	{
		return false;
	}

	if (UnlockedAchievements.Contains(ID))
	{
		return false;
	}

	UnlockedAchievements.Add(ID);
	AchievementProgress.Add(ID, 1.0f);

	OnAchievementUnlocked.Broadcast(ID);
	return true;
}

bool ULesFightAchievementManager::IsAchievementUnlocked(EAchievementId ID) const
{
	return UnlockedAchievements.Contains(ID);
}

float ULesFightAchievementManager::GetAchievementProgress(EAchievementId ID) const
{
	if (const float* Progress = AchievementProgress.Find(ID))
	{
		return *Progress;
	}
	return 0.0f;
}

bool ULesFightAchievementManager::SetAchievementProgress(EAchievementId ID, float Progress)
{
	if (ID == EAchievementId::MAX)
	{
		return false;
	}

	float ClampedProgress = FMath::Clamp(Progress, 0.0f, 1.0f);
	AchievementProgress.Add(ID, ClampedProgress);
	return true;
}

bool ULesFightAchievementManager::IncrementAchievementProgress(EAchievementId ID, float Amount)
{
	if (ID == EAchievementId::MAX)
	{
		return false;
	}

	float Current = GetAchievementProgress(ID);
	float NewProgress = FMath::Clamp(Current + Amount, 0.0f, 1.0f);
	AchievementProgress.Add(ID, NewProgress);
	return true;
}

FAchievementDef ULesFightAchievementManager::GetAchievementDef(EAchievementId ID) const
{
	if (const FAchievementDef* Def = AchievementRegistry.Find(ID))
	{
		return *Def;
	}
	return FAchievementDef();
}

TArray<FAchievementDef> ULesFightAchievementManager::GetAllAchievements() const
{
	TArray<FAchievementDef> Result;
	AchievementRegistry.GenerateValueArray(Result);
	return Result;
}

TArray<FAchievementDef> ULesFightAchievementManager::GetUnlockedAchievements() const
{
	TArray<FAchievementDef> Result;
	for (EAchievementId ID : UnlockedAchievements)
	{
		if (const FAchievementDef* Def = AchievementRegistry.Find(ID))
		{
			Result.Add(*Def);
		}
	}
	return Result;
}

TArray<FAchievementDef> ULesFightAchievementManager::GetLockedAchievements() const
{
	TArray<FAchievementDef> Result;
	for (const auto& Pair : AchievementRegistry)
	{
		if (!UnlockedAchievements.Contains(Pair.Key))
		{
			Result.Add(Pair.Value);
		}
	}
	return Result;
}

int32 ULesFightAchievementManager::GetTotalUnlocked() const
{
	return UnlockedAchievements.Num();
}

int32 ULesFightAchievementManager::GetTotalAchievements() const
{
	return AchievementRegistry.Num();
}

float ULesFightAchievementManager::GetOverallProgress() const
{
	if (AchievementRegistry.Num() == 0)
	{
		return 0.0f;
	}
	return (float)UnlockedAchievements.Num() / (float)AchievementRegistry.Num();
}

void ULesFightAchievementManager::ResetAchievements()
{
	UnlockedAchievements.Empty();
	AchievementProgress.Empty();

	for (const auto& Pair : AchievementRegistry)
	{
		AchievementProgress.Add(Pair.Key, 0.0f);
	}
}
