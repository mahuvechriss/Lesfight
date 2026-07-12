#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightIntegrationTestSuite.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightIntegrationTestSuite : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    TArray<FIntegrationTestResult> RunAllTests();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    FIntegrationTestResult RunTestByName(FName TestName);

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    TArray<FIntegrationTestResult> RunTestsByCategory(FName Category);

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    TArray<FIntegrationTestResult> GetTestResults() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    TArray<FName> GetTestNames() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    int32 GetPassCount() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    int32 GetFailCount() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    int32 GetTotalCount() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    EIntegrationTestResult GetOverallResult() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    void ClearResults();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite")
    bool ExportResultsToFile(FString FilePath);

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestFullMatchFlow();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestCharacterCreationThroughSave();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestAIFightSimulation();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestLANMultiplayerFlow();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestSaveAndLoadProfile();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestSaveAndLoadCharacter();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestSettingsPersistence();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestMainMenuNavigation();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestCharacterSelectToCombat();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestArenaLoading();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestAudioSystemStateChange();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestVFXSystemTrigger();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestProgressionTracking();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestAchievementUnlockFlow();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestBackupAndRestore();

    UFUNCTION(BlueprintCallable, Category = "Integration|TestSuite|Tests")
    FIntegrationTestResult TestAllModuleInitialization();

protected:
    UPROPERTY()
    TArray<FIntegrationTestResult> TestResults;

    UPROPERTY()
    bool bTestsRunning;

private:
    FIntegrationTestResult RunTestWithTimer(FName Name, TFunction<bool()> TestFunc, FText Description);
    bool VerifyModuleLoaded(ESystemModule Module);
};
