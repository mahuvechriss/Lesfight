#include "LesFightHealthComponent.h"
#include "LesFight.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"

ULesFightHealthComponent::ULesFightHealthComponent()
    : CurrentHealth(1000.0f)
    , MaxHealth(1000.0f)
    , bIsDead(false)
    , bIsInvulnerable(false)
    , TotalDamageTaken(0.0f)
    , TotalHealingReceived(0.0f)
{
    PrimaryActorTick.bCanEverTick = false;
}

void ULesFightHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
}

void ULesFightHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULesFightHealthComponent::Initialize(float InMaxHealth)
{
    MaxHealth = InMaxHealth;
    CurrentHealth = MaxHealth;
    bIsDead = false;
    TotalDamageTaken = 0.0f;
    TotalHealingReceived = 0.0f;
}

float ULesFightHealthComponent::TakeDamage(float DamageAmount, AActor* DamageInstigator)
{
    if (bIsDead || bIsInvulnerable || DamageAmount <= 0.0f)
        return 0.0f;

    float ActualDamage = FMath::Min(DamageAmount, CurrentHealth);
    CurrentHealth -= ActualDamage;
    TotalDamageTaken += ActualDamage;

    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
    OnDamageTaken.Broadcast(ActualDamage, DamageInstigator);

    if (CurrentHealth <= 0.0f && !bIsDead)
    {
        bIsDead = true;
        CurrentHealth = 0.0f;
        OnDeath.Broadcast();
        UE_LOG(LogLesFight, Log, TEXT("Character %s has died"), *GetOwner()->GetName());
    }

    return ActualDamage;
}

float ULesFightHealthComponent::Heal(float HealAmount, AActor* Healer)
{
    if (bIsDead || HealAmount <= 0.0f)
        return 0.0f;

    float ActualHeal = FMath::Min(HealAmount, MaxHealth - CurrentHealth);
    CurrentHealth += ActualHeal;
    TotalHealingReceived += ActualHeal;

    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
    OnHealingReceived.Broadcast(ActualHeal, Healer);

    return ActualHeal;
}

void ULesFightHealthComponent::SetCurrentHealth(float NewHealth)
{
    CurrentHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);

    if (CurrentHealth <= 0.0f && !bIsDead)
    {
        bIsDead = true;
        OnDeath.Broadcast();
    }
}

void ULesFightHealthComponent::SetMaxHealth(float NewMaxHealth)
{
    MaxHealth = FMath::Max(1.0f, NewMaxHealth);
    CurrentHealth = FMath::Min(CurrentHealth, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void ULesFightHealthComponent::ResetHealth()
{
    CurrentHealth = MaxHealth;
    bIsDead = false;
    bIsInvulnerable = false;
    TotalDamageTaken = 0.0f;
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

void ULesFightHealthComponent::Kill()
{
    if (!bIsDead)
    {
        CurrentHealth = 0.0f;
        bIsDead = true;
        OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
        OnDeath.Broadcast();
    }
}

void ULesFightHealthComponent::Revive(float HealthPercent)
{
    if (bIsDead)
    {
        CurrentHealth = MaxHealth * FMath::Clamp(HealthPercent, 0.0f, 1.0f);
        bIsDead = false;
        OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
        OnRevived.Broadcast();
    }
}

void ULesFightHealthComponent::SetInvulnerable(bool bInvulnerable, float Duration)
{
    bIsInvulnerable = bInvulnerable;

    if (bInvulnerable && Duration > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(InvulnerabilityTimer, this,
            &ULesFightHealthComponent::EndInvulnerability, Duration, false);
    }

    if (!bInvulnerable)
    {
        GetWorld()->GetTimerManager().ClearTimer(InvulnerabilityTimer);
    }
}

float ULesFightHealthComponent::GetHealthPercent() const
{
    return MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;
}

void ULesFightHealthComponent::EndInvulnerability()
{
    bIsInvulnerable = false;
}

void ULesFightHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ULesFightHealthComponent, CurrentHealth);
    DOREPLIFETIME(ULesFightHealthComponent, MaxHealth);
}
