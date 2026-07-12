#include "LesFightSettingsWidget.h"

void ULesFightSettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    LoadSettings();
}

void ULesFightSettingsWidget::SwitchTab(int32 TabIndex)
{
    if (TabIndex >= 0 && TabIndex < TabNames.Num())
    {
        CurrentTab = TabIndex;
        OnTabChanged.Broadcast(TabIndex);
    }
}

void ULesFightSettingsWidget::ApplySettings()
{
    OnSettingsApplied.Broadcast();
}

void ULesFightSettingsWidget::SaveSettings()
{
    OnSettingsSaved.Broadcast();
}

void ULesFightSettingsWidget::LoadSettings()
{
}

void ULesFightSettingsWidget::ResetToDefaults()
{
    CurrentTab = 0;
    OnTabChanged.Broadcast(CurrentTab);
}

void ULesFightSettingsWidget::SetTabEnabled(int32 TabIndex, bool bEnabled)
{
}
