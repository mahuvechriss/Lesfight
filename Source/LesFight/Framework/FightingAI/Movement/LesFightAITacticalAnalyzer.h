#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAITacticalAnalyzer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAITacticalAnalyzer : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    void AnalyzeTactics(const FAIPerceptionData& Perception, FAIDecisionContext& Decision);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    FVector GetRecommendedPosition() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    bool ShouldChangeRange() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    EAICombatRange GetIdealRange() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    bool IsCornered() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    bool ShouldUseArenaEdges() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    FVector FindAdvantageousPosition() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Tactical")
    float GetTacticalScore() const;

    void Initialize(ULesFightAIFighterController* InController);

protected:
    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Tactical")
    FVector RecommendedPosition;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Tactical")
    EAICombatRange IdealRange;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Tactical")
    float TacticalScore;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Tactical")
    bool bCornered;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Tactical")
    bool bUseArenaEdges;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Tactical")
    TArray<FString> TacticalNotes;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
