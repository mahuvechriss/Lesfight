#include "LesFightMartialArtsAudio.h"
#include "LesFightMartialArtsManager.h"
#include "Engine/World.h"

ULesFightMartialArtsAudio::ULesFightMartialArtsAudio()
    : BreathTimer(0.0f)
    , BreathInterval(4.0f)
    , VoiceCooldown(2.0f)
    , CurrentStyle(EFightingStyle::None)
    , LastVoiceTime(0.0f)
    , LastFootstepTime(0.0f)
{
}

void ULesFightMartialArtsAudio::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    BreathTimer = BreathInterval;
    LastVoiceTime = -VoiceCooldown;
}

void ULesFightMartialArtsAudio::Tick(float DeltaTime)
{
    BreathTimer -= DeltaTime;
    if (BreathTimer <= 0.0f)
    {
        BreathTimer = BreathInterval;
        PlayBreathingSound(0.3f);
    }

    LastVoiceTime += DeltaTime;
}

void ULesFightMartialArtsAudio::PlayAttackSound(EFightingStyle Style, int32 ComboStep)
{
    const FStyleAudioProfile* Profile = StyleAudioProfiles.Find(Style);
    if (!Profile) return;
    if (LastVoiceTime < VoiceCooldown) return;

    PlayVoiceFromSet(Profile->AttackVoiceSet);
    LastVoiceTime = 0.0f;
}

void ULesFightMartialArtsAudio::PlayHitSound(float ImpactForce)
{
    const FStyleAudioProfile* Profile = StyleAudioProfiles.Find(CurrentStyle);
    if (!Profile) return;

    int32 SoundIndex = FMath::Clamp(
        FMath::FloorToInt(ImpactForce / 25.0f), 0,
        Profile->ImpactSounds.Num() - 1);

    if (Profile->ImpactSounds.IsValidIndex(SoundIndex))
    {
        PlaySoundFromSet({Profile->ImpactSounds[SoundIndex]}, FVector::ZeroVector);
    }
}

void ULesFightMartialArtsAudio::PlayCounterSound(ECounterType CounterType)
{
    const FStyleAudioProfile* Profile = StyleAudioProfiles.Find(CurrentStyle);
    if (!Profile) return;

    PlayVoiceFromSet(Profile->CounterVoiceSet);
}

void ULesFightMartialArtsAudio::PlayUltimateSound(EFightingStyle Style)
{
    const FStyleAudioProfile* Profile = StyleAudioProfiles.Find(Style);
    if (!Profile) return;

    PlayVoiceFromSet(Profile->UltimateVoiceSet);
}

void ULesFightMartialArtsAudio::PlayVictorySound(EFightingStyle Style)
{
    const FStyleAudioProfile* Profile = StyleAudioProfiles.Find(Style);
    if (!Profile) return;

    PlayVoiceFromSet(Profile->VictoryVoiceSet);
}

void ULesFightMartialArtsAudio::PlayDefeatSound(EFightingStyle Style)
{
    const FStyleAudioProfile* Profile = StyleAudioProfiles.Find(Style);
    if (!Profile) return;

    PlayVoiceFromSet(Profile->DefeatVoiceSet);
}

void ULesFightMartialArtsAudio::PlayFootstep(float Speed)
{
}

void ULesFightMartialArtsAudio::PlayClothingSound(float Intensity)
{
}

void ULesFightMartialArtsAudio::PlayBreathingSound(float ExertionLevel)
{
}

void ULesFightMartialArtsAudio::SetAudioProfile(EFightingStyle Style,
    const FStyleAudioProfile& Profile)
{
    StyleAudioProfiles.Add(Style, Profile);
}

void ULesFightMartialArtsAudio::Reset()
{
    BreathTimer = BreathInterval;
    LastVoiceTime = -VoiceCooldown;
}

void ULesFightMartialArtsAudio::PlayVoiceFromSet(const TArray<FName>& VoiceSet)
{
}

void ULesFightMartialArtsAudio::PlaySoundFromSet(const TArray<FName>& SoundSet,
    FVector Location)
{
}

FName ULesFightMartialArtsAudio::GetRandomFromArray(const TArray<FName>& Array) const
{
    if (Array.Num() == 0) return NAME_None;
    return Array[FMath::RandRange(0, Array.Num() - 1)];
}
