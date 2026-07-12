#include "LesFightCinematicCombat.h"
#include "LesFightMartialArtsManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ULesFightCinematicCombat::ULesFightCinematicCombat()
    : bSlowMotionActive(false)
    , CurrentTimeScale(1.0f)
    , SlowMotionTimer(0.0f)
    , bCinematicActive(false)
    , ActiveEffect(ECinematicEffect::None)
    , LastCameraEffect(ECinematicEffect::None)
    , DefaultTimeScale(1.0f)
    , CameraBlendTimer(0.0f)
{
}

void ULesFightCinematicCombat::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    DefaultTimeScale = 1.0f;
}

void ULesFightCinematicCombat::Tick(float DeltaTime)
{
    if (bSlowMotionActive)
    {
        SlowMotionTimer -= DeltaTime * (1.0f / CurrentTimeScale);
        if (SlowMotionTimer <= 0.0f)
        {
            StopSlowMotion();
        }
    }

    if (CameraBlendTimer > 0.0f)
    {
        UpdateCamera(DeltaTime);
    }
}

void ULesFightCinematicCombat::TriggerCinematicEffect(ECinematicEffect EffectType)
{
    const FCinematicEffectData* Data = CinematicDefinitions.Find(EffectType);
    if (!Data) return;

    ActiveEffect = EffectType;

    switch (EffectType)
    {
    case ECinematicEffect::SlowMotion:
        StartSlowMotion(Data->TimeScale, Data->Duration);
        break;
    case ECinematicEffect::DynamicCamera:
        SetActiveCamera(EffectType);
        break;
    case ECinematicEffect::DramaticImpact:
        TriggerDramaticImpact(FVector::ZeroVector);
        break;
    default:
        break;
    }

    OnCinematicTriggered.Broadcast(EffectType);
}

void ULesFightCinematicCombat::StartSlowMotion(float TimeScale, float Duration)
{
    if (bSlowMotionActive) return;

    bSlowMotionActive = true;
    CurrentTimeScale = TimeScale;
    SlowMotionTimer = Duration;

    ApplySlowMotion(TimeScale, Duration);
    OnSlowMotionChanged.Broadcast(TimeScale);
    OnCinematicStarted.Broadcast();
}

void ULesFightCinematicCombat::StopSlowMotion()
{
    if (!bSlowMotionActive) return;

    bSlowMotionActive = false;
    CurrentTimeScale = DefaultTimeScale;
    SlowMotionTimer = 0.0f;

    RevertTimeScale();
    OnSlowMotionChanged.Broadcast(DefaultTimeScale);
    OnCinematicEnded.Broadcast();
}

void ULesFightCinematicCombat::SetActiveCamera(ECinematicEffect EffectType)
{
    LastCameraEffect = EffectType;
    const FCinematicEffectData* Data = CinematicDefinitions.Find(EffectType);
    CameraBlendTimer = Data ? Data->CameraBlendTime : 0.5f;
}

void ULesFightCinematicCombat::ResetCamera()
{
    LastCameraEffect = ECinematicEffect::None;
    CameraBlendTimer = 0.0f;
}

void ULesFightCinematicCombat::PlayUltimateCinematic(FName UltimateMontageName)
{
    bCinematicActive = true;
    OnCinematicStarted.Broadcast();
}

void ULesFightCinematicCombat::PlaySignatureMove(FName SignatureMontageName)
{
    bCinematicActive = true;
    OnCinematicStarted.Broadcast();
}

void ULesFightCinematicCombat::PlayVictoryCutscene(int32 WinnerIndex)
{
    bCinematicActive = true;
    OnCinematicStarted.Broadcast();
}

void ULesFightCinematicCombat::TriggerDramaticImpact(
    FVector ImpactLocation, float Radius)
{
    PlayCameraShake(ECinematicEffect::DramaticImpact);
}

void ULesFightCinematicCombat::SetCinematicData(
    const TMap<ECinematicEffect, FCinematicEffectData>& Data)
{
    CinematicDefinitions = Data;
}

void ULesFightCinematicCombat::Reset()
{
    if (bSlowMotionActive) StopSlowMotion();
    bCinematicActive = false;
    ActiveEffect = ECinematicEffect::None;
    CameraBlendTimer = 0.0f;
    ResetCamera();
}

void ULesFightCinematicCombat::ApplySlowMotion(float TimeScale, float Duration)
{
    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeScale);
}

void ULesFightCinematicCombat::RevertTimeScale()
{
    UGameplayStatics::SetGlobalTimeDilation(GetWorld(), DefaultTimeScale);
}

void ULesFightCinematicCombat::UpdateCamera(float DeltaTime)
{
    CameraBlendTimer -= DeltaTime;
    if (CameraBlendTimer <= 0.0f)
    {
        CameraBlendTimer = 0.0f;
    }
}

void ULesFightCinematicCombat::PlayCameraShake(ECinematicEffect EffectType)
{
    if (!OwnerManager.IsValid() || !OwnerManager->GetWorld()) return;
    APlayerController* PC = OwnerManager->GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->ClientStartCameraShake(TEXT("DramaticImpactShake"));
    }
}
