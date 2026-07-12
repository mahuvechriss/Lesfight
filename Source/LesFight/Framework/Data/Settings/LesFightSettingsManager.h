#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightSettingsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsEvent);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSettingsManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	FSettingsData LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	ESaveResult SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void ApplySettings();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void ResetToDefaults();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	FSettingsData GetCurrentSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	FGraphicsSettingsData GetGraphicsSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	FAudioSettingsData GetAudioSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	FControlSettingsData GetControlSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetGraphicsSettings(FGraphicsSettingsData Graphics);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetAudioSettings(FAudioSettingsData Audio);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetControlSettings(FControlSettingsData Controls);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetMasterVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	float GetMasterVolume();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetMusicVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	float GetMusicVolume();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetEffectsVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	float GetEffectsVolume();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetVoiceVolume(float Volume);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	float GetVoiceVolume();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetResolution(int32 Width, int32 Height);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	FIntPoint GetResolution();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetQualityPreset(int32 Preset);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	int32 GetQualityPreset();

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	void SetKeyBinding(FName ActionName, FKey Key);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	FKey GetKeyBinding(FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Settings Manager")
	bool IsDirty();

	UPROPERTY(BlueprintAssignable, Category = "Settings Manager")
	FOnSettingsEvent OnSettingsLoaded;

	UPROPERTY(BlueprintAssignable, Category = "Settings Manager")
	FOnSettingsEvent OnSettingsSaved;

	UPROPERTY(BlueprintAssignable, Category = "Settings Manager")
	FOnSettingsEvent OnSettingsApplied;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Settings Manager")
	FSettingsData CurrentSettings;

	UPROPERTY(VisibleAnywhere, Category = "Settings Manager")
	FSettingsData DefaultSettings;

	UPROPERTY(VisibleAnywhere, Category = "Settings Manager")
	bool bDirty = false;

	UPROPERTY(VisibleAnywhere, Category = "Settings Manager")
	bool bLoaded = false;
};
