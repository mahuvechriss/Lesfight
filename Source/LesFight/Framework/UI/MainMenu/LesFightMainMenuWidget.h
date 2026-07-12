#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightMainMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMultiplayerClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterCreatorClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProfileClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCreditsClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitClicked);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightMainMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void SetBackgroundScene(class UTextureRenderTarget2D* Scene);

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void PlayTitleAnimation();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void PlayMenuEntranceAnimation();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void PlayButtonHighlight(int32 ButtonIndex);

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void NavigateToPlay();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void NavigateToMultiplayer();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void NavigateToCharacterCreator();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void NavigateToProfile();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void NavigateToSettings();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void NavigateToCredits();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void QuitGame();

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void SetMenuButtonEnabled(int32 ButtonIndex, bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    void SetMenuButtonText(int32 ButtonIndex, FText Text);

    UFUNCTION(BlueprintCallable, Category = "MainMenu")
    bool IsAnySubMenuOpen() const;

    UPROPERTY(BlueprintAssignable, Category = "MainMenu")
    FOnPlayClicked OnPlayClicked;

    UPROPERTY(BlueprintAssignable, Category = "MainMenu")
    FOnMultiplayerClicked OnMultiplayerClicked;

    UPROPERTY(BlueprintAssignable, Category = "MainMenu")
    FOnCharacterCreatorClicked OnCharacterCreatorClicked;

    UPROPERTY(BlueprintAssignable, Category = "MainMenu")
    FOnProfileClicked OnProfileClicked;

    UPROPERTY(BlueprintAssignable, Category = "MainMenu")
    FOnSettingsClicked OnSettingsClicked;

    UPROPERTY(BlueprintAssignable, Category = "MainMenu")
    FOnCreditsClicked OnCreditsClicked;

    UPROPERTY(BlueprintAssignable, Category = "MainMenu")
    FOnExitClicked OnExitClicked;

protected:
    UPROPERTY(meta = (BindWidget))
    class UWidget* MainMenuCanvas;

    UPROPERTY(meta = (BindWidget))
    class UWidget* TitleText;

    UPROPERTY(meta = (BindWidget))
    class UWidget* BackgroundImage;

    UPROPERTY(meta = (BindWidget))
    TArray<class UButton*> MenuButtons;

    UPROPERTY()
    int32 HighlightedIndex = -1;

    UPROPERTY()
    bool bSubMenuOpen = false;
};
