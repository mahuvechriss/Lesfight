#include "LesFightScalabilitySettings.h"

void ULesFightScalabilitySettings::Initialize()
{
	BuildDefaultPresets();
	CurrentPreset = TEXT("High");
	GlobalQuality = 3;
}

void ULesFightScalabilitySettings::Shutdown()
{
	ScalabilityPresets.Empty();
}

void ULesFightScalabilitySettings::BuildDefaultPresets()
{
	FQualitySettings Ultra;
	Ultra.QualityLevel = EPerformanceQualityLevel::Ultra;
	Ultra.ResolutionScale = 100;
	Ultra.TextureQuality = ETextureQualityLevel::Full;
	Ultra.ShadowQuality = EShadowQualityLevel::Cinematic;
	Ultra.VFXQuality = EVFXQualityLevel::Ultra;
	Ultra.ViewDistance = 100;
	Ultra.bNaniteEnabled = true;
	Ultra.bLumenEnabled = true;
	Ultra.bMotionBlur = true;
	Ultra.bBloom = true;
	Ultra.bSSR = true;
	Ultra.bPostProcessing = true;

	FQualitySettings High;
	High.QualityLevel = EPerformanceQualityLevel::High;
	High.ResolutionScale = 100;
	High.TextureQuality = ETextureQualityLevel::High;
	High.ShadowQuality = EShadowQualityLevel::High;
	High.VFXQuality = EVFXQualityLevel::High;
	High.ViewDistance = 100;
	High.bNaniteEnabled = true;
	High.bLumenEnabled = true;
	High.bMotionBlur = true;
	High.bBloom = true;
	High.bSSR = true;
	High.bPostProcessing = true;

	FQualitySettings Medium;
	Medium.QualityLevel = EPerformanceQualityLevel::Medium;
	Medium.ResolutionScale = 75;
	Medium.TextureQuality = ETextureQualityLevel::Medium;
	Medium.ShadowQuality = EShadowQualityLevel::Medium;
	Medium.VFXQuality = EVFXQualityLevel::Medium;
	Medium.ViewDistance = 75;
	Medium.bNaniteEnabled = true;
	Medium.bLumenEnabled = false;
	Medium.bMotionBlur = true;
	Medium.bBloom = true;
	Medium.bSSR = true;
	Medium.bPostProcessing = true;

	FQualitySettings Low;
	Low.QualityLevel = EPerformanceQualityLevel::Low;
	Low.ResolutionScale = 50;
	Low.TextureQuality = ETextureQualityLevel::Low;
	Low.ShadowQuality = EShadowQualityLevel::Low;
	Low.VFXQuality = EVFXQualityLevel::Low;
	Low.ViewDistance = 50;
	Low.bNaniteEnabled = false;
	Low.bLumenEnabled = false;
	Low.bMotionBlur = false;
	Low.bBloom = true;
	Low.bSSR = false;
	Low.bPostProcessing = false;

	ScalabilityPresets.Add(TEXT("Ultra"), Ultra);
	ScalabilityPresets.Add(TEXT("High"), High);
	ScalabilityPresets.Add(TEXT("Medium"), Medium);
	ScalabilityPresets.Add(TEXT("Low"), Low);
}

void ULesFightScalabilitySettings::LoadScalabilitySettings()
{
}

void ULesFightScalabilitySettings::SaveScalabilitySettings()
{
}

TArray<FString> ULesFightScalabilitySettings::GetScalabilityPresets() const
{
	TArray<FString> PresetNames;
	for (const auto& Entry : ScalabilityPresets)
	{
		PresetNames.Add(Entry.Key.ToString());
	}
	return PresetNames;
}

void ULesFightScalabilitySettings::ApplyScalabilityPreset(FName PresetName)
{
	if (!ScalabilityPresets.Contains(PresetName))
	{
		return;
	}

	CurrentPreset = PresetName;
	const FQualitySettings& Settings = ScalabilityPresets[PresetName];

	switch (Settings.QualityLevel)
	{
	case EPerformanceQualityLevel::Ultra: GlobalQuality = 3; break;
	case EPerformanceQualityLevel::High:  GlobalQuality = 2; break;
	case EPerformanceQualityLevel::Medium: GlobalQuality = 1; break;
	case EPerformanceQualityLevel::Low:   GlobalQuality = 0; break;
	default:                              GlobalQuality = 2; break;
	}
}

FName ULesFightScalabilitySettings::GetCurrentPreset() const
{
	return CurrentPreset;
}

void ULesFightScalabilitySettings::SetResolutionScale(int32 Percent)
{
	if (ScalabilityPresets.Contains(CurrentPreset))
	{
		ScalabilityPresets[CurrentPreset].ResolutionScale = FMath::Clamp(Percent, 10, 200);
	}
}

void ULesFightScalabilitySettings::SetGlobalQualityLevel(int32 Level)
{
	GlobalQuality = FMath::Clamp(Level, 0, 4);
}

int32 ULesFightScalabilitySettings::GetGlobalQualityLevel() const
{
	return GlobalQuality;
}

void ULesFightScalabilitySettings::CreateCustomPreset(const FQualitySettings& Settings, FName PresetName)
{
	FQualitySettings Custom = Settings;
	Custom.QualityLevel = EPerformanceQualityLevel::Custom;
	ScalabilityPresets.Add(PresetName, Custom);
}

void ULesFightScalabilitySettings::DeleteCustomPreset(FName PresetName)
{
	static const TArray<FName> DefaultPresets = { TEXT("Ultra"), TEXT("High"), TEXT("Medium"), TEXT("Low") };
	if (DefaultPresets.Contains(PresetName))
	{
		return;
	}

	ScalabilityPresets.Remove(PresetName);
}

void ULesFightScalabilitySettings::ResetToDefaults()
{
	ScalabilityPresets.Empty();
	BuildDefaultPresets();
	CurrentPreset = TEXT("High");
	GlobalQuality = 2;
}
