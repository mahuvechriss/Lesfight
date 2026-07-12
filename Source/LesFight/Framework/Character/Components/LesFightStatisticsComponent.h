#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightCharacterData.h"
#include "LesFightStatisticsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStatChanged, const FString&, StatName, float, NewValue);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightStatisticsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightStatisticsComponent();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void Initialize(const FCharacterCombatAttributes& CombatStats,
                    const FCharacterMovementAttributes& MoveStats,
                    const FCharacterResourceAttributes& ResourceStats);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void SetStat(const FString& StatName, float Value);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    float GetStat(const FString& StatName) const;

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void ModifyStat(const FString& StatName, float Delta);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void ResetStats();

    UFUNCTION(BlueprintPure, Category = "Statistics")
    FCharacterCombatAttributes GetCombatStats() const { return CombatAttributes; }

    UFUNCTION(BlueprintPure, Category = "Statistics")
    FCharacterMovementAttributes GetMovementStats() const { return MovementAttributes; }

    UFUNCTION(BlueprintPure, Category = "Statistics")
    FCharacterResourceAttributes GetResourceStats() const { return ResourceAttributes; }

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void SetCombatStats(const FCharacterCombatAttributes& NewStats);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void SetMovementStats(const FCharacterMovementAttributes& NewStats);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void SetResourceStats(const FCharacterResourceAttributes& NewStats);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void ApplyStatMultiplier(const FString& StatName, float Multiplier);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void ClearAllMultipliers();

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Statistics")
    FCharacterCombatAttributes CombatAttributes;

    UPROPERTY(BlueprintReadWrite, Category = "Statistics")
    FCharacterMovementAttributes MovementAttributes;

    UPROPERTY(BlueprintReadWrite, Category = "Statistics")
    FCharacterResourceAttributes ResourceAttributes;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStatChanged OnStatChanged;

    UPROPERTY(BlueprintReadWrite, Category = "Statistics")
    TMap<FString, float> StatMultipliers;

private:
    TMap<FString, float> BaseStats;

    void CacheBaseStats();
    void ApplyAllMultipliers();
};
