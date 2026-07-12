#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightComboData.h"
#include "LesFightComboManager.generated.h"

class ULesFightCombatComponent;
class ULesFightCombatDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboStarted, FName, ComboID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboProgressed, int32, StepIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboEnded);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightComboManager : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightComboManager();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Combo")
    void Initialize(ULesFightCombatComponent* InCombat, ULesFightCombatDataAsset* CombatData);

    UFUNCTION(BlueprintCallable, Category = "Combo")
    bool RegisterHit(FName AttackID);

    UFUNCTION(BlueprintCallable, Category = "Combo")
    void BreakCombo();

    UFUNCTION(BlueprintCallable, Category = "Combo")
    void ResetCombo();

    UFUNCTION(BlueprintPure, Category = "Combo")
    bool IsComboActive() const { return bComboActive; }

    UFUNCTION(BlueprintPure, Category = "Combo")
    int32 GetComboCount() const { return ComboCount; }

    UFUNCTION(BlueprintPure, Category = "Combo")
    float GetCurrentScaling() const { return CurrentScaling; }

    UFUNCTION(BlueprintPure, Category = "Combo")
    FName GetActiveComboID() const { return ActiveComboID; }

    UFUNCTION(BlueprintPure, Category = "Combo")
    float GetComboTimer() const { return ComboTimer; }

    UFUNCTION(BlueprintPure, Category = "Combo")
    float GetComboWindow() const { return ComboWindow; }

    UFUNCTION(BlueprintCallable, Category = "Combo")
    void SetComboWindow(float Window) { ComboWindow = Window; }

    UFUNCTION(BlueprintCallable, Category = "Combo")
    bool CanCancelInto(FName NextAttackID) const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnComboStarted OnComboStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnComboProgressed OnComboProgressed;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnComboEnded OnComboEnded;

    UPROPERTY(BlueprintReadOnly, Category = "Combo")
    TArray<FComboDefinition> ComboDefinitions;

private:
    TWeakObjectPtr<ULesFightCombatComponent> CombatComponent;
    bool bComboActive;
    int32 ComboCount;
    int32 CurrentComboStep;
    float CurrentScaling;
    float ComboTimer;
    float ComboWindow;
    FName ActiveComboID;
    TArray<FName> ComboHistory;

    const FComboDefinition* FindMatchingCombo(FName LastAttackID) const;
    void StartCombo(const FComboDefinition& Combo);
    void ProgressCombo(int32 StepIndex);
    void EndCombo();
    float CalculateScaling(int32 HitCount) const;
};
