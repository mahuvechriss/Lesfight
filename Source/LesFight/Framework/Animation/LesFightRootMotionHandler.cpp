#include "LesFightRootMotionHandler.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"
#include "GameFramework/CharacterMovementComponent.h"

ULesFightRootMotionHandler::ULesFightRootMotionHandler()
    : bRootMotionEnabled(true)
    , AccumulatedTranslation(FVector::ZeroVector)
    , AccumulatedRotation(FRotator::ZeroRotator)
{
}

void ULesFightRootMotionHandler::Initialize(ULesFightCharacterAnimationComponent* InComponent)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AActor* Owner = AnimComponent->GetOwner();
        if (Owner)
        {
            MovementComponent = Owner->FindComponentByClass<UCharacterMovementComponent>();
        }
    }
}

void ULesFightRootMotionHandler::Update(float DeltaTime)
{
    if (!bRootMotionEnabled || !AnimComponent.IsValid()) return;

    USkeletalMeshComponent* Mesh = AnimComponent->GetMesh();
    if (!Mesh) return;

    if (MovementComponent.IsValid() && Mesh->GetAttachedRootMotion())
    {
        FTransform RootMotion = Mesh->ConsumeRootMotion();
        FVector Translation = RootMotion.GetTranslation() * CurrentParams.TranslationMultiplier;
        FRotator Rotation = RootMotion.GetRotation().Rotator() * CurrentParams.RotationMultiplier;

        if (!CurrentParams.bIgnoreTranslation)
        {
            AccumulatedTranslation += Translation;
        }
        if (!CurrentParams.bIgnoreRotation)
        {
            AccumulatedRotation += Rotation;
        }

        if (CurrentParams.RootMotionMode == ERootMotionMode::Full)
        {
            MovementComponent->AddImpulse(Translation / DeltaTime, true);
            AnimComponent->GetOwner()->AddActorWorldRotation(Rotation);
        }
    }
}

void ULesFightRootMotionHandler::EnableRootMotion(bool bEnable)
{
    bRootMotionEnabled = bEnable;
    if (AnimComponent.IsValid())
    {
        USkeletalMeshComponent* Mesh = AnimComponent->GetMesh();
        if (Mesh)
        {
            Mesh->SetEnableBodyGravity(!bEnable);
        }
    }
}

void ULesFightRootMotionHandler::SetRootMotionMode(ERootMotionMode Mode)
{
    CurrentParams.RootMotionMode = Mode;
}

void ULesFightRootMotionHandler::SetTranslationMultiplier(float Multiplier)
{
    CurrentParams.TranslationMultiplier = Multiplier;
}

void ULesFightRootMotionHandler::SetRotationMultiplier(float Multiplier)
{
    CurrentParams.RotationMultiplier = Multiplier;
}

void ULesFightRootMotionHandler::SetRootMotionParams(const FRootMotionParams& Params)
{
    CurrentParams = Params;
}

FRootMotionSnapshot ULesFightRootMotionHandler::CaptureSnapshot()
{
    FRootMotionSnapshot Snapshot;
    if (AnimComponent.IsValid())
    {
        Snapshot.StartTransform = AnimComponent->GetOwner()->GetActorTransform();
    }
    Snapshot.AccumulatedTransform.SetLocation(AccumulatedTranslation);
    Snapshot.AccumulatedTransform.SetRotation(AccumulatedRotation.Quaternion());
    Snapshot.TotalDistance = AccumulatedTranslation.Size();
    Snapshot.bActive = true;
    return Snapshot;
}

void ULesFightRootMotionHandler::RestoreSnapshot(const FRootMotionSnapshot& Snapshot)
{
    if (Snapshot.bActive && AnimComponent.IsValid())
    {
        AnimComponent->GetOwner()->SetActorTransform(Snapshot.StartTransform);
        AccumulatedTranslation = Snapshot.AccumulatedTransform.GetLocation();
        AccumulatedRotation = Snapshot.AccumulatedTransform.GetRotation().Rotator();
    }
}

void ULesFightRootMotionHandler::ResetRootMotion()
{
    AccumulatedTranslation = FVector::ZeroVector;
    AccumulatedRotation = FRotator::ZeroRotator;
}
