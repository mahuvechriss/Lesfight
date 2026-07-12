#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LesFightMartialArtsData.generated.h"

UENUM(BlueprintType)
enum class EFightingStyle : uint8
{
    None,
    ShaolinKungFu,
    WingChun,
    TaiChi,
    Wushu,
    DrunkenFist,
    JeetKuneDo,
    MuayThai,
    Taekwondo,
    Karate,
    Judo,
    BrazilianJiuJitsu,
    Boxing,
    Kickboxing,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ECombatStance : uint8
{
    Neutral,
    Offensive,
    Defensive,
    Agile,
    Heavy,
    StyleSpecific,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAdvancedMovementType : uint8
{
    None,
    Dash,
    AirDash,
    WallRun,
    WallJump,
    WallKick,
    Vault,
    Slide,
    QuickStep,
    SideStep,
    BackFlip,
    FrontFlip,
    CombatRoll,
    SprintBurst,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ECounterType : uint8
{
    None,
    CounterAttack,
    PerfectCounter,
    CounterGrab,
    CounterThrow,
    CounterKick,
    CounterPunch,
    SlowMotionFinish,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAdvancedDodgeType : uint8
{
    None,
    PerfectDodge,
    DirectionalDodge,
    AirDodge,
    RollingDodge,
    BackStep,
    SideEvade,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EComboExpansionType : uint8
{
    None,
    Branching,
    AirCombo,
    Launcher,
    WallCombo,
    GroundCombo,
    CancelCombo,
    StyleSpecific,
    UltimateChain,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EEnvironmentInteraction : uint8
{
    None,
    WallBounce,
    WallSlam,
    EnvironmentalFinisher,
    ObjectDestruction,
    TerrainAdapt,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ECinematicEffect : uint8
{
    None,
    DynamicCamera,
    SlowMotion,
    UltimateCinematic,
    SignatureMove,
    DramaticImpact,
    VictoryCutscene,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EPhysicsSimulation : uint8
{
    None,
    Cloth,
    Hair,
    Accessory,
    SecondaryMotion,
    Momentum,
    BodyWeight,
    RealisticRecovery,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMotionMatchingMode : uint8
{
    Disabled,
    BasicBlending,
    MotionMatching,
    PredictiveSelection,
    FullPipeline,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAggressionLevel : uint8
{
    Passive,
    Defensive,
    Balanced,
    Aggressive,
    Relentless,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EPreferredDistance : uint8
{
    Close,
    Medium,
    Far,
    Any,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMartialArtsVFXIntensity : uint8
{
    Realistic,
    Enhanced,
    Cinematic,
    Fantasy,
    MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FStyleAttributes
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFightingStyle StyleID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText StyleName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseSpeedMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseDefenseMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ComboWindowMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaDrainMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CounterWindowMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DodgeDistanceMultiplier;

    FStyleAttributes()
        : StyleID(EFightingStyle::None)
        , BaseDamageMultiplier(1.0f), BaseSpeedMultiplier(1.0f)
        , BaseDefenseMultiplier(1.0f), ComboWindowMultiplier(1.0f)
        , StaminaDrainMultiplier(1.0f), CounterWindowMultiplier(1.0f)
        , DodgeDistanceMultiplier(1.0f)
    {}
};

USTRUCT(BlueprintType)
struct FStanceAttributes
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECombatStance StanceType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText StanceName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageModifier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpeedModifier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DefenseModifier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CounterChanceBonus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaRegenModifier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DodgeWindowModifier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ComboDamageBonus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanCounter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanPerfectDodge;

    FStanceAttributes()
        : StanceType(ECombatStance::Neutral)
        , DamageModifier(1.0f), SpeedModifier(1.0f)
        , DefenseModifier(1.0f), CounterChanceBonus(0.0f)
        , StaminaRegenModifier(1.0f), DodgeWindowModifier(1.0f)
        , ComboDamageBonus(0.0f)
        , bCanCounter(true), bCanPerfectDodge(true)
    {}
};

USTRUCT(BlueprintType)
struct FCounterWindowData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECounterType CounterType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WindowOpenTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WindowDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTriggersSlowMotion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SlowMotionDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SlowMotionTimeScale;

    FCounterWindowData()
        : CounterType(ECounterType::None)
        , WindowOpenTime(0.1f), WindowDuration(0.15f)
        , DamageMultiplier(1.5f), StaminaCost(20.0f)
        , bTriggersSlowMotion(false)
        , SlowMotionDuration(1.0f), SlowMotionTimeScale(0.25f)
    {}
};

USTRUCT(BlueprintType)
struct FAdvancedDodgeData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAdvancedDodgeType DodgeType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Distance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float IFrameDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanPerfectDodge;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PerfectDodgeWindow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTriggersSlowMotion;

    FAdvancedDodgeData()
        : DodgeType(EAdvancedDodgeType::None)
        , Distance(200.0f), Duration(0.3f)
        , IFrameDuration(0.2f), StaminaCost(15.0f)
        , bCanPerfectDodge(true), PerfectDodgeWindow(0.1f)
        , bTriggersSlowMotion(false)
    {}
};

USTRUCT(BlueprintType)
struct FAdvancedMovementData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAdvancedMovementType MovementType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Distance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanCancelIntoAttack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanCancelIntoDodge;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxWallJumps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown;

    FAdvancedMovementData()
        : MovementType(EAdvancedMovementType::None)
        , Speed(800.0f), Distance(300.0f)
        , Duration(0.3f), StaminaCost(10.0f)
        , bCanCancelIntoAttack(true), bCanCancelIntoDodge(true)
        , MaxWallJumps(1), Cooldown(0.0f)
    {}
};

USTRUCT(BlueprintType)
struct FComboExpansionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EComboExpansionType ExpansionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxChainLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChainWindow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaCostMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRequiresLauncher;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRequiresWall;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanEndWithUltimate;

    FComboExpansionData()
        : ExpansionType(EComboExpansionType::None)
        , MaxChainLength(3), ChainWindow(0.3f)
        , DamageMultiplier(1.0f), StaminaCostMultiplier(1.0f)
        , bRequiresLauncher(false), bRequiresWall(false)
        , bCanEndWithUltimate(false)
    {}
};

USTRUCT(BlueprintType)
struct FEnvironmentInteractionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEnvironmentInteraction InteractionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BounceDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SlamDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float KnockbackDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StunDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanDestroyObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTriggersFinisher;

    FEnvironmentInteractionData()
        : InteractionType(EEnvironmentInteraction::None)
        , BounceDamage(10.0f), SlamDamage(20.0f)
        , KnockbackDistance(300.0f), StunDuration(1.0f)
        , bCanDestroyObject(false), bTriggersFinisher(false)
    {}
};

USTRUCT(BlueprintType)
struct FCinematicEffectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECinematicEffect EffectType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector CameraOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraFOV;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraBlendTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseCustomMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLockInput;

    FCinematicEffectData()
        : EffectType(ECinematicEffect::None)
        , Duration(2.0f), TimeScale(1.0f)
        , CameraOffset(FVector(0, 0, 50)), CameraFOV(60.0f)
        , CameraBlendTime(0.5f)
        , bUseCustomMontage(false), bLockInput(true)
    {}
};

USTRUCT(BlueprintType)
struct FPhysicsMotionSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bClothEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHairEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAccessoryEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSecondaryMotionEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bMomentumEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MomentumInheritance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BodyWeightInfluence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RecoveryRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPhysicsSimulation SimulationLevel;

    FPhysicsMotionSettings()
        : bClothEnabled(true), bHairEnabled(true)
        , bAccessoryEnabled(true), bSecondaryMotionEnabled(true)
        , bMomentumEnabled(true), MomentumInheritance(0.5f)
        , BodyWeightInfluence(1.0f), RecoveryRate(1.0f)
        , SimulationLevel(EPhysicsSimulation::SecondaryMotion)
    {}
};

USTRUCT(BlueprintType)
struct FMotionMatchingSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMotionMatchingMode Mode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SearchRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxPoseMatches;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableTerrainAdaptation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableDirectionalBlending;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WarpSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WarpDuration;

    FMotionMatchingSettings()
        : Mode(EMotionMatchingMode::BasicBlending)
        , BlendSpeed(5.0f), SearchRadius(50.0f)
        , MaxPoseMatches(3), bEnableTerrainAdaptation(true)
        , bEnableDirectionalBlending(true)
        , WarpSpeed(2.0f), WarpDuration(0.3f)
    {}
};

USTRUCT(BlueprintType)
struct FCombatAIHooks
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFightingStyle PreferredStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPreferredDistance PreferredDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAggressionLevel AggressionLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CounterProbability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DodgeProbability;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ComboLengthPreference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DefensiveReactionTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float OffensiveReactionTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUsesUltimate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUsesEnvironmental;

    FCombatAIHooks()
        : PreferredStyle(EFightingStyle::None)
        , PreferredDistance(EPreferredDistance::Any)
        , AggressionLevel(EAggressionLevel::Balanced)
        , CounterProbability(0.3f), DodgeProbability(0.4f)
        , ComboLengthPreference(2.0f)
        , DefensiveReactionTime(0.3f), OffensiveReactionTime(0.2f)
        , bUsesUltimate(true), bUsesEnvironmental(true)
    {}
};

USTRUCT(BlueprintType)
struct FStyleAudioProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> AttackVoiceSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> HitVoiceSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> CounterVoiceSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UltimateVoiceSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> VictoryVoiceSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> DefeatVoiceSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ImpactSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ClothingSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> FootstepSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VoiceFrequency;
};

USTRUCT(BlueprintType)
struct FStyleVFXProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> AttackTrailEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ImpactEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> DodgeTrailEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> CounterEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UltimateEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> DustEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ShockwaveEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> AuraEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMartialArtsVFXIntensity VFXIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor PrimaryAuraColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor SecondaryAuraColor;
};

