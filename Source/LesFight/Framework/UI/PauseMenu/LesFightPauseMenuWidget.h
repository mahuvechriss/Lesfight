#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LesFightPauseMenuWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnResumeGame)
DECLARE_MULTICAST_DELEGATE(FOnRestartMatch)
DECLARE_MULTICAST_DELEGATE(FOnOpenSettings)
DECLARE_MULTICAST_DELEGATE(FOnOpenControls)
DECLARE_MULTICAST_DELEGATE(FOnOpenAudio)
DECLARE_MULTICAST_DELEGATE(FOnOpenGraphics)
DECLARE_MULTICAST_DELEGATE(FOnOpenAccessibility)
DECLARE_MULTICAST_DELEGATE(FOnQuitMatch)
DECLARE_MULTICAST_DELEGATE(FOnQuitToMainMenu)

USTRUCT(BlueprintType)
struct FMenuItem
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Menu")
    FText Label;

    UPROPERTY(BlueprintReadOnly, Category = "Menu")
    bool bEnabled = true;
};

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPauseMenuWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void ResumeGame();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void RestartMatch();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void OpenSettings();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void OpenControls();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void OpenAudioOptions();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void OpenGraphicsOptions();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void OpenAccessibility();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void QuitMatch();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void QuitToMainMenu();

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void SetPauseMenuTitle(FText Title);

    UFUNCTION(BlueprintCallable, Category = "PauseMenu")
    void SetMenuItemsEnabled(TArray<bool> EnabledStates);

    FOnResumeGame OnResumeGame;
    FOnRestartMatch OnRestartMatch;
    FOnOpenSettings OnOpenSettings;
    FOnOpenControls OnOpenControls;
    FOnOpenAudio OnOpenAudio;
    FOnOpenGraphics OnOpenGraphics;
    FOnOpenAccessibility OnOpenAccessibility;
    FOnQuitMatch OnQuitMatch;
    FOnQuitToMainMenu OnQuitToMainMenu;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "PauseMenu")
    TArray<FMenuItem> MenuItems;
};
