#include "LesFightAnimationAudioSync.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAudioManager.h"
#include "LesFightAudioComponent.h"
#include "LesFight.h"
#include "Kismet/GameplayStatics.h"

ULesFightAnimationAudioSync::ULesFightAnimationAudioSync()
    : FootstepVolume(1.0f)
    , PunchVolume(1.0f)
    , KickVolume(1.0f)
    , LandingVolume(1.0f)
    , GlobalVolumeMultiplier(1.0f)
    , bAudioEnabled(true)
{
}

void ULesFightAnimationAudioSync::Initialize(
    ULesFightCharacterAnimationComponent* InComponent)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AActor* Owner = AnimComponent->GetOwner();
        if (Owner)
        {
            ULesFightAudioComponent* CharAudio = Owner->FindComponentByClass<ULesFightAudioComponent>();
        }
    }
}

void ULesFightAnimationAudioSync::PlayFootstepSound(bool bIsRightFoot)
{
    if (!bAudioEnabled || !AnimComponent.IsValid()) return;

    float Volume = FootstepVolume * GlobalVolumeMultiplier;
    AnimComponent->OnAnimationEvent.Broadcast(FName(TEXT("Footstep")), Volume);
}

void ULesFightAnimationAudioSync::PlayVoiceLine(ECharacterVoiceType VoiceType)
{
    if (!bAudioEnabled || !AnimComponent.IsValid()) return;

    AActor* Owner = AnimComponent->GetOwner();
    ULesFightAudioComponent* AudioComp = Owner
        ? Owner->FindComponentByClass<ULesFightAudioComponent>() : nullptr;
    if (AudioComp)
    {
        AudioComp->PlayVoice(VoiceType);
    }
}

void ULesFightAnimationAudioSync::PlayPunchSound(float Intensity)
{
    if (!bAudioEnabled) return;
    AnimComponent->OnAnimationEvent.Broadcast(FName(TEXT("PunchImpact")),
        PunchVolume * Intensity * GlobalVolumeMultiplier);
}

void ULesFightAnimationAudioSync::PlayKickSound(float Intensity)
{
    if (!bAudioEnabled) return;
    AnimComponent->OnAnimationEvent.Broadcast(FName(TEXT("KickImpact")),
        KickVolume * Intensity * GlobalVolumeMultiplier);
}

void ULesFightAnimationAudioSync::PlayClothingSound()
{
    if (!bAudioEnabled) return;
    AnimComponent->OnAnimationEvent.Broadcast(FName(TEXT("Clothing")), GlobalVolumeMultiplier);
}

void ULesFightAnimationAudioSync::PlayLandingSound(float ImpactVelocity)
{
    if (!bAudioEnabled) return;
    float Volume = FMath::Clamp(ImpactVelocity / 1000.0f, 0.0f, 1.0f) * LandingVolume;
    AnimComponent->OnAnimationEvent.Broadcast(FName(TEXT("Landing")), Volume);
}

void ULesFightAnimationAudioSync::PlayWhooshSound(float Speed)
{
    if (!bAudioEnabled) return;
    AnimComponent->OnAnimationEvent.Broadcast(FName(TEXT("Whoosh")), Speed * GlobalVolumeMultiplier);
}

void ULesFightAnimationAudioSync::RegisterAudioEvent(const FAnimAudioEvent& AudioEvent)
{
    if (!AudioEvent.EventName.IsNone())
    {
        RegisteredAudioEvents.Add(AudioEvent.EventName, AudioEvent);
    }
}

void ULesFightAnimationAudioSync::TriggerAudioEvent(FName EventName)
{
    if (!bAudioEnabled) return;

    const FAnimAudioEvent* AudioEvent = RegisteredAudioEvents.Find(EventName);
    if (AudioEvent && AudioEvent->Sound && AnimComponent.IsValid())
    {
        float Volume = AudioEvent->VolumeMultiplier * GlobalVolumeMultiplier;
        if (AudioEvent->bAttached && AudioEvent->AttachSocket != NAME_None)
        {
            USkeletalMeshComponent* Mesh = AnimComponent->GetMesh();
            if (Mesh)
            {
                UGameplayStatics::PlaySoundAtLocation(AnimComponent->GetOwner(),
                    AudioEvent->Sound, Mesh->GetSocketLocation(AudioEvent->AttachSocket),
                    Volume, AudioEvent->PitchMultiplier);
            }
        }
        else
        {
            UGameplayStatics::PlaySoundAtLocation(AnimComponent->GetOwner(),
                AudioEvent->Sound, AnimComponent->GetOwner()->GetActorLocation(),
                Volume, AudioEvent->PitchMultiplier);
        }
    }
}
