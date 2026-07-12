#include "LesFightInteractionSystem.h"
#include "Framework/Arena/Data/LesFightArenaData.h"

void ULesFightInteractionSystem::Initialize(ULesFightArenaWorldManager* InManager)
{
    OwnerManager = InManager;
}

FName ULesFightInteractionSystem::RegisterInteractiveObject(AActor* Object, EInteractiveObjectType Type, float Health)
{
    if (!Object || InteractiveObjects.Num() >= MaxObjects)
    {
        return NAME_None;
    }

    FName ObjectID = FName(*FString::Printf(TEXT("Auto_%d"), NextObjectID++));

    FDestructibleObjectState State;
    State.ObjectID = ObjectID;
    State.ObjectType = Type;
    State.Health = Health;
    State.MaxHealth = Health;
    State.DestructionLevel = EDestructionLevel::None;
    State.ObjectTransform = Object->GetTransform();
    State.bIsDestroyed = false;

    InteractiveObjects.Add(ObjectID, State);
    ObjectCounts.FindOrAdd(Type)++;

    return ObjectID;
}

bool ULesFightInteractionSystem::UnregisterInteractiveObject(FName ObjectID)
{
    if (!InteractiveObjects.Contains(ObjectID))
    {
        return false;
    }

    EInteractiveObjectType Type = InteractiveObjects[ObjectID].ObjectType;
    if (ObjectCounts.Contains(Type))
    {
        ObjectCounts[Type]--;
    }

    DestroyedObjects.Remove(ObjectID);
    InteractiveObjects.Remove(ObjectID);

    return true;
}

bool ULesFightInteractionSystem::ApplyDamage(FName ObjectID, float Damage, FVector HitLocation, FVector HitForce)
{
    FDestructibleObjectState* State = InteractiveObjects.Find(ObjectID);
    if (!State || State->bIsDestroyed)
    {
        return false;
    }

    State->Health = FMath::Max(0.0f, State->Health - Damage);
    OnObjectDamaged.Broadcast(ObjectID, Damage);

    float HealthPercent = State->MaxHealth > 0.0f ? State->Health / State->MaxHealth : 0.0f;

    EDestructionLevel NewLevel = EDestructionLevel::None;
    if (HealthPercent > 0.75f)
    {
        NewLevel = EDestructionLevel::None;
    }
    else if (HealthPercent > 0.50f)
    {
        NewLevel = EDestructionLevel::Partial;
    }
    else if (HealthPercent > 0.25f)
    {
        NewLevel = EDestructionLevel::Heavy;
    }
    else
    {
        NewLevel = EDestructionLevel::Total;
    }

    State->DestructionLevel = NewLevel;

    if (State->Health <= 0.0f)
    {
        State->bIsDestroyed = true;
        DestroyedObjects.AddUnique(ObjectID);
        OnObjectDestroyed.Broadcast(ObjectID, NewLevel);
    }

    return true;
}

FDestructibleObjectState ULesFightInteractionSystem::GetObjectState(FName ObjectID) const
{
    if (const FDestructibleObjectState* State = InteractiveObjects.Find(ObjectID))
    {
        return *State;
    }
    return FDestructibleObjectState();
}

TArray<FDestructibleObjectState> ULesFightInteractionSystem::GetAllObjectStates() const
{
    TArray<FDestructibleObjectState> Result;
    InteractiveObjects.GenerateValueArray(Result);
    return Result;
}

TArray<FDestructibleObjectState> ULesFightInteractionSystem::GetObjectsOfType(EInteractiveObjectType Type) const
{
    TArray<FDestructibleObjectState> Result;
    for (const auto& Pair : InteractiveObjects)
    {
        if (Pair.Value.ObjectType == Type)
        {
            Result.Add(Pair.Value);
        }
    }
    return Result;
}

bool ULesFightInteractionSystem::IsObjectDestroyed(FName ObjectID) const
{
    return DestroyedObjects.Contains(ObjectID);
}

int32 ULesFightInteractionSystem::GetDestroyedObjectCount() const
{
    return DestroyedObjects.Num();
}

void ULesFightInteractionSystem::ResetAllObjects()
{
    InteractiveObjects.Empty();
    DestroyedObjects.Empty();
    ObjectCounts.Empty();
}

TArray<FDestructibleObjectState> ULesFightInteractionSystem::GetInteractionAtLocation(FVector Location, float Radius) const
{
    TArray<FDestructibleObjectState> Result;
    float RadiusSq = Radius * Radius;

    for (const auto& Pair : InteractiveObjects)
    {
        float DistSq = FVector::DistSquared(Location, Pair.Value.ObjectTransform.GetLocation());
        if (DistSq <= RadiusSq)
        {
            Result.Add(Pair.Value);
        }
    }
    return Result;
}
