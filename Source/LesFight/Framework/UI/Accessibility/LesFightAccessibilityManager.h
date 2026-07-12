#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightAccessibilityManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAccessibilityManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void Shutdown();

    UFUNCTION(BlueprintCallable)
    void ApplySettings(FUIAccessibilitySettings Settings);

    UFUNCTION(BlueprintCallable)
    FUIAccessibilitySettings GetCurrentSettings() const { return CurrentSettings; }

    UFUNCTION(BlueprintCallable)
    void SetHighContrast(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsHighContrastActive() const { return CurrentSettings.bHighContrast; }

    UFUNCTION(BlueprintCallable)
    void SetLargeText(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsLargeTextActive() const { return CurrentSettings.bLargeText; }

    UFUNCTION(BlueprintCallable)
    void SetColorBlindMode(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsColorBlindModeActive() const { return CurrentSettings.bColorBlindMode; }

    UFUNCTION(BlueprintCallable)
    void SetSubtitleEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool AreSubtitlesEnabled() const { return CurrentSettings.bSubtitlesEnabled; }

    UFUNCTION(BlueprintCallable)
    void SetReducedMotion(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsReducedMotionActive() const { return CurrentSettings.bReducedMotion; }

    UFUNCTION(BlueprintCallable)
    void SetUIScale(float Scale);

    UFUNCTION(BlueprintCallable)
    float GetUIScale() const { return CurrentSettings.UIScale; }

    UFUNCTION(BlueprintCallable)
    void SetTextScale(float Scale);

    UFUNCTION(BlueprintCallable)
    float GetTextScale() const { return CurrentSettings.TextScale; }

    UFUNCTION(BlueprintCallable)
    void SetLanguage(FString LanguageCode);

    UFUNCTION(BlueprintCallable)
    FString GetLanguage() const { return CurrentSettings.Language; }

    UFUNCTION(BlueprintCallable)
    void SaveAccessibilitySettings();

    UFUNCTION(BlueprintCallable)
    void LoadAccessibilitySettings();

    UFUNCTION(BlueprintCallable)
    TArray<FString> GetSupportedLanguages();

    UPROPERTY(BlueprintAssignable)
    FOnAccessibilityChanged OnAccessibilityChanged;

protected:
    UPROPERTY()
    FUIAccessibilitySettings CurrentSettings;
};
