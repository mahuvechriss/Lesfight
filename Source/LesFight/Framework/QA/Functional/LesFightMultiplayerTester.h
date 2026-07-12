#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightMultiplayerTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMultiplayerTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	TArray<FQATestCase> TestLANHost();

	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	TArray<FQATestCase> TestLANJoin();

	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	TArray<FQATestCase> TestMatchSync();

	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	TArray<FQATestCase> TestDisconnect();

	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	TArray<FQATestCase> TestReconnection();

	UFUNCTION(BlueprintCallable, Category = "QA|Multiplayer")
	TArray<FQATestCase> RunFullMultiplayerTestSuite();

protected:
	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
