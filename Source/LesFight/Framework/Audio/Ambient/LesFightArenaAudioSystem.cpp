#include "LesFightArenaAudioSystem.h"

ULesFightArenaAudioSystem::ULesFightArenaAudioSystem()
{
    FArenaAudioState TempleCourtyard;
    TempleCourtyard.AmbientSound = TEXT("Temple_Chimes");
    TempleCourtyard.ReverbPreset = EReverbPreset::Outdoor;
    TempleCourtyard.bHasCrowd = false;
    TempleCourtyard.AmbientVolumeModifier = 0.8f;
    ArenaAudioProfiles.Add(EArenaType::TempleCourtyard, TempleCourtyard);
    ArenaMusicTracks.Add(EArenaType::TempleCourtyard, TEXT("Music_TempleCourtyard"));

    FArenaAudioState MountainDojo;
    MountainDojo.AmbientSound = TEXT("Wind_Soft");
    MountainDojo.ReverbPreset = EReverbPreset::LargeRoom;
    MountainDojo.bHasCrowd = true;
    MountainDojo.AmbientVolumeModifier = 0.7f;
    ArenaAudioProfiles.Add(EArenaType::MountainDojo, MountainDojo);
    ArenaMusicTracks.Add(EArenaType::MountainDojo, TEXT("Music_MountainDojo"));

    FArenaAudioState BambooForest;
    BambooForest.AmbientSound = TEXT("Forest_Ambient");
    BambooForest.ReverbPreset = EReverbPreset::Outdoor;
    BambooForest.bHasCrowd = true;
    BambooForest.AmbientVolumeModifier = 0.9f;
    ArenaAudioProfiles.Add(EArenaType::BambooForest, BambooForest);
    ArenaMusicTracks.Add(EArenaType::BambooForest, TEXT("Music_BambooForest"));

    FArenaAudioState AncientVillage;
    AncientVillage.AmbientSound = TEXT("Crickets");
    AncientVillage.ReverbPreset = EReverbPreset::Outdoor;
    AncientVillage.bHasCrowd = true;
    AncientVillage.AmbientVolumeModifier = 0.85f;
    ArenaAudioProfiles.Add(EArenaType::AncientVillage, AncientVillage);
    ArenaMusicTracks.Add(EArenaType::AncientVillage, TEXT("Music_AncientVillage"));

    FArenaAudioState PalaceGrounds;
    PalaceGrounds.AmbientSound = TEXT("Wind_Soft");
    PalaceGrounds.ReverbPreset = EReverbPreset::LargeRoom;
    PalaceGrounds.bHasCrowd = true;
    PalaceGrounds.AmbientVolumeModifier = 0.75f;
    ArenaAudioProfiles.Add(EArenaType::PalaceGrounds, PalaceGrounds);
    ArenaMusicTracks.Add(EArenaType::PalaceGrounds, TEXT("Music_PalaceGrounds"));

    FArenaAudioState CityRooftop;
    CityRooftop.AmbientSound = TEXT("Wind_Strong");
    CityRooftop.ReverbPreset = EReverbPreset::Outdoor;
    CityRooftop.bHasCrowd = false;
    CityRooftop.AmbientVolumeModifier = 0.7f;
    ArenaAudioProfiles.Add(EArenaType::CityRooftop, CityRooftop);
    ArenaMusicTracks.Add(EArenaType::CityRooftop, TEXT("Music_CityRooftop"));

    FArenaAudioState UndergroundArena;
    UndergroundArena.AmbientSound = TEXT("Machinery_Hum");
    UndergroundArena.ReverbPreset = EReverbPreset::Underground;
    UndergroundArena.bHasCrowd = true;
    UndergroundArena.AmbientVolumeModifier = 1.0f;
    ArenaAudioProfiles.Add(EArenaType::UndergroundArena, UndergroundArena);
    ArenaMusicTracks.Add(EArenaType::UndergroundArena, TEXT("Music_UndergroundArena"));

    CurrentArenaAudio = TempleCourtyard;
}

void ULesFightArenaAudioSystem::SetArenaAudio(EArenaType ArenaType)
{
    if (const FArenaAudioState* Profile = ArenaAudioProfiles.Find(ArenaType))
    {
        CurrentArenaAudio = *Profile;
    }
}

void ULesFightArenaAudioSystem::ApplyWeatherAudio(EWeatherType Weather, EWeatherIntensity Intensity)
{
    switch (Weather)
    {
    case EWeatherType::Rain:
        if (Intensity >= EWeatherIntensity::Moderate)
        {
            CurrentArenaAudio.WeatherOverrideSound = TEXT("Rain_Heavy");
        }
        else
        {
            CurrentArenaAudio.WeatherOverrideSound = TEXT("Rain_Light");
        }
        break;
    case EWeatherType::Thunderstorm:
        CurrentArenaAudio.WeatherOverrideSound = TEXT("Thunder_Distant");
        break;
    case EWeatherType::Windy:
        CurrentArenaAudio.WeatherOverrideSound = TEXT("Wind_Strong");
        break;
    case EWeatherType::Foggy:
        CurrentArenaAudio.WeatherOverrideSound = TEXT("Wind_Soft");
        break;
    default:
        CurrentArenaAudio.WeatherOverrideSound = NAME_None;
        break;
    }
}

void ULesFightArenaAudioSystem::PlayArenaFootstep(ETerrainType Surface, FVector Location)
{
}

void ULesFightArenaAudioSystem::PlayArenaDestructionSound(EDestructionLevel Level, FVector Location)
{
}

void ULesFightArenaAudioSystem::PlayArenaCrowdReaction(FName ReactionType)
{
}

FArenaAudioState ULesFightArenaAudioSystem::GetArenaAudioProfile() const
{
    return CurrentArenaAudio;
}
