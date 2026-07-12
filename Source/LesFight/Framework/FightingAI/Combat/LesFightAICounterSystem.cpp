#include "LesFightAICounterSystem.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"
#include "Math/UnrealMathUtility.h"

void ULesFightAICounterSystem::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;

    CounterType = EAIActionType::Counter;
    CounterRate = 0.0f;
    CounterAggression = 0.5f;
    CounterWindow = 0.3f;
}

void ULesFightAICounterSystem::SetCounterAggression(float Aggression)
{
    CounterAggression = FMath::Clamp(Aggression, 0.0f, 1.0f);
}

bool ULesFightAICounterSystem::CanCounter(const FAIPerceptionData& Perception) const
{
    if (!Perception.bPlayerIsAttacking)
        return false;

    if (Perception.TimeSinceLastPlayerAttack > CounterWindow)
        return false;

    float SuccessChance = CounterRate + (CounterAggression * 0.3f);
    SuccessChance = FMath::Clamp(SuccessChance, 0.0f, 0.95f);

    return FMath::FRand() <= SuccessChance;
}

void ULesFightAICounterSystem::ExecuteCounter(FAIDecisionContext& Context)
{
    Context.ChosenAction = EAIActionType::Counter;
    Context.ActionScore = 1.0f;
    Context.Priority = EAIDecisionPriority::High;

    CounterType = EAIActionType::Counter;
    CounterRate = FMath::Min(1.0f, CounterRate + 0.05f);

    OnCounterExecuted.Broadcast(CounterType);
}

void ULesFightAICounterSystem::LearnCounterTiming(EAIActionType AttackType, float SuccessTime)
{
    if (float* Existing = CounterTimings.Find(AttackType))
    {
        *Existing = (*Existing + SuccessTime) * 0.5f;
    }
    else
    {
        CounterTimings.Add(AttackType, SuccessTime);
    }

    CounterRate = 0.0f;
    for (const auto& Elem : CounterTimings)
    {
        CounterRate += Elem.Value;
    }
    if (CounterTimings.Num() > 0)
    {
        CounterRate /= CounterTimings.Num();
        CounterRate = FMath::Clamp(CounterRate, 0.0f, 1.0f);
    }
}
