#include "LesFightTerrainSystem.h"
#include "Framework/Arena/Data/LesFightArenaData.h"

void ULesFightTerrainSystem::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    CellSize = 100.0f;
    GridOrigin = FVector::ZeroVector;

    SpeedModifiers.Empty();
    SpeedModifiers.Add(ETerrainType::Stone, 1.0f);
    SpeedModifiers.Add(ETerrainType::Wood, 0.95f);
    SpeedModifiers.Add(ETerrainType::Sand, 0.7f);
    SpeedModifiers.Add(ETerrainType::Mud, 0.5f);
    SpeedModifiers.Add(ETerrainType::Water, 0.6f);
    SpeedModifiers.Add(ETerrainType::Grass, 0.9f);
    SpeedModifiers.Add(ETerrainType::Snow, 0.75f);
    SpeedModifiers.Add(ETerrainType::Metal, 1.0f);
    SpeedModifiers.Add(ETerrainType::Concrete, 1.0f);

    FrictionCoefficients.Empty();
    FrictionCoefficients.Add(ETerrainType::Stone, 0.5f);
    FrictionCoefficients.Add(ETerrainType::Wood, 0.6f);
    FrictionCoefficients.Add(ETerrainType::Sand, 0.8f);
    FrictionCoefficients.Add(ETerrainType::Mud, 0.9f);
    FrictionCoefficients.Add(ETerrainType::Water, 0.95f);
    FrictionCoefficients.Add(ETerrainType::Grass, 0.7f);
    FrictionCoefficients.Add(ETerrainType::Snow, 0.7f);
    FrictionCoefficients.Add(ETerrainType::Metal, 0.3f);
    FrictionCoefficients.Add(ETerrainType::Concrete, 0.6f);

    SurfaceMaterials.Empty();
    SurfaceMaterials.Add(ETerrainType::Stone, FName("M_Stone"));
    SurfaceMaterials.Add(ETerrainType::Wood, FName("M_Wood"));
    SurfaceMaterials.Add(ETerrainType::Sand, FName("M_Sand"));
    SurfaceMaterials.Add(ETerrainType::Mud, FName("M_Mud"));
    SurfaceMaterials.Add(ETerrainType::Water, FName("M_Water"));
    SurfaceMaterials.Add(ETerrainType::Grass, FName("M_Grass"));
    SurfaceMaterials.Add(ETerrainType::Snow, FName("M_Snow"));
    SurfaceMaterials.Add(ETerrainType::Metal, FName("M_Metal"));
    SurfaceMaterials.Add(ETerrainType::Concrete, FName("M_Concrete"));

    AvailableTerrains.Empty();
    SpeedModifiers.GenerateKeyArray(AvailableTerrains);
}

void ULesFightTerrainSystem::RegisterTerrainType(ETerrainType Type, FName SurfaceMaterial)
{
    if (!AvailableTerrains.Contains(Type))
    {
        AvailableTerrains.Add(Type);
    }

    SurfaceMaterials.Add(Type, SurfaceMaterial);

    if (!SpeedModifiers.Contains(Type))
    {
        SpeedModifiers.Add(Type, 1.0f);
    }

    if (!FrictionCoefficients.Contains(Type))
    {
        FrictionCoefficients.Add(Type, 0.5f);
    }
}

ETerrainType ULesFightTerrainSystem::GetTerrainAtLocation(FVector WorldLocation) const
{
    if (TerrainGrid.Num() == 0)
    {
        return ETerrainType::Stone;
    }

    FVector Offset = WorldLocation - GridOrigin;
    int32 GridX = FMath::FloorToInt(Offset.X / CellSize);
    int32 GridY = FMath::FloorToInt(Offset.Y / CellSize);

    if (GridY < 0 || GridY >= TerrainGrid.Num())
    {
        return ETerrainType::Stone;
    }

    const TArray<ETerrainType>& Row = TerrainGrid[GridY];
    if (GridX < 0 || GridX >= Row.Num())
    {
        return ETerrainType::Stone;
    }

    return Row[GridX];
}

FName ULesFightTerrainSystem::GetSurfaceMaterial(ETerrainType Type) const
{
    const FName* Material = SurfaceMaterials.Find(Type);
    return Material ? *Material : FName("M_Default");
}

float ULesFightTerrainSystem::GetMovementSpeedModifier(ETerrainType Type) const
{
    const float* Modifier = SpeedModifiers.Find(Type);
    return Modifier ? *Modifier : 1.0f;
}

float ULesFightTerrainSystem::GetFrictionCoefficient(ETerrainType Type) const
{
    const float* Friction = FrictionCoefficients.Find(Type);
    return Friction ? *Friction : 0.5f;
}

TArray<ETerrainType> ULesFightTerrainSystem::GetTerrainList() const
{
    return AvailableTerrains;
}

void ULesFightTerrainSystem::SetTerrainGrid(TArray<TArray<ETerrainType>> Grid, FVector InGridOrigin, float InCellSize)
{
    TerrainGrid = Grid;
    GridOrigin = InGridOrigin;
    CellSize = InCellSize;
}
