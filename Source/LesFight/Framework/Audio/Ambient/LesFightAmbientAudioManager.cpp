#include "LesFightAmbientAudioManager.h"

ULesFightAmbientAudioManager::ULesFightAmbientAudioManager()
{
    AmbientSoundLibrary = {
        TEXT("Wind_Soft"),
        TEXT("Wind_Strong"),
        TEXT("Rain_Light"),
        TEXT("Rain_Heavy"),
        TEXT("Thunder_Distant"),
        TEXT("Birds"),
        TEXT("Crickets"),
        TEXT("Water_Stream"),
        TEXT("Fire_Crackling"),
        TEXT("Crowd_Distant"),
        TEXT("Crowd_Cheering"),
        TEXT("Machinery_Hum"),
        TEXT("Temple_Chimes"),
        TEXT("Forest_Ambient"),
        TEXT("Cave_Drip")
    };
}

void ULesFightAmbientAudioManager::PlayAmbientSound(FName SoundName, FVector Location)
{
    if (ActiveAmbients.Num() >= MaxAmbientSounds)
    {
        return;
    }
    if (!AmbientSoundLibrary.Contains(SoundName.ToString()))
    {
        return;
    }
    if (ActiveAmbients.Contains(SoundName))
    {
        return;
    }
    ActiveAmbients.Add(SoundName, GlobalAmbientVolume);
}

void ULesFightAmbientAudioManager::StopAmbientSound(FName SoundName)
{
    ActiveAmbients.Remove(SoundName);
}

void ULesFightAmbientAudioManager::StopAllAmbient()
{
    ActiveAmbients.Empty();
}

void ULesFightAmbientAudioManager::SetAmbientZone(FName ZoneName)
{
    for (const auto& Entry : ActiveAmbients)
    {
        ActiveAmbients[Entry.Key] = GlobalAmbientVolume;
    }
}

void ULesFightAmbientAudioManager::SetAmbientVolume(float Volume)
{
    GlobalAmbientVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
    for (const auto& Entry : ActiveAmbients)
    {
        ActiveAmbients[Entry.Key] = GlobalAmbientVolume;
    }
}

void ULesFightAmbientAudioManager::CrossfadeAmbient(FName FromSound, FName ToSound, float Duration)
{
    if (ActiveAmbients.Contains(FromSound))
    {
        ActiveAmbients.Remove(FromSound);
    }
    if (AmbientSoundLibrary.Contains(ToSound.ToString()) && !ActiveAmbients.Contains(ToSound))
    {
        ActiveAmbients.Add(ToSound, 0.0f);
    }
}

TMap<FName, float> ULesFightAmbientAudioManager::GetActiveAmbientSounds() const
{
    return ActiveAmbients;
}

bool ULesFightAmbientAudioManager::IsAmbientPlaying(FName SoundName) const
{
    return ActiveAmbients.Contains(SoundName);
}
