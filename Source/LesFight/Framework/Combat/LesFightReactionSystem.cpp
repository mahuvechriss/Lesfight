#include "LesFightReactionSystem.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"

ULesFightReactionSystem::ULesFightReactionSystem()
    : StaggerThreshold(30.0f)
    , KnockbackDistance(200.0f)
    , KnockdownDuration(1.5f)
    , GetupDuration(0.5f)
    , LaunchHeight(300.0f)
    , LaunchDuration(1.0f)
    , CurrentState(EReactionState::None)
    , ReactionTimer(0.0f)
    , ReactionDuration(0.0f)
    , ReactionForce(FVector::ZeroVector)
    , CurrentReactionID(NAME_None)
{
}

void ULesFightReactionSystem::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
}

void ULesFightReactionSystem::ApplyHitReaction(const FAttackDefinition& Attack,
    FVector HitDirection, float Damage)
{
    switch (Attack.Properties.HitReaction)
    {
    case EHitReaction::LightStun:
        if (Damage >= StaggerThreshold)
        {
            SetReactionState(EReactionState::Staggered);
            ReactionDuration = 0.5f;
        }
        else
        {
            SetReactionState(EReactionState::Hitstun);
            ReactionDuration = 0.25f;
        }
        break;

    case EHitReaction::HeavyStun:
        SetReactionState(EReactionState::Hitstun);
        ReactionDuration = 0.5f;
        break;

    case EHitReaction::Knockback:
        SetReactionState(EReactionState::Knockback);
        ReactionDuration = 0.6f;
        ApplyKnockback(HitDirection, Attack.DamageData.KnockbackForce);
        break;

    case EHitReaction::Launch:
        SetReactionState(EReactionState::Launched);
        ReactionDuration = LaunchDuration;
        ApplyLaunch(HitDirection, Attack.DamageData.LaunchForce);
        break;

    case EHitReaction::Knockdown:
        SetReactionState(EReactionState::Knockdown);
        ReactionDuration = KnockdownDuration;
        ApplyKnockback(HitDirection, Attack.DamageData.KnockbackForce);
        break;

    case EHitReaction::AirHit:
        SetReactionState(EReactionState::Airborne);
        ReactionDuration = 0.5f;
        ApplyKnockback(HitDirection, Attack.DamageData.KnockbackForce * 0.5f);
        break;

    default:
        SetReactionState(EReactionState::Hitstun);
        ReactionDuration = 0.25f;
        break;
    }

    CurrentReactionID = Attack.AttackID;
    ReactionTimer = 0.0f;

    PlayReactionAnimation(CurrentReactionID);
}

void ULesFightReactionSystem::ApplyBlockReaction(const FAttackDefinition& Attack,
    FVector HitDirection)
{
    SetReactionState(EReactionState::Blockstun);
    ReactionDuration = FMath::Max(Attack.FrameData.BlockstunFrames * 0.016f, 0.15f);
    ReactionTimer = 0.0f;

    ApplyKnockback(HitDirection, Attack.DamageData.KnockbackForce * 0.3f);

    PlayReactionAnimation(CurrentReactionID);
}

void ULesFightReactionSystem::EndCurrentReaction()
{
    if (CurrentState == EReactionState::Knockdown)
    {
        SetReactionState(EReactionState::Getup);
        ReactionDuration = GetupDuration;
        ReactionTimer = 0.0f;
        return;
    }

    SetReactionState(EReactionState::None);
    ReactionDuration = 0.0f;
    ReactionTimer = 0.0f;
    CurrentReactionID = NAME_None;
    OnReactionEnded.Broadcast();
}

void ULesFightReactionSystem::Freeze(float Duration)
{
    SetReactionState(EReactionState::Frozen);
    ReactionDuration = Duration;
    ReactionTimer = 0.0f;
}

void ULesFightReactionSystem::Unfreeze()
{
    if (CurrentState == EReactionState::Frozen)
    {
        EndCurrentReaction();
    }
}

bool ULesFightReactionSystem::IsInHitstun() const
{
    return CurrentState == EReactionState::Hitstun ||
           CurrentState == EReactionState::Staggered;
}

bool ULesFightReactionSystem::IsInBlockstun() const
{
    return CurrentState == EReactionState::Blockstun;
}

bool ULesFightReactionSystem::IsKnockedDown() const
{
    return CurrentState == EReactionState::Knockdown;
}

bool ULesFightReactionSystem::IsLaunched() const
{
    return CurrentState == EReactionState::Launched ||
           CurrentState == EReactionState::Airborne;
}

bool ULesFightReactionSystem::IsStaggered() const
{
    return CurrentState == EReactionState::Staggered;
}

float ULesFightReactionSystem::GetRemainingReactionRatio() const
{
    if (ReactionDuration <= 0.0f) return 0.0f;
    return FMath::Clamp(1.0f - (ReactionTimer / ReactionDuration), 0.0f, 1.0f);
}

bool ULesFightReactionSystem::CanAct() const
{
    return CurrentState == EReactionState::None;
}

void ULesFightReactionSystem::SetReactionState(EReactionState NewState)
{
    EReactionState OldState = CurrentState;
    CurrentState = NewState;
    OnReactionStateChanged.Broadcast(NewState);

    if (OwnerFighter.IsValid())
    {
        UE_LOG(LogLesFight, Verbose, TEXT("Reaction state: %d -> %d"),
            (int32)OldState, (int32)NewState);
    }
}

void ULesFightReactionSystem::ApplyKnockback(FVector Direction, float Force)
{
    if (!OwnerFighter.IsValid()) return;

    FVector KnockbackVelocity = Direction.GetSafeNormal() * Force * KnockbackDistance * 0.01f;
    KnockbackVelocity.Z = 100.0f;

    if (UCharacterMovementComponent* MoveComp = OwnerFighter->FindComponentByClass<UCharacterMovementComponent>())
    {
        MoveComp->Velocity = KnockbackVelocity;
        MoveComp->SetMovementMode(MOVE_Falling);
    }
}

void ULesFightReactionSystem::ApplyLaunch(FVector Direction, float Force)
{
    if (!OwnerFighter.IsValid()) return;

    FVector LaunchVelocity = Direction.GetSafeNormal() * Force * 0.5f;
    LaunchVelocity.Z = LaunchHeight;

    if (UCharacterMovementComponent* MoveComp = OwnerFighter->FindComponentByClass<UCharacterMovementComponent>())
    {
        MoveComp->Velocity = LaunchVelocity;
        MoveComp->SetMovementMode(MOVE_Falling);
    }
}

void ULesFightReactionSystem::ApplyDisplacement(FVector Offset)
{
    if (!OwnerFighter.IsValid()) return;
    OwnerFighter->AddActorWorldOffset(Offset, false, nullptr, ETeleportType::TeleportPhysics);
}

void ULesFightReactionSystem::PlayReactionAnimation(FName AnimationID)
{
    if (!OwnerFighter.IsValid()) return;

    UAnimInstance* AnimInst = OwnerFighter->GetMesh()->GetAnimInstance();
    if (AnimInst)
    {
        AnimInst->Montage_Stop(0.2f);
    }
}
