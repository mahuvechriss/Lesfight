#include "LesFightFacialAnimationSystem.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFightAnimationDataAsset.h"
#include "LesFight.h"

ULesFightFacialAnimationSystem::ULesFightFacialAnimationSystem()
    : CurrentExpression(EFacialExpression::Neutral)
    , TargetExpression(EFacialExpression::Neutral)
    , ExpressionBlendTime(0.3f)
    , ExpressionBlendProgress(1.0f)
    , BlinkAlpha(0.0f)
    , EyeTarget(FVector::ZeroVector)
    , LipSyncAlpha(0.0f)
    , BlinkSpeed(15.0f)
    , EyeTrackingSpeed(5.0f)
    , LipSyncSpeed(10.0f)
    , bBlinkEnabled(true)
    , bEyeTrackingEnabled(true)
    , bLipSyncEnabled(true)
    , BlinkTimer(0.0f)
    , BlinkIntervalMin(2.0f)
    , BlinkIntervalMax(6.0f)
    , NextBlinkTime(3.0f)
    , bBlinking(false)
    , LipSyncTimer(0.0f)
{
}

void ULesFightFacialAnimationSystem::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AnimBP = AnimComponent->GetAnimBlueprintInstance();
    }

    if (AnimData)
    {
        ExpressionAnimations = AnimData->FacialAnimations;
    }
}

void ULesFightFacialAnimationSystem::Update(float DeltaTime)
{
    if (bBlinkEnabled) UpdateBlinking(DeltaTime);
    if (bEyeTrackingEnabled) UpdateEyeTracking(DeltaTime);
    if (bLipSyncEnabled) UpdateLipSync(DeltaTime);

    UpdateExpressionBlend(DeltaTime);
}

void ULesFightFacialAnimationSystem::SetExpression(EFacialExpression Expression,
    float BlendTime)
{
    if (Expression != CurrentExpression)
    {
        TargetExpression = Expression;
        ExpressionBlendTime = BlendTime;
        ExpressionBlendProgress = 0.0f;
    }
}

void ULesFightFacialAnimationSystem::SetBlinkInterval(float Min, float Max)
{
    BlinkIntervalMin = Min;
    BlinkIntervalMax = Max;
}

void ULesFightFacialAnimationSystem::SetEyeTarget(FVector TargetLocation)
{
    EyeTarget = TargetLocation;
}

void ULesFightFacialAnimationSystem::TriggerLipSync(float Duration)
{
    LipSyncAlpha = 1.0f;
    LipSyncTimer = Duration;
}

void ULesFightFacialAnimationSystem::ResetFacial()
{
    CurrentExpression = EFacialExpression::Neutral;
    TargetExpression = EFacialExpression::Neutral;
    BlinkAlpha = 0.0f;
    LipSyncAlpha = 0.0f;
}

void ULesFightFacialAnimationSystem::UpdateBlinking(float DeltaTime)
{
    BlinkTimer += DeltaTime;

    if (!bBlinking && BlinkTimer >= NextBlinkTime)
    {
        bBlinking = true;
        BlinkTimer = 0.0f;
    }

    if (bBlinking)
    {
        BlinkAlpha = FMath::FInterpTo(BlinkAlpha, 1.0f, DeltaTime, BlinkSpeed);
        if (BlinkAlpha >= 0.95f)
        {
            bBlinking = false;
            NextBlinkTime = FMath::FRandRange(BlinkIntervalMin, BlinkIntervalMax);
        }
    }
    else
    {
        BlinkAlpha = FMath::FInterpTo(BlinkAlpha, 0.0f, DeltaTime, BlinkSpeed);
    }
}

void ULesFightFacialAnimationSystem::UpdateEyeTracking(float DeltaTime)
{
    if (!AnimComponent.IsValid()) return;

    APlayerController* PC = Cast<APlayerController>(
        AnimComponent->GetOwner()->GetInstigatorController());
    if (PC && PC->GetPawn())
    {
        AActor* TargetActor = Cast<AActor>(PC->GetPawn());
        if (TargetActor)
        {
            FVector TargetLoc = TargetActor->GetActorLocation();
            EyeTarget = FMath::VInterpTo(EyeTarget, TargetLoc, DeltaTime, EyeTrackingSpeed);
        }
    }
}

void ULesFightFacialAnimationSystem::UpdateLipSync(float DeltaTime)
{
    if (LipSyncAlpha > 0.0f)
    {
        LipSyncTimer -= DeltaTime;
        if (LipSyncTimer <= 0.0f)
        {
            LipSyncAlpha = FMath::FInterpTo(LipSyncAlpha, 0.0f, DeltaTime, LipSyncSpeed);
        }
    }
}

void ULesFightFacialAnimationSystem::UpdateExpressionBlend(float DeltaTime)
{
    if (ExpressionBlendProgress < 1.0f)
    {
        ExpressionBlendProgress = FMath::Clamp(
            ExpressionBlendProgress + (DeltaTime / FMath::Max(ExpressionBlendTime, 0.01f)),
            0.0f, 1.0f);

        if (ExpressionBlendProgress >= 1.0f)
        {
            CurrentExpression = TargetExpression;
        }
    }
}
