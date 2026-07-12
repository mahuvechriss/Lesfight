#include "Framework/Performance/Optimization/LesFightPhysicsOptimizer.h"

void ULesFightPhysicsOptimizer::Initialize()
{
}

void ULesFightPhysicsOptimizer::Shutdown()
{
}

void ULesFightPhysicsOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	CurrentLevel = Level;

	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		bClothEnabled = true;
		bHairEnabled = true;
		PhysicsSubsteps = 4;
		MaxDestructibles = 20;
		bAsyncPhysics = true;
		CollisionComplexity = ECollisionComplexity::Full;
		break;

	case EPerformanceQualityLevel::High:
		bClothEnabled = true;
		bHairEnabled = true;
		PhysicsSubsteps = 2;
		MaxDestructibles = 10;
		bAsyncPhysics = true;
		CollisionComplexity = ECollisionComplexity::Reduced;
		break;

	case EPerformanceQualityLevel::Medium:
		bClothEnabled = false;
		bHairEnabled = true;
		PhysicsSubsteps = 1;
		MaxDestructibles = 5;
		bAsyncPhysics = false;
		CollisionComplexity = ECollisionComplexity::Simplified;
		break;

	case EPerformanceQualityLevel::Low:
		bClothEnabled = false;
		bHairEnabled = false;
		PhysicsSubsteps = 1;
		MaxDestructibles = 2;
		bAsyncPhysics = false;
		CollisionComplexity = ECollisionComplexity::Simplified;
		break;

	default:
		break;
	}
}

void ULesFightPhysicsOptimizer::EnableClothPhysics(bool bEnable)
{
	bClothEnabled = bEnable;
}

void ULesFightPhysicsOptimizer::EnableHairPhysics(bool bEnable)
{
	bHairEnabled = bEnable;
}

void ULesFightPhysicsOptimizer::SetPhysicsSubstepCount(int32 Count)
{
	PhysicsSubsteps = Count;
}

int32 ULesFightPhysicsOptimizer::GetPhysicsSubstepCount() const
{
	return PhysicsSubsteps;
}

void ULesFightPhysicsOptimizer::SetMaxDestructibleObjects(int32 Count)
{
	MaxDestructibles = Count;
}

int32 ULesFightPhysicsOptimizer::GetMaxDestructibleObjects() const
{
	return MaxDestructibles;
}

void ULesFightPhysicsOptimizer::EnableAsyncPhysics(bool bEnable)
{
	bAsyncPhysics = bEnable;
}

void ULesFightPhysicsOptimizer::SetCollisionComplexity(ECollisionComplexity Complexity)
{
	CollisionComplexity = Complexity;
}

int32 ULesFightPhysicsOptimizer::GetActivePhysicsBodies() const
{
	return 0;
}

TArray<FString> ULesFightPhysicsOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentLevel)));
	Status.Add(FString::Printf(TEXT("Cloth Physics: %s"), bClothEnabled ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Hair Physics: %s"), bHairEnabled ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Physics Substeps: %d"), PhysicsSubsteps));
	Status.Add(FString::Printf(TEXT("Max Destructibles: %d"), MaxDestructibles));
	Status.Add(FString::Printf(TEXT("Async Physics: %s"), bAsyncPhysics ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Collision Complexity: %d"), static_cast<int32>(CollisionComplexity)));
	return Status;
}
