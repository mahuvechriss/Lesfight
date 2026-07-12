#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioSettingsManager.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightAudioSettingsManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void LoadSettings();

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void SaveSettings();

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void SetMasterVolume(float Vol);

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void SetMusicVolume(float Vol);

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void SetSFXVolume(float Vol);

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void SetVoiceVolume(float Vol);

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void SetAmbientVolume(float Vol);

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void SetUIVolume(float Vol);

    UFUNCTION(BlueprintPure, Category = "Audio|Settings")
    FAudioSettingsData GetSettings() const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void ResetToDefaults();

    UFUNCTION(BlueprintCallable, Category = "Audio|Settings")
    void ApplySettings();

    UFUNCTION(BlueprintPure, Category = "Audio|Settings")
    float GetVolumeForBus(EAudioBusType Bus) const;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Audio|Settings")
    FAudioSettingsData CurrentSettings;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Settings")
    FString SettingsSavePath;

private:
    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
