#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIAdaptiveLearning.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIAdaptiveLearning : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAIAdaptiveLearning();

    UFUNCTION(BlueprintCallable)
    void ObservePlayerAction(EAIActionType Action);

    UFUNCTION(BlueprintCallable)
    void ObservePlayerCombo(FName ComboName);

    UFUNCTION(BlueprintCallable)
    void AnalyzePatterns();

    UFUNCTION(BlueprintCallable)
    FAIAdaptiveData GetAdaptiveData() const { return AdaptiveData; }

    UFUNCTION(BlueprintCallable)
    EAIActionType GetPlayerFavoriteAction() const;

    UFUNCTION(BlueprintCallable)
    FName GetPlayerFavoriteCombo() const;

    UFUNCTION(BlueprintCallable)
    float GetPlayerAggression() const { return AdaptiveData.PlayerAggressionScore; }

    UFUNCTION(BlueprintCallable)
    float GetPlayerDefenseStyle() const { return AdaptiveData.PlayerDefenseScore; }

    UFUNCTION(BlueprintCallable)
    bool ShouldAdaptStrategy() const;

    UFUNCTION(BlueprintCallable)
    void AdaptStrategy(FAIDecisionContext& Decision);

    UFUNCTION(BlueprintCallable)
    void ResetLearning();

    UFUNCTION(BlueprintCallable)
    void SetLearningRate(float Rate) { LearningRate = Rate; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Learning")
    FAIAdaptiveData AdaptiveData;

    UPROPERTY()
    TArray<EAIActionType> RecentActions;

    UPROPERTY()
    TArray<FName> RecentCombos;

    UPROPERTY(EditDefaultsOnly, Category = "Learning")
    float LearningRate;

    UPROPERTY(VisibleAnywhere, Category = "Learning")
    int32 AdaptationsPerformed;

    UPROPERTY()
    float LastAdaptationTime;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
