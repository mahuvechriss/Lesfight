#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightCharCreationDevTools.generated.h"

UENUM(BlueprintType)
enum class EDevToolMode : uint8
{
    None,
    VisualDebug,
    PerformanceDebug,
    DataInspection,
    StressTest,
    Automation,
    MAX
};

UCLASS(Blueprintable)
class ULesFightCharCreationDevTools : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharCreationDevTools();

    void Initialize(class ULesFightCharCreationManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void SetDevMode(EDevToolMode Mode);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    EDevToolMode GetDevMode() const { return CurrentMode; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void ToggleDebugOverlay();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    bool IsDebugOverlayVisible() const { return bDebugOverlayVisible; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void LogCharacterState(const FString& CharacterID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void RunStressTest(int32 CharacterCount);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void RunAutomationSequence(const TArray<FString>& Commands);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void ExportDebugReport(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void SetMorphVisualization(bool bVisualize);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    bool IsMorphVisualizationEnabled() const { return bMorphVisualization; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void ForceGarbageCollection();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void SimulateNetworkLatency(int32 LatencyMs);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|DevTools")
    void ResetAllDevSettings();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EDevToolMode CurrentMode;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bDebugOverlayVisible;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bMorphVisualization;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    bool bDevModeEnabled;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 StressTestMaxCharacters;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FString> DebugLog;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 MaxLogEntries;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    int32 SimulatedLatencyMs;

    void AddLogEntry(const FString& Entry);
};
