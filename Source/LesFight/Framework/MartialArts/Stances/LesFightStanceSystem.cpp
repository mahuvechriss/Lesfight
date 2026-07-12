#include "LesFightStanceSystem.h"
#include "LesFightMartialArtsManager.h"

ULesFightStanceSystem::ULesFightStanceSystem()
    : CurrentStance(ECombatStance::Neutral)
    , StanceSwitchCooldown(0.0f)
    , bStanceLocked(false)
    , SwitchCooldownDuration(0.2f)
    , LastSwitchTime(0.0f)
{
    AvailableStances = {
        ECombatStance::Neutral,
        ECombatStance::Offensive,
        ECombatStance::Defensive,
        ECombatStance::Agile,
        ECombatStance::Heavy,
        ECombatStance::StyleSpecific
    };
}

void ULesFightStanceSystem::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    CurrentStance = ECombatStance::Neutral;
    LastSwitchTime = 0.0f;

    for (ECombatStance Stance : AvailableStances)
    {
        StanceDefinitions.Emplace(Stance, GetDefaultStanceData(Stance));
    }
}

void ULesFightStanceSystem::Tick(float DeltaTime)
{
    if (StanceSwitchCooldown > 0.0f)
    {
        StanceSwitchCooldown -= DeltaTime;
    }
}

bool ULesFightStanceSystem::SwitchStance(ECombatStance NewStance)
{
    if (bStanceLocked) return false;
    if (CurrentStance == NewStance) return true;
    if (StanceSwitchCooldown > 0.0f) return false;
    if (!AvailableStances.Contains(NewStance)) return false;

    CurrentStance = NewStance;
    StanceSwitchCooldown = SwitchCooldownDuration;
    LastSwitchTime = OwnerManager.IsValid() && OwnerManager->GetWorld()
        ? OwnerManager->GetWorld()->GetTimeSeconds() : 0.0f;

    BroadcastStanceChange(NewStance);
    return true;
}

bool ULesFightStanceSystem::SwitchToNeutral() { return SwitchStance(ECombatStance::Neutral); }
bool ULesFightStanceSystem::SwitchToOffensive() { return SwitchStance(ECombatStance::Offensive); }
bool ULesFightStanceSystem::SwitchToDefensive() { return SwitchStance(ECombatStance::Defensive); }
bool ULesFightStanceSystem::SwitchToAgile() { return SwitchStance(ECombatStance::Agile); }
bool ULesFightStanceSystem::SwitchToHeavy() { return SwitchStance(ECombatStance::Heavy); }
bool ULesFightStanceSystem::SwitchToStyleSpecific() { return SwitchStance(ECombatStance::StyleSpecific); }

void ULesFightStanceSystem::CycleStance(bool bForward)
{
    if (AvailableStances.Num() == 0) return;

    int32 CurrentIndex = AvailableStances.IndexOfByKey(CurrentStance);
    int32 NextIndex = CurrentIndex + (bForward ? 1 : -1);

    if (NextIndex < 0) NextIndex = AvailableStances.Num() - 1;
    if (NextIndex >= AvailableStances.Num()) NextIndex = 0;

    SwitchStance(AvailableStances[NextIndex]);
}

FStanceAttributes ULesFightStanceSystem::GetCurrentStanceAttributes() const
{
    const FStanceAttributes* Found = StanceDefinitions.Find(CurrentStance);
    return Found ? *Found : FStanceAttributes();
}

float ULesFightStanceSystem::GetDamageModifier() const
{
    return GetCurrentStanceAttributes().DamageModifier;
}

float ULesFightStanceSystem::GetSpeedModifier() const
{
    return GetCurrentStanceAttributes().SpeedModifier;
}

float ULesFightStanceSystem::GetDefenseModifier() const
{
    return GetCurrentStanceAttributes().DefenseModifier;
}

float ULesFightStanceSystem::GetStaminaRegenModifier() const
{
    return GetCurrentStanceAttributes().StaminaRegenModifier;
}

void ULesFightStanceSystem::SetStanceData(const TMap<ECombatStance, FStanceAttributes>& Definitions)
{
    for (const auto& Pair : Definitions)
    {
        if (StanceDefinitions.Contains(Pair.Key))
        {
            StanceDefinitions[Pair.Key] = Pair.Value;
        }
    }
}

void ULesFightStanceSystem::LockStance(bool bLocked)
{
    bStanceLocked = bLocked;
}

void ULesFightStanceSystem::ResetToNeutral()
{
    CurrentStance = ECombatStance::Neutral;
    StanceSwitchCooldown = 0.0f;
    bStanceLocked = false;
    BroadcastStanceChange(ECombatStance::Neutral);
}

void ULesFightStanceSystem::BroadcastStanceChange(ECombatStance NewStance)
{
    OnStanceChanged.Broadcast(NewStance);
}

FStanceAttributes ULesFightStanceSystem::GetDefaultStanceData(ECombatStance Stance) const
{
    FStanceAttributes Attr;
    switch (Stance)
    {
    case ECombatStance::Neutral:
        Attr = FStanceAttributes();
        break;
    case ECombatStance::Offensive:
        Attr.DamageModifier = 1.2f;
        Attr.DefenseModifier = 0.8f;
        Attr.ComboDamageBonus = 0.15f;
        break;
    case ECombatStance::Defensive:
        Attr.DamageModifier = 0.8f;
        Attr.DefenseModifier = 1.3f;
        Attr.CounterChanceBonus = 0.2f;
        Attr.StaminaRegenModifier = 1.2f;
        break;
    case ECombatStance::Agile:
        Attr.SpeedModifier = 1.3f;
        Attr.DamageModifier = 0.9f;
        Attr.DodgeWindowModifier = 1.3f;
        break;
    case ECombatStance::Heavy:
        Attr.DamageModifier = 1.3f;
        Attr.SpeedModifier = 0.8f;
        Attr.DefenseModifier = 1.2f;
        Attr.StaminaRegenModifier = 0.7f;
        break;
    case ECombatStance::StyleSpecific:
        Attr.DamageModifier = 1.1f;
        Attr.SpeedModifier = 1.1f;
        Attr.DefenseModifier = 1.1f;
        break;
    }
    return Attr;
}
