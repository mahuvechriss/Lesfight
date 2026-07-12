#include "LesFightArenaDataSystem.h"
#include "Framework/Arena/Data/LesFightArenaData.h"

void ULesFightArenaDataSystem::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    DatabasePath = TEXT("/Game/Arenas/");
}

void ULesFightArenaDataSystem::LoadArenaDatabase()
{
    ArenaDatabase.Empty();
    ArenaList.Empty();

    auto AddArena = [&](EArenaType Type, EArenaEnvironmentCategory Category, const FString& Name, const FString& Desc, const TArray<EWeatherType>& Weather, const TArray<ELightingPreset>& Lighting, const TArray<ETerrainType>& Terrain, const FVector& Bounds, const FVector& S1, const FVector& S2)
    {
        FArenaInfo Info = BuildDefaultArenaInfo(Type, Category, Name, Desc, Weather, Lighting, Terrain, Bounds, S1, S2);
        ArenaDatabase.Add(Type, Info);
        ArenaList.Add(Type);
    };

    AddArena(EArenaType::TempleCourtyard, EArenaEnvironmentCategory::Ancient,
        TEXT("Temple Courtyard"), TEXT("An ancient temple courtyard with stone pathways and wooden structures."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Fog},
        {ELightingPreset::SunnyDay, ELightingPreset::Overcast, ELightingPreset::Sunset},
        {ETerrainType::Stone, ETerrainType::Wood},
        FVector(4000, 4000, 2000), FVector(-1500, -1500, 100), FVector(1500, 1500, 100));

    AddArena(EArenaType::MountainDojo, EArenaEnvironmentCategory::Ancient,
        TEXT("Mountain Dojo"), TEXT("A secluded dojo high in the mountains, surrounded by wooden training structures."),
        {EWeatherType::Clear, EWeatherType::Snow, EWeatherType::Fog},
        {ELightingPreset::SunnyDay, ELightingPreset::Overcast, ELightingPreset::Sunset, ELightingPreset::Dramatic},
        {ETerrainType::Wood, ETerrainType::Stone},
        FVector(3500, 3500, 1800), FVector(-1200, -1200, 100), FVector(1200, 1200, 100));

    AddArena(EArenaType::BambooForest, EArenaEnvironmentCategory::Ancient,
        TEXT("Bamboo Forest"), TEXT("A dense bamboo forest with grass and dirt terrain."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Fog, EWeatherType::Wind},
        {ELightingPreset::SunnyDay, ELightingPreset::Overcast, ELightingPreset::FantasyGlow},
        {ETerrainType::Grass, ETerrainType::Mud},
        FVector(5000, 5000, 1500), FVector(-2000, -2000, 100), FVector(2000, 2000, 100));

    AddArena(EArenaType::AncientVillage, EArenaEnvironmentCategory::Ancient,
        TEXT("Ancient Village"), TEXT("An abandoned ancient village with stone and dirt pathways."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Fog, EWeatherType::Dust},
        {ELightingPreset::SunnyDay, ELightingPreset::Overcast, ELightingPreset::Sunset},
        {ETerrainType::Stone, ETerrainType::Mud},
        FVector(4500, 4500, 1800), FVector(-1800, -1800, 100), FVector(1800, 1800, 100));

    AddArena(EArenaType::PalaceGrounds, EArenaEnvironmentCategory::Ancient,
        TEXT("Palace Grounds"), TEXT("Grand palace grounds with opulent stone architecture."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Snow, EWeatherType::Fog},
        {ELightingPreset::SunnyDay, ELightingPreset::Sunset, ELightingPreset::Night, ELightingPreset::Dramatic},
        {ETerrainType::Stone},
        FVector(6000, 6000, 2500), FVector(-2500, -2500, 100), FVector(2500, 2500, 100));

    AddArena(EArenaType::CityRooftop, EArenaEnvironmentCategory::Modern,
        TEXT("City Rooftop"), TEXT("A neon-lit city rooftop with metal and concrete surfaces."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Fog, EWeatherType::Wind},
        {ELightingPreset::Night, ELightingPreset::Sunset, ELightingPreset::Cyberpunk, ELightingPreset::Dramatic},
        {ETerrainType::Metal, ETerrainType::Concrete},
        FVector(3000, 3000, 1200), FVector(-1000, -1000, 100), FVector(1000, 1000, 100));

    AddArena(EArenaType::UndergroundArena, EArenaEnvironmentCategory::Modern,
        TEXT("Underground Arena"), TEXT("A gritty underground fighting pit with concrete walls."),
        {EWeatherType::Clear, EWeatherType::Fog, EWeatherType::Dust},
        {ELightingPreset::Overcast, ELightingPreset::Dramatic, ELightingPreset::Cyberpunk},
        {ETerrainType::Concrete},
        FVector(2500, 2500, 1000), FVector(-800, -800, 100), FVector(800, 800, 100));

    AddArena(EArenaType::IndustrialFactory, EArenaEnvironmentCategory::Modern,
        TEXT("Industrial Factory"), TEXT("An abandoned industrial factory with metal and concrete structures."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Fog, EWeatherType::Dust},
        {ELightingPreset::Overcast, ELightingPreset::Sunset, ELightingPreset::Dramatic},
        {ETerrainType::Metal, ETerrainType::Concrete},
        FVector(5000, 4000, 2000), FVector(-2000, -1500, 100), FVector(2000, 1500, 100));

    AddArena(EArenaType::AbandonedBuilding, EArenaEnvironmentCategory::Modern,
        TEXT("Abandoned Building"), TEXT("A crumbling abandoned building with concrete floors and wooden debris."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Fog, EWeatherType::Wind},
        {ELightingPreset::Overcast, ELightingPreset::Night, ELightingPreset::Dramatic},
        {ETerrainType::Concrete, ETerrainType::Wood},
        FVector(3500, 3500, 1500), FVector(-1400, -1400, 100), FVector(1400, 1400, 100));

    AddArena(EArenaType::FloatingIslands, EArenaEnvironmentCategory::Fantasy,
        TEXT("Floating Islands"), TEXT("Magical floating islands suspended in the sky with stone and grass terrain."),
        {EWeatherType::Clear, EWeatherType::Wind, EWeatherType::Fog},
        {ELightingPreset::SunnyDay, ELightingPreset::Sunset, ELightingPreset::FantasyGlow, ELightingPreset::Dramatic},
        {ETerrainType::Stone, ETerrainType::Grass},
        FVector(5500, 5500, 3000), FVector(-2200, -2200, 200), FVector(2200, 2200, 200));

    AddArena(EArenaType::MysticForest, EArenaEnvironmentCategory::Fantasy,
        TEXT("Mystic Forest"), TEXT("An enchanted forest filled with mystical energy, grass and dirt underfoot."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Fog, EWeatherType::Wind},
        {ELightingPreset::Overcast, ELightingPreset::Night, ELightingPreset::FantasyGlow},
        {ETerrainType::Grass, ETerrainType::Mud},
        FVector(4800, 4800, 1600), FVector(-1900, -1900, 100), FVector(1900, 1900, 100));

    AddArena(EArenaType::AncientRuins, EArenaEnvironmentCategory::Fantasy,
        TEXT("Ancient Ruins"), TEXT("Remains of an ancient civilization with crumbling stone structures."),
        {EWeatherType::Clear, EWeatherType::Fog, EWeatherType::Dust, EWeatherType::Storm},
        {ELightingPreset::SunnyDay, ELightingPreset::Sunset, ELightingPreset::Night, ELightingPreset::Dramatic, ELightingPreset::FantasyGlow},
        {ETerrainType::Stone},
        FVector(4200, 4200, 1800), FVector(-1600, -1600, 100), FVector(1600, 1600, 100));

    AddArena(EArenaType::DragonValley, EArenaEnvironmentCategory::Fantasy,
        TEXT("Dragon Valley"), TEXT("A mythical valley where dragons once roamed, with stone outcroppings and grassy fields."),
        {EWeatherType::Clear, EWeatherType::Rain, EWeatherType::Storm, EWeatherType::Fog, EWeatherType::Wind},
        {ELightingPreset::SunnyDay, ELightingPreset::Sunset, ELightingPreset::Dramatic, ELightingPreset::FantasyGlow},
        {ETerrainType::Stone, ETerrainType::Grass},
        FVector(7000, 6000, 2200), FVector(-2800, -2400, 100), FVector(2800, 2400, 100));
}

