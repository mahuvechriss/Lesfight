#include "LesFightClothingSystem.h"
#include "LesFightCharCreationManager.h"

ULesFightClothingSystem::ULesFightClothingSystem()
    : MaxLayers(3)
{
    for (int32 i = 0; i < static_cast<int32>(EClothingSlot::MAX); i++)
    {
        AvailableSlots.Add(static_cast<EClothingSlot>(i));
    }
}

void ULesFightClothingSystem::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

bool ULesFightClothingSystem::EquipItem(EClothingSlot Slot, const FClothingItemData& Item)
{
    if (!AvailableSlots.Contains(Slot)) return false;
    EquippedItems.Add(Slot, Item);
    EquippedItems[Slot].bEquipped = true;
    return true;
}

bool ULesFightClothingSystem::UnequipItem(EClothingSlot Slot)
{
    if (!EquippedItems.Contains(Slot)) return false;
    EquippedItems.Remove(Slot);
    return true;
}

bool ULesFightClothingSystem::IsSlotEquipped(EClothingSlot Slot) const
{
    return EquippedItems.Contains(Slot) && EquippedItems[Slot].bEquipped;
}

FClothingItemData ULesFightClothingSystem::GetEquippedItem(EClothingSlot Slot) const
{
    const FClothingItemData* Item = EquippedItems.Find(Slot);
    return Item ? *Item : FClothingItemData();
}

TMap<EClothingSlot, FClothingItemData> ULesFightClothingSystem::GetAllClothing() const
{
    return EquippedItems;
}

void ULesFightClothingSystem::SetAllFromMap(
    const TMap<EClothingSlot, FClothingItemData>& Clothing)
{
    EquippedItems = Clothing;
}

void ULesFightClothingSystem::SetColor(EClothingSlot Slot, FLinearColor Color)
{
    if (FClothingItemData* Item = EquippedItems.Find(Slot))
    {
        Item->PrimaryColor = Color;
    }
}

void ULesFightClothingSystem::SetMaterialOverride(
    EClothingSlot Slot, UMaterialInterface* Material)
{
    if (Material)
    {
        MaterialOverrides.Add(Slot, Material);
    }
}

TArray<EClothingSlot> ULesFightClothingSystem::GetAvailableSlots() const
{
    return AvailableSlots;
}

void ULesFightClothingSystem::ApplyToCharacter(AActor* CharacterActor)
{
}

void ULesFightClothingSystem::ResetToDefault()
{
    EquippedItems.Empty();
    MaterialOverrides.Empty();
}
