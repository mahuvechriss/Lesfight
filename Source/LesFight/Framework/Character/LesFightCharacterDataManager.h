#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightCharacterData.h"
#include "LesFightCharacterDataManager.generated.h"

class ULesFightFighterDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFighterDataLoaded, FName, CharacterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllFighterDataLoaded);

UCLASS(Blueprintable, Config = Game)
class ULesFightCharacterDataManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterDataManager();

    UFUNCTION(BlueprintCallable, Category = "Data")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Data")
    void LoadFighterDataTable(UDataTable* DataTable);

    UFUNCTION(BlueprintCallable, Category = "Data")
    void RegisterFighterDataAsset(ULesFightFighterDataAsset* DataAsset);

    UFUNCTION(BlueprintCallable, Category = "Data")
    void UnregisterFighterDataAsset(FName CharacterID);

    UFUNCTION(BlueprintPure, Category = "Data")
    ULesFightFighterDataAsset* GetFighterData(FName CharacterID) const;

    UFUNCTION(BlueprintPure, Category = "Data")
    FCharacterTableRow* GetFighterTableRow(FName CharacterID);

    UFUNCTION(BlueprintPure, Category = "Data")
    TArray<FName> GetAllFighterIDs() const;

    UFUNCTION(BlueprintPure, Category = "Data")
    TArray<ULesFightFighterDataAsset*> GetAllFighterData() const;

    UFUNCTION(BlueprintPure, Category = "Data")
    int32 GetFighterCount() const { return FighterDataMap.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Data")
    void ClearData();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    TObjectPtr<UDataTable> FighterDataTable;

    UPROPERTY(BlueprintReadOnly, Category = "Data")
    TMap<FName, TObjectPtr<ULesFightFighterDataAsset>> FighterDataMap;

    UPROPERTY(BlueprintReadOnly, Category = "Data")
    TMap<FName, FCharacterTableRow> FighterTableData;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFighterDataLoaded OnFighterDataLoaded;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAllFighterDataLoaded OnAllFighterDataLoaded;

private:
    void LoadFromDataTable();
};
