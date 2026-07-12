#include "Framework/Data/Statistics/LesFightStatisticsManager.h"

void ULesFightStatisticsManager::Initialize()
{
	Statistics = FMatchStatisticsData();
	Statistics.Wins = 0;
	Statistics.Losses = 0;
	Statistics.Draws = 0;
	Statistics.TotalFights = 0;
	Statistics.HighestCombo = 0;
	Statistics.HighestDamage = 0;
	Statistics.TotalPlayTimeSeconds = 0.0f;
	Statistics.TotalKOs = 0;
	Statistics.TotalPerfects = 0;
	Statistics.CurrentWinStreak = 0;
	Statistics.LongestWinStreak = 0;
	Statistics.FavoriteFighter = FName();
	Statistics.FavoriteStyle = EFightingStyle::Karate;
	FighterUsageCount.Empty();
	StyleUsageCount.Empty();
}

void ULesFightStatisticsManager::Shutdown()
{
}

void ULesFightStatisticsManager::RecordMatch(bool bWon, int32 Combo, float Damage, int32 KOs, bool bPerfect)
{
	Statistics.TotalFights++;

	if (bWon)
	{
		Statistics.Wins++;
		Statistics.CurrentWinStreak++;
		if (Statistics.CurrentWinStreak > Statistics.LongestWinStreak)
		{
			Statistics.LongestWinStreak = Statistics.CurrentWinStreak;
		}
	}
	else
	{
		Statistics.Losses++;
		Statistics.CurrentWinStreak = 0;
	}

	if (Combo > Statistics.HighestCombo)
	{
		Statistics.HighestCombo = Combo;
	}

	if (Damage > Statistics.HighestDamage)
	{
		Statistics.HighestDamage = Damage;
	}

	if (bPerfect)
	{
		Statistics.TotalPerfects++;
	}

	if (KOs > 0)
	{
		Statistics.TotalKOs += KOs;
	}

	OnStatisticsUpdated.Broadcast();
}

FMatchStatisticsData ULesFightStatisticsManager::GetStatistics() const
{
	return Statistics;
}

void ULesFightStatisticsManager::SetStatistics(const FMatchStatisticsData& Stats)
{
	Statistics = Stats;
}

void ULesFightStatisticsManager::ResetStatistics()
{
	Initialize();
	OnStatisticsUpdated.Broadcast();
}

int32 ULesFightStatisticsManager::GetWins() const
{
	return Statistics.Wins;
}

int32 ULesFightStatisticsManager::GetLosses() const
{
	return Statistics.Losses;
}

int32 ULesFightStatisticsManager::GetDraws() const
{
	return Statistics.Draws;
}

float ULesFightStatisticsManager::GetWinRate() const
{
	if (Statistics.TotalFights == 0)
	{
		return 0.0f;
	}
	return (float)Statistics.Wins / (float)Statistics.TotalFights;
}

int32 ULesFightStatisticsManager::GetTotalFights() const
{
	return Statistics.TotalFights;
}

void ULesFightStatisticsManager::RecordFighterUsage(FName FighterID, EFightingStyle Style)
{
	int32& FighterCount = FighterUsageCount.FindOrAdd(FighterID);
	FighterCount++;

	int32& StyleCount = StyleUsageCount.FindOrAdd(Style);
	StyleCount++;

	int32 MaxFighterCount = 0;
	for (const auto& Pair : FighterUsageCount)
	{
		if (Pair.Value > MaxFighterCount)
		{
			MaxFighterCount = Pair.Value;
			Statistics.FavoriteFighter = Pair.Key;
		}
	}

	int32 MaxStyleCount = 0;
	for (const auto& Pair : StyleUsageCount)
	{
		if (Pair.Value > MaxStyleCount)
		{
			MaxStyleCount = Pair.Value;
			Statistics.FavoriteStyle = Pair.Key;
		}
	}
}

FName ULesFightStatisticsManager::GetFavoriteFighter() const
{
	return Statistics.FavoriteFighter;
}

EFightingStyle ULesFightStatisticsManager::GetFavoriteStyle() const
{
	return Statistics.FavoriteStyle;
}

void ULesFightStatisticsManager::AddPlayTime(float Seconds)
{
	Statistics.TotalPlayTimeSeconds += Seconds;
}

float ULesFightStatisticsManager::GetTotalPlayTime() const
{
	return Statistics.TotalPlayTimeSeconds;
}

void ULesFightStatisticsManager::UpdateHighestCombo(int32 Combo)
{
	if (Combo > Statistics.HighestCombo)
	{
		Statistics.HighestCombo = Combo;
	}
}

void ULesFightStatisticsManager::UpdateHighestDamage(float Damage)
{
	if (Damage > Statistics.HighestDamage)
	{
		Statistics.HighestDamage = Damage;
	}
}

int32 ULesFightStatisticsManager::GetHighestCombo() const
{
	return Statistics.HighestCombo;
}

float ULesFightStatisticsManager::GetHighestDamage() const
{
	return Statistics.HighestDamage;
}
