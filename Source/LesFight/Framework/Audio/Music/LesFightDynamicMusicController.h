#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightDynamicMusicController.generated.h"

class ULesFightAudioWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIntensityChanged, float, NewIntensity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLayerTriggered, EAudioLayerType, Layer);

UCLASS(Blueprintable)
class ULesFightDynamicMusicController : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void Update(float DeltaTime, float PlayerHealth, float OpponentHealth, int32 ComboCount, bool bUltimateReady);

    UFUNCTION(BlueprintPure, Category = "Audio|Music")
    float GetCurrentIntensityLevel() const;

    UFUNCTION(BlueprintPure, Category = "Audio|Music")
    TArray<FMusicLayerState> GetActiveLayers() const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void TriggerLayer(EAudioLayerType Layer, float FadeIn);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void SilenceLayer(EAudioLayerType Layer, float FadeOut);

    UFUNCTION(BlueprintPure, Category = "Audio|Music")
    FString GetMusicDescription() const;

    UPROPERTY(BlueprintAssignable, Category = "Audio|Events")
    FOnIntensityChanged OnIntensityChanged;

    UPROPERTY(BlueprintAssignable, Category = "Audio|Events")
    FOnLayerTriggered OnLayerTriggered;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    float Intensity;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    float TargetIntensity;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    TArray<FMusicLayerState> ActiveLayers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio|Music")
    float IntensitySmoothSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    TMap<float, TArray<EAudioLayerType>> IntensityLayerMap;

private:
    void BuildIntensityLayerMap();
    void UpdateLayers();

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
