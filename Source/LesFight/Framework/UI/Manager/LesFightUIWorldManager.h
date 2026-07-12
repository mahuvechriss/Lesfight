#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightUIWorldManager.generated.h"

class ULesFightUIManager;
class ULesFightWidgetManager;
class ULesFightScreenNavigationManager;
class ULesFightMenuStateManager;
class ULesFightInputNavigationManager;
class ULesFightNotificationManager;
class ULesFightPopupManager;
class ULesFightUIAnimationManager;
class ULesFightPlayerProfileManager;
class ULesFightAccessibilityManager;
class ULesFightUIDevTools;
class ULesFightUIAnimationSystem;

UCLASS(Blueprintable, BlueprintType)
class LESFIGHT_API ULesFightUIWorldManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void Shutdown();

    UFUNCTION(BlueprintCallable)
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable)
    ULesFightUIManager* GetUIManager() const { return UIManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightWidgetManager* GetWidgetManager() const { return WidgetManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightScreenNavigationManager* GetScreenNavigationManager() const { return ScreenNavigationManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightMenuStateManager* GetMenuStateManager() const { return MenuStateManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightInputNavigationManager* GetInputNavigationManager() const { return InputNavigationManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightNotificationManager* GetNotificationManager() const { return NotificationManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightPopupManager* GetPopupManager() const { return PopupManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightUIAnimationManager* GetUIAnimationManager() const { return UIAnimationManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightPlayerProfileManager* GetPlayerProfileManager() const { return PlayerProfileManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightAccessibilityManager* GetAccessibilityManager() const { return AccessibilityManager; }

    UFUNCTION(BlueprintCallable)
    ULesFightUIDevTools* GetUIDevTools() const { return UIDevTools; }

    UFUNCTION(BlueprintCallable)
    ULesFightUIAnimationSystem* GetUIAnimationSystem() const { return UIAnimationSystem; }

    UFUNCTION(BlueprintCallable)
    UUserWidget* GetMainMenuWidget() const;

    UFUNCTION(BlueprintCallable)
    UUserWidget* GetCharacterSelectWidget() const;

    UFUNCTION(BlueprintCallable)
    UUserWidget* GetCombatHUD() const;

    UFUNCTION(BlueprintCallable)
    UUserWidget* GetPauseMenuWidget() const;

    UFUNCTION(BlueprintCallable)
    UUserWidget* GetMatchResultWidget() const;

    UFUNCTION(BlueprintCallable)
    UUserWidget* GetSettingsWidget() const;

protected:
    void CreateAndInitializeSubsystems();

    UPROPERTY()
    ULesFightUIManager* UIManager = nullptr;

    UPROPERTY()
    ULesFightWidgetManager* WidgetManager = nullptr;

    UPROPERTY()
    ULesFightScreenNavigationManager* ScreenNavigationManager = nullptr;

    UPROPERTY()
    ULesFightMenuStateManager* MenuStateManager = nullptr;

    UPROPERTY()
    ULesFightInputNavigationManager* InputNavigationManager = nullptr;

    UPROPERTY()
    ULesFightNotificationManager* NotificationManager = nullptr;

    UPROPERTY()
    ULesFightPopupManager* PopupManager = nullptr;

    UPROPERTY()
    ULesFightUIAnimationManager* UIAnimationManager = nullptr;

    UPROPERTY()
    ULesFightPlayerProfileManager* PlayerProfileManager = nullptr;

    UPROPERTY()
    ULesFightAccessibilityManager* AccessibilityManager = nullptr;

    UPROPERTY()
    ULesFightUIDevTools* UIDevTools = nullptr;

    UPROPERTY()
    ULesFightUIAnimationSystem* UIAnimationSystem = nullptr;

    UPROPERTY()
    bool bInitialized = false;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightUIManager> UIManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightWidgetManager> WidgetManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightScreenNavigationManager> ScreenNavigationManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightMenuStateManager> MenuStateManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightInputNavigationManager> InputNavigationManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightNotificationManager> NotificationManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightPopupManager> PopupManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightUIAnimationManager> UIAnimationManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightPlayerProfileManager> PlayerProfileManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightAccessibilityManager> AccessibilityManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightUIDevTools> UIDevToolsClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightUIAnimationSystem> UIAnimationSystemClass;

private:
    template<typename T>
    T* CreateSubsystem(TSubclassOf<T> Class, UObject* Outer)
    {
        if (!Class)
        {
            return nullptr;
        }
        return NewObject<T>(Outer, Class);
    }
};
