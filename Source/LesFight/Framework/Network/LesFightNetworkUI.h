#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLANGamesFound, const TArray<FLANSessionInfo>&, Sessions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConnectionStatusChanged, int32, StatusCode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoinedLobby, int32, PlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLeftLobby, int32, PlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReadyStateChanged, int32, PlayerIndex, bool, bReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchCountdown, int32, SecondsRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMatchSummary, int32, WinnerIndex, const TArray<FNetworkPlayerInfo>&, Players);

UCLASS(Blueprintable)
class ULesFightNetworkUI : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkUI();

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void Initialize(class ULesFightMultiplayerManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowHostScreen();

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowJoinScreen();

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowLobbyScreen();

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowMatchCountdown(int32 Seconds);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowMatchSummary(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowLoadingScreen(const FString& LoadMessage);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowError(const FString& ErrorMessage);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void ShowConnectionStatus(const FString& Status, EConnectionQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void UpdatePingDisplay(int32 PingMs);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void UpdatePlayerList(const TArray<FNetworkPlayerInfo>& Players);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void HideAllNetworkUI();

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void OnSessionsFound(const TArray<FLANSessionInfo>& Sessions);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void OnConnectionStateChanged(ENetworkSessionState NewState);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void OnMatchStateChanged(ENetworkMatchState NewState);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void NotifyRoundStart(int32 RoundNumber);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void NotifyRoundEnd(int32 WinnerIndex, EWinCondition WinCondition);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void NotifyMatchEnd(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void NotifyPlayerDisconnected(int32 PlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|UI")
    void SetUIEnabled(bool bEnabled);

    UFUNCTION(BlueprintPure, Category = "Network|UI")
    bool IsUIVisible() const { return bUIVisible; }

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLANGamesFound OnLANGamesFound;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnConnectionStatusChanged OnConnectionStatusChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerJoinedLobby OnPlayerJoinedLobby;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerLeftLobby OnPlayerLeftLobby;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnReadyStateChanged OnReadyStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMatchCountdown OnMatchCountdown;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMatchSummary OnMatchSummary;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bUIVisible;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;
    FString CurrentScreen;
};
