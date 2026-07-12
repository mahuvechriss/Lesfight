#include "Framework/Audio/Core/LesFightAudioSettingsManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Misc/Parse.h"

void ULesFightAudioSettingsManager::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    SettingsSavePath = FPaths::ProjectSavedDir() / TEXT("AudioSettings.ini");
    LoadSettings();
}

void ULesFightAudioSettingsManager::LoadSettings()
{
    if (FPaths::FileExists(SettingsSavePath))
    {
        FString FileContent;
        if (FFileHelper::LoadFileToString(FileContent, *SettingsSavePath))
        {
            float Value;
            if (FParse::Value(*FileContent, TEXT("MasterVolume="), Value)) CurrentSettings.MasterVolume = Value;
            if (FParse::Value(*FileContent, TEXT("MusicVolume="), Value)) CurrentSettings.MusicVolume = Value;
            if (FParse::Value(*FileContent, TEXT("SFXVolume="), Value)) CurrentSettings.SFXVolume = Value;
            if (FParse::Value(*FileContent, TEXT("VoiceVolume="), Value)) CurrentSettings.VoiceVolume = Value;
            if (FParse::Value(*FileContent, TEXT("AmbientVolume="), Value)) CurrentSettings.AmbientVolume = Value;
            if (FParse::Value(*FileContent, TEXT("UIVolume="), Value)) CurrentSettings.UIVolume = Value;
            return;
        }
    }
    ResetToDefaults();
}

void ULesFightAudioSettingsManager::SaveSettings()
{
    FString FileContent;
    FileContent += FString::Printf(TEXT("MasterVolume=%f\n"), CurrentSettings.MasterVolume);
    FileContent += FString::Printf(TEXT("MusicVolume=%f\n"), CurrentSettings.MusicVolume);
    FileContent += FString::Printf(TEXT("SFXVolume=%f\n"), CurrentSettings.SFXVolume);
    FileContent += FString::Printf(TEXT("VoiceVolume=%f\n"), CurrentSettings.VoiceVolume);
    FileContent += FString::Printf(TEXT("AmbientVolume=%f\n"), CurrentSettings.AmbientVolume);
    FileContent += FString::Printf(TEXT("UIVolume=%f\n"), CurrentSettings.UIVolume);
    FFileHelper::SaveStringToFile(FileContent, *SettingsSavePath);
}

void ULesFightAudioSettingsManager::SetMasterVolume(float Vol)
{
    CurrentSettings.MasterVolume = FMath::Clamp(Vol, 0.0f, 1.0f);
}

void ULesFightAudioSettingsManager::SetMusicVolume(float Vol)
{
    CurrentSettings.MusicVolume = FMath::Clamp(Vol, 0.0f, 1.0f);
}

void ULesFightAudioSettingsManager::SetSFXVolume(float Vol)
{
    CurrentSettings.SFXVolume = FMath::Clamp(Vol, 0.0f, 1.0f);
}

void ULesFightAudioSettingsManager::SetVoiceVolume(float Vol)
{
    CurrentSettings.VoiceVolume = FMath::Clamp(Vol, 0.0f, 1.0f);
}

void ULesFightAudioSettingsManager::SetAmbientVolume(float Vol)
{
    CurrentSettings.AmbientVolume = FMath::Clamp(Vol, 0.0f, 1.0f);
}

void ULesFightAudioSettingsManager::SetUIVolume(float Vol)
{
    CurrentSettings.UIVolume = FMath::Clamp(Vol, 0.0f, 1.0f);
}

FAudioSettingsData ULesFightAudioSettingsManager::GetSettings() const
{
    return CurrentSettings;
}

void ULesFightAudioSettingsManager::ResetToDefaults()
{
    CurrentSettings.MasterVolume = 1.0f;
    CurrentSettings.MusicVolume = 0.8f;
    CurrentSettings.SFXVolume = 1.0f;
    CurrentSettings.VoiceVolume = 0.9f;
    CurrentSettings.AmbientVolume = 0.6f;
    CurrentSettings.UIVolume = 0.8f;
}

void ULesFightAudioSettingsManager::ApplySettings()
{
    if (!OwnerManager.IsValid()) return;
}

float ULesFightAudioSettingsManager::GetVolumeForBus(EAudioBusType Bus) const
{
    switch (Bus)
    {
    case EAudioBusType::Master:    return CurrentSettings.MasterVolume;
    case EAudioBusType::Music:     return CurrentSettings.MusicVolume;
    case EAudioBusType::SFX:       return CurrentSettings.SFXVolume;
    case EAudioBusType::Voice:     return CurrentSettings.VoiceVolume;
    case EAudioBusType::Ambient:   return CurrentSettings.AmbientVolume;
    case EAudioBusType::Cinematic: return 1.0f;
    case EAudioBusType::UI:        return CurrentSettings.UIVolume;
    default:                       return 1.0f;
    }
}
