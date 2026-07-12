#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightAchievementManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAchievementUnlockedDelegate, EAchievementId, ID);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAchievementManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Achievement")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	void RegisterAchievement(EAchievementId ID, FText Title, FText Description, bool bHidden);

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	bool UnlockAchievement(EAchievementId ID);

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	bool IsAchievementUnlocked(EAchievementId ID) const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	float GetAchievementProgress(EAchievementId ID) const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	bool SetAchievementProgress(EAchievementId ID, float Progress);

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	bool IncrementAchievementProgress(EAchievementId ID, float Amount);

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	FAchievementDef GetAchievementDef(EAchievementId ID) const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	TArray<FAchievementDef> GetAllAchievements() const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	TArray<FAchievementDef> GetUnlockedAchievements() const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	TArray<FAchievementDef> GetLockedAchievements() const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	int32 GetTotalUnlocked() const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	int32 GetTotalAchievements() const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	float GetOverallProgress() const;

	UFUNCTION(BlueprintCallable, Category = "Achievement")
	void ResetAchievements();

	UPROPERTY(BlueprintAssignable, Category = "Achievement")
	FOnAchievementUnlockedDelegate OnAchievementUnlocked;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Achievement")
	TMap<EAchievementId, FAchievementDef> AchievementRegistry;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Achievement")
	TSet<EAchievementId> UnlockedAchievements;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Achievement")
	TMap<EAchievementId, float> AchievementProgress;
};
