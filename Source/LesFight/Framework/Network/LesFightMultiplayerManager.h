#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightMultiplayerManager.generated.h"

UCLASS(Blueprintable)
class ULesFightMultiplayerManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMultiplayerManager();

    UFUNCTION(BlueprintCallable, Category = "Network")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Network")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Network")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|Session")
    bool HostGame(const FString& SessionName, int32 MaxPlayers = 2);

    UFUNCTION(BlueprintCallable, Category = "Network|Session")
    bool FindLANGames();

    UFUNCTION(BlueprintCallable, Category = "Network|Session")
    bool JoinGame(int32 SessionIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Session")
    bool LeaveGame();

    UFUNCTION(BlueprintCallable, Category = "Network|Session")
    bool ReturnToLobby();

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void RequestStartMatch();

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void RequestRoundEnd(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Player")
    void SetPlayerReady(bool bReady);

    UFUNCTION(BlueprintCallable, Category = "Network|Player")
    void OnPlayerInput(const FName& InputAction, float InputValue);

    UFUNCTION(BlueprintCallable, Category = "Network|Player")
    void OnCombatAction(const FNetworkCombatAction& Action);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void SyncAnimationState(const FNetworkAnimSyncData& AnimData);

    UFUNCTION(BlueprintCallable, Category = "Network|Sync")
    void RequestFullStateSync();

    UFUNCTION(BlueprintCallable, Category = "Network")
    void ReplicateCombatAction(int32 PlayerIndex, const FNetworkCombatAction& Action);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void BroadcastChatMessage(const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "Network")
    void SendSystemMessage(const FString& Message);

    UFUNCTION(BlueprintPure, Category = "Network|State")
    bool IsMultiplayerActive() const { return bMultiplayerActive; }

    UFUNCTION(BlueprintPure, Category = "Network|State")
    bool IsHosting() const;

    UFUNCTION(BlueprintPure, Category = "Network|State")
    int32 GetLocalPlayerIndex() const { return LocalPlayerIndex; }

    UFUNCTION(BlueprintPure, Category = "Network|State")
    FString GetLocalPlayerName() const { return LocalPlayerName; }

    UFUNCTION(BlueprintPure, Category = "Network|State")
    ENetworkSessionState GetSessionState() const;

    UFUNCTION(BlueprintPure, Category = "Network|State")
    ENetworkMatchState GetMatchState() const;

    UFUNCTION(BlueprintPure, Category = "Network|State")
    TArray<FLANSessionInfo> GetFoundSessions() const;

    UFUNCTION(BlueprintPure, Category = "Network|State")
    TArray<FNetworkPlayerInfo> GetPlayerList() const;

    UFUNCTION(BlueprintPure, Category = "Network|State")
    FNetworkMatchData GetCurrentMatchData() const;

    UFUNCTION(BlueprintCallable, Category = "Network|State")
    void SetLocalPlayerName(const FString& Name) { LocalPlayerName = Name; }

    UFUNCTION(BlueprintCallable, Category = "Network|Configuration")
    void SetMaxRounds(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Network|Configuration")
    void SetRoundTimeLimit(float Seconds);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightSessionManager* SessionManager;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightConnectionManager* ConnectionManager;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightMatchManager* MatchManager;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightNetworkSyncManager* SyncManager;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightReplicationManager* ReplicationManager;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightNetworkPrediction* NetworkPrediction;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightNetworkOptimizer* NetworkOptimizer;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightLagCompensation* LagCompensation;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightNetworkSecurity* NetworkSecurity;

    UPROPERTY(BlueprintReadOnly, Category = "Managers")
    class ULesFightNetworkDebugger* NetworkDebugger;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    ULesFightNetworkDataAsset* NetworkSettings;

private:
    bool bMultiplayerActive;
    bool bInitialized;
    int32 LocalPlayerIndex;
    FString LocalPlayerName;
    TWeakObjectPtr<UWorld> CachedWorld;

    void CreateSubManagers();
    void ConfigureNetworkSettings();
};
