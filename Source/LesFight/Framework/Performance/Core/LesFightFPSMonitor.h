#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightFPSMonitor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFPSWarning, float, CurrentFPS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFPSStabilized);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightFPSMonitor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetCurrentFPS() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetMinFPS() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetMaxFPS() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetAverageFPS() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetFrameTime() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetMinFrameTime() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetMaxFrameTime() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	bool IsFPSStable() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	TArray<float> GetFPSHistory() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	TArray<float> GetFrameTimeHistory() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetP1FrameTime() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetP5FrameTime() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	FText GetFPSQualityRating() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	void SetFPSTarget(float Target);

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetFPSTarget() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	void SetWarningThreshold(float FPS);

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	float GetWarningThreshold() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	void EnableFPSLogging(bool bEnabled);

	UPROPERTY(BlueprintAssignable, Category = "Performance|FPS")
	FOnFPSWarning OnFPSWarning;

	UPROPERTY(BlueprintAssignable, Category = "Performance|FPS")
	FOnFPSStabilized OnFPSStabilized;

	UFUNCTION(BlueprintCallable, Category = "Performance|FPS")
	void ResetStats();

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	TArray<float> FPSHistory;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	TArray<float> FrameTimeHistory;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	float CurrentFPS = 60.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	float MinFPS = 999.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	float MaxFPS = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	float AverageFPS = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	float FPSTarget = 60.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	float WarningThreshold = 30.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	int32 SampleCount = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|FPS")
	bool bFPSLogging = false;

	static constexpr int32 MaxHistory = 300;
};
