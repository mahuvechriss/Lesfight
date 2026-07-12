#include "LesFightUIWorldManager.h"

void ULesFightUIWorldManager::Initialize()
{
    if (bInitialized)
    {
        return;
    }

    CreateAndInitializeSubsystems();

    bInitialized = true;
}

void ULesFightUIWorldManager::CreateAndInitializeSubsystems()
{
    UObject* Outer = this;

    UIManager = CreateSubsystem(UIManagerClass, Outer);
    WidgetManager = CreateSubsystem(WidgetManagerClass, Outer);
    ScreenNavigationManager = CreateSubsystem(ScreenNavigationManagerClass, Outer);
    MenuStateManager = CreateSubsystem(MenuStateManagerClass, Outer);
    InputNavigationManager = CreateSubsystem(InputNavigationManagerClass, Outer);
    NotificationManager = CreateSubsystem(NotificationManagerClass, Outer);
    PopupManager = CreateSubsystem(PopupManagerClass, Outer);
    UIAnimationManager = CreateSubsystem(UIAnimationManagerClass, Outer);
    PlayerProfileManager = CreateSubsystem(PlayerProfileManagerClass, Outer);
    AccessibilityManager = CreateSubsystem(AccessibilityManagerClass, Outer);
    UIDevTools = CreateSubsystem(UIDevToolsClass, Outer);
    UIAnimationSystem = CreateSubsystem(UIAnimationSystemClass, Outer);

    if (UIManager) UIManager->Initialize();
    if (WidgetManager) WidgetManager->Initialize();
    if (ScreenNavigationManager) ScreenNavigationManager->Initialize();
    if (MenuStateManager) MenuStateManager->Initialize();
    if (InputNavigationManager) InputNavigationManager->Initialize();
    if (NotificationManager) NotificationManager->Initialize();
    if (PopupManager) PopupManager->Initialize();
    if (UIAnimationManager) UIAnimationManager->Initialize();
    if (PlayerProfileManager) PlayerProfileManager->Initialize();
    if (AccessibilityManager) AccessibilityManager->Initialize();
    if (UIDevTools) UIDevTools->Initialize();
    if (UIAnimationSystem) UIAnimationSystem->Initialize();
}

void ULesFightUIWorldManager::Shutdown()
{
    if (!bInitialized)
    {
        return;
    }

    if (UIAnimationSystem) UIAnimationSystem->Shutdown();
    if (UIDevTools) UIDevTools->Shutdown();
    if (AccessibilityManager) AccessibilityManager->Shutdown();
    if (PlayerProfileManager) PlayerProfileManager->Shutdown();
    if (UIAnimationManager) UIAnimationManager->Shutdown();
    if (PopupManager) PopupManager->Shutdown();
    if (NotificationManager) NotificationManager->Shutdown();
    if (InputNavigationManager) InputNavigationManager->Shutdown();
    if (MenuStateManager) MenuStateManager->Shutdown();
    if (ScreenNavigationManager) ScreenNavigationManager->Shutdown();
    if (WidgetManager) WidgetManager->Shutdown();
    if (UIManager) UIManager->Shutdown();

    UIManager = nullptr;
    WidgetManager = nullptr;
    ScreenNavigationManager = nullptr;
    MenuStateManager = nullptr;
    InputNavigationManager = nullptr;
    NotificationManager = nullptr;
    PopupManager = nullptr;
    UIAnimationManager = nullptr;
    PlayerProfileManager = nullptr;
    AccessibilityManager = nullptr;
    UIDevTools = nullptr;
    UIAnimationSystem = nullptr;

    bInitialized = false;
}

void ULesFightUIWorldManager::Tick(float DeltaTime)
{
    if (!bInitialized)
    {
        return;
    }

    if (UIAnimationManager)
    {
        UIAnimationManager->Tick(DeltaTime);
    }

    if (UIAnimationSystem)
    {
        UIAnimationSystem->Tick(DeltaTime);
    }

    if (NotificationManager)
    {
        NotificationManager->Tick(DeltaTime);
    }
}

UUserWidget* ULesFightUIWorldManager::GetMainMenuWidget() const
{
    return nullptr;
}

UUserWidget* ULesFightUIWorldManager::GetCharacterSelectWidget() const
{
    return nullptr;
}

UUserWidget* ULesFightUIWorldManager::GetCombatHUD() const
{
    return nullptr;
}

UUserWidget* ULesFightUIWorldManager::GetPauseMenuWidget() const
{
    return nullptr;
}

UUserWidget* ULesFightUIWorldManager::GetMatchResultWidget() const
{
    return nullptr;
}

UUserWidget* ULesFightUIWorldManager::GetSettingsWidget() const
{
    return nullptr;
}
