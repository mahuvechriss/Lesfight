#include "LesFightMainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ULesFightMainMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (MenuButtons.Num() >= 7)
    {
        MenuButtons[0]->OnClicked.AddDynamic(this, &ULesFightMainMenuWidget::NavigateToPlay);
        MenuButtons[1]->OnClicked.AddDynamic(this, &ULesFightMainMenuWidget::NavigateToMultiplayer);
        MenuButtons[2]->OnClicked.AddDynamic(this, &ULesFightMainMenuWidget::NavigateToCharacterCreator);
        MenuButtons[3]->OnClicked.AddDynamic(this, &ULesFightMainMenuWidget::NavigateToProfile);
        MenuButtons[4]->OnClicked.AddDynamic(this, &ULesFightMainMenuWidget::NavigateToSettings);
        MenuButtons[5]->OnClicked.AddDynamic(this, &ULesFightMainMenuWidget::NavigateToCredits);
        MenuButtons[6]->OnClicked.AddDynamic(this, &ULesFightMainMenuWidget::QuitGame);
    }
}

void ULesFightMainMenuWidget::SetBackgroundScene(UTextureRenderTarget2D* Scene)
{
    BackgroundImage = Scene;
}

void ULesFightMainMenuWidget::PlayTitleAnimation()
{
    PlayAnimation(nullptr);
}

void ULesFightMainMenuWidget::PlayMenuEntranceAnimation()
{
    PlayAnimation(nullptr);
}

void ULesFightMainMenuWidget::PlayButtonHighlight(int32 ButtonIndex)
{
    if (!MenuButtons.IsValidIndex(ButtonIndex))
    {
        return;
    }

    HighlightedIndex = ButtonIndex;

    UButton* Button = MenuButtons[ButtonIndex];
    if (Button)
    {
        FWidgetTransform Transform;
        Transform.Scale = FVector2D(1.1f, 1.1f);
        Button->SetRenderTransform(Transform);
    }
}

void ULesFightMainMenuWidget::NavigateToPlay()
{
    OnPlayClicked.Broadcast();
}

void ULesFightMainMenuWidget::NavigateToMultiplayer()
{
    OnMultiplayerClicked.Broadcast();
}

void ULesFightMainMenuWidget::NavigateToCharacterCreator()
{
    OnCharacterCreatorClicked.Broadcast();
}

void ULesFightMainMenuWidget::NavigateToProfile()
{
    OnProfileClicked.Broadcast();
}

void ULesFightMainMenuWidget::NavigateToSettings()
{
    OnSettingsClicked.Broadcast();
}

void ULesFightMainMenuWidget::NavigateToCredits()
{
    OnCreditsClicked.Broadcast();
}

void ULesFightMainMenuWidget::QuitGame()
{
    OnExitClicked.Broadcast();

    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
    }
}

void ULesFightMainMenuWidget::SetMenuButtonEnabled(int32 ButtonIndex, bool bEnabled)
{
    if (MenuButtons.IsValidIndex(ButtonIndex))
    {
        MenuButtons[ButtonIndex]->SetIsEnabled(bEnabled);
    }
}

void ULesFightMainMenuWidget::SetMenuButtonText(int32 ButtonIndex, FText Text)
{
    if (MenuButtons.IsValidIndex(ButtonIndex))
    {
        UButton* Button = MenuButtons[ButtonIndex];
        if (Button)
        {
            FWidgetTransform Transform;
            Transform.Scale = FVector2D(1.0f, 1.0f);
            Button->SetRenderTransform(Transform);
        }
    }
}

bool ULesFightMainMenuWidget::IsAnySubMenuOpen() const
{
    return bSubMenuOpen;
}
