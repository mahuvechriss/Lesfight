#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightGameFlowController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameFlowStateChanged, EGameFlowState, OldState, EGameFlowState, NewState);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightGameFlowController : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    void SetState(EGameFlowState NewState);

    UFUNCTION(BlueprintPure, Category = "Integration|GameFlow")
    EGameFlowState GetCurrentState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "Integration|GameFlow")
    EGameFlowState GetPreviousState() const { return PreviousState; }

    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    bool CanTransitionTo(EGameFlowState Target) const;

    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    TArray<EGameFlowState> GetValidTransitions() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    void TransitionToNextState();

    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    void TransitionToPreviousState();

    UFUNCTION(BlueprintCallable, Category = "Integration|GameFlow")
    void ResetToState(EGameFlowState State);

    UFUNCTION(BlueprintPure, Category = "Integration|GameFlow")
    bool IsStateValid(EGameFlowState State) const;

    UFUNCTION(BlueprintPure, Category = "Integration|GameFlow")
    FText GetStateDisplayName(EGameFlowState State) const;

    UPROPERTY(BlueprintAssignable, Category = "Integration|GameFlow")
    FOnGameFlowStateChanged OnGameFlowStateChanged;

protected:
    UPROPERTY()
    EGameFlowState CurrentState = EGameFlowState::Init;

    UPROPERTY()
    EGameFlowState PreviousState = EGameFlowState::Init;

    UPROPERTY()
    TMap<EGameFlowState, TArray<EGameFlowState>> ValidTransitions;

    UPROPERTY()
    TMap<EGameFlowState, FText> StateDisplayNames;
};
