#include "LesFightMovementSoundSystem.h"
#include "LesFightSoundEffectManager.h"
#include "Framework/Audio/Data/LesFightAudioData.h"

ULesFightMovementSoundSystem::ULesFightMovementSoundSystem()
{
    FootstepSoundPaths.Emplace(ETerrainType::Stone, "/Game/Audio/Footsteps/Foot_Stone");
    FootstepSoundPaths.Emplace(ETerrainType::Concrete, "/Game/Audio/Footsteps/Foot_Concrete");
    FootstepSoundPaths.Emplace(ETerrainType::Wood, "/Game/Audio/Footsteps/Foot_Wood");
    FootstepSoundPaths.Emplace(ETerrainType::Metal, "/Game/Audio/Footsteps/Foot_Metal");
    FootstepSoundPaths.Emplace(ETerrainType::Grass, "/Game/Audio/Footsteps/Foot_Grass");
    FootstepSoundPaths.Emplace(ETerrainType::Dirt, "/Game/Audio/Footsteps/Foot_Dirt");
    FootstepSoundPaths.Emplace(ETerrainType::Sand, "/Game/Audio/Footsteps/Foot_Sand");
    FootstepSoundPaths.Emplace(ETerrainType::Water, "/Game/Audio/Footsteps/Foot_Water");
    FootstepSoundPaths.Emplace(ETerrainType::Snow, "/Game/Audio/Footsteps/Foot_Snow");
    FootstepSoundPaths.Emplace(ETerrainType::Carpet, "/Game/Audio/Footsteps/Foot_Carpet");

    SpeedFootstepMap.Emplace(100.0f, "Walk");
    SpeedFootstepMap.Emplace(300.0f, "Jog");
    SpeedFootstepMap.Emplace(600.0f, "Run");
    SpeedFootstepMap.Emplace(900.0f, "Sprint");
}

void ULesFightMovementSoundSystem::PlayFootstep(ETerrainType Surface, FVector Location, float Speed)
{
    if (!OwnerManager.IsValid())
    {
        return;
    }

    FString* BasePath = FootstepSoundPaths.Find(Surface);
    if (BasePath == nullptr)
    {
        BasePath = &FootstepSoundPaths.FindOrAdd(ETerrainType::Stone);
    }

    FString SpeedKey = "Walk";
    for (const auto& Pair : SpeedFootstepMap)
    {
        if (Speed >= Pair.Key)
        {
            SpeedKey = Pair.Value;
        }
    }

    FName SoundName = FName(*(*BasePath + TEXT("_") + SpeedKey));
    float Volume = FMath::Clamp(MovementIntensity * 1.5f, 0.3f, 1.2f);

    if (OwnerManager->GetSoundEffectManager().IsValid())
    {
        OwnerManager->GetSoundEffectManager()->PlayMovementSound(EMovementSoundType::Footstep, Location, Volume);
    }
}

void ULesFightMovementSoundSystem::PlaySlide(FVector Location)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        float Volume = FMath::Clamp(MovementIntensity * 1.2f, 0.3f, 1.0f);
        OwnerManager->GetSoundEffectManager()->PlayMovementSound(EMovementSoundType::Slide, Location, Volume);
    }
}

void ULesFightMovementSoundSystem::PlayDodge(FVector Location)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        float Volume = FMath::Clamp(MovementIntensity * 1.3f, 0.4f, 1.0f);
        OwnerManager->GetSoundEffectManager()->PlayMovementSound(EMovementSoundType::Dodge, Location, Volume);
    }
}

void ULesFightMovementSoundSystem::PlayLanding(FVector Location, float Height)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        float Volume = FMath::Clamp((Height / 500.0f) * MovementIntensity, 0.3f, 1.2f);
        OwnerManager->GetSoundEffectManager()->PlayMovementSound(EMovementSoundType::Landing, Location, Volume);
    }
}

void ULesFightMovementSoundSystem::PlayJump(FVector Location)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        float Volume = FMath::Clamp(MovementIntensity * 0.8f, 0.3f, 1.0f);
        OwnerManager->GetSoundEffectManager()->PlayMovementSound(EMovementSoundType::Jump, Location, Volume);
    }
}

void ULesFightMovementSoundSystem::PlayRun(FVector Location, float Speed)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        float Volume = FMath::Clamp((Speed / 600.0f) * MovementIntensity, 0.3f, 1.0f);
        OwnerManager->GetSoundEffectManager()->PlayMovementSound(EMovementSoundType::Run, Location, Volume);
    }
}

void ULesFightMovementSoundSystem::PlayDash(FVector Location)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        float Volume = FMath::Clamp(MovementIntensity * 1.4f, 0.4f, 1.0f);
        OwnerManager->GetSoundEffectManager()->PlayMovementSound(EMovementSoundType::Dash, Location, Volume);
    }
}

void ULesFightMovementSoundSystem::SetMovementIntensity(float Intensity)
{
    MovementIntensity = FMath::Clamp(Intensity, 0.0f, 1.0f);
}

float ULesFightMovementSoundSystem::GetMovementIntensity() const
{
    return MovementIntensity;
}
