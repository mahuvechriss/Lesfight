#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightMemoryTracker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMemoryWarning, float, CurrentMB, float, BudgetMB);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMemoryTracker : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	float GetCurrentMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	float GetPeakMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	float GetAvailableMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	float GetMemoryUsageByCategory(EPerformanceCategory Category) const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void ReportMemoryUsage(FName AssetName, float SizeMB);

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void RemoveMemoryReport(FName AssetName);

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	TArray<FString> GetLargestAssets(int32 Count) const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	FMemoryBudget GetMemoryBudget() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void SetMemoryBudget(FMemoryBudget NewBudget);

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	bool IsMemoryBudgetExceeded() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	float GetMemoryUsagePercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	bool TrackObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void UntrackObject(UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	int32 GetTrackedObjectCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	TArray<FString> DetectMemoryLeaks() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Memory")
	void EnableMemoryLogging(bool bEnabled);

	UPROPERTY(BlueprintAssignable, Category = "Performance|Memory")
	FOnMemoryWarning OnMemoryWarning;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	TMap<FName, float> AssetMemoryMap;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	float CurrentMemoryMB = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	float PeakMemoryMB = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	float AvailableMemoryMB = 0.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	FMemoryBudget Budget;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	TSet<TWeakObjectPtr<UObject>> TrackedObjects;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	TMap<FName, float> ObjectMemorySnapshots;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Memory")
	bool bMemoryLogging = false;

	float BaselineMemoryMB = 0.0f;
};
