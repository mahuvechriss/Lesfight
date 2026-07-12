#include "LesFightIKSystem.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"
#include "DrawDebugHelpers.h"

ULesFightIKSystem::ULesFightIKSystem()
    : IKBlendSpeed(8.0f)
    , IKTraceDistance(50.0f)
    , FootRaiseDistance(20.0f)
    , PelvisOffset(0.0f)
    , IKQuality(EAnimationQuality::High)
    , CurrentIKAlpha(1.0f)
    , bFootIKEnabled(true)
    , bHandIKEnabled(false)
    , bGroundAdaptationEnabled(true)
{
    FIKFootData LeftFoot;
    LeftFoot.FootBoneName = FName(TEXT("foot_l"));
    LeftFoot.EffectorBoneName = FName(TEXT("ik_foot_l"));
    LeftFoot.HipBoneName = FName(TEXT("pelvis"));
    FootIKData.Add(LeftFoot);

    FIKFootData RightFoot;
    RightFoot.FootBoneName = FName(TEXT("foot_r"));
    RightFoot.EffectorBoneName = FName(TEXT("ik_foot_r"));
    RightFoot.HipBoneName = FName(TEXT("pelvis"));
    FootIKData.Add(RightFoot);
}

void ULesFightIKSystem::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        MeshComponent = AnimComponent->GetMesh();
    }

    if (AnimData)
    {
        for (const FIKChainSetup& Chain : AnimData->IKChains)
        {
            if (Chain.IKType == EIKType::FootIK)
            {
                FIKFootData Foot;
                Foot.FootBoneName = Chain.ChainEndBone;
                Foot.EffectorBoneName = Chain.ChainEndBone;
                Foot.TraceDistance = Chain.TraceDistance;
                Foot.InterpSpeed = Chain.IKBlendSpeed;
                Foot.IKAlpha = Chain.IKAlpha;
                FootIKData.Add(Foot);
            }
        }
    }
}

void ULesFightIKSystem::Update(float DeltaTime)
{
    if (!bFootIKEnabled && !bHandIKEnabled && !bGroundAdaptationEnabled) return;

    if (bFootIKEnabled)
    {
        UpdateFootIK(DeltaTime);
    }

    if (bHandIKEnabled)
    {
        UpdateHandIK(DeltaTime);
    }

    if (bGroundAdaptationEnabled)
    {
        UpdateGroundAdaptation(DeltaTime);
    }
}

void ULesFightIKSystem::SetIKQuality(EAnimationQuality Quality)
{
    IKQuality = Quality;
    switch (Quality)
    {
    case EAnimationQuality::Low:
        IKBlendSpeed = 15.0f;
        IKTraceDistance = 30.0f;
        bFootIKEnabled = false;
        bHandIKEnabled = false;
        break;
    case EAnimationQuality::Medium:
        IKBlendSpeed = 10.0f;
        IKTraceDistance = 40.0f;
        bFootIKEnabled = true;
        bHandIKEnabled = false;
        break;
    case EAnimationQuality::High:
    case EAnimationQuality::Epic:
    case EAnimationQuality::Cinematic:
        IKBlendSpeed = 8.0f;
        IKTraceDistance = 50.0f;
        bFootIKEnabled = true;
        bHandIKEnabled = true;
        break;
    }
}

void ULesFightIKSystem::SetFootLocking(bool bEnable)
{
    for (FIKFootData& Foot : FootIKData)
    {
        Foot.bEnableLock = bEnable;
    }
}

void ULesFightIKSystem::SetIKAlpha(float Alpha)
{
    CurrentIKAlpha = FMath::Clamp(Alpha, 0.0f, 1.0f);
}

void ULesFightIKSystem::OverrideFootIK(FName FootBone, FVector Location, FRotator Rotation)
{
    for (FIKFootData& Foot : FootIKData)
    {
        if (Foot.FootBoneName == FootBone)
        {
            Foot.IKLocation = Location;
            Foot.IKRotation = Rotation;
            Foot.IKAlpha = 1.0f;
            break;
        }
    }
}

void ULesFightIKSystem::OverrideHandIK(FName HandBone, FVector Location, FRotator Rotation)
{
    for (FIKHandData& Hand : HandIKData)
    {
        if (Hand.HandBoneName == HandBone)
        {
            Hand.IKLocation = Location;
            Hand.IKRotation = Rotation;
            Hand.IKAlpha = 1.0f;
            break;
        }
    }
}

