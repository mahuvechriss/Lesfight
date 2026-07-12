#include "LesFightCombatEffects.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"
#include "GameFramework/GameUserSettings.h"

ULesFightCombatEffects::ULesFightCombatEffects()
    : HitstopDuration(0.1f)
    , KnockbackEffectScale(1.0f)
    , LaunchEffectScale(1.2f)
    , GroundHitEffectScale(1.0f)
    , ScreenShakeIntensity(1.0f)
    , ScreenShakeDuration(0.2f)
    , HitstopCurve(nullptr)
    , HitShakeClass(nullptr)
    , BlockShakeClass(nullptr)
    , HeavyHitShakeClass(nullptr)
    , LaunchShakeClass(nullptr)
    , bEffectsEnabled(true)
    , bSoundEnabled(true)
    , bScreenShakeEnabled(true)
    , bTimeDilationEnabled(false)
    , HitstopRemaining(0.0f)
{
}

void ULesFightCombatEffects::Initialize(ALesFightBaseFighter* InOwner)
{
    OwnerFighter = InOwner;
}

void ULesFightCombatEffects::PlayHitEffect(FVector Location, FRotator Rotation,
    EHitReaction ReactionType)
{
    if (!bEffectsEnabled) return;

    const FHitEffectData* EffectData = HitEffects.Find(ReactionType);
    if (!EffectData) return;

    UNiagaraComponent* NiagaraComp = SpawnNiagaraEffect(EffectData->HitEffect,
        Location, Rotation, EffectData->EffectScale, false, NAME_None);

    if (NiagaraComp)
    {
        ActiveEffects.Add(NiagaraComp);
    }

    if (bSoundEnabled && EffectData->HitSound)
    {
        PlaySound(EffectData->HitSound, Location);
    }

    if (bScreenShakeEnabled)
    {
        switch (ReactionType)
        {
        case EHitReaction::LightStun:
            PlayCameraShake(HitShakeClass);
            break;
        case EHitReaction::HeavyStun:
        case EHitReaction::Knockback:
            PlayCameraShake(HeavyHitShakeClass);
            break;
        case EHitReaction::Launch:
        case EHitReaction::Knockdown:
            PlayCameraShake(LaunchShakeClass);
            break;
        default:
            PlayCameraShake(HitShakeClass);
            break;
        }
    }
}

void ULesFightCombatEffects::PlayBlockEffect(FVector Location, FRotator Rotation)
{
    if (!bEffectsEnabled) return;

    UNiagaraComponent* NiagaraComp = SpawnNiagaraEffect(BlockEffects.BlockEffect,
        Location, Rotation, BlockEffects.EffectScale, false, NAME_None);

    if (NiagaraComp)
    {
        ActiveEffects.Add(NiagaraComp);
    }

    if (bSoundEnabled && BlockEffects.BlockSound)
    {
        PlaySound(BlockEffects.BlockSound, Location);
    }

    if (bScreenShakeEnabled)
    {
        PlayCameraShake(BlockShakeClass);
    }
}

void ULesFightCombatEffects::PlaySpecialEffect(FName EffectID, FVector Location,
    FRotator Rotation)
{
    if (!bEffectsEnabled) return;

    const FSpecialEffectData* Data = SpecialEffects.Find(EffectID);
    if (!Data) return;

    UNiagaraComponent* NiagaraComp = SpawnNiagaraEffect(Data->Effect,
        Location, Rotation, Data->EffectScale, Data->bAttachToOwner, Data->AttachSocket);

    if (NiagaraComp)
    {
        ActiveEffects.Add(NiagaraComp);
    }

    if (bSoundEnabled && Data->Sound)
    {
        PlaySound(Data->Sound, Location);
    }
}

void ULesFightCombatEffects::PlayKnockbackEffect(FVector Location, FVector Direction)
{
    FRotator Rotation = Direction.Rotation();
    PlayHitEffect(Location, Rotation, EHitReaction::Knockback);
}

void ULesFightCombatEffects::PlayLaunchEffect(FVector Location)
{
    PlayHitEffect(Location, FRotator::ZeroRotator, EHitReaction::Launch);
}

void ULesFightCombatEffects::PlayGroundHitEffect(FVector Location)
{
    PlayHitEffect(Location, FRotator(-90.0f, 0.0f, 0.0f), EHitReaction::Knockdown);
}

void ULesFightCombatEffects::PlayEffectByType(EAttackType AttackType, FVector Location,
    FRotator Rotation)
{
    switch (AttackType)
    {
    case EAttackType::LightPunch:
    case EAttackType::LightKick:
        PlayHitEffect(Location, Rotation, EHitReaction::LightStun);
        break;
    case EAttackType::HeavyPunch:
    case EAttackType::HeavyKick:
        PlayHitEffect(Location, Rotation, EHitReaction::HeavyStun);
        break;
    case EAttackType::Special:
        PlaySpecialEffect("Special", Location, Rotation);
        break;
    case EAttackType::Ultimate:
        PlaySpecialEffect("Ultimate", Location, Rotation);
        break;
    default:
        PlayHitEffect(Location, Rotation, EHitReaction::LightStun);
        break;
    }
}

void ULesFightCombatEffects::StopAllEffects()
{
    for (UNiagaraComponent* Effect : ActiveEffects)
    {
        if (Effect)
        {
            Effect->Deactivate();
        }
    }
    ActiveEffects.Empty();
}

void ULesFightCombatEffects::TriggerHitstop(float Duration)
{
    float ActualDuration = (Duration > 0.0f) ? Duration : HitstopDuration;

    if (!OwnerFighter.IsValid()) return;

    APlayerController* PC = Cast<APlayerController>(OwnerFighter->GetController());
    if (PC)
    {
        if (bTimeDilationEnabled)
        {
            PC->CustomTimeDilation = 0.0f;
        }
        FTimerHandle UnusedHandle;
        OwnerFighter->GetWorldTimerManager().SetTimer(UnusedHandle, FTimerDelegate::CreateLambda([PC]() {
            if (PC) PC->CustomTimeDilation = 1.0f;
        }), ActualDuration, false);
    }
}

UNiagaraComponent* ULesFightCombatEffects::SpawnNiagaraEffect(UNiagaraSystem* Effect,
    FVector Location, FRotator Rotation, FVector Scale, bool bAttach, FName Socket)
{
    if (!Effect || !OwnerFighter.IsValid()) return nullptr;

    if (bAttach && Socket != NAME_None)
    {
        USceneComponent* AttachComp = OwnerFighter->GetMesh();
        if (AttachComp)
        {
            return UNiagaraFunctionLibrary::SpawnSystemAttached(Effect, AttachComp,
                Socket, FVector::ZeroVector, FRotator::ZeroRotator,
                EAttachLocation::SnapToTarget, true);
        }
    }

    return UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect,
        Location, Rotation, Scale, true);
}

void ULesFightCombatEffects::PlaySound(USoundBase* Sound, FVector Location)
{
    if (Sound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location);
    }
}

void ULesFightCombatEffects::PlayCameraShake(TSubclassOf<class UCameraShakeBase> ShakeClass)
{
    if (!ShakeClass || !OwnerFighter.IsValid()) return;

    APlayerController* PC = Cast<APlayerController>(OwnerFighter->GetController());
    if (PC)
    {
        PC->ClientStartCameraShake(ShakeClass, ScreenShakeIntensity);
    }
}
