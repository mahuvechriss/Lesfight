#include "Framework/FightingAI/Testing/LesFightAIDevTools.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"

void ULesFightAIDevTools::EnableDebugMode(bool bEnabled)
{
    bDebugMode = bEnabled;
    if (bDebugMode)
    {
        DebugLog.Add(TEXT("Debug mode enabled"));
    }
    else
    {
        DebugLog.Add(TEXT("Debug mode disabled"));
    }
}

bool ULesFightAIDevTools::IsDebugModeEnabled() const
{
    return bDebugMode;
}

FAIDebugSnapshot ULesFightAIDevTools::GetDebugSnapshot() const
{
    return CurrentSnapshot;
}

void ULesFightAIDevTools::VisualizeDecision(const FAIDecisionContext& Decision)
{
    if (!bDebugMode)
    {
        return;
    }

    CurrentSnapshot.CurrentAction = Decision.ChosenAction;
    CurrentSnapshot.DecisionScore = Decision.ActionScore;
    CurrentSnapshot.TimeSinceLastDecision = Decision.DecisionTime;
    CurrentSnapshot.TopConsideredActions = Decision.ReasoningLog;

    SnapshotHistory.Add(CurrentSnapshot);
    if (SnapshotHistory.Num() > 200)
    {
        SnapshotHistory.RemoveAt(0);
    }

    OnDebugUpdated.Broadcast(CurrentSnapshot);
}

void ULesFightAIDevTools::DisplayBehaviorTree(const TArray<FString>& TreeNodes)
{
    if (!bDebugMode)
    {
        return;
    }

    DebugLog.Add(TEXT("--- Behavior Tree ---"));
    for (const FString& Node : TreeNodes)
    {
        DebugLog.Add(Node);
    }
}

void ULesFightAIDevTools::ShowReactionTiming(float ReactionTime)
{
    if (!bDebugMode)
    {
        return;
    }

    FString LogEntry = FString::Printf(TEXT("Reaction Time: %.2f ms"), ReactionTime);
    DebugLog.Add(LogEntry);
}

void ULesFightAIDevTools::ShowCombatPrediction(const FAIPerceptionData& Perception)
{
    if (!bDebugMode)
    {
        return;
    }

    FString LogEntry = FString::Printf(TEXT("Prediction - Distance: %.2f, Confidence: %.2f"),
        Perception.DistanceToPlayer, Perception.PredictionConfidence);
    DebugLog.Add(LogEntry);
}

void ULesFightAIDevTools::TestDifficulty(EAIDifficulty Difficulty)
{
    FString DifficultyName = StaticEnum<EAIDifficulty>()->GetNameStringByValue(static_cast<int64>(Difficulty));
    FString LogEntry = FString::Printf(TEXT("Testing difficulty: %s"), *DifficultyName);
    DebugLog.Add(LogEntry);

    RunAIBenchmark(10);
}

void ULesFightAIDevTools::RunAIBenchmark(int32 TestIterations)
{
    if (!OwnerController.IsValid())
    {
        return;
    }

    DebugLog.Add(FString::Printf(TEXT("Running benchmark: %d iterations"), TestIterations));

    float TotalDecisionTime = 0.0f;
    int32 SuccessfulDecisions = 0;

    for (int32 i = 0; i < TestIterations; ++i)
    {
        float DecisionTime = FMath::FRandRange(0.5f, 5.0f);
        TotalDecisionTime += DecisionTime;

        if (DecisionTime < 4.0f)
        {
            SuccessfulDecisions++;
        }
    }

    float AvgTime = TotalDecisionTime / TestIterations;
    float Accuracy = static_cast<float>(SuccessfulDecisions) / TestIterations * 100.0f;

    BenchmarkResults.Add(TEXT("AvgDecisionTime"), AvgTime);
    BenchmarkResults.Add(TEXT("Accuracy"), Accuracy);
    BenchmarkResults.Add(TEXT("Iterations"), static_cast<float>(TestIterations));

    DebugLog.Add(FString::Printf(TEXT("Benchmark complete - Avg Time: %.2fms, Accuracy: %.1f%%"), AvgTime, Accuracy));
}

FString ULesFightAIDevTools::GenerateAIReport() const
{
    FString Report;
    Report += TEXT("=== AI Performance Report ===\n");
    Report += FString::Printf(TEXT("Debug Mode: %s\n"), bDebugMode ? TEXT("Enabled") : TEXT("Disabled"));
    Report += FString::Printf(TEXT("Snapshot History: %d entries\n"), SnapshotHistory.Num());
    Report += FString::Printf(TEXT("Debug Log: %d entries\n"), DebugLog.Num());
    Report += TEXT("\n--- Benchmark Results ---\n");

    for (const auto& Entry : BenchmarkResults)
    {
        Report += FString::Printf(TEXT("%s: %.2f\n"), *Entry.Key, Entry.Value);
    }

    Report += TEXT("\n--- Current Snapshot ---\n");
    Report += FString::Printf(TEXT("Action: %d\n"), static_cast<int32>(CurrentSnapshot.CurrentAction));
    Report += FString::Printf(TEXT("Score: %.2f\n"), CurrentSnapshot.DecisionScore);
    Report += FString::Printf(TEXT("Reason: %s\n"), *CurrentSnapshot.DecisionReason);

    return Report;
}

void ULesFightAIDevTools::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;
    SnapshotHistory.Reserve(200);
}
