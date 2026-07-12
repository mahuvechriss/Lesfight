#include "Framework/Arena/Camera/LesFightArenaCamera.h"

void ULesFightArenaCamera::SetCameraBehavior(ECameraBehavior Behavior)
{
    if (CurrentBehavior != Behavior)
    {
        CurrentBehavior = Behavior;
        OnCameraBehaviorChanged.Broadcast(CurrentBehavior);
    }
}

void ULesFightArenaCamera::PlayIntroSequence()
{
    SetCameraBehavior(ECameraBehavior::Intro);
}

void ULesFightArenaCamera::PlayFinisherCamera(FVector Location)
{
    CameraTarget = Location;
    SetCameraBehavior(ECameraBehavior::Finisher);
}

void ULesFightArenaCamera::UpdateCombatCamera(FVector Fighter1Pos, FVector Fighter2Pos, float DeltaTime)
{
    FVector MidPoint = (Fighter1Pos + Fighter2Pos) * 0.5f;
    float Separation = FVector::Dist(Fighter1Pos, Fighter2Pos);
    float DesiredDistance = FMath::Max(Separation * 1.5f, CameraDistance);
    FVector DesiredLocation = MidPoint - FVector(0.0f, DesiredDistance, -CameraHeight);

    CameraTarget = FMath::VInterpTo(CameraTarget, DesiredLocation, DeltaTime, CameraSmoothSpeed);

    ECameraBehavior CombatBehavior = ECameraBehavior::Combat;
    SetCameraBehavior(CombatBehavior);
}

void ULesFightArenaCamera::SetArenaBounds(FVector Bounds)
{
    ArenaBounds = Bounds;
}

ECameraBehavior ULesFightArenaCamera::GetCurrentBehavior() const
{
    return CurrentBehavior;
}

FVector ULesFightArenaCamera::GetCameraTarget() const
{
    return CameraTarget;
}

void ULesFightArenaCamera::SetCameraCollisionEnabled(bool bEnabled)
{
    bCollisionEnabled = bEnabled;
}

void ULesFightArenaCamera::ResetCamera()
{
    CameraTarget = FVector::ZeroVector;
    CameraDistance = 400.0f;
    CameraHeight = 150.0f;
    SetCameraBehavior(ECameraBehavior::Default);
}
