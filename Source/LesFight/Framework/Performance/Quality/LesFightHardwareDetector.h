#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightHardwareDetector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHardwareDetected, EPerformanceQualityLevel, Recommended);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightHardwareDetector : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	void DetectHardware();

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	EPerformanceQualityLevel GetDetectedQualityLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	FString GetCPUName() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	int32 GetCPUCores() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	FString GetGPUName() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	float GetGPUMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	float GetTotalRAMMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	float GetAvailableRAMMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	float GetStorageFreeGB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	FString GetOSVersion() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	bool IsHighEndPC() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	bool IsMidRangePC() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	bool IsLowEndPC() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	float GetHardwareScore() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Hardware")
	TArray<FString> GetHardwareReport() const;

	UPROPERTY(BlueprintAssignable, Category = "Performance|Hardware")
	FOnHardwareDetected OnHardwareDetected;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	FString CPUName;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	FString GPUName;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	FString OSVersion;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	int32 CPUCores = 0;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	float GPUMemoryMB = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	float TotalRAMMB = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	float AvailableRAMMB = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	float StorageFreeGB = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	EPerformanceQualityLevel DetectedQuality = EPerformanceQualityLevel::High;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Hardware")
	float HardwareScore = 0.0f;
};
