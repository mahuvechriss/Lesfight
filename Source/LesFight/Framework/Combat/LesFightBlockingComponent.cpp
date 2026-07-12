#include "LesFightBlockingComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightBlockingComponent::ULesFightBlockingComponent()
    : GuardMeterMax(100.0f)
    , GuardRegenRate(15.0f)
    , GuardRegenDelay(1.0f)
    , ChipDamageMultiplier(0.25f)
    , PushbackDistance(50.0f)
    , BlockstunDuration(0.15f)
    , GuardBreakThreshold(100.0f)
    , GuardCrushDuration(1.0f)
    , bIsBlocking(false)
    , CurrentBlockState(EBlockState::None)
    , GuardMeter(100.0f)
    , LastGuardDamageTime(0.0f)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.1f;
}

void ULesFightBlockingComponent::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
    GuardMeter = GuardMeterMax;
}

void ULesFightBlockingComponent::StartBlocking(EBlockState BlockState)
{
    bIsBlocking = true;
    CurrentBlockState = BlockState;
    OnBlockStateChanged.Broadcast(BlockState);
}

void ULesFightBlockingComponent::StopBlocking()
{
    if (bIsBlocking)
    {
        bIsBlocking = false;
        CurrentBlockState = EBlockState::None;
        OnBlockStateChanged.Broadcast(EBlockState::None);
    }
}

bool ULesFightBlockingComponent::TryBlock(const FAttackDefinition& Attack, AActor* Attacker)
{
    if (!bIsBlocking || !CanBlockAttack(Attack)) return false;

    AddGuardDamage(Attack.DamageData.BaseDamage * ChipDamageMultiplier);
    OnBlockedAttack.Broadcast(Attacker, Attack);

    if (GuardMeter >= GuardBreakThreshold)
    {
        CurrentBlockState = EBlockState::GuardCrush;
        OnGuardBreak.Broadcast();
        return false;
    }

    return true;
}

void ULesFightBlockingComponent::ResetGuardMeter()
{
    GuardMeter = 0.0f;
}

void ULesFightBlockingComponent::AddGuardDamage(float Damage)
{
    GuardMeter = FMath::Clamp(GuardMeter + Damage, 0.0f, GuardMeterMax);
    LastGuardDamageTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

void ULesFightBlockingComponent::ApplyGuardRegen(float DeltaTime)
{
    if (!GetWorld()) return;

    float CurrentTime = GetWorld()->GetTimeSeconds();
    if ((CurrentTime - LastGuardDamageTime) < GuardRegenDelay) return;

    if (GuardMeter > 0.0f)
    {
        GuardMeter = FMath::Max(0.0f, GuardMeter - GuardRegenRate * DeltaTime);
    }
}

bool ULesFightBlockingComponent::CanBlockAttack(const FAttackDefinition& Attack) const
{
    if (GuardMeter >= GuardBreakThreshold) return false;
    if (CurrentBlockState == EBlockState::GuardCrush) return false;

    return IsAttackBlockable(Attack);
}

bool ULesFightBlockingComponent::IsAttackBlockable(const FAttackDefinition& Attack) const
{
    switch (Attack.Properties.AntiBlock)
    {
    case EAntiBlock::None:
        return true;
    case EAntiBlock::StandOnly:
        return CurrentBlockState != EBlockState::Standing;
    case EAntiBlock::CrouchOnly:
        return CurrentBlockState != EBlockState::Crouching;
    case EAntiBlock::Unblockable:
        return false;
    case EAntiBlock::GuardBreak:
        return false;
    default:
        return true;
    }
}
