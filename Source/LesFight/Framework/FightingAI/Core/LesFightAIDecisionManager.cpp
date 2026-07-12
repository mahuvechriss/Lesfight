#include "LesFightAIDecisionManager.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"

void ULesFightAIDecisionManager::MakeDecision(const FAIPerceptionData& Perception, FAIDecisionContext& OutDecision)
{
    ActionScores.Empty();

    static const EAIActionType AllActions[] = {
        EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::Block,
        EAIActionType::Dodge, EAIActionType::Dash, EAIActionType::Jump,
        EAIActionType::SpecialMove, EAIActionType::Grab, EAIActionType::Counter,
        EAIActionType::Retreat, EAIActionType::Approach, EAIActionType::Wait,
        EAIActionType::Combo, EAIActionType::Taunt
    };

    for (EAIActionType Action : AllActions)
    {
        float Score = 0.0f;

        switch (Action)
        {
        case EAIActionType::LightAttack:
            if (Perception.DistanceToTarget < 200.0f && Perception.SelfStamina > 20.0f)
                Score = 60.0f + (Perception.ThreatLevel * 10.0f);
            break;
        case EAIActionType::HeavyAttack:
            if (Perception.DistanceToTarget < 150.0f && Perception.SelfStamina > 40.0f)
                Score = 40.0f + (Perception.TargetHealth < 30.0f ? 30.0f : 0.0f);
            break;
        case EAIActionType::Block:
            if (Perception.bIsTargetAttacking)
                Score = 70.0f + (Perception.SelfHealth < 30.0f ? 20.0f : 0.0f);
            else
                Score = 20.0f;
            break;
        case EAIActionType::Dodge:
            if (Perception.bIsTargetAttacking && Perception.DistanceToTarget < 150.0f)
                Score = 65.0f;
            break;
        case EAIActionType::Dash:
            if (Perception.DistanceToTarget > 300.0f)
                Score = 50.0f + (Perception.ThreatLevel * 5.0f);
            break;
        case EAIActionType::Combo:
            if (Perception.DistanceToTarget < 200.0f && Perception.SelfStamina > 50.0f)
                Score = 45.0f + (Perception.bIsTargetBlocking ? -20.0f : 10.0f);
            break;
        case EAIActionType::Retreat:
            if (Perception.SelfHealth < 20.0f || Perception.SelfStamina < 15.0f)
                Score = 80.0f;
            break;
        case EAIActionType::Approach:
            if (Perception.DistanceToTarget > 250.0f)
                Score = 55.0f;
            break;
        case EAIActionType::Wait:
            Score = 10.0f;
            break;
        case EAIActionType::Grab:
            if (Perception.bIsTargetBlocking && Perception.DistanceToTarget < 150.0f)
                Score = 60.0f;
            break;
        case EAIActionType::Counter:
            if (Perception.bIsTargetAttacking && Perception.SelfStamina > 30.0f)
                Score = 50.0f + (Perception.DistanceToTarget < 100.0f ? 20.0f : 0.0f);
            break;
        case EAIActionType::SpecialMove:
            if (Perception.SelfStamina > 60.0f && Perception.DistanceToTarget < 200.0f)
                Score = 35.0f * (CurrentPersonality == EAIPersonalityType::Aggressive ? 1.5f : 1.0f);
            break;
        case EAIActionType::Jump:
            if (Perception.bIsTargetAttacking && Perception.DistanceToTarget < 100.0f)
                Score = 40.0f;
            break;
        case EAIActionType::Taunt:
            Score = 5.0f;
            break;
        }

        switch (CurrentDifficulty)
        {
        case EAIDifficulty::Easy:
            Score *= 0.5f;
            break;
        case EAIDifficulty::Normal:
            Score *= 1.0f;
            break;
        case EAIDifficulty::Hard:
            Score *= 1.5f;
            break;
        case EAIDifficulty::Expert:
            Score *= 2.0f;
            break;
        }

        switch (CurrentPersonality)
        {
        case EAIPersonalityType::Aggressive:
            if (Action == EAIActionType::LightAttack || Action == EAIActionType::HeavyAttack || Action == EAIActionType::Combo || Action == EAIActionType::SpecialMove)
                Score *= 1.3f;
            if (Action == EAIActionType::Block || Action == EAIActionType::Retreat)
                Score *= 0.6f;
            break;
        case EAIPersonalityType::Defensive:
            if (Action == EAIActionType::Block || Action == EAIActionType::Dodge || Action == EAIActionType::Counter)
                Score *= 1.3f;
            if (Action == EAIActionType::LightAttack || Action == EAIActionType::HeavyAttack)
                Score *= 0.7f;
            break;
        case EAIPersonalityType::Balanced:
            break;
        case EAIPersonalityType::Adaptive:
            if (Perception.SelfHealth < Perception.TargetHealth)
            {
                if (Action == EAIActionType::Block || Action == EAIActionType::Dodge)
                    Score *= 1.2f;
            }
            else
            {
                if (Action == EAIActionType::LightAttack || Action == EAIActionType::HeavyAttack)
                    Score *= 1.2f;
            }
            break;
        case EAIPersonalityType::Unpredictable:
            Score *= FMath::FRandRange(0.5f, 1.5f);
            break;
        }

        ActionScores.Add(Action, Score);
    }

    EAIActionType BestAction = EAIActionType::Wait;
    float BestScore = 0.0f;
    for (const auto& Entry : ActionScores)
    {
        if (Entry.Value > BestScore)
        {
            BestScore = Entry.Value;
            BestAction = Entry.Key;
        }
    }

    OutDecision.Action = BestAction;
    OutDecision.Score = BestScore;
    OutDecision.Confidence = FMath::Clamp(BestScore / 100.0f, 0.0f, 1.0f);
    OutDecision.Target = Perception.TargetActor;
    OutDecision.TargetLocation = Perception.TargetLocation;
    OutDecision.ReactionTime = 1.0f - (static_cast<int32>(CurrentDifficulty) * 0.25f);
    OutDecision.ResultingMode = Perception.CurrentState;

    LastDecision = OutDecision;
    DecisionHistory.Add(OutDecision);
    if (DecisionHistory.Num() > 100)
    {
        DecisionHistory.RemoveAt(0);
    }
}

void ULesFightAIDecisionManager::SetDifficulty(EAIDifficulty Difficulty)
{
    CurrentDifficulty = Difficulty;
}

EAIDifficulty ULesFightAIDecisionManager::GetDifficulty() const
{
    return CurrentDifficulty;
}

void ULesFightAIDecisionManager::SetPersonality(EAIPersonalityType Personality)
{
    CurrentPersonality = Personality;
}

void ULesFightAIDecisionManager::CancelCurrentDecision()
{
    LastDecision = FAIDecisionContext();
    ActionScores.Empty();
}

FAIDecisionContext ULesFightAIDecisionManager::GetLastDecision() const
{
    return LastDecision;
}

TArray<FAIDecisionContext> ULesFightAIDecisionManager::GetDecisionHistory() const
{
    return DecisionHistory;
}
