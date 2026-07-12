#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightUIManager.generated.h"

class ULesFightWidgetManager;
class ULesFightScreenNavigationManager;
class ULesFightMenuStateManager;
class ULesFightInputNavigationManager;
class ULesFightNotificationManager;
class ULesFightPopupManager;
class ULesFightUIAnimationManager;

UCLASS(Blueprintable)
class ULesFightUIManager : public UObject
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
	void PushScreen(FName ScreenID);

	UFUNCTION(BlueprintCallable)
	void PopScreen();

	UFUNCTION(BlueprintCallable)
	void SwitchScreen(FName ScreenID);

	UFUNCTION(BlueprintCallable)
	const TArray<FUIScreenStackEntry>& GetScreenStack() const { return ScreenStack; }

	UFUNCTION(BlueprintCallable)
	const FUIScreenStackEntry* GetTopScreen() const;

	UFUNCTION(BlueprintCallable)
	int32 GetScreenCount() const { return ScreenStack.Num(); }

	UFUNCTION(BlueprintCallable)
	void NavigateBack();

	UFUNCTION(BlueprintCallable)
	bool CanNavigateBack() const { return ScreenStack.Num() > 1; }

	UFUNCTION(BlueprintCallable)
	void ShowNotification(const FNotificationDef& Notification);

	UFUNCTION(BlueprintCallable)
	void HideNotification();

	UFUNCTION(BlueprintCallable)
	void ShowPopup(const FPopupRequest& Request);

	UFUNCTION(BlueprintCallable)
	void ClosePopup();

	UFUNCTION(BlueprintCallable)
	void SetMenuState(EUIMenuState NewState);

	UFUNCTION(BlueprintCallable)
	EUIMenuState GetMenuState() const { return CurrentMenuState; }

	UFUNCTION(BlueprintCallable)
	void SetInputDevice(EInputDeviceType DeviceType);

	UFUNCTION(BlueprintCallable)
	EInputDeviceType GetInputDevice() const { return CurrentInputDevice; }

	UFUNCTION(BlueprintCallable)
	bool IsTransitioning() const;

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
	ULesFightUIAnimationManager* GetAnimationManager() const { return AnimationManager; }

protected:
	UPROPERTY()
	TObjectPtr<ULesFightWidgetManager> WidgetManager;

	UPROPERTY()
	TObjectPtr<ULesFightScreenNavigationManager> ScreenNavigationManager;

	UPROPERTY()
	TObjectPtr<ULesFightMenuStateManager> MenuStateManager;

	UPROPERTY()
	TObjectPtr<ULesFightInputNavigationManager> InputNavigationManager;

	UPROPERTY()
	TObjectPtr<ULesFightNotificationManager> NotificationManager;

	UPROPERTY()
	TObjectPtr<ULesFightPopupManager> PopupManager;

	UPROPERTY()
	TObjectPtr<ULesFightUIAnimationManager> AnimationManager;

	UPROPERTY()
	EUIMenuState CurrentMenuState = EUIMenuState::MainMenu;

	UPROPERTY()
	bool bInitialized = false;

	UPROPERTY()
	TArray<FUIScreenStackEntry> ScreenStack;

	UPROPERTY()
	EInputDeviceType CurrentInputDevice = EInputDeviceType::Keyboard;
};
