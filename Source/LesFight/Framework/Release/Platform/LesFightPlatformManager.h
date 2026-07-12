#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightPlatformManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPlatformManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	void SetActivePlatform(EReleasePlatform Platform);

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	EReleasePlatform GetActivePlatform() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	TArray<FString> GetPlatformRequirements() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	TArray<FString> GetPlatformSpecificSettings() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	FString GetMinimumSpecs() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	FString GetRecommendedSpecs() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	TArray<FString> ValidatePlatformCompatibility();

	UFUNCTION(BlueprintCallable, Category = "Release|Platform")
	bool IsPlatformReady() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Platform")
	EReleasePlatform ActivePlatform = EReleasePlatform::Windows;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Platform")
	TArray<FString> PlatformLog;
};
