#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaDevTools.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaDevTools : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    void EnableDebugMode(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    void TestDestruction(EInteractiveObjectType Type, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    void TestWeather(EWeatherType Weather, EWeatherIntensity Intensity);

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    void TestLighting(ELightingPreset Preset);

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    void PreviewArena(EArenaType Arena, bool bPreview);

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    FString GetArenaPerformanceReport() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    float RunDestructionStressTest(int32 ObjectCount);

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    bool TestMultiplayerSync();

    UFUNCTION(BlueprintCallable, Category = "Arena|DevTools")
    void LogArenaState();

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Arena|DevTools")
    bool bDebugMode = false;

    UPROPERTY()
    TArray<FString> TestLog;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|DevTools")
    int32 MaxLogEntries = 200;

    UPROPERTY()
    TMap<FString, bool> TestResults;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;

    void AddTestLog(const FString& Entry);
};
