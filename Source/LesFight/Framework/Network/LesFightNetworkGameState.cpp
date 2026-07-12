#include "LesFightNetworkGameState.h"
#include "Net/UnrealNetwork.h"

ALesFightNetworkGameState::ALesFightNetworkGameState()
    : CurrentMatchState(ENetworkMatchState::None)
    , CurrentRound(0)
    , RoundTimer(0.0f)
    , MatchWinnerIndex(-1)
    , MaxRounds(3)
    , RoundTimeLimit(99.0f)
    , WinnerPlayerIndex(-1)
{
    bReplicates = true;
    bAlwaysRelevant = true;
}

void ALesFightNetworkGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALesFightNetworkGameState, CurrentMatchState);
    DOREPLIFETIME(ALesFightNetworkGameState, CurrentRound);
    DOREPLIFETIME(ALesFightNetworkGameState, RoundTimer);
    DOREPLIFETIME(ALesFightNetworkGameState, MatchWinnerIndex);
    DOREPLIFETIME(ALesFightNetworkGameState, MaxRounds);
    DOREPLIFETIME(ALesFightNetworkGameState, RoundTimeLimit);
    DOREPLIFETIME(ALesFightNetworkGameState, WinnerPlayerIndex);
    DOREPLIFETIME(ALesFightNetworkGameState, PlayerScores);
}

void ALesFightNetworkGameState::OnMatchStarted()
{
    CurrentMatchState = ENetworkMatchState::WaitingForPlayers;
    CurrentRound = 1;
    MatchWinnerIndex = -1;
    PlayerScores.Empty();
    PlayerScores.Add(0);
    PlayerScores.Add(0);
}

void ALesFightNetworkGameState::OnMatchEnded(int32 WinnerIndex)
{
    CurrentMatchState = ENetworkMatchState::MatchEnd;
    MatchWinnerIndex = WinnerIndex;
}

void ALesFightNetworkGameState::OnRoundStarted(int32 RoundNumber)
{
    CurrentMatchState = ENetworkMatchState::Countdown;
    CurrentRound = RoundNumber;
    RoundTimer = RoundTimeLimit;
}

void ALesFightNetworkGameState::OnRoundEnded(int32 WinnerIndex)
{
    CurrentMatchState = ENetworkMatchState::RoundEnd;
    WinnerPlayerIndex = WinnerIndex;

    if (WinnerIndex >= 0 && WinnerIndex < PlayerScores.Num())
    {
        PlayerScores[WinnerIndex]++;
    }
}

void ALesFightNetworkGameState::OnFullStateSyncRequested()
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("Full state sync requested"));
}

void ALesFightNetworkGameState::UpdateRoundTimer(float TimeRemaining)
{
    RoundTimer = TimeRemaining;
}

void ALesFightNetworkGameState::UpdatePlayerScore(int32 PlayerIndex, int32 Score)
{
    if (PlayerIndex >= 0 && PlayerIndex < PlayerScores.Num())
    {
        PlayerScores[PlayerIndex] = Score;
    }
}

void ALesFightNetworkGameState::SetMaxRounds(int32 InMaxRounds)
{
    MaxRounds = FMath::Clamp(InMaxRounds, 1, 9);
}

void ALesFightNetworkGameState::SetRoundTimeLimit(float InTimeLimit)
{
    RoundTimeLimit = FMath::Clamp(InTimeLimit, 10.0f, 999.0f);
}
