#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightUXEvaluator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightUXEvaluator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	TArray<FQATestCase> EvaluateDifficulty();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	TArray<FQATestCase> EvaluateControls();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	TArray<FQATestCase> EvaluateMenuUsability();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	TArray<FQATestCase> EvaluateCharCreationExperience();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	TArray<FQATestCase> EvaluateOverallEnjoyment();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	TArray<FQATestCase> RunFullUXEvaluation();

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	TArray<FString> GetImprovementFeedback() const;

	UFUNCTION(BlueprintCallable, Category = "QA|UX")
	float GetUXScore() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|UX")
	TArray<FString> FeedbackCollection;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|UX")
	float UXScore = 100.0f;

	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
