#include "Framework/Arena/Effects/LesFightDebrisSystem.h"
#include "Engine/StaticMesh.h"

void ULesFightDebrisSystem::Initialize()
{
    DebrisMeshPaths.Add(TEXT("/Game/Meshes/Debris/Debris_Stone_01"));
    DebrisMeshPaths.Add(TEXT("/Game/Meshes/Debris/Debris_Stone_02"));
    DebrisMeshPaths.Add(TEXT("/Game/Meshes/Debris/Debris_Wood_01"));
    DebrisMeshPaths.Add(TEXT("/Game/Meshes/Debris/Debris_Wood_02"));
    DebrisMeshPaths.Add(TEXT("/Game/Meshes/Debris/Debris_Metal_01"));
}

void ULesFightDebrisSystem::SpawnDebris(FVector Location, int32 Count, FVector Spread)
{
    for (int32 i = 0; i < Count && DebrisLocations.Num() < MaxDebris; ++i)
    {
        FVector Offset(
            FMath::RandRange(-Spread.X, Spread.X),
            FMath::RandRange(-Spread.Y, Spread.Y),
            FMath::RandRange(-Spread.Z, Spread.Z)
        );
        DebrisLocations.Add(Location + Offset);
        DebrisTimers.Add(DebrisLifetime);
    }
}

void ULesFightDebrisSystem::SpawnDebrisFromMesh(FVector Location, UStaticMesh* SourceMesh, int32 FragmentCount)
{
    if (!SourceMesh)
    {
        return;
    }

    FBoxSphereBounds MeshBounds = SourceMesh->GetBounds();
    FVector Spread = MeshBounds.BoxExtent * 0.5f;

    SpawnDebris(Location, FragmentCount, Spread);
}

int32 ULesFightDebrisSystem::GetActiveDebrisCount() const
{
    return DebrisLocations.Num();
}

void ULesFightDebrisSystem::SetMaxDebris(int32 Max)
{
    MaxDebris = Max;
}

void ULesFightDebrisSystem::CleanupExpiredDebris()
{
    for (int32 i = DebrisTimers.Num() - 1; i >= 0; --i)
    {
        if (DebrisTimers[i] <= 0.0f)
        {
            DebrisTimers.RemoveAt(i);
            DebrisLocations.RemoveAt(i);
        }
    }
}

void ULesFightDebrisSystem::ClearAllDebris()
{
    DebrisLocations.Empty();
    DebrisTimers.Empty();
}

void ULesFightDebrisSystem::SetDebrisLifetime(float Seconds)
{
    DebrisLifetime = Seconds;
}
