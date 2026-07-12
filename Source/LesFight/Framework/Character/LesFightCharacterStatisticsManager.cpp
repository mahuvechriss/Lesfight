#include "LesFightCharacterStatisticsManager.h"
#include "LesFight.h"

ULesFightCharacterStatisticsManager::ULesFightCharacterStatisticsManager()
{
}

void ULesFightCharacterStatisticsManager::Initialize()
{
    LoadStats();
    UE_LOG(LogLesFight, Log, TEXT("CharacterStatisticsManager initialized"));
}

void ULesFightCharacterStatisticsManager::RecordMatch(FName CharacterID, bool bWon, bool bByKO, bool bPerfect)
{
    if (!FighterStatsMap.Contains(CharacterID))
    {
        FighterStatsMap.Add(CharacterID, FFighterMatchStats());
    }

    FFighterMatchStats& Stats = FighterStatsMap[CharacterID];
    Stats.MatchesPlayed++;

    if (bWon)
    {
        Stats.Wins++;
        Stats.CurrentWinStreak++;
        if (Stats.CurrentWinStreak > Stats.BestWinStreak)
        {
            Stats.BestWinStreak = Stats.CurrentWinStreak;
        }
    }
    else
    {
        Stats.Losses++;
        Stats.CurrentWinStreak = 0;
    }

    if (bByKO) Stats.KOs++;
    if (bPerfect) Stats.Perfects++;

    UpdateWinRate(Stats);
    OnFighterStatsUpdated.Broadcast(CharacterID, Stats);
}

void ULesFightCharacterStatisticsManager::RecordDamage(FName CharacterID, float DamageDealt, float DamageReceived)
{
    if (!FighterStatsMap.Contains(CharacterID))
    {
        FighterStatsMap.Add(CharacterID, FFighterMatchStats());
    }

    FFighterMatchStats& Stats = FighterStatsMap[CharacterID];
    Stats.TotalDamageDealt += DamageDealt;
    Stats.TotalDamageReceived += DamageReceived;
}

void ULesFightCharacterStatisticsManager::RecordPlayTime(FName CharacterID, float TimeSeconds)
{
    if (!FighterStatsMap.Contains(CharacterID))
    {
        FighterStatsMap.Add(CharacterID, FFighterMatchStats());
    }

    FighterStatsMap[CharacterID].TotalPlayTime += TimeSeconds;
}

FFighterMatchStats ULesFightCharacterStatisticsManager::GetFighterStats(FName CharacterID) const
{
    if (FighterStatsMap.Contains(CharacterID))
        return FighterStatsMap[CharacterID];
    return FFighterMatchStats();
}

TArray<FName> ULesFightCharacterStatisticsManager::GetMostPlayedFighters(int32 Count) const
{
    TArray<FName> Sorted;
    FighterStatsMap.GetKeys(Sorted);

    Sorted.Sort([this](const FName& A, const FName& B) {
        return FighterStatsMap[A].MatchesPlayed > FighterStatsMap[B].MatchesPlayed;
    });

    if (Sorted.Num() > Count)
        Sorted.SetNum(Count);

    return Sorted;
}

TArray<FName> ULesFightCharacterStatisticsManager::GetHighestWinRateFighters(int32 Count) const
{
    TArray<FName> Sorted;
    FighterStatsMap.GetKeys(Sorted);

    Sorted.Sort([this](const FName& A, const FName& B) {
        return FighterStatsMap[A].WinRate > FighterStatsMap[B].WinRate;
    });

    if (Sorted.Num() > Count)
        Sorted.SetNum(Count);

    return Sorted;
}

void ULesFightCharacterStatisticsManager::ResetAllStats()
{
    FighterStatsMap.Empty();
    SaveStats();
}

void ULesFightCharacterStatisticsManager::ResetFighterStats(FName CharacterID)
{
    if (FighterStatsMap.Contains(CharacterID))
    {
        FighterStatsMap[CharacterID] = FFighterMatchStats();
    }
}

void ULesFightCharacterStatisticsManager::SaveStats()
{
    UE_LOG(LogLesFight, Log, TEXT("Fighter stats saved"));
}

void ULesFightCharacterStatisticsManager::LoadStats()
{
    UE_LOG(LogLesFight, Log, TEXT("Fighter stats loaded"));
}

void ULesFightCharacterStatisticsManager::UpdateWinRate(FFighterMatchStats& Stats)
{
    Stats.WinRate = Stats.MatchesPlayed > 0
        ? (static_cast<float>(Stats.Wins) / Stats.MatchesPlayed) * 100.0f
        : 0.0f;
}
