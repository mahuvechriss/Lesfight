#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightLaunchManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightLaunchManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	TArray<FString> GetFinalReleaseChecklist();

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	int32 GetChecklistCompletion() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	bool IsReadyForLaunch() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	TArray<FString> GetMarketingInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	TArray<FString> GetPressBuildInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	void GenerateScreenshotList();

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	void PreparePressBuild();

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	void PrepareReviewBuild();

	UFUNCTION(BlueprintCallable, Category = "Release|Launch")
	TArray<FString> GetLaunchLog() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Launch")
	TArray<FReleaseChecklist> LaunchChecklist;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Launch")
	TArray<FString> LaunchLog;
};
