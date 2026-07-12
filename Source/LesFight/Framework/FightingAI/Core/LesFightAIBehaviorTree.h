#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIBehaviorTree.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIBehaviorTree : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")
    void Evaluate(const FAIPerceptionData& Perception, FAIDecisionContext& Decision);

    UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")
    FAIDecisionContext SelectNode(const TArray<FAIDecisionContext>& Candidates);

    UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")
    FAIDecisionContext GetSelectedNode() const;

    UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")
    void SetBehaviorProfile(const FAIStyleBehaviorProfile& Profile);

    UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree")
    void SetDifficultyProfile(const FAIDifficultySettings& Settings);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|BehaviorTree")
    FAIStyleBehaviorProfile CurrentProfile;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|BehaviorTree")
    FAIDifficultySettings CurrentDifficultySettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|BehaviorTree")
    FAIDecisionContext SelectedNode;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|BehaviorTree")
    TArray<FString> EvaluationLog;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
