#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LesFightPlayerSpawnManager.generated.h"

class ALesFightPlayerCharacter;

USTRUCT(BlueprintType)
struct FPlayerSpawnPoint
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransform SpawnTransform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOccupied;

    FPlayerSpawnPoint()
        : PlayerIndex(-1)
        , bIsOccupied(false)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerSpawned, ALesFightPlayerCharacter*, Player, int32, PlayerIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDespawned, int32, PlayerIndex);

UCLASS()
class ALesFightPlayerSpawnManager : public AActor
{
    GENERATED_BODY()

public:
    ALesFightPlayerSpawnManager();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    ALesFightPlayerCharacter* SpawnPlayer(int32 PlayerIndex, TSubclassOf<ALesFightPlayerCharacter> PlayerClass);

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void DespawnPlayer(int32 PlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void DespawnAllPlayers();

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void RegisterSpawnPoint(const FPlayerSpawnPoint& SpawnPoint);

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void ClearSpawnPoints();

    UFUNCTION(BlueprintPure, Category = "Spawning")
    int32 GetActivePlayerCount() const { return ActivePlayers.Num(); }

    UFUNCTION(BlueprintPure, Category = "Spawning")
    ALesFightPlayerCharacter* GetPlayer(int32 PlayerIndex) const;

    UFUNCTION(BlueprintPure, Category = "Spawning")
    TArray<ALesFightPlayerCharacter*> GetAllPlayers() const { return ActivePlayers; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
    TArray<FPlayerSpawnPoint> SpawnPoints;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerSpawned OnPlayerSpawned;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerDespawned OnPlayerDespawned;

private:
    UPROPERTY()
    TArray<ALesFightPlayerCharacter*> ActivePlayers;

    FPlayerSpawnPoint* FindAvailableSpawnPoint(int32 PlayerIndex);
};
