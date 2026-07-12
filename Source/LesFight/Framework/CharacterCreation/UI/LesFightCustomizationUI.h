#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCustomizationUI.generated.h"

UENUM(BlueprintType)
enum class ECustomizationScreen : uint8
{
    MainMenu,
    Biography,
    Face,
    Hair,
    Body,
    Skin,
    Clothing,
    Materials,
    Accessories,
    Voice,
    FightingStyle,
    Preview,
    PresetSelection,
    MAX
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScreenChanged, ECustomizationScreen, NewScreen);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUIEvent, const FString&, EventName);

UCLASS(Blueprintable)
class ULesFightCustomizationUI : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCustomizationUI();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void OpenScreen(ECustomizationScreen Screen);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void CloseScreen(ECustomizationScreen Screen);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void GoBack();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void ShowNotification(const FString& Message, float Duration = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void ShowConfirmationDialog(const FString& Title, const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void ShowLoadingScreen(const FString& LoadingMessage);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void HideLoadingScreen();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void SetUndoRedoEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void Undo();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void Redo();

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|UI")
    ECustomizationScreen GetCurrentScreen() const { return CurrentScreen; }

    UFUNCTION(BlueprintPure, Category = "CharacterCreator|UI")
    TArray<ECustomizationScreen> GetScreenHistory() const { return ScreenHistory; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void RefreshCurrentScreen();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void NavigateTo(ECustomizationScreen Screen);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void ResetNavigation();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void SetContextHelpEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|UI")
    void ShowContextHelp(const FString& ContextKey);

    UPROPERTY(BlueprintAssignable, Category = "CharacterCreator|UI")
    FOnScreenChanged OnScreenChanged;

    UPROPERTY(BlueprintAssignable, Category = "CharacterCreator|UI")
    FOnUIEvent OnUIEvent;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECustomizationScreen CurrentScreen;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<ECustomizationScreen> ScreenHistory;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<ECustomizationScreen> OpenScreens;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TMap<ECustomizationScreen, FString> ScreenTitles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    bool bContextHelpEnabled;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxHistorySize;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
    TMap<ECustomizationScreen, FString> ContextHelpTexts;
};
