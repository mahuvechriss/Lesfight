#include "LesFightConnectionManager.h"
#include "LesFightMultiplayerManager.h"

ULesFightConnectionManager::ULesFightConnectionManager()
    : TimeoutDuration(15.0f)
    , ConnectionQuality(EConnectionQuality::Excellent)
    , LastPingUpdateTime(0.0f)
{
}

void ULesFightConnectionManager::Initialize(ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
    ConnectedPlayers.Empty();
    PlayerPings.Empty();
    PlayerLastSeenTime.Empty();
    DisconnectedPlayersSet.Empty();
    ConnectionQuality = EConnectionQuality::Excellent;
}

void ULesFightConnectionManager::Tick(float DeltaTime)
{
    if (!MultiplayerManager.IsValid()) return;

    float CurrentTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    LastPingUpdateTime += DeltaTime;

    if (LastPingUpdateTime >= 1.0f)
    {
        LastPingUpdateTime = 0.0f;
        CheckForTimeouts(CurrentTime);

        int32 TotalPing = 0;
        int32 PlayerCount = 0;
        for (const auto& Pair : PlayerPings)
        {
            TotalPing += Pair.Value;
            PlayerCount++;
        }

        if (PlayerCount > 0)
        {
            EConnectionQuality NewQuality = CalculateConnectionQuality(TotalPing / PlayerCount);
            if (NewQuality != ConnectionQuality)
            {
                ConnectionQuality = NewQuality;
                OnConnectionQualityChanged.Broadcast(NewQuality, TotalPing / PlayerCount);
            }
        }
    }
}

void ULesFightConnectionManager::UpdatePingForPlayer(int32 PlayerIndex, int32 PingMs)
{
    PlayerPings.Add(PlayerIndex, PingMs);
    PlayerLastSeenTime.Add(PlayerIndex, GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f);
    if (DisconnectedPlayersSet.Contains(PlayerIndex))
    {
        DisconnectedPlayersSet.Remove(PlayerIndex);
    }
}

void ULesFightConnectionManager::ReportPlayerConnected(int32 PlayerIndex, const FString& PlayerName)
{
    FNetworkPlayerInfo Info;
    Info.PlayerIndex = PlayerIndex;
    Info.PlayerName = PlayerName;
    Info.bIsConnected = true;
    Info.PingMs = 0;
    Info.Role = ENetworkPlayerRole::Client;

    ConnectedPlayers.Add(Info);
    PlayerLastSeenTime.Add(PlayerIndex, GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f);
    DisconnectedPlayersSet.Remove(PlayerIndex);

    OnPlayerConnected.Broadcast(PlayerIndex, PlayerName);
    UE_LOG(LogLesFightNetwork, Log, TEXT("Player connected: %s (Index: %d)"), *PlayerName, PlayerIndex);
}

void ULesFightConnectionManager::ReportPlayerDisconnected(int32 PlayerIndex)
{
    DisconnectedPlayersSet.Add(PlayerIndex);

    for (int32 i = 0; i < ConnectedPlayers.Num(); i++)
    {
        if (ConnectedPlayers[i].PlayerIndex == PlayerIndex)
        {
            ConnectedPlayers[i].bIsConnected = false;
            break;
        }
    }

    OnPlayerDisconnected.Broadcast(PlayerIndex);
    UE_LOG(LogLesFightNetwork, Warning, TEXT("Player disconnected: Index %d"), PlayerIndex);
}

void ULesFightConnectionManager::SetConnectionTimeout(float Seconds)
{
    TimeoutDuration = FMath::Max(5.0f, Seconds);
}

bool ULesFightConnectionManager::IsPlayerConnected(int32 PlayerIndex) const
{
    return !DisconnectedPlayersSet.Contains(PlayerIndex);
}

bool ULesFightConnectionManager::AreAllPlayersConnected() const
{
    return DisconnectedPlayersSet.Num() == 0 && ConnectedPlayers.Num() > 0;
}

TArray<int32> ULesFightConnectionManager::GetDisconnectedPlayers() const
{
    TArray<int32> Result;
    for (int32 Id : DisconnectedPlayersSet)
    {
        Result.Add(Id);
    }
    return Result;
}

int32 ULesFightConnectionManager::GetPlayerPingMs(int32 PlayerIndex) const
{
    const int32* Found = PlayerPings.Find(PlayerIndex);
    return Found ? *Found : 0;
}

void ULesFightConnectionManager::ForceDisconnect(int32 PlayerIndex)
{
    ReportPlayerDisconnected(PlayerIndex);
}

void ULesFightConnectionManager::Reset()
{
    ConnectedPlayers.Empty();
    PlayerPings.Empty();
    PlayerLastSeenTime.Empty();
    DisconnectedPlayersSet.Empty();
    ConnectionQuality = EConnectionQuality::Excellent;
    LastPingUpdateTime = 0.0f;
}

EConnectionQuality ULesFightConnectionManager::CalculateConnectionQuality(int32 AvgPingMs) const
{
    if (AvgPingMs < 30) return EConnectionQuality::Excellent;
    if (AvgPingMs < 80) return EConnectionQuality::Good;
    if (AvgPingMs < 150) return EConnectionQuality::Fair;
    if (AvgPingMs < 300) return EConnectionQuality::Poor;
    return EConnectionQuality::Lost;
}

void ULesFightConnectionManager::CheckForTimeouts(float CurrentTime)
{
    TArray<int32> TimedOutPlayers;
    for (const auto& Pair : PlayerLastSeenTime)
    {
        if (DisconnectedPlayersSet.Contains(Pair.Key)) continue;
        if ((CurrentTime - Pair.Value) > TimeoutDuration)
        {
            TimedOutPlayers.Add(Pair.Key);
        }
    }

    for (int32 PlayerIdx : TimedOutPlayers)
    {
        ReportPlayerDisconnected(PlayerIdx);
        OnConnectionTimedOut.Broadcast(PlayerIdx);
    }
}
