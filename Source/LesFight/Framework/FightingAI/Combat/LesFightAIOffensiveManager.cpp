#include "LesFightAIOffensiveManager.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"
#include "Math/UnrealMathUtility.h"

void ULesFightAIOffensiveManager::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;

    AvailableAttacks = {
        EAIActionType::LightAttack,
        EAIActionType::HeavyAttack,
        EAIActionType::ComboAttack,
        EAIActionType::SpecialMove,
        EAIActionType::Grab,
        EAIActionType::StepForward
    };

    OffensivenessScore = 0.5f;
    bComboing = false;
    ComboProgress = 0;
}

EAIActionType ULesFightAIOffensiveManager::SelectAttackType() const
{
    if (AvailableAttacks.Num() == 0)
        return EAIActionType::LightAttack;

    float TotalWeight = 0.0f;
    TArray<float> Weights;
    Weights.Reserve(AvailableAttacks.Num());

    for (const EAIActionType& Attack : AvailableAttacks)
    {
        float Weight = 1.0f;
        if (const float* Cooldown = AttackCooldowns.Find(Attack))
        {
            if (*Cooldown > 0.0f)
                Weight = 0.1f;
        }
        Weights.Add(Weight);
        TotalWeight += Weight;
    }

    float Rand = FMath::FRandRange(0.0f, TotalWeight);
    float Accum = 0.0f;
    for (int32 i = 0; i < AvailableAttacks.Num(); ++i)
    {
        Accum += Weights[i];
        if (Rand <= Accum)
            return AvailableAttacks[i];
    }

    return AvailableAttacks.Last();
}

bool ULesFightAIOffensiveManager::ShouldUseSpecial() const
{
    return OffensivenessScore > 0.7f;
}

bool ULesFightAIOffensiveManager::ShouldUseUltimate() const
{
    return OffensivenessScore > 0.95f;
}

void ULesFightAIOffensiveManager::DecideAttack(const FAIPerceptionData& Perception, FAIDecisionContext& Context)
{
    Context.ChosenAction = EAIActionType::Wait;
    Context.ActionScore = 0.0f;
    Context.Priority = EAIDecisionPriority::Medium;

    if (!OwnerController.IsValid())
        return;

    OffensivenessScore = FMath::Clamp(OffensivenessScore + FMath::FRandRange(-0.05f, 0.05f), 0.0f, 1.0f);

    TMap<EAIActionType, float> AttackScores;
    AttackScores.Add(EAIActionType::LightAttack, 0.0f);
    AttackScores.Add(EAIActionType::HeavyAttack, 0.0f);
    AttackScores.Add(EAIActionType::ComboAttack, 0.0f);
    AttackScores.Add(EAIActionType::SpecialMove, 0.0f);
    AttackScores.Add(EAIActionType::Grab, 0.0f);
    AttackScores.Add(EAIActionType::StepForward, 0.0f);

    switch (Perception.CurrentRange)
    {
    case EAICombatRange::Close:
        AttackScores[EAIActionType::LightAttack] = FMath::FRandRange(0.6f, 0.9f);
        AttackScores[EAIActionType::HeavyAttack] = FMath::FRandRange(0.4f, 0.8f);
        AttackScores[EAIActionType::Grab] = FMath::FRandRange(0.3f, 0.7f);
        AttackScores[EAIActionType::ComboAttack] = FMath::FRandRange(0.5f, 0.85f);
        break;

    case EAICombatRange::Medium:
        AttackScores[EAIActionType::ComboAttack] = FMath::FRandRange(0.6f, 0.9f);
        AttackScores[EAIActionType::SpecialMove] = FMath::FRandRange(0.5f, 0.85f);
        AttackScores[EAIActionType::LightAttack] = FMath::FRandRange(0.3f, 0.6f);
        AttackScores[EAIActionType::StepForward] = FMath::FRandRange(0.3f, 0.5f);
        break;

    case EAICombatRange::Far:
        AttackScores[EAIActionType::StepForward] = FMath::FRandRange(0.7f, 1.0f);
        break;

    case EAICombatRange::Grappling:
        AttackScores[EAIActionType::Grab] = FMath::FRandRange(0.7f, 1.0f);
        AttackScores[EAIActionType::HeavyAttack] = FMath::FRandRange(0.4f, 0.7f);
        break;
    }

    if (ShouldUseUltimate())
    {
        AttackScores[EAIActionType::UltimateAttack] = 1.0f;
    }
    else if (ShouldUseSpecial())
    {
        AttackScores[EAIActionType::SpecialMove] = FMath::Max(AttackScores[EAIActionType::SpecialMove], 0.85f);
    }

    for (auto& Elem : AttackCooldowns)
    {
        Elem.Value = FMath::Max(0.0f, Elem.Value - 0.016f);
        if (Elem.Value > 0.0f && AttackScores.Contains(Elem.Key))
        {
            AttackScores[Elem.Key] *= 0.2f;
        }
    }

    EAIActionType BestAction = EAIActionType::Wait;
    float BestScore = 0.0f;
    for (const auto& Elem : AttackScores)
    {
        if (Elem.Value > BestScore)
        {
            BestScore = Elem.Value;
            BestAction = Elem.Key;
        }
    }

    Context.ChosenAction = BestAction;
    Context.ActionScore = BestScore;
    Context.Priority = (BestScore > 0.8f) ? EAIDecisionPriority::High : EAIDecisionPriority::Medium;

    if (BestAction != EAIActionType::Wait && BestAction != EAIActionType::StepForward)
    {
        AttackCooldowns.FindOrAdd(BestAction) = 0.3f;
    }
}
