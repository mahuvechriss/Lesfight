#include "LesFightMotionWarpingSystem.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"

ULesFightMotionWarpingSystem::ULesFightMotionWarpingSystem()
    : WarpSpeed(5.0f)
    , MaxWarpDistance(200.0f)
    , MaxWarpAngle(90.0f)
    , bWarpEnabled(true)
{
}

void ULesFightMotionWarpingSystem::Initialize(ULesFightCharacterAnimationComponent* InComponent)
{
    AnimComponent = InComponent;
}

void ULesFightMotionWarpingSystem::Update(float DeltaTime)
{
    if (!bWarpEnabled) return;

    for (int32 i = ActiveWarps.Num() - 1; i >= 0; i--)
    {
        FWarpRequest& Warp = ActiveWarps[i];

        if (Warp.bComplete) continue;

        Warp.WarpProgress = FMath::Clamp(Warp.WarpProgress + WarpSpeed * DeltaTime, 0.0f, 1.0f);

        ApplyWarp(Warp);

        if (Warp.WarpProgress >= 1.0f)
        {
            Warp.bComplete = true;
        }
    }

    ActiveWarps.RemoveAll([](const FWarpRequest& W) { return W.bComplete; });
}

void ULesFightMotionWarpingSystem::SetWarpTarget(const FMotionWarpTargetData& Target)
{
    if (!bWarpEnabled) return;

    for (FWarpRequest& Warp : ActiveWarps)
    {
        if (Warp.TargetData.TargetName == Target.TargetName)
        {
            Warp.TargetData = Target;
            return;
        }
    }

    FWarpRequest Request;
    Request.TargetData = Target;
    Request.bActive = true;
    ActiveWarps.Add(Request);
}

void ULesFightMotionWarpingSystem::ClearWarpTarget(FName TargetName)
{
    ActiveWarps.RemoveAll([TargetName](const FWarpRequest& W) {
        return W.TargetData.TargetName == TargetName;
    });
}

void ULesFightMotionWarpingSystem::ClearAllWarpTargets()
{
    ActiveWarps.Empty();
}

void ULesFightMotionWarpingSystem::WarpToTarget(const FMotionWarpTargetData& Target,
    float Duration)
{
    if (!bWarpEnabled) return;

    FWarpRequest Request;
    Request.TargetData = Target;
    Request.WarpStartTime = 0.0f;
    Request.WarpEndTime = Duration;
    Request.bActive = true;
    ActiveWarps.Add(Request);
}

void ULesFightMotionWarpingSystem::CancelActiveWarp()
{
    ActiveWarps.Empty();
}

bool ULesFightMotionWarpingSystem::IsWarping() const
{
    return ActiveWarps.Num() > 0;
}

bool ULesFightMotionWarpingSystem::HasWarpTarget(FName TargetName) const
{
    for (const FWarpRequest& Warp : ActiveWarps)
    {
        if (Warp.TargetData.TargetName == TargetName) return true;
    }
    return false;
}

FVector ULesFightMotionWarpingSystem::GetWarpTargetLocation(FName TargetName) const
{
    for (const FWarpRequest& Warp : ActiveWarps)
    {
        if (Warp.TargetData.TargetName == TargetName)
        {
            return Warp.TargetData.TargetLocation;
        }
    }
    return FVector::ZeroVector;
}

void ULesFightMotionWarpingSystem::ApplyWarp(FWarpRequest& Warp)
{
    if (!AnimComponent.IsValid()) return;

    AActor* Owner = AnimComponent->GetOwner();
    if (!Owner) return;

    FVector TargetLocation = CalculateWarpPosition(Warp);
    FRotator TargetRotation = CalculateWarpRotation(Warp);

    if (Warp.TargetData.bWarpPosition)
    {
        FVector CurrentLoc = Owner->GetActorLocation();
        FVector WarpedLoc = FMath::Lerp(CurrentLoc, TargetLocation, Warp.WarpProgress);
        Owner->SetActorLocation(WarpedLoc);
    }

    if (Warp.TargetData.bWarpRotation)
    {
        FRotator CurrentRot = Owner->GetActorRotation();
        FRotator WarpedRot = FMath::Lerp(CurrentRot, TargetRotation, Warp.WarpProgress);
        Owner->SetActorRotation(WarpedRot);
    }
}

FVector ULesFightMotionWarpingSystem::CalculateWarpPosition(const FWarpRequest& Warp) const
{
    switch (Warp.TargetData.TargetType)
    {
    case EMotionWarpTarget::TargetActor:
        if (Warp.TargetData.TargetActor.IsValid())
        {
            return Warp.TargetData.TargetActor->GetActorLocation();
        }
        break;
    case EMotionWarpTarget::TargetLocation:
        return Warp.TargetData.TargetLocation;
    default:
        break;
    }
    return AnimComponent.IsValid() ? AnimComponent->GetOwner()->GetActorLocation() : FVector::ZeroVector;
}

FRotator ULesFightMotionWarpingSystem::CalculateWarpRotation(const FWarpRequest& Warp) const
{
    switch (Warp.TargetData.TargetType)
    {
    case EMotionWarpTarget::TargetActor:
        if (Warp.TargetData.TargetActor.IsValid() && AnimComponent.IsValid())
        {
            FVector Dir = Warp.TargetData.TargetActor->GetActorLocation()
                - AnimComponent->GetOwner()->GetActorLocation();
            return Dir.Rotation();
        }
        break;
    case EMotionWarpTarget::TargetLocation:
    {
        FVector Dir = Warp.TargetData.TargetLocation
            - AnimComponent->GetOwner()->GetActorLocation();
        return Dir.Rotation();
    }
    default:
        break;
    }
    return AnimComponent.IsValid() ? AnimComponent->GetOwner()->GetActorRotation() : FRotator::ZeroRotator;
}
