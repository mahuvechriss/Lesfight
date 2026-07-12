#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightTextureOptimizer.generated.h"

USTRUCT(BlueprintType)
struct FTextureInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 Width = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	int32 Height = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	float SizeMB = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
	bool bStreamed = true;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextureBudgetExceeded, float, CurrentUsageMB);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightTextureOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void SetTextureQuality(ETextureQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	ETextureQualityLevel GetTextureQuality() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void SetMemoryBudget(float BudgetMB);

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	float GetMemoryBudget() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void EnableTextureStreaming(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void OptimizeTexturePool();

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	float GetCurrentTextureMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	float GetTexturePoolSizeMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	TArray<FString> GetStreamedTextures() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void ReportTextureUsage(FName TextureName, int32 Width, int32 Height, float SizeMB);

	UFUNCTION(BlueprintCallable, Category = "Performance|Textures")
	void ApplyTextureScale(int32 Percent);

	UPROPERTY(BlueprintAssignable, Category = "Performance|Textures")
	FOnTextureBudgetExceeded OnTextureBudgetExceeded;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Performance|Textures")
	ETextureQualityLevel CurrentQuality = ETextureQualityLevel::High;

	UPROPERTY(EditDefaultsOnly, Category = "Performance|Textures")
	float MemoryBudgetMB = 1024.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Textures")
	float CurrentMemoryMB = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Textures")
	int32 ResolutionScale = 100;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Textures")
	bool bStreamingEnabled = true;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Textures")
	TMap<FName, FTextureInfo> TextureRegistry;
};
