#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightCompatibilityTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCompatibilityTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	TArray<FQATestCase> TestHardwareConfigs();

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	TArray<FQATestCase> TestControllerTypes();

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	TArray<FQATestCase> TestScreenResolutions();

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	TArray<FQATestCase> TestQualitySettings();

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	TArray<FQATestCase> RunFullCompatibilityTestSuite();

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	void RegisterTestEnvironment(const FQATestEnvironment& Environment);

	UFUNCTION(BlueprintCallable, Category = "QA|Compatibility")
	TArray<FQATestEnvironment> GetTestEnvironments() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|Compatibility")
	TArray<FQATestEnvironment> TestEnvironments;

	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
