#include "LesFightStaminaComponent.h"
#include "LesFight.h"

ULesFightStaminaComponent::ULesFightStaminaComponent()
    : CurrentStamina(100.0f)
    , MaxStamina(100.0f)
    , RecoveryRate(15.0f)
    , RecoveryDelay(1.5f)
    , StaminaState(EStaminaState::Ready)
    , TimeSinceLastConsumption(0.0f)
    , bRecoveryPaused(false)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.1f;
}

void ULesFightStaminaComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentStamina = MaxStamina;
}

void ULesFightStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (StaminaState == EStaminaState::Exhausted || bRecoveryPaused)
        return;

    TimeSinceLastConsumption += DeltaTime;

    if (TimeSinceLastConsumption >= RecoveryDelay && CurrentStamina < MaxStamina)
    {
        StaminaState = EStaminaState::Regenerating;
        float RecoveredAmount = RecoveryRate * DeltaTime;
        CurrentStamina = FMath::Min(CurrentStamina + RecoveredAmount, MaxStamina);
        OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

        if (CurrentStamina >= MaxStamina)
        {
            StaminaState = EStaminaState::Ready;
            OnStaminaRecovered.Broadcast();
        }
    }
    else if (CurrentStamina >= MaxStamina)
    {
        StaminaState = EStaminaState::Ready;
    }
}

void ULesFightStaminaComponent::Initialize(float InMaxStamina, float InRecoveryRate)
{
    MaxStamina = InMaxStamina;
    RecoveryRate = InRecoveryRate;
    CurrentStamina = MaxStamina;
    StaminaState = EStaminaState::Ready;
    TimeSinceLastConsumption = 0.0f;
}

bool ULesFightStaminaComponent::ConsumeStamina(float Amount)
{
    if (CurrentStamina < Amount)
        return false;

    CurrentStamina -= Amount;
    TimeSinceLastConsumption = 0.0f;
    StaminaState = EStaminaState::Recovering;
    OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

    if (CurrentStamina <= 0.0f)
    {
        StaminaState = EStaminaState::Exhausted;
        OnExhausted.Broadcast();
    }

    return true;
}

void ULesFightStaminaComponent::RecoverStamina(float Amount)
{
    CurrentStamina = FMath::Min(CurrentStamina + Amount, MaxStamina);
    OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

    if (CurrentStamina >= MaxStamina)
    {
        StaminaState = EStaminaState::Ready;
        OnStaminaRecovered.Broadcast();
    }
}

void ULesFightStaminaComponent::SetCurrentStamina(float NewStamina)
{
    CurrentStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
    OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);

    if (CurrentStamina <= 0.0f)
    {
        StaminaState = EStaminaState::Exhausted;
        OnExhausted.Broadcast();
    }
}

void ULesFightStaminaComponent::SetMaxStamina(float NewMaxStamina)
{
    MaxStamina = FMath::Max(1.0f, NewMaxStamina);
    CurrentStamina = FMath::Min(CurrentStamina, MaxStamina);
    OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
}

void ULesFightStaminaComponent::ResetStamina()
{
    CurrentStamina = MaxStamina;
    StaminaState = EStaminaState::Ready;
    TimeSinceLastConsumption = 0.0f;
    OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina);
}

float ULesFightStaminaComponent::GetStaminaPercent() const
{
    return MaxStamina > 0.0f ? CurrentStamina / MaxStamina : 0.0f;
}
