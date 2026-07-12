#include "LesFightCameraEffects.h"
#include "Framework/VFX/Manager/LesFightVFXWorldManager.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

void ULesFightCameraEffects::Initialize(ULesFightVFXWorldManager* InOwner)
{
    OwnerManager = InOwner;
    bShakeEnabled = true;
    DefaultFOV = 90.0f;

    CameraEffectDefs.Empty();
    CameraEffectDefs.Add(EImpactVFXType::LightPunch, FCameraEffectDef{ 0.3f, 10.0f, 0.1f, 0.0f });
    CameraEffectDefs.Add(EImpactVFXType::HeavyPunch, FCameraEffectDef{ 0.6f, 8.0f, 0.2f, -5.0f });
    CameraEffectDefs.Add(EImpactVFXType::SpecialAttack, FCameraEffectDef{ 0.8f, 6.0f, 0.3f, -10.0f });
    CameraEffectDefs.Add(EImpactVFXType::UltimateAttack, FCameraEffectDef{ 1.0f, 4.0f, 0.5f, -15.0f });
    CameraEffectDefs.Add(EImpactVFXType::BlockImpact, FCameraEffectDef{ 0.2f, 12.0f, 0.1f, 0.0f });
    CameraEffectDefs.Add(EImpactVFXType::Knockdown, FCameraEffectDef{ 0.7f, 5.0f, 0.4f, 0.0f });
}

void ULesFightCameraEffects::PlayCameraShake(EImpactVFXType Type, FVector Location)
{
    if (!bShakeEnabled) return;

    const FCameraEffectDef* Def = CameraEffectDefs.Find(Type);
    if (!Def) return;

    CurrentEffect = *Def;
    PlayImpactShake(Def->ShakeIntensity, Location);
}

void ULesFightCameraEffects::PlayImpactShake(float Intensity, FVector Location)
{
    if (!bShakeEnabled) return;

    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (!CameraManager) return;

    FVector CameraLocation = CameraManager->GetCameraLocation();
    float Distance = FVector::Dist(CameraLocation, Location);
    float Falloff = FMath::Clamp(1.0f - (Distance / 3000.0f), 0.0f, 1.0f);

    float FinalIntensity = Intensity * Falloff;
    if (FinalIntensity <= 0.01f) return;

    CameraManager->PlayWorldCameraShake(this, nullptr, Location, 0.0f, 3000.0f, 1.0f, false);
}

void ULesFightCameraEffects::PlayZoomEffect(float TargetFOV, float Duration)
{
    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (!CameraManager) return;

    CameraManager->SetFOV(TargetFOV);
    CameraManager->UnlockFOV();
}

void ULesFightCameraEffects::PlayImpactZoom(float Duration)
{
    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (!CameraManager) return;

    float TargetFOV = DefaultFOV + CurrentEffect.FOVOffset;
    CameraManager->SetFOV(TargetFOV);
    CameraManager->UnlockFOV();
}

void ULesFightCameraEffects::PlayDynamicFOV(float Fighter1Dist, float Fighter2Dist)
{
    float AvgDist = (Fighter1Dist + Fighter2Dist) * 0.5f;
    float TargetFOV = FMath::Clamp(DefaultFOV + (AvgDist * 0.5f), 60.0f, 120.0f);

    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (!CameraManager) return;

    CameraManager->SetFOV(TargetFOV);
}

void ULesFightCameraEffects::PlayRotationEffect(FRotator Offset, float Duration)
{
    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (!CameraManager) return;

    FRotator CurrentRot = CameraManager->GetCameraRotation();
    FRotator TargetRot = CurrentRot + Offset;
    CameraManager->SetCameraCachePOV(FMinimalViewInfo());
}

void ULesFightCameraEffects::ResetCamera()
{
    APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
    if (!CameraManager) return;

    CameraManager->SetFOV(DefaultFOV);
    CameraManager->ResetCamera();
    CurrentEffect = FCameraEffectDef();
}

void ULesFightCameraEffects::SetCameraShakeEnabled(bool bEnabled)
{
    bShakeEnabled = bEnabled;
}

bool ULesFightCameraEffects::IsCameraShakeEnabled() const
{
    return bShakeEnabled;
}
