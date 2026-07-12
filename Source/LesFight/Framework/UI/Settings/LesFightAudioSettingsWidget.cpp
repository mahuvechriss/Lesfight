#include "LesFightAudioSettingsWidget.h"

void ULesFightAudioSettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void ULesFightAudioSettingsWidget::SetMasterVolume(float Volume)
{
    MasterVol = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void ULesFightAudioSettingsWidget::SetMusicVolume(float Volume)
{
    MusicVol = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void ULesFightAudioSettingsWidget::SetEffectsVolume(float Volume)
{
    EffectsVol = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void ULesFightAudioSettingsWidget::SetVoiceVolume(float Volume)
{
    VoiceVol = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void ULesFightAudioSettingsWidget::SetVolumePreset(int32 PresetIndex)
{
    VolumePreset = PresetIndex;
    switch (PresetIndex)
    {
    case 0:
        break;
    case 1:
        MasterVol = 1.0f;
        MusicVol = 1.0f;
        EffectsVol = 1.0f;
        VoiceVol = 1.0f;
        break;
    case 2:
        MasterVol = 1.0f;
        MusicVol = 0.7f;
        EffectsVol = 0.9f;
        VoiceVol = 0.8f;
        break;
    case 3:
        MasterVol = 1.0f;
        MusicVol = 1.0f;
        EffectsVol = 0.8f;
        VoiceVol = 0.6f;
        break;
    default:
        break;
    }
}

void ULesFightAudioSettingsWidget::ApplyAudioSettings()
{
    SavedMasterVol = MasterVol;
    SavedMusicVol = MusicVol;
    SavedEffectsVol = EffectsVol;
    SavedVoiceVol = VoiceVol;
}

void ULesFightAudioSettingsWidget::RevertAudioSettings()
{
    MasterVol = SavedMasterVol;
    MusicVol = SavedMusicVol;
    EffectsVol = SavedEffectsVol;
    VoiceVol = SavedVoiceVol;
}

void ULesFightAudioSettingsWidget::MuteAll(bool bShouldMute)
{
    bMuted = bShouldMute;
    if (bShouldMute)
    {
        SavedMasterVol = MasterVol;
        SavedMusicVol = MusicVol;
        SavedEffectsVol = EffectsVol;
        SavedVoiceVol = VoiceVol;
        MasterVol = 0.0f;
        MusicVol = 0.0f;
        EffectsVol = 0.0f;
        VoiceVol = 0.0f;
    }
    else
    {
        MasterVol = SavedMasterVol;
        MusicVol = SavedMusicVol;
        EffectsVol = SavedEffectsVol;
        VoiceVol = SavedVoiceVol;
    }
}
