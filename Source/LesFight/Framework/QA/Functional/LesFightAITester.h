#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightAITester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAITester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	TArray<FQATestCase> TestDifficultyLevels();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	TArray<FQATestCase> TestAIReactions();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	TArray<FQATestCase> TestCombatDecisions();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	TArray<FQATestCase> TestStyleBehaviors();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	TArray<FQATestCase> TestAdaptiveLearning();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	TArray<FQATestCase> TestFairness();

	UFUNCTION(BlueprintCallable, Category = "QA|AI")
	TArray<FQATestCase> RunFullAITestSuite();

protected:
	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
