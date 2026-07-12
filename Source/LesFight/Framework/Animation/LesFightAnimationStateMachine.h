#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationStateMachine.generated.h"

class ULesFightCharacterAnimationComponent;
class ULesFightAnimBlueprintBase;

USTRUCT(BlueprintType)
struct FAnimStateInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName StateName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ELocomotionState LocomotionState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECombatAnimType CombatState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FAnimTransitionRule> Transitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanBeInterrupted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinStateTime;

    FAnimStateInfo()
        : StateName(NAME_None)
        , LocomotionState(ELocomotionState::None)
        , CombatState(ECombatAnimType::None)
        , bCanBeInterrupted(true)
        , MinStateTime(0.0f)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimStateChanged, FName, FromState, FName, ToState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimStateEntered, FName, StateName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimStateExited, FName, StateName);

UCLASS(Blueprintable)
class ULesFightAnimationStateMachine : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationStateMachine();

    UFUNCTION(BlueprintCallable, Category = "Animation State Machine")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Animation State Machine")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Animation State Machine")
    bool RequestTransition(FName TargetState);

    UFUNCTION(BlueprintCallable, Category = "Animation State Machine")
    void ForceTransition(FName TargetState);

    UFUNCTION(BlueprintCallable, Category = "Animation State Machine")
    void RegisterState(const FAnimStateInfo& StateInfo);

    UFUNCTION(BlueprintCallable, Category = "Animation State Machine")
    void SetAnimationQuality(EAnimationQuality Quality);

    UFUNCTION(BlueprintPure, Category = "Animation State Machine")
    FName GetCurrentState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "Animation State Machine")
    FName GetPreviousState() const { return PreviousState; }

    UFUNCTION(BlueprintPure, Category = "Animation State Machine")
    float GetStateTime() const { return StateTimer; }

    UFUNCTION(BlueprintPure, Category = "Animation State Machine")
    float GetNormalizedStateTime() const;

    UFUNCTION(BlueprintPure, Category = "Animation State Machine")
    bool IsInState(FName StateName) const { return CurrentState == StateName; }

    UFUNCTION(BlueprintPure, Category = "Animation State Machine")
    bool CanTransitionTo(FName TargetState) const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimStateChanged OnAnimStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimStateEntered OnAnimStateEntered;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimStateExited OnAnimStateExited;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<FName, FAnimStateInfo> RegisteredStates;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FName CurrentState;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FName PreviousState;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FName PendingState;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float StateTimer;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
    float TransitionBlendTime;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    bool bTransitionPending;
    float PendingBlendTime;

    void ExecuteTransition(const FAnimTransitionRule& Rule);
    void OnStateEnter(FName StateName);
    void OnStateExit(FName StateName);
};
