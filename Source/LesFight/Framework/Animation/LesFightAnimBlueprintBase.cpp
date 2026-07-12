#include "LesFightAnimBlueprintBase.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightAnimBlueprintBase::ULesFightAnimBlueprintBase()
    : OwnerFighter(nullptr)
    , AnimComponent(nullptr)
    , CurrentLocomotionState(ELocomotionState::None)
    , CurrentCombatAnimType(ECombatAnimType::None)
    , CurrentHitReactionAnim(EHitReactionAnimType::None)
    , CurrentFacialExpression(EFacialExpression::Neutral)
    , Speed(0.0f), Direction(0.0f), Acceleration(0.0f)
    , bIsInAir(false), bIsCrouching(false)
    , bIsBlocking(false), bIsAttacking(false)
    , bIsHitReacting(false)
    , PlayRate(1.0f)
    , AnimQuality(EAnimationQuality::High)
{
}

void ULesFightAnimBlueprintBase::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    AActor* Owner = GetOwningActor();
    if (Owner)
    {
        OwnerFighter = Cast<ALesFightBaseFighter>(Owner);
        if (OwnerFighter)
        {
            AnimComponent = OwnerFighter->FindComponentByClass<ULesFightCharacterAnimationComponent>();
        }
    }
}

void ULesFightAnimBlueprintBase::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!OwnerFighter) return;

    FVector Velocity = OwnerFighter->GetVelocity();
    Speed = Velocity.Size2D();
    Direction = CalculateDirection(Velocity, OwnerFighter->GetActorRotation());
    Acceleration = OwnerFighter->GetCharacterMovement()
        ? OwnerFighter->GetCharacterMovement()->GetCurrentAcceleration().Size2D() : 0.0f;
    bIsInAir = OwnerFighter->GetCharacterMovement()
        ? OwnerFighter->GetCharacterMovement()->IsFalling() : false;
    bIsCrouching = OwnerFighter->bIsCrouched;
}

void ULesFightAnimBlueprintBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void ULesFightAnimBlueprintBase::NativePostEvaluateAnimation()
{
    Super::NativePostEvaluateAnimation();
}

void ULesFightAnimBlueprintBase::NativeUninitializeAnimation()
{
    Super::NativeUninitializeAnimation();
}

void ULesFightAnimBlueprintBase::InitializeWithCharacter(ALesFightBaseFighter* InFighter)
{
    OwnerFighter = InFighter;
    if (OwnerFighter)
    {
        AnimComponent = OwnerFighter->FindComponentByClass<ULesFightCharacterAnimationComponent>();
    }
}

void ULesFightAnimBlueprintBase::SetLocomotionState(ELocomotionState NewState)
{
    CurrentLocomotionState = NewState;
}

void ULesFightAnimBlueprintBase::SetCombatAnimType(ECombatAnimType NewType)
{
    CurrentCombatAnimType = NewType;
}

void ULesFightAnimBlueprintBase::SetHitReactionAnim(EHitReactionAnimType NewReaction)
{
    CurrentHitReactionAnim = NewReaction;
    bIsHitReacting = NewReaction != EHitReactionAnimType::None;
}

void ULesFightAnimBlueprintBase::PlayMontageFromData(const FAnimationMontageData& MontageData)
{
    if (!MontageData.Montage) return;

    if (MontageData.bEnableRootMotion)
    {
        EnableRootMotion(true);
    }

    PlaySlotAnimationAsDynamicMontage(MontageData.Montage, MontageData.SectionName,
        0.2f, 0.2f, MontageData.PlayRate, 1, 0.0f, MontageData.StartPosition);

    if (MontageData.bUseMotionWarping)
    {
        for (const FMotionWarpTargetData& WarpTarget : MontageData.WarpTargets)
        {
            if (AnimComponent)
            {
                AnimComponent->SetMotionWarpTarget(WarpTarget);
            }
        }
    }
}

void ULesFightAnimBlueprintBase::StopAllMontages(float BlendOut)
{
    Montage_Stop(BlendOut);
}

void ULesFightAnimBlueprintBase::SetBlendValues(float InSpeed, float InDirection,
    float InAcceleration)
{
    Speed = InSpeed;
    Direction = InDirection;
    Acceleration = InAcceleration;
}

void ULesFightAnimBlueprintBase::TriggerAdditiveAnimation(FName SlotName,
    UAnimSequence* AdditiveAnim, float BlendIn)
{
    if (!AdditiveAnim) return;
    PlaySlotAnimationAsDynamicMontage(AdditiveAnim, SlotName, BlendIn, 0.2f, 1.0f, 1, 0.0f, 0.0f);
}

void ULesFightAnimBlueprintBase::SetFacialExpression(EFacialExpression Expression,
    float BlendTime)
{
    CurrentFacialExpression = Expression;
}

void ULesFightAnimBlueprintBase::EnableRootMotion(bool bEnable)
{
    if (OwnerFighter)
    {
        OwnerFighter->GetMesh()->SetEnableBodyGravity(bEnable);
    }
}

void ULesFightAnimBlueprintBase::SetAnimationQuality(EAnimationQuality Quality)
{
    AnimQuality = Quality;
}

bool ULesFightAnimBlueprintBase::IsPlayingMontage() const
{
    return Montage_IsPlaying(nullptr);
}
