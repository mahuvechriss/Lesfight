#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioEffectsProcessor.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightAudioEffectsProcessor : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void ApplyReverb(FReverbZoneData ReverbData);

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void RemoveReverb();

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void ApplyLowPassFilter(float CutoffFrequency);

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void RemoveLowPassFilter();

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void ApplyHighPassFilter(float CutoffFrequency);

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void RemoveHighPassFilter();

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void ApplyEQ(float LowGain, float MidGain, float HighGain);

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void ApplyCompression(float Threshold, float Ratio, float Attack, float Release);

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void SetEnvironmentalFilter(EArenaType ArenaType);

    UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
    void ClearAllEffects();

    UFUNCTION(BlueprintPure, Category = "Audio|Effects")
    bool IsEffectActive(FName EffectName) const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Effects")
    TMap<FName, bool> ActiveEffects;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Effects")
    TMap<FName, float> EffectParameters;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Effects")
    FReverbZoneData CurrentReverb;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Effects")
    bool bLowPassActive;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Effects")
    bool bHighPassActive;

private:
    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
