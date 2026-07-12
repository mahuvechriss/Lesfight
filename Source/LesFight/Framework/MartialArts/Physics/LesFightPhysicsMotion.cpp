#include "LesFightPhysicsMotion.h"
#include "LesFightMartialArtsManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ULesFightPhysicsMotion::ULesFightPhysicsMotion()
    : CurrentMomentum(FVector::ZeroVector)
    , CurrentRecovery(0.0f)
    , MomentumDecayRate(5.0f)
{
}

void ULesFightPhysicsMotion::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    if (InOwner)
    {
        OwnerCharacter = Cast<ACharacter>(InOwner->GetOuter());
    }
}

void ULesFightPhysicsMotion::Tick(float DeltaTime)
{
    if (Settings.bClothEnabled) ApplyClothPhysics(DeltaTime);
    if (Settings.bHairEnabled) ApplyHairPhysics(DeltaTime);
    if (Settings.bAccessoryEnabled) ApplyAccessoryPhysics(DeltaTime);
    if (Settings.bSecondaryMotionEnabled) ApplySecondaryMotion(DeltaTime);
    if (Settings.bMomentumEnabled) UpdateMomentum(DeltaTime);

    UpdateRecovery(DeltaTime);
}

void ULesFightPhysicsMotion::ApplyMomentum(FVector Impulse, float Weight)
{
    CurrentMomentum += Impulse * Weight * Settings.MomentumInheritance;

    if (OwnerCharacter.IsValid())
    {
        UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
        if (MoveComp)
        {
            MoveComp->AddImpulse(Impulse * Settings.BodyWeightInfluence, true);
        }
    }
}

void ULesFightPhysicsMotion::ApplyBodyWeight(float DeltaTime)
{
    if (!OwnerCharacter.IsValid()) return;

    UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
    if (MoveComp && Settings.BodyWeightInfluence > 1.0f)
    {
        MoveComp->GravityScale = 1.0f + (Settings.BodyWeightInfluence - 1.0f) * 0.5f;
    }
}

void ULesFightPhysicsMotion::RecoverFromHit(float RecoveryRate)
{
    CurrentRecovery = FMath::Min(CurrentRecovery + RecoveryRate, 1.0f);
}

void ULesFightPhysicsMotion::SetPhysicsSettings(const FPhysicsMotionSettings& NewSettings)
{
    Settings = NewSettings;
    ApplySimulationLevel(Settings.SimulationLevel);
}

void ULesFightPhysicsMotion::ToggleClothPhysics(bool bEnabled)
{
    Settings.bClothEnabled = bEnabled;
}

void ULesFightPhysicsMotion::ToggleHairPhysics(bool bEnabled)
{
    Settings.bHairEnabled = bEnabled;
}

void ULesFightPhysicsMotion::ToggleAccessoryPhysics(bool bEnabled)
{
    Settings.bAccessoryEnabled = bEnabled;
}

void ULesFightPhysicsMotion::ResetPhysics()
{
    CurrentMomentum = FVector::ZeroVector;
    CurrentRecovery = 0.0f;
}

void ULesFightPhysicsMotion::ApplyClothPhysics(float DeltaTime)
{
}

void ULesFightPhysicsMotion::ApplyHairPhysics(float DeltaTime)
{
}

void ULesFightPhysicsMotion::ApplyAccessoryPhysics(float DeltaTime)
{
}

void ULesFightPhysicsMotion::ApplySecondaryMotion(float DeltaTime)
{
}

void ULesFightPhysicsMotion::UpdateMomentum(float DeltaTime)
{
    if (CurrentMomentum.SizeSquared() > 0.0f)
    {
        CurrentMomentum = FMath::VInterpTo(CurrentMomentum, FVector::ZeroVector,
            DeltaTime, MomentumDecayRate);
        if (CurrentMomentum.SizeSquared() < 0.1f)
        {
            CurrentMomentum = FVector::ZeroVector;
        }
    }
}

void ULesFightPhysicsMotion::UpdateRecovery(float DeltaTime)
{
    if (CurrentRecovery < 1.0f)
    {
        CurrentRecovery = FMath::Min(CurrentRecovery +
            Settings.RecoveryRate * DeltaTime, 1.0f);
    }
}

void ULesFightPhysicsMotion::ApplySimulationLevel(EPhysicsSimulation Level)
{
    switch (Level)
    {
    case EPhysicsSimulation::None:
        Settings.bClothEnabled = false;
        Settings.bHairEnabled = false;
        Settings.bAccessoryEnabled = false;
        Settings.bSecondaryMotionEnabled = false;
        break;
    case EPhysicsSimulation::Cloth:
        Settings.bClothEnabled = true;
        break;
    case EPhysicsSimulation::Hair:
        Settings.bHairEnabled = true;
        break;
    case EPhysicsSimulation::Accessory:
        Settings.bAccessoryEnabled = true;
        break;
    case EPhysicsSimulation::SecondaryMotion:
        Settings.bSecondaryMotionEnabled = true;
        break;
    default:
        break;
    }
}
