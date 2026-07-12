#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightCharacterCreationData.h"
#include "LesFightCharacterReplication.generated.h"

USTRUCT(BlueprintType)
struct FReplicatedCharacterData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CharacterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FCharacterCustomizationPreset Preset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsLocalPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LastSyncTime;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterDataReceived, const FReplicatedCharacterData&);

UCLASS(Blueprintable)
class ULesFightCharacterReplication : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterReplication();

    void Initialize(class ULesFightCharCreationManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    void SendCharacterData(const FCharacterCustomizationPreset& Preset, int32 TargetPlayerID = -1);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    void RequestCharacterData(int32 FromPlayerID);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    bool HasPendingData() const { return PendingData.Num() > 0; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    int32 GetPendingDataCount() const { return PendingData.Num(); }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    void ProcessPendingData();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    void ClearPendingData();

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    void SetReplicationEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    bool IsReplicationEnabled() const { return bReplicationEnabled; }

    UFUNCTION(BlueprintCallable, Category = "CharacterCreator|Replication")
    void SetCompressionLevel(int32 Level);

    FOnCharacterDataReceived OnCharacterDataReceived;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bReplicationEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CompressionLevel;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float SyncInterval;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxPendingData;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FReplicatedCharacterData> PendingData;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FReplicatedCharacterData> ReceivedData;

private:
    TWeakObjectPtr<class ULesFightCharCreationManager> OwnerManager;
};
