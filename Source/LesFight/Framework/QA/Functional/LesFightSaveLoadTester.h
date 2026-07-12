#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightSaveLoadTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSaveLoadTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	TArray<FQATestCase> TestSaveCreation();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	TArray<FQATestCase> TestLoading();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	TArray<FQATestCase> TestBackupRecovery();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	TArray<FQATestCase> TestCorruptedDataHandling();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	TArray<FQATestCase> TestCharacterRestoration();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	TArray<FQATestCase> TestSettingsPersistence();

	UFUNCTION(BlueprintCallable, Category = "QA|SaveLoad")
	TArray<FQATestCase> RunFullSaveLoadTestSuite();

protected:
	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
