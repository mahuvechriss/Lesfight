#include "LesFightDamageManager.h"
#include "LesFight.h"

ULesFightDamageManager::ULesFightDamageManager()
    : GlobalDamageMultiplier(1.0f)
    , ComboScalingReduction(0.1f)
    , MinimumScaling(0.1f)
    , BlockDamageReduction(0.5f)
    , CritChanceMultiplier(1.0f)
    , WeightKnockbackFactor(1.0f)
    , bComboScalingEnabled(true)
    , KnockbackForceMultiplier(1.0f)
    , BaseHitstun(12)
{
}

void ULesFightDamageManager::Initialize()
{
    UE_LOG(LogLesFight, Log, TEXT("DamageManager initialized"));
}

float ULesFightDamageManager::CalculateDamage(const FAttackDefinition& Attack, int32 ComboCount)
{
    float Damage = Attack.DamageData.BaseDamage * GlobalDamageMultiplier;

    if (bComboScalingEnabled)
    {
        Damage = ApplyDamageScaling(Damage, ComboCount);
    }

    if (Attack.DamageData.bCanCrit && RollCriticalHit(Attack))
    {
        Damage *= Attack.DamageData.CritMultiplier;
    }

    return Damage;
}

FDamageResult ULesFightDamageManager::CalculateFullDamage(const FAttackDefinition& Attack,
    int32 ComboCount, bool bIsBlocked)
{
    FDamageResult Result;
    Result.BaseDamage = Attack.DamageData.BaseDamage;
    Result.ScaledDamage = CalculateDamage(Attack, ComboCount);
    Result.bWasCrit = Attack.DamageData.bCanCrit && RollCriticalHit(Attack);

    Result.FinalDamage = bIsBlocked
        ? Result.ScaledDamage * BlockDamageReduction
        : Result.ScaledDamage;

    Result.KnockbackForce = Attack.DamageData.KnockbackForce * KnockbackForceMultiplier;
    Result.LaunchForce = Attack.DamageData.LaunchForce * KnockbackForceMultiplier;
    Result.HitReaction = Attack.Properties.HitReaction;
    Result.HitstunFrames = bIsBlocked
        ? Attack.FrameData.BlockstunFrames
        : GetHitstunDuration(Result.FinalDamage, Attack.Properties.HitReaction);
    Result.BlockstunFrames = Attack.FrameData.BlockstunFrames;

    return Result;
}

float ULesFightDamageManager::ApplyDamageScaling(float BaseDamage, int32 ComboCount) const
{
    if (ComboCount <= 0) return BaseDamage;
    float Scaling = FMath::Max(1.0f - (ComboCount * ComboScalingReduction), MinimumScaling);
    return BaseDamage * Scaling;
}

bool ULesFightDamageManager::RollCriticalHit(const FAttackDefinition& Attack) const
{
    return FMath::FRand() < 0.05f * CritChanceMultiplier;
}

float ULesFightDamageManager::GetKnockbackDistance(float BaseKnockback, float TargetWeight) const
{
    return BaseKnockback / FMath::Max(TargetWeight * WeightKnockbackFactor, 0.1f);
}

int32 ULesFightDamageManager::GetHitstunDuration(float Damage, EHitReaction ReactionType) const
{
    switch (ReactionType)
    {
    case EHitReaction::LightStun:  return BaseHitstun;
    case EHitReaction::HeavyStun:  return BaseHitstun * 2;
    case EHitReaction::Knockback:  return BaseHitstun * 3;
    case EHitReaction::Launch:     return BaseHitstun * 4;
    case EHitReaction::Knockdown:  return BaseHitstun * 5;
    case EHitReaction::AirHit:     return BaseHitstun * 3;
    default: return BaseHitstun;
    }
}
