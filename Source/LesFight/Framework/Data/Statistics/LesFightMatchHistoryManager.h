#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightMatchHistoryManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHistoryUpdatedDelegate);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMatchHistoryManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Match History")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Match History")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Match History")
	void AddMatchEntry(const FMatchHistoryEntry& Entry);

	UFUNCTION(BlueprintCallable, Category = "Match History")
	TArray<FMatchHistoryEntry> GetMatchHistory() const;

	TArray<FMatchHistoryEntry> GetMatchHistory(int32 Count) const;

	UFUNCTION(BlueprintCallable, Category = "Match History")
	FMatchHistoryEntry GetMatch(int32 Index) const;

	UFUNCTION(BlueprintCallable, Category = "Match History")
	int32 GetMatchCount() const;

	UFUNCTION(BlueprintCallable, Category = "Match History")
	void ClearHistory();

	UFUNCTION(BlueprintCallable, Category = "Match History")
	TArray<FMatchHistoryEntry> GetRecentMatches(int32 Count) const;

	UFUNCTION(BlueprintCallable, Category = "Match History")
	TArray<FMatchHistoryEntry> GetMatchesByArena(FName ArenaID) const;

	UFUNCTION(BlueprintCallable, Category = "Match History")
	TArray<FMatchHistoryEntry> GetMatchesByOpponent(FName OpponentName) const;

	UFUNCTION(BlueprintCallable, Category = "Match History")
	float GetWinLossRatio() const;

	UFUNCTION(BlueprintCallable, Category = "Match History")
	FString ExportHistoryToCSV() const;

	UPROPERTY(BlueprintAssignable, Category = "Match History")
	FOnHistoryUpdatedDelegate OnHistoryUpdated;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match History")
	TArray<FMatchHistoryEntry> MatchHistory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match History")
	int32 MaxHistoryEntries = 200;
};
