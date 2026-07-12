#include "Framework/Arena/Audio/LesFightArenaAudio.h"

void ULesFightArenaAudio::InitializeAudio(FArenaInfo Arena)
{
    FootstepLibraries.Add(ETerrainType::Stone, TEXT("/Game/Audio/Footsteps/Stone"));
    FootstepLibraries.Add(ETerrainType::Wood, TEXT("/Game/Audio/Footsteps/Wood"));
    FootstepLibraries.Add(ETerrainType::Metal, TEXT("/Game/Audio/Footsteps/Metal"));
    FootstepLibraries.Add(ETerrainType::Dirt, TEXT("/Game/Audio/Footsteps/Dirt"));
    FootstepLibraries.Add(ETerrainType::Water, TEXT("/Game/Audio/Footsteps/Water"));
}

void ULesFightArenaAudio::SetWeatherAudio(EWeatherType Weather)
{
    FString AmbientName;
    switch (Weather)
    {
    case EWeatherType::Rain:
        AmbientName = TEXT("Ambient_Rain");
        break;
    case EWeatherType::Snow:
        AmbientName = TEXT("Ambient_Snow");
        break;
    case EWeatherType::Fog:
        AmbientName = TEXT("Ambient_Fog");
        break;
    case EWeatherType::Storm:
        AmbientName = TEXT("Ambient_Storm");
        break;
    default:
        return;
    }

    if (!AmbientName.IsEmpty())
    {
        ActiveAmbientSounds.Add(AmbientName);
    }
}

void ULesFightArenaAudio::PlayFootstepSound(ETerrainType Surface)
{
    FString* Library = FootstepLibraries.Find(Surface);
    if (Library)
    {
    }
}

void ULesFightArenaAudio::PlayDestructionSound(EDestructionLevel Level)
{
    FString SoundPath;
    switch (Level)
    {
    case EDestructionLevel::Small:
        SoundPath = TEXT("/Game/Audio/Destruction/Destruction_Small");
        break;
    case EDestructionLevel::Medium:
        SoundPath = TEXT("/Game/Audio/Destruction/Destruction_Medium");
        break;
    case EDestructionLevel::Large:
        SoundPath = TEXT("/Game/Audio/Destruction/Destruction_Large");
        break;
    }
}

void ULesFightArenaAudio::PlayAmbientSound(FName SoundName)
{
    ActiveAmbientSounds.Add(SoundName.ToString());
}

void ULesFightArenaAudio::SetAmbientVolume(float Volume)
{
    CurrentAudio.AmbientVolume = Volume;
}

void ULesFightArenaAudio::SetWeatherVolume(float Volume)
{
    CurrentAudio.WeatherVolume = Volume;
}

void ULesFightArenaAudio::SetCrowdVolume(float Volume)
{
    CurrentAudio.CrowdVolume = Volume;
}

void ULesFightArenaAudio::PlayCrowdReaction(FName ReactionType)
{
    FString SoundPath = FString::Printf(TEXT("/Game/Audio/Crowd/%s"), *ReactionType.ToString());
}

void ULesFightArenaAudio::StopAllSounds()
{
    ActiveAmbientSounds.Empty();
}

void ULesFightArenaAudio::SetMusicTrack(FName TrackName)
{
    FString TrackPath = FString::Printf(TEXT("/Game/Audio/Music/%s"), *TrackName.ToString());
}

FArenaAudioState ULesFightArenaAudio::GetAudioState() const
{
    return CurrentAudio;
}
