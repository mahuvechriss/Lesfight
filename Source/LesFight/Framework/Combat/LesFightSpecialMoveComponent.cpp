#include "LesFightSpecialMoveComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightSpecialMoveComponent::ULesFightSpecialMoveComponent()
    : MeterPoolMax(100.0f)
    , MeterRegenRate(5.0f)
    , CurrentState(ESpecialMoveState::Ready)
    , CurrentMeter(0.0f)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.05f;
}

void ULesFightSpecialMoveComponent::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
    CurrentMeter = 0.0f;
    CurrentState = ESpecialMoveState::Ready;
}

void ULesFightSpecialMoveComponent::RegisterSpecialMove(const FSpecialMoveDefinition& MoveDef)
{
    if (!MoveDef.MoveID.IsNone())
    {
        RegisteredMoves.Add(MoveDef.MoveID, MoveDef);
        UE_LOG(LogLesFight, Log, TEXT("Special move registered: %s"), *MoveDef.MoveName);
    }
}

bool ULesFightSpecialMoveComponent::TryExecuteSpecialMove(FName MoveID)
{
    if (CurrentState != ESpecialMoveState::Ready) return false;

    const FSpecialMoveDefinition* MoveDef = RegisteredMoves.Find(MoveID);
    if (!MoveDef) return false;

    if (!HasMeterForMove(MoveID)) return false;

    StartSpecialMove(MoveID);
    return true;
}

bool ULesFightSpecialMoveComponent::DetectSpecialMoveInput(
    TArray<ESpecialMoveInput> RecentInputs, EAttackType ButtonPressed)
{
    for (auto& [MoveID, MoveDef] : RegisteredMoves)
    {
        if (MoveDef.InputSequence.bRequiresButtonPress && MoveDef.InputSequence.RequiredButton != ButtonPressed)
        {
            continue;
        }

        if (MatchInputSequence(MoveDef.InputSequence.InputSequence))
        {
            if (HasMeterForMove(MoveID))
            {
                StartSpecialMove(MoveID);
                return true;
            }
        }
    }
    return false;
}

bool ULesFightSpecialMoveComponent::HasMeterForMove(FName MoveID) const
{
    const FSpecialMoveDefinition* MoveDef = RegisteredMoves.Find(MoveID);
    if (!MoveDef) return false;
    return CurrentMeter >= MoveDef.MeterCost;
}

void ULesFightSpecialMoveComponent::ConsumeMeterForMove(FName MoveID)
{
    const FSpecialMoveDefinition* MoveDef = RegisteredMoves.Find(MoveID);
    if (MoveDef)
    {
        CurrentMeter = FMath::Max(0.0f, CurrentMeter - MoveDef->MeterCost);
    }
}

void ULesFightSpecialMoveComponent::StartSpecialMove(FName MoveID)
{
    const FSpecialMoveDefinition* MoveDef = RegisteredMoves.Find(MoveID);
    if (!MoveDef) return;

    CurrentState = ESpecialMoveState::Startup;
    ConsumeMeterForMove(MoveID);

    CurrentState = ESpecialMoveState::Active;
    OnSpecialMoveExecuted.Broadcast(MoveID);
    UE_LOG(LogLesFight, Log, TEXT("Special move executed: %s"), *MoveDef->MoveName);
}

void ULesFightSpecialMoveComponent::EndSpecialMove()
{
    CurrentState = ESpecialMoveState::Cooldown;
    CurrentState = ESpecialMoveState::Ready;
}

TArray<FName> ULesFightSpecialMoveComponent::GetAvailableMoves() const
{
    TArray<FName> Available;
    for (const auto& Pair : RegisteredMoves)
    {
        if (CurrentMeter >= Pair.Value.MeterCost)
        {
            Available.Add(Pair.Key);
        }
    }
    return Available;
}

bool ULesFightSpecialMoveComponent::MatchInputSequence(
    const TArray<ESpecialMoveInput>& Sequence)
{
    if (Sequence.Num() == 0) return false;
    if (RecentInputHistory.Num() < Sequence.Num()) return false;

    int32 HistoryOffset = RecentInputHistory.Num() - Sequence.Num();
    for (int32 i = 0; i < Sequence.Num(); i++)
    {
        if (RecentInputHistory[HistoryOffset + i] != Sequence[i])
        {
            return false;
        }
    }
    return true;
}
