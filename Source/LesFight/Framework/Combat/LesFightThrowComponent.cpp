#include "LesFightThrowComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightThrowComponent::ULesFightThrowComponent()
    : ThrowRange(150.0f)
    , ThrowDamage(30.0f)
    , StartupFrames(5)
    , ActiveFrames(3)
    , RecoveryFrames(10)
    , TechWindowDuration(0.2f)
    , ThrowState(EThrowState::Ready)
    , FrameCounter(0)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.016f;
}

void ULesFightThrowComponent::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
    ThrowState = EThrowState::Ready;
}

bool ULesFightThrowComponent::StartThrow()
{
    if (ThrowState != EThrowState::Ready) return false;
    if (!OwnerFighter.IsValid()) return false;

    ThrowState = EThrowState::Startup;
    FrameCounter = 0;

    OnThrowStart.Broadcast(ThrowTarget.Get());
    UE_LOG(LogLesFight, Verbose, TEXT("Throw startup started"));
    return true;
}

void ULesFightThrowComponent::PerformThrow()
{
    if (ThrowState != EThrowState::Active) return;

    if (ThrowTarget.IsValid())
    {
        OnThrowHit.Broadcast(ThrowTarget.Get());
        UE_LOG(LogLesFight, Verbose, TEXT("Throw hit on %s"), *ThrowTarget->GetName());
    }
    else
    {
        OnThrowWhiffed.Broadcast();
    }
}

void ULesFightThrowComponent::EndThrow()
{
    if (ThrowState != EThrowState::Ready && ThrowState != EThrowState::Cooldown)
    {
        ThrowState = EThrowState::Cooldown;
        FrameCounter = 0;
    }
}

bool ULesFightThrowComponent::CanTechThrow() const
{
    return ThrowState == EThrowState::Active;
}

void ULesFightThrowComponent::TryTechThrow()
{
    if (!CanTechThrow()) return;

    OnThrowTeched.Broadcast();
    ThrowState = EThrowState::Ready;
    UE_LOG(LogLesFight, Verbose, TEXT("Throw was teched"));
}

void ULesFightThrowComponent::BreakThrow(ALesFightBaseFighter* Breaker)
{
    OnThrowBroken.Broadcast(Breaker, EThrowResult::Broken);
    ThrowState = EThrowState::Ready;
    UE_LOG(LogLesFight, Verbose, TEXT("Throw was broken by %s"), *Breaker->GetName());
}
