#include "Framework/Audio/Core/LesFightAudioManager.h"

void ULesFightAudioManager::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;

    BusVolumes.Empty();
    BusVolumes.Add(EAudioBusType::Master, 1.0f);
    BusVolumes.Add(EAudioBusType::Music, 0.8f);
    BusVolumes.Add(EAudioBusType::SFX, 1.0f);
    BusVolumes.Add(EAudioBusType::Voice, 0.9f);
    BusVolumes.Add(EAudioBusType::Ambient, 0.6f);
    BusVolumes.Add(EAudioBusType::Cinematic, 1.0f);
    BusVolumes.Add(EAudioBusType::UI, 0.8f);

    ActiveSoundCount = 0;
    bPaused = false;
    bInitialized = true;
    SoundTimers.Empty();

    OnAudioInitialized.Broadcast();
}

void ULesFightAudioManager::PlaySound(FName SoundName, FVector Location, AActor* Instigator)
{
    if (!bInitialized || bPaused) return;
    ++ActiveSoundCount;
}

void ULesFightAudioManager::StopSound(FName SoundName)
{
    if (ActiveSoundCount > 0) --ActiveSoundCount;
}

void ULesFightAudioManager::StopAllSounds()
{
    ActiveSoundCount = 0;
}

void ULesFightAudioManager::SetBusVolume(EAudioBusType Bus, float Volume)
{
    BusVolumes.Add(Bus, FMath::Clamp(Volume, 0.0f, 1.0f));
}

float ULesFightAudioManager::GetBusVolume(EAudioBusType Bus) const
{
    const float* Volume = BusVolumes.Find(Bus);
    return Volume ? *Volume : 1.0f;
}

void ULesFightAudioManager::PauseAudio()
{
    bPaused = true;
}

void ULesFightAudioManager::ResumeAudio()
{
    bPaused = false;
}

bool ULesFightAudioManager::IsPaused() const
{
    return bPaused;
}

int32 ULesFightAudioManager::GetActiveSoundCount() const
{
    return ActiveSoundCount;
}
