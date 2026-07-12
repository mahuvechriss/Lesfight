#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightInteractionSystem.generated.h"

class ULesFightArenaWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectDamaged, FName, ObjectID, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnObjectDestroyed, FName, ObjectID, EDestructionLevel, Level);

UCLASS(Blueprintable)
class ULesFightInteractionSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FName RegisterInteractiveObject(AActor* Object, EInteractiveObjectType Type, float Health);

    UFUNCTION(BlueprintCallable)
    bool UnregisterInteractiveObject(FName ObjectID);

    UFUNCTION(BlueprintCallable)
    bool ApplyDamage(FName ObjectID, float Damage, FVector HitLocation, FVector HitForce);

    UFUNCTION(BlueprintCallable)
    FDestructibleObjectState GetObjectState(FName ObjectID) const;

    UFUNCTION(BlueprintCallable)
    TArray<FDestructibleObjectState> GetAllObjectStates() const;

    UFUNCTION(BlueprintCallable)
    TArray<FDestructibleObjectState> GetObjectsOfType(EInteractiveObjectType Type) const;

    UFUNCTION(BlueprintCallable)
    bool IsObjectDestroyed(FName ObjectID) const;

    UFUNCTION(BlueprintCallable)
    int32 GetDestroyedObjectCount() const;

    UFUNCTION(BlueprintCallable)
    void ResetAllObjects();

    UFUNCTION(BlueprintCallable)
    TArray<FDestructibleObjectState> GetInteractionAtLocation(FVector Location, float Radius) const;

    void Initialize(ULesFightArenaWorldManager* InManager);

    UPROPERTY(BlueprintAssignable)
    FOnObjectDamaged OnObjectDamaged;

    UPROPERTY(BlueprintAssignable)
    FOnObjectDestroyed OnObjectDestroyed;

protected:
    UPROPERTY()
    TMap<FName, FDestructibleObjectState> InteractiveObjects;

    UPROPERTY()
    TArray<FName> DestroyedObjects;

    UPROPERTY()
    TMap<EInteractiveObjectType, int32> ObjectCounts;

    UPROPERTY()
    int32 MaxObjects = 100;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;

    int32 NextObjectID = 0;
};
