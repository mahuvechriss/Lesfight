#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightAudioVisualTester.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAudioVisualTester : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestMusicTransitions();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestCombatSounds();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestVoiceLines();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestEnvironmentAudio();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestCharacterModels();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestLighting();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestVFX();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> TestCameraEffects();

	UFUNCTION(BlueprintCallable, Category = "QA|AudioVisual")
	TArray<FQATestCase> RunFullAudioVisualTestSuite();

protected:
	int32 TestCounter = 0;
	FQATestCase MakeTest(const FString& Name, const FText& Desc, bool bPassed);
};
