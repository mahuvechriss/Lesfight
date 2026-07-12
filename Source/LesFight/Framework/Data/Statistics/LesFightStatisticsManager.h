#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightStatisticsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatisticsUpdatedDelegate);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightStatisticsManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void RecordMatch(bool bWon, int32 Combo, float Damage, int32 KOs, bool bPerfect);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	FMatchStatisticsData GetStatistics() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void SetStatistics(const FMatchStatisticsData& Stats);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void ResetStatistics();

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32 GetWins() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32 GetLosses() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32 GetDraws() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	float GetWinRate() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32 GetTotalFights() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void RecordFighterUsage(FName FighterID, EFightingStyle Style);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	FName GetFavoriteFighter() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	EFightingStyle GetFavoriteStyle() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void AddPlayTime(float Seconds);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	float GetTotalPlayTime() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void UpdateHighestCombo(int32 Combo);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	void UpdateHighestDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	int32 GetHighestCombo() const;

	UFUNCTION(BlueprintCallable, Category = "Statistics")
	float GetHighestDamage() const;

	UPROPERTY(BlueprintAssignable, Category = "Statistics")
	FOnStatisticsUpdatedDelegate OnStatisticsUpdated;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")
	FMatchStatisticsData Statistics;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")
	TMap<FName, int32> FighterUsageCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Statistics")
	TMap<EFightingStyle, int32> StyleUsageCount;
};
