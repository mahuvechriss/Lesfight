#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightControlSettingsWidget.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightControlSettingsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable)
    void SetKeyBinding(FName ActionName, FKey NewKey);

    UFUNCTION(BlueprintCallable)
    void ResetKeyBinding(FName ActionName);

    UFUNCTION(BlueprintCallable)
    void ResetAllKeyBindings();

    UFUNCTION(BlueprintCallable)
    FKey GetKeyBinding(FName ActionName) const;

    UFUNCTION(BlueprintCallable)
    void SetControllerSensitivity(float Sensitivity);

    UFUNCTION(BlueprintCallable)
    float GetControllerSensitivity() const { return ControllerSensitivity; }

    UFUNCTION(BlueprintCallable)
    void SetVibrationEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsVibrationEnabled() const { return bVibrationEnabled; }

    UFUNCTION(BlueprintCallable)
    void SetInvertYAxis(bool bInvert);

    UFUNCTION(BlueprintCallable)
    bool IsYAxisInverted() const { return bInvertYAxis; }

    UFUNCTION(BlueprintCallable)
    void SetControlScheme(int32 SchemeIndex);

    UFUNCTION(BlueprintCallable)
    int32 GetControlScheme() const { return ControlScheme; }

    UFUNCTION(BlueprintCallable)
    void ApplyControlSettings();

    UFUNCTION(BlueprintCallable)
    void RevertControlSettings();

    UPROPERTY(BlueprintAssignable)
    FOnControlsApplied OnControlsApplied;

    UPROPERTY(BlueprintAssignable)
    FOnControlsReverted OnControlsReverted;

protected:
    void InitializeDefaultKeyBindings();

    UPROPERTY()
    TMap<FName, FKey> KeyBindings;

    UPROPERTY()
    TMap<FName, FKey> SavedKeyBindings;

    UPROPERTY(BlueprintReadOnly)
    float ControllerSensitivity = 0.5f;

    UPROPERTY(BlueprintReadOnly)
    bool bVibrationEnabled = true;

    UPROPERTY(BlueprintReadOnly)
    bool bInvertYAxis = false;

    UPROPERTY(BlueprintReadOnly)
    int32 ControlScheme = 0;
};
