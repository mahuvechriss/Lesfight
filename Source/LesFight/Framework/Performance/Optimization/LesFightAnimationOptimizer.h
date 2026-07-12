#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightAnimationOptimizer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAnimationOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void OptimizeAnimationBlueprints();

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void SetBlendCalculationRate(float Rate);

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	float GetBlendCalculationRate() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void EnableLODBlending(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void SetMaxActiveAnimations(int32 Max);

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	int32 GetMaxActiveAnimations() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void OptimizeIKFrequency(float UpdateRate);

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	void OptimizeMotionMatching(bool bEnabled, float QualityScale);

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	float GetAnimationMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	int32 GetActiveAnimationCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Animation")
	TArray<FString> GetOptimizationStatus() const;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Performance|Animation")
	float BlendRate = 60.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Animation")
	float IKUpdateRate = 60.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Animation")
	float MotionMatchingQuality = 1.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Animation")
	int32 MaxActiveAnims = 10;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Animation")
	bool bLODBlending = false;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Animation")
	bool bMotionMatching = true;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Animation")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;
};
