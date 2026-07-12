#include "LesFightUIAnimationManager.h"

void ULesFightUIAnimationManager::Initialize()
{
	AnimationDefinitions.Empty();
	ActiveAnimations.Empty();
	AnimationTimers.Empty();
}

void ULesFightUIAnimationManager::Shutdown()
{
	ActiveAnimations.Empty();
	AnimationTimers.Empty();
	AnimationDefinitions.Empty();
}

void ULesFightUIAnimationManager::PlayAnimation(FName AnimationID, UUserWidget* TargetWidget)
{
	if (!TargetWidget)
	{
		return;
	}

	const FUIAnimationDef* Def = AnimationDefinitions.Find(AnimationID);
	if (!Def)
	{
		return;
	}

	float AdjustedDuration = Def->Duration / GlobalSpeedMultiplier;

	AnimationTimers.Add(AnimationID, AdjustedDuration);

	TArray<FName>& WidgetAnims = ActiveAnimations.FindOrAdd(TargetWidget);
	WidgetAnims.Add(AnimationID);

	OnAnimationStarted.Broadcast(AnimationID, TargetWidget);
}

void ULesFightUIAnimationManager::StopAnimation(FName AnimationID, UUserWidget* TargetWidget)
{
	if (!TargetWidget)
	{
		return;
	}

	AnimationTimers.Remove(AnimationID);

	TArray<FName>* WidgetAnims = ActiveAnimations.Find(TargetWidget);
	if (WidgetAnims)
	{
		WidgetAnims->Remove(AnimationID);
		if (WidgetAnims->Num() == 0)
		{
			ActiveAnimations.Remove(TargetWidget);
		}
	}
}

void ULesFightUIAnimationManager::StopAllAnimations(UUserWidget* TargetWidget)
{
	if (!TargetWidget)
	{
		return;
	}

	TArray<FName>* WidgetAnims = ActiveAnimations.Find(TargetWidget);
	if (WidgetAnims)
	{
		for (const FName& AnimID : *WidgetAnims)
		{
			AnimationTimers.Remove(AnimID);
			OnAnimationCompleted.Broadcast(AnimID, TargetWidget);
		}
		ActiveAnimations.Remove(TargetWidget);
	}
}

bool ULesFightUIAnimationManager::IsAnimating(UUserWidget* TargetWidget) const
{
	if (!TargetWidget)
	{
		return false;
	}

	const TArray<FName>* WidgetAnims = ActiveAnimations.Find(TargetWidget);
	return WidgetAnims && WidgetAnims->Num() > 0;
}

void ULesFightUIAnimationManager::RegisterAnimation(FName AnimationID, const FUIAnimationDef& Definition)
{
	AnimationDefinitions.Add(AnimationID, Definition);
}

void ULesFightUIAnimationManager::UnregisterAnimation(FName AnimationID)
{
	AnimationDefinitions.Remove(AnimationID);
	AnimationTimers.Remove(AnimationID);

	for (auto& Pair : ActiveAnimations)
	{
		Pair.Value.Remove(AnimationID);
	}
}

const FUIAnimationDef* ULesFightUIAnimationManager::GetAnimationDef(FName AnimationID) const
{
	return AnimationDefinitions.Find(AnimationID);
}

void ULesFightUIAnimationManager::Tick(float DeltaTime)
{
	if (ActiveAnimations.Num() == 0)
	{
		return;
	}

	float AdjustedDelta = DeltaTime * GlobalSpeedMultiplier;

	TArray<FName> CompletedAnimations;

	for (auto& TimerPair : AnimationTimers)
	{
		TimerPair.Value -= AdjustedDelta;
		if (TimerPair.Value <= 0.0f)
		{
			CompletedAnimations.Add(TimerPair.Key);
		}
	}

	for (const FName& AnimID : CompletedAnimations)
	{
		AnimationTimers.Remove(AnimID);

		for (auto& AnimPair : ActiveAnimations)
		{
			UUserWidget* Widget = AnimPair.Key;
			TArray<FName>& Anims = AnimPair.Value;
			if (Anims.Contains(AnimID))
			{
				Anims.Remove(AnimID);
				OnAnimationCompleted.Broadcast(AnimID, Widget);
			}
		}
	}

	TArray<TObjectPtr<UUserWidget>> WidgetsToRemove;
	for (auto& AnimPair : ActiveAnimations)
	{
		if (AnimPair.Value.Num() == 0)
		{
			WidgetsToRemove.Add(AnimPair.Key);
		}
	}

	for (const TObjectPtr<UUserWidget>& Widget : WidgetsToRemove)
	{
		ActiveAnimations.Remove(Widget);
	}
}
