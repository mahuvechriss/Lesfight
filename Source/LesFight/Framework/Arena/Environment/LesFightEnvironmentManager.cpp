#include "LesFightEnvironmentManager.h"
#include "Framework/Arena/Data/LesFightArenaData.h"

void ULesFightEnvironmentManager::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightEnvironmentManager::InitializeEnvironment(FArenaInfo Arena)
{
    CurrentLighting = FArenaLightingState();
    CurrentLighting.Preset = Arena.SupportedLighting.Num() > 0 ? Arena.SupportedLighting[0] : ELightingPreset::SunnyDay;
    CurrentLighting.AmbientColor = FLinearColor(0.3f, 0.3f, 0.3f);
    CurrentLighting.DirectionalColor = FLinearColor(1.0f, 0.95f, 0.8f);
    CurrentLighting.LightDirection = FVector(0.5f, 0.5f, -1.0f).GetSafeNormal();
    CurrentLighting.LightIntensity = 1.0f;
    CurrentLighting.ShadowStrength = 0.8f;
    CurrentLighting.bCastShadows = true;
    CurrentLighting.bEnableGI = true;
    CurrentLighting.GIIntensity = 1.0f;

    CurrentWeather = FWeatherState();
    CurrentWeather.WeatherType = Arena.SupportedWeather.Num() > 0 ? Arena.SupportedWeather[0] : EWeatherType::Clear;
    CurrentWeather.Intensity = EWeatherIntensity::Moderate;
    CurrentWeather.WindSpeed = 5.0f;
    CurrentWeather.WindDirection = FVector(1.0f, 0.0f, 0.0f);
    CurrentWeather.Precipitation = 0.0f;
    CurrentWeather.FogDensity = 0.02f;
    CurrentWeather.FogColor = FLinearColor(0.6f, 0.6f, 0.6f);
    CurrentWeather.Visibility = 10000.0f;
    CurrentWeather.bIsTransitioning = false;
    CurrentWeather.CurrentTransitionTime = 0.0f;
    CurrentWeather.TransitionDuration = 2.0f;

    ArenaTerrain = Arena.TerrainTypes;
    EnvironmentTime = 12.0f;
}

void ULesFightEnvironmentManager::UpdateEnvironment(float DeltaTime)
{
    if (CurrentWeather.bIsTransitioning)
    {
        CurrentWeather.CurrentTransitionTime += DeltaTime;
        if (CurrentWeather.CurrentTransitionTime >= CurrentWeather.TransitionDuration)
        {
            CurrentWeather.bIsTransitioning = false;
            CurrentWeather.CurrentTransitionTime = 0.0f;
        }
    }

    EnvironmentTime += DeltaTime * 0.01f;
    if (EnvironmentTime > 24.0f)
    {
        EnvironmentTime -= 24.0f;
    }
}

void ULesFightEnvironmentManager::SetWeather(EWeatherType Weather, EWeatherIntensity Intensity)
{
    CurrentWeather.WeatherType = Weather;
    CurrentWeather.Intensity = Intensity;
    CurrentWeather.bIsTransitioning = false;
    CurrentWeather.CurrentTransitionTime = 0.0f;

    switch (Weather)
    {
    case EWeatherType::Clear:
        CurrentWeather.Precipitation = 0.0f;
        CurrentWeather.FogDensity = 0.01f;
        CurrentWeather.Visibility = 15000.0f;
        break;
    case EWeatherType::Rain:
        CurrentWeather.Precipitation = 1.0f;
        CurrentWeather.FogDensity = 0.05f;
        CurrentWeather.Visibility = 8000.0f;
        break;
    case EWeatherType::Storm:
        CurrentWeather.Precipitation = 2.0f;
        CurrentWeather.FogDensity = 0.08f;
        CurrentWeather.Visibility = 5000.0f;
        break;
    case EWeatherType::Snow:
        CurrentWeather.Precipitation = 1.5f;
        CurrentWeather.FogDensity = 0.04f;
        CurrentWeather.Visibility = 6000.0f;
        break;
    case EWeatherType::Fog:
        CurrentWeather.Precipitation = 0.0f;
        CurrentWeather.FogDensity = 0.15f;
        CurrentWeather.Visibility = 2000.0f;
        break;
    case EWeatherType::Wind:
        CurrentWeather.Precipitation = 0.0f;
        CurrentWeather.FogDensity = 0.02f;
        CurrentWeather.Visibility = 12000.0f;
        break;
    case EWeatherType::Dust:
        CurrentWeather.Precipitation = 0.0f;
        CurrentWeather.FogDensity = 0.1f;
        CurrentWeather.Visibility = 4000.0f;
        break;
    default:
        break;
    }
}

void ULesFightEnvironmentManager::SetLighting(ELightingPreset Preset)
{
    CurrentLighting.Preset = Preset;
}

void ULesFightEnvironmentManager::TransitionToWeather(EWeatherType Target, float Duration)
{
    CurrentWeather.WeatherType = Target;
    CurrentWeather.TransitionDuration = Duration;
    CurrentWeather.CurrentTransitionTime = 0.0f;
    CurrentWeather.bIsTransitioning = true;
}

EWeatherType ULesFightEnvironmentManager::GetCurrentWeather() const
{
    return CurrentWeather.WeatherType;
}

ELightingPreset ULesFightEnvironmentManager::GetCurrentLighting() const
{
    return CurrentLighting.Preset;
}

ETerrainType ULesFightEnvironmentManager::GetTerrainAtLocation(FVector Location) const
{
    if (ArenaTerrain.Num() == 0)
    {
        return ETerrainType::Stone;
    }

    int32 Index = FMath::Abs(FMath::RoundToInt(Location.X * 0.1f + Location.Y * 0.05f)) % ArenaTerrain.Num();
    return ArenaTerrain[Index];
}

ETerrainType ULesFightEnvironmentManager::GetSurfaceTypeAtLocation(FVector Location) const
{
    return GetTerrainAtLocation(Location);
}

FString ULesFightEnvironmentManager::GetEnvironmentDescription() const
{
    const UEnum* WeatherEnum = StaticEnum<EWeatherType>();
    const UEnum* LightingEnum = StaticEnum<ELightingPreset>();

    FString WeatherStr = WeatherEnum ? WeatherEnum->GetNameStringByValue(static_cast<int64>(CurrentWeather.WeatherType)) : TEXT("Unknown");
    FString LightingStr = LightingEnum ? LightingEnum->GetNameStringByValue(static_cast<int64>(CurrentLighting.Preset)) : TEXT("Unknown");

    return FString::Printf(TEXT("Weather: %s | Lighting: %s | Time: %.1fh | Terrains: %d"), *WeatherStr, *LightingStr, EnvironmentTime, ArenaTerrain.Num());
}
