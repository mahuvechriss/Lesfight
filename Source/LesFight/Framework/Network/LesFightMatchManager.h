#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightMatchManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchStateChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStarted, int32, RoundNumber);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundEnded, int32, WinnerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchEnded, int32, WinnerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountdownStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountdownTick, int32, SecondsRemaining);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerReadyChanged, int32, PlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchTimeUpdated, float, TimeRemaining);

UCLASS(Blueprintable)
class ULesFightMatchManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMatchManager();

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void Initialize(class ALesFightNetworkGameMode* InGameMode);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void StartMatch();

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void EndMatch(int32 WinnerPlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void StartRound(int32 RoundNumber);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void EndRound(int32 WinnerPlayerIndex, EWinCondition WinCondition);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void StartCountdown(int32 Seconds);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void SetPlayerReady(int32 PlayerIndex, bool bReady);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    bool AreAllPlayersReady() const;

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    FNetworkMatchData GetMatchData() const { return CurrentMatchData; }

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    ENetworkMatchState GetMatchState() const { return CurrentMatchData.MatchState; }

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void SetRoundTimeLimit(float Seconds);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void SetMaxRounds(int32 MaxRounds);

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void Reset();

    UFUNCTION(BlueprintCallable, Category = "Network|Match")
    void TickRoundTimer(float DeltaTime);

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMatchStateChanged OnMatchStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRoundStarted OnRoundStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRoundEnded OnRoundEnded;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMatchEnded OnMatchEnded;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCountdownStarted OnCountdownStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCountdownTick OnCountdownTick;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerReadyChanged OnPlayerReadyChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMatchTimeUpdated OnMatchTimeUpdated;

    UPROPERTY(BlueprintReadWrite, Category = "State")
    FNetworkMatchData CurrentMatchData;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<int32, bool> PlayerReadyStates;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<int32, int32> PlayerRoundWins;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxRounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float RoundTimeLimit;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 CountdownDuration;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 LastRoundWinner;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EWinCondition LastWinCondition;

private:
    TWeakObjectPtr<ALesFightNetworkGameMode> GameMode;
    TArray<int32> RoundHistory;
    bool bMatchInProgress;
    int32 CountdownRemaining;
    FTimerHandle CountdownTimerHandle;

    void BroadcastMatchState();
};
