#include "LesFightCharCreationDevTools.h"
#include "LesFightCharCreationManager.h"

ULesFightCharCreationDevTools::ULesFightCharCreationDevTools()
    : CurrentMode(EDevToolMode::None)
    , bDebugOverlayVisible(false)
    , bMorphVisualization(false)
    , bDevModeEnabled(false)
    , StressTestMaxCharacters(100)
    , MaxLogEntries(200)
    , SimulatedLatencyMs(0)
{
}

void ULesFightCharCreationDevTools::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightCharCreationDevTools::Tick(float DeltaTime)
{
}

void ULesFightCharCreationDevTools::SetDevMode(EDevToolMode Mode)
{
    CurrentMode = Mode;
    AddLogEntry(TEXT("DevMode set to: ") + FString::FromInt(static_cast<int32>(Mode)));
}

void ULesFightCharCreationDevTools::ToggleDebugOverlay()
{
    bDebugOverlayVisible = !bDebugOverlayVisible;
    AddLogEntry(bDebugOverlayVisible ? TEXT("Debug overlay shown") : TEXT("Debug overlay hidden"));
}

void ULesFightCharCreationDevTools::LogCharacterState(const FString& CharacterID)
{
    AddLogEntry(TEXT("Character state requested: ") + CharacterID);
}

void ULesFightCharCreationDevTools::RunStressTest(int32 CharacterCount)
{
    int32 Count = FMath::Min(CharacterCount, StressTestMaxCharacters);
    AddLogEntry(FString::Printf(TEXT("Running stress test with %d characters..."), Count));
}

void ULesFightCharCreationDevTools::RunAutomationSequence(
    const TArray<FString>& Commands)
{
    AddLogEntry(FString::Printf(TEXT("Running automation sequence: %d commands"), Commands.Num()));
}

void ULesFightCharCreationDevTools::ExportDebugReport(const FString& FilePath)
{
    TArray<FString> ReportLines;
    ReportLines.Add(TEXT("=== LES FIGHT Character Creation Debug Report ==="));
    ReportLines.Add(FString::Printf(TEXT("DevMode: %d"), static_cast<int32>(CurrentMode)));
    ReportLines.Add(FString::Printf(TEXT("Debug Overlay: %s"), bDebugOverlayVisible ? TEXT("true") : TEXT("false")));
    ReportLines.Add(FString::Printf(TEXT("Morph Visualization: %s"), bMorphVisualization ? TEXT("true") : TEXT("false")));
    ReportLines.Add(FString::Printf(TEXT("Log Entries: %d"), DebugLog.Num()));
    ReportLines.Add(TEXT("=== Recent Log ==="));
    for (const FString& Entry : DebugLog)
    {
        ReportLines.Add(Entry);
    }
    FFileHelper::SaveStringArrayToFile(ReportLines, *FilePath);
    AddLogEntry(TEXT("Debug report exported: ") + FilePath);
}

void ULesFightCharCreationDevTools::SetMorphVisualization(bool bVisualize)
{
    bMorphVisualization = bVisualize;
    AddLogEntry(bMorphVisualization ? TEXT("Morph visualization enabled") : TEXT("Morph visualization disabled"));
}

void ULesFightCharCreationDevTools::ForceGarbageCollection()
{
    AddLogEntry(TEXT("Forcing garbage collection..."));
}

void ULesFightCharCreationDevTools::SimulateNetworkLatency(int32 LatencyMs)
{
    SimulatedLatencyMs = FMath::Max(0, LatencyMs);
    AddLogEntry(FString::Printf(TEXT("Network latency set to %dms"), SimulatedLatencyMs));
}

void ULesFightCharCreationDevTools::ResetAllDevSettings()
{
    CurrentMode = EDevToolMode::None;
    bDebugOverlayVisible = false;
    bMorphVisualization = false;
    DebugLog.Empty();
    SimulatedLatencyMs = 0;
    AddLogEntry(TEXT("All dev settings reset"));
}

void ULesFightCharCreationDevTools::AddLogEntry(const FString& Entry)
{
    DebugLog.Add(FDateTime::Now().ToString(TEXT("[%H:%M:%s] ")) + Entry);
    if (DebugLog.Num() > MaxLogEntries)
    {
        DebugLog.RemoveAt(0);
    }
}
