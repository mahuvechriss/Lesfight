#include "LesFightPlayerSpawnManager.h"
#include "LesFightPlayerCharacter.h"
#include "LesFight.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ALesFightPlayerSpawnManager::ALesFightPlayerSpawnManager()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;
}

void ALesFightPlayerSpawnManager::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogLesFight, Log, TEXT("PlayerSpawnManager initialized with %d spawn points"), SpawnPoints.Num());
}

ALesFightPlayerCharacter* ALesFightPlayerSpawnManager::SpawnPlayer(
    int32 PlayerIndex, TSubclassOf<ALesFightPlayerCharacter> PlayerClass)
{
    if (!PlayerClass || !GetWorld()) return nullptr;

    FPlayerSpawnPoint* SpawnPoint = FindAvailableSpawnPoint(PlayerIndex);
    if (!SpawnPoint)
    {
        UE_LOG(LogLesFight, Warning, TEXT("No available spawn point for player %d"), PlayerIndex);
        return nullptr;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    ALesFightPlayerCharacter* NewPlayer = GetWorld()->SpawnActor<ALesFightPlayerCharacter>(
        PlayerClass, SpawnPoint->SpawnTransform, SpawnParams);

    if (NewPlayer)
    {
        SpawnPoint->bIsOccupied = true;
        SpawnPoint->PlayerIndex = PlayerIndex;
        ActivePlayers.Add(NewPlayer);

        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC && PlayerIndex == 0)
        {
            PC->Possess(NewPlayer);
        }

        OnPlayerSpawned.Broadcast(NewPlayer, PlayerIndex);
        UE_LOG(LogLesFight, Log, TEXT("Spawned player %d at spawn point"), PlayerIndex);
    }

    return NewPlayer;
}

void ALesFightPlayerSpawnManager::DespawnPlayer(int32 PlayerIndex)
{
    ALesFightPlayerCharacter* Player = GetPlayer(PlayerIndex);
    if (Player)
    {
        ActivePlayers.Remove(Player);
        Player->Destroy();
        OnPlayerDespawned.Broadcast(PlayerIndex);

        for (FPlayerSpawnPoint& SpawnPoint : SpawnPoints)
        {
            if (SpawnPoint.PlayerIndex == PlayerIndex)
            {
                SpawnPoint.bIsOccupied = false;
                SpawnPoint.PlayerIndex = -1;
                break;
            }
        }
    }
}

void ALesFightPlayerSpawnManager::DespawnAllPlayers()
{
    for (int32 i = ActivePlayers.Num() - 1; i >= 0; i--)
    {
        if (ActivePlayers[i])
        {
            int32 PlayerIdx = i;
            ActivePlayers[i]->Destroy();
            OnPlayerDespawned.Broadcast(PlayerIdx);
        }
    }
    ActivePlayers.Empty();

    for (FPlayerSpawnPoint& SpawnPoint : SpawnPoints)
    {
        SpawnPoint.bIsOccupied = false;
        SpawnPoint.PlayerIndex = -1;
    }
}

void ALesFightPlayerSpawnManager::RegisterSpawnPoint(const FPlayerSpawnPoint& SpawnPoint)
{
    SpawnPoints.Add(SpawnPoint);
}

void ALesFightPlayerSpawnManager::ClearSpawnPoints()
{
    SpawnPoints.Empty();
}

ALesFightPlayerCharacter* ALesFightPlayerSpawnManager::GetPlayer(int32 PlayerIndex) const
{
    int32 Idx = 0;
    for (ALesFightPlayerCharacter* Player : ActivePlayers)
    {
        if (Idx == PlayerIndex)
            return Player;
        Idx++;
    }
    return nullptr;
}

FPlayerSpawnPoint* ALesFightPlayerSpawnManager::FindAvailableSpawnPoint(int32 PlayerIndex)
{
    for (FPlayerSpawnPoint& Point : SpawnPoints)
    {
        if (!Point.bIsOccupied)
            return &Point;
    }
    return nullptr;
}
