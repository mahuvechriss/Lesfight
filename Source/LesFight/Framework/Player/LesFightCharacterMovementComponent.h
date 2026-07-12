#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LesFightCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
    Idle,
    Walking,
    Running,
    Sprinting,
    Jumping,
    Falling,
    Landing,
    Crouching,
    Sliding
};

UCLASS()
class ULesFightCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    ULesFightCharacterMovementComponent();

    virtual float GetMaxSpeed() const override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetWantsToSprint(bool bInWantsToSprint) { bWantsToSprint = bInWantsToSprint; }

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetWantsToCrouch(bool bInWantsToCrouch) { bWantsToCrouch = bInWantsToCrouch; }

    UFUNCTION(BlueprintPure, Category = "Movement")
    bool IsSprinting() const { return bIsSprinting; }

    UFUNCTION(BlueprintPure, Category = "Movement")
    EMovementState GetCurrentMovementState() const { return CurrentMovementState; }

    UFUNCTION(BlueprintPure, Category = "Movement")
    float GetMovementInputMagnitude() const { return CurrentInputMagnitude; }

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetMovementSpeedMultiplier(float Multiplier) { SpeedMultiplier = Multiplier; }

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void ResetMovementState();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Speeds")
    float WalkSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Speeds")
    float RunSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Speeds")
    float SprintSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Speeds")
    float CrouchSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Speeds")
    float AirSpeedMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Rotation")
    float RotationRateMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Sprint")
    float SprintStaminaCostPerSecond;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Sprint")
    float SprintAcceleration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Landing")
    float LandingHardVelocityThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Landing")
    float LandingHardTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Landing")
    float LandingSoftTime;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementStateChanged, EMovementState, NewState);
    FOnMovementStateChanged OnMovementStateChanged;

private:
    bool bWantsToSprint;
    bool bWantsToCrouch;
    bool bIsSprinting;
    EMovementState CurrentMovementState;
    EMovementState PreviousMovementState;
    float CurrentInputMagnitude;
    float SpeedMultiplier;

    void UpdateMovementState();
    void HandleSprint(float DeltaTime);
    void HandleCrouch();
    void HandleLanding();
    void BroadcastStateChange(EMovementState NewState);
};
