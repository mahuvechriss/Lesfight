#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkSyncManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCombatActionReceived, int32, PlayerIndex, const FNetworkCombatAction&, Action);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimSyncReceived, int32, PlayerIndex, const FNetworkAnimSyncData&, AnimData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFullStateSyncRequested);

UCLASS(Blueprintable)
class ULesFightNetworkSyncManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkSyncManager();

    void Initialize(ULesFightMultiplayerManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendCombatAction(int32 PlayerIndex, const FNetworkCombatAction& Action);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendAnimationState(int32 PlayerIndex, const FNetworkAnimSyncData& AnimData);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendHealthSync(int32 PlayerIndex, float Health, float MaxHealth);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendStaminaSync(int32 PlayerIndex, float Stamina, float MaxStamina);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendMeterSync(int32 PlayerIndex, float Meter, float MaxMeter);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendPositionSync(int32 PlayerIndex, FVector Position, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendRoundStateSync(int32 RoundNumber, float TimeRemaining);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendRoundWinCount(int32 PlayerIndex, int32 Wins);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SendReadyState(int32 PlayerIndex, ENetworkReadyState ReadyState);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void RequestFullStateSync();

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void OnCombatActionReceived_Client(int32 PlayerIndex, const FNetworkCombatAction& Action);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void OnAnimSyncReceived_Client(int32 PlayerIndex, const FNetworkAnimSyncData& AnimData);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void OnFullStateSyncReceived(const FNetworkMatchData& MatchData);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    int32 GetPendingSyncCount() const { return PendingSyncs.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void ClearPendingSyncs();

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SetSyncRate(float SyncsPerSecond);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SetCompressionEnabled(bool bEnabled);

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCombatActionReceived OnCombatActionReceived;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimSyncReceived OnAnimSyncReceived;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFullStateSyncRequested OnFullStateSyncRequested;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float SyncInterval;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxSyncsPerTick;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    bool bCompressionEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FNetworkCombatAction> PendingSyncs;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float LastSyncTime;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bIsSynchronized;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;

    struct FQueuedSync
    {
        int32 PlayerIndex;
        FNetworkCombatAction Action;
        float SendTime;
    };
    TArray<FQueuedSync> SyncQueue;

    void ProcessSyncQueue();
    void ApplyCombatActionToRemote(int32 PlayerIndex, const FNetworkCombatAction& Action);
    void ApplyAnimSyncToRemote(int32 PlayerIndex, const FNetworkAnimSyncData& AnimData);
};
