#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Sound/SoundCue.h"
#include "LesFightAudioData.generated.h"

UENUM(BlueprintType)
enum class EAudioBusType : uint8
{
    Master,
    Music,
    SFX,
    Voice,
    Ambient,
    Cinematic,
    UI,
    MAX
};

UENUM(BlueprintType)
enum class EMusicState : uint8
{
    Menu,
    CharacterSelect,
    ArenaIntro,
    FightNeutral,
    FightLowIntensity,
    FightMediumIntensity,
    FightHighIntensity,
    FightCritical,
    PlayerAdvantage,
    PlayerDisadvantage,
    UltimateReady,
    FinalHit,
    Victory,
    Defeat,
    MAX
};

UENUM(BlueprintType)
enum class ECombatSoundType : uint8
{
    LightPunch,
    HeavyPunch,
    LightKick,
    HeavyKick,
    SpecialAttack,
    UltimateAttack,
    BodyImpact,
    BlockImpact,
    GroundImpact,
    WallImpact,
    CounterImpact,
    Knockdown,
    GetUp,
    MAX
};

UENUM(BlueprintType)
enum class EMovementSoundType : uint8
{
    Footstep,
    Slide,
    Dodge,
    Landing,
    Jump,
    Run,
    Dash,
    Backstep,
    MAX
};

UENUM(BlueprintType)
enum class EVoiceContext : uint8
{
    Taunt,
    Pain,
    Victory,
    Defeat,
    UltimateCall,
    SpecialCall,
    HitReaction,
    CombatCall,
    Entrance,
    MAX
};

UENUM(BlueprintType)
enum class EReverbPreset : uint8
{
    None,
    SmallRoom,
    MediumRoom,
    LargeRoom,
    Cathedral,
    Arena,
    Outdoor,
    Underground,
    MAX
};

UENUM(BlueprintType)
enum class EAudioFadeType : uint8
{
    Linear,
    Logarithmic,
    Exponential,
    Sinusoidal,
    MAX
};

UENUM(BlueprintType)
enum class EAudioLayerType : uint8
{
    Rhythm,
    Bass,
    Melody,
    Harmony,
    Percussion,
    Vocals,
    FX,
    MAX
};

UENUM(BlueprintType)
enum class EFighterMusicRole : uint8
{
    Player1,
    Player2,
    Spectator,
    MAX
};

USTRUCT(BlueprintType)
struct FMusicLayerState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAudioLayerType Layer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Volume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TargetVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FadeDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentFadeTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SoundWaveName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MetaSoundPath;
};

USTRUCT(BlueprintType)
struct FMusicStateData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMusicState State;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ThemeName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EAudioLayerType, FMusicLayerState> Layers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Intensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TransitionDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BeatsPerMinute;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MusicalKey;
};

USTRUCT(BlueprintType)
struct FCombatSoundDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECombatSoundType SoundType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> SoundPaths;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VolumeMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PitchVariation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChanceToPlay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUse3DSpatialization;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttenuationDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> MetaSoundVariations;
};

USTRUCT(BlueprintType)
struct FCharacterVoicePack
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName VoicePackName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EVoiceContext, TArray<FString>> VoiceLines;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BasePitch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> TauntLines;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Language;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 VoicePackPriority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsAIVoice;
};

USTRUCT(BlueprintType)
struct FAudioSettingsData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MasterVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MusicVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SFXVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VoiceVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AmbientVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float UIVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ControllerSpeakerVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableSurroundSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableSubtitles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveOutputDevice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AudioLanguage;
};

USTRUCT(BlueprintType)
struct FAudioPerformanceStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveVoices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveMusicLayers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveReverbZones;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EstimatedAudioMemoryMB;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AudioCPUUsage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SoundPoolSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ActiveSoundNames;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> PerformanceWarnings;
};

USTRUCT(BlueprintType)
struct FReverbZoneData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ZoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EReverbPreset Preset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ZoneCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ZoneRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WetLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DryLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DecayTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PreDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Diffusion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HFReference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnabled;
};

USTRUCT(BlueprintType)
struct FAudioEventData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EventType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EventTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector EventLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TWeakObjectPtr<AActor> EventInstigator;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, float> EventParams;
};

UCLASS(BlueprintType)
class ULesFightAudioDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    ULesFightAudioDataAsset();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Music")
    TMap<EMusicState, FMusicStateData> MusicStateDefaults;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    TMap<ECombatSoundType, FCombatSoundDef> CombatSoundDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
    TMap<EMovementSoundType, FCombatSoundDef> MovementSoundDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Voice")
    TMap<FName, FCharacterVoicePack> VoicePackDatabase;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reverb")
    TMap<EReverbPreset, FReverbZoneData> ReverbPresets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
    FAudioSettingsData DefaultSettings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxConcurrentSounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxConcurrentVoices;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxMusicLayers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    float AudioPoolSizeMB;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MetaSounds")
    bool bEnableMetaSounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spatial")
    float DefaultAttenuationDistance;
};
