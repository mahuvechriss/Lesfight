#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightVFXReplication.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVFXEventReplicated, FName, EventName, FVector, Location);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightVFXReplication : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    void ReplicateVFXEvent(FName EventName, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    void ReplicateImpact(EImpactVFXType Type, FVector Location, FVector Normal);

    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    void ReplicateCinematicEvent(ECinematicVFXEvent Event, AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    void SetReplicationEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    bool IsReplicationEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    bool IsEffectDuplicate(FName EventID) const;

    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    void ProcessReplicatedVFX();

    UFUNCTION(BlueprintCallable, Category = "VFX Replication")
    void SetSyncQuality(int32 Quality);

    void Initialize(ULesFightVFXWorldManager* InOwner);

    UPROPERTY(BlueprintAssignable, Category = "VFX Replication")
    FOnVFXEventReplicated OnVFXEventReplicated;

protected:
    UPROPERTY()
    bool bReplicationEnabled;

    UPROPERTY()
    TArray<struct FVFXReplicatedEntry> PendingEffects;

    UPROPERTY()
    TMap<FName, float> RecentEvents;

    UPROPERTY()
    float DuplicateWindow;

    UPROPERTY()
    int32 SyncQuality;

private:
    TWeakObjectPtr<class ULesFightVFXWorldManager> OwnerManager;
};
