#include "LesFightCharacterMovementComponent.h"
#include "LesFight.h"
#include "GameFramework/Character.h"

ULesFightCharacterMovementComponent::ULesFightCharacterMovementComponent()
    : WalkSpeed(150.0f)
    , RunSpeed(350.0f)
    , SprintSpeed(600.0f)
    , CrouchSpeed(100.0f)
    , AirSpeedMultiplier(0.8f)
    , RotationRateMultiplier(1.0f)
    , SprintStaminaCostPerSecond(10.0f)
    , SprintAcceleration(2048.0f)
    , LandingHardVelocityThreshold(800.0f)
    , LandingHardTime(0.5f)
    , LandingSoftTime(0.2f)
    , bWantsToSprint(false)
    , bWantsToCrouch(false)
    , bIsSprinting(false)
    , CurrentMovementState(EMovementState::Idle)
    , PreviousMovementState(EMovementState::Idle)
    , CurrentInputMagnitude(0.0f)
    , SpeedMultiplier(1.0f)
{
    RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    MaxAcceleration = 2048.0f;
    BrakingDecelerationWalking = 2048.0f;
    GroundFriction = 8.0f;
    AirControl = 0.8f;
    bOrientRotationToMovement = true;
    NavAgentProps.bCanCrouch = true;
}

float ULesFightCharacterMovementComponent::GetMaxSpeed() const
{
    float BaseSpeed = 0.0f;
    const ACharacter* CharOwner = CharacterOwner;

    if (IsCrouching())
    {
        BaseSpeed = CrouchSpeed;
    }
    else if (bIsSprinting && !CharOwner->GetVelocity().IsZero())
    {
        BaseSpeed = SprintSpeed;
    }
    else if (CurrentInputMagnitude > 0.5f)
    {
        BaseSpeed = RunSpeed;
    }
    else if (CurrentInputMagnitude > 0.0f)
    {
        BaseSpeed = WalkSpeed;
    }
    else
    {
        BaseSpeed = RunSpeed;
    }

    if (!IsMovingOnGround())
    {
        BaseSpeed *= AirSpeedMultiplier;
    }

    return BaseSpeed * SpeedMultiplier;
}

void ULesFightCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!HasValidData()) return;

    UpdateMovementState();
    HandleSprint(DeltaTime);
    HandleLanding();
}

void ULesFightCharacterMovementComponent::OnMovementUpdated(float DeltaTime, const FVector& OldLocation,
    const FVector& OldVelocity)
{
    Super::OnMovementUpdated(DeltaTime, OldLocation, OldVelocity);
    HandleCrouch();
}

void ULesFightCharacterMovementComponent::ResetMovementState()
{
    bWantsToSprint = false;
    bWantsToCrouch = false;
    bIsSprinting = false;
    CurrentMovementState = EMovementState::Idle;
    SpeedMultiplier = 1.0f;
}

void ULesFightCharacterMovementComponent::UpdateMovementState()
{
    PreviousMovementState = CurrentMovementState;
    EMovementState NewState = CurrentMovementState;

    const FVector Velocity = GetLastUpdateVelocity();
    CurrentInputMagnitude = Velocity.Size2D();

    if (!IsMovingOnGround())
    {
        NewState = (Velocity.Z > 0.0f) ? EMovementState::Jumping : EMovementState::Falling;
    }
    else if (IsCrouching())
    {
        NewState = EMovementState::Crouching;
    }
    else if (bIsSprinting)
    {
        NewState = EMovementState::Sprinting;
    }
    else if (CurrentInputMagnitude > 0.5f)
    {
        NewState = EMovementState::Running;
    }
    else if (CurrentInputMagnitude > 0.0f)
    {
        NewState = EMovementState::Walking;
    }
    else
    {
        NewState = EMovementState::Idle;
    }

    if (NewState != CurrentMovementState)
    {
        BroadcastStateChange(NewState);
        CurrentMovementState = NewState;
    }
}

void ULesFightCharacterMovementComponent::HandleSprint(float DeltaTime)
{
    if (!CharacterOwner) return;

    if (bWantsToSprint && !IsCrouching() && IsMovingOnGround() && CurrentInputMagnitude > 0.0f)
    {
        bIsSprinting = true;
        MaxAcceleration = SprintAcceleration;
    }
    else
    {
        bIsSprinting = false;
        MaxAcceleration = 2048.0f;
    }
}

void ULesFightCharacterMovementComponent::HandleCrouch()
{
    if (!CharacterOwner) return;

    if (bWantsToCrouch && IsMovingOnGround() && !IsCrouching())
    {
        CharacterOwner->Crouch();
    }
    else if (!bWantsToCrouch && IsCrouching())
    {
        CharacterOwner->UnCrouch();
    }
}

void ULesFightCharacterMovementComponent::HandleLanding()
{
    if (PreviousMovementState == EMovementState::Falling || PreviousMovementState == EMovementState::Jumping)
    {
        if (IsMovingOnGround() && CurrentMovementState != EMovementState::Falling)
        {
            float FallSpeed = FMath::Abs(GetLastUpdateVelocity().Z);
            float LandTime = (FallSpeed > LandingHardVelocityThreshold) ? LandingHardTime : LandingSoftTime;
        }
    }
}

void ULesFightCharacterMovementComponent::BroadcastStateChange(EMovementState NewState)
{
    OnMovementStateChanged.Broadcast(NewState);
}
