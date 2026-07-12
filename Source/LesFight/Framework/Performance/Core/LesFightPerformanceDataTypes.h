#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightPerformanceDataTypes.generated.h"

UENUM(BlueprintType)
enum class EPerformanceQualityLevel : uint8
{
	Ultra	UMETA(DisplayName = "Ultra"),
	High	UMETA(DisplayName = "High"),
	Medium	UMETA(DisplayName = "Medium"),
	Low		UMETA(DisplayName = "Low"),
	Custom	UMETA(DisplayName = "Custom")
};

UENUM(BlueprintType)
enum class EPerformanceCategory : uint8
{
	CPU		UMETA(DisplayName = "CPU"),
	GPU		UMETA(DisplayName = "GPU"),
	Memory	UMETA(DisplayName = "Memory"),
	Loading	UMETA(DisplayName = "Loading"),
	Network	UMETA(DisplayName = "Network"),
	Asset	UMETA(DisplayName = "Asset"),
	Overall	UMETA(DisplayName = "Overall")
};

UENUM(BlueprintType)
enum class EOptimizationTarget : uint8
{
	FPS				UMETA(DisplayName = "FPS"),
	Memory			UMETA(DisplayName = "Memory"),
	LoadingTime		UMETA(DisplayName = "Loading Time"),
	NetworkBandwidth UMETA(DisplayName = "Network Bandwidth"),
	BatteryLife		UMETA(DisplayName = "Battery Life")
};

UENUM(BlueprintType)
enum class ETextureQualityLevel : uint8
{
	Full	UMETA(DisplayName = "Full"),
	High	UMETA(DisplayName = "High"),
	Medium	UMETA(DisplayName = "Medium"),
	Low		UMETA(DisplayName = "Low"),
	Mobile	UMETA(DisplayName = "Mobile")
};

UENUM(BlueprintType)
enum class EShadowQualityLevel : uint8
{
	Cinematic	UMETA(DisplayName = "Cinematic"),
	High		UMETA(DisplayName = "High"),
	Medium		UMETA(DisplayName = "Medium"),
	Low			UMETA(DisplayName = "Low"),
	Disabled	UMETA(DisplayName = "Disabled")
};

UENUM(BlueprintType)
enum class EVFXQualityLevel : uint8
{
	Ultra	UMETA(DisplayName = "Ultra"),
	High	UMETA(DisplayName = "High"),
	Medium	UMETA(DisplayName = "Medium"),
	Low		UMETA(DisplayName = "Low"),
	Minimal	UMETA(DisplayName = "Minimal")
};

USTRUCT(BlueprintType)
struct FPerformanceSnapshot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float Timestamp = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float FPS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float FrameTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float CPUTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float GPUTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float MemoryUsageMB = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float AvailableMemoryMB = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 DrawCalls = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 TriangleCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float NetworkLatency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 ActiveNiagaraSystems = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float LoadingTimeMs = 0.0f;
};

USTRUCT(BlueprintType)
struct FMemoryBudget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float TextureBudgetMB = 1024.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float MeshBudgetMB = 512.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float AudioBudgetMB = 256.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float AnimationBudgetMB = 384.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float VFXBudgetMB = 256.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float TotalBudgetMB = 4096.0f;
};

USTRUCT(BlueprintType)
struct FQualitySettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	EPerformanceQualityLevel QualityLevel = EPerformanceQualityLevel::High;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 ResolutionScale = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	ETextureQualityLevel TextureQuality = ETextureQualityLevel::High;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	EShadowQualityLevel ShadowQuality = EShadowQualityLevel::High;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	EVFXQualityLevel VFXQuality = EVFXQualityLevel::High;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 ViewDistance = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bNaniteEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bLumenEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bMotionBlur = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bBloom = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bSSR = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bPostProcessing = true;
};

USTRUCT(BlueprintType)
struct FOptimizationMetrics
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float AverageFPS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float MinFPS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float MaxFPS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float AverageFrameTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float P1FrameTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float MemoryPeakMB = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float AverageLoadTimeMs = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 TotalDrawCalls = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float NetworkBandwidthKbps = 0.0f;
};

USTRUCT(BlueprintType)
struct FPerformanceAlert
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	FText Message;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	EPerformanceCategory Category = EPerformanceCategory::Overall;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float Threshold = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float CurrentValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	FDateTime Timestamp;
};
