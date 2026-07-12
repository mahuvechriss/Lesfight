#include "LesFightCharacterPreset.h"
#include "LesFightCharCreationManager.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

ULesFightCharacterPreset::ULesFightCharacterPreset()
    : MaxPresetSlots(20)
    , PresetDirectory(TEXT("SaveGames/CharacterPresets"))
{
}

void ULesFightCharacterPreset::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
    CachedPresets.Empty();
}

bool ULesFightCharacterPreset::ExportPreset(
    const FCharacterCustomizationPreset& Preset, const FString& FilePath)
{
    TArray<uint8> SaveData;
    FMemoryWriter Writer(SaveData);
    FObjectAndNameAsStringProxyArchive Ar(Writer, false);
    const_cast<FCharacterCustomizationPreset&>(Preset).Serialize(Ar);
    return FFileHelper::SaveArrayToFile(SaveData, *FilePath);
}

FCharacterCustomizationPreset ULesFightCharacterPreset::ImportPreset(const FString& FilePath)
{
    FCharacterCustomizationPreset Preset;
    TArray<uint8> SaveData;
    if (!FFileHelper::LoadFileToArray(SaveData, *FilePath)) return Preset;

    FMemoryReader Reader(SaveData);
    FObjectAndNameAsStringProxyArchive Ar(Reader, false);
    Preset.Serialize(Ar);
    return Preset;
}

bool ULesFightCharacterPreset::SavePresetToSlot(
    const FCharacterCustomizationPreset& Preset, int32 SlotIndex)
{
    CachedPresets.Add(SlotIndex, Preset);
    return ExportPreset(Preset, GetPresetSlotPath(SlotIndex));
}

FCharacterCustomizationPreset ULesFightCharacterPreset::LoadPresetFromSlot(int32 SlotIndex)
{
    if (CachedPresets.Contains(SlotIndex))
    {
        return CachedPresets[SlotIndex];
    }
    FCharacterCustomizationPreset Preset = ImportPreset(GetPresetSlotPath(SlotIndex));
    CachedPresets.Add(SlotIndex, Preset);
    return Preset;
}

TArray<int32> ULesFightCharacterPreset::GetOccupiedPresetSlots() const
{
    TArray<int32> Slots;
    CachedPresets.GetKeys(Slots);
    return Slots;
}

bool ULesFightCharacterPreset::DeletePresetFromSlot(int32 SlotIndex)
{
    CachedPresets.Remove(SlotIndex);
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    return PlatformFile.DeleteFile(*GetPresetSlotPath(SlotIndex));
}

FString ULesFightCharacterPreset::GetPresetFilePath(int32 SlotIndex) const
{
    return GetPresetSlotPath(SlotIndex);
}

FString ULesFightCharacterPreset::GetPresetSlotPath(int32 SlotIndex) const
{
    return FPaths::ProjectSavedDir() / PresetDirectory /
        FString::Printf(TEXT("Preset_%d%s"), SlotIndex, *GetPresetExtension());
}
