#include "LesFightDestructibleObject.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "Engine/StaticMesh.h"

void ULesFightDestructibleObject::Initialize(ULesFightArenaWorldManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightDestructibleObject::InitializeDestructible(AActor* InOwnerActor, EInteractiveObjectType Type, float MaxHP)
{
    OwnerActor = InOwnerActor;
    ObjectType = Type;
    MaxHealth = MaxHP;
    CurrentHealth = MaxHP;
    DestructionLevel = EDestructionLevel::None;
    bDestroyed = false;

    if (OwnerActor)
    {
        MeshComponent = OwnerActor->FindComponentByClass<UStaticMeshComponent>();
    }
}

void ULesFightDestructibleObject::TakeDamage(float Damage, FVector HitLocation, FVector Impulse)
{
    if (bDestroyed)
    {
        return;
    }

    CurrentHealth = FMath::Max(0.0f, CurrentHealth - Damage);

    float HealthPercent = MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;

    if (HealthPercent > 0.75f)
    {
        DestructionLevel = EDestructionLevel::None;
    }
    else if (HealthPercent > 0.50f)
    {
        DestructionLevel = EDestructionLevel::Partial;
    }
    else if (HealthPercent > 0.25f)
    {
        DestructionLevel = EDestructionLevel::Heavy;
    }
    else
    {
        DestructionLevel = EDestructionLevel::Total;
    }

    if (CurrentHealth <= 0.0f)
    {
        bDestroyed = true;
        SpawnDebris();
        PlayDestructionEffect();
        OnDestroyed.Broadcast();
    }
}

float ULesFightDestructibleObject::GetCurrentHealth() const
{
    return CurrentHealth;
}

float ULesFightDestructibleObject::GetMaxHealth() const
{
    return MaxHealth;
}

EDestructionLevel ULesFightDestructibleObject::GetDestructionLevel() const
{
    return DestructionLevel;
}

bool ULesFightDestructibleObject::IsDestroyed() const
{
    return bDestroyed;
}

void ULesFightDestructibleObject::Repair()
{
    CurrentHealth = MaxHealth;
    DestructionLevel = EDestructionLevel::None;
    bDestroyed = false;
    DebrisSpawnPoints.Empty();
}

void ULesFightDestructibleObject::SetDestructibleMesh(UStaticMesh* Mesh)
{
    if (MeshComponent)
    {
        MeshComponent->SetStaticMesh(Mesh);
    }
}

void ULesFightDestructibleObject::SpawnDebris()
{
    DebrisSpawnPoints.Empty();

    if (!MeshComponent || !MeshComponent->GetStaticMesh())
    {
        return;
    }

    FBox Bounds = MeshComponent->Bounds.GetBox();
    FVector Center = Bounds.GetCenter();
    FVector Extent = Bounds.GetExtent();

    for (int32 i = 0; i < 8; i++)
    {
        FVector Offset = FVector(
            FMath::RandRange(-Extent.X, Extent.X),
            FMath::RandRange(-Extent.Y, Extent.Y),
            FMath::RandRange(-Extent.Z, Extent.Z)
        );
        DebrisSpawnPoints.Add(Center + Offset);
    }
}

void ULesFightDestructibleObject::PlayDestructionEffect()
{
}
