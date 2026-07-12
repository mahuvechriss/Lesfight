#include "LesFightAudioComponent.h"
#include "LesFight.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Engine/World.h"

ULesFightAudioComponent::ULesFightAudioComponent()
    : VoicePitchMultiplier(1.0f)
    , FootstepVolume(0.5f)
    , LastFootstepIndex(-1)
{
    PrimaryActorTick.bCanEverTick = false;
}

void ULesFightAudioComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightAudioComponent::Initialize(const TArray<TSoftObjectPtr<USoundBase>>& InFootsteps,
    const TArray<TSoftObjectPtr<USoundBase>>& InBreathing,
    const TArray<TSoftObjectPtr<USoundBase>>& InGruntSounds,
    USoundBase* InVictoryVoice, USoundBase* InDefeatVoice,
    const TArray<TSoftObjectPtr<USoundBase>>& InTauntSounds)
{
    FootstepSounds = InFootsteps;
    BreathingSounds = InBreathing;
    GruntSounds = InGruntSounds;
    VictoryVoice = InVictoryVoice;
    DefeatVoice = InDefeatVoice;
    TauntSounds = InTauntSounds;
}

void ULesFightAudioComponent::PlayFootstep()
{
    USoundBase* Sound = GetRandomSound(FootstepSounds);
    if (Sound)
    {
        PlaySoundAtCharacter(Sound, FootstepVolume);
    }
}

void ULesFightAudioComponent::PlayBreath(bool bHeavy)
{
    int32 BreathIndex = bHeavy && BreathingSounds.IsValidIndex(0)
        ? FMath::RandRange(0, BreathingSounds.Num() - 1) : 0;
    if (BreathingSounds.IsValidIndex(BreathIndex))
    {
        USoundBase* Sound = BreathingSounds[BreathIndex].LoadSynchronous();
        if (Sound)
        {
            PlaySoundAtCharacter(Sound, 0.3f);
        }
    }
}

void ULesFightAudioComponent::PlayVoice(ECharacterVoiceType VoiceType)
{
    OnVoicePlayed.Broadcast(VoiceType);

    switch (VoiceType)
    {
    case ECharacterVoiceType::Victory: PlayVictoryVoice(); break;
    case ECharacterVoiceType::Defeat:  PlayDefeatVoice();  break;
    case ECharacterVoiceType::Grunt:   PlayGrunt();        break;
    case ECharacterVoiceType::Taunt:   PlayTaunt();        break;
    default: break;
    }
}

void ULesFightAudioComponent::PlayVictoryVoice()
{
    if (VictoryVoice)
    {
        PlaySoundAtCharacter(VictoryVoice, 0.8f);
    }
}

void ULesFightAudioComponent::PlayDefeatVoice()
{
    if (DefeatVoice)
    {
        PlaySoundAtCharacter(DefeatVoice, 0.8f);
    }
}

void ULesFightAudioComponent::PlayGrunt()
{
    USoundBase* Sound = GetRandomSound(GruntSounds);
    if (Sound)
    {
        PlaySoundAtCharacter(Sound, 0.6f);
    }
}

void ULesFightAudioComponent::PlayTaunt()
{
    USoundBase* Sound = GetRandomSound(TauntSounds);
    if (Sound)
    {
        PlaySoundAtCharacter(Sound, 0.7f);
    }
}

USoundBase* ULesFightAudioComponent::GetRandomSound(const TArray<TSoftObjectPtr<USoundBase>>& Sounds) const
{
    if (Sounds.Num() == 0) return nullptr;

    int32 Index;
    do {
        Index = FMath::RandRange(0, Sounds.Num() - 1);
    } while (Index == LastFootstepIndex && Sounds.Num() > 1);

    const_cast<ULesFightAudioComponent*>(this)->LastFootstepIndex = Index;
    return Sounds[Index].LoadSynchronous();
}

void ULesFightAudioComponent::PlaySoundAtCharacter(USoundBase* Sound, float VolumeMultiplier)
{
    if (!Sound || !GetWorld() || !GetOwner()) return;

    UGameplayStatics::PlaySoundAtLocation(
        GetWorld(), Sound, GetOwner()->GetActorLocation(),
        VolumeMultiplier, VoicePitchMultiplier);
}
