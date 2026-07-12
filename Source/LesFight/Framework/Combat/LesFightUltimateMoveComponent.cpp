#include "LesFightUltimateMoveComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightUltimateMoveComponent::ULesFightUltimateMoveComponent()
    : SuperMeterMax(100.0f)
    , MeterBuildRate(5.0f)
    , StartupFrames(10)
    , RecoveryFrames(20)
    , bInvulnerableDuringUltimate(true)
    , CurrentState(EUltimateState::Ready)
    , SuperMeter(0.0f)
    , CurrentUltimateID(NAME_None)
    , FrameCounter(0)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.016f;
}

void ULesFightUltimateMoveComponent::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
    SuperMeter = 0.0f;
    CurrentState = EUltimateState::Ready;
}

void ULesFightUltimateMoveComponent::RegisterUltimateMove(
    const FUltimateMoveDefinition& UltimateDef)
{
    if (!UltimateDef.MoveID.IsNone())
    {
        RegisteredUltimates.Add(UltimateDef.MoveID, UltimateDef);
        UE_LOG(LogLesFight, Log, TEXT("Ultimate move registered: %s"), *UltimateDef.MoveName);
    }
}

bool ULesFightUltimateMoveComponent::TryExecuteUltimate(FName UltimateID)
{
    if (CurrentState != EUltimateState::Ready) return false;
    if (!HasFullMeter()) return false;

    const FUltimateMoveDefinition* Def = RegisteredUltimates.Find(UltimateID);
    if (!Def) return false;

    StartUltimate(UltimateID);
    return true;
}

void ULesFightUltimateMoveComponent::StartUltimate(FName UltimateID)
{
    const FUltimateMoveDefinition* Def = RegisteredUltimates.Find(UltimateID);
    if (!Def) return;

    CurrentState = EUltimateState::Startup;
    CurrentUltimateID = UltimateID;
    FrameCounter = 0;
    SuperMeter = 0.0f;

    CurrentState = EUltimateState::Active;
    OnUltimateExecuted.Broadcast(UltimateID);

    UE_LOG(LogLesFight, Log, TEXT("Ultimate move executed: %s"), *Def->MoveName);
}

void ULesFightUltimateMoveComponent::EndUltimate()
{
    if (CurrentState == EUltimateState::Active)
    {
        CurrentState = EUltimateState::Recovery;
        FrameCounter = 0;
        CurrentState = EUltimateState::Cooldown;

        FTimerHandle UnusedHandle;
        GetWorld()->GetTimerManager().SetTimer(UnusedHandle, FTimerDelegate::CreateLambda([this]() {
            CurrentState = EUltimateState::Ready;
        }), 0.5f, false);
    }
}

void ULesFightUltimateMoveComponent::InterruptUltimate()
{
    if (CurrentState == EUltimateState::Active)
    {
        OnUltimateInterrupted.Broadcast(CurrentUltimateID);
        CurrentState = EUltimateState::Interrupted;
        CurrentUltimateID = NAME_None;
        CurrentState = EUltimateState::Ready;
    }
}

void ULesFightUltimateMoveComponent::AddMeter(float Amount)
{
    float OldMeter = SuperMeter;
    SuperMeter = FMath::Clamp(SuperMeter + Amount, 0.0f, SuperMeterMax);

    if (OldMeter < SuperMeterMax && SuperMeter >= SuperMeterMax)
    {
        OnUltimateReady.Broadcast();
    }
}

void ULesFightUltimateMoveComponent::ResetMeter()
{
    SuperMeter = 0.0f;
}

TArray<FName> ULesFightUltimateMoveComponent::GetAvailableUltimates() const
{
    TArray<FName> Available;
    if (!HasFullMeter()) return Available;

    for (const auto& Pair : RegisteredUltimates)
    {
        Available.Add(Pair.Key);
    }
    return Available;
}
