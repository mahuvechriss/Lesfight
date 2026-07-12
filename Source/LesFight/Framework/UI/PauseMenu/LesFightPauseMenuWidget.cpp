#include "LesFightPauseMenuWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"

void ULesFightPauseMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void ULesFightPauseMenuWidget::ResumeGame()
{
    OnResumeGame.Broadcast();
}

void ULesFightPauseMenuWidget::RestartMatch()
{
    OnRestartMatch.Broadcast();
}

void ULesFightPauseMenuWidget::OpenSettings()
{
    OnOpenSettings.Broadcast();
}

void ULesFightPauseMenuWidget::OpenControls()
{
    OnOpenControls.Broadcast();
}

void ULesFightPauseMenuWidget::OpenAudioOptions()
{
    OnOpenAudio.Broadcast();
}

void ULesFightPauseMenuWidget::OpenGraphicsOptions()
{
    OnOpenGraphics.Broadcast();
}

void ULesFightPauseMenuWidget::OpenAccessibility()
{
    OnOpenAccessibility.Broadcast();
}

void ULesFightPauseMenuWidget::QuitMatch()
{
    OnQuitMatch.Broadcast();
}

void ULesFightPauseMenuWidget::QuitToMainMenu()
{
    OnQuitToMainMenu.Broadcast();
}

void ULesFightPauseMenuWidget::SetPauseMenuTitle(FText Title)
{
}

void ULesFightPauseMenuWidget::SetMenuItemsEnabled(TArray<bool> EnabledStates)
{
    for (int32 i = 0; i < FMath::Min(EnabledStates.Num(), MenuItems.Num()); ++i)
    {
        MenuItems[i].bEnabled = EnabledStates[i];
    }
}
