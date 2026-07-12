#include "Framework/Data/Statistics/LesFightMatchHistoryManager.h"

void ULesFightMatchHistoryManager::Initialize()
{
	MatchHistory.Empty();
	MaxHistoryEntries = 200;
}

void ULesFightMatchHistoryManager::Shutdown()
{
}

void ULesFightMatchHistoryManager::AddMatchEntry(const FMatchHistoryEntry& Entry)
{
	MatchHistory.Insert(Entry, 0);

	while (MatchHistory.Num() > MaxHistoryEntries)
	{
		MatchHistory.RemoveAt(MatchHistory.Num() - 1);
	}

	OnHistoryUpdated.Broadcast();
}

TArray<FMatchHistoryEntry> ULesFightMatchHistoryManager::GetMatchHistory() const
{
	return MatchHistory;
}

TArray<FMatchHistoryEntry> ULesFightMatchHistoryManager::GetMatchHistory(int32 Count) const
{
	return GetRecentMatches(Count);
}

FMatchHistoryEntry ULesFightMatchHistoryManager::GetMatch(int32 Index) const
{
	if (MatchHistory.IsValidIndex(Index))
	{
		return MatchHistory[Index];
	}
	return FMatchHistoryEntry();
}

int32 ULesFightMatchHistoryManager::GetMatchCount() const
{
	return MatchHistory.Num();
}

void ULesFightMatchHistoryManager::ClearHistory()
{
	MatchHistory.Empty();
	OnHistoryUpdated.Broadcast();
}

TArray<FMatchHistoryEntry> ULesFightMatchHistoryManager::GetRecentMatches(int32 Count) const
{
	TArray<FMatchHistoryEntry> Result;
	int32 NumToTake = FMath::Min(Count, MatchHistory.Num());
	for (int32 i = 0; i < NumToTake; i++)
	{
		Result.Add(MatchHistory[i]);
	}
	return Result;
}

TArray<FMatchHistoryEntry> ULesFightMatchHistoryManager::GetMatchesByArena(FName ArenaID) const
{
	TArray<FMatchHistoryEntry> Result;
	for (const FMatchHistoryEntry& Entry : MatchHistory)
	{
		if (Entry.ArenaID == ArenaID)
		{
			Result.Add(Entry);
		}
	}
	return Result;
}

TArray<FMatchHistoryEntry> ULesFightMatchHistoryManager::GetMatchesByOpponent(FName OpponentName) const
{
	TArray<FMatchHistoryEntry> Result;
	for (const FMatchHistoryEntry& Entry : MatchHistory)
	{
		if (Entry.OpponentName == OpponentName)
		{
			Result.Add(Entry);
		}
	}
	return Result;
}

float ULesFightMatchHistoryManager::GetWinLossRatio() const
{
	int32 Wins = 0;
	int32 Losses = 0;

	for (const FMatchHistoryEntry& Entry : MatchHistory)
	{
		if (Entry.bWon)
		{
			Wins++;
		}
		else
		{
			Losses++;
		}
	}

	if (Losses == 0)
	{
		return Wins > 0 ? static_cast<float>(Wins) : 0.0f;
	}

	return (float)Wins / (float)Losses;
}

FString ULesFightMatchHistoryManager::ExportHistoryToCSV() const
{
	FString CSV = TEXT("Date,Opponent,Result,Arena,Duration,Rounds,Combo,Damage,Summary\n");

	for (const FMatchHistoryEntry& Entry : MatchHistory)
	{
		FString DateStr = Entry.Date.ToString(TEXT("%Y-%m-%d %H:%M:%S"));
		FString ResultStr = Entry.bWon ? TEXT("Win") : TEXT("Loss");
		FString DurationStr = FString::SanitizeFloat(Entry.DurationSeconds);
		FString DamageStr = FString::SanitizeFloat(Entry.TotalDamage);

		CSV += FString::Printf(TEXT("%s,%s,%s,%s,%s,%d,%d,%s,\"%s\"\n"),
			*DateStr,
			*Entry.OpponentName.ToString(),
			*ResultStr,
			*Entry.ArenaID.ToString(),
			*DurationStr,
			Entry.RoundCount,
			Entry.MaxCombo,
			*DamageStr,
			*Entry.FightSummary
		);
	}

	return CSV;
}
