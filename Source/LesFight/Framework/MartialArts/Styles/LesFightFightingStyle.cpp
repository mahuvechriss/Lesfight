#include "LesFightFightingStyle.h"

ULesFightFightingStyle::ULesFightFightingStyle()
    : StyleID(EFightingStyle::None)
{
}

void ULesFightFightingStyle::Initialize(EFightingStyle InStyleID)
{
    StyleID = InStyleID;
}

void ULesFightFightingStyle::OnEquip()
{
}

void ULesFightFightingStyle::OnUnequip()
{
}

void ULesFightFightingStyle::Tick(float DeltaTime)
{
}

void ULesFightFightingStyle::SetAttributes(const FStyleAttributes& NewAttributes)
{
    Attributes = NewAttributes;
}

TArray<ECombatStance> ULesFightFightingStyle::GetAvailableStances() const
{
    return AvailableStances;
}

TArray<EAdvancedMovementType> ULesFightFightingStyle::GetAvailableMovements() const
{
    return AvailableMovements;
}

TArray<ECounterType> ULesFightFightingStyle::GetAvailableCounters() const
{
    return AvailableCounters;
}

TArray<EAdvancedDodgeType> ULesFightFightingStyle::GetAvailableDodges() const
{
    return AvailableDodges;
}

TArray<EComboExpansionType> ULesFightFightingStyle::GetAvailableCombos() const
{
    return AvailableCombos;
}

TArray<EEnvironmentInteraction> ULesFightFightingStyle::GetAvailableInteractions() const
{
    return AvailableInteractions;
}

TArray<ECinematicEffect> ULesFightFightingStyle::GetAvailableCinematics() const
{
    return AvailableCinematics;
}

FName ULesFightFightingStyle::GetStanceAnimation(ECombatStance Stance) const
{
    const FName* Found = StanceAnimations.Find(Stance);
    return Found ? *Found : NAME_None;
}

FName ULesFightFightingStyle::GetAttackAnimation(int32 ComboStep) const
{
    const FName* Found = AttackAnimations.Find(ComboStep);
    return Found ? *Found : NAME_None;
}

FName ULesFightFightingStyle::GetCounterAnimation(ECounterType InCounterType) const
{
    const FName* Found = CounterAnimations.Find(InCounterType);
    return Found ? *Found : NAME_None;
}

FName ULesFightFightingStyle::GetDodgeAnimation(EAdvancedDodgeType DodgeType) const
{
    const FName* Found = DodgeAnimations.Find(DodgeType);
    return Found ? *Found : NAME_None;
}

FName ULesFightFightingStyle::GetMovementAnimation(EAdvancedMovementType MovementType) const
{
    const FName* Found = MovementAnimations.Find(MovementType);
    return Found ? *Found : NAME_None;
}

FName ULesFightFightingStyle::GetUltimateAnimation() const
{
    return UltimateMontageName;
}

float ULesFightFightingStyle::GetDamageMultiplier() const
{
    return Attributes.BaseDamageMultiplier;
}

float ULesFightFightingStyle::GetSpeedMultiplier() const
{
    return Attributes.BaseSpeedMultiplier;
}

float ULesFightFightingStyle::GetDefenseMultiplier() const
{
    return Attributes.BaseDefenseMultiplier;
}
