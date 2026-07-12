#include "Framework/FightingAI/Style/LesFightAIDifficultyManager.h"

ULesFightAIDifficultyManager::ULesFightAIDifficultyManager()
{
    CurrentDifficulty = EAIDifficulty::Normal;
    PlayerWinRateTracking = 0.5f;

    FAIDifficultySettings Easy;
    Easy.Difficulty = EAIDifficulty::Easy;
    Easy.ReactionTimeMin = 0.5f;
    Easy.ReactionTimeMax = 0.8f;
    Easy.DecisionSpeed = 0.6f;
    Easy.BlockChance = 0.3f;
    Easy.DodgeChance = 0.2f;
    Easy.ParryChance = 0.1f;
    Easy.CounterChance = 0.15f;
    Easy.ComboAccuracy = 0.3f;
    Easy.DamageMultiplier = 0.7f;
    Easy.DefenseMultiplier = 0.8f;
    Easy.AggressionModifier = 0.4f;
    Easy.PredictionAccuracy = 0.2f;
    Easy.MaxComboLength = 2;
    Easy.MistakeChance = 0.3f;
    Easy.LearningRate = 0.05f;
    Presets.Add(EAIDifficulty::Easy, Easy);

    FAIDifficultySettings Normal;
    Normal.Difficulty = EAIDifficulty::Normal;
    Normal.ReactionTimeMin = 0.3f;
    Normal.ReactionTimeMax = 0.5f;
    Normal.DecisionSpeed = 0.75f;
    Normal.BlockChance = 0.5f;
    Normal.DodgeChance = 0.3f;
    Normal.ParryChance = 0.2f;
    Normal.CounterChance = 0.3f;
    Normal.ComboAccuracy = 0.5f;
    Normal.DamageMultiplier = 1.0f;
    Normal.DefenseMultiplier = 1.0f;
    Normal.AggressionModifier = 0.6f;
    Normal.PredictionAccuracy = 0.4f;
    Normal.MaxComboLength = 3;
    Normal.MistakeChance = 0.15f;
    Normal.LearningRate = 0.1f;
    Presets.Add(EAIDifficulty::Normal, Normal);

    FAIDifficultySettings Hard;
    Hard.Difficulty = EAIDifficulty::Hard;
    Hard.ReactionTimeMin = 0.2f;
    Hard.ReactionTimeMax = 0.3f;
    Hard.DecisionSpeed = 0.85f;
    Hard.BlockChance = 0.7f;
    Hard.DodgeChance = 0.5f;
    Hard.ParryChance = 0.4f;
    Hard.CounterChance = 0.5f;
    Hard.ComboAccuracy = 0.7f;
    Hard.DamageMultiplier = 1.2f;
    Hard.DefenseMultiplier = 1.15f;
    Hard.AggressionModifier = 0.7f;
    Hard.PredictionAccuracy = 0.6f;
    Hard.MaxComboLength = 4;
    Hard.MistakeChance = 0.08f;
    Hard.LearningRate = 0.15f;
    Presets.Add(EAIDifficulty::Hard, Hard);

    FAIDifficultySettings Expert;
    Expert.Difficulty = EAIDifficulty::Expert;
    Expert.ReactionTimeMin = 0.1f;
    Expert.ReactionTimeMax = 0.2f;
    Expert.DecisionSpeed = 0.92f;
    Expert.BlockChance = 0.85f;
    Expert.DodgeChance = 0.7f;
    Expert.ParryChance = 0.6f;
    Expert.CounterChance = 0.7f;
    Expert.ComboAccuracy = 0.85f;
    Expert.DamageMultiplier = 1.4f;
    Expert.DefenseMultiplier = 1.3f;
    Expert.AggressionModifier = 0.8f;
    Expert.PredictionAccuracy = 0.8f;
    Expert.MaxComboLength = 5;
    Expert.MistakeChance = 0.03f;
    Expert.LearningRate = 0.2f;
    Presets.Add(EAIDifficulty::Expert, Expert);

    FAIDifficultySettings Master;
    Master.Difficulty = EAIDifficulty::Master;
    Master.ReactionTimeMin = 0.05f;
    Master.ReactionTimeMax = 0.1f;
    Master.DecisionSpeed = 0.98f;
    Master.BlockChance = 0.95f;
    Master.DodgeChance = 0.85f;
    Master.ParryChance = 0.75f;
    Master.CounterChance = 0.85f;
    Master.ComboAccuracy = 0.95f;
    Master.DamageMultiplier = 1.6f;
    Master.DefenseMultiplier = 1.5f;
    Master.AggressionModifier = 0.9f;
    Master.PredictionAccuracy = 0.95f;
    Master.MaxComboLength = 6;
    Master.MistakeChance = 0.01f;
    Master.LearningRate = 0.25f;
    Presets.Add(EAIDifficulty::Master, Master);

    SetDifficulty(EAIDifficulty::Normal);
}

