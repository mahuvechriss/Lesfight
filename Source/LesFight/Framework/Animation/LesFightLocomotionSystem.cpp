#include "LesFightLocomotionSystem.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFightAnimationDataAsset.h"
#include "LesFight.h"

ULesFightLocomotionSystem::ULesFightLocomotionSystem()
    : CurrentState(ELocomotionState::Idle)
    , PreviousState(ELocomotionState::None)
    , CurrentSpeed(0.0f), CurrentDirection(0.0f)
    , CurrentAcceleration(0.0f)
    , SpeedBlendValue(0.0f), DirectionBlendValue(0.0f)
    , IdleTimer(0.0f)
    , bIsMoving(false)
    , IdleVariationInterval(5.0f)
    , TurnThreshold(90.0f)
    , MoveStartThreshold(10.0f)
    , SpeedSmoothRate(8.0f)
    , DirectionSmoothRate(6.0f)
    , SmoothedSpeed(0.0f), SmoothedDirection(0.0f)
    , TurnYawDelta(0.0f), LastYaw(0.0f)
    , CurrentIdleVariation(0)
{
}

void ULesFightLocomotionSystem::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;
    AnimationData = AnimData;
    if (AnimComponent.IsValid())
    {
        AnimBP = AnimComponent->GetAnimBlueprintInstance();
    }
    if (AnimData)
    {
        CurrentAnimSet = AnimData->LocomotionSet;
    }
}

void ULesFightLocomotionSystem::Update(float DeltaTime)
{
    if (!AnimComponent.IsValid()) return;

    UpdateBlendValues(DeltaTime);
    CheckTurnInPlace(DeltaTime);

    switch (CurrentState)
    {
    case ELocomotionState::Idle:
        UpdateIdle(DeltaTime);
        break;
    case ELocomotionState::Walk:
    case ELocomotionState::Jog:
    case ELocomotionState::Sprint:
    case ELocomotionState::CrouchWalk:
        UpdateMoving(DeltaTime);
        break;
    case ELocomotionState::Falling:
    case ELocomotionState::JumpStart:
    case ELocomotionState::JumpLoop:
    case ELocomotionState::JumpLand:
        UpdateInAir(DeltaTime);
        break;
    default:
        break;
    }

    if (AnimBP.IsValid())
    {
        AnimBP->SetBlendValues(SmoothedSpeed, SmoothedDirection, CurrentAcceleration);
    }
}

void ULesFightLocomotionSystem::SetMovementValues(float Speed, float Direction,
    float Acceleration)
{
    CurrentSpeed = Speed;
    CurrentDirection = Direction;
    CurrentAcceleration = Acceleration;
    bIsMoving = Speed > MoveStartThreshold;
}

void ULesFightLocomotionSystem::SetLocomotionState(ELocomotionState State)
{
    if (CurrentState != State)
    {
        PreviousState = CurrentState;
        CurrentState = State;

        if (State == ELocomotionState::Idle)
        {
            IdleTimer = 0.0f;
        }

        if (AnimBP.IsValid())
        {
            AnimBP->SetLocomotionState(State);
        }
    }
}

void ULesFightLocomotionSystem::SetAnimationSet(const FLocomotionAnimSet& AnimSet)
{
    CurrentAnimSet = AnimSet;
}

void ULesFightLocomotionSystem::ResetLocomotion()
{
    CurrentState = ELocomotionState::Idle;
    SmoothedSpeed = 0.0f;
    SmoothedDirection = 0.0f;
    SpeedBlendValue = 0.0f;
    DirectionBlendValue = 0.0f;
    bIsMoving = false;
}

void ULesFightLocomotionSystem::UpdateIdle(float DeltaTime)
{
    IdleTimer += DeltaTime;

    if (bIdleVariationsEnabled && IdleTimer >= IdleVariationInterval)
    {
        PlayIdleVariation();
        IdleTimer = 0.0f;
    }
}

void ULesFightLocomotionSystem::UpdateMoving(float DeltaTime)
{
    IdleTimer = 0.0f;
}

void ULesFightLocomotionSystem::UpdateInAir(float DeltaTime)
{
    IdleTimer = 0.0f;
}

void ULesFightLocomotionSystem::UpdateTransitionStates(float DeltaTime)
{
}

void ULesFightLocomotionSystem::CheckTurnInPlace(float DeltaTime)
{
    if (!AnimComponent.IsValid()) return;

    FRotator ActorRot = AnimComponent->GetOwner()->GetActorRotation();
    float YawChange = FMath::FindDeltaAngleDegrees(LastYaw, ActorRot.Yaw);
    TurnYawDelta = FMath::FInterpTo(TurnYawDelta, YawChange, DeltaTime, 5.0f);
    LastYaw = ActorRot.Yaw;

    if (!bIsMoving && FMath::Abs(YawChange) > TurnThreshold && bTurnInPlaceEnabled)
    {
        SetLocomotionState(YawChange > 0.0f
            ? ELocomotionState::TurnRight : ELocomotionState::TurnLeft);
    }
}

void ULesFightLocomotionSystem::UpdateBlendValues(float DeltaTime)
{
    SmoothedSpeed = FMath::FInterpTo(SmoothedSpeed, CurrentSpeed, DeltaTime, SpeedSmoothRate);
    SmoothedDirection = FMath::FInterpTo(SmoothedDirection, CurrentDirection, DeltaTime,
        DirectionSmoothRate);

    SpeedBlendValue = FMath::Clamp(SmoothedSpeed / 600.0f, 0.0f, 1.0f);
    DirectionBlendValue = FMath::Clamp((SmoothedDirection + 180.0f) / 360.0f, 0.0f, 1.0f);
}

void ULesFightLocomotionSystem::PlayIdleVariation()
{
    if (CurrentAnimSet.IdleVariations.Num() == 0) return;

    CurrentIdleVariation = (CurrentIdleVariation + 1) % CurrentAnimSet.IdleVariations.Num();
    UAnimSequence* Variation = CurrentAnimSet.IdleVariations[CurrentIdleVariation];
    if (Variation && AnimBP.IsValid())
    {
        AnimBP->TriggerAdditiveAnimation(FName(TEXT("IdleVariation")), Variation, 0.3f);
    }
}
