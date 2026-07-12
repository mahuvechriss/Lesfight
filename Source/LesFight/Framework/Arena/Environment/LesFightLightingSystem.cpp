#include "LesFightLightingSystem.h"
#include "Framework/Arena/Data/LesFightArenaData.h"

static FArenaLightingState MakeLightingState(ELightingPreset InPreset, FLinearColor Ambient, FLinearColor Directional, FVector LightDir, float Intensity, float ShadowStr, float ShadowRes, bool bShadows, bool bGI, float GI, float Reflection, float Temp)
{
    FArenaLightingState State;
    State.Preset = InPreset;
    State.AmbientColor = Ambient;
    State.DirectionalColor = Directional;
    State.LightDirection = LightDir.GetSafeNormal();
    State.LightIntensity = Intensity;
    State.ShadowStrength = ShadowStr;
    State.ShadowResolution = ShadowRes;
    State.bCastShadows = bShadows;
    State.bEnableGI = bGI;
    State.GIIntensity = GI;
    State.ReflectionIntensity = Reflection;
    State.Temperature = Temp;
    return State;
}

void ULesFightLightingSystem::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    InitializePresets();

    CurrentPreset = ELightingPreset::ArenaDefault;
    CurrentState = Presets[ELightingPreset::ArenaDefault];
    TargetState = CurrentState;
    TransitionDuration = 0.0f;
    TransitionProgress = 0.0f;
    bTransitioning = false;
}

void ULesFightLightingSystem::InitializePresets()
{
    Presets.Empty();

    Presets.Add(ELightingPreset::SunnyDay, MakeLightingState(
        ELightingPreset::SunnyDay,
        FLinearColor(0.4f, 0.35f, 0.25f),
        FLinearColor(1.0f, 0.95f, 0.8f),
        FVector(0.5f, 0.5f, -1.0f),
        1.5f, 0.9f, 4096.0f, true, true, 1.2f, 1.0f, 5800.0f
    ));

    Presets.Add(ELightingPreset::Overcast, MakeLightingState(
        ELightingPreset::Overcast,
        FLinearColor(0.25f, 0.25f, 0.3f),
        FLinearColor(0.6f, 0.6f, 0.7f),
        FVector(0.3f, 0.2f, -0.9f),
        0.5f, 0.3f, 2048.0f, true, true, 0.8f, 0.6f, 6500.0f
    ));

    Presets.Add(ELightingPreset::Sunset, MakeLightingState(
        ELightingPreset::Sunset,
        FLinearColor(0.6f, 0.3f, 0.1f),
        FLinearColor(1.0f, 0.5f, 0.2f),
        FVector(-0.2f, 0.8f, -0.5f),
        1.2f, 0.7f, 3072.0f, true, true, 1.0f, 0.9f, 3500.0f
    ));

    Presets.Add(ELightingPreset::Night, MakeLightingState(
        ELightingPreset::Night,
        FLinearColor(0.03f, 0.03f, 0.1f),
        FLinearColor(0.1f, 0.1f, 0.3f),
        FVector(0.0f, 0.0f, -1.0f),
        0.15f, 0.2f, 1024.0f, false, false, 0.3f, 0.2f, 4500.0f
    ));

    Presets.Add(ELightingPreset::ArenaDefault, MakeLightingState(
        ELightingPreset::ArenaDefault,
        FLinearColor(0.3f, 0.3f, 0.3f),
        FLinearColor(1.0f, 0.95f, 0.8f),
        FVector(0.5f, 0.5f, -1.0f),
        1.0f, 0.8f, 2048.0f, true, true, 1.0f, 1.0f, 5500.0f
    ));

    Presets.Add(ELightingPreset::Dramatic, MakeLightingState(
        ELightingPreset::Dramatic,
        FLinearColor(0.02f, 0.02f, 0.02f),
        FLinearColor(1.2f, 1.1f, 1.0f),
        FVector(0.7f, -0.3f, -0.6f),
        2.0f, 1.0f, 4096.0f, true, false, 0.1f, 0.5f, 5000.0f
    ));

    Presets.Add(ELightingPreset::Cyberpunk, MakeLightingState(
        ELightingPreset::Cyberpunk,
        FLinearColor(0.15f, 0.02f, 0.15f),
        FLinearColor(1.0f, 0.2f, 0.5f),
        FVector(0.3f, 0.8f, -0.5f),
        1.2f, 0.6f, 2048.0f, true, true, 1.5f, 1.8f, 7000.0f
    ));

    Presets.Add(ELightingPreset::FantasyGlow, MakeLightingState(
        ELightingPreset::FantasyGlow,
        FLinearColor(0.25f, 0.05f, 0.35f),
        FLinearColor(0.5f, 0.3f, 1.0f),
        FVector(-0.2f, 0.5f, -0.8f),
        1.0f, 0.5f, 3072.0f, true, true, 1.8f, 2.0f, 8000.0f
    ));
}

