#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightAudioSettingsWidget.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAudioSettingsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable)
    void SetMasterVolume(float Volume);

    UFUNCTION(BlueprintCallable)
    float GetMasterVolume() const { return MasterVol; }

    UFUNCTION(BlueprintCallable)
    void SetMusicVolume(float Volume);

    UFUNCTION(BlueprintCallable)
    float GetMusicVolume() const { return MusicVol; }

    UFUNCTION(BlueprintCallable)
    void SetEffectsVolume(float Volume);

    UFUNCTION(BlueprintCallable)
    float GetEffectsVolume() const { return EffectsVol; }

    UFUNCTION(BlueprintCallable)
    void SetVoiceVolume(float Volume);

    UFUNCTION(BlueprintCallable)
    float GetVoiceVolume() const { return VoiceVol; }

    UFUNCTION(BlueprintCallable)
    void SetVolumePreset(int32 PresetIndex);

    UFUNCTION(BlueprintCallable)
    void ApplyAudioSettings();

    UFUNCTION(BlueprintCallable)
    void RevertAudioSettings();

    UFUNCTION(BlueprintCallable)
    void MuteAll(bool bShouldMute);

    UFUNCTION(BlueprintCallable)
    bool IsMuted() const { return bMuted; }

protected:
    UPROPERTY(BlueprintReadOnly)
    float MasterVol = 1.0f;

    UPROPERTY(BlueprintReadOnly)
    float MusicVol = 0.8f;

    UPROPERTY(BlueprintReadOnly)
    float EffectsVol = 1.0f;

    UPROPERTY(BlueprintReadOnly)
    float VoiceVol = 1.0f;

    UPROPERTY()
    float SavedMasterVol = 1.0f;

    UPROPERTY()
    float SavedMusicVol = 0.8f;

    UPROPERTY()
    float SavedEffectsVol = 1.0f;

    UPROPERTY()
    float SavedVoiceVol = 1.0f;

    UPROPERTY(BlueprintReadOnly)
    int32 VolumePreset = 0;

    UPROPERTY(BlueprintReadOnly)
    bool bMuted = false;
};
