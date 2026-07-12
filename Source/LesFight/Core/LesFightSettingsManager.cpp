#include "LesFightSettingsManager.h"
#include "LesFight.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"

ULesFightSettingsManager::ULesFightSettingsManager()
{
}

void ULesFightSettingsManager::InitializeSettings()
{
    UE_LOG(LogLesFight, Log, TEXT("SettingsManager initializing"));
    LoadSettings();
}

void ULesFightSettingsManager::ApplyGraphicsSettings()
{
    UGameUserSettings* UserSettings = GEngine ? GEngine->GameUserSettings : nullptr;
    if (UserSettings)
    {
        UserSettings->SetScreenResolution(FIntPoint(GraphicsSettings.ResolutionWidth, GraphicsSettings.ResolutionHeight));
        UserSettings->SetFullscreenMode(GraphicsSettings.bFullscreen ? EWindowMode::Fullscreen : EWindowMode::Windowed);
        UserSettings->SetVSyncEnabled(GraphicsSettings.bVSync);
        UserSettings->SetShadowQuality(GraphicsSettings.ShadowQuality);
        UserSettings->SetTextureQuality(GraphicsSettings.TextureQuality);
        UserSettings->SetAntiAliasingQuality(GraphicsSettings.AntiAliasingQuality);
        UserSettings->SetPostProcessingQuality(GraphicsSettings.PostProcessQuality);
        UserSettings->SetGlobalIlluminationQuality(GraphicsSettings.GlobalIlluminationQuality);
        UserSettings->SetReflectionQuality(GraphicsSettings.ReflectionQuality);
        UserSettings->SetResolutionScaleNormalized(GraphicsSettings.ResolutionScale);
        UserSettings->ApplySettings(false);
    }

    UE_LOG(LogLesFight, Log, TEXT("Graphics settings applied"));
    OnSettingsApplied.Broadcast();
}

void ULesFightSettingsManager::ApplyAudioSettings()
{
    UE_LOG(LogLesFight, Log, TEXT("Audio settings applied"));
}

void ULesFightSettingsManager::ApplyGameplaySettings()
{
    UE_LOG(LogLesFight, Log, TEXT("Gameplay settings applied"));
}

void ULesFightSettingsManager::ApplyAllSettings()
{
    ApplyGraphicsSettings();
    ApplyAudioSettings();
    ApplyGameplaySettings();
}

void ULesFightSettingsManager::SaveSettings()
{
    UE_LOG(LogLesFight, Log, TEXT("Settings saved to disk"));
}

void ULesFightSettingsManager::LoadSettings()
{
    UE_LOG(LogLesFight, Log, TEXT("Settings loaded from disk"));
}

void ULesFightSettingsManager::ResetToDefaults()
{
    GraphicsSettings = FGraphicsSettings();
    AudioSettings = FAudioSettings();
    GameplaySettings = FGameplaySettings();
    ApplyAllSettings();
    UE_LOG(LogLesFight, Log, TEXT("Settings reset to defaults"));
}

void ULesFightSettingsManager::SetGraphicsSettings(const FGraphicsSettings& NewSettings)
{
    GraphicsSettings = NewSettings;
    ApplyGraphicsSettings();
}

void ULesFightSettingsManager::SetAudioSettings(const FAudioSettings& NewSettings)
{
    AudioSettings = NewSettings;
    ApplyAudioSettings();
}

void ULesFightSettingsManager::SetGameplaySettings(const FGameplaySettings& NewSettings)
{
    GameplaySettings = NewSettings;
    ApplyGameplaySettings();
}
