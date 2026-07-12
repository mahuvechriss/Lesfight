#include "Framework/Data/Progression/LesFightProgressionManager.h"

void ULesFightProgressionManager::Initialize()
{
	Progression = FProgressionData();
	Progression.PlayerLevel = 1;
	Progression.CurrentXP = 0;
	Progression.XPToNextLevel = CalculateXPForLevel(1);

	LevelRewards.Empty();

	TArray<FProgressionReward> Level1Rewards;
	LevelRewards.Add(1, Level1Rewards);

	TArray<FProgressionReward> Level2Rewards;
	{
		FProgressionReward& Reward = Level2Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::CharacterSlot;
		Reward.Amount = 1;
	}
	LevelRewards.Add(2, Level2Rewards);

	TArray<FProgressionReward> Level5Rewards;
	{
		FProgressionReward& Reward = Level5Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::UnlockItem;
		Reward.ItemID = FName("StyleUnlock");
	}
	LevelRewards.Add(5, Level5Rewards);

	TArray<FProgressionReward> Level10Rewards;
	{
		FProgressionReward& Reward = Level10Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::Title;
		Reward.ItemID = FName("Title_Level10");
	}
	LevelRewards.Add(10, Level10Rewards);

	TArray<FProgressionReward> Level15Rewards;
	{
		FProgressionReward& Reward = Level15Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::Currency;
		Reward.Amount = 500;
	}
	LevelRewards.Add(15, Level15Rewards);

	TArray<FProgressionReward> Level20Rewards;
	{
		FProgressionReward& Reward = Level20Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::CharacterSlot;
		Reward.Amount = 1;
	}
	LevelRewards.Add(20, Level20Rewards);

	TArray<FProgressionReward> Level25Rewards;
	{
		FProgressionReward& Reward = Level25Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::Avatar;
		Reward.ItemID = FName("Avatar_Level25");
	}
	LevelRewards.Add(25, Level25Rewards);

	TArray<FProgressionReward> Level30Rewards;
	{
		FProgressionReward& Reward = Level30Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::Currency;
		Reward.Amount = 1000;
	}
	LevelRewards.Add(30, Level30Rewards);

	TArray<FProgressionReward> Level50Rewards;
	{
		FProgressionReward& Reward = Level50Rewards.AddDefaulted_GetRef();
		Reward.Type = EProgressionRewardType::Title;
		Reward.ItemID = FName("Title_Legendary");
	}
	LevelRewards.Add(50, Level50Rewards);
}

void ULesFightProgressionManager::Shutdown()
{
}

int32 ULesFightProgressionManager::AddXP(int32 Amount)
{
	if (Amount <= 0)
	{
		return 0;
	}

	Progression.CurrentXP += Amount;
	Progression.TotalXP += Amount;

	int32 NewLevel = 0;

	while (Progression.CurrentXP >= Progression.XPToNextLevel)
	{
		Progression.CurrentXP -= Progression.XPToNextLevel;
		Progression.PlayerLevel++;
		Progression.XPToNextLevel = CalculateXPForLevel(Progression.PlayerLevel);

		TArray<FProgressionReward> Rewards;
		if (const TArray<FProgressionReward>* FoundRewards = LevelRewards.Find(Progression.PlayerLevel))
		{
			Rewards = *FoundRewards;
		}

		OnLevelUp.Broadcast(Progression.PlayerLevel, Rewards);
		NewLevel = Progression.PlayerLevel;
	}

	OnXPGained.Broadcast(Amount, Progression.CurrentXP, Progression.XPToNextLevel);
	return NewLevel;
}

int32 ULesFightProgressionManager::GetCurrentLevel() const
{
	return Progression.PlayerLevel;
}

int32 ULesFightProgressionManager::GetCurrentXP() const
{
	return Progression.CurrentXP;
}

int32 ULesFightProgressionManager::GetXPToNextLevel() const
{
	return Progression.XPToNextLevel;
}

int32 ULesFightProgressionManager::GetTotalXP() const
{
	return Progression.TotalXP;
}

bool ULesFightProgressionManager::SetLevel(int32 Level)
{
	if (Level < 1)
	{
		return false;
	}

	Progression.PlayerLevel = Level;
	Progression.CurrentXP = 0;
	Progression.XPToNextLevel = CalculateXPForLevel(Level);
	return true;
}

FProgressionData ULesFightProgressionManager::GetProgressionData() const
{
	return Progression;
}

void ULesFightProgressionManager::SetProgressionData(const FProgressionData& Data)
{
	Progression = Data;
}

int32 ULesFightProgressionManager::CalculateXPForLevel(int32 Level) const
{
	return Level * 1000;
}

int32 ULesFightProgressionManager::GetLevelForXP(int32 XP) const
{
	if (XP <= 0)
	{
		return 1;
	}

	int32 Level = 1;
	int32 AccumulatedXP = 0;

	while (true)
	{
		int32 NeededForThisLevel = CalculateXPForLevel(Level);
		if (AccumulatedXP + NeededForThisLevel > XP)
		{
			return Level;
		}
		AccumulatedXP += NeededForThisLevel;
		Level++;
	}
}

float ULesFightProgressionManager::GetLevelProgress() const
{
	if (Progression.XPToNextLevel <= 0)
	{
		return 0.0f;
	}
	return (float)Progression.CurrentXP / (float)Progression.XPToNextLevel;
}

TArray<FProgressionReward> ULesFightProgressionManager::RegisterProgressionEvent(EProgressionEvent Event)
{
	TArray<FProgressionReward> Rewards;

	switch (Event)
	{
	case EProgressionEvent::FightCompleted:
		AddXP(50);
		break;

	case EProgressionEvent::FirstWin:
	{
		FProgressionReward Reward;
		Reward.Type = EProgressionRewardType::Currency;
		Reward.Amount = 200;
		Rewards.Add(Reward);
		AddXP(200);
		break;
	}

	case EProgressionEvent::WinStreak:
		AddXP(100);
		break;

	case EProgressionEvent::AchievementUnlocked:
	{
		FProgressionReward Reward;
		Reward.Type = EProgressionRewardType::XP;
		Reward.Amount = 500;
		Rewards.Add(Reward);
		AddXP(Reward.Amount);
		break;
	}

	case EProgressionEvent::CharacterCreated:
		AddXP(75);
		break;

	case EProgressionEvent::MilestoneReached:
	{
		FProgressionReward Reward;
		Reward.Type = EProgressionRewardType::Currency;
		Reward.Amount = 1000;
		Rewards.Add(Reward);
		AddXP(300);
		break;
	}

	default:
		break;
	}

	return Rewards;
}
