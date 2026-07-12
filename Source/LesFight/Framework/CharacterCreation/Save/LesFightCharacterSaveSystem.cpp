#include "LesFightCharacterSaveSystem.h"
#include "LesFightCharCreationManager.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

ULesFightCharacterSaveSystem::ULesFightCharacterSaveSystem()
    : MaxSaveSlots(50)
    , SaveDirectory(TEXT("SaveGames/Characters"))
    , bAutoSave(true)
    , AutoSaveInterval(120.0f)
    , TimeSinceLastAutoSave(0.0f)
{
    SaveSlotName = TEXT("Default");
}

void ULesFightCharacterSaveSystem::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
    InMemoryCharacters.Empty();
}

bool ULesFightCharacterSaveSystem::SaveCharacter(
    FName CharacterID, const FCharacterCustomizationPreset& Data)
{
    InMemoryCharacters.Add(CharacterID, Data);
    TArray<uint8> SaveData;
    FMemoryWriter Writer(SaveData);
    FObjectAndNameAsStringProxyArchive Ar(Writer, false);
    const_cast<FCharacterCustomizationPreset&>(Data).Serialize(Ar);
    return FFileHelper::SaveArrayToFile(SaveData, *GetCharacterSavePath(CharacterID));
}

bool ULesFightCharacterSaveSystem::LoadCharacter(
    FName CharacterID, FCharacterCustomizationPreset& OutData)
{
    if (InMemoryCharacters.Contains(CharacterID))
    {
        OutData = InMemoryCharacters[CharacterID];
        return true;
    }

    TArray<uint8> SaveData;
    if (!FFileHelper::LoadFileToArray(SaveData, *GetCharacterSavePath(CharacterID)))
    {
        return false;
    }

    FMemoryReader Reader(SaveData);
    FObjectAndNameAsStringProxyArchive Ar(Reader, false);
    OutData.Serialize(Ar);
    InMemoryCharacters.Add(CharacterID, OutData);
    return true;
}

bool ULesFightCharacterSaveSystem::DeleteCharacterSave(FName CharacterID)
{
    InMemoryCharacters.Remove(CharacterID);
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    return PlatformFile.DeleteFile(*GetCharacterSavePath(CharacterID));
}

bool ULesFightCharacterSaveSystem::SaveAllCharacters(
    const TMap<FName, FCharacterCustomizationPreset>& Characters)
{
    InMemoryCharacters = Characters;
    bool bAllSuccess = true;
    for (const auto& Pair : Characters)
    {
        if (!SaveCharacter(Pair.Key, Pair.Value))
        {
            bAllSuccess = false;
        }
    }
    return bAllSuccess;
}

TMap<FName, FCharacterCustomizationPreset> ULesFightCharacterSaveSystem::LoadAllCharacters()
{
    TMap<FName, FCharacterCustomizationPreset> AllCharacters;
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    FString SearchPath = FPaths::ProjectSavedDir() / SaveDirectory;
    TArray<FString> FoundFiles;
    PlatformFile.FindFiles(FoundFiles, *SearchPath, *GetSaveExtension());

    for (const FString& FilePath : FoundFiles)
    {
        FString Filename = FPaths::GetBaseFilename(FilePath);
        FName CharID(*Filename);
        FCharacterCustomizationPreset Data;
        if (LoadCharacter(CharID, Data))
        {
            AllCharacters.Add(CharID, Data);
        }
    }
    return AllCharacters;
}

TArray<FName> ULesFightCharacterSaveSystem::GetSavedCharacterIDs()
{
    TArray<FName> IDs;
    InMemoryCharacters.GetKeys(IDs);
    return IDs;
}

bool ULesFightCharacterSaveSystem::CharacterSaveExists(FName CharacterID)
{
    return InMemoryCharacters.Contains(CharacterID) ||
        IPlatformFile::GetPlatformPhysical().FileExists(*GetCharacterSavePath(CharacterID));
}

bool ULesFightCharacterSaveSystem::SaveToSlot(int32 SlotIndex)
{
    TArray<uint8> SaveData;
    FMemoryWriter Writer(SaveData);
    for (const auto& Pair : InMemoryCharacters)
    {
        Pair.Value.Serialize(Writer);
    }
    return FFileHelper::SaveArrayToFile(SaveData, *GetSlotSavePath(SlotIndex));
}

bool ULesFightCharacterSaveSystem::LoadFromSlot(int32 SlotIndex)
{
    TArray<uint8> SaveData;
    if (!FFileHelper::LoadFileToArray(SaveData, *GetSlotSavePath(SlotIndex)))
    {
        return false;
    }
    FMemoryReader Reader(SaveData);
    InMemoryCharacters.Empty();
    for (int32 i = 0; i < MaxSaveSlots && Reader.Tell() < Reader.TotalSize(); i++)
    {
        FCharacterCustomizationPreset Data;
        Data.Serialize(Reader);
        InMemoryCharacters.Add(FName(*FString::Printf(TEXT("SlotChar_%d"), i)), Data);
    }
    return true;
}

void ULesFightCharacterSaveSystem::SetAutoSave(bool bInAutoSave)
{
    bAutoSave = bInAutoSave;
    TimeSinceLastAutoSave = 0.0f;
}

void ULesFightCharacterSaveSystem::AutoSave()
{
    if (!InMemoryCharacters.IsEmpty())
    {
        SaveAllCharacters(InMemoryCharacters);
    }
}

FString ULesFightCharacterSaveSystem::GetCharacterSavePath(FName CharacterID) const
{
    return FPaths::ProjectSavedDir() / SaveDirectory /
        CharacterID.ToString() + GetSaveExtension();
}

FString ULesFightCharacterSaveSystem::GetSlotSavePath(int32 SlotIndex) const
{
    return FPaths::ProjectSavedDir() / SaveDirectory /
        FString::Printf(TEXT("Slot_%d_%s%s"), SlotIndex, *SaveSlotName, *GetSaveExtension());
}
