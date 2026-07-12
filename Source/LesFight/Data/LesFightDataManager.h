#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightCharacterDataAsset.h"
#include "LesFightArenaDataAsset.h"
#include "LesFightDataManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataLoaded, const FString&, DataType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAssetLoaded, const FPrimaryAssetId&, AssetId, UObject*, LoadedAsset);

UCLASS(Blueprintable, Config = Game)
class ULesFightDataManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightDataManager();

    UFUNCTION(BlueprintCallable, Category = "Data")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Data")
    void LoadCharacterData();

    UFUNCTION(BlueprintCallable, Category = "Data")
    void LoadArenaData();

    UFUNCTION(BlueprintCallable, Category = "Data")
    void LoadAllData();

    UFUNCTION(BlueprintPure, Category = "Data")
    ULesFightCharacterDataAsset* GetCharacterData(FName CharacterID) const;

    UFUNCTION(BlueprintPure, Category = "Data")
    ULesFightArenaDataAsset* GetArenaData(FName ArenaID) const;

    UFUNCTION(BlueprintPure, Category = "Data")
    TArray<FName> GetAvailableCharacterIDs() const;

    UFUNCTION(BlueprintPure, Category = "Data")
    TArray<FName> GetAvailableArenaIDs() const;

    UFUNCTION(BlueprintPure, Category = "Data")
    int32 GetCharacterCount() const { return CharacterDataMap.Num(); }

    UFUNCTION(BlueprintPure, Category = "Data")
    int32 GetArenaCount() const { return ArenaDataMap.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Data")
    void ClearData();

    UFUNCTION(BlueprintCallable, Category = "Data")
    void AsyncLoadAsset(const FPrimaryAssetId& AssetId);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    TObjectPtr<UDataTable> CharacterDataTable;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    TObjectPtr<UDataTable> ArenaDataTable;

    UPROPERTY(BlueprintReadOnly, Category = "Data")
    TMap<FName, TObjectPtr<ULesFightCharacterDataAsset>> CharacterDataMap;

    UPROPERTY(BlueprintReadOnly, Category = "Data")
    TMap<FName, TObjectPtr<ULesFightArenaDataAsset>> ArenaDataMap;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDataLoaded OnDataLoaded;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAssetLoaded OnAssetLoaded;

private:
    TMap<FPrimaryAssetId, TObjectPtr<UObject>> LoadedAssets;

    void LoadDataTable(UDataTable* Table, const FString& Type);
    void OnAssetLoadComplete(FPrimaryAssetId AssetId, UObject* Asset);
};
