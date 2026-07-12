#include "LesFightFollowCameraComponent.h"
#include "LesFightPlayerCharacter.h"
#include "LesFight.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ULesFightFollowCameraComponent::ULesFightFollowCameraComponent()
    : CurrentCameraDistance(300.0f)
    , CurrentFOV(90.0f)
    , TargetCameraDistance(300.0f)
    , TargetFOV(90.0f)
    , bCameraFollowEnabled(true)
    , LockOnTarget(nullptr)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_PostUpdateWork;

    DefaultSettings = FCameraFollowSettings();
    CombatSettings = FCameraFollowSettings();
    CombatSettings.TargetArmLength = 250.0f;
    CombatSettings.CameraLagSpeed = 15.0f;
    CinematicSettings = FCameraFollowSettings();
    CinematicSettings.TargetArmLength = 400.0f;
    CinematicSettings.CameraLagSpeed = 5.0f;
    CinematicSettings.FieldOfView = 70.0f;
}

void ULesFightFollowCameraComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentSettings = DefaultSettings;
    TargetCameraDistance = CurrentSettings.TargetArmLength;
    TargetFOV = CurrentSettings.FieldOfView;
}

void ULesFightFollowCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULesFightFollowCameraComponent::InitializeCamera(ALesFightPlayerCharacter* Owner,
    USpringArmComponent* SpringArm, UCameraComponent* Camera)
{
    OwnerCharacter = Owner;
    CameraBoom = SpringArm;
    PlayerCamera = Camera;

    if (CameraBoom.IsValid())
    {
        CameraBoom->TargetArmLength = CurrentSettings.TargetArmLength;
        CameraBoom->SocketOffset = CurrentSettings.SocketOffset;
        CameraBoom->bEnableCameraLag = CurrentSettings.bEnableCameraLag;
        CameraBoom->CameraLagSpeed = CurrentSettings.CameraLagSpeed;
        CameraBoom->CameraRotationLagSpeed = CurrentSettings.CameraRotationLagSpeed;
        CameraBoom->CameraLagMaxDistance = CurrentSettings.CameraLagMaxDistance;
    }

    if (PlayerCamera.IsValid())
    {
        PlayerCamera->SetFieldOfView(CurrentSettings.FieldOfView);
    }

    UE_LOG(LogLesFight, Log, TEXT("FollowCamera initialized"));
}

void ULesFightFollowCameraComponent::UpdateCamera(float DeltaTime)
{
    if (!bCameraFollowEnabled) return;

    InterpolateCamera(DeltaTime);
    HandleCameraCollision();
    HandleLockOnCamera(DeltaTime);
}

void ULesFightFollowCameraComponent::SetCameraDistance(float NewDistance)
{
    TargetCameraDistance = FMath::Clamp(NewDistance, 100.0f, 800.0f);
}

void ULesFightFollowCameraComponent::SetFieldOfView(float NewFOV)
{
    TargetFOV = FMath::Clamp(NewFOV, 50.0f, 120.0f);
}

void ULesFightFollowCameraComponent::ResetCamera()
{
    TargetCameraDistance = DefaultSettings.TargetArmLength;
    TargetFOV = DefaultSettings.FieldOfView;
    CurrentSettings = DefaultSettings;

    if (CameraBoom.IsValid())
    {
        CameraBoom->TargetArmLength = TargetCameraDistance;
    }
}

void ULesFightFollowCameraComponent::ZoomIn(float Amount)
{
    SetCameraDistance(CurrentCameraDistance - Amount);
}

void ULesFightFollowCameraComponent::ZoomOut(float Amount)
{
    SetCameraDistance(CurrentCameraDistance + Amount);
}

void ULesFightFollowCameraComponent::SetCameraFollowEnabled(bool bEnabled)
{
    bCameraFollowEnabled = bEnabled;
}

