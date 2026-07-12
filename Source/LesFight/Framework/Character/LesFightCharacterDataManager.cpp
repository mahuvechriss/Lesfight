#include "LesFightCharacterDataManager.h"
#include "LesFightFighterDataAsset.h"
#include "LesFight.h"
#include "Engine/DataTable.h"

ULesFightCharacterDataManager::ULesFightCharacterDataManager()
{
}

void ULesFightCharacterDataManager::Initialize()
{
    LoadFromDataTable();
    UE_LOG(LogLesFight, Log, TEXT("CharacterDataManager initialized with %d fighters"), FighterDataMap.Num());
}

void ULesFightCharacterDataManager::LoadFighterDataTable(UDataTable* DataTable)
{
    FighterDataTable = DataTable;
    LoadFromDataTable();
}

void ULesFightCharacterDataManager::RegisterFighterDataAsset(ULesFightFighterDataAsset* DataAsset)
{
    if (!DataAsset) return;

    FName CharacterID = DataAsset->FighterData.Identity.CharacterID;
    if (CharacterID != NAME_None)
    {
        FighterDataMap.Add(CharacterID, DataAsset);
        FighterTableData.Add(CharacterID, DataAsset->FighterData);
        OnFighterDataLoaded.Broadcast(CharacterID);
    }
}

void ULesFightCharacterDataManager::UnregisterFighterDataAsset(FName CharacterID)
{
    FighterDataMap.Remove(CharacterID);
    FighterTableData.Remove(CharacterID);
}

ULesFightFighterDataAsset* ULesFightCharacterDataManager::GetFighterData(FName CharacterID) const
{
    if (FighterDataMap.Contains(CharacterID))
        return FighterDataMap[CharacterID];
    return nullptr;
}

FCharacterTableRow* ULesFightCharacterDataManager::GetFighterTableRow(FName CharacterID)
{
    if (FighterTableData.Contains(CharacterID))
        return &FighterTableData[CharacterID];
    return nullptr;
}

TArray<FName> ULesFightCharacterDataManager::GetAllFighterIDs() const
{
    TArray<FName> Keys;
    FighterDataMap.GetKeys(Keys);
    return Keys;
}

TArray<ULesFightFighterDataAsset*> ULesFightCharacterDataManager::GetAllFighterData() const
{
    TArray<ULesFightFighterDataAsset*> Results;
    for (auto& Pair : FighterDataMap)
    {
        if (Pair.Value)
            Results.Add(Pair.Value);
    }
    return Results;
}

void ULesFightCharacterDataManager::ClearData()
{
    FighterDataMap.Empty();
    FighterTableData.Empty();
}

void ULesFightCharacterDataManager::LoadFromDataTable()
{
    if (!FighterDataTable) return;

    TArray<FCharacterTableRow*> Rows;
    FighterDataTable->GetAllRows<FCharacterTableRow>(TEXT("FighterData"), Rows);

    for (FCharacterTableRow* Row : Rows)
    {
        if (Row && Row->Identity.CharacterID != NAME_None)
        {
            FighterTableData.Add(Row->Identity.CharacterID, *Row);
            FighterDataMap.Add(Row->Identity.CharacterID, nullptr);
        }
    }

    OnAllFighterDataLoaded.Broadcast();
}
