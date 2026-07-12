#include "LesFightNotificationManager.h"

void ULesFightNotificationManager::Initialize()
{
	CurrentNotification.Reset();
	NotificationQueue.Empty();
	Timer = 0.0f;
}

void ULesFightNotificationManager::Shutdown()
{
	CurrentNotification.Reset();
	NotificationQueue.Empty();
	Timer = 0.0f;
}

void ULesFightNotificationManager::ShowNotification(const FNotificationDef& Notification)
{
	if (CurrentNotification.IsSet())
	{
		QueueNotification(Notification);
		return;
	}

	CurrentNotification = Notification;
	Timer = Notification.Duration > 0.0f ? Notification.Duration : DefaultDuration;

	OnNotificationShown.Broadcast(Notification);
}

void ULesFightNotificationManager::QueueNotification(const FNotificationDef& Notification)
{
	if (NotificationQueue.Num() < 10)
	{
		NotificationQueue.Add(Notification);
	}
}

void ULesFightNotificationManager::HideCurrentNotification()
{
	if (CurrentNotification.IsSet())
	{
		FNotificationDef HiddenNotification = CurrentNotification.GetValue();
		CurrentNotification.Reset();
		Timer = 0.0f;

		OnNotificationHidden.Broadcast(HiddenNotification);

		if (NotificationQueue.Num() > 0)
		{
			FNotificationDef NextNotification = NotificationQueue[0];
			NotificationQueue.RemoveAt(0);
			ShowNotification(NextNotification);
		}
	}
}

void ULesFightNotificationManager::ClearQueue()
{
	NotificationQueue.Empty();
}

void ULesFightNotificationManager::Tick(float DeltaTime)
{
	if (!CurrentNotification.IsSet())
	{
		return;
	}

	Timer -= DeltaTime;
	if (Timer <= 0.0f)
	{
		HideCurrentNotification();
	}
}
