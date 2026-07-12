#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraSystem.h"
#include "LesFightVFXData.generated.h"

UENUM(BlueprintType)
enum class EImpactVFXType : uint8
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
enum class EMotionVFXType : uint8
{
    PunchTrail,
    KickTrail,
    DodgeTrail,
    DashTrail,
    SpeedLines,
    Afterimage,
    AirDistortion,
    MAX
};

UENUM(BlueprintType)
enum class ECharacterAuraType : uint8
{
    None,
    PowerAura,
    UltimateCharge,
    LowHealth,
    Victory,
    Entrance,
    MAX
};

UENUM(BlueprintType)
enum class ECinematicVFXEvent : uint8
{
    RoundStart,
    RoundEnd,
    UltimateStart,
    UltimateHit,
    FinisherStart,
    FinisherHit,
    Knockdown,
    Victory,
    Defeat,
    DramaticPause,
    MAX
};

UENUM(BlueprintType)
enum class EPostProcessingPreset : uint8
{
    Default,
    Combat,
    Cinematic,
    SlowMotion,
    Ultimate,
    LowHealth,
    Victory,
    Defeat,
    MAX
};

UENUM(BlueprintType)
enum class EVFXQualityLevel : uint8
{
    Low,
    Medium,
    High,
    Ultra,
    MAX
};

UENUM(BlueprintType)
enum class EWaveType : uint8
{
    Shockwave,
    DustRing,
    EnergyWave,
    PressureWave,
    MAX
};

UENUM(BlueprintType)
enum class ETrailType : uint8
{
    MotionBlur,
    GhostTrail,
    ParticleTrail,
    RibbonTrail,
    MAX
};

UENUM(BlueprintType)
enum class EVFXStyleMode : uint8
{
    Realistic,
    Fantasy,
    Cinematic,
    MAX
};

USTRUCT(BlueprintType)
struct FImpactVFXDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EImpactVFXType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UNiagaraSystem> NiagaraSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Scale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Lifetime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAttachedToCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseDecal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UMaterialInterface> DecalMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DecalSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> NiagaraAssetPaths;
};

USTRUCT(BlueprintType)
struct FCharacterAuraDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECharacterAuraType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UNiagaraSystem> AuraSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor AuraColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AuraIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AuraRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPulsating;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PulseSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EFightingStyle, FLinearColor> StyleColorOverrides;
};

USTRUCT(BlueprintType)
struct FPostProcessingState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPostProcessingPreset Preset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MotionBlurAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DepthOfFieldStrength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BloomIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor ColorGrading;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VignetteIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Saturation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Contrast;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Gamma;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TransitionDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableLensFlares;
};

USTRUCT(BlueprintType)
struct FCameraEffectDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShakeIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShakeFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShakeDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FOVChange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FOVDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ZoomAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator RotationOffset;
};

USTRUCT(BlueprintType)
struct FSlowMotionParams
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeDilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EnterDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HoldDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExitDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAffectsAudio;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAffectsVFX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPostProcessingPreset PostProcessPreset;
};

USTRUCT(BlueprintType)
struct FVFXPerformanceMetrics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveNiagaraSystems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalParticles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GPUTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DrawCalls;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EVFXQualityLevel CurrentQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ActiveEffectNames;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> PerformanceWarnings;
};

USTRUCT(BlueprintType)
struct FMotionTrailDef
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMotionVFXType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETrailType TrailType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TrailLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TrailWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor TrailColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UNiagaraSystem> TrailSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxTrailCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpawnInterval;
};

UCLASS(BlueprintType)
class ULesFightVFXDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    ULesFightVFXDataAsset();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Impacts")
    TMap<EImpactVFXType, FImpactVFXDef> ImpactDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Auras")
    TMap<ECharacterAuraType, FCharacterAuraDef> AuraDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion")
    TMap<EMotionVFXType, FMotionTrailDef> MotionDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PostProcessing")
    TMap<EPostProcessingPreset, FPostProcessingState> PostProcessingPresets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
    TMap<EImpactVFXType, FCameraEffectDef> CameraEffectDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SlowMotion")
    TMap<ECinematicVFXEvent, FSlowMotionParams> SlowMotionPresets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    EVFXQualityMode QualityMode;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxNiagaraSystems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxTotalParticles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Style")
    EVFXStyleMode StyleMode;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Multiplayer")
    bool bReplicateMajorEffectsOnly;
};
