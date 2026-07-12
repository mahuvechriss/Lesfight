#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightConnectionManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStateChanged, ENetworkSessionState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDisconnected, int32, PlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerConnected, int32, PlayerIndex, const FString&, PlayerName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionTimedOut, int32, PlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConnectionQualityChanged, EConnectionQuality, NewQuality, int32, PingMs);

UCLASS(Blueprintable)
class ULesFightConnectionManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightConnectionManager();

    void Initialize(class ULesFightMultiplayerManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void UpdatePingForPlayer(int32 PlayerIndex, int32 PingMs);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void ReportPlayerConnected(int32 PlayerIndex, const FString& PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void ReportPlayerDisconnected(int32 PlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void SetConnectionTimeout(float Seconds);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    bool IsPlayerConnected(int32 PlayerIndex) const;

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    bool AreAllPlayersConnected() const;

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    TArray<int32> GetDisconnectedPlayers() const;

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    int32 GetPlayerPingMs(int32 PlayerIndex) const;

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    EConnectionQuality GetConnectionQuality() const { return ConnectionQuality; }

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void ForceDisconnect(int32 PlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Connection")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnConnectionStateChanged OnConnectionStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerDisconnected OnPlayerDisconnected;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerConnected OnPlayerConnected;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnConnectionTimedOut OnConnectionTimedOut;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnConnectionQualityChanged OnConnectionQualityChanged;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float TimeoutDuration;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EConnectionQuality ConnectionQuality;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<int32, int32> PlayerPings;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FNetworkPlayerInfo> ConnectedPlayers;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float LastPingUpdateTime;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;
    TMap<int32, float> PlayerLastSeenTime;
    TSet<int32> DisconnectedPlayersSet;

    EConnectionQuality CalculateConnectionQuality(int32 AvgPingMs) const;
    void CheckForTimeouts(float CurrentTime);
};
