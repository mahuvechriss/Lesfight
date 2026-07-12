#include "LesFightCustomizationUI.h"
#include "LesFightCharCreationManager.h"

ULesFightCustomizationUI::ULesFightCustomizationUI()
    : CurrentScreen(ECustomizationScreen::MainMenu)
    , bContextHelpEnabled(true)
    , MaxHistorySize(20)
{
    ScreenTitles = {
        {ECustomizationScreen::MainMenu, TEXT("Character Creation")},
        {ECustomizationScreen::Biography, TEXT("Biography")},
        {ECustomizationScreen::Face, TEXT("Face Customization")},
        {ECustomizationScreen::Hair, TEXT("Hair Style")},
        {ECustomizationScreen::Body, TEXT("Body Customization")},
        {ECustomizationScreen::Skin, TEXT("Skin & Tattoos")},
        {ECustomizationScreen::Clothing, TEXT("Clothing")},
        {ECustomizationScreen::Materials, TEXT("Material Editor")},
        {ECustomizationScreen::Accessories, TEXT("Accessories")},
        {ECustomizationScreen::Voice, TEXT("Voice Selection")},
        {ECustomizationScreen::FightingStyle, TEXT("Fighting Style")},
        {ECustomizationScreen::Preview, TEXT("Character Preview")},
        {ECustomizationScreen::PresetSelection, TEXT("Presets")},
    };
}

void ULesFightCustomizationUI::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightCustomizationUI::OpenScreen(ECustomizationScreen Screen)
{
    if (Screen == ECustomizationScreen::MAX) return;

    if (CurrentScreen != Screen && CurrentScreen != ECustomizationScreen::MAX)
    {
        ScreenHistory.Push(CurrentScreen);
        if (ScreenHistory.Num() > MaxHistorySize)
        {
            ScreenHistory.RemoveAt(0);
        }
    }

    CurrentScreen = Screen;
    if (!OpenScreens.Contains(Screen))
    {
        OpenScreens.Add(Screen);
    }
    OnScreenChanged.Broadcast(Screen);
    OnUIEvent.Broadcast(TEXT("ScreenOpened:") + ScreenTitles.FindRef(Screen));
}

void ULesFightCustomizationUI::CloseScreen(ECustomizationScreen Screen)
{
    OpenScreens.Remove(Screen);
    if (CurrentScreen == Screen)
    {
        GoBack();
    }
}

void ULesFightCustomizationUI::GoBack()
{
    if (ScreenHistory.Num() > 0)
    {
        ECustomizationScreen PreviousScreen = ScreenHistory.Pop();
        CurrentScreen = PreviousScreen;
        OnScreenChanged.Broadcast(PreviousScreen);
    }
    else
    {
        OpenScreen(ECustomizationScreen::MainMenu);
    }
}

void ULesFightCustomizationUI::ShowNotification(const FString& Message, float Duration)
{
    OnUIEvent.Broadcast(TEXT("Notification:") + Message);
}

void ULesFightCustomizationUI::ShowConfirmationDialog(
    const FString& Title, const FString& Message)
{
    OnUIEvent.Broadcast(TEXT("Confirmation:") + Title + TEXT("|") + Message);
}

void ULesFightCustomizationUI::ShowLoadingScreen(const FString& LoadingMessage)
{
    OnUIEvent.Broadcast(TEXT("Loading:") + LoadingMessage);
}

void ULesFightCustomizationUI::HideLoadingScreen()
{
    OnUIEvent.Broadcast(TEXT("LoadingEnd"));
}

void ULesFightCustomizationUI::SetUndoRedoEnabled(bool bEnabled)
{
}

void ULesFightCustomizationUI::Undo()
{
    if (ScreenHistory.Num() > 0)
    {
        GoBack();
    }
}

void ULesFightCustomizationUI::Redo()
{
}

void ULesFightCustomizationUI::RefreshCurrentScreen()
{
    OnScreenChanged.Broadcast(CurrentScreen);
}

void ULesFightCustomizationUI::NavigateTo(ECustomizationScreen Screen)
{
    OpenScreen(Screen);
}

void ULesFightCustomizationUI::ResetNavigation()
{
    ScreenHistory.Empty();
    OpenScreens.Empty();
    CurrentScreen = ECustomizationScreen::MainMenu;
}

void ULesFightCustomizationUI::SetContextHelpEnabled(bool bEnabled)
{
    bContextHelpEnabled = bEnabled;
}

void ULesFightCustomizationUI::ShowContextHelp(const FString& ContextKey)
{
    OnUIEvent.Broadcast(TEXT("ContextHelp:") + ContextKey);
}
