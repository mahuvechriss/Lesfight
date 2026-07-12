#include "LesFightGraphicsQualityManager.h"
#include "Kismet/KismetSystemLibrary.h"

void ULesFightGraphicsQualityManager::Initialize()
{
	BuildDefaultPresets();
	CurrentLevel = EPerformanceQualityLevel::High;
	CurrentSettings = QualityPresets[CurrentLevel];
	RecommendedSettings = CurrentSettings;
}

void ULesFightGraphicsQualityManager::Shutdown()
{
	QualityPresets.Empty();
}

void ULesFightGraphicsQualityManager::BuildDefaultPresets()
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

	QualityPresets.Add(EPerformanceQualityLevel::Ultra, Ultra);
	QualityPresets.Add(EPerformanceQualityLevel::High, High);
	QualityPresets.Add(EPerformanceQualityLevel::Medium, Medium);
	QualityPresets.Add(EPerformanceQualityLevel::Low, Low);
}

void ULesFightGraphicsQualityManager::SetQualityLevel(EPerformanceQualityLevel Level)
{
	if (!QualityPresets.Contains(Level))
	{
		return;
	}

	CurrentLevel = Level;
	const FQualitySettings& Preset = QualityPresets[Level];
	ApplyGraphicsSettings(Preset);
}

EPerformanceQualityLevel ULesFightGraphicsQualityManager::GetQualityLevel() const
{
	return CurrentLevel;
}

void ULesFightGraphicsQualityManager::ApplyGraphicsSettings(const FQualitySettings& Settings)
{
	CurrentSettings = Settings;

	SetResolutionScale(Settings.ResolutionScale);
	SetTextureQuality(Settings.TextureQuality);
	SetShadowQuality(Settings.ShadowQuality);
	SetVFXQuality(Settings.VFXQuality);
	SetViewDistance(Settings.ViewDistance);
	ToggleNanite(Settings.bNaniteEnabled);
	ToggleLumen(Settings.bLumenEnabled);
	ToggleMotionBlur(Settings.bMotionBlur);
	ToggleBloom(Settings.bBloom);
	ToggleSSR(Settings.bSSR);
	TogglePostProcessing(Settings.bPostProcessing);

	OnQualitySettingsApplied.Broadcast();
}

FQualitySettings ULesFightGraphicsQualityManager::GetCurrentSettings() const
{
	return CurrentSettings;
}

FQualitySettings ULesFightGraphicsQualityManager::GetRecommendedSettings() const
{
	return RecommendedSettings;
}

void ULesFightGraphicsQualityManager::SetTextureQuality(ETextureQualityLevel Level)
{
	CurrentSettings.TextureQuality = Level;

	FString Cmd;
	switch (Level)
	{
	case ETextureQualityLevel::Full:   Cmd = TEXT("r.StreamingPoolSize 4096"); break;
	case ETextureQualityLevel::High:   Cmd = TEXT("r.StreamingPoolSize 2048"); break;
	case ETextureQualityLevel::Medium: Cmd = TEXT("r.StreamingPoolSize 1024"); break;
	case ETextureQualityLevel::Low:    Cmd = TEXT("r.StreamingPoolSize 512"); break;
	case ETextureQualityLevel::Mobile: Cmd = TEXT("r.StreamingPoolSize 256"); break;
	}
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), Cmd);
}

void ULesFightGraphicsQualityManager::SetShadowQuality(EShadowQualityLevel Level)
{
	CurrentSettings.ShadowQuality = Level;

	int32 Value;
	switch (Level)
	{
	case EShadowQualityLevel::Cinematic: Value = 5; break;
	case EShadowQualityLevel::High:      Value = 4; break;
	case EShadowQualityLevel::Medium:    Value = 3; break;
	case EShadowQualityLevel::Low:       Value = 2; break;
	case EShadowQualityLevel::Disabled:  Value = 0; break;
	default:                             Value = 3; break;
	}
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.ShadowQuality %d"), Value));
}

