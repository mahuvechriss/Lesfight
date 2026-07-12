#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightAIOptimizer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void SetDecisionFrequency(float Hz);

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	float GetDecisionFrequency() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void SetPerceptionUpdateRate(float Hz);

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void EnableBehaviorTreeOptimization(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void SetMaxAIControllers(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	int32 GetMaxAIControllers() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void SetMaxPerceptionUpdates(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	void EnableAsyncPathfinding(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	int32 GetActiveAICount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	float GetAverageDecisionTimeMs() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|AI")
	TArray<FString> GetOptimizationStatus() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|AI")
	float DecisionFreq = 60.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|AI")
	float PerceptionRate = 30.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|AI")
	int32 MaxAIControllers = 4;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|AI")
	int32 MaxPerceptionUpdatesPerFrame = 5;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|AI")
	bool bBehaviorTreeOpt = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|AI")
	bool bAsyncPathfinding = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|AI")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;
};