void ULesFightIKSystem::ResetIK()
{
    for (FIKFootData& Foot : FootIKData)
    {
        Foot.IKLocation = FVector::ZeroVector;
        Foot.IKRotation = FRotator::ZeroRotator;
        Foot.IKAlpha = 0.0f;
        Foot.bLocked = false;
    }
    for (FIKHandData& Hand : HandIKData)
    {
        Hand.IKLocation = FVector::ZeroVector;
        Hand.IKRotation = FRotator::ZeroRotator;
        Hand.IKAlpha = 0.0f;
    }
}

void ULesFightIKSystem::UpdateFootIK(float DeltaTime)
{
    if (!MeshComponent.IsValid()) return;

    for (FIKFootData& Foot : FootIKData)
    {
        FVector FootLocation = MeshComponent->GetSocketLocation(Foot.FootBoneName);
        FVector TraceStart = FootLocation + FVector(0.0f, 0.0f, FootRaiseDistance);
        FVector TraceEnd = FootLocation - FVector(0.0f, 0.0f, IKTraceDistance);

        FHitResult Hit = LineTraceSingle(TraceStart, TraceEnd);

        float TargetAlpha = CurrentIKAlpha;
        if (Hit.bBlockingHit)
        {
            FVector GroundLocation = Hit.Location;
            GroundLocation.Z += Foot.FootOffset;

            Foot.IKLocation = FMath::VInterpTo(Foot.IKLocation, GroundLocation,
                DeltaTime, Foot.InterpSpeed);

            FRotator TargetRot = FRotator(
                FMath::RadiansToDegrees(FMath::Atan2(Hit.Normal.Y, Hit.Normal.Z)),
                0.0f,
                -FMath::RadiansToDegrees(FMath::Atan2(Hit.Normal.X, Hit.Normal.Z)));
            Foot.IKRotation = FMath::RInterpTo(Foot.IKRotation, TargetRot,
                DeltaTime, Foot.InterpSpeed);
        }

        Foot.IKAlpha = FMath::FInterpTo(Foot.IKAlpha, TargetAlpha, DeltaTime, Foot.InterpSpeed);

        UpdateFootLocking(DeltaTime);
    }

    ApplyPelvisOffset(DeltaTime);
}

void ULesFightIKSystem::UpdateHandIK(float DeltaTime)
{
    for (FIKHandData& Hand : HandIKData)
    {
        Hand.IKAlpha = FMath::FInterpTo(Hand.IKAlpha, 0.0f, DeltaTime, IKBlendSpeed);
    }
}

void ULesFightIKSystem::UpdateGroundAdaptation(float DeltaTime)
{
}

void ULesFightIKSystem::UpdateFootLocking(float DeltaTime)
{
    for (FIKFootData& Foot : FootIKData)
    {
        if (!Foot.bEnableLock) continue;
    }
}

FVector ULesFightIKSystem::TraceGround(FName BoneName, float TraceDist) const
{
    if (!MeshComponent.IsValid()) return FVector::ZeroVector;
    FVector BoneLoc = MeshComponent->GetSocketLocation(BoneName);
    FVector Start = BoneLoc + FVector(0, 0, TraceDist * 0.5f);
    FVector End = BoneLoc - FVector(0, 0, TraceDist);
    FHitResult Hit = LineTraceSingle(Start, End);
    return Hit.bBlockingHit ? Hit.Location : BoneLoc;
}

FHitResult ULesFightIKSystem::LineTraceSingle(const FVector& Start, const FVector& End) const
{
    FHitResult Hit;
    if (!AnimComponent.IsValid()) return Hit;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(AnimComponent->GetOwner());

    AnimComponent->GetOwner()->GetWorld()->LineTraceSingleByChannel(
        Hit, Start, End, ECC_WorldStatic, QueryParams);

    return Hit;
}

void ULesFightIKSystem::ApplyPelvisOffset(float DeltaTime)
{
    if (FootIKData.Num() < 2) return;

    float LeftZ = FootIKData[0].IKLocation.Z;
    float RightZ = FootIKData[1].IKLocation.Z;
    float TargetOffset = FMath::Min(LeftZ, RightZ);

    PelvisOffset = FMath::FInterpTo(PelvisOffset, TargetOffset, DeltaTime, IKBlendSpeed);
}
