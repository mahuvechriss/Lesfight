#include "Framework/FightingAI/Learning/LesFightAIAdaptiveLearning.h"

ULesFightAIAdaptiveLearning::ULesFightAIAdaptiveLearning()
{
    LearningRate = 0.1f;
    AdaptationsPerformed = 0;
    LastAdaptationTime = 0.0f;
}

void ULesFightAIAdaptiveLearning::ObservePlayerAction(EAIActionType Action)
{
    if (Action == EAIActionType::None || Action == EAIActionType::MAX)
    {
        return;
    }

    int32* Count = AdaptiveData.PlayerActionFrequency.Find(Action);
    if (Count)
    {
        (*Count)++;
    }
    else
    {
        AdaptiveData.PlayerActionFrequency.Add(Action, 1);
    }

    RecentActions.Add(Action);
    if (RecentActions.Num() > 50)
    {
        RecentActions.RemoveAt(0);
    }
}

void ULesFightAIAdaptiveLearning::ObservePlayerCombo(FName ComboName)
{
    if (ComboName == NAME_None)
    {
        return;
    }

    int32* Count = AdaptiveData.PlayerComboFrequency.Find(ComboName);
    if (Count)
    {
        (*Count)++;
    }
    else
    {
        AdaptiveData.PlayerComboFrequency.Add(ComboName, 1);
    }

    RecentCombos.Add(ComboName);
    if (RecentCombos.Num() > 30)
    {
        RecentCombos.RemoveAt(0);
    }
}

void ULesFightAIAdaptiveLearning::AnalyzePatterns()
{
    if (RecentActions.Num() == 0)
    {
        return;
    }

    int32 TotalActions = 0;
    int32 AttackCount = 0;
    int32 DefenseCount = 0;

    TMap<EAIActionType, int32> RecentFrequency;
    for (EAIActionType Action : RecentActions)
    {
        int32* Count = RecentFrequency.Find(Action);
        if (Count)
        {
            (*Count)++;
        }
        else
        {
            RecentFrequency.Add(Action, 1);
        }
        TotalActions++;

        switch (Action)
        {
        case EAIActionType::LightAttack:
        case EAIActionType::HeavyAttack:
        case EAIActionType::ComboAttack:
        case EAIActionType::SpecialMove:
        case EAIActionType::UltimateAttack:
        case EAIActionType::Grab:
        case EAIActionType::Throw:
            AttackCount++;
            break;
        case EAIActionType::Block:
        case EAIActionType::Dodge:
        case EAIActionType::Parry:
        case EAIActionType::Counter:
        case EAIActionType::StepBack:
            DefenseCount++;
            break;
        }
    }

    AdaptiveData.PlayerAggressionScore = TotalActions > 0 ? (float)AttackCount / (float)TotalActions : 0.0f;
    AdaptiveData.PlayerDefenseScore = TotalActions > 0 ? (float)DefenseCount / (float)TotalActions : 0.0f;
    AdaptiveData.FightsAnalyzed++;
}

EAIActionType ULesFightAIAdaptiveLearning::GetPlayerFavoriteAction() const
{
    EAIActionType Favorite = EAIActionType::None;
    int32 HighestCount = 0;

    for (const auto& Entry : AdaptiveData.PlayerActionFrequency)
    {
        if (Entry.Value > HighestCount)
        {
            HighestCount = Entry.Value;
            Favorite = Entry.Key;
        }
    }

    return Favorite;
}

FName ULesFightAIAdaptiveLearning::GetPlayerFavoriteCombo() const
{
    FName Favorite = NAME_None;
    int32 HighestCount = 0;

    for (const auto& Entry : AdaptiveData.PlayerComboFrequency)
    {
        if (Entry.Value > HighestCount)
        {
            HighestCount = Entry.Value;
            Favorite = Entry.Key;
        }
    }

    return Favorite;
}

bool ULesFightAIAdaptiveLearning::ShouldAdaptStrategy() const
{
    if (RecentActions.Num() < 5)
    {
        return false;
    }

    return true;
}

void ULesFightAIAdaptiveLearning::AdaptStrategy(FAIDecisionContext& Decision)
{
    EAIActionType FavoriteAction = GetPlayerFavoriteAction();
    if (FavoriteAction == EAIActionType::None)
    {
        return;
    }

    switch (FavoriteAction)
    {
    case EAIActionType::LightAttack:
    case EAIActionType::HeavyAttack:
        Decision.ChosenAction = EAIActionType::Block;
        Decision.Priority = EAIDecisionPriority::High;
        Decision.ActionScore = 0.8f;
        Decision.ReasoningLog.Add(TEXT("Player favors attacking: prioritizing block and counter."));
        break;

    case EAIActionType::ComboAttack:
        Decision.ChosenAction = EAIActionType::Dodge;
        Decision.Priority = EAIDecisionPriority::High;
        Decision.ActionScore = 0.75f;
        Decision.ReasoningLog.Add(TEXT("Player favors combos: prioritizing dodge to evade strings."));
        break;

    case EAIActionType::Grab:
    case EAIActionType::Throw:
        Decision.ChosenAction = EAIActionType::Dodge;
        Decision.Priority = EAIDecisionPriority::High;
        Decision.ActionScore = 0.85f;
        Decision.ReasoningLog.Add(TEXT("Player favors grabs: prioritizing dodge to avoid throws."));
        break;

    case EAIActionType::Block:
        Decision.ChosenAction = EAIActionType::Grab;
        Decision.Priority = EAIDecisionPriority::Medium;
        Decision.ActionScore = 0.7f;
        Decision.ReasoningLog.Add(TEXT("Player favors blocking: using grabs to break defense."));
        break;

    case EAIActionType::Dodge:
        Decision.ChosenAction = EAIActionType::LightAttack;
        Decision.Priority = EAIDecisionPriority::Medium;
        Decision.ActionScore = 0.65f;
        Decision.ReasoningLog.Add(TEXT("Player favors dodging: using quick attacks to catch recovery."));
        break;

    default:
        break;
    }

    AdaptationsPerformed++;
}

void ULesFightAIAdaptiveLearning::ResetLearning()
{
    AdaptiveData = FAIAdaptiveData();
    RecentActions.Empty();
    RecentCombos.Empty();
    AdaptationsPerformed = 0;
    LastAdaptationTime = 0.0f;
}
