#include "Framework/FightingAI/Integration/LesFightAIPerformance.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"

void ULesFightAIPerformance::SetMaxAIUpdatesPerSecond(int32 Updates)
{
    MaxUpdatesPerSecond = FMath::Max(1, Updates);
}

int32 ULesFightAIPerformance::GetMaxAIUpdatesPerSecond() const
{
    return MaxUpdatesPerSecond;
}

void ULesFightAIPerformance::SetDecisionBudget(float Milliseconds)
{
    DecisionBudgetMs = FMath::Max(0.1f, Milliseconds);
}

float ULesFightAIPerformance::GetDecisionBudget() const
{
    return DecisionBudgetMs;
}

void ULesFightAIPerformance::OptimizeForMultipleAI(int32 Count)
{
    if (Count <= 0)
    {
        return;
    }

    float ReductionFactor = 1.0f / FMath::Sqrt(static_cast<float>(Count));
    MaxUpdatesPerSecond = FMath::Max(5, FMath::FloorToInt(20.0f * ReductionFactor));
    DecisionBudgetMs = FMath::Max(1.0f, 5.0f * ReductionFactor);
}

FString ULesFightAIPerformance::GetPerformanceReport() const
{
    FString Report;
    Report += FString::Printf(TEXT("Max Updates/s: %d\n"), MaxUpdatesPerSecond);
    Report += FString::Printf(TEXT("Decision Budget: %.2f ms\n"), DecisionBudgetMs);
    Report += FString::Printf(TEXT("Avg Decision Time: %.2f ms\n"), GetAverageDecisionTime());
    Report += FString::Printf(TEXT("Performance Score: %.2f\n"), PerformanceScore);
    Report += FString::Printf(TEXT("Profiling: %s\n"), bProfiling ? TEXT("Enabled") : TEXT("Disabled"));
    return Report;
}

void ULesFightAIPerformance::EnableProfiling(bool bInEnable)
{
    bProfiling = bInEnable;
}

float ULesFightAIPerformance::GetAverageDecisionTime() const
{
    if (DecisionTimes.Num() == 0)
    {
        return 0.0f;
    }

    float Sum = 0.0f;
    int32 Count = FMath::Min(DecisionTimes.Num(), 100);
    int32 StartIndex = DecisionTimes.Num() - Count;

    for (int32 i = StartIndex; i < DecisionTimes.Num(); ++i)
    {
        Sum += DecisionTimes[i];
    }

    return Sum / static_cast<float>(Count);
}

float ULesFightAIPerformance::GetPerformanceScore() const
{
    if (DecisionBudgetMs <= 0.0f)
    {
        return 0.0f;
    }

    float AvgTime = GetAverageDecisionTime();
    float Ratio = AvgTime / DecisionBudgetMs;

    if (Ratio <= 0.5f)
    {
        return 100.0f;
    }
    else if (Ratio <= 0.75f)
    {
        return 75.0f;
    }
    else if (Ratio <= 1.0f)
    {
        return 50.0f;
    }

    return FMath::Max(0.0f, 50.0f - (Ratio - 1.0f) * 50.0f);
}

void ULesFightAIPerformance::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;
    DecisionTimes.Reserve(100);
}
