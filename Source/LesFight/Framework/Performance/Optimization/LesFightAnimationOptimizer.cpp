#include "Framework/Performance/Optimization/LesFightAnimationOptimizer.h"

void ULesFightAnimationOptimizer::Initialize()
{
	BlendRate = 60.0f;
	IKUpdateRate = 60.0f;
	MotionMatchingQuality = 1.0f;
	MaxActiveAnims = 10;
	bLODBlending = false;
	bMotionMatching = true;
	CurrentLevel = EPerformanceQualityLevel::High;
}

void ULesFightAnimationOptimizer::Shutdown()
{
}

void ULesFightAnimationOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	CurrentLevel = Level;

	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		BlendRate = 60.0f;
		IKUpdateRate = 60.0f;
		MaxActiveAnims = 10;
		bLODBlending = false;
		bMotionMatching = true;
		MotionMatchingQuality = 1.0f;
		break;

	case EPerformanceQualityLevel::High:
		BlendRate = 60.0f;
		IKUpdateRate = 30.0f;
		MaxActiveAnims = 8;
		bLODBlending = false;
		bMotionMatching = true;
		MotionMatchingQuality = 0.75f;
		break;

	case EPerformanceQualityLevel::Medium:
		BlendRate = 30.0f;
		IKUpdateRate = 15.0f;
		MaxActiveAnims = 5;
		bLODBlending = true;
		bMotionMatching = false;
		MotionMatchingQuality = 0.0f;
		break;

	case EPerformanceQualityLevel::Low:
		BlendRate = 15.0f;
		IKUpdateRate = 10.0f;
		MaxActiveAnims = 3;
		bLODBlending = true;
		bMotionMatching = false;
		MotionMatchingQuality = 0.0f;
		break;

	default:
		break;
	}
}

void ULesFightAnimationOptimizer::OptimizeAnimationBlueprints()
{
	UE_LOG(LogTemp, Log, TEXT("ULesFightAnimationOptimizer: Optimizing animation blueprints..."));
	UE_LOG(LogTemp, Log, TEXT("  Blend Rate: %.1f Hz"), BlendRate);
	UE_LOG(LogTemp, Log, TEXT("  IK Update Rate: %.1f Hz"), IKUpdateRate);
	UE_LOG(LogTemp, Log, TEXT("  LOD Blending: %s"), bLODBlending ? TEXT("Enabled") : TEXT("Disabled"));
	UE_LOG(LogTemp, Log, TEXT("  Max Active Animations: %d"), MaxActiveAnims);
	UE_LOG(LogTemp, Log, TEXT("  Motion Matching: %s"), bMotionMatching ? TEXT("Enabled") : TEXT("Disabled"));
}

void ULesFightAnimationOptimizer::SetBlendCalculationRate(float Rate)
{
	BlendRate = FMath::Clamp(Rate, 1.0f, 120.0f);
}

float ULesFightAnimationOptimizer::GetBlendCalculationRate() const
{
	return BlendRate;
}

void ULesFightAnimationOptimizer::EnableLODBlending(bool bEnabled)
{
	bLODBlending = bEnabled;

	if (bLODBlending)
	{
		UE_LOG(LogTemp, Log, TEXT("LOD-based animation blending enabled"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("LOD-based animation blending disabled"));
	}
}

void ULesFightAnimationOptimizer::SetMaxActiveAnimations(int32 Max)
{
	MaxActiveAnims = FMath::Clamp(Max, 1, 50);
}

int32 ULesFightAnimationOptimizer::GetMaxActiveAnimations() const
{
	return MaxActiveAnims;
}

void ULesFightAnimationOptimizer::OptimizeIKFrequency(float UpdateRate)
{
	IKUpdateRate = FMath::Clamp(UpdateRate, 1.0f, 120.0f);
}

void ULesFightAnimationOptimizer::OptimizeMotionMatching(bool bEnabled, float QualityScale)
{
	bMotionMatching = bEnabled;
	MotionMatchingQuality = FMath::Clamp(QualityScale, 0.0f, 1.0f);

	if (bMotionMatching)
	{
		UE_LOG(LogTemp, Log, TEXT("Motion matching enabled with quality scale: %.2f"), MotionMatchingQuality);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Motion matching disabled"));
	}
}

float ULesFightAnimationOptimizer::GetAnimationMemoryMB() const
{
	return 0.0f;
}

int32 ULesFightAnimationOptimizer::GetActiveAnimationCount() const
{
	return 0;
}

TArray<FString> ULesFightAnimationOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentLevel)));
	Status.Add(FString::Printf(TEXT("Blend Rate: %.1f Hz"), BlendRate));
	Status.Add(FString::Printf(TEXT("IK Update Rate: %.1f Hz"), IKUpdateRate));
	Status.Add(FString::Printf(TEXT("Max Active Animations: %d"), MaxActiveAnims));
	Status.Add(FString::Printf(TEXT("LOD Blending: %s"), bLODBlending ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Motion Matching: %s"), bMotionMatching ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Motion Matching Quality: %.2f"), MotionMatchingQuality));
	return Status;
}
