#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightStanceSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStanceChanged, ECombatStance, NewStance);

UCLASS(Blueprintable)
class ULesFightStanceSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightStanceSystem();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    bool SwitchStance(ECombatStance NewStance);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    bool SwitchToNeutral();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    bool SwitchToOffensive();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    bool SwitchToDefensive();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    bool SwitchToAgile();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    bool SwitchToHeavy();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    bool SwitchToStyleSpecific();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    void CycleStance(bool bForward);

    UFUNCTION(BlueprintPure, Category = "MartialArts|Stance")
    ECombatStance GetCurrentStance() const { return CurrentStance; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Stance")
    FStanceAttributes GetCurrentStanceAttributes() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Stance")
    TArray<ECombatStance> GetAvailableStances() const { return AvailableStances; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    void SetStanceData(const TMap<ECombatStance, FStanceAttributes>& Definitions);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    float GetDamageModifier() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    float GetSpeedModifier() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    float GetDefenseModifier() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    float GetStaminaRegenModifier() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    void LockStance(bool bLocked);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Stance")
    void ResetToNeutral();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStanceChanged OnStanceChanged;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECombatStance CurrentStance;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float StanceSwitchCooldown;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bStanceLocked;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<ECombatStance> AvailableStances;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TMap<ECombatStance, FStanceAttributes> StanceDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float SwitchCooldownDuration;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    float LastSwitchTime;

    void BroadcastStanceChange(ECombatStance NewStance);
    FStanceAttributes GetDefaultStanceData(ECombatStance Stance) const;
};
