#include "LesFightScreenNavigationManager.h"

void ULesFightScreenNavigationManager::Initialize()
{
	NavigationHistory.Empty();
	PreviousScreen = NAME_None;
	CurrentScreen = NAME_None;
	bNavigationInProgress = false;
}

void ULesFightScreenNavigationManager::Shutdown()
{
	NavigationHistory.Empty();
	PreviousScreen = NAME_None;
	CurrentScreen = NAME_None;
	bNavigationInProgress = false;
}

void ULesFightScreenNavigationManager::NavigateTo(FName ScreenID, EScreenTransitionType TransitionType, float Duration)
{
	if (CurrentScreen != NAME_None)
	{
		if (NavigationHistory.Num() >= 20)
		{
			NavigationHistory.RemoveAt(0);
		}
		NavigationHistory.Push(CurrentScreen);
	}

	PreviousScreen = CurrentScreen;
	CurrentScreen = ScreenID;
	CurrentTransition = TransitionType;
	TransitionDuration = Duration;
	bNavigationInProgress = true;

	OnScreenChanged.Broadcast(PreviousScreen, CurrentScreen);
}

void ULesFightScreenNavigationManager::GoBack()
{
	if (NavigationHistory.Num() > 0)
	{
		PreviousScreen = CurrentScreen;
		CurrentScreen = NavigationHistory.Pop();
		bNavigationInProgress = true;

		OnScreenChanged.Broadcast(PreviousScreen, CurrentScreen);
	}
}

void ULesFightScreenNavigationManager::ClearHistory()
{
	NavigationHistory.Empty();
}

void ULesFightScreenNavigationManager::SetTransition(EScreenTransitionType Type, float Duration)
{
	CurrentTransition = Type;
	TransitionDuration = Duration;
}
