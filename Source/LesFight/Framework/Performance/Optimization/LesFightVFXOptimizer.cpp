#include "Framework/Performance/Optimization/LesFightVFXOptimizer.h"

void ULesFightVFXOptimizer::Initialize()
{
	MaxParticleCount = 10000;
	MaxNiagaraSystemCount = 50;
	DecalLimit = 100;
	CullDistance = 5000.0f;
	bScreenEffects = true;
	bDistanceCulling = false;
	CurrentLevel = EPerformanceQualityLevel::High;
}

void ULesFightVFXOptimizer::Shutdown()
{
}

void ULesFightVFXOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	CurrentLevel = Level;

	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		MaxParticleCount = 50000;
		MaxNiagaraSystemCount = 100;
		DecalLimit = 200;
		CullDistance = 10000.0f;
		bScreenEffects = true;
		bDistanceCulling = false;
		break;

	case EPerformanceQualityLevel::High:
		MaxParticleCount = 20000;
		MaxNiagaraSystemCount = 50;
		DecalLimit = 100;
		CullDistance = 7500.0f;
		bScreenEffects = true;
		bDistanceCulling = false;
		break;

	case EPerformanceQualityLevel::Medium:
		MaxParticleCount = 5000;
		MaxNiagaraSystemCount = 25;
		DecalLimit = 50;
		CullDistance = 5000.0f;
		bScreenEffects = false;
		bDistanceCulling = true;
		break;

	case EPerformanceQualityLevel::Low:
		MaxParticleCount = 1000;
		MaxNiagaraSystemCount = 10;
		DecalLimit = 25;
		CullDistance = 2500.0f;
		bScreenEffects = false;
		bDistanceCulling = true;
		break;

	default:
		break;
	}
}

void ULesFightVFXOptimizer::SetMaxParticleCount(int32 Count)
{
	MaxParticleCount = FMath::Clamp(Count, 100, 100000);
}

int32 ULesFightVFXOptimizer::GetMaxParticleCount() const
{
	return MaxParticleCount;
}

void ULesFightVFXOptimizer::SetMaxNiagaraSystems(int32 Count)
{
	MaxNiagaraSystemCount = FMath::Clamp(Count, 1, 200);
}

int32 ULesFightVFXOptimizer::GetMaxNiagaraSystems() const
{
	return MaxNiagaraSystemCount;
}

void ULesFightVFXOptimizer::EnableScreenEffects(bool bEnable)
{
	bScreenEffects = bEnable;

	if (bScreenEffects)
	{
		UE_LOG(LogTemp, Log, TEXT("Screen-space VFX effects enabled"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Screen-space VFX effects disabled"));
	}
}

void ULesFightVFXOptimizer::EnableDistanceCulling(bool bEnable)
{
	bDistanceCulling = bEnable;

	if (bDistanceCulling)
	{
		UE_LOG(LogTemp, Log, TEXT("VFX distance culling enabled at %.1f units"), CullDistance);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("VFX distance culling disabled"));
	}
}

void ULesFightVFXOptimizer::SetCullDistance(float Distance)
{
	CullDistance = FMath::Max(1000.0f, Distance);
}

void ULesFightVFXOptimizer::SetDecalLimit(int32 Count)
{
	DecalLimit = FMath::Clamp(Count, 0, 500);
}

int32 ULesFightVFXOptimizer::GetDecalLimit() const
{
	return DecalLimit;
}

void ULesFightVFXOptimizer::OptimizeNiagaraEffects()
{
	UE_LOG(LogTemp, Log, TEXT("ULesFightVFXOptimizer: Optimizing Niagara effects..."));
	UE_LOG(LogTemp, Log, TEXT("  Max Particles: %d"), MaxParticleCount);
	UE_LOG(LogTemp, Log, TEXT("  Max Niagara Systems: %d"), MaxNiagaraSystemCount);
	UE_LOG(LogTemp, Log, TEXT("  Decal Limit: %d"), DecalLimit);
	UE_LOG(LogTemp, Log, TEXT("  Cull Distance: %.1f"), CullDistance);
	UE_LOG(LogTemp, Log, TEXT("  Screen Effects: %s"), bScreenEffects ? TEXT("Enabled") : TEXT("Disabled"));
	UE_LOG(LogTemp, Log, TEXT("  Distance Culling: %s"), bDistanceCulling ? TEXT("Enabled") : TEXT("Disabled"));
}

int32 ULesFightVFXOptimizer::GetActiveVFXCount() const
{
	return 0;
}

float ULesFightVFXOptimizer::GetVFXMemoryMB() const
{
	return 0.0f;
}

TArray<FString> ULesFightVFXOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentLevel)));
	Status.Add(FString::Printf(TEXT("Max Particles: %d"), MaxParticleCount));
	Status.Add(FString::Printf(TEXT("Max Niagara Systems: %d"), MaxNiagaraSystemCount));
	Status.Add(FString::Printf(TEXT("Decal Limit: %d"), DecalLimit));
	Status.Add(FString::Printf(TEXT("Cull Distance: %.1f"), CullDistance));
	Status.Add(FString::Printf(TEXT("Screen Effects: %s"), bScreenEffects ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Distance Culling: %s"), bDistanceCulling ? TEXT("Enabled") : TEXT("Disabled")));
	return Status;
}
