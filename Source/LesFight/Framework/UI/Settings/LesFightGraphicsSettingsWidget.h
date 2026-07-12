#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightGraphicsSettingsWidget.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightGraphicsSettingsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable)
    void SetResolution(int32 Width, int32 Height);

    UFUNCTION(BlueprintCallable)
    FIntPoint GetResolution() const { return FIntPoint(ResolutionWidth, ResolutionHeight); }

    UFUNCTION(BlueprintCallable)
    void SetQualityPreset(int32 PresetIndex);

    UFUNCTION(BlueprintCallable)
    int32 GetQualityPreset() const { return QualityPreset; }

    UFUNCTION(BlueprintCallable)
    void SetTextureQuality(int32 Quality);

    UFUNCTION(BlueprintCallable)
    void SetShadowQuality(int32 Quality);

    UFUNCTION(BlueprintCallable)
    void SetEffectsQuality(int32 Quality);

    UFUNCTION(BlueprintCallable)
    void SetFrameRateLimit(int32 FPS);

    UFUNCTION(BlueprintCallable)
    void SetVSyncEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    void ApplyGraphicsSettings();

    UFUNCTION(BlueprintCallable)
    void RevertGraphicsSettings();

    UFUNCTION(BlueprintCallable)
    TArray<FIntPoint> GetAvailableResolutions();

    UPROPERTY(BlueprintAssignable)
    FOnGraphicsApplied OnGraphicsApplied;

    UPROPERTY(BlueprintAssignable)
    FOnGraphicsReverted OnGraphicsReverted;

protected:
    UPROPERTY(BlueprintReadOnly)
    int32 ResolutionWidth = 1920;

    UPROPERTY(BlueprintReadOnly)
    int32 ResolutionHeight = 1080;

    UPROPERTY(BlueprintReadOnly)
    int32 QualityPreset = 2;

    UPROPERTY(BlueprintReadOnly)
    int32 TextureQuality = 3;

    UPROPERTY(BlueprintReadOnly)
    int32 ShadowQuality = 3;

    UPROPERTY(BlueprintReadOnly)
    int32 EffectsQuality = 3;

    UPROPERTY(BlueprintReadOnly)
    int32 FrameRateLimit = 60;

    UPROPERTY(BlueprintReadOnly)
    bool bVSyncEnabled = false;
};
