#include "LesFightCombatAudioHandler.h"
#include "LesFightCombatComponent.h"
#include "LesFightAudioManager.h"
#include "LesFight.h"
#include "Kismet/GameplayStatics.h"

ULesFightCombatAudioHandler::ULesFightCombatAudioHandler()
    : HitSoundLight(nullptr)
    , HitSoundHeavy(nullptr)
    , HitSoundKnockback(nullptr)
    , HitSoundLaunch(nullptr)
    , BlockSound(nullptr)
    , WhiffSound(nullptr)
    , KOSound(nullptr)
    , RoundStartSound(nullptr)
    , RoundEndSound(nullptr)
    , UltimateSound(nullptr)
    , SpecialSound(nullptr)
    , CombatMusic(nullptr)
    , HitSoundVolume(1.0f)
{
}

void ULesFightCombatAudioHandler::Initialize(ULesFightCombatComponent* CombatComp,
    ULesFightAudioManager* AudioMgr)
{
    CombatComponent = CombatComp;
    AudioManager = AudioMgr;
}

void ULesFightCombatAudioHandler::PlayHitSound(EHitReaction ReactionType)
{
    USoundBase* Sound = GetHitSoundForReaction(ReactionType);
    if (Sound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(Sound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlayBlockSound()
{
    if (BlockSound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(BlockSound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlayWhiffSound()
{
    if (WhiffSound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(WhiffSound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlayKOSound()
{
    if (KOSound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(KOSound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlayRoundStartSound()
{
    if (RoundStartSound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(RoundStartSound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlayRoundEndSound()
{
    if (RoundEndSound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(RoundEndSound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlayUltimateSound()
{
    if (UltimateSound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(UltimateSound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlaySpecialSound()
{
    if (SpecialSound && AudioManager.IsValid())
    {
        AudioManager->PlaySound(SpecialSound, EAudioChannel::SFX);
    }
}

void ULesFightCombatAudioHandler::PlayHitSoundByType(EAttackType AttackType)
{
    switch (AttackType)
    {
    case EAttackType::LightPunch:
    case EAttackType::LightKick:
        PlayHitSound(EHitReaction::LightStun);
        break;
    case EAttackType::HeavyPunch:
    case EAttackType::HeavyKick:
        PlayHitSound(EHitReaction::HeavyStun);
        break;
    case EAttackType::Special:
        PlaySpecialSound();
        break;
    case EAttackType::Ultimate:
        PlayUltimateSound();
        break;
    default:
        PlayHitSound(EHitReaction::LightStun);
        break;
    }
}

void ULesFightCombatAudioHandler::SetCombatMusic(USoundBase* InCombatMusic)
{
    CombatMusic = InCombatMusic;
    if (CombatMusic && AudioManager.IsValid())
    {
        AudioManager->PlayMusic(CombatMusic);
    }
}

void ULesFightCombatAudioHandler::StopCombatMusic()
{
    if (AudioManager.IsValid())
    {
        AudioManager->StopMusic();
    }
}

USoundBase* ULesFightCombatAudioHandler::GetHitSoundForReaction(
    EHitReaction ReactionType) const
{
    switch (ReactionType)
    {
    case EHitReaction::LightStun:  return HitSoundLight;
    case EHitReaction::HeavyStun:  return HitSoundHeavy;
    case EHitReaction::Knockback:  return HitSoundKnockback;
    case EHitReaction::Launch:
    case EHitReaction::Knockdown:  return HitSoundLaunch;
    default: return HitSoundLight;
    }
}
