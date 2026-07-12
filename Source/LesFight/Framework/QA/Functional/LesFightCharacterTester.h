#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightCharacterTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCharacterTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	TArray<FQATestCase> TestCharacterCreation();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	TArray<FQATestCase> TestCharacterLoading();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	TArray<FQATestCase> TestCustomization();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	TArray<FQATestCase> TestAIGeneratedCharacters();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	TArray<FQATestCase> TestAnimationCompatibility();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	TArray<FQATestCase> TestCharacterSaving();

	UFUNCTION(BlueprintCallable, Category = "QA|Character")
	TArray<FQATestCase> RunFullCharacterTestSuite();

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|Character")
	TArray<FQATestCase> TestResults;

	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
