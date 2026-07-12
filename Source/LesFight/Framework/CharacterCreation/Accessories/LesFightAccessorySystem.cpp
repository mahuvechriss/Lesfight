#include "LesFightAccessorySystem.h"
#include "LesFightCharCreationManager.h"

ULesFightAccessorySystem::ULesFightAccessorySystem()
	: MaxAccessories(8)
{
	for (uint8 i = 0; i < static_cast<uint8>(EAccessorySlot::MAX); ++i)
	{
		AvailableSlots.Add(static_cast<EAccessorySlot>(i));
	}
}

void ULesFightAccessorySystem::Initialize(ULesFightCharCreationManager* InOwnerManager)
{
	OwnerManager = InOwnerManager;
}

void ULesFightAccessorySystem::EquipAccessory(const FAccessoryEditState& InAccessory)
{
	if (InAccessory.Slot >= EAccessorySlot::MAX)
	{
		return;
	}

	if (EquippedAccessories.Num() >= MaxAccessories)
	{
		return;
	}

	FAccessoryEditState NewEntry = InAccessory;
	NewEntry.bEquipped = true;
	EquippedAccessories.Add(InAccessory.Slot, NewEntry);
}

void ULesFightAccessorySystem::UnequipAccessory(EAccessorySlot Slot)
{
	if (Slot >= EAccessorySlot::MAX)
	{
		return;
	}

	EquippedAccessories.Remove(Slot);
}

bool ULesFightAccessorySystem::IsSlotOccupied(EAccessorySlot Slot) const
{
	if (Slot >= EAccessorySlot::MAX)
	{
		return false;
	}

	return EquippedAccessories.Contains(Slot);
}

FAccessoryEditState ULesFightAccessorySystem::GetAccessory(EAccessorySlot Slot) const
{
	if (Slot >= EAccessorySlot::MAX)
	{
		return FAccessoryEditState();
	}

	const FAccessoryEditState* Found = EquippedAccessories.Find(Slot);
	if (Found)
	{
		return *Found;
	}

	return FAccessoryEditState();
}

const TMap<EAccessorySlot, FAccessoryEditState>& ULesFightAccessorySystem::GetAllAccessories() const
{
	return EquippedAccessories;
}

void ULesFightAccessorySystem::SetAccessoryTransform(EAccessorySlot Slot, const FVector& NewOffset, const FRotator& NewRotation, const FVector& NewScale)
{
	if (Slot >= EAccessorySlot::MAX)
	{
		return;
	}

	FAccessoryEditState* Entry = EquippedAccessories.Find(Slot);
	if (!Entry)
	{
		return;
	}

	Entry->Offset = NewOffset;
	Entry->Rotation = NewRotation;
	Entry->Scale = NewScale.ClampAxes(0.01, 100.0);
}

void ULesFightAccessorySystem::SetAccessoryColor(EAccessorySlot Slot, const FLinearColor& NewColor)
{
	if (Slot >= EAccessorySlot::MAX)
	{
		return;
	}

	FAccessoryEditState* Entry = EquippedAccessories.Find(Slot);
	if (!Entry)
	{
		return;
	}

	Entry->Color = NewColor;
}

TArray<EAccessorySlot> ULesFightAccessorySystem::GetAvailableSlots() const
{
	TArray<EAccessorySlot> Result;
	for (const EAccessorySlot Slot : AvailableSlots)
	{
		if (!EquippedAccessories.Contains(Slot))
		{
			Result.Add(Slot);
		}
	}
	return Result;
}

void ULesFightAccessorySystem::ApplyToCharacter(AActor* TargetCharacter)
{
}

void ULesFightAccessorySystem::ResetToDefault()
{
	EquippedAccessories.Empty();
}