void ULesFightArenaDataSystem::RegisterArena(const FArenaInfo& Info)
{
    if (Info.ArenaType != EArenaType::MAX)
    {
        ArenaDatabase.Add(Info.ArenaType, Info);
        ArenaList.AddUnique(Info.ArenaType);
    }
}

FArenaInfo ULesFightArenaDataSystem::GetArenaInfo(EArenaType Type) const
{
    const FArenaInfo* Info = ArenaDatabase.Find(Type);
    if (Info)
    {
        return *Info;
    }
    return FArenaInfo();
}

TArray<FArenaInfo> ULesFightArenaDataSystem::GetAllArenaInfos() const
{
    TArray<FArenaInfo> Result;
    ArenaDatabase.GenerateValueArray(Result);
    return Result;
}

TArray<FArenaInfo> ULesFightArenaDataSystem::GetArenasByCategory(EArenaEnvironmentCategory Category) const
{
    TArray<FArenaInfo> Result;
    for (const auto& Pair : ArenaDatabase)
    {
        if (Pair.Value.Category == Category)
        {
            Result.Add(Pair.Value);
        }
    }
    return Result;
}

EArenaType ULesFightArenaDataSystem::GetRandomArena() const
{
    if (ArenaList.Num() == 0)
    {
        return EArenaType::MAX;
    }
    int32 Index = FMath::RandRange(0, ArenaList.Num() - 1);
    return ArenaList[Index];
}

int32 ULesFightArenaDataSystem::GetArenaCount() const
{
    return ArenaDatabase.Num();
}

TArray<FString> ULesFightArenaDataSystem::GetArenaNames() const
{
    TArray<FString> Names;
    for (const auto& Pair : ArenaDatabase)
    {
        Names.Add(Pair.Value.ArenaName);
    }
    return Names;
}

FArenaInfo ULesFightArenaDataSystem::BuildDefaultArenaInfo(EArenaType Type, EArenaEnvironmentCategory Category, const FString& Name, const FString& Description, const TArray<EWeatherType>& Weather, const TArray<ELightingPreset>& Lighting, const TArray<ETerrainType>& Terrain, const FVector& Bounds, const FVector& Spawn1, const FVector& Spawn2) const
{
    FArenaInfo Info;
    Info.ArenaType = Type;
    Info.Category = Category;
    Info.ArenaName = Name;
    Info.ArenaDescription = Description;
    Info.LevelPath = DatabasePath + Name;
    Info.ThumbnailPath = TEXT("/Game/Textures/ArenaThumbnails/") + Name;
    Info.SupportedWeather = Weather;
    Info.SupportedLighting = Lighting;
    Info.TerrainTypes = Terrain;
    Info.ArenaBounds = Bounds;
    Info.SpawnPoint1 = Spawn1;
    Info.SpawnPoint2 = Spawn2;
    Info.bHasDestructibles = true;
    Info.AmbientTemperature = 22.0f;
    return Info;
}
