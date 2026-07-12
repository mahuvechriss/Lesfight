#include "LesFightAnimInstance.h"
#include "LesFightBaseFighter.h"
#include "LesFightCharacterMovementComponent.h"
#include "LesFight.h"
#include "GameFramework/CharacterMovementComponent.h"

ULesFightAnimInstance::ULesFightAnimInstance()
    : LocomotionSpeed(0.0f)
    , LocomotionDirection(0.0f)
    , CharacterYaw(0.0f)
    , CharacterPitch(0.0f)
    , bIsInAir(false)
    , bIsCrouching(false)
    , bIsSprinting(false)
    , CurrentLocomotionState(ELocomotionState::Idle)
    , OwnerFighter(nullptr)
{
}

void ULesFightAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    OwnerFighter = Cast<ALesFightBaseFighter>(TryGetPawnOwner());
}

void ULesFightAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    UpdateCharacterReferences();
    if (!OwnerFighter) return;

    const FVector Velocity = OwnerFighter->GetVelocity();
    LocomotionSpeed = Velocity.Size2D();
    LocomotionDirection = CalculateDirection(Velocity, OwnerFighter->GetActorRotation());
    bIsInAir = OwnerFighter->GetCharacterMovement()->IsFalling();
    bIsCrouching = OwnerFighter->GetCharacterMovement()->IsCrouching();

    ULesFightCharacterMovementComponent* MovComp = OwnerFighter->GetLesFightMovement();
    bIsSprinting = MovComp ? MovComp->IsSprinting() : false;

    UpdateLocomotionState();
}

void ULesFightAnimInstance::SetBlendSpaceParameter(const FName& ParameterName, float Value)
{
    BlendSpaceParameters.Add(ParameterName, Value);
}

void ULesFightAnimInstance::TriggerPunch()
{
    // Placeholder for combat module
}

void ULesFightAnimInstance::TriggerKick()
{
    // Placeholder for combat module
}

void ULesFightAnimInstance::TriggerBlock()
{
    // Placeholder for combat module
}

void ULesFightAnimInstance::TriggerHitReaction()
{
    // Placeholder for combat module
}

void ULesFightAnimInstance::TriggerVictory()
{
    // Placeholder for combat module
}

void ULesFightAnimInstance::TriggerDefeat()
{
    // Placeholder for combat module
}

void ULesFightAnimInstance::UpdateLocomotionState()
{
    if (bIsInAir)
    {
        CurrentLocomotionState = OwnerFighter->GetVelocity().Z > 0.0f
            ? ELocomotionState::Jumping : ELocomotionState::Falling;
    }
    else if (bIsCrouching)
    {
        CurrentLocomotionState = ELocomotionState::Crouching;
    }
    else if (bIsSprinting)
    {
        CurrentLocomotionState = ELocomotionState::Sprinting;
    }
    else if (LocomotionSpeed > 300.0f)
    {
        CurrentLocomotionState = ELocomotionState::Running;
    }
    else if (LocomotionSpeed > 10.0f)
    {
        CurrentLocomotionState = ELocomotionState::Walking;
    }
    else
    {
        CurrentLocomotionState = ELocomotionState::Idle;
    }
}

void ULesFightAnimInstance::UpdateCharacterReferences()
{
    if (!OwnerFighter)
    {
        OwnerFighter = Cast<ALesFightBaseFighter>(TryGetPawnOwner());
    }
}
