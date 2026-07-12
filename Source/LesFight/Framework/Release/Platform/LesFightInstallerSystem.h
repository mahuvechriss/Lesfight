#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightInstallerSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightInstallerSystem : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	void SetInstallPath(const FString& Path);

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	FString GetInstallPath() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	TArray<FString> GenerateInstallSteps();

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	TArray<FString> GenerateUninstallSteps();

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	bool ValidateInstallation();

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	bool VerifyRequiredFiles();

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	void CreateShortcuts();

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	int64 GetInstallSizeBytes() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Installer")
	FString GetInstallSummary() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Installer")
	FString InstallPath;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Installer")
	TArray<FString> RequiredDirectories;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Installer")
	bool bInstalled = false;
};
