#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightBuildVerifier.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightBuildVerifier : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	FATestSuiteResult VerifyBuild();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	bool DoesGameLaunch();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	bool DoAllLevelsLoad();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	bool DoAllBlueprintsCompile();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	bool AreAllMaterialsValid();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	bool DoAllSoundCuesReferenceValidAssets();

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	int32 GetBuildVersion() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	FString GetBuildSummary() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	TArray<FString> GetBuildErrors() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	TArray<FString> GetBuildWarnings() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BuildVerification")
	bool ExportBuildReport(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|BuildVerification")
	TArray<FString> BuildErrors;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|BuildVerification")
	TArray<FString> BuildWarnings;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|BuildVerification")
	int32 BuildNumber = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|BuildVerification")
	bool bBuildVerified = false;
};
