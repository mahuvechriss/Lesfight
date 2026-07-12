#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightGameplayTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightGameplayTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestAllAttacks();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestAllCombos();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestBlocking();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestDodging();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestCounters();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestThrows();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestSpecialMoves();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestUltimateMoves();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestDamageCalculation();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestHitDetection();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestFightingStyles();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestStances();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> TestEnvironmentalInteractions();

	UFUNCTION(BlueprintCallable, Category = "QA|Gameplay")
	TArray<FQATestCase> RunFullGameplayTestSuite();

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|Gameplay")
	TArray<FQATestCase> TestResults;

	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
