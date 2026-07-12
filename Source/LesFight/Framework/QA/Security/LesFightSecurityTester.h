#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightSecurityTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSecurityTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Security")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Security")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Security")
	TArray<FQATestCase> TestSaveTampering();

	UFUNCTION(BlueprintCallable, Category = "QA|Security")
	TArray<FQATestCase> TestNetworkManipulation();

	UFUNCTION(BlueprintCallable, Category = "QA|Security")
	TArray<FQATestCase> TestDataCorruption();

	UFUNCTION(BlueprintCallable, Category = "QA|Security")
	TArray<FQATestCase> TestInvalidCharacterData();

	UFUNCTION(BlueprintCallable, Category = "QA|Security")
	TArray<FQATestCase> RunFullSecurityTestSuite();

protected:
	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
