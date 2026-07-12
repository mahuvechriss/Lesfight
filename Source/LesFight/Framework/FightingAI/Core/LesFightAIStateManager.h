#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIStateManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIStateManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|State")
    void SetState(EAIBehaviorMode NewMode);

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    EAIBehaviorMode GetState() const;

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    void SetFlag(EAIStateFlags Flag, bool bValue);

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    bool HasFlag(EAIStateFlags Flag) const;

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    float GetStateTime() const;

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    bool CanTransitionTo(EAIBehaviorMode Target) const;

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    void Reset();

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    void PushState(EAIBehaviorMode State);

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    void PopState();

    UFUNCTION(BlueprintCallable, Category = "AI|State")
    TArray<EAIBehaviorMode> GetStateStack() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|State")
    EAIBehaviorMode CurrentState = EAIBehaviorMode::Idle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|State")
    TArray<EAIBehaviorMode> StateStack;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|State")
    TArray<TPair<EAIBehaviorMode, float>> StateTimers;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|State")
    int32 StateFlags = 0;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|State")
    float StateStartTime = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|State")
    TMap<EAIBehaviorMode, TArray<EAIBehaviorMode>> ValidTransitions;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;

    void BuildValidTransitions();
};
