#include "LesFightUIManager.h"
#include "LesFightWidgetManager.h"
#include "LesFightScreenNavigationManager.h"
#include "LesFightMenuStateManager.h"
#include "LesFightInputNavigationManager.h"
#include "LesFightNotificationManager.h"
#include "LesFightPopupManager.h"
#include "LesFightUIAnimationManager.h"

void ULesFightUIManager::Initialize()
{
	if (bInitialized)
	{
		return;
	}

	WidgetManager = NewObject<ULesFightWidgetManager>(this);
	WidgetManager->Initialize();

	ScreenNavigationManager = NewObject<ULesFightScreenNavigationManager>(this);
	ScreenNavigationManager->Initialize();

	MenuStateManager = NewObject<ULesFightMenuStateManager>(this);
	MenuStateManager->Initialize();

	InputNavigationManager = NewObject<ULesFightInputNavigationManager>(this);
	InputNavigationManager->Initialize();

	NotificationManager = NewObject<ULesFightNotificationManager>(this);
	NotificationManager->Initialize();

	PopupManager = NewObject<ULesFightPopupManager>(this);
	PopupManager->Initialize();

	AnimationManager = NewObject<ULesFightUIAnimationManager>(this);
	AnimationManager->Initialize();

	bInitialized = true;
}

void ULesFightUIManager::Shutdown()
{
	if (!bInitialized)
	{
		return;
	}

	while (ScreenStack.Num() > 0)
	{
		FUIScreenStackEntry& Entry = ScreenStack.Last();
		if (Entry.Widget)
		{
			Entry.Widget->RemoveFromParent();
		}
		ScreenStack.Pop();
	}

	if (WidgetManager)
	{
		WidgetManager->Shutdown();
		WidgetManager = nullptr;
	}

	if (ScreenNavigationManager)
	{
		ScreenNavigationManager->Shutdown();
		ScreenNavigationManager = nullptr;
	}

	if (MenuStateManager)
	{
		MenuStateManager->Shutdown();
		MenuStateManager = nullptr;
	}

	if (InputNavigationManager)
	{
		InputNavigationManager->Shutdown();
		InputNavigationManager = nullptr;
	}

	if (NotificationManager)
	{
		NotificationManager->Shutdown();
		NotificationManager = nullptr;
	}

	if (PopupManager)
	{
		PopupManager->Shutdown();
		PopupManager = nullptr;
	}

	if (AnimationManager)
	{
		AnimationManager->Shutdown();
		AnimationManager = nullptr;
	}

	bInitialized = false;
}

void ULesFightUIManager::Tick(float DeltaTime)
{
	if (!bInitialized)
	{
		return;
	}

	if (AnimationManager)
	{
		AnimationManager->Tick(DeltaTime);
	}

	if (NotificationManager)
	{
		NotificationManager->Tick(DeltaTime);
	}
}

void ULesFightUIManager::PushScreen(FName ScreenID)
{
	if (!WidgetManager)
	{
		return;
	}

	if (ScreenStack.Num() >= 20)
	{
		return;
	}

	UUserWidget* Widget = WidgetManager->CreateWidget(ScreenID, nullptr, nullptr);
	if (!Widget)
	{
		return;
	}

	Widget->AddToViewport();

	FUIScreenStackEntry Entry;
	Entry.ScreenID = ScreenID;
	Entry.Widget = Widget;
	Entry.Layer = EWidgetLayer::Medium;

	ScreenStack.Push(Entry);

	if (ScreenNavigationManager)
	{
		ScreenNavigationManager->NavigateTo(ScreenID, EScreenTransitionType::Fade, 0.5f);
	}
}

void ULesFightUIManager::PopScreen()
{
	if (ScreenStack.Num() == 0)
	{
		return;
	}

	FUIScreenStackEntry& Entry = ScreenStack.Last();
	if (Entry.Widget)
	{
		Entry.Widget->RemoveFromParent();
		WidgetManager->RemoveWidget(Entry.ScreenID);
	}

	ScreenStack.Pop();
}

void ULesFightUIManager::SwitchScreen(FName ScreenID)
{
	while (ScreenStack.Num() > 0)
	{
		FUIScreenStackEntry& Entry = ScreenStack.Last();
		if (Entry.Widget)
		{
			Entry.Widget->RemoveFromParent();
		}
		ScreenStack.Pop();
	}

	PushScreen(ScreenID);
}

void ULesFightUIManager::NavigateBack()
{
	if (CanNavigateBack())
	{
		PopScreen();
	}
}

void ULesFightUIManager::ShowNotification(const FNotificationDef& Notification)
{
	if (NotificationManager)
	{
		NotificationManager->ShowNotification(Notification);
	}
}

void ULesFightUIManager::HideNotification()
{
	if (NotificationManager)
	{
		NotificationManager->HideCurrentNotification();
	}
}

void ULesFightUIManager::ShowPopup(const FPopupRequest& Request)
{
	if (PopupManager)
	{
		PopupManager->ShowPopup(Request);
	}
}

void ULesFightUIManager::ClosePopup()
{
	if (PopupManager)
	{
		PopupManager->CloseCurrentPopup();
	}
}

void ULesFightUIManager::SetMenuState(EUIMenuState NewState)
{
	if (MenuStateManager)
	{
		MenuStateManager->SetState(NewState);
		CurrentMenuState = NewState;
	}
}

void ULesFightUIManager::SetInputDevice(EInputDeviceType DeviceType)
{
	CurrentInputDevice = DeviceType;
	if (InputNavigationManager)
	{
		InputNavigationManager->SetInputDevice(DeviceType);
	}
}

bool ULesFightUIManager::IsTransitioning() const
{
	if (ScreenNavigationManager)
	{
		return ScreenNavigationManager->IsNavigationInProgress();
	}
	return false;
}

const FUIScreenStackEntry* ULesFightUIManager::GetTopScreen() const
{
	if (ScreenStack.Num() == 0)
	{
		return nullptr;
	}
	return &ScreenStack.Last();
}
