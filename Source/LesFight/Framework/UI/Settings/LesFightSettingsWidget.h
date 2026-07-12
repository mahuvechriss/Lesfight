#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightSettingsWidget.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSettingsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable)
    void SwitchTab(int32 TabIndex);

    UFUNCTION(BlueprintCallable)
    int32 GetCurrentTab() const { return CurrentTab; }

    UFUNCTION(BlueprintCallable)
    void ApplySettings();

    UFUNCTION(BlueprintCallable)
    void SaveSettings();

    UFUNCTION(BlueprintCallable)
    void LoadSettings();

    UFUNCTION(BlueprintCallable)
    void ResetToDefaults();

    UFUNCTION(BlueprintCallable)
    void SetTabEnabled(int32 TabIndex, bool bEnabled);

    UPROPERTY(BlueprintAssignable)
    FOnSettingsApplied OnSettingsApplied;

    UPROPERTY(BlueprintAssignable)
    FOnSettingsSaved OnSettingsSaved;

    UPROPERTY(BlueprintAssignable)
    FOnTabChanged OnTabChanged;

protected:
    UPROPERTY(BlueprintReadOnly)
    int32 CurrentTab = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FText> TabNames;
};
