#include "LesFightArenaEnvironmentState.h"
#include "Framework/Arena/Data/LesFightArenaData.h"

void ULesFightArenaEnvironmentState::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightArenaEnvironmentState::InitializeState(FArenaInfo Arena)
{
    CurrentState = FArenaEnvironmentState();
    CurrentState.CurrentArena = Arena;
    CurrentState.ArenaVersion = 1;

    LoadDefaultsFromArenaInfo(Arena);
    ResetToDefaults();
}

void ULesFightArenaEnvironmentState::LoadDefaultsFromArenaInfo(const FArenaInfo& Arena)
{
    DefaultWeather = FWeatherState();
    DefaultWeather.WeatherType = Arena.SupportedWeather.Num() > 0 ? Arena.SupportedWeather[0] : EWeatherType::Clear;
    DefaultWeather.Intensity = EWeatherIntensity::Moderate;
    DefaultWeather.WindSpeed = 5.0f;
    DefaultWeather.WindDirection = FVector(1.0f, 0.0f, 0.0f);
    DefaultWeather.Precipitation = 0.0f;
    DefaultWeather.FogDensity = 0.02f;
    DefaultWeather.FogColor = FLinearColor(0.6f, 0.6f, 0.6f);
    DefaultWeather.Visibility = 10000.0f;
    DefaultWeather.TransitionDuration = 2.0f;
    DefaultWeather.CurrentTransitionTime = 0.0f;
    DefaultWeather.bIsTransitioning = false;

    DefaultLighting = FArenaLightingState();
    DefaultLighting.Preset = Arena.SupportedLighting.Num() > 0 ? Arena.SupportedLighting[0] : ELightingPreset::SunnyDay;
    DefaultLighting.AmbientColor = FLinearColor(0.3f, 0.3f, 0.3f);
    DefaultLighting.DirectionalColor = FLinearColor(1.0f, 0.95f, 0.8f);
    DefaultLighting.LightDirection = FVector(0.5f, 0.5f, -1.0f).GetSafeNormal();
    DefaultLighting.LightIntensity = 1.0f;
    DefaultLighting.ShadowStrength = 0.8f;
    DefaultLighting.ShadowResolution = 2048.0f;
    DefaultLighting.bCastShadows = true;
    DefaultLighting.bEnableGI = true;
    DefaultLighting.GIIntensity = 1.0f;
    DefaultLighting.ReflectionIntensity = 1.0f;
    DefaultLighting.Temperature = 5500.0f;

    CurrentState.SurfaceTypes = Arena.TerrainTypes;
}

void ULesFightArenaEnvironmentState::SetWeather(const FWeatherState& Weather)
{
    CurrentState.Weather = Weather;
    if (!Weather.bIsTransitioning)
    {
        CurrentState.Weather.bIsTransitioning = true;
        CurrentState.Weather.CurrentTransitionTime = 0.0f;
    }
}

void ULesFightArenaEnvironmentState::SetLighting(const FArenaLightingState& Lighting)
{
    CurrentState.Lighting = Lighting;
}

FArenaEnvironmentState ULesFightArenaEnvironmentState::GetCurrentState() const
{
    return CurrentState;
}

void ULesFightArenaEnvironmentState::UpdateState(float DeltaTime)
{
    if (CurrentState.Weather.bIsTransitioning)
    {
        CurrentState.Weather.CurrentTransitionTime += DeltaTime;
        if (CurrentState.Weather.CurrentTransitionTime >= CurrentState.Weather.TransitionDuration)
        {
            CurrentState.Weather.bIsTransitioning = false;
            CurrentState.Weather.CurrentTransitionTime = 0.0f;
        }
    }

    CurrentState.TimeOfDay += DeltaTime * 0.01f;
    if (CurrentState.TimeOfDay > 24.0f)
    {
        CurrentState.TimeOfDay -= 24.0f;
    }
}

FArenaEnvironmentState ULesFightArenaEnvironmentState::SerializeState() const
{
    FArenaEnvironmentState Serialized = CurrentState;
    Serialized.DestructibleStates = ObjectStateCache;
    return Serialized;
}

void ULesFightArenaEnvironmentState::DeserializeState(const FArenaEnvironmentState& State)
{
    CurrentState = State;
    CurrentState.Weather.bIsTransitioning = false;
    CurrentState.Weather.CurrentTransitionTime = 0.0f;
    ObjectStateCache = State.DestructibleStates;
}

void ULesFightArenaEnvironmentState::ResetToDefaults()
{
    CurrentState.Weather = DefaultWeather;
    CurrentState.Lighting = DefaultLighting;
    CurrentState.DestructibleStates.Empty();
    CurrentState.TimeOfDay = 12.0f;
    CurrentState.Weather.bIsTransitioning = false;
    CurrentState.Weather.CurrentTransitionTime = 0.0f;
}
