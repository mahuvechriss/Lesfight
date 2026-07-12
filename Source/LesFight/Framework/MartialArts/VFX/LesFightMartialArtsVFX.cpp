#include "LesFightMartialArtsVFX.h"
#include "LesFightMartialArtsManager.h"

ULesFightMartialArtsVFX::ULesFightMartialArtsVFX()
    : CurrentIntensity(EMartialArtsVFXIntensity::Cinematic)
    , CurrentStyle(EFightingStyle::None)
{
}

void ULesFightMartialArtsVFX::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
}

void ULesFightMartialArtsVFX::Tick(float DeltaTime)
{
}

void ULesFightMartialArtsVFX::PlayAttackTrail(EFightingStyle Style, int32 ComboStep)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(Style);
    if (!Profile) return;

    SpawnTrailEffect(Profile->AttackTrailEffects);
}

void ULesFightMartialArtsVFX::PlayImpactEffect(FVector Location, float Force)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(CurrentStyle);
    if (!Profile) return;

    SpawnEffect(FName(TEXT("Impact")), Location);
    ApplyCameraShake(Force / 100.0f);

    if (Force > 50.0f)
    {
        PlayShockwave(Location, Force);
    }
}

void ULesFightMartialArtsVFX::PlayDodgeTrail(EAdvancedDodgeType DodgeType)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(CurrentStyle);
    if (!Profile) return;

    SpawnTrailEffect(Profile->DodgeTrailEffects);
}

void ULesFightMartialArtsVFX::PlayCounterEffect(ECounterType CounterType)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(CurrentStyle);
    if (!Profile) return;

    SpawnTrailEffect(Profile->CounterEffects);
}

void ULesFightMartialArtsVFX::PlayUltimateEffect(EFightingStyle Style)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(Style);
    if (!Profile) return;

    SpawnTrailEffect(Profile->UltimateEffects);
}

void ULesFightMartialArtsVFX::PlayDustEffect(FVector Location, float Intensity)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(CurrentStyle);
    if (!Profile) return;

    SpawnEffect(FName(TEXT("Dust")), Location);
}

void ULesFightMartialArtsVFX::PlayShockwave(FVector Location, float Radius)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(CurrentStyle);
    if (!Profile) return;

    SpawnEffect(FName(TEXT("Shockwave")), Location);
}

void ULesFightMartialArtsVFX::PlayAura(EFightingStyle Style, bool bEnabled)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(Style);
    if (!Profile || !bEnabled) return;

    SpawnEffect(FName(TEXT("Aura")), FVector::ZeroVector);
}

void ULesFightMartialArtsVFX::PlayFootstepDust(FVector Location)
{
    const FStyleVFXProfile* Profile = StyleVFXProfiles.Find(CurrentStyle);
    if (!Profile) return;

    SpawnEffect(FName(TEXT("FootstepDust")), Location);
}

void ULesFightMartialArtsVFX::SetVFXProfile(EFightingStyle Style,
    const FStyleVFXProfile& Profile)
{
    StyleVFXProfiles.Add(Style, Profile);
}

void ULesFightMartialArtsVFX::SetVFXIntensity(EMartialArtsVFXIntensity Intensity)
{
    CurrentIntensity = Intensity;
}

void ULesFightMartialArtsVFX::Reset()
{
    StyleVFXProfiles.Empty();
}

void ULesFightMartialArtsVFX::SpawnEffect(FName EffectName, FVector Location,
    FRotator Rotation)
{
}

void ULesFightMartialArtsVFX::SpawnTrailEffect(const TArray<FName>& TrailEffects)
{
}

void ULesFightMartialArtsVFX::SpawnNiagaraSystem(FName SystemName, FVector Location)
{
}

void ULesFightMartialArtsVFX::ApplyDynamicLighting(FVector Location,
    FLinearColor Color, float Intensity)
{
}

void ULesFightMartialArtsVFX::ApplyCameraShake(float Intensity)
{
    if (!OwnerManager.IsValid() || !OwnerManager->GetWorld()) return;

    APlayerController* PC = OwnerManager->GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->ClientStartCameraShake(TEXT("MartialArtsHitShake"), Intensity);
    }
}
