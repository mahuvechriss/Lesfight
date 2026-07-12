#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIDecisionManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIDecisionManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    void MakeDecision(const FAIPerceptionData& Perception, FAIDecisionContext& OutDecision);

    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    void SetDifficulty(EAIDifficulty Difficulty);

    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    EAIDifficulty GetDifficulty() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    void SetPersonality(EAIPersonalityType Personality);

    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    void CancelCurrentDecision();

    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    FAIDecisionContext GetLastDecision() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Decision")
    TArray<FAIDecisionContext> GetDecisionHistory() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Decision")
    FAIDecisionContext LastDecision;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Decision")
    TArray<FAIDecisionContext> DecisionHistory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Decision")
    EAIDifficulty CurrentDifficulty = EAIDifficulty::Normal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Decision")
    EAIPersonalityType CurrentPersonality = EAIPersonalityType::Adaptive;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Decision")
    TMap<EAIActionType, float> ActionScores;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
