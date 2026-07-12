#include "LesFightCameraManager.h"
#include "LesFight.h"
#include "Engine/World.h"

ALesFightCameraManager::ALesFightCameraManager()
    : CurrentCameraMode(ECameraMode::Default)
    , TransitionProgress(0.0f)
    , TransitionDuration(0.0f)
    , bIsTransitioning(false)
    , bCameraLagEnabled(true)
{
    DefaultCameraSettings = FCameraSettings();
    CombatCameraSettings = FCameraSettings();
    CombatCameraSettings.CameraDistance = 250.0f;
    CombatCameraSettings.CameraLagSpeed = 15.0f;
    CinematicCameraSettings = FCameraSettings();
    CinematicCameraSettings.CameraDistance = 400.0f;
    CinematicCameraSettings.CameraLagSpeed = 5.0f;
    CinematicCameraSettings.FieldOfView = 70.0f;
}

void ALesFightCameraManager::BeginPlay()
{
    Super::BeginPlay();
    CurrentSettings = DefaultCameraSettings;
    UE_LOG(LogLesFight, Log, TEXT("CameraManager initialized"));
}

void ALesFightCameraManager::UpdateCamera(float DeltaTime)
{
    Super::UpdateCamera(DeltaTime);

    if (bIsTransitioning)
    {
        TransitionProgress += DeltaTime;
        float Alpha = FMath::Clamp(TransitionProgress / TransitionDuration, 0.0f, 1.0f);
        float SmoothAlpha = FMath::SmoothStep(0.0f, 1.0f, Alpha);

        CurrentSettings.CameraDistance = FMath::Lerp(
            GetSettingsForMode(CurrentCameraMode).CameraDistance,
            TargetSettings.CameraDistance, SmoothAlpha);

        if (Alpha >= 1.0f)
        {
            bIsTransitioning = false;
            CurrentSettings = TargetSettings;
            OnCameraTransitionComplete.Broadcast(CameraTargetActor);
        }
    }

    if (PCOwner && CameraTargetActor)
    {
        FVector TargetLocation = CameraTargetActor->GetActorLocation();
        FVector POVLocation = PCOwner->PlayerCameraManager->GetCameraLocation();

        if (bCameraLagEnabled)
        {
            float LagSpeed = CurrentSettings.CameraLagSpeed * DeltaTime;
            FVector DesiredLocation = FMath::VInterpTo(POVLocation, TargetLocation, DeltaTime, LagSpeed);
            SetActorLocation(DesiredLocation);
        }
    }

    UpdateCameraCollision();
}

void ALesFightCameraManager::ProcessViewRotation(float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot)
{
    Super::ProcessViewRotation(DeltaTime, OutViewRotation, OutDeltaRot);
}

void ALesFightCameraManager::SetCameraMode(ECameraMode NewMode)
{
    if (CurrentCameraMode != NewMode)
    {
        CurrentCameraMode = NewMode;
        TargetSettings = GetSettingsForMode(NewMode);

        UE_LOG(LogLesFight, Log, TEXT("Camera mode changed to %d"), static_cast<int32>(NewMode));
    }
}

void ALesFightCameraManager::SetCameraTarget(AActor* NewTarget)
{
    CameraTargetActor = NewTarget;
    UE_LOG(LogLesFight, Verbose, TEXT("Camera target set to %s"),
        NewTarget ? *NewTarget->GetName() : TEXT("None"));
}

void ALesFightCameraManager::SetCameraDistance(float NewDistance)
{
    CurrentSettings.CameraDistance = NewDistance;
}

void ALesFightCameraManager::SetFieldOfView(float NewFOV)
{
    CurrentSettings.FieldOfView = NewFOV;
    if (PCOwner)
    {
        PCOwner->PlayerCameraManager->SetFOV(NewFOV);
    }
}

void ALesFightCameraManager::SetCameraLagEnabled(bool bEnabled)
{
    bCameraLagEnabled = bEnabled;
}

void ALesFightCameraManager::PlayCinematicTransition(float Duration)
{
    TargetSettings = CinematicCameraSettings;
    TransitionDuration = Duration;
    TransitionProgress = 0.0f;
    bIsTransitioning = true;
}

void ALesFightCameraManager::ZoomIn(float TargetFOV, float Duration)
{
    TargetSettings.FieldOfView = TargetFOV;
    TransitionDuration = Duration;
    TransitionProgress = 0.0f;
    bIsTransitioning = true;
}

void ALesFightCameraManager::ZoomOut(float TargetFOV, float Duration)
{
    TargetSettings.FieldOfView = TargetFOV;
    TransitionDuration = Duration;
    TransitionProgress = 0.0f;
    bIsTransitioning = true;
}

FCameraSettings ALesFightCameraManager::GetSettingsForMode(ECameraMode Mode) const
{
    switch (Mode)
    {
    case ECameraMode::Default:
        return DefaultCameraSettings;
    case ECameraMode::Combat:
        return CombatCameraSettings;
    case ECameraMode::Cinematic:
        return CinematicCameraSettings;
    default:
        return DefaultCameraSettings;
    }
}

void ALesFightCameraManager::UpdateCameraCollision()
{
    if (!PCOwner || !PCOwner->GetPawn()) return;

    FVector CameraLocation = GetCameraLocation();
    FVector PawnLocation = PCOwner->GetPawn()->GetActorLocation();

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(PCOwner->GetPawn());

    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        PawnLocation,
        CameraLocation,
        ECC_Camera,
        QueryParams
    );

    if (bHit)
    {
        FVector AdjustedLocation = HitResult.Location;
        SetActorLocation(AdjustedLocation);
    }
}