UCLASS(BlueprintType)
class ULesFightMartialArtsDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Styles")
    TMap<EFightingStyle, FStyleAttributes> StyleDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stances")
    TMap<ECombatStance, FStanceAttributes> StanceDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    TMap<EAdvancedMovementType, FAdvancedMovementData> MovementDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counters")
    TMap<ECounterType, FCounterWindowData> CounterDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
    TMap<EAdvancedDodgeType, FAdvancedDodgeData> DodgeDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos")
    TMap<EComboExpansionType, FComboExpansionData> ComboDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environment")
    TMap<EEnvironmentInteraction, FEnvironmentInteractionData> EnvironmentDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cinematic")
    TMap<ECinematicEffect, FCinematicEffectData> CinematicDefinitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
    FPhysicsMotionSettings PhysicsSettings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotionMatching")
    FMotionMatchingSettings MotionMatchingSettings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float AnimationLODDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float PhysicsLODDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
    float VFXLODDistance;

    ULesFightMartialArtsDataAsset()
        : AnimationLODDistance(1500.0f)
        , PhysicsLODDistance(1000.0f)
        , VFXLODDistance(2000.0f)
    {
        StanceDefinitions.Emplace(ECombatStance::Neutral, FStanceAttributes());
        StanceDefinitions.Emplace(ECombatStance::Offensive, FStanceAttributes());
        StanceDefinitions.Emplace(ECombatStance::Defensive, FStanceAttributes());
        StanceDefinitions.Emplace(ECombatStance::Agile, FStanceAttributes());
        StanceDefinitions.Emplace(ECombatStance::Heavy, FStanceAttributes());
    }
};
