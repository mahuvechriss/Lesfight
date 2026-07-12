#include "LesFightWidgetManager.h"

void ULesFightWidgetManager::Initialize()
{
	WidgetCache.Empty();
	WidgetPool.Empty();
	ActiveWidgets.Empty();
}

void ULesFightWidgetManager::Shutdown()
{
	ClearCache();

	for (auto& PoolEntry : WidgetPool)
	{
		for (UUserWidget* Widget : PoolEntry.Value)
		{
			if (Widget)
			{
				Widget->RemoveFromParent();
			}
		}
	}
	WidgetPool.Empty();

	for (UUserWidget* Widget : ActiveWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}
	ActiveWidgets.Empty();
}

UUserWidget* ULesFightWidgetManager::CreateWidget(FName ScreenID, TSubclassOf<UUserWidget> WidgetClass, UWorld* World)
{
	if (UUserWidget** Cached = WidgetCache.Find(ScreenID))
	{
		if (*Cached)
		{
			ActiveWidgets.Add(*Cached);
			return *Cached;
		}
	}

	if (bPoolingEnabled)
	{
		TArray<TObjectPtr<UUserWidget>>* Pool = WidgetPool.Find(ScreenID);
		if (Pool && Pool->Num() > 0)
		{
			UUserWidget* Widget = Pool->Pop();
			if (Widget)
			{
				ActiveWidgets.Add(Widget);
				return Widget;
			}
		}
	}

	if (!WidgetClass || !World)
	{
		return nullptr;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC)
	{
		return nullptr;
	}

	UUserWidget* Widget = CreateWidget<UUserWidget>(PC, WidgetClass);
	if (Widget)
	{
		WidgetCache.Add(ScreenID, Widget);
		ActiveWidgets.Add(Widget);
	}

	return Widget;
}

void ULesFightWidgetManager::RemoveWidget(FName ScreenID)
{
	if (UUserWidget** Widget = WidgetCache.Find(ScreenID))
	{
		if (*Widget)
		{
			(*Widget)->RemoveFromParent();

			if (bPoolingEnabled)
			{
				TArray<TObjectPtr<UUserWidget>>& Pool = WidgetPool.FindOrAdd(ScreenID);
				if (Pool.Num() < PoolSize)
				{
					Pool.Add(*Widget);
				}
			}

			ActiveWidgets.Remove(*Widget);
		}
		WidgetCache.Remove(ScreenID);
	}
}

UUserWidget* ULesFightWidgetManager::GetWidget(FName ScreenID) const
{
	const TObjectPtr<UUserWidget>* Widget = WidgetCache.Find(ScreenID);
	return Widget ? Widget->Get() : nullptr;
}

TArray<UUserWidget*> ULesFightWidgetManager::GetAllWidgets() const
{
	TArray<UUserWidget*> Result;
	for (const auto& Pair : WidgetCache)
	{
		if (Pair.Value)
		{
			Result.Add(Pair.Value);
		}
	}
	return Result;
}

void ULesFightWidgetManager::CacheWidget(FName ScreenID, UUserWidget* Widget)
{
	if (Widget)
	{
		WidgetCache.Add(ScreenID, Widget);
	}
}

void ULesFightWidgetManager::ClearCache()
{
	for (auto& Pair : WidgetCache)
	{
		if (Pair.Value)
		{
			Pair.Value->RemoveFromParent();
		}
	}
	WidgetCache.Empty();
	ActiveWidgets.Empty();
}
