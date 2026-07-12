#include "LesFightControlSettingsWidget.h"
#include "InputCoreTypes.h"

void ULesFightControlSettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    InitializeDefaultKeyBindings();
}

void ULesFightControlSettingsWidget::InitializeDefaultKeyBindings()
{
    KeyBindings.Empty();
    KeyBindings.Add(TEXT("MoveUp"), FKey(TEXT("W")));
    KeyBindings.Add(TEXT("MoveDown"), FKey(TEXT("S")));
    KeyBindings.Add(TEXT("MoveLeft"), FKey(TEXT("A")));
    KeyBindings.Add(TEXT("MoveRight"), FKey(TEXT("D")));
    KeyBindings.Add(TEXT("Jump"), FKey(TEXT("SpaceBar")));
    KeyBindings.Add(TEXT("Punch"), FKey(TEXT("LeftMouseButton")));
    KeyBindings.Add(TEXT("Kick"), FKey(TEXT("RightMouseButton")));
    KeyBindings.Add(TEXT("Block"), FKey(TEXT("Q")));
    KeyBindings.Add(TEXT("Special"), FKey(TEXT("E")));
    KeyBindings.Add(TEXT("Ultimate"), FKey(TEXT("R")));
    KeyBindings.Add(TEXT("Throw"), FKey(TEXT("F")));
    KeyBindings.Add(TEXT("Pause"), FKey(TEXT("Tab")));
    KeyBindings.Add(TEXT("Menu"), FKey(TEXT("Escape")));
    SavedKeyBindings = KeyBindings;
}

void ULesFightControlSettingsWidget::SetKeyBinding(FName ActionName, FKey NewKey)
{
    if (KeyBindings.Contains(ActionName))
    {
        KeyBindings[ActionName] = NewKey;
    }
}

void ULesFightControlSettingsWidget::ResetKeyBinding(FName ActionName)
{
    InitializeDefaultKeyBindings();
}

void ULesFightControlSettingsWidget::ResetAllKeyBindings()
{
    InitializeDefaultKeyBindings();
}

FKey ULesFightControlSettingsWidget::GetKeyBinding(FName ActionName) const
{
    const FKey* Found = KeyBindings.Find(ActionName);
    if (Found)
    {
        return *Found;
    }
    return FKey();
}

void ULesFightControlSettingsWidget::SetControllerSensitivity(float Sensitivity)
{
    ControllerSensitivity = FMath::Clamp(Sensitivity, 0.0f, 1.0f);
}

void ULesFightControlSettingsWidget::SetVibrationEnabled(bool bEnabled)
{
    bVibrationEnabled = bEnabled;
}

void ULesFightControlSettingsWidget::SetInvertYAxis(bool bInvert)
{
    bInvertYAxis = bInvert;
}

void ULesFightControlSettingsWidget::SetControlScheme(int32 SchemeIndex)
{
    ControlScheme = SchemeIndex;
}

void ULesFightControlSettingsWidget::ApplyControlSettings()
{
    SavedKeyBindings = KeyBindings;
    OnControlsApplied.Broadcast();
}

void ULesFightControlSettingsWidget::RevertControlSettings()
{
    KeyBindings = SavedKeyBindings;
    OnControlsReverted.Broadcast();
}