void ULesFightLightingSystem::ApplyLightingPreset(ELightingPreset Preset)
{
    if (!Presets.Contains(Preset))
    {
        return;
    }

    CurrentPreset = Preset;
    CurrentState = Presets[Preset];
    TargetState = CurrentState;
    bTransitioning = false;
    TransitionProgress = 0.0f;

    OnLightingChanged.Broadcast(Preset);
}

void ULesFightLightingSystem::TransitionLighting(ELightingPreset Target, float Duration)
{
    if (!Presets.Contains(Target))
    {
        return;
    }

    TargetState = Presets[Target];
    TransitionDuration = Duration;
    TransitionProgress = 0.0f;
    bTransitioning = true;
}

void ULesFightLightingSystem::UpdateLighting(float DeltaTime)
{
    if (!bTransitioning)
    {
        return;
    }

    TransitionProgress += DeltaTime;
    float Alpha = FMath::Clamp(TransitionProgress / TransitionDuration, 0.0f, 1.0f);

    CurrentState.AmbientColor = FLinearColor::LerpUsingHSV(CurrentState.AmbientColor, TargetState.AmbientColor, Alpha);
    CurrentState.DirectionalColor = FLinearColor::LerpUsingHSV(CurrentState.DirectionalColor, TargetState.DirectionalColor, Alpha);
    CurrentState.LightDirection = FMath::Lerp(CurrentState.LightDirection, TargetState.LightDirection, Alpha).GetSafeNormal();
    CurrentState.LightIntensity = FMath::Lerp(CurrentState.LightIntensity, TargetState.LightIntensity, Alpha);
    CurrentState.ShadowStrength = FMath::Lerp(CurrentState.ShadowStrength, TargetState.ShadowStrength, Alpha);
    CurrentState.ShadowResolution = FMath::Lerp(CurrentState.ShadowResolution, TargetState.ShadowResolution, Alpha);
    CurrentState.GIIntensity = FMath::Lerp(CurrentState.GIIntensity, TargetState.GIIntensity, Alpha);
    CurrentState.ReflectionIntensity = FMath::Lerp(CurrentState.ReflectionIntensity, TargetState.ReflectionIntensity, Alpha);
    CurrentState.Temperature = FMath::Lerp(CurrentState.Temperature, TargetState.Temperature, Alpha);

    if (Alpha >= 1.0f)
    {
        CurrentState = TargetState;
        CurrentPreset = TargetState.Preset;
        bTransitioning = false;
        TransitionProgress = 0.0f;

        OnLightingChanged.Broadcast(CurrentPreset);
    }
}

ELightingPreset ULesFightLightingSystem::GetCurrentPreset() const
{
    return CurrentPreset;
}

FLinearColor ULesFightLightingSystem::GetAmbientColor() const
{
    return CurrentState.AmbientColor;
}

void ULesFightLightingSystem::SetLightIntensity(float Intensity)
{
    CurrentState.LightIntensity = Intensity;
}

void ULesFightLightingSystem::SetShadowQuality(int32 Quality)
{
    CurrentState.ShadowResolution = static_cast<float>(Quality);
}

void ULesFightLightingSystem::EnableLumen(bool bEnabled)
{
    CurrentState.bEnableGI = bEnabled;
}

void ULesFightLightingSystem::EnableVirtualShadowMaps(bool bEnabled)
{
    CurrentState.ShadowResolution = bEnabled ? 4096.0f : 2048.0f;
}

FString ULesFightLightingSystem::GetLightingDescription() const
{
    const UEnum* LightingEnum = StaticEnum<ELightingPreset>();
    FString PresetName = LightingEnum ? LightingEnum->GetNameStringByValue(static_cast<int64>(CurrentPreset)) : TEXT("Unknown");

    return FString::Printf(TEXT("Preset: %s | Intensity: %.1f | Shadows: %.1f | Lumen: %s | Temp: %.0fK"),
        *PresetName, CurrentState.LightIntensity, CurrentState.ShadowStrength,
        CurrentState.bEnableGI ? TEXT("On") : TEXT("Off"), CurrentState.Temperature);
}
