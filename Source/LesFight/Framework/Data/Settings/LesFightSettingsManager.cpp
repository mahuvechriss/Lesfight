#include "LesFightSettingsManager.h"
#include "Framework/Data/Core/LesFightDataTypes.h"

void ULesFightSettingsManager::Initialize()
{
	DefaultSettings.Graphics.Resolution = FIntPoint(1920, 1080);
	DefaultSettings.Graphics.QualityPreset = 2;

	FSettingsData Loaded = LoadSettings();
	if (Loaded.Graphics.Resolution.X == 0)
	{
		CurrentSettings = DefaultSettings;
	}
}

void ULesFightSettingsManager::Shutdown()
{
	CurrentSettings = FSettingsData();
	bLoaded = false;
	bDirty = false;
}

FSettingsData ULesFightSettingsManager::LoadSettings()
{
	// Load from SaveManager in production
	CurrentSettings = DefaultSettings;
	bLoaded = true;
	OnSettingsLoaded.Broadcast();
	return CurrentSettings;
}

ESaveResult ULesFightSettingsManager::SaveSettings()
{
	// SaveManager->SaveSettings(CurrentSettings)
	bDirty = false;
	OnSettingsSaved.Broadcast();
	return ESaveResult::Success;
}

void ULesFightSettingsManager::ApplySettings()
{
	OnSettingsApplied.Broadcast();
}

void ULesFightSettingsManager::ResetToDefaults()
{
	CurrentSettings = DefaultSettings;
	bDirty = true;
}

FSettingsData ULesFightSettingsManager::GetCurrentSettings()
{
	return CurrentSettings;
}

FGraphicsSettingsData ULesFightSettingsManager::GetGraphicsSettings()
{
	return CurrentSettings.Graphics;
}

FAudioSettingsData ULesFightSettingsManager::GetAudioSettings()
{
	return CurrentSettings.Audio;
}

FControlSettingsData ULesFightSettingsManager::GetControlSettings()
{
	return CurrentSettings.Controls;
}

void ULesFightSettingsManager::SetGraphicsSettings(FGraphicsSettingsData Graphics)
{
	CurrentSettings.Graphics = Graphics;
	bDirty = true;
}

void ULesFightSettingsManager::SetAudioSettings(FAudioSettingsData Audio)
{
	CurrentSettings.Audio = Audio;
	bDirty = true;
}

void ULesFightSettingsManager::SetControlSettings(FControlSettingsData Controls)
{
	CurrentSettings.Controls = Controls;
	bDirty = true;
}

void ULesFightSettingsManager::SetMasterVolume(float Volume)
{
	CurrentSettings.Audio.MasterVolume = Volume;
	bDirty = true;
}

float ULesFightSettingsManager::GetMasterVolume()
{
	return CurrentSettings.Audio.MasterVolume;
}

void ULesFightSettingsManager::SetMusicVolume(float Volume)
{
	CurrentSettings.Audio.MusicVolume = Volume;
	bDirty = true;
}

float ULesFightSettingsManager::GetMusicVolume()
{
	return CurrentSettings.Audio.MusicVolume;
}

void ULesFightSettingsManager::SetEffectsVolume(float Volume)
{
	CurrentSettings.Audio.EffectsVolume = Volume;
	bDirty = true;
}

float ULesFightSettingsManager::GetEffectsVolume()
{
	return CurrentSettings.Audio.EffectsVolume;
}

void ULesFightSettingsManager::SetVoiceVolume(float Volume)
{
	CurrentSettings.Audio.VoiceVolume = Volume;
	bDirty = true;
}

float ULesFightSettingsManager::GetVoiceVolume()
{
	return CurrentSettings.Audio.VoiceVolume;
}

void ULesFightSettingsManager::SetResolution(int32 Width, int32 Height)
{
	CurrentSettings.Graphics.Resolution = FIntPoint(Width, Height);
	bDirty = true;
}

FIntPoint ULesFightSettingsManager::GetResolution()
{
	return CurrentSettings.Graphics.Resolution;
}

void ULesFightSettingsManager::SetQualityPreset(int32 Preset)
{
	CurrentSettings.Graphics.QualityPreset = Preset;
	bDirty = true;
}

int32 ULesFightSettingsManager::GetQualityPreset()
{
	return CurrentSettings.Graphics.QualityPreset;
}

void ULesFightSettingsManager::SetKeyBinding(FName ActionName, FKey Key)
{
	CurrentSettings.Controls.KeyBindings.Add(ActionName, Key);
	bDirty = true;
}

FKey ULesFightSettingsManager::GetKeyBinding(FName ActionName)
{
	const FKey* Found = CurrentSettings.Controls.KeyBindings.Find(ActionName);
	if (Found)
	{
		return *Found;
	}
	return FKey();
}

bool ULesFightSettingsManager::IsDirty()
{
	return bDirty;
}
