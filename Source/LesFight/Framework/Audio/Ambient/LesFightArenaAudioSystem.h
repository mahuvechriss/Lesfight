#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightArenaAudioSystem.generated.h"

class ULesFightAudioWorldManager;

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
    MAX
};

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    Clear,
    Rain,
    Thunderstorm,
    Windy,
    Foggy,
    Snow,
    MAX
};

UENUM(BlueprintType)
enum class EWeatherIntensity : uint8
{
    None,
    Light,
    Moderate,
    Heavy,
    Extreme,
    MAX
};

UENUM(BlueprintType)
enum class ETerrainType : uint8
{
    Stone,
    Wood,
    Grass,
    Dirt,
    Metal,
    Water,
    Sand,
    Snow,
    Rock,
    MAX
};

UENUM(BlueprintType)
enum class EDestructionLevel : uint8
{
    Minor,
    Moderate,
    Severe,
    Total,
    MAX
};

USTRUCT(BlueprintType)
struct FArenaAudioState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AmbientSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EReverbPreset ReverbPreset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasCrowd = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmbientVolumeModifier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName WeatherOverrideSound;
};

UCLASS(Blueprintable)
class ULesFightArenaAudioSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena")
    void SetArenaAudio(EArenaType ArenaType);

    UFUNCTION(BlueprintCallable, Category = "Arena")
    void ApplyWeatherAudio(EWeatherType Weather, EWeatherIntensity Intensity);

    UFUNCTION(BlueprintCallable, Category = "Arena")
    void PlayArenaFootstep(ETerrainType Surface, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Arena")
    void PlayArenaDestructionSound(EDestructionLevel Level, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Arena")
    void PlayArenaCrowdReaction(FName ReactionType);

    UFUNCTION(BlueprintCallable, Category = "Arena")
    FArenaAudioState GetArenaAudioProfile() const;

protected:
    UPROPERTY()
    FArenaAudioState CurrentArenaAudio;

    UPROPERTY()
    TMap<EArenaType, FArenaAudioState> ArenaAudioProfiles;

    UPROPERTY()
    TMap<EArenaType, FName> ArenaMusicTracks;

private:
    friend class ULesFightAudioWorldManager;

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
