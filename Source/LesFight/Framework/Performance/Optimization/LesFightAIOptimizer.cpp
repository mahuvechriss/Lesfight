#include "Framework/Performance/Optimization/LesFightAIOptimizer.h"

void ULesFightAIOptimizer::Initialize()
{
}

void ULesFightAIOptimizer::Shutdown()
{
}

void ULesFightAIOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	CurrentLevel = Level;

	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		DecisionFreq = 60.0f;
		PerceptionRate = 60.0f;
		MaxAIControllers = 8;
		MaxPerceptionUpdatesPerFrame = 10;
		bBehaviorTreeOpt = true;
		bAsyncPathfinding = true;
		break;

	case EPerformanceQualityLevel::High:
		DecisionFreq = 30.0f;
		PerceptionRate = 30.0f;
		MaxAIControllers = 4;
		MaxPerceptionUpdatesPerFrame = 5;
		bBehaviorTreeOpt = true;
		bAsyncPathfinding = true;
		break;

	case EPerformanceQualityLevel::Medium:
		DecisionFreq = 15.0f;
		PerceptionRate = 15.0f;
		MaxAIControllers = 2;
		MaxPerceptionUpdatesPerFrame = 3;
		bBehaviorTreeOpt = true;
		bAsyncPathfinding = true;
		break;

	case EPerformanceQualityLevel::Low:
		DecisionFreq = 10.0f;
		PerceptionRate = 10.0f;
		MaxAIControllers = 2;
		MaxPerceptionUpdatesPerFrame = 2;
		bBehaviorTreeOpt = false;
		bAsyncPathfinding = false;
		break;

	default:
		break;
	}
}

void ULesFightAIOptimizer::SetDecisionFrequency(float Hz)
{
	DecisionFreq = Hz;
}

float ULesFightAIOptimizer::GetDecisionFrequency() const
{
	return DecisionFreq;
}

void ULesFightAIOptimizer::SetPerceptionUpdateRate(float Hz)
{
	PerceptionRate = Hz;
}

void ULesFightAIOptimizer::EnableBehaviorTreeOptimization(bool bEnable)
{
	bBehaviorTreeOpt = bEnable;
}

void ULesFightAIOptimizer::SetMaxAIControllers(int32 Count)
{
	MaxAIControllers = Count;
}

int32 ULesFightAIOptimizer::GetMaxAIControllers() const
{
	return MaxAIControllers;
}

void ULesFightAIOptimizer::SetMaxPerceptionUpdates(int32 Count)
{
	MaxPerceptionUpdatesPerFrame = Count;
}

void ULesFightAIOptimizer::EnableAsyncPathfinding(bool bEnable)
{
	bAsyncPathfinding = bEnable;
}

int32 ULesFightAIOptimizer::GetActiveAICount() const
{
	return 0;
}

float ULesFightAIOptimizer::GetAverageDecisionTimeMs() const
{
	return 0.0f;
}

TArray<FString> ULesFightAIOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentLevel)));
	Status.Add(FString::Printf(TEXT("Decision Frequency: %.1f Hz"), DecisionFreq));
	Status.Add(FString::Printf(TEXT("Perception Rate: %.1f Hz"), PerceptionRate));
	Status.Add(FString::Printf(TEXT("Max AI Controllers: %d"), MaxAIControllers));
	Status.Add(FString::Printf(TEXT("Max Perception Updates/Frame: %d"), MaxPerceptionUpdatesPerFrame));
	Status.Add(FString::Printf(TEXT("Behavior Tree Optimization: %s"), bBehaviorTreeOpt ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Async Pathfinding: %s"), bAsyncPathfinding ? TEXT("Enabled") : TEXT("Disabled")));
	return Status;
}
