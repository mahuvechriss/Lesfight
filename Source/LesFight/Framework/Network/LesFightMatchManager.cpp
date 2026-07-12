#include "LesFightMatchManager.h"
#include "LesFightNetworkGameMode.h"
#include "Engine/World.h"
#include "TimerManager.h"

ULesFightMatchManager::ULesFightMatchManager()
    : MaxRounds(3)
    , RoundTimeLimit(99.0f)
    , CountdownDuration(3)
    , LastRoundWinner(-1)
    , LastWinCondition(EWinCondition::None)
    , bMatchInProgress(false)
    , CountdownRemaining(0)
{
}

void ULesFightMatchManager::Initialize(ALesFightNetworkGameMode* InGameMode)
{
    GameMode = InGameMode;
    Reset();
}

void ULesFightMatchManager::StartMatch()
{
    if (bMatchInProgress) return;

    bMatchInProgress = true;
    CurrentMatchData.MatchState = ENetworkMatchState::WaitingForPlayers;
    RoundHistory.Empty();
    PlayerRoundWins.Empty();
    BroadcastMatchState();

    StartRound(1);
}

void ULesFightMatchManager::EndMatch(int32 WinnerPlayerIndex)
{
    if (!bMatchInProgress) return;

    bMatchInProgress = false;
    CurrentMatchData.MatchState = ENetworkMatchState::MatchEnd;
    CurrentMatchData.RoundNumber = MaxRounds;
    LastRoundWinner = WinnerPlayerIndex;

    BroadcastMatchState();
    OnMatchEnded.Broadcast(WinnerPlayerIndex);

    UE_LOG(LogLesFightNetwork, Log, TEXT("Match ended. Winner: Player %d"), WinnerPlayerIndex);
}

void ULesFightMatchManager::StartRound(int32 RoundNumber)
{
    CurrentMatchData.MatchState = ENetworkMatchState::CharacterSelect;
    CurrentMatchData.RoundNumber = RoundNumber;
    CurrentMatchData.RoundTimeRemaining = RoundTimeLimit;
    BroadcastMatchState();

    StartCountdown(CountdownDuration);
}

void ULesFightMatchManager::EndRound(int32 WinnerPlayerIndex, EWinCondition WinCondition)
{
    LastRoundWinner = WinnerPlayerIndex;
    LastWinCondition = WinCondition;
    CurrentMatchData.MatchState = ENetworkMatchState::RoundEnd;

    int32& Wins = PlayerRoundWins.FindOrAdd(WinnerPlayerIndex);
    Wins++;

    RoundHistory.Add(WinnerPlayerIndex);

    BroadcastMatchState();
    OnRoundEnded.Broadcast(WinnerPlayerIndex);

    UE_LOG(LogLesFightNetwork, Log, TEXT("Round %d ended. Winner: Player %d (%s)"),
        CurrentMatchData.RoundNumber, WinnerPlayerIndex, *UEnum::GetValueAsString(WinCondition));

    int32 MaxWins = (MaxRounds / 2) + 1;
    if (Wins >= MaxWins)
    {
        EndMatch(WinnerPlayerIndex);
    }
    else if (CurrentMatchData.RoundNumber < MaxRounds)
    {
        StartRound(CurrentMatchData.RoundNumber + 1);
    }
    else
    {
        int32 FinalWinner = -1;
        int32 HighestScore = 0;
        for (const auto& Pair : PlayerRoundWins)
        {
            if (Pair.Value > HighestScore)
            {
                HighestScore = Pair.Value;
                FinalWinner = Pair.Key;
            }
        }
        EndMatch(FinalWinner);
    }
}

void ULesFightMatchManager::StartCountdown(int32 Seconds)
{
    CurrentMatchData.MatchState = ENetworkMatchState::Countdown;
    CountdownRemaining = Seconds;
    BroadcastMatchState();
    OnCountdownStarted.Broadcast();

    FTimerDelegate CountdownDelegate = FTimerDelegate::CreateWeakLambda(this, [this]()
    {
        CountdownRemaining--;
        OnCountdownTick.Broadcast(CountdownRemaining);

        if (CountdownRemaining <= 0)
        {
            CurrentMatchData.MatchState = ENetworkMatchState::RoundInProgress;
            BroadcastMatchState();
            OnRoundStarted.Broadcast(CurrentMatchData.RoundNumber);
        }
    });

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, CountdownDelegate, 1.0f, true);
        OnCountdownTick.Broadcast(CountdownRemaining);
    }
}

void ULesFightMatchManager::SetPlayerReady(int32 PlayerIndex, bool bReady)
{
    PlayerReadyStates.Add(PlayerIndex, bReady);
    OnPlayerReadyChanged.Broadcast(PlayerIndex);
}

bool ULesFightMatchManager::AreAllPlayersReady() const
{
    for (const auto& Pair : PlayerReadyStates)
    {
        if (!Pair.Value) return false;
    }
    return PlayerReadyStates.Num() >= 2;
}

void ULesFightMatchManager::SetRoundTimeLimit(float Seconds)
{
    RoundTimeLimit = FMath::Clamp(Seconds, 10.0f, 999.0f);
}

void ULesFightMatchManager::SetMaxRounds(int32 InMaxRounds)
{
    MaxRounds = FMath::Clamp(InMaxRounds, 1, 9);
}

void ULesFightMatchManager::Reset()
{
    CurrentMatchData = FNetworkMatchData();
    PlayerReadyStates.Empty();
    PlayerRoundWins.Empty();
    RoundHistory.Empty();
    bMatchInProgress = false;
    CountdownRemaining = 0;
    LastRoundWinner = -1;
    LastWinCondition = EWinCondition::None;

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
    }
}

void ULesFightMatchManager::TickRoundTimer(float DeltaTime)
{
    if (CurrentMatchData.MatchState != ENetworkMatchState::RoundInProgress) return;

    CurrentMatchData.RoundTimeRemaining -= DeltaTime;
    OnMatchTimeUpdated.Broadcast(CurrentMatchData.RoundTimeRemaining);

    if (CurrentMatchData.RoundTimeRemaining <= 0.0f)
    {
        CurrentMatchData.RoundTimeRemaining = 0.0f;
        EndRound(-1, EWinCondition::TimeOut);
    }
}

void ULesFightMatchManager::BroadcastMatchState()
{
    OnMatchStateChanged.Broadcast();
}
