#include "LesFightArenaDevTools.h"
#include "Framework/Arena/Manager/LesFightArenaWorldManager.h"

void ULesFightArenaDevTools::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bDebugMode = false;
    TestLog.Empty();
    TestLog.Reserve(MaxLogEntries);
    TestResults.Empty();
}

void ULesFightArenaDevTools::EnableDebugMode(bool bEnabled)
{
    bDebugMode = bEnabled;
    AddTestLog(FString::Printf(TEXT("Debug mode %s"), bEnabled ? TEXT("enabled") : TEXT("disabled")));
}

void ULesFightArenaDevTools::TestDestruction(EInteractiveObjectType Type, FVector Location)
{
    if (!bDebugMode) return;

    AddTestLog(FString::Printf(TEXT("TestDestruction: Type=%d Location=%s"), (int32)Type, *Location.ToString()));

    if (OwnerManager.IsValid() && OwnerManager->GetDestructibleObject())
    {
        FDestructibleObjectState ObjState;
        ObjState.ObjectType = Type;
        ObjState.Location = Location;
        ObjState.bDestroyed = true;

        OwnerManager->GetDestructibleObject()->DestroyObject(ObjState);
        AddTestLog(TEXT("Destruction test completed"));
    }
}

void ULesFightArenaDevTools::TestWeather(EWeatherType Weather, EWeatherIntensity Intensity)
{
    if (!bDebugMode) return;

    AddTestLog(FString::Printf(TEXT("TestWeather: Type=%d Intensity=%d"), (int32)Weather, (int32)Intensity));

    if (OwnerManager.IsValid() && OwnerManager->GetWeatherSystem())
    {
        FWeatherState WeatherState;
        WeatherState.WeatherType = Weather;
        WeatherState.Intensity = Intensity;

        OwnerManager->GetWeatherSystem()->SetWeather(WeatherState);
        AddTestLog(TEXT("Weather test completed"));
    }
}

void ULesFightArenaDevTools::TestLighting(ELightingPreset Preset)
{
    if (!bDebugMode) return;

    AddTestLog(FString::Printf(TEXT("TestLighting: Preset=%d"), (int32)Preset));

    if (OwnerManager.IsValid() && OwnerManager->GetLightingSystem())
    {
        OwnerManager->GetLightingSystem()->ApplyPreset(Preset);
        AddTestLog(TEXT("Lighting test completed"));
    }
}

void ULesFightArenaDevTools::PreviewArena(EArenaType Arena, bool bPreview)
{
    AddTestLog(FString::Printf(TEXT("PreviewArena: Arena=%d bPreview=%s"), (int32)Arena, bPreview ? TEXT("true") : TEXT("false")));

    if (OwnerManager.IsValid() && OwnerManager->GetLoader())
    {
        if (bPreview)
        {
            OwnerManager->GetLoader()->LoadPreview(Arena);
        }
        else
        {
            OwnerManager->GetLoader()->UnloadPreview();
        }
        AddTestLog(TEXT("Preview completed"));
    }
}

FString ULesFightArenaDevTools::GetArenaPerformanceReport() const
{
    FString Report;

    if (OwnerManager.IsValid() && OwnerManager->GetArenaPerformance())
    {
        FArenaPerformanceMetrics Metrics = OwnerManager->GetArenaPerformance()->GetCurrentMetrics();
        Report = FString::Printf(TEXT(
            "=== Arena Performance Report ===\n"
            "Quality Level: %d\n"
            "Nanite: %s\n"
            "Lumen: %s\n"
            "Texture Pool: %d MB\n"
            "Average FPS: %.1f\n"
            "Performance Score: %.2f\n"
            "==============================="
        ),
            Metrics.QualityLevel,
            Metrics.bNaniteEnabled ? TEXT("On") : TEXT("Off"),
            Metrics.bLumenEnabled ? TEXT("On") : TEXT("Off"),
            Metrics.TexturePoolSizeMB,
            Metrics.AverageFPS,
            Metrics.PerformanceScore);
    }
    else
    {
        Report = TEXT("Performance subsystem unavailable");
    }

    return Report;
}

float ULesFightArenaDevTools::RunDestructionStressTest(int32 ObjectCount)
{
    if (!OwnerManager.IsValid() || !OwnerManager->GetDestructibleObject())
    {
        AddTestLog(TEXT("Destruction stress test failed: subsystem unavailable"));
        return 0.0f;
    }

    AddTestLog(FString::Printf(TEXT("Running destruction stress test with %d objects..."), ObjectCount));

    double StartTime = FPlatformTime::Seconds();

    TArray<FDestructibleObjectState> Objects;
    Objects.Reserve(ObjectCount);

    for (int32 i = 0; i < ObjectCount; i++)
    {
        FDestructibleObjectState ObjState;
        ObjState.ObjectType = (EInteractiveObjectType)(i % (int32)EInteractiveObjectType::Max);
        ObjState.Location = FVector(FMath::FRandRange(-1000.0f, 1000.0f), FMath::FRandRange(-1000.0f, 1000.0f), 0.0f);
        ObjState.bDestroyed = false;
        ObjState.ObjectID = i;
        Objects.Add(ObjState);
    }

    for (FDestructibleObjectState& Obj : Objects)
    {
        Obj.bDestroyed = true;
        OwnerManager->GetDestructibleObject()->DestroyObject(Obj);
    }

    double Duration = FPlatformTime::Seconds() - StartTime;

    AddTestLog(FString::Printf(TEXT("Destruction stress test completed: %d objects in %.4f seconds"), ObjectCount, Duration));

    return (float)Duration;
}

bool ULesFightArenaDevTools::TestMultiplayerSync()
{
    AddTestLog(TEXT("Testing multiplayer sync..."));

    if (!OwnerManager.IsValid() || !OwnerManager->GetArenaReplication())
    {
        AddTestLog(TEXT("Multiplayer sync test failed: replication subsystem unavailable"));
        TestResults.Add(TEXT("MultiplayerSync"), false);
        return false;
    }

    bool bSyncOk = OwnerManager->GetArenaReplication()->IsReplicationEnabled();
    int32 PendingCount = OwnerManager->GetArenaReplication()->GetPendingStateUpdates().Num();

    AddTestLog(FString::Printf(TEXT("Replication enabled: %s, Pending updates: %d"),
        bSyncOk ? TEXT("true") : TEXT("false"), PendingCount));

    TestResults.Add(TEXT("MultiplayerSync"), bSyncOk);
    return bSyncOk;
}

void ULesFightArenaDevTools::LogArenaState()
{
    if (!OwnerManager.IsValid()) return;

    FString StateLog = FString::Printf(TEXT(
        "=== Arena State ===\n"
        "Initialized: %s\n"
        "Current Arena: %d\n"
        "Arena Loaded: %s\n"
        "Debug Mode: %s\n"
        "Test Log Entries: %d\n"
        "=================="),
        OwnerManager->IsArenaLoaded() ? TEXT("true") : TEXT("false"),
        (int32)OwnerManager->GetCurrentArena(),
        OwnerManager->IsArenaLoaded() ? TEXT("true") : TEXT("false"),
        bDebugMode ? TEXT("true") : TEXT("false"),
        TestLog.Num());

    AddTestLog(StateLog);
}

void ULesFightArenaDevTools::AddTestLog(const FString& Entry)
{
    TestLog.Add(Entry);
    if (TestLog.Num() > MaxLogEntries)
    {
        TestLog.RemoveAt(0, TestLog.Num() - MaxLogEntries, false);
    }

    UE_LOG(LogTemp, Log, TEXT("[LesFightDevTools] %s"), *Entry);
}
