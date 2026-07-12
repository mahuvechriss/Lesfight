#include "LesFightAIBehaviorTree.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"

void ULesFightAIBehaviorTree::Evaluate(const FAIPerceptionData& Perception, FAIDecisionContext& Decision)
{
    EvaluationLog.Empty();

    TArray<FAIDecisionContext> Candidates;

    static const EAIActionType ActionTypes[] = {
        EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::Block,
        EAIActionType::Dodge, EAIActionType::Dash, EAIActionType::Jump,
        EAIActionType::SpecialMove, EAIActionType::Grab, EAIActionType::Counter,
        EAIActionType::Retreat, EAIActionType::Approach, EAIActionType::Wait,
        EAIActionType::Combo, EAIActionType::Taunt
    };

    for (EAIActionType Action : ActionTypes)
    {
        float BaseScore = 0.0f;
        float* ProfileWeight = CurrentProfile.ActionWeights.Find(Action);
        float WeightMultiplier = ProfileWeight ? *ProfileWeight : 1.0f;

        switch (Action)
        {
        case EAIActionType::LightAttack:
            BaseScore = Perception.DistanceToTarget < 200.0f ? 60.0f : 10.0f;
            break;
        case EAIActionType::HeavyAttack:
            BaseScore = Perception.DistanceToTarget < 150.0f ? 50.0f : 5.0f;
            break;
        case EAIActionType::Block:
            BaseScore = Perception.bIsTargetAttacking ? 70.0f : 15.0f;
            break;
        case EAIActionType::Dodge:
            BaseScore = Perception.bIsTargetAttacking ? 65.0f : 20.0f;
            break;
        case EAIActionType::Dash:
            BaseScore = Perception.DistanceToTarget > 300.0f ? 55.0f : 10.0f;
            break;
        case EAIActionType::Combo:
            BaseScore = (Perception.DistanceToTarget < 200.0f && Perception.SelfStamina > 50.0f) ? 50.0f : 0.0f;
            break;
        case EAIActionType::Retreat:
            BaseScore = Perception.SelfHealth < 25.0f ? 75.0f : 5.0f;
            break;
        case EAIActionType::Approach:
            BaseScore = Perception.DistanceToTarget > 250.0f ? 50.0f : 5.0f;
            break;
        case EAIActionType::Wait:
            BaseScore = 10.0f;
            break;
        case EAIActionType::Grab:
            BaseScore = (Perception.bIsTargetBlocking && Perception.DistanceToTarget < 150.0f) ? 60.0f : 5.0f;
            break;
        case EAIActionType::Counter:
            BaseScore = (Perception.bIsTargetAttacking && Perception.SelfStamina > 30.0f) ? 55.0f : 0.0f;
            break;
        case EAIActionType::SpecialMove:
            BaseScore = Perception.SelfStamina > 60.0f ? 40.0f : 0.0f;
            break;
        case EAIActionType::Jump:
            BaseScore = 15.0f;
            break;
        case EAIActionType::Taunt:
            BaseScore = 2.0f;
            break;
        }

        float FinalScore = BaseScore * WeightMultiplier * CurrentDifficultySettings.DecisionAccuracy;
        FinalScore += FMath::FRand() * CurrentDifficultySettings.ErrorRate * -10.0f;

        FAIDecisionContext Candidate;
        Candidate.Action = Action;
        Candidate.Score = FinalScore;
        Candidate.Confidence = FMath::Clamp(FinalScore / 100.0f, 0.0f, 1.0f);
        Candidate.ReactionTime = CurrentDifficultySettings.ReactionSpeed;
        Candidates.Add(Candidate);

        const UEnum* EnumPtr = StaticEnum<EAIActionType>();
        if (EnumPtr)
        {
            FString ActionName = EnumPtr->GetNameStringByValue(static_cast<int64>(Action));
            EvaluationLog.Add(FString::Printf(TEXT("%s: Score=%.2f"), *ActionName, FinalScore));
        }
    }

    Decision = SelectNode(Candidates);
    SelectedNode = Decision;
}

FAIDecisionContext ULesFightAIBehaviorTree::SelectNode(const TArray<FAIDecisionContext>& Candidates)
{
    if (Candidates.Num() == 0)
    {
        return FAIDecisionContext();
    }

    FAIDecisionContext Best;
    for (const FAIDecisionContext& Candidate : Candidates)
    {
        if (Candidate.Score > Best.Score)
        {
            Best = Candidate;
        }
    }
    return Best;
}

FAIDecisionContext ULesFightAIBehaviorTree::GetSelectedNode() const
{
    return SelectedNode;
}

void ULesFightAIBehaviorTree::SetBehaviorProfile(const FAIStyleBehaviorProfile& Profile)
{
    CurrentProfile = Profile;
}

void ULesFightAIBehaviorTree::SetDifficultyProfile(const FAIDifficultySettings& Settings)
{
    CurrentDifficultySettings = Settings;
}