void ULesFightGraphicsQualityManager::SetVFXQuality(EVFXQualityLevel Level)
{
	CurrentSettings.VFXQuality = Level;

	int32 Value;
	switch (Level)
	{
	case EVFXQualityLevel::Ultra:   Value = 5; break;
	case EVFXQualityLevel::High:    Value = 4; break;
	case EVFXQualityLevel::Medium:  Value = 3; break;
	case EVFXQualityLevel::Low:     Value = 2; break;
	case EVFXQualityLevel::Minimal: Value = 1; break;
	default:                        Value = 3; break;
	}
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.VFXQuality %d"), Value));
}

void ULesFightGraphicsQualityManager::SetResolutionScale(int32 Percent)
{
	CurrentSettings.ResolutionScale = FMath::Clamp(Percent, 10, 200);

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.SetResQuality %d"), CurrentSettings.ResolutionScale));
}

void ULesFightGraphicsQualityManager::SetViewDistance(int32 Percent)
{
	CurrentSettings.ViewDistance = FMath::Clamp(Percent, 10, 200);

	const float Scale = CurrentSettings.ViewDistance / 100.0f;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.ViewDistanceScale %f"), Scale));
}

void ULesFightGraphicsQualityManager::ToggleNanite(bool bEnabled)
{
	CurrentSettings.bNaniteEnabled = bEnabled;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		bEnabled ? TEXT("r.Nanite 1") : TEXT("r.Nanite 0"));
}

void ULesFightGraphicsQualityManager::ToggleLumen(bool bEnabled)
{
	CurrentSettings.bLumenEnabled = bEnabled;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		bEnabled ? TEXT("r.Lumen 1") : TEXT("r.Lumen 0"));
}

void ULesFightGraphicsQualityManager::ToggleMotionBlur(bool bEnabled)
{
	CurrentSettings.bMotionBlur = bEnabled;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		bEnabled ? TEXT("r.MotionBlurQuality 5") : TEXT("r.MotionBlurQuality 0"));
}

void ULesFightGraphicsQualityManager::ToggleBloom(bool bEnabled)
{
	CurrentSettings.bBloom = bEnabled;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		bEnabled ? TEXT("r.BloomQuality 5") : TEXT("r.BloomQuality 0"));
}

void ULesFightGraphicsQualityManager::ToggleSSR(bool bEnabled)
{
	CurrentSettings.bSSR = bEnabled;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		bEnabled ? TEXT("r.SSR.Quality 4") : TEXT("r.SSR.Quality 0"));
}

void ULesFightGraphicsQualityManager::TogglePostProcessing(bool bEnabled)
{
	CurrentSettings.bPostProcessing = bEnabled;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		bEnabled ? TEXT("r.PostProcessing.Enable 1") : TEXT("r.PostProcessing.Enable 0"));
}

FString ULesFightGraphicsQualityManager::GetScalabilityString() const
{
	return FString::Printf(TEXT("Quality=%d,ResScale=%d,Textures=%d,Shadows=%d,VFX=%d,ViewDist=%d,Nanite=%d,Lumen=%d,MotionBlur=%d,Bloom=%d,SSR=%d,PostProcess=%d"),
		static_cast<int32>(CurrentLevel),
		CurrentSettings.ResolutionScale,
		static_cast<int32>(CurrentSettings.TextureQuality),
		static_cast<int32>(CurrentSettings.ShadowQuality),
		static_cast<int32>(CurrentSettings.VFXQuality),
		CurrentSettings.ViewDistance,
		CurrentSettings.bNaniteEnabled ? 1 : 0,
		CurrentSettings.bLumenEnabled ? 1 : 0,
		CurrentSettings.bMotionBlur ? 1 : 0,
		CurrentSettings.bBloom ? 1 : 0,
		CurrentSettings.bSSR ? 1 : 0,
		CurrentSettings.bPostProcessing ? 1 : 0);
}
