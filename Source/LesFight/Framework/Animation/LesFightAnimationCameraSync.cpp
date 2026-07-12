#include "LesFightAnimationCameraSync.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"
#include "Camera/CameraComponent.h"

ULesFightAnimationCameraSync::ULesFightAnimationCameraSync()
    : CombatZoomSpeed(8.0f)
    , ImpactZoomIntensity(1.0f)
    , bCameraShakeEnabled(true)
    , bDynamicZoomEnabled(true)
    , CurrentZoom(0.0f), TargetZoom(0.0f), ZoomTimer(0.0f)
{
}

void ULesFightAnimationCameraSync::Initialize(
    ULesFightCharacterAnimationComponent* InComponent)
{
    AnimComponent = InComponent;
    if (AnimComponent.IsValid())
    {
        AActor* Owner = AnimComponent->GetOwner();
        if (Owner)
        {
            CameraComponent = Owner->FindComponentByClass<UCameraComponent>();
        }
    }
}

void ULesFightAnimationCameraSync::Update(float DeltaTime)
{
    if (!bDynamicZoomEnabled) return;

    if (ZoomTimer > 0.0f)
    {
        ZoomTimer -= DeltaTime;
        CurrentZoom = FMath::FInterpTo(CurrentZoom, TargetZoom, DeltaTime, CombatZoomSpeed);

        if (CameraComponent.IsValid())
        {
            CameraComponent->FieldOfView = FMath::Clamp(
                90.0f - CurrentZoom, 60.0f, 120.0f);
        }

        if (ZoomTimer <= 0.0f)
        {
            TargetZoom = 0.0f;
        }
    }
    else
    {
        CurrentZoom = FMath::FInterpTo(CurrentZoom, 0.0f, DeltaTime, CombatZoomSpeed);
        if (CameraComponent.IsValid())
        {
            CameraComponent->FieldOfView = FMath::Clamp(
                90.0f - CurrentZoom, 60.0f, 120.0f);
        }
    }
}

void ULesFightAnimationCameraSync::TriggerCombatZoom(float Distance, float Duration)
{
    TargetZoom = Distance;
    ZoomTimer = Duration;
}

void ULesFightAnimationCameraSync::TriggerImpactZoom(float Intensity)
{
    TargetZoom = 80.0f * Intensity * ImpactZoomIntensity;
    ZoomTimer = 0.2f;
}

void ULesFightAnimationCameraSync::TriggerCinematicCamera(
    const FCameraAnimSyncData& CameraData)
{
    CurrentCameraData = CameraData;
}

void ULesFightAnimationCameraSync::ResetToDefaultCamera(float BlendTime)
{
    CurrentCameraData = DefaultCameraData;
    TargetZoom = 0.0f;
    ZoomTimer = 0.0f;
}
