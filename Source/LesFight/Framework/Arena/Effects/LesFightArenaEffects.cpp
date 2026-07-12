#include "Framework/Arena/Effects/LesFightArenaEffects.h"

void ULesFightArenaEffects::InitializeEffects(FArenaInfo Arena)
{
    ImpactEffectPaths.Add(ETerrainType::Stone, TEXT("/Game/Effects/Impact_Stone"));
    ImpactEffectPaths.Add(ETerrainType::Wood, TEXT("/Game/Effects/Impact_Wood"));
    ImpactEffectPaths.Add(ETerrainType::Metal, TEXT("/Game/Effects/Impact_Metal"));
    ImpactEffectPaths.Add(ETerrainType::Dirt, TEXT("/Game/Effects/Impact_Dirt"));
    ImpactEffectPaths.Add(ETerrainType::Water, TEXT("/Game/Effects/Impact_Water"));

    DestructionEffectPaths.Add(EDestructionLevel::Small, TEXT("/Game/Effects/Destruction_Small"));
    DestructionEffectPaths.Add(EDestructionLevel::Medium, TEXT("/Game/Effects/Destruction_Medium"));
    DestructionEffectPaths.Add(EDestructionLevel::Large, TEXT("/Game/Effects/Destruction_Large"));

    WeatherEffectPaths.Add(EWeatherType::Clear, TEXT(""));
    WeatherEffectPaths.Add(EWeatherType::Rain, TEXT("/Game/Effects/Weather_Rain"));
    WeatherEffectPaths.Add(EWeatherType::Snow, TEXT("/Game/Effects/Weather_Snow"));
    WeatherEffectPaths.Add(EWeatherType::Fog, TEXT("/Game/Effects/Weather_Fog"));
    WeatherEffectPaths.Add(EWeatherType::Storm, TEXT("/Game/Effects/Weather_Storm"));
}

void ULesFightArenaEffects::PlayImpactEffect(FVector Location, FVector Normal, ETerrainType Surface)
{
    FString* Path = ImpactEffectPaths.Find(Surface);
    if (Path && !Path->IsEmpty())
    {
        ActiveEffects.Add(*Path);
    }
}

void ULesFightArenaEffects::PlayDestructionEffect(FVector Location, EDestructionLevel Level)
{
    FString* Path = DestructionEffectPaths.Find(Level);
    if (Path && !Path->IsEmpty())
    {
        ActiveEffects.Add(*Path);
    }
}

void ULesFightArenaEffects::PlayWeatherEffect(EWeatherType Weather)
{
    FString* Path = WeatherEffectPaths.Find(Weather);
    if (Path && !Path->IsEmpty())
    {
        ActiveEffects.Add(*Path);
    }
}

void ULesFightArenaEffects::StopWeatherEffect()
{
    for (int32 i = ActiveEffects.Num() - 1; i >= 0; --i)
    {
        if (ActiveEffects[i].StartsWith(TEXT("/Game/Effects/Weather_")))
        {
            ActiveEffects.RemoveAt(i);
        }
    }
}

void ULesFightArenaEffects::UpdateEffects(float DeltaTime)
{
}

void ULesFightArenaEffects::ClearAllEffects()
{
    ActiveEffects.Empty();
}
