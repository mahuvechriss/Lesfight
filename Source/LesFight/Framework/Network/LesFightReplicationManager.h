#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightReplicationManager.generated.h"

UCLASS(Blueprintable)
class ULesFightReplicationManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightReplicationManager();

    void Initialize(ULesFightMultiplayerManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateCombatAction(int32 PlayerIndex, const FNetworkCombatAction& Action);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateAnimationState(int32 PlayerIndex, const FNetworkAnimSyncData& AnimData);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateHealthChange(int32 PlayerIndex, float OldHealth, float NewHealth);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateStaminaChange(int32 PlayerIndex, float OldStamina, float NewStamina);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateMeterChange(int32 PlayerIndex, float OldMeter, float NewMeter);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateKnockdown(int32 PlayerIndex, int32 AttackerIndex, float Force);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateBlockState(int32 PlayerIndex, bool bIsBlocking, EBlockType BlockType);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateSpecialMove(int32 PlayerIndex, FName SpecialMoveID);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateUltimateMove(int32 PlayerIndex, FName UltimateMoveID);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateRoundStart();

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateRoundEnd(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateMatchEnd(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicatePlayerTransform(int32 PlayerIndex, FTransform Transform);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateVFX(FName EffectID, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateAudio(FName SoundID, FVector Location, float Volume);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ReplicateHitConfirmation(int32 AttackerIndex, int32 DefenderIndex, float Damage);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void SetReplicationEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void FlushPendingReplications();

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    int32 GetPendingReplicationCount() const { return PendingActions.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Network|Replication")
    void ClearPendingReplications();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxReplicationRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxActionsPerTick;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FNetworkCombatAction> PendingActions;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bReplicationEnabled;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;
    float LastReplicationTime;

    struct FPendingReplication
    {
        int32 PlayerIndex;
        FNetworkCombatAction Action;
        float Timestamp;
    };
    TArray<FPendingReplication> ReplicationQueue;
};
