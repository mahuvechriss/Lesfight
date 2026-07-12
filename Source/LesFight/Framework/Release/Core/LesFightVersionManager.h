#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightVersionManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightVersionManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	FVersionInfo GetCurrentVersion() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void SetVersion(int32 Major, int32 Minor, int32 Patch);

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void BumpMajor();

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void BumpMinor();

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void BumpPatch();

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void IncrementBuildNumber();

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	FString GetVersionString() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	FString GetShortVersionString() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	void SetVersionSuffix(const FString& Suffix);

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	TArray<FVersionInfo> GetVersionHistory() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	bool SaveVersionToConfig();

	UFUNCTION(BlueprintCallable, Category = "Release|Version")
	bool LoadVersionFromConfig();

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Version")
	FVersionInfo CurrentVersion;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Version")
	TArray<FVersionInfo> VersionHistory;

	void RecordVersion();
};
