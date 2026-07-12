#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioPerformance.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightAudioPerformance : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Performance")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Performance")
    void SetMaxActiveSounds(int32 Max);

    UFUNCTION(BlueprintPure, Category = "Audio|Performance")
    int32 GetMaxActiveSounds() const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Performance")
    void SetSoundPoolSize(int32 MB);

    UFUNCTION(BlueprintPure, Category = "Audio|Performance")
    int32 GetSoundPoolSize() const;

    UFUNCTION(BlueprintPure, Category = "Audio|Performance")
    FAudioPerformanceStats GetCurrentStats() const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Performance")
    void OptimizeForQuality(int32 QualityLevel);

    UFUNCTION(BlueprintCallable, Category = "Audio|Performance")
    void StartProfiling();

    UFUNCTION(BlueprintCallable, Category = "Audio|Performance")
    void StopProfiling();

    UFUNCTION(BlueprintPure, Category = "Audio|Performance")
    FString GetPerformanceReport() const;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Audio|Performance")
    int32 MaxActiveSounds;

    UPROPERTY(BlueprintReadWrite, Category = "Audio|Performance")
    int32 SoundPoolMB;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Performance")
    FAudioPerformanceStats Stats;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Performance")
    bool bProfiling;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Performance")
    TArray<float> FrameAudioCPUTimes;

private:
    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