void ULesFightFollowCameraComponent::SetLockOnTarget(AActor* Target)
{
    LockOnTarget = Target;
    if (Target && CameraBoom.IsValid())
    {
        CameraBoom->bUsePawnControlRotation = false;
    }
    else if (CameraBoom.IsValid())
    {
        CameraBoom->bUsePawnControlRotation = true;
    }
}

void ULesFightFollowCameraComponent::ClearLockOnTarget()
{
    LockOnTarget = nullptr;
    if (CameraBoom.IsValid())
    {
        CameraBoom->bUsePawnControlRotation = true;
    }
}

void ULesFightFollowCameraComponent::SetCameraSettings(const FCameraFollowSettings& NewSettings)
{
    CurrentSettings = NewSettings;
    TargetCameraDistance = NewSettings.TargetArmLength;
    TargetFOV = NewSettings.FieldOfView;

    if (CameraBoom.IsValid())
    {
        CameraBoom->TargetArmLength = TargetCameraDistance;
        CameraBoom->SocketOffset = NewSettings.SocketOffset;
        CameraBoom->bEnableCameraLag = NewSettings.bEnableCameraLag;
        CameraBoom->CameraLagSpeed = NewSettings.CameraLagSpeed;
    }
}

void ULesFightFollowCameraComponent::ApplyCinematicPreset()
{
    SetCameraSettings(CinematicSettings);
}

void ULesFightFollowCameraComponent::ApplyCombatPreset()
{
    SetCameraSettings(CombatSettings);
}

void ULesFightFollowCameraComponent::ApplyDefaultPreset()
{
    SetCameraSettings(DefaultSettings);
}

void ULesFightFollowCameraComponent::HandleCameraCollision()
{
    if (!CameraBoom.IsValid() || !OwnerCharacter.IsValid()) return;

    FVector Start = OwnerCharacter->GetActorLocation();
    FVector End = CameraBoom->GetComponentLocation();

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(OwnerCharacter.Get());

    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult, Start, End, ECC_Camera, QueryParams);

    if (bHit)
    {
        float NewDistance = (HitResult.Location - Start).Size() - CurrentSettings.CameraCollisionRadius;
        CameraBoom->TargetArmLength = FMath::Max(NewDistance, 50.0f);
    }
    else
    {
        CameraBoom->TargetArmLength = FMath::FInterpTo(
            CameraBoom->TargetArmLength, TargetCameraDistance,
            GetWorld()->GetDeltaSeconds(), 10.0f);
    }
}

void ULesFightFollowCameraComponent::HandleLockOnCamera(float DeltaTime)
{
    if (!LockOnTarget || !CameraBoom.IsValid() || !OwnerCharacter.IsValid()) return;

    FVector TargetLocation = LockOnTarget->GetActorLocation();
    FVector OwnerLocation = OwnerCharacter->GetActorLocation();
    FVector DirectionToTarget = (TargetLocation - OwnerLocation).GetSafeNormal();

    FRotator TargetRotation = DirectionToTarget.Rotation();
    TargetRotation.Pitch = 0.0f;

    FRotator CurrentRotation = CameraBoom->GetComponentRotation();
    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation,
        DeltaTime, CurrentSettings.CameraRotationLagSpeed);

    CameraBoom->SetWorldRotation(NewRotation);
}

void ULesFightFollowCameraComponent::InterpolateCamera(float DeltaTime)
{
    if (!CameraBoom.IsValid() || !PlayerCamera.IsValid()) return;

    float CurrentArmLength = CameraBoom->TargetArmLength;
    float NewArmLength = FMath::FInterpTo(CurrentArmLength, TargetCameraDistance, DeltaTime, 8.0f);
    CameraBoom->TargetArmLength = NewArmLength;
    CurrentCameraDistance = NewArmLength;

    float CurrentFOVValue = PlayerCamera->FieldOfView;
    float NewFOV = FMath::FInterpTo(CurrentFOVValue, TargetFOV, DeltaTime, 5.0f);
    PlayerCamera->SetFieldOfView(NewFOV);
    CurrentFOV = NewFOV;
}
