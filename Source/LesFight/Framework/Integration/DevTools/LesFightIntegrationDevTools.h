#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightIntegrationDevTools.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightIntegrationDevTools : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void ShowDebugGameFlowMenu();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FString> GetSystemStatus();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FString> GetModuleDependencyGraph();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void LaunchTestMode(FName ModeName);

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FIntegrationTestResult> RunIntegrationTests();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FString> GetPerformanceReport();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    bool ForceGameFlowState(EGameFlowState State);

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    bool ResetAllSystems();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void SimulateCrash(FName SystemName);

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void LogIntegrationEvent(FString Message);

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FString> GetIntegrationLog() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void ClearIntegrationLog();

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    void EnableSystemLogging(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FString> GetSystemPerformanceSnapshot() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FString> LoadingTimeReport() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|DevTools")
    TArray<FString> MemoryUsageReport() const;

protected:
    UPROPERTY()
    TArray<FString> IntegrationLog;

    UPROPERTY()
    bool bSystemLogging;

    UPROPERTY()
    TMap<FDateTime, FString> PerformanceSnapshots;

    static constexpr int32 MaxLogEntries = 1000;
};