void ULesFightAIDifficultyManager::SetDifficulty(EAIDifficulty Difficulty)
{
    if (Presets.Contains(Difficulty))
    {
        CurrentDifficulty = Difficulty;
        CurrentSettings = Presets[Difficulty];
    }
}

void ULesFightAIDifficultyManager::AdjustForPerformance(float PlayerWinRate)
{
    PlayerWinRateTracking = PlayerWinRate;

    if (PlayerWinRate > 0.7f)
    {
        float Scale = FMath::Min((PlayerWinRate - 0.7f) / 0.3f, 1.0f);
        CurrentSettings.ReactionTimeMin = FMath::Max(CurrentSettings.ReactionTimeMin - 0.05f * Scale, 0.01f);
        CurrentSettings.ReactionTimeMax = FMath::Max(CurrentSettings.ReactionTimeMax - 0.05f * Scale, 0.02f);
        CurrentSettings.BlockChance = FMath::Min(CurrentSettings.BlockChance + 0.05f * Scale, 1.0f);
        CurrentSettings.DodgeChance = FMath::Min(CurrentSettings.DodgeChance + 0.04f * Scale, 1.0f);
        CurrentSettings.MistakeChance = FMath::Max(CurrentSettings.MistakeChance - 0.02f * Scale, 0.0f);
    }
    else if (PlayerWinRate < 0.3f)
    {
        float Scale = FMath::Min((0.3f - PlayerWinRate) / 0.3f, 1.0f);
        CurrentSettings.ReactionTimeMin = FMath::Min(CurrentSettings.ReactionTimeMin + 0.05f * Scale, 1.0f);
        CurrentSettings.ReactionTimeMax = FMath::Min(CurrentSettings.ReactionTimeMax + 0.05f * Scale, 1.5f);
        CurrentSettings.BlockChance = FMath::Max(CurrentSettings.BlockChance - 0.05f * Scale, 0.0f);
        CurrentSettings.DodgeChance = FMath::Max(CurrentSettings.DodgeChance - 0.04f * Scale, 0.0f);
        CurrentSettings.MistakeChance = FMath::Min(CurrentSettings.MistakeChance + 0.02f * Scale, 1.0f);
    }
}

float ULesFightAIDifficultyManager::GetReactionTime() const
{
    return FMath::FRandRange(CurrentSettings.ReactionTimeMin, CurrentSettings.ReactionTimeMax);
}

FString ULesFightAIDifficultyManager::GetDifficultyName() const
{
    switch (CurrentDifficulty)
    {
    case EAIDifficulty::Easy:
        return TEXT("Easy");
    case EAIDifficulty::Normal:
        return TEXT("Normal");
    case EAIDifficulty::Hard:
        return TEXT("Hard");
    case EAIDifficulty::Expert:
        return TEXT("Expert");
    case EAIDifficulty::Master:
        return TEXT("Master");
    default:
        return TEXT("Unknown");
    }
}
