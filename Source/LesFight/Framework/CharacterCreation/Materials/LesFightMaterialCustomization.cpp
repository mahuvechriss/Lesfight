#include "LesFightMaterialCustomization.h"
#include "LesFightCharCreationManager.h"

ULesFightMaterialCustomization::ULesFightMaterialCustomization()
{
    DefaultMaterialSlots = {
        TEXT("Body"), TEXT("Head"), TEXT("Arms"), TEXT("Legs"),
        TEXT("Torso"), TEXT("Feet"), TEXT("Hands")
    };
    for (const FName& Slot : DefaultMaterialSlots)
    {
        FMaterialEditState State;
        State.MaterialSlotName = Slot;
        State.BaseColor = FLinearColor(0.5f, 0.5f, 0.5f);
        State.Metallic = 0.0f;
        State.Roughness = 0.5f;
        MaterialEditStates.Add(Slot, State);
    }
}

void ULesFightMaterialCustomization::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightMaterialCustomization::EditMaterialSlot(const FMaterialEditState& EditState)
{
    MaterialEditStates.Add(EditState.MaterialSlotName, EditState);
}

FMaterialEditState ULesFightMaterialCustomization::GetMaterialSlotState(
    FName SlotName) const
{
    const FMaterialEditState* State = MaterialEditStates.Find(SlotName);
    return State ? *State : FMaterialEditState();
}

TArray<FName> ULesFightMaterialCustomization::GetEditableMaterialSlots() const
{
    TArray<FName> Slots;
    MaterialEditStates.GetKeys(Slots);
    return Slots;
}

void ULesFightMaterialCustomization::ResetMaterialSlot(FName SlotName)
{
    if (MaterialEditStates.Contains(SlotName))
    {
        FMaterialEditState& State = MaterialEditStates[SlotName];
        State.BaseColor = FLinearColor(0.5f, 0.5f, 0.5f);
        State.Metallic = 0.0f;
        State.Roughness = 0.5f;
        State.DiffuseTexture = nullptr;
        State.NormalTexture = nullptr;
        State.OverrideMaterial = nullptr;
    }
}

void ULesFightMaterialCustomization::ResetAllMaterialSlots()
{
    for (auto& Pair : MaterialEditStates)
    {
        ResetMaterialSlot(Pair.Key);
    }
}

void ULesFightMaterialCustomization::ApplyToCharacter(AActor* CharacterActor)
{
}

TArray<FMaterialEditState> ULesFightMaterialCustomization::GetAllEditStates() const
{
    TArray<FMaterialEditState> States;
    MaterialEditStates.GenerateValueArray(States);
    return States;
}

void ULesFightMaterialCustomization::SetAllEditStates(
    const TArray<FMaterialEditState>& States)
{
    for (const FMaterialEditState& State : States)
    {
        MaterialEditStates.Add(State.MaterialSlotName, State);
    }
}

void ULesFightMaterialCustomization::SaveMaterialPreset(FName PresetName)
{
    for (auto& Pair : MaterialEditStates)
    {
        SavedPresets.Add(FName(PresetName.ToString() + TEXT("_") + Pair.Key.ToString()), Pair.Value);
    }
}

bool ULesFightMaterialCustomization::LoadMaterialPreset(FName PresetName)
{
    FString Prefix = PresetName.ToString() + TEXT("_");
    for (auto& Pair : SavedPresets)
    {
        if (Pair.Key.ToString().StartsWith(Prefix))
        {
            FString SlotName = Pair.Key.ToString().RightChop(Prefix.Len());
            MaterialEditStates.Add(FName(*SlotName), Pair.Value);
        }
    }
    return true;
}
