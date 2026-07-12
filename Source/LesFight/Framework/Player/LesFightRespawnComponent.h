#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightRespawnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRespawnStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRespawnComplete);

UENUM(BlueprintType)
enum class ERespawnState : uint8
{
    None,
    Waiting,
    Spawning,
    Complete
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightRespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightRespawnComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Respawn")
    void StartRespawn(float Delay = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "Respawn")
    void CancelRespawn();

    UFUNCTION(BlueprintPure, Category = "Respawn")
    bool IsRespawning() const { return RespawnState != ERespawnState::None; }

    UFUNCTION(BlueprintPure, Category = "Respawn")
    float GetRespawnTimeRemaining() const { return RespawnTimeRemaining; }

    UFUNCTION(BlueprintPure, Category = "Respawn")
    ERespawnState GetRespawnState() const { return RespawnState; }

    UFUNCTION(BlueprintCallable, Category = "Respawn")
    void SetRespawnLocation(const FVector& Location) { RespawnLocation = Location; }

    UFUNCTION(BlueprintCallable, Category = "Respawn")
    void SetRespawnRotation(const FRotator& Rotation) { RespawnRotation = Rotation; }

    UFUNCTION(BlueprintCallable, Category = "Respawn")
    void SetMaxRespawns(int32 Max) { MaxRespawns = Max; }

    UFUNCTION(BlueprintPure, Category = "Respawn")
    int32 GetRemainingRespawns() const { return MaxRespawns - RespawnCount; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Respawn")
    float DefaultRespawnDelay;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Respawn")
    int32 MaxRespawns;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRespawnStarted OnRespawnStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRespawnComplete OnRespawnComplete;

private:
    ERespawnState RespawnState;
    float RespawnTimeRemaining;
    float RespawnDelay;
    FVector RespawnLocation;
    FRotator RespawnRotation;
    int32 RespawnCount;

    class ALesFightPlayerSpawnManager* GetSpawnManager() const;
    void PerformRespawn();
};
