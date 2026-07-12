#include "LesFightGraphicsSettingsWidget.h"

void ULesFightGraphicsSettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void ULesFightGraphicsSettingsWidget::SetResolution(int32 Width, int32 Height)
{
    ResolutionWidth = Width;
    ResolutionHeight = Height;
}

void ULesFightGraphicsSettingsWidget::SetQualityPreset(int32 PresetIndex)
{
    QualityPreset = PresetIndex;
}

void ULesFightGraphicsSettingsWidget::SetTextureQuality(int32 Quality)
{
    TextureQuality = Quality;
}

void ULesFightGraphicsSettingsWidget::SetShadowQuality(int32 Quality)
{
    ShadowQuality = Quality;
}

void ULesFightGraphicsSettingsWidget::SetEffectsQuality(int32 Quality)
{
    EffectsQuality = Quality;
}

void ULesFightGraphicsSettingsWidget::SetFrameRateLimit(int32 FPS)
{
    FrameRateLimit = FPS;
}

void ULesFightGraphicsSettingsWidget::SetVSyncEnabled(bool bEnabled)
{
    bVSyncEnabled = bEnabled;
}

void ULesFightGraphicsSettingsWidget::ApplyGraphicsSettings()
{
    OnGraphicsApplied.Broadcast();
}

void ULesFightGraphicsSettingsWidget::RevertGraphicsSettings()
{
    OnGraphicsReverted.Broadcast();
}

TArray<FIntPoint> ULesFightGraphicsSettingsWidget::GetAvailableResolutions()
{
    TArray<FIntPoint> Resolutions;
    Resolutions.Add(FIntPoint(1920, 1080));
    Resolutions.Add(FIntPoint(2560, 1440));
    Resolutions.Add(FIntPoint(3840, 2160));
    Resolutions.Add(FIntPoint(1280, 720));
    return Resolutions;
}
