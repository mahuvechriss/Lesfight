#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightUIDevTools.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightUIDevTools : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void Shutdown();

    UFUNCTION(BlueprintCallable)
    void EnableUIPreviewMode(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsUIPreviewModeActive() const { return bPreviewMode; }

    UFUNCTION(BlueprintCallable)
    void PreviewScreen(FName ScreenID);

    UFUNCTION(BlueprintCallable)
    TArray<FString> TestNavigationForScreen(FName ScreenID);

    UFUNCTION(BlueprintCallable)
    FWidgetTestResult RunWidgetTest(UUserWidget* Widget);

    UFUNCTION(BlueprintCallable)
    TArray<FLocalizationIssue> RunLocalizationTest();

    UFUNCTION(BlueprintCallable)
    TMap<FString, int32> RunAllTests();

    UFUNCTION(BlueprintCallable)
    void StartPerformanceMonitoring();

    UFUNCTION(BlueprintCallable)
    void StopPerformanceMonitoring();

    UFUNCTION(BlueprintCallable)
    TArray<FPerformanceSample> GetPerformanceReport() const { return PerformanceSamples; }

    UFUNCTION(BlueprintCallable)
    void LogUITest(FText Message);

    UFUNCTION(BlueprintCallable)
    TArray<FText> GetTestLog() const { return TestLog; }

    UFUNCTION(BlueprintCallable)
    void ClearTestLog();

protected:
    UPROPERTY()
    bool bPreviewMode = false;

    UPROPERTY()
    TArray<FText> TestLog;

    UPROPERTY()
    bool bMonitoring = false;

    UPROPERTY()
    TArray<FPerformanceSample> PerformanceSamples;

    static constexpr int32 MaxLogEntries = 500;
};
