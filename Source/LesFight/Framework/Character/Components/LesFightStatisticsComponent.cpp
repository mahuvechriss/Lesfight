#include "LesFightStatisticsComponent.h"
#include "LesFight.h"

ULesFightStatisticsComponent::ULesFightStatisticsComponent()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ULesFightStatisticsComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightStatisticsComponent::Initialize(const FCharacterCombatAttributes& CombatStats,
    const FCharacterMovementAttributes& MoveStats,
    const FCharacterResourceAttributes& ResourceStats)
{
    CombatAttributes = CombatStats;
    MovementAttributes = MoveStats;
    ResourceAttributes = ResourceStats;
    CacheBaseStats();
}

void ULesFightStatisticsComponent::SetStat(const FString& StatName, float Value)
{
    if (StatName == TEXT("Strength")) CombatAttributes.Strength = Value;
    else if (StatName == TEXT("Defense")) CombatAttributes.Defense = Value;
    else if (StatName == TEXT("Agility")) CombatAttributes.Agility = Value;
    else if (StatName == TEXT("Balance")) CombatAttributes.Balance = Value;
    else if (StatName == TEXT("HitPoints")) ResourceAttributes.MaxHealth = Value;
    else if (StatName == TEXT("Stamina")) ResourceAttributes.MaxStamina = Value;

    OnStatChanged.Broadcast(StatName, Value);
}

float ULesFightStatisticsComponent::GetStat(const FString& StatName) const
{
    if (StatName == TEXT("Strength")) return CombatAttributes.Strength;
    if (StatName == TEXT("Defense")) return CombatAttributes.Defense;
    if (StatName == TEXT("Agility")) return CombatAttributes.Agility;
    if (StatName == TEXT("Balance")) return CombatAttributes.Balance;
    if (StatName == TEXT("HitPoints")) return ResourceAttributes.MaxHealth;
    if (StatName == TEXT("Stamina")) return ResourceAttributes.MaxStamina;

    float* Multiplier = StatMultipliers.Find(StatName);
    if (Multiplier)
    {
        if (BaseStats.Contains(StatName))
            return BaseStats[StatName] * (*Multiplier);
    }

    return 0.0f;
}

void ULesFightStatisticsComponent::ModifyStat(const FString& StatName, float Delta)
{
    float CurrentValue = GetStat(StatName);
    SetStat(StatName, CurrentValue + Delta);
}

void ULesFightStatisticsComponent::ResetStats()
{
    if (BaseStats.Contains(TEXT("Strength"))) CombatAttributes.Strength = BaseStats[TEXT("Strength")];
    if (BaseStats.Contains(TEXT("Defense"))) CombatAttributes.Defense = BaseStats[TEXT("Defense")];
    if (BaseStats.Contains(TEXT("Agility"))) CombatAttributes.Agility = BaseStats[TEXT("Agility")];
    if (BaseStats.Contains(TEXT("Balance"))) CombatAttributes.Balance = BaseStats[TEXT("Balance")];

    ClearAllMultipliers();
}

void ULesFightStatisticsComponent::SetCombatStats(const FCharacterCombatAttributes& NewStats)
{
    CombatAttributes = NewStats;
}

void ULesFightStatisticsComponent::SetMovementStats(const FCharacterMovementAttributes& NewStats)
{
    MovementAttributes = NewStats;
}

void ULesFightStatisticsComponent::SetResourceStats(const FCharacterResourceAttributes& NewStats)
{
    ResourceAttributes = NewStats;
}

void ULesFightStatisticsComponent::ApplyStatMultiplier(const FString& StatName, float Multiplier)
{
    StatMultipliers.Add(StatName, Multiplier);
}

void ULesFightStatisticsComponent::ClearAllMultipliers()
{
    StatMultipliers.Empty();
}

void ULesFightStatisticsComponent::CacheBaseStats()
{
    BaseStats.Empty();
    BaseStats.Add(TEXT("Strength"), CombatAttributes.Strength);
    BaseStats.Add(TEXT("Defense"), CombatAttributes.Defense);
    BaseStats.Add(TEXT("Agility"), CombatAttributes.Agility);
    BaseStats.Add(TEXT("Balance"), CombatAttributes.Balance);
    BaseStats.Add(TEXT("HitPoints"), ResourceAttributes.MaxHealth);
    BaseStats.Add(TEXT("Stamina"), ResourceAttributes.MaxStamina);
}

void ULesFightStatisticsComponent::ApplyAllMultipliers()
{
    for (auto& Pair : StatMultipliers)
    {
        if (BaseStats.Contains(Pair.Key))
        {
            float BaseValue = BaseStats[Pair.Key];
            SetStat(Pair.Key, BaseValue * Pair.Value);
        }
    }
}
