#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightDestructibleObject.generated.h"

class ULesFightArenaWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyed);

UCLASS(Blueprintable)
class ULesFightDestructibleObject : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void InitializeDestructible(AActor* OwnerActor, EInteractiveObjectType Type, float MaxHP);

    UFUNCTION(BlueprintCallable)
    void TakeDamage(float Damage, FVector HitLocation, FVector Impulse);

    UFUNCTION(BlueprintCallable)
    float GetCurrentHealth() const;

    UFUNCTION(BlueprintCallable)
    float GetMaxHealth() const;

    UFUNCTION(BlueprintCallable)
    EDestructionLevel GetDestructionLevel() const;

    UFUNCTION(BlueprintCallable)
    bool IsDestroyed() const;

    UFUNCTION(BlueprintCallable)
    void Repair();

    UFUNCTION(BlueprintCallable)
    void SetDestructibleMesh(UStaticMesh* Mesh);

    UFUNCTION(BlueprintCallable)
    void SpawnDebris();

    UFUNCTION(BlueprintCallable)
    void PlayDestructionEffect();

    void Initialize(ULesFightArenaWorldManager* InManager);

    UPROPERTY(BlueprintAssignable)
    FOnDestroyed OnDestroyed;

protected:
    UPROPERTY()
    float CurrentHealth;

    UPROPERTY()
    float MaxHealth;

    UPROPERTY()
    EDestructionLevel DestructionLevel;

    UPROPERTY()
    bool bDestroyed;

    UPROPERTY()
    EInteractiveObjectType ObjectType;

    UPROPERTY()
    AActor* OwnerActor;

    UPROPERTY()
    UStaticMeshComponent* MeshComponent;

    UPROPERTY()
    TArray<FVector> DebrisSpawnPoints;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
};
