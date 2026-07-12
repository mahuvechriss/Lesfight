#include "LesFightDodgeComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightDodgeComponent::ULesFightDodgeComponent()
    : DodgeDistance(200.0f)
    , DodgeDuration(0.3f)
    , DodgeCooldown(0.5f)
    , DodgeSpeed(800.0f)
    , InvulnerabilityFrames(8)
    , DodgeCostStamina(20.0f)
    , DodgeState(EDodgeState::Ready)
    , DodgeDirection(FVector::ZeroVector)
    , DodgeTimer(0.0f)
    , CooldownTimer(0.0f)
    , iFrameCount(0)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.016f;
}

void ULesFightDodgeComponent::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
    DodgeState = EDodgeState::Ready;
}

bool ULesFightDodgeComponent::StartDodge(FVector Direction)
{
    if (DodgeState != EDodgeState::Ready) return false;

    if (!OwnerFighter.IsValid()) return false;

    DodgeDirection = Direction.GetSafeNormal();
    if (DodgeDirection.IsNearlyZero())
    {
        DodgeDirection = OwnerFighter->GetActorForwardVector();
    }

    DodgeState = EDodgeState::Dodging;
    DodgeTimer = 0.0f;
    CooldownTimer = 0.0f;
    iFrameCount = InvulnerabilityFrames;

    FVector DodgeVelocity = DodgeDirection * DodgeSpeed;
    if (UCharacterMovementComponent* MoveComp = OwnerFighter->FindComponentByClass<UCharacterMovementComponent>())
    {
        MoveComp->Velocity = DodgeVelocity;
    }

    OnDodgeStart.Broadcast();
    UE_LOG(LogLesFight, Verbose, TEXT("Dodge started"));
    return true;
}

void ULesFightDodgeComponent::EndDodge()
{
    if (DodgeState == EDodgeState::Dodging)
    {
        DodgeState = EDodgeState::Cooldown;
        DodgeTimer = 0.0f;
        CooldownTimer = 0.0f;
        OnDodgeCooldown.Broadcast();
    }
}

bool ULesFightDodgeComponent::TryDodgeAttack(FVector AttackDirection)
{
    if (DodgeState != EDodgeState::Dodging) return false;

    FVector OwnerForward = OwnerFighter->GetActorForwardVector();
    FVector ToAttacker = AttackDirection.GetSafeNormal();
    float DotProduct = FVector::DotProduct(OwnerForward, ToAttacker);

    bool bDodgeSuccessful = DotProduct > 0.3f;

    if (bDodgeSuccessful)
    {
        OnDodgeSuccess.Broadcast();
        UE_LOG(LogLesFight, Verbose, TEXT("Dodge successful"));
        return true;
    }

    OnDodgeFailed.Broadcast();
    return false;
}

void ULesFightDodgeComponent::ResetDodge()
{
    DodgeState = EDodgeState::Ready;
    DodgeTimer = 0.0f;
    CooldownTimer = 0.0f;
    iFrameCount = 0;
}
