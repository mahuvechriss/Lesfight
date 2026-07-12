#include "Framework/Audio/Music/LesFightDynamicMusicController.h"

void ULesFightDynamicMusicController::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    Intensity = 0.0f;
    TargetIntensity = 0.0f;
    IntensitySmoothSpeed = 2.0f;
    ActiveLayers.Empty();
    BuildIntensityLayerMap();
}

void ULesFightDynamicMusicController::BuildIntensityLayerMap()
{
    IntensityLayerMap.Empty();
    IntensityLayerMap.Add(0.2f, { EAudioLayerType::Rhythm });
    IntensityLayerMap.Add(0.4f, { EAudioLayerType::Bass });
    IntensityLayerMap.Add(0.6f, { EAudioLayerType::Melody });
    IntensityLayerMap.Add(0.7f, { EAudioLayerType::Harmony });
    IntensityLayerMap.Add(0.8f, { EAudioLayerType::Percussion });
    IntensityLayerMap.Add(0.9f, { EAudioLayerType::Vocals });
    IntensityLayerMap.Add(1.0f, { EAudioLayerType::FX });
}

void ULesFightDynamicMusicController::Update(float DeltaTime, float PlayerHealth, float OpponentHealth, int32 ComboCount, bool bUltimateReady)
{
    float HealthFactor = 0.0f;
    if (PlayerHealth > 0.0f)
    {
        float LowHealth = 1.0f - (PlayerHealth / 100.0f);
        float OpponentLowHealth = 1.0f - (OpponentHealth / 100.0f);
        float CloseToDeath = (PlayerHealth < 20.0f) ? 0.3f : 0.0f;
        HealthFactor = FMath::Clamp(LowHealth * 0.5f + OpponentLowHealth * 0.3f + CloseToDeath, 0.0f, 0.7f);
    }

    float ComboFactor = FMath::Clamp(ComboCount / 20.0f, 0.0f, 0.3f);

    float UltimateFactor = bUltimateReady ? 0.2f : 0.0f;

    TargetIntensity = FMath::Clamp(HealthFactor + ComboFactor + UltimateFactor, 0.0f, 1.0f);

    Intensity = FMath::FInterpTo(Intensity, TargetIntensity, DeltaTime, IntensitySmoothSpeed);

    UpdateLayers();
}

void ULesFightDynamicMusicController::UpdateLayers()
{
    TArray<float> Thresholds;
    IntensityLayerMap.GetKeys(Thresholds);
    Thresholds.Sort();

    for (float Threshold : Thresholds)
    {
        const TArray<EAudioLayerType>* LayersAtThreshold = IntensityLayerMap.Find(Threshold);
        if (!LayersAtThreshold) continue;

        bool bShouldBeActive = Intensity >= Threshold;

        for (EAudioLayerType LayerType : *LayersAtThreshold)
        {
            bool bFound = false;
            for (FMusicLayerState& Existing : ActiveLayers)
            {
                if (Existing.Layer == LayerType)
                {
                    bFound = true;
                    if (bShouldBeActive && !Existing.bActive)
                    {
                        Existing.bActive = true;
                        Existing.TargetVolume = 1.0f;
                        Existing.CurrentFadeTime = 0.0f;
                        OnLayerTriggered.Broadcast(LayerType);
                    }
                    else if (!bShouldBeActive && Existing.bActive)
                    {
                        Existing.bActive = false;
                        Existing.TargetVolume = 0.0f;
                        Existing.CurrentFadeTime = 0.0f;
                    }
                    break;
                }
            }
            if (!bFound && bShouldBeActive)
            {
                FMusicLayerState NewLayer;
                NewLayer.Layer = LayerType;
                NewLayer.bActive = true;
                NewLayer.Volume = 0.0f;
                NewLayer.TargetVolume = 1.0f;
                NewLayer.FadeDuration = 0.5f;
                NewLayer.CurrentFadeTime = 0.0f;
                ActiveLayers.Add(NewLayer);
                OnLayerTriggered.Broadcast(LayerType);
            }
        }
    }
}

float ULesFightDynamicMusicController::GetCurrentIntensityLevel() const
{
    return Intensity;
}

TArray<FMusicLayerState> ULesFightDynamicMusicController::GetActiveLayers() const
{
    return ActiveLayers;
}

void ULesFightDynamicMusicController::TriggerLayer(EAudioLayerType Layer, float FadeIn)
{
    for (FMusicLayerState& Existing : ActiveLayers)
    {
        if (Existing.Layer == Layer)
        {
            Existing.bActive = true;
            Existing.TargetVolume = 1.0f;
            Existing.FadeDuration = FadeIn;
            Existing.CurrentFadeTime = 0.0f;
            OnLayerTriggered.Broadcast(Layer);
            return;
        }
    }

    FMusicLayerState NewLayer;
    NewLayer.Layer = Layer;
    NewLayer.bActive = true;
    NewLayer.Volume = 0.0f;
    NewLayer.TargetVolume = 1.0f;
    NewLayer.FadeDuration = FadeIn;
    NewLayer.CurrentFadeTime = 0.0f;
    ActiveLayers.Add(NewLayer);
    OnLayerTriggered.Broadcast(Layer);
}

void ULesFightDynamicMusicController::SilenceLayer(EAudioLayerType Layer, float FadeOut)
{
    for (FMusicLayerState& Existing : ActiveLayers)
    {
        if (Existing.Layer == Layer)
        {
            Existing.bActive = false;
            Existing.TargetVolume = 0.0f;
            Existing.FadeDuration = FadeOut;
            Existing.CurrentFadeTime = 0.0f;
            return;
        }
    }
}

FString ULesFightDynamicMusicController::GetMusicDescription() const
{
    int32 ActiveLayerCount = 0;
    for (const FMusicLayerState& Layer : ActiveLayers)
    {
        if (Layer.bActive) ++ActiveLayerCount;
    }
    return FString::Printf(TEXT("Intensity: %.2f | Active Layers: %d/%d | Target: %.2f"),
        Intensity, ActiveLayerCount, ActiveLayers.Num(), TargetIntensity);
}
