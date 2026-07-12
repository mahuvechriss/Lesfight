#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightPackageOptimizer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPackageOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	void CompressTextures();

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	void OptimizePackages();

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	void VerifyReferences();

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	void ValidateMaterials();

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	void CheckAnimations();

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	int64 EstimateSavingsAfterOptimization() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	float GetOptimizationRatio() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Optimization")
	TArray<FString> GetOptimizationLog() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Optimization")
	TArray<FString> OptimizationLog;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Optimization")
	int64 OriginalSize = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Optimization")
	int64 OptimizedSize = 0;
};
