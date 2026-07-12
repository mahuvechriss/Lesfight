#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAITrainingMode.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAITrainingMode : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void SetTrainingMode(EAITrainingMode Mode);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    EAITrainingMode GetTrainingMode() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void SetTrainingIntensity(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void EnableTraining(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    bool IsTrainingEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    FString GetTrainingDescription() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void SetPassiveBehavior();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void SetBlockingOnly();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void SetComboPractice();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void SetCounterPractice();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void SetDodgePractice();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Training")
    void ResetTrainingSettings();

    void Initialize(ULesFightAIFighterController* InController);

protected:
    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Training")
    EAITrainingMode CurrentMode;

    UPROPERTY(EditDefaultsOnly, Category = "FightingAI|Training")
    float TrainingIntensity = 0.5f;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Training")
    bool bTrainingEnabled;

    UPROPERTY()
    TMap<EAITrainingMode, TArray<EAIActionType>> AllowedActions;

    UPROPERTY()
    TMap<EAITrainingMode, FString> ModeDescriptions;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;

    void BuildAllowedActions();
    void BuildModeDescriptions();
};
