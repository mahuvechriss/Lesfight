#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIDefensiveManager.generated.h"

UCLASS(Blueprintable)
class ULesFightAIDefensiveManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    void DecideDefense(const FAIPerceptionData& Perception, const FAIDecisionContext& OffensiveDecision);

    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    bool ShouldBlock() const { return BlockWeight > 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    bool ShouldDodge() const { return DodgeWeight > 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    bool ShouldParry() const { return ParryWeight > 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    bool ShouldCounter() const { return CounterWeight > 0.0f; }

    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    EAIActionType GetDefensiveAction() const { return DefensiveAction; }

    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    void SetDefensiveStyle(float InBlockWeight, float InDodgeWeight, float InParryWeight, float InCounterWeight);

    UFUNCTION(BlueprintCallable, Category = "AI|Defensive")
    void Initialize(class ULesFightAIFighterController* InController);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive")
    EAIActionType DefensiveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive")
    float BlockWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive")
    float DodgeWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive")
    float ParryWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defensive")
    float CounterWeight;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive")
    float DefenseScore;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defensive")
    bool bDefending;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
    UPROPERTY()
    float LastDefenseTime;
};
