#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightSettingsManager.generated.h"

USTRUCT(BlueprintType)
struct FGraphicsSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResolutionWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ResolutionHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bFullscreen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bVSync;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ShadowQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TextureQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AntiAliasingQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PostProcessQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GlobalIlluminationQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ReflectionQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ResolutionScale;

    FGraphicsSettings()
        : ResolutionWidth(1920)
        , ResolutionHeight(1080)
        , bFullscreen(true)
        , bVSync(true)
        , ShadowQuality(3)
        , TextureQuality(3)
        , AntiAliasingQuality(3)
        , PostProcessQuality(3)
        , GlobalIlluminationQuality(3)
        , ReflectionQuality(3)
        , ResolutionScale(1.0f)
    {}
};

USTRUCT(BlueprintType)
struct FAudioSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MasterVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MusicVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SFXVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VoiceVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float UIVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSpatialAudio;

    FAudioSettings()
        : MasterVolume(1.0f)
        , MusicVolume(0.8f)
        , SFXVolume(1.0f)
        , VoiceVolume(1.0f)
        , UIVolume(0.7f)
        , bSpatialAudio(true)
    {}
};

USTRUCT(BlueprintType)
struct FGameplaySettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraSensitivity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInvertYAxis;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCameraShake;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHitStop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 InputBufferSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageNumbersScale;

    FGameplaySettings()
        : CameraSensitivity(1.0f)
        , bInvertYAxis(false)
        , bCameraShake(true)
        , bHitStop(true)
        , InputBufferSize(10)
        , DamageNumbersScale(1.0f)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsApplied);

UCLASS(Blueprintable)
class ULesFightSettingsManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightSettingsManager();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void InitializeSettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void ApplyGraphicsSettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void ApplyAudioSettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void ApplyGameplaySettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void ApplyAllSettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void SaveSettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void LoadSettings();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void ResetToDefaults();

    UFUNCTION(BlueprintPure, Category = "LesFight|Settings")
    FGraphicsSettings GetGraphicsSettings() const { return GraphicsSettings; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void SetGraphicsSettings(const FGraphicsSettings& NewSettings);

    UFUNCTION(BlueprintPure, Category = "LesFight|Settings")
    FAudioSettings GetAudioSettings() const { return AudioSettings; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void SetAudioSettings(const FAudioSettings& NewSettings);

    UFUNCTION(BlueprintPure, Category = "LesFight|Settings")
    FGameplaySettings GetGameplaySettings() const { return GameplaySettings; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    void SetGameplaySettings(const FGameplaySettings& NewSettings);

    UFUNCTION(BlueprintPure, Category = "LesFight|Settings")
    float GetMasterVolume() const { return AudioSettings.MasterVolume; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Settings")
    float GetSFXVolume() const { return AudioSettings.SFXVolume; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Settings")
    float GetMusicVolume() const { return AudioSettings.MusicVolume; }

protected:
    UPROPERTY(BlueprintReadWrite, Category = "LesFight|Settings")
    FGraphicsSettings GraphicsSettings;

    UPROPERTY(BlueprintReadWrite, Category = "LesFight|Settings")
    FAudioSettings AudioSettings;

    UPROPERTY(BlueprintReadWrite, Category = "LesFight|Settings")
    FGameplaySettings GameplaySettings;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnSettingsApplied OnSettingsApplied;

private:
    FString ConfigFilePath;
};
