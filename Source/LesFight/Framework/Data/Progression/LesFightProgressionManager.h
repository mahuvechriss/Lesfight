#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightProgressionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelUpDelegate, int32, NewLevel, const TArray<FProgressionReward>&, Rewards);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnXPGainedDelegate, int32, Amount, int32, CurrentXP, int32, XPToNext);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightProgressionManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Progression")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Progression")
	int32 AddXP(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	int32 GetCurrentLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	int32 GetCurrentXP() const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	int32 GetXPToNextLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	int32 GetTotalXP() const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	bool SetLevel(int32 Level);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	FProgressionData GetProgressionData() const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void SetProgressionData(const FProgressionData& Data);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	int32 CalculateXPForLevel(int32 Level) const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	int32 GetLevelForXP(int32 XP) const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	float GetLevelProgress() const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	TArray<FProgressionReward> RegisterProgressionEvent(EProgressionEvent Event);

	UPROPERTY(BlueprintAssignable, Category = "Progression")
	FOnLevelUpDelegate OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Progression")
	FOnXPGainedDelegate OnXPGained;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	FProgressionData Progression;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression")
	TMap<int32, TArray<FProgressionReward>> LevelRewards;
};
