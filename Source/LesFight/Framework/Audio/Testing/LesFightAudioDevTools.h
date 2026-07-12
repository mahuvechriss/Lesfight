#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioDevTools.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightAudioDevTools : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void EnableDebugMode(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void PlayTestSound(FName SoundName);

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void PlayTestMusicState(EMusicState State);

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void PlayTestVoiceLine(EVoiceContext Context);

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void TestSpatialAudio(FVector SoundPosition);

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void DisplayAudioStats();

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void LogActiveSounds();

    UFUNCTION(BlueprintCallable, Category = "Audio|DevTools")
    void RunAudioBenchmark();

    UFUNCTION(BlueprintPure, Category = "Audio|DevTools")
    FString GenerateAudioReport() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|DevTools")
    bool bDebugMode;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|DevTools")
    TArray<FString> TestLog;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|DevTools")
    TMap<FString, float> BenchmarkResults;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|DevTools")
    int32 MaxLogEntries;

private:
    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
