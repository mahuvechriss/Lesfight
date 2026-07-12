#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightUITester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightUITester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestMenuNavigation();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestControllerSupport();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestKeyboardSupport();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestCharacterCreatorUI();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestLobbyUI();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestSettingsUI();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestHUD();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> TestResultsScreen();

	UFUNCTION(BlueprintCallable, Category = "QA|UI")
	TArray<FQATestCase> RunFullUITestSuite();

protected:
	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
