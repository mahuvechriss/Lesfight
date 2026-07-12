#include "LesFightAccessibilityManager.h"

void ULesFightAccessibilityManager::Initialize()
{
    LoadAccessibilitySettings();
}

void ULesFightAccessibilityManager::Shutdown()
{
    SaveAccessibilitySettings();
}

void ULesFightAccessibilityManager::ApplySettings(FUIAccessibilitySettings Settings)
{
    CurrentSettings = Settings;
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetHighContrast(bool bEnabled)
{
    CurrentSettings.bHighContrast = bEnabled;
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetLargeText(bool bEnabled)
{
    CurrentSettings.bLargeText = bEnabled;
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetColorBlindMode(bool bEnabled)
{
    CurrentSettings.bColorBlindMode = bEnabled;
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetSubtitleEnabled(bool bEnabled)
{
    CurrentSettings.bSubtitlesEnabled = bEnabled;
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetReducedMotion(bool bEnabled)
{
    CurrentSettings.bReducedMotion = bEnabled;
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetUIScale(float Scale)
{
    CurrentSettings.UIScale = FMath::Clamp(Scale, 0.5f, 2.0f);
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetTextScale(float Scale)
{
    CurrentSettings.TextScale = FMath::Clamp(Scale, 0.5f, 2.0f);
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SetLanguage(FString LanguageCode)
{
    CurrentSettings.Language = LanguageCode;
    OnAccessibilityChanged.Broadcast(CurrentSettings);
}

void ULesFightAccessibilityManager::SaveAccessibilitySettings()
{
}

void ULesFightAccessibilityManager::LoadAccessibilitySettings()
{
}

TArray<FString> ULesFightAccessibilityManager::GetSupportedLanguages()
{
    TArray<FString> Languages;
    Languages.Add(TEXT("en"));
    Languages.Add(TEXT("fr"));
    Languages.Add(TEXT("de"));
    Languages.Add(TEXT("es"));
    Languages.Add(TEXT("ja"));
    Languages.Add(TEXT("ko"));
    Languages.Add(TEXT("zh"));
    Languages.Add(TEXT("pt"));
    Languages.Add(TEXT("ru"));
    return Languages;
}
