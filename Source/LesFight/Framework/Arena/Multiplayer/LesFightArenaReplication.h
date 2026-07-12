#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaReplication.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArenaStateReceived, const FArenaEnvironmentState&, State);

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaReplication : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    void ReplicateArenaSelection(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    void ReplicateWeatherState(const FWeatherState& Weather);

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    void ReplicateLightingState(const FArenaLightingState& Lighting);

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    void ReplicateDestructionEvent(const FDestructibleObjectState& ObjectState);

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    void ReplicateEnvironmentState(const FArenaEnvironmentState& State);

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    void SetReplicationEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    bool IsReplicationEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    const TArray<FArenaEnvironmentState>& GetPendingStateUpdates() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    void ProcessPendingUpdates();

    UFUNCTION(BlueprintCallable, Category = "Arena|Multiplayer")
    float GetLastSyncTime() const;

    UPROPERTY(BlueprintAssignable, Category = "Arena|Multiplayer")
    FOnArenaStateReceived OnArenaStateReceived;

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Arena|Multiplayer")
    bool bReplicationEnabled = true;

    UPROPERTY()
    TArray<FArenaEnvironmentState> PendingUpdates;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Multiplayer")
    float SyncInterval = 0.5f;

    UPROPERTY()
    float LastSyncTime = 0.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Multiplayer")
    int32 MaxUpdatesPerTick = 10;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
};
