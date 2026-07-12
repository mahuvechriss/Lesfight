#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightBuildManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightBuildManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	FBuildConfiguration GetActiveConfiguration() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void SetBuildType(EBuildType Type);

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void SetTargetPlatform(EReleasePlatform Platform);

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void ConfigureDevelopmentBuild();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void ConfigureQABuild();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void ConfigureReleaseBuild();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	void ConfigureShippingBuild();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	TArray<FString> GenerateBuildCommands();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	bool ValidateConfiguration();

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	TArray<FString> GetBuildLog() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Build")
	FString GetBuildStatus() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Build")
	FBuildConfiguration ActiveConfig;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Build")
	TArray<FString> BuildLog;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Build")
	bool bBuildInProgress = false;
};
