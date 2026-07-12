#include "LesFightCharacterOptimizer.h"

void ULesFightCharacterOptimizer::Initialize()
{
	LODBias = 0;
	CullDistance = 5000.0f;
	bSkeletonOptimized = false;
	bCullingEnabled = false;
	bInstancedMaterials = false;
	MaxActiveCharacters = 2;
	CurrentLevel = EPerformanceQualityLevel::High;
}

void ULesFightCharacterOptimizer::Shutdown()
{
}

void ULesFightCharacterOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	CurrentLevel = Level;

	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		LODBias = 0;
		CullDistance = 10000.0f;
		bSkeletonOptimized = false;
		bCullingEnabled = false;
		bInstancedMaterials = false;
		MaxActiveCharacters = 4;
		break;

	case EPerformanceQualityLevel::High:
		LODBias = 0;
		CullDistance = 7500.0f;
		bSkeletonOptimized = false;
		bCullingEnabled = true;
		bInstancedMaterials = false;
		MaxActiveCharacters = 3;
		break;

	case EPerformanceQualityLevel::Medium:
		LODBias = 1;
		CullDistance = 5000.0f;
		bSkeletonOptimized = true;
		bCullingEnabled = true;
		bInstancedMaterials = true;
		MaxActiveCharacters = 2;
		break;

	case EPerformanceQualityLevel::Low:
		LODBias = 2;
		CullDistance = 3000.0f;
		bSkeletonOptimized = true;
		bCullingEnabled = true;
		bInstancedMaterials = true;
		MaxActiveCharacters = 1;
		break;

	default:
		break;
	}
}

void ULesFightCharacterOptimizer::OptimizeCharacterMeshes()
{
	UE_LOG(LogTemp, Log, TEXT("ULesFightCharacterOptimizer: Optimizing character meshes..."));
	UE_LOG(LogTemp, Log, TEXT("  LOD Bias: %d"), LODBias);
	UE_LOG(LogTemp, Log, TEXT("  Cull Distance: %.1f"), CullDistance);
	UE_LOG(LogTemp, Log, TEXT("  Skeleton Optimization: %s"), bSkeletonOptimized ? TEXT("Enabled") : TEXT("Disabled"));
	UE_LOG(LogTemp, Log, TEXT("  Culling: %s"), bCullingEnabled ? TEXT("Enabled") : TEXT("Disabled"));
	UE_LOG(LogTemp, Log, TEXT("  Instanced Materials: %s"), bInstancedMaterials ? TEXT("Enabled") : TEXT("Disabled"));
	UE_LOG(LogTemp, Log, TEXT("  Max Active Characters: %d"), MaxActiveCharacters);
}

void ULesFightCharacterOptimizer::SetLODBias(int32 Bias)
{
	LODBias = FMath::Clamp(Bias, 0, 4);
}

int32 ULesFightCharacterOptimizer::GetLODBias() const
{
	return LODBias;
}

void ULesFightCharacterOptimizer::SetSkeletonOptimization(bool bOptimize)
{
	bSkeletonOptimized = bOptimize;
}

void ULesFightCharacterOptimizer::EnableCullDistance(bool bEnable)
{
	bCullingEnabled = bEnable;

	if (bCullingEnabled)
	{
		UE_LOG(LogTemp, Log, TEXT("Character culling enabled at distance %.1f"), CullDistance);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Character culling disabled"));
	}
}

void ULesFightCharacterOptimizer::SetCullDistance(float Distance)
{
	CullDistance = FMath::Max(1000.0f, Distance);
}

void ULesFightCharacterOptimizer::OptimizeMaterials(bool bUseInstancedMaterials)
{
	bInstancedMaterials = bUseInstancedMaterials;

	if (bInstancedMaterials)
	{
		UE_LOG(LogTemp, Log, TEXT("Instanced materials enabled for characters"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Instanced materials disabled for characters"));
	}
}

int32 ULesFightCharacterOptimizer::GetMeshTriangleCount() const
{
	return 0;
}

int32 ULesFightCharacterOptimizer::GetActiveCharacterCount() const
{
	return 0;
}

TArray<FString> ULesFightCharacterOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentLevel)));
	Status.Add(FString::Printf(TEXT("LOD Bias: %d"), LODBias));
	Status.Add(FString::Printf(TEXT("Cull Distance: %.1f"), CullDistance));
	Status.Add(FString::Printf(TEXT("Skeleton Optimized: %s"), bSkeletonOptimized ? TEXT("Yes") : TEXT("No")));
	Status.Add(FString::Printf(TEXT("Culling Enabled: %s"), bCullingEnabled ? TEXT("Yes") : TEXT("No")));
	Status.Add(FString::Printf(TEXT("Instanced Materials: %s"), bInstancedMaterials ? TEXT("Yes") : TEXT("No")));
	Status.Add(FString::Printf(TEXT("Max Active Characters: %d"), MaxActiveCharacters));
	return Status;
}
