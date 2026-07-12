#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightAICharReplication.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAICharDataReceived, const FAICharacterGenerationResult&, Result);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAICharReplication : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    void SendGeneratedCharacter(const FAICharacterGenerationResult& Result, int32 TargetPlayerID = -1);

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    void RequestCharacterData(int32 FromPlayerID);

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    bool HasPendingData() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    int32 GetPendingDataCount() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    void ProcessPendingData();

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    void ClearPendingData();

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    void SetReplicationEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    bool IsReplicationEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    FAICharacterGenerationResult OptimizeCharacterData(const FAICharacterGenerationResult& Result);

    UFUNCTION(BlueprintCallable, Category = "AI|Replication")
    FAICharacterGenerationResult ReconstructCharacterFromOptimized(const FAICharacterGenerationResult& Optimized);

    UPROPERTY(BlueprintAssignable, Category = "AI|Replication")
    FOnAICharDataReceived OnAICharDataReceived;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Replication|Config")
    bool bReplicationEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Replication|Config")
    int32 CompressionLevel;

    UPROPERTY(BlueprintReadOnly, Category = "AI|Replication|Data")
    TArray<FAICharacterGenerationResult> PendingData;

    UPROPERTY(BlueprintReadOnly, Category = "AI|Replication|Data")
    TArray<FAICharacterGenerationResult> ReceivedData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Replication|Config")
    float SyncInterval;

private:
    TWeakObjectPtr<class ULesFightAIManager> OwnerManager;

public:
    void Initialize(ULesFightAIManager* InManager);
};
