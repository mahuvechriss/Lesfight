#include "Framework/FightingAI/Learning/LesFightAIReactionSystem.h"

ULesFightAIReactionSystem::ULesFightAIReactionSystem()
{
    ReactionAction = EAIActionType::None;
    ReactionDelay = 0.0f;
    BaseReactionMin = 0.2f;
    BaseReactionMax = 0.5f;

    DefaultReactions.Add(EAIAnimationEvent::AttackStart, EAIActionType::Block);
    DefaultReactions.Add(EAIAnimationEvent::AttackHit, EAIActionType::Recover);
    DefaultReactions.Add(EAIAnimationEvent::AttackMiss, EAIActionType::Counter);
    DefaultReactions.Add(EAIAnimationEvent::ComboStart, EAIActionType::Dodge);
    DefaultReactions.Add(EAIAnimationEvent::ComboEnd, EAIActionType::LightAttack);
    DefaultReactions.Add(EAIAnimationEvent::BlockStart, EAIActionType::Wait);
    DefaultReactions.Add(EAIAnimationEvent::BlockHit, EAIActionType::Block);
    DefaultReactions.Add(EAIAnimationEvent::DodgeStart, EAIActionType::Wait);
    DefaultReactions.Add(EAIAnimationEvent::DodgeComplete, EAIActionType::LightAttack);
    DefaultReactions.Add(EAIAnimationEvent::ParrySuccess, EAIActionType::Counter);
    DefaultReactions.Add(EAIAnimationEvent::CounterStart, EAIActionType::Dodge);
    DefaultReactions.Add(EAIAnimationEvent::CounterHit, EAIActionType::Recover);
    DefaultReactions.Add(EAIAnimationEvent::GetHit, EAIActionType::Block);
    DefaultReactions.Add(EAIAnimationEvent::Knockdown, EAIActionType::Recover);
    DefaultReactions.Add(EAIAnimationEvent::GetUp, EAIActionType::Block);
    DefaultReactions.Add(EAIAnimationEvent::Stunned, EAIActionType::Block);
    DefaultReactions.Add(EAIAnimationEvent::RecoverStart, EAIActionType::Wait);
    DefaultReactions.Add(EAIAnimationEvent::RecoverEnd, EAIActionType::LightAttack);
}

void ULesFightAIReactionSystem::ReactToEvent(EAIAnimationEvent Event, const FAIPerceptionData& Perception)
{
    EAIActionType* DefaultAction = DefaultReactions.Find(Event);
    if (DefaultAction)
    {
        ReactionAction = *DefaultAction;
    }
    else
    {
        ReactionAction = EAIActionType::Wait;
    }

    ReactionDelay = FMath::FRandRange(BaseReactionMin, BaseReactionMax);

    if (ReactionAction != EAIActionType::None)
    {
        OnReactionTriggered.Broadcast(ReactionAction);
    }
}

void ULesFightAIReactionSystem::SetBaseReactionTime(float Min, float Max)
{
    BaseReactionMin = FMath::Max(Min, 0.01f);
    BaseReactionMax = FMath::Max(Max, BaseReactionMin);
}

float ULesFightAIReactionSystem::GetCurrentReactionTime() const
{
    return FMath::FRandRange(BaseReactionMin, BaseReactionMax);
}

void ULesFightAIReactionSystem::ReactToPlayerAttack(const FAIPerceptionData& Perception)
{
    float DecisionRoll = FMath::FRand();

    float BlockThreshold = 0.5f;
    float DodgeThreshold = BlockThreshold + 0.3f;
    float ParryThreshold = DodgeThreshold + 0.15f;

    if (DecisionRoll < BlockThreshold)
    {
        ReactionAction = EAIActionType::Block;
    }
    else if (DecisionRoll < DodgeThreshold)
    {
        ReactionAction = EAIActionType::Dodge;
    }
    else if (DecisionRoll < ParryThreshold)
    {
        ReactionAction = EAIActionType::Parry;
    }
    else
    {
        ReactionAction = EAIActionType::Counter;
    }

    ReactionDelay = GetCurrentReactionTime();
    OnReactionTriggered.Broadcast(ReactionAction);
}

void ULesFightAIReactionSystem::ReactToMissedAttack()
{
    ReactionAction = EAIActionType::Counter;
    ReactionDelay = GetCurrentReactionTime() * 0.5f;
    OnReactionTriggered.Broadcast(ReactionAction);
}

void ULesFightAIReactionSystem::ReactToLowHealth()
{
    ReactionAction = EAIActionType::StepBack;
    ReactionDelay = GetCurrentReactionTime();
    OnReactionTriggered.Broadcast(ReactionAction);
}

void ULesFightAIReactionSystem::ReactToStaminaExhausted()
{
    ReactionAction = EAIActionType::StepBack;
    ReactionDelay = GetCurrentReactionTime() * 0.8f;
    OnReactionTriggered.Broadcast(ReactionAction);
}

void ULesFightAIReactionSystem::ReactToUltimateOpportunity()
{
    ReactionAction = EAIActionType::UltimateAttack;
    ReactionDelay = GetCurrentReactionTime() * 1.2f;
    OnReactionTriggered.Broadcast(ReactionAction);
}
