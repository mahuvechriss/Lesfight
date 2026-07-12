#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightLocomotionSystem.generated.h"

class ULesFightCharacterAnimationComponent;
class ULesFightAnimBlueprintBase;

UCLASS(Blueprintable)
class ULesFightLocomotionSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightLocomotionSystem();

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void SetMovementValues(float Speed, float Direction, float Acceleration);

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void SetLocomotionState(ELocomotionState State);

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void SetAnimationSet(const FLocomotionAnimSet& AnimSet);

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void ResetLocomotion();

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void SetIdleVariationEnabled(bool bEnable) { bIdleVariationsEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Locomotion")
    void SetTurnInPlaceEnabled(bool bEnable) { bTurnInPlaceEnabled = bEnable; }

    UFUNCTION(BlueprintPure, Category = "Locomotion")
    ELocomotionState GetCurrentState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "Locomotion")
    float GetCurrentSpeed() const { return CurrentSpeed; }

    UFUNCTION(BlueprintPure, Category = "Locomotion")
    float GetCurrentDirection() const { return CurrentDirection; }

    UFUNCTION(BlueprintPure, Category = "Locomotion")
    bool IsMoving() const { return bIsMoving; }

    UFUNCTION(BlueprintPure, Category = "Locomotion")
    float GetSpeedBlendValue() const { return SpeedBlendValue; }

    UFUNCTION(BlueprintPure, Category = "Locomotion")
    float GetDirectionBlendValue() const { return DirectionBlendValue; }

    UFUNCTION(BlueprintPure, Category = "Locomotion")
    float GetIdleTimer() const { return IdleTimer; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    TObjectPtr<ULesFightAnimationDataAsset> AnimationData;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    FLocomotionAnimSet CurrentAnimSet;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    ELocomotionState CurrentState;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    ELocomotionState PreviousState;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    float CurrentSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    float CurrentDirection;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    float CurrentAcceleration;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    float SpeedBlendValue;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    float DirectionBlendValue;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    float IdleTimer;

    UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
    bool bIsMoving;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
    float IdleVariationInterval;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
    float TurnThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
    float MoveStartThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
    float SpeedSmoothRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
    float DirectionSmoothRate;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<ULesFightAnimBlueprintBase> AnimBP;
    float SmoothedSpeed;
    float SmoothedDirection;
    float TurnYawDelta;
    float LastYaw;
    int32 CurrentIdleVariation;

    void UpdateIdle(float DeltaTime);
    void UpdateMoving(float DeltaTime);
    void UpdateInAir(float DeltaTime);
    void UpdateTransitionStates(float DeltaTime);
    void CheckTurnInPlace(float DeltaTime);
    void UpdateBlendValues(float DeltaTime);
    void PlayIdleVariation();
};
