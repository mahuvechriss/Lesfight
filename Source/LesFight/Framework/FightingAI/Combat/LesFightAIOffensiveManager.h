#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIOffensiveManager.generated.h"

UCLASS(Blueprintable)
class ULesFightAIOffensiveManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    void DecideAttack(const FAIPerceptionData& Perception, FAIDecisionContext& Context);

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    FName GetCurrentCombo() const { return CurrentComboName; }

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    bool IsComboing() const { return bComboing; }

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    int32 GetComboProgress() const { return ComboProgress; }

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    EAIActionType SelectAttackType() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    bool ShouldUseSpecial() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    bool ShouldUseUltimate() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    float GetOffensivenessScore() const { return OffensivenessScore; }

    UFUNCTION(BlueprintCallable, Category = "AI|Offensive")
    void Initialize(class ULesFightAIFighterController* InController);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Offensive")
    FName CurrentComboName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Offensive")
    TArray<EAIActionType> ComboSequence;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Offensive")
    int32 ComboProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offensive")
    float OffensivenessScore;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Offensive")
    bool bComboing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Offensive")
    TArray<EAIActionType> AvailableAttacks;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
    UPROPERTY()
    TMap<EAIActionType, float> AttackCooldowns;
};
