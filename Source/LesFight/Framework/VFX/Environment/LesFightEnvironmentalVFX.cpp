#include "LesFightEnvironmentalVFX.h"
#include "Framework/VFX/Manager/LesFightVFXWorldManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

void ULesFightEnvironmentalVFX::Initialize(ULesFightVFXWorldManager* InOwner)
{
    OwnerManager = InOwner;
    MaxEnvEffects = 30;

    ArenaEffects.Empty();
    WeatherEffectPaths.Empty();

    WeatherEffectPaths.Add(EWeatherType::Rain, TEXT("Rain_Splash"));
    WeatherEffectPaths.Add(EWeatherType::Snow, TEXT("/Game/VFX/Weather/Snow"));
    WeatherEffectPaths.Add(EWeatherType::Fog, TEXT("/Game/VFX/Weather/Fog"));
    WeatherEffectPaths.Add(EWeatherType::Sandstorm, TEXT("/Game/VFX/Weather/Sandstorm"));
    WeatherEffectPaths.Add(EWeatherType::Clear, TEXT(""));
}

void ULesFightEnvironmentalVFX::InitializeForArena(EArenaType Arena)
{
    ArenaEffects.Empty();
    switch (Arena)
    {
    case EArenaType::Dojo:
        ArenaEffects.Add(Arena, { TEXT("Dust_Dojo"), TEXT("Debris_Wood") });
        break;
    case EArenaType::Beach:
        ArenaEffects.Add(Arena, { TEXT("Dust_Sand"), TEXT("Water_Splash"), TEXT("Palm_Leaves") });
        break;
    case EArenaType::Arena:
        ArenaEffects.Add(Arena, { TEXT("Dust_Stone"), TEXT("Debris_Stone") });
        break;
    case EArenaType::Forest:
        ArenaEffects.Add(Arena, { TEXT("Dust_Dirt"), TEXT("Leaf_Burst"), TEXT("Debris_Wood") });
        break;
    case EArenaType::Volcano:
        ArenaEffects.Add(Arena, { TEXT("Smoke_Volcanic"), TEXT("Fire_Embers"), TEXT("Debris_Rock") });
        break;
    case EArenaType::IceCave:
        ArenaEffects.Add(Arena, { TEXT("Ice_Shards"), TEXT("Dust_Ice"), TEXT("Crystal_Sparks") });
        break;
    default:
        ArenaEffects.Add(Arena, { TEXT("Dust_Default") });
        break;
    }
}

void ULesFightEnvironmentalVFX::PlayDustCloud(FVector Location, float Size)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, nullptr, Location);
}

void ULesFightEnvironmentalVFX::PlayDebrisBurst(FVector Location, int32 Count)
{
    for (int32 i = 0; i < FMath::Min(Count, 20); i++)
    {
        FVector RandomOffset = FVector(
            FMath::FRandRange(-100.0f, 100.0f),
            FMath::FRandRange(-100.0f, 100.0f),
            FMath::FRandRange(0.0f, 50.0f)
        );
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, nullptr, Location + RandomOffset);
    }
}

void ULesFightEnvironmentalVFX::PlayWaterSplash(FVector Location, float Force)
{
    FVector SplashLocation = Location;
    SplashLocation.Z = 0.0f;
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, nullptr, SplashLocation);
}

void ULesFightEnvironmentalVFX::PlayRainReaction(FVector Location)
{
    FVector ImpactLocation = Location;
    ImpactLocation.Z += 5.0f;
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, nullptr, ImpactLocation);
}

void ULesFightEnvironmentalVFX::PlayLeafBurst(FVector Location)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, nullptr, Location);
}

void ULesFightEnvironmentalVFX::PlaySmokeEffect(FVector Location, float Density)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, nullptr, Location);
}

void ULesFightEnvironmentalVFX::PlayFireEffect(FVector Location, float Intensity)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, nullptr, Location);
}

void ULesFightEnvironmentalVFX::SetWeatherVFX(EWeatherType Weather, EWeatherIntensity Intensity)
{
    if (const FString* Path = WeatherEffectPaths.Find(Weather))
    {
        ClearEnvironmentalEffects();
    }
}

void ULesFightEnvironmentalVFX::ClearEnvironmentalEffects()
{
    for (const FName& EffectName : ActiveEnvEffects)
    {
    }
    ActiveEnvEffects.Empty();
}
