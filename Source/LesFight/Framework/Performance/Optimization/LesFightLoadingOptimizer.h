#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightLoadingOptimizer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetPreloaded, FName, AssetName);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightLoadingOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void EnableAsyncLoading(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void SetMaxConcurrentLoads(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void EnableBackgroundAssetStreaming(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void PreloadCommonAssets();

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void SetTextureStreamingPool(float SizeMB);

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	void OptimizeLevelLoadOrder();

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	float GetAverageLoadTimeMs() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	float GetTotalLoadTimeMs() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	int32 GetLoadedAssetCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Loading")
	TArray<FString> GetOptimizationStatus() const;

	UPROPERTY(BlueprintAssignable, Category = "Performance|Loading")
	FOnAssetPreloaded OnAssetPreloaded;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Loading")
	bool bAsyncLoading = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Loading")
	bool bBackgroundStreaming = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Loading")
	int32 MaxConcurrentLoads = 4;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Loading")
	float TexturePoolMB = 1024.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Loading")
	TArray<FName> PreloadedAssets;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Loading")
	TMap<FName, float> LoadTimes;
};
