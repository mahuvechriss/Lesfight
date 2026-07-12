#include "LesFightDataManager.h"
#include "LesFight.h"
#include "Engine/DataTable.h"

ULesFightDataManager::ULesFightDataManager()
{
}

void ULesFightDataManager::Initialize()
{
    LoadAllData();
    UE_LOG(LogLesFight, Log, TEXT("DataManager initialized with %d characters, %d arenas"),
        CharacterDataMap.Num(), ArenaDataMap.Num());
}

void ULesFightDataManager::LoadCharacterData()
{
    LoadDataTable(CharacterDataTable, TEXT("Character"));
}

void ULesFightDataManager::LoadArenaData()
{
    LoadDataTable(ArenaDataTable, TEXT("Arena"));
}

void ULesFightDataManager::LoadAllData()
{
    LoadCharacterData();
    LoadArenaData();
}

ULesFightCharacterDataAsset* ULesFightDataManager::GetCharacterData(FName CharacterID) const
{
    if (CharacterDataMap.Contains(CharacterID))
        return CharacterDataMap[CharacterID];
    return nullptr;
}

ULesFightArenaDataAsset* ULesFightDataManager::GetArenaData(FName ArenaID) const
{
    if (ArenaDataMap.Contains(ArenaID))
        return ArenaDataMap[ArenaID];
    return nullptr;
}

TArray<FName> ULesFightDataManager::GetAvailableCharacterIDs() const
{
    TArray<FName> Keys;
    CharacterDataMap.GetKeys(Keys);
    return Keys;
}

TArray<FName> ULesFightDataManager::GetAvailableArenaIDs() const
{
    TArray<FName> Keys;
    ArenaDataMap.GetKeys(Keys);
    return Keys;
}

void ULesFightDataManager::ClearData()
{
    CharacterDataMap.Empty();
    ArenaDataMap.Empty();
    LoadedAssets.Empty();
}

void ULesFightDataManager::AsyncLoadAsset(const FPrimaryAssetId& AssetId)
{
}

void ULesFightDataManager::LoadDataTable(UDataTable* Table, const FString& Type)
{
    if (!Table)
    {
        UE_LOG(LogLesFight, Warning, TEXT("Data table for %s is null"), *Type);
        return;
    }

    TArray<FName> RowNames = Table->GetRowNames();
    UE_LOG(LogLesFight, Log, TEXT("Loaded %d rows from %s data table"), RowNames.Num(), *Type);
    OnDataLoaded.Broadcast(Type);
}

void ULesFightDataManager::OnAssetLoadComplete(FPrimaryAssetId AssetId, UObject* Asset)
{
    if (Asset)
    {
        LoadedAssets.Add(AssetId, Asset);
        OnAssetLoaded.Broadcast(AssetId, Asset);
    }
}
