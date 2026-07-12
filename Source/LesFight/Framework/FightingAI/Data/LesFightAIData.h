#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Framework/MartialArts/Data/LesFightMartialArtsData.h"
#include "Framework/Combat/Data/LesFightComboData.h"
#include "LesFightAIData.generated.h"

UENUM(BlueprintType)
enum class EAIBehaviorMode : uint8
{
    Idle,
    Patrol,
    Engage,
    Combat,
    Retreat,
    Recovery,
    BossPhase,
    Training,
    MAX
};

UENUM(BlueprintType)
enum class EAICombatRole : uint8
{
    Aggressor,
    Defender,
    Balanced,
    Tactical,
    MAX
};

UENUM(BlueprintType)
enum class EAIThreatLevel : uint8
{
    None,
    Low,
    Medium,
    High,
    Critical,
    MAX
};

UENUM(BlueprintType)
enum class EAIDifficulty : uint8
{
    Easy,
    Normal,
    Hard,
    Expert,
    Master,
    MAX
};

UENUM(BlueprintType)
enum class EAIPersonalityType : uint8
{
    Warrior,
    Assassin,
    Master,
    Berserker,
    Trickster,
    Technician,
    Brawler,
    Adaptive,
    MAX
};

UENUM(BlueprintType)
enum class EAIActionType : uint8
{
    None,
    LightAttack,
    HeavyAttack,
    ComboAttack,
    SpecialMove,
    UltimateAttack,
    Block,
    Dodge,
    Parry,
    Counter,
    Grab,
    Throw,
    StepBack,
    StepForward,
    Sidestep,
    Jump,
    Crouch,
    Taunt,
    Recover,
    Wait,
    MAX
};

UENUM(BlueprintType)
enum class EAICombatRange : uint8
{
    Far,
    Medium,
    Close,
    Grappling,
    MAX
};

UENUM(BlueprintType)
enum class EAIStateFlags : uint8
{
    None,
    Stunned,
    KnockedDown,
    Blocking,
    Attacking,
    Recovering,
    Invulnerable,
    Comboing,
    MAX
};

UENUM(BlueprintType)
enum class EAITrainingMode : uint8
{
    Passive,
    BlockingPractice,
    ComboPractice,
    CounterPractice,
    DodgePractice,
    FullPractice,
    MAX
};

UENUM(BlueprintType)
enum class EAIBossPhase : uint8
{
    Phase1,
    Phase2,
    Phase3,
    Enrage,
    Final,
    MAX
};

UENUM(BlueprintType)
enum class EAIAnimationEvent : uint8
{
    AttackStart,
    AttackHit,
    AttackMiss,
    ComboStart,
    ComboEnd,
    BlockStart,
    BlockHit,
    DodgeStart,
    DodgeComplete,
    ParrySuccess,
    CounterStart,
    CounterHit,
    GetHit,
    Knockdown,
    GetUp,
    Stunned,
    RecoverStart,
    RecoverEnd,
    Taunt,
    Victory,
    Defeat,
    MAX
};

UENUM(BlueprintType)
enum class EAIDecisionPriority : uint8
{
    Emergency,
    High,
    Medium,
    Low,
    Idle,
    MAX
};

USTRUCT(BlueprintType)
struct FAIPerceptionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector DetectedPlayerLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector DetectedPlayerVelocity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DistanceToPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AngleToPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerHealthPercent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerStaminaPercent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsAttacking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsBlocking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsRecovering;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bPlayerIsVulnerable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeSinceLastPlayerAttack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerAttackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAICombatRange CurrentRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RecentPlayerMoves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DetectionConfidence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector PredictedPlayerPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PredictionConfidence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ArenaCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DistanceToArenaEdge;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bNearArenaEdge;
};

USTRUCT(BlueprintType)
struct FAIDecisionContext
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIActionType ChosenAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIDecisionPriority Priority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ActionScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName TargetComboName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DecisionTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReactionDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFightingStyle StyleOverride;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ReasoningLog;
};

USTRUCT(BlueprintType)
struct FAIStyleBehaviorProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFightingStyle FightingStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AggressionWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DefenseWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CounterWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MovementWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ComboFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpecialMoveFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PreferredRange;  // 0=far, 1=close

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> PreferredCombos;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<EAIActionType> FavoriteActions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Reactivity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RiskTolerance;
};

USTRUCT(BlueprintType)
struct FAIDifficultySettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIDifficulty Difficulty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReactionTimeMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReactionTimeMax;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DecisionSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlockChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DodgeChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ParryChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CounterChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ComboAccuracy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DefenseMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AggressionModifier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PredictionAccuracy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxComboLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MistakeChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LearningRate;
};

USTRUCT(BlueprintType)
struct FAIAdaptiveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EAIActionType, int32> PlayerActionFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EAIActionType, float> PlayerActionSuccessRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, int32> PlayerComboFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ObservedPatterns;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerAggressionScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerDefenseScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerPreferredRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 FightsAnalyzed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AdaptationRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EAIActionType, float> CounterEffectiveness;
};

USTRUCT(BlueprintType)
struct FAIPersonalityOverride
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIPersonalityType Personality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AggressionBias;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DefenseBias;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RiskBias;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TauntFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PersonalityName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> TauntLines;
};

USTRUCT(BlueprintType)
struct FAIDebugSnapshot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIActionType CurrentAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAICombatRole CurrentRole;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAICombatRange CurrentRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIThreatLevel ThreatLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DecisionScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DecisionReason;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> TopConsideredActions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeSinceLastDecision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ComboProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentAggression;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CurrentDefense;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsLearning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> BehaviorLog;
};

UCLASS(BlueprintType)
class ULesFightAIDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    ULesFightAIDataAsset();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Difficulty")
    TMap<EAIDifficulty, FAIDifficultySettings> DifficultySettings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Personalities")
    TMap<EAIPersonalityType, FAIPersonalityOverride> PersonalityProfiles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Style")
    TMap<EFightingStyle, FAIStyleBehaviorProfile> StyleProfiles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    float GlobalReactionMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    float MaxDecisionTime;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    float MinDecisionInterval;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Learning")
    int32 MaxObservedPatterns;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Learning")
    float AdaptationCooldown;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxAIDebugLogEntries;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    float AIUpdateInterval;
};
