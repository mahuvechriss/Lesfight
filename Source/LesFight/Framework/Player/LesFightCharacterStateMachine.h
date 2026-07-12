#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightCharacterStateMachine.generated.h"

UENUM(BlueprintType)
enum class ECharacterGameplayState : uint8
{
    None,
    Spawning,
    Idle,
    Moving,
    Sprinting,
    Jumping,
    Falling,
    Landing,
    Crouching,
    Attacking,
    Blocking,
    HitStun,
    KnockedDown,
    GettingUp,
    Dead,
    Respawning,
    Cinematic
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayStateChanged, ECharacterGameplayState, NewState, ECharacterGameplayState, PreviousState);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightCharacterStateMachine : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightCharacterStateMachine();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "State Machine")
    void SetState(ECharacterGameplayState NewState);

    UFUNCTION(BlueprintPure, Category = "State Machine")
    ECharacterGameplayState GetCurrentState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "State Machine")
    ECharacterGameplayState GetPreviousState() const { return PreviousState; }

    UFUNCTION(BlueprintPure, Category = "State Machine")
    float GetTimeInCurrentState() const { return TimeInCurrentState; }

    UFUNCTION(BlueprintCallable, Category = "State Machine")
    bool CanTransitionTo(ECharacterGameplayState NewState) const;

    UFUNCTION(BlueprintCallable, Category = "State Machine")
    void ForceState(ECharacterGameplayState NewState);

    UFUNCTION(BlueprintCallable, Category = "State Machine")
    void SetStateTransitionDuration(ECharacterGameplayState State, float Duration);

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnGameplayStateChanged OnGameplayStateChanged;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State Machine")
    TMap<ECharacterGameplayState, float> StateTransitionDurations;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State Machine")
    TArray<ECharacterGameplayState> AllowedStateTransitions;

private:
    ECharacterGameplayState CurrentState;
    ECharacterGameplayState PreviousState;
    float TimeInCurrentState;
    float StateStartTime;

    void OnStateEnter(ECharacterGameplayState NewState);
    void OnStateExit(ECharacterGameplayState OldState);
    void OnStateTick(float DeltaTime);
    bool IsStateTransitionAllowed(ECharacterGameplayState From, ECharacterGameplayState To) const;
};
