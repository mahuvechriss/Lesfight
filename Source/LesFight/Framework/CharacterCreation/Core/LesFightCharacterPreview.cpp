#include "LesFightCharacterPreview.h"
#include "LesFightCharCreationManager.h"

ULesFightCharacterPreview::ULesFightCharacterPreview()
    : bPreviewActive(false)
    , bAutoRotate(false)
    , CurrentRotation(0.0f)
    , CurrentZoom(200.0f)
    , CurrentBackground(EPreviewBackground::Default)
    , PreviewCharacterID(NAME_None)
    , RotationSpeed(100.0f)
    , ZoomSpeed(50.0f)
    , MinZoom(50.0f)
    , MaxZoom(500.0f)
    , DefaultZoom(200.0f)
{
}

void ULesFightCharacterPreview::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightCharacterPreview::Tick(float DeltaTime)
{
    if (!bPreviewActive) return;

    if (bAutoRotate)
    {
        CurrentRotation += RotationSpeed * DeltaTime;
        if (CurrentRotation >= 360.0f) CurrentRotation -= 360.0f;
    }
}

void ULesFightCharacterPreview::ShowPreview(FName CharacterID)
{
    bPreviewActive = true;
    PreviewCharacterID = CharacterID;
    ResetCamera();
}

void ULesFightCharacterPreview::HidePreview()
{
    bPreviewActive = false;
    PreviewCharacterID = NAME_None;
}

void ULesFightCharacterPreview::RotateCharacter(float YawInput)
{
    CurrentRotation += YawInput * RotationSpeed * 0.1f;
    if (CurrentRotation >= 360.0f) CurrentRotation -= 360.0f;
    if (CurrentRotation < 0.0f) CurrentRotation += 360.0f;
}

void ULesFightCharacterPreview::ZoomCharacter(float ZoomInput)
{
    CurrentZoom = FMath::Clamp(
        CurrentZoom + ZoomInput * ZoomSpeed * 0.1f,
        MinZoom, MaxZoom);
}

void ULesFightCharacterPreview::ResetCamera()
{
    CurrentRotation = 0.0f;
    CurrentZoom = DefaultZoom;
}

void ULesFightCharacterPreview::SetBackground(EPreviewBackground Background)
{
    CurrentBackground = Background;
}

void ULesFightCharacterPreview::SetLighting(
    float Intensity, float Angle, FLinearColor Color)
{
}

void ULesFightCharacterPreview::SetAutoRotate(bool bInAutoRotate)
{
    bAutoRotate = bInAutoRotate;
}

void ULesFightCharacterPreview::CaptureScreenshot(const FString& FilePath)
{
}

void ULesFightCharacterPreview::UpdatePreviewMesh(
    const FCharacterCustomizationPreset& Preset)
{
}

void ULesFightCharacterPreview::SetAnimationPreview(
    bool bPlaying, FName MontageName)
{
}

void ULesFightCharacterPreview::Reset()
{
    HidePreview();
    ResetCamera();
    bAutoRotate = false;
}
