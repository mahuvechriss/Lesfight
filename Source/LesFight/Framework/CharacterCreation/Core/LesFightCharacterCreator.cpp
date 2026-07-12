#include "LesFightCharacterCreator.h"
#include "LesFightCharCreationManager.h"

ULesFightCharacterCreator::ULesFightCharacterCreator()
    : ActiveCharacterID(NAME_None)
    , CurrentMode(ECharacterCreatorMode::Create)
    , NextCharacterIndex(0)
{
}

void ULesFightCharacterCreator::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
    NextCharacterIndex = 0;
}

FName ULesFightCharacterCreator::CreateNewCharacter(const FCharacterBiographyData& BioData)
{
    FName CharID = GenerateCharacterID();
    FCharacterCustomizationPreset Preset;
    Preset.Biography = BioData;
    Preset.Biography.CreatedDate = FDateTime::Now();
    Preset.Biography.LastModifiedDate = FDateTime::Now();
    CharacterData.Add(CharID, Preset);
    ActiveCharacterID = CharID;
    OnCharacterCreated.Broadcast(CharID);
    return CharID;
}

bool ULesFightCharacterCreator::EditCharacter(FName CharacterID)
{
    if (!CharacterData.Contains(CharacterID)) return false;
    ActiveCharacterID = CharacterID;
    CurrentMode = ECharacterCreatorMode::Edit;
    return true;
}

bool ULesFightCharacterCreator::DuplicateCharacter(FName CharacterID)
{
    const FCharacterCustomizationPreset* Source = CharacterData.Find(CharacterID);
    if (!Source) return false;

    FName NewID = GenerateCharacterID();
    CharacterData.Add(NewID, *Source);
    CharacterData[NewID].Biography.CharacterName = Source->Biography.CharacterName + TEXT(" (Copy)");
    CharacterData[NewID].Biography.CreatedDate = FDateTime::Now();
    CharacterData[NewID].Biography.LastModifiedDate = FDateTime::Now();
    OnCharacterDuplicated.Broadcast(NewID);
    return true;
}

bool ULesFightCharacterCreator::DeleteCharacter(FName CharacterID)
{
    if (!CharacterData.Remove(CharacterID)) return false;
    if (ActiveCharacterID == CharacterID)
    {
        ActiveCharacterID = NAME_None;
    }
    OnCharacterDeleted.Broadcast(CharacterID);
    return true;
}

FCharacterCustomizationPreset ULesFightCharacterCreator::GetCharacterData(
    FName CharacterID) const
{
    const FCharacterCustomizationPreset* Found = CharacterData.Find(CharacterID);
    return Found ? *Found : FCharacterCustomizationPreset();
}

bool ULesFightCharacterCreator::SetCharacterData(
    FName CharacterID, const FCharacterCustomizationPreset& Data)
{
    if (!CharacterData.Contains(CharacterID)) return false;
    CharacterData[CharacterID] = Data;
    CharacterData[CharacterID].Biography.LastModifiedDate = FDateTime::Now();
    OnCharacterUpdated.Broadcast(CharacterID);
    return true;
}

void ULesFightCharacterCreator::SetActiveCharacter(FName CharacterID)
{
    if (CharacterData.Contains(CharacterID))
    {
        ActiveCharacterID = CharacterID;
    }
}

FCharacterCustomizationPreset ULesFightCharacterCreator::GetActiveCharacterData() const
{
    return GetCharacterData(ActiveCharacterID);
}

TArray<FName> ULesFightCharacterCreator::GetAllCharacterIDs() const
{
    TArray<FName> IDs;
    CharacterData.GetKeys(IDs);
    return IDs;
}

FValidationResult ULesFightCharacterCreator::ValidateCharacter(FName CharacterID) const
{
    FValidationResult Result;
    const FCharacterCustomizationPreset* Data = CharacterData.Find(CharacterID);
    if (!Data)
    {
        Result.bIsValid = false;
        Result.Errors.Add(TEXT("Character not found"));
        return Result;
    }

    if (Data->Biography.CharacterName.IsEmpty())
    {
        Result.Errors.Add(TEXT("Character name is required"));
        Result.bIsValid = false;
    }

    if (Data->Biography.Age < 16 || Data->Biography.Age > 99)
    {
        Result.Warnings.Add(TEXT("Age outside typical range"));
    }

    if (Data->Clothing.Num() > 12)
    {
        Result.Warnings.Add(TEXT("Excessive clothing items may impact performance"));
    }

    return Result;
}

void ULesFightCharacterCreator::ClearAllCharacters()
{
    CharacterData.Empty();
    ActiveCharacterID = NAME_None;
}

FName ULesFightCharacterCreator::GenerateCharacterID()
{
    FString ID;
    do
    {
        ID = FString::Printf(TEXT("Character_%d"), NextCharacterIndex++);
    } while (CharacterData.Contains(FName(*ID)));
    return FName(*ID);
}
