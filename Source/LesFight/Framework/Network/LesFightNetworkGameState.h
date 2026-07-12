#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkGameState.generated.h"

UCLASS(Blueprintable)
class ALesFightNetworkGameState : public AGameState
{
    GENERATED_BODY()

public:
    ALesFightNetworkGameState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void OnMatchStarted();

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void OnMatchEnded(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void OnRoundStarted(int32 RoundNumber);

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void OnRoundEnded(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void OnFullStateSyncRequested();

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void UpdateRoundTimer(float TimeRemaining);

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void UpdatePlayerScore(int32 PlayerIndex, int32 Score);

    UFUNCTION(BlueprintPure, Category = "Network|GameState")
    ENetworkMatchState GetCurrentMatchState() const { return CurrentMatchState; }

    UFUNCTION(BlueprintPure, Category = "Network|GameState")
    int32 GetCurrentRound() const { return CurrentRound; }

    UFUNCTION(BlueprintPure, Category = "Network|GameState")
    float GetRoundTimeRemaining() const { return RoundTimer; }

    UFUNCTION(BlueprintPure, Category = "Network|GameState")
    int32 GetMatchWinnerIndex() const { return MatchWinnerIndex; }

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void SetMaxRounds(int32 InMaxRounds);

    UFUNCTION(BlueprintCallable, Category = "Network|GameState")
    void SetRoundTimeLimit(float InTimeLimit);

    UFUNCTION(BlueprintPure, Category = "Network|GameState")
    int32 GetMaxRounds() const { return MaxRounds; }

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    ENetworkMatchState CurrentMatchState;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 CurrentRound;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    float RoundTimer;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 MatchWinnerIndex;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 MaxRounds;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    float RoundTimeLimit;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 WinnerPlayerIndex;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    TArray<int32> PlayerScores;
};
