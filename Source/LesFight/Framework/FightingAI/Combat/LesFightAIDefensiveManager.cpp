#include "LesFightAIDefensiveManager.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"
#include "Math/UnrealMathUtility.h"

void ULesFightAIDefensiveManager::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;

    BlockWeight = 0.4f;
    DodgeWeight = 0.3f;
    ParryWeight = 0.2f;
    CounterWeight = 0.1f;
    DefenseScore = 0.0f;
    bDefending = false;
    LastDefenseTime = 0.0f;
    DefensiveAction = EAIActionType::Block;
}

void ULesFightAIDefensiveManager::SetDefensiveStyle(float InBlockWeight, float InDodgeWeight, float InParryWeight, float InCounterWeight)
{
    BlockWeight = FMath::Clamp(InBlockWeight, 0.0f, 1.0f);
    DodgeWeight = FMath::Clamp(InDodgeWeight, 0.0f, 1.0f);
    ParryWeight = FMath::Clamp(InParryWeight, 0.0f, 1.0f);
    CounterWeight = FMath::Clamp(InCounterWeight, 0.0f, 1.0f);

    float Total = BlockWeight + DodgeWeight + ParryWeight + CounterWeight;
    if (Total > 0.0f)
    {
        BlockWeight /= Total;
        DodgeWeight /= Total;
        ParryWeight /= Total;
        CounterWeight /= Total;
    }
}

void ULesFightAIDefensiveManager::DecideDefense(const FAIPerceptionData& Perception, const FAIDecisionContext& OffensiveDecision)
{
    DefensiveAction = EAIActionType::Block;
    DefenseScore = 0.0f;
    bDefending = false;

    if (!OwnerController.IsValid())
        return;

    if (!Perception.bPlayerIsAttacking && !Perception.bPlayerIsRecovering)
    {
        bDefending = false;
        DefenseScore = 0.0f;
        return;
    }

    TMap<EAIActionType, float> DefenseScores;
    DefenseScores.Add(EAIActionType::Block, BlockWeight);
    DefenseScores.Add(EAIActionType::Dodge, DodgeWeight);
    DefenseScores.Add(EAIActionType::Parry, ParryWeight);
    DefenseScores.Add(EAIActionType::Counter, CounterWeight);

    if (Perception.bPlayerIsVulnerable && Perception.bPlayerIsRecovering)
    {
        DefenseScores[EAIActionType::Counter] *= 2.0f;
        DefenseScores[EAIActionType::Parry] *= 0.5f;
        DefenseScores[EAIActionType::Block] *= 0.3f;
    }

    if (Perception.PlayerStaminaPercent < 0.3f)
    {
        DefenseScores[EAIActionType::Dodge] *= 1.5f;
        DefenseScores[EAIActionType::Block] *= 0.6f;
    }

    if (Perception.TimeSinceLastPlayerAttack < 0.5f)
    {
        DefenseScores[EAIActionType::Dodge] *= 1.3f;
        DefenseScores[EAIActionType::Parry] *= 1.2f;
    }

    float TotalWeight = 0.0f;
    for (const auto& Elem : DefenseScores)
    {
        TotalWeight += Elem.Value;
    }

    if (TotalWeight <= 0.0f)
    {
        DefensiveAction = EAIActionType::Block;
        DefenseScore = BlockWeight;
        bDefending = BlockWeight > 0.0f;
        return;
    }

    float Rand = FMath::FRandRange(0.0f, TotalWeight);
    float Accum = 0.0f;
    for (const auto& Elem : DefenseScores)
    {
        Accum += Elem.Value;
        if (Rand <= Accum)
        {
            DefensiveAction = Elem.Key;
            DefenseScore = Elem.Value / TotalWeight;
            bDefending = true;
            LastDefenseTime = Perception.TimeSinceLastPlayerAttack;
            return;
        }
    }

    DefensiveAction = EAIActionType::Block;
    DefenseScore = 0.3f;
    bDefending = true;
}
