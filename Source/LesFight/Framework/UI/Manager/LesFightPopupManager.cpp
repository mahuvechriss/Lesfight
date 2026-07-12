#include "LesFightPopupManager.h"

void ULesFightPopupManager::Initialize()
{
	PopupQueue.Empty();
	CurrentPopup.Reset();
	bPopupActive = false;
}

void ULesFightPopupManager::Shutdown()
{
	PopupQueue.Empty();
	CurrentPopup.Reset();
	bPopupActive = false;
}

void ULesFightPopupManager::ShowPopup(const FPopupRequest& Request)
{
	if (bPopupActive)
	{
		if (bQueueEnabled && PopupQueue.Num() < MaxQueueSize)
		{
			PopupQueue.Add(Request);
		}
		return;
	}

	CurrentPopup = Request;
	bPopupActive = true;

	OnPopupShown.Broadcast(Request);
}

void ULesFightPopupManager::CloseCurrentPopup()
{
	if (!bPopupActive || !CurrentPopup.IsSet())
	{
		return;
	}

	FPopupRequest ClosedPopup = CurrentPopup.GetValue();
	CurrentPopup.Reset();
	bPopupActive = false;

	OnPopupHidden.Broadcast(ClosedPopup);

	if (bQueueEnabled && PopupQueue.Num() > 0)
	{
		FPopupRequest NextPopup = PopupQueue[0];
		PopupQueue.RemoveAt(0);
		ShowPopup(NextPopup);
	}
}

const FPopupRequest* ULesFightPopupManager::GetCurrentPopup() const
{
	return CurrentPopup.IsSet() ? &CurrentPopup.GetValue() : nullptr;
}
