#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightCharacterProgression.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExperienceGained, float, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityUnlocked, FName, AbilityID);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightCharacterProgression : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightCharacterProgression();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Progression")
    void Initialize(int32 StartLevel = 1);

    UFUNCTION(BlueprintCallable, Category = "Progression")
    void AddExperience(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Progression")
    void SetLevel(int32 NewLevel);

    UFUNCTION(BlueprintPure, Category = "Progression")
    int32 GetLevel() const { return CurrentLevel; }

    UFUNCTION(BlueprintPure, Category = "Progression")
    float GetCurrentExperience() const { return CurrentExperience; }

    UFUNCTION(BlueprintPure, Category = "Progression")
    float GetExperienceToNextLevel() const;

    UFUNCTION(BlueprintPure, Category = "Progression")
    float GetExperienceProgress() const;

    UFUNCTION(BlueprintCallable, Category = "Progression")
    void UnlockAbility(FName AbilityID);

    UFUNCTION(BlueprintPure, Category = "Progression")
    bool IsAbilityUnlocked(FName AbilityID) const;

    UFUNCTION(BlueprintPure, Category = "Progression")
    TArray<FName> GetUnlockedAbilities() const { return UnlockedAbilities; }

    UFUNCTION(BlueprintCallable, Category = "Progression")
    void SetProgressionMultiplier(float Multiplier) { ProgressionMultiplier = Multiplier; }

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLevelUp OnLevelUp;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnExperienceGained OnExperienceGained;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAbilityUnlocked OnAbilityUnlocked;

    UPROPERTY(BlueprintReadOnly, Category = "Progression")
    int32 CurrentLevel;

    UPROPERTY(BlueprintReadOnly, Category = "Progression")
    float CurrentExperience;

    UPROPERTY(BlueprintReadOnly, Category = "Progression")
    TArray<FName> UnlockedAbilities;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression")
    float ProgressionMultiplier;

private:
    TArray<float> LevelThresholds;

    float GetExperienceForLevel(int32 Level) const;
    void CheckLevelUp();
};
