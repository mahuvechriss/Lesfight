#include "LesFightWeatherSystem.h"
#include "Framework/Arena/Data/LesFightArenaData.h"

void ULesFightWeatherSystem::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;

    ActiveWeather = EWeatherType::Clear;
    Intensity = EWeatherIntensity::Moderate;
    WindDirection = FVector(1.0f, 0.0f, 0.0f);
    WindSpeed = 5.0f;
    VisibilityModifier = 1.0f;
    ParticleDensity = 0.0f;

    IntensityScales.Empty();
    IntensityScales.Add(EWeatherType::Clear, 0.0f);
    IntensityScales.Add(EWeatherType::Rain, 1.0f);
    IntensityScales.Add(EWeatherType::Storm, 1.5f);
    IntensityScales.Add(EWeatherType::Snow, 1.0f);
    IntensityScales.Add(EWeatherType::Fog, 0.8f);
    IntensityScales.Add(EWeatherType::Wind, 0.6f);
    IntensityScales.Add(EWeatherType::Dust, 0.7f);
}

void ULesFightWeatherSystem::ActivateWeather(EWeatherType Type, EWeatherIntensity InIntensity)
{
    ActiveWeather = Type;
    Intensity = InIntensity;

    switch (InIntensity)
    {
    case EWeatherIntensity::Light:
        ParticleDensity = 250.0f;
        break;
    case EWeatherIntensity::Moderate:
        ParticleDensity = 500.0f;
        break;
    case EWeatherIntensity::Heavy:
        ParticleDensity = 1000.0f;
        break;
    case EWeatherIntensity::Extreme:
        ParticleDensity = 2000.0f;
        break;
    default:
        ParticleDensity = 0.0f;
        break;
    }

    float Scale = IntensityScales.FindRef(Type);
    switch (Type)
    {
    case EWeatherType::Clear:
        VisibilityModifier = 1.0f;
        break;
    case EWeatherType::Rain:
        VisibilityModifier = FMath::Clamp(0.9f - (static_cast<float>(InIntensity) * 0.15f), 0.3f, 0.9f);
        break;
    case EWeatherType::Storm:
        VisibilityModifier = FMath::Clamp(0.7f - (static_cast<float>(InIntensity) * 0.15f), 0.2f, 0.7f);
        break;
    case EWeatherType::Snow:
        VisibilityModifier = FMath::Clamp(0.85f - (static_cast<float>(InIntensity) * 0.12f), 0.35f, 0.85f);
        break;
    case EWeatherType::Fog:
        VisibilityModifier = FMath::Clamp(0.5f - (static_cast<float>(InIntensity) * 0.1f), 0.1f, 0.5f);
        break;
    case EWeatherType::Wind:
        VisibilityModifier = 0.95f;
        break;
    case EWeatherType::Dust:
        VisibilityModifier = FMath::Clamp(0.7f - (static_cast<float>(InIntensity) * 0.1f), 0.25f, 0.7f);
        break;
    default:
        VisibilityModifier = 1.0f;
        break;
    }
}

void ULesFightWeatherSystem::DeactivateWeather()
{
    ActiveWeather = EWeatherType::Clear;
    Intensity = EWeatherIntensity::Light;
    ParticleDensity = 0.0f;
    VisibilityModifier = 1.0f;
}

void ULesFightWeatherSystem::UpdateWeather(float DeltaTime)
{
    if (ActiveWeather == EWeatherType::Fog || ActiveWeather == EWeatherType::Dust)
    {
        VisibilityModifier = FMath::Max(VisibilityModifier - DeltaTime * 0.05f, 0.1f);
    }
    else if (ActiveWeather == EWeatherType::Clear)
    {
        VisibilityModifier = FMath::Min(VisibilityModifier + DeltaTime * 0.1f, 1.0f);
    }

    WindDirection = WindDirection.RotateAngleAxis(DeltaTime * 0.5f, FVector::UpVector);
    WindDirection.Normalize();
}

EWeatherType ULesFightWeatherSystem::GetActiveWeather() const
{
    return ActiveWeather;
}

EWeatherIntensity ULesFightWeatherSystem::GetIntensity() const
{
    return Intensity;
}

void ULesFightWeatherSystem::GetWindParams(FVector& Direction, float& Speed) const
{
    Direction = WindDirection;
    Speed = WindSpeed;
}

void ULesFightWeatherSystem::SetWind(FVector Direction, float Speed)
{
    WindDirection = Direction.GetSafeNormal();
    WindSpeed = Speed;
}

FString ULesFightWeatherSystem::GenerateRainParticles() const
{
    return TEXT("/Niagara/FX/Particles/Rain/FX_RainSystem.FX_RainSystem");
}

FString ULesFightWeatherSystem::GenerateSnowParticles() const
{
    return TEXT("/Niagara/FX/Particles/Snow/FX_SnowSystem.FX_SnowSystem");
}

FString ULesFightWeatherSystem::GenerateFog() const
{
    return TEXT("/Niagara/FX/Particles/Fog/FX_FogSystem.FX_FogSystem");
}

bool ULesFightWeatherSystem::IsWeatherActive() const
{
    return ActiveWeather != EWeatherType::Clear;
}

float ULesFightWeatherSystem::GetVisibilityModifier() const
{
    return VisibilityModifier;
}
