#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/TextureCube.h"
#include "LesFightArenaData.generated.h"

UENUM(BlueprintType)
enum class EArenaType : uint8
{
    TempleCourtyard,
    MountainDojo,
    BambooForest,
    AncientVillage,
    PalaceGrounds,
    CityRooftop,
    UndergroundArena,
    IndustrialFactory,
    AbandonedBuilding,
    FloatingIslands,
    MysticForest,
    AncientRuins,
    DragonValley,
    MAX
};

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    Clear,
    Rain,
    Storm,
    Snow,
    Fog,
    Wind,
    Dust,
    MAX
};

UENUM(BlueprintType)
enum class EWeatherIntensity : uint8
{
    Light,
    Moderate,
    Heavy,
    Extreme,
    MAX
};

UENUM(BlueprintType)
enum class ELightingPreset : uint8
{
    SunnyDay,
    Overcast,
    Sunset,
    Night,
    ArenaDefault,
    Dramatic,
    Cyberpunk,
    FantasyGlow,
    MAX
};

UENUM(BlueprintType)
enum class ETerrainType : uint8
{
    Stone,
    Wood,
    Sand,
    Mud,
    Water,
    Grass,
    Snow,
    Metal,
    Concrete,
    MAX
};

UENUM(BlueprintType)
enum class EDestructionLevel : uint8
{
    None,
    Partial,
    Heavy,
    Total,
    MAX
};

UENUM(BlueprintType)
enum class EInteractiveObjectType : uint8
{
    None,
    DestructibleWall,
    BreakableBarrier,
    WoodenCrate,
    StonePillar,
    HangingLamp,
    Furniture,
    RopeBridge,
    WaterBarrel,
    MAX
};

UENUM(BlueprintType)
enum class EArenaEnvironmentCategory : uint8
{
    Ancient,
    Modern,
    Fantasy,
    MAX
};

UENUM(BlueprintType)
enum class ECameraBehavior : uint8
{
    Default,
    Cinematic,
    DynamicCombat,
    Showcase,
    Finisher,
    Intro,
    MAX
};

USTRUCT(BlueprintType)
struct FArenaInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EArenaType ArenaType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EArenaEnvironmentCategory Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ArenaName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ArenaDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LevelPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ThumbnailPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EWeatherType> SupportedWeather;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ELightingPreset> SupportedLighting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ETerrainType> TerrainTypes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EInteractiveObjectType> InteractiveObjects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasDestructibles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ArenaBounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnPoint1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnPoint2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> CameraLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTextureCube> SkyboxTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmbientTemperature;
};

USTRUCT(BlueprintType)
struct FWeatherState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeatherType WeatherType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeatherIntensity Intensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WindSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector WindDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Precipitation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FogDensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor FogColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Visibility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TransitionDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentTransitionTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTransitioning;
};

USTRUCT(BlueprintType)
struct FArenaLightingState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ELightingPreset Preset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor AmbientColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor DirectionalColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector LightDirection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LightIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShadowStrength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShadowResolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCastShadows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableGI;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GIIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReflectionIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UTextureCube> SkyLightCubeMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Temperature;
};

USTRUCT(BlueprintType)
struct FDestructibleObjectState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ObjectID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInteractiveObjectType ObjectType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDestructionLevel DestructionLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransform ObjectTransform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsDestroyed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> DebrisPositions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bReplicated;
};

USTRUCT(BlueprintType)
struct FArenaAudioState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> AmbientSoundPaths;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmbientVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WeatherVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReverbAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EchoDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> FootstepSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<ETerrainType, FString> TerrainFootstepMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> DestructionSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasCrowdSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> CrowdSoundPaths;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CrowdVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MusicTrack;
};

USTRUCT(BlueprintType)
struct FArenaPerformanceMetrics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TriangleCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DrawCalls;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DynamicObjects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DestructibleObjects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EstimatedMemoryMB;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseNanite;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseLumen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExpectedFPS;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LODCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> PerformanceWarnings;
};

USTRUCT(BlueprintType)
struct FArenaEnvironmentState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FArenaInfo CurrentArena;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FWeatherState Weather;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FArenaLightingState Lighting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FArenaAudioState Audio;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FDestructibleObjectState> DestructibleStates;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ETerrainType> SurfaceTypes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeOfDay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ArenaVersion;
};

UCLASS(BlueprintType)
class ULesFightArenaDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    ULesFightArenaDataAsset();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Arenas")
    TMap<EArenaType, FArenaInfo> ArenaDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weather")
    TMap<EWeatherType, FWeatherState> WeatherDefaults;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lighting")
    TMap<ELightingPreset, FArenaLightingState> LightingDefaults;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
    float GlobalDestructibleHealthMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
    float DebrisLifetime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Physics")
    int32 MaxDestructibleObjects;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxDynamicDebris;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxParticleEffects;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    float WeatherUpdateInterval;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Multiplayer")
    float DestructionSyncInterval;
};
