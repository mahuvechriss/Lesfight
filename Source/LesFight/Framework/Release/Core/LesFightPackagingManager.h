#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightPackagingManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPackagingManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	void BuildPackageManifest();

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	TArray<FPackageManifestEntry> GetManifest() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	int64 CalculatePackageSize() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	bool ValidateManifest();

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	TArray<FString> GetPackagingSteps();

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	TArray<FString> GetRequiredFiles() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	FString GetPackageSummary() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Packaging")
	bool ExportManifest(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Packaging")
	TArray<FPackageManifestEntry> Manifest;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Packaging")
	FString PackageOutputPath;
};
