#include "Framework/QA/Core/LesFightReleaseValidator.h"

void ULesFightReleaseValidator::Initialize()
{
	BuildDefaultChecklist();
}

void ULesFightReleaseValidator::Shutdown()
{
	Checklist.Empty();
}

void ULesFightReleaseValidator::BuildDefaultChecklist()
{
	Checklist.Empty();

	auto AddItem = [this](const FString& Name, EReleaseChecklistItem Priority)
	{
		FQAReleaseChecklistItem Item;
		Item.Item = Name;
		Item.Priority = Priority;
		Item.bCompleted = false;
		Checklist.Add(Item);
	};

	AddItem(TEXT("Game launches without crash"), EReleaseChecklistItem::Critical);
	AddItem(TEXT("No critical bugs remain"), EReleaseChecklistItem::Critical);
	AddItem(TEXT("Complete game flow works"), EReleaseChecklistItem::Critical);
	AddItem(TEXT("Characters work correctly"), EReleaseChecklistItem::Critical);
	AddItem(TEXT("Combat is stable"), EReleaseChecklistItem::Critical);
	AddItem(TEXT("AI works correctly"), EReleaseChecklistItem::Required);
	AddItem(TEXT("LAN multiplayer works"), EReleaseChecklistItem::Required);
	AddItem(TEXT("Save/load system works"), EReleaseChecklistItem::Required);
	AddItem(TEXT("Performance targets met (60 FPS)"), EReleaseChecklistItem::Required);
	AddItem(TEXT("Audio plays correctly"), EReleaseChecklistItem::Required);
	AddItem(TEXT("UI functions correctly"), EReleaseChecklistItem::Required);
	AddItem(TEXT("All animations play correctly"), EReleaseChecklistItem::Recommended);
	AddItem(TEXT("VFX display correctly"), EReleaseChecklistItem::Recommended);
	AddItem(TEXT("Controller support works"), EReleaseChecklistItem::Recommended);
	AddItem(TEXT("Keyboard/mouse support works"), EReleaseChecklistItem::Recommended);
	AddItem(TEXT("Character creator works"), EReleaseChecklistItem::Recommended);
	AddItem(TEXT("Settings persist across sessions"), EReleaseChecklistItem::Recommended);
	AddItem(TEXT("All achievements unlockable"), EReleaseChecklistItem::Optional);
	AddItem(TEXT("Photo-to-character AI works"), EReleaseChecklistItem::Optional);
	AddItem(TEXT("Multiple resolutions supported"), EReleaseChecklistItem::Optional);
}

TArray<FQAReleaseChecklistItem> ULesFightReleaseValidator::GetChecklist() const
{
	return Checklist;
}

bool ULesFightReleaseValidator::SetItemCompleted(const FString& ItemName, bool bCompleted)
{
	for (FQAReleaseChecklistItem& Item : Checklist)
	{
		if (Item.Item == ItemName)
		{
			Item.bCompleted = bCompleted;
			return true;
		}
	}
	return false;
}

bool ULesFightReleaseValidator::IsReadyForRelease() const
{
	for (const FQAReleaseChecklistItem& Item : Checklist)
	{
		if (Item.Priority == EReleaseChecklistItem::Critical && !Item.bCompleted)
		{
			return false;
		}
		if (Item.Priority == EReleaseChecklistItem::Required && !Item.bCompleted)
		{
			return false;
		}
	}
	return true;
}

float ULesFightReleaseValidator::GetCompletionPercentage() const
{
	if (Checklist.Num() == 0) return 0.0f;

	int32 Completed = 0;
	for (const FQAReleaseChecklistItem& Item : Checklist)
	{
		if (Item.bCompleted) Completed++;
	}
	return (static_cast<float>(Completed) / static_cast<float>(Checklist.Num())) * 100.0f;
}

TArray<FString> ULesFightReleaseValidator::GetIncompleteCriticalItems() const
{
	TArray<FString> Incomplete;
	for (const FQAReleaseChecklistItem& Item : Checklist)
	{
		if ((Item.Priority == EReleaseChecklistItem::Critical || Item.Priority == EReleaseChecklistItem::Required) && !Item.bCompleted)
		{
			Incomplete.Add(Item.Item);
		}
	}
	return Incomplete;
}

void ULesFightReleaseValidator::ResetChecklist()
{
	for (FQAReleaseChecklistItem& Item : Checklist)
	{
		Item.bCompleted = false;
		Item.VerifiedBy.Empty();
	}
}
