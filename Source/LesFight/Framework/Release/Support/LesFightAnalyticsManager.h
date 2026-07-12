#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnalyticsManager.generated.h"

USTRUCT(BlueprintType)
struct FAnalyticsEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analytics")
	FString EventName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analytics")
	TMap<FString, FString> Properties;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Analytics")
	FDateTime Timestamp;
};

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAnalyticsManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	void SetAnalyticsEnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	bool IsAnalyticsEnabled() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	void RecordCrashReport(const FString& CrashData);

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	void RecordPerformanceReport(float FPS, float FrameTime, float MemoryMB);

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	void RecordGameplayEvent(const FString& EventName, const TMap<FString, FString>& Properties);

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	TArray<FAnalyticsEvent> GetPendingEvents() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	int32 FlushEvents();

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	void RequestConsent();

	UFUNCTION(BlueprintCallable, Category = "Release|Analytics")
	bool HasConsent() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Analytics")
	TArray<FAnalyticsEvent> PendingEvents;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Analytics")
	bool bEnabled = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Analytics")
	bool bConsentGiven = false;
};
