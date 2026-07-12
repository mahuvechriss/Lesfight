#include "LesFightUltimatePresentation.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "Framework/VFX/World/LesFightVFXWorldManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

void ULesFightUltimatePresentation::Initialize(ULesFightVFXWorldManager* InManager)
{
    OwnerManager = InManager;

    StyleUltimateEffects.Empty();

    StyleUltimateEffects.Add(EFightingStyle::Karate, { TEXT("SwiftEnergySlash"), TEXT("SlashTrail"), TEXT("ImpactSpark") });
    StyleUltimateEffects.Add(EFightingStyle::MuayThai, { TEXT("KneeStrikeBurst"), TEXT("ShockwaveRing"), TEXT("ImpactDebris") });
    StyleUltimateEffects.Add(EFightingStyle::Boxing, { TEXT("PunchFlurry"), TEXT("RapidImpact"), TEXT("SpeedLines") });
    StyleUltimateEffects.Add(EFightingStyle::Wushu, { TEXT("AcrobaticEnergyWave"), TEXT("SpinTrail"), TEXT("EnergyRing") });

    bUltimatePlaying = false;
    UltimateProgress = 0.0f;
}

void ULesFightUltimatePresentation::BeginUltimateSequence(FName CharacterID, AActor* Attacker, AActor* Target)
{
    if (!Attacker || !Target)
    {
        return;
    }

    CurrentCharacterID = CharacterID;
    bUltimatePlaying = true;
    UltimateProgress = 0.0f;

    if (OwnerManager.IsValid())
    {
        OwnerManager->RequestSlowMotion(ECinematicVFXEvent::UltimateStart);
        OwnerManager->RequestCameraZoom(Attacker, ECinematicVFXEvent::UltimateStart);
        OwnerManager->RequestAuraBurst(Attacker, 200.0f);
        OwnerManager->RequestCinematicLighting(ECinematicVFXEvent::UltimateStart);
    }

    OnUltimateStarted.Broadcast(CharacterID);
}

void ULesFightUltimatePresentation::PlayUltimateAttack(FVector Location)
{
    if (!bUltimatePlaying)
    {
        return;
    }

    if (StyleUltimateEffects.Contains(UltimateStyle))
    {
        TArray<FString> Effects = StyleUltimateEffects[UltimateStyle];
        for (const FString& EffectPath : Effects)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                GetWorld(),
                nullptr,
                Location,
                FRotator::ZeroRotator,
                FVector::OneVector,
                true
            );
        }
    }

    UltimateProgress = 0.5f;
}

void ULesFightUltimatePresentation::PlayUltimateImpact(FVector Location, AActor* Target)
{
    if (!bUltimatePlaying)
    {
        return;
    }

    if (OwnerManager.IsValid())
    {
        OwnerManager->RequestShockwave(Location, 300.0f, 500.0f, EWaveType::Shockwave);
        OwnerManager->RequestScreenShake(ECinematicVFXEvent::UltimateHit);
        OwnerManager->RequestImpactDecal(Location, Target);
        OwnerManager->RequestDebrisEffect(Location);
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        nullptr,
        Location,
        FRotator::ZeroRotator,
        FVector::OneVector,
        true
    );

    UltimateProgress = 1.0f;

    OnUltimateCompleted.Broadcast(CurrentCharacterID, true);
}

void ULesFightUltimatePresentation::EndUltimateSequence()
{
    if (!bUltimatePlaying)
    {
        return;
    }

    if (OwnerManager.IsValid())
    {
        OwnerManager->RestoreNormalTime();
        OwnerManager->RestoreCamera();
        OwnerManager->ResetCinematicLighting();
    }

    bUltimatePlaying = false;
    UltimateProgress = 1.0f;
}

bool ULesFightUltimatePresentation::IsUltimatePlaying() const
{
    return bUltimatePlaying;
}

float ULesFightUltimatePresentation::GetUltimateProgress() const
{
    return UltimateProgress;
}

void ULesFightUltimatePresentation::SetUltimateStyle(EFightingStyle Style)
{
    UltimateStyle = Style;
}

UWorld* ULesFightUltimatePresentation::GetWorld() const
{
    if (OwnerManager.IsValid())
    {
        return OwnerManager->GetWorld();
    }
    return nullptr;
}
