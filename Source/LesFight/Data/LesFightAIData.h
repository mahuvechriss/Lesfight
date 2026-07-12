#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LesFightAIData.generated.h"

UENUM(BlueprintType)
enum class EAIBehaviorMode : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Patrol      UMETA(DisplayName = "Patrol"),
    Engage      UMETA(DisplayName = "Engage"),
    Combat      UMETA(DisplayName = "Combat"),
    Retreat     UMETA(DisplayName = "Retreat"),
    Recovery    UMETA(DisplayName = "Recovery")
};

UENUM(BlueprintType)
enum class EAIDifficulty : uint8
{
    Easy        UMETA(DisplayName = "Easy"),
    Normal      UMETA(DisplayName = "Normal"),
    Hard        UMETA(DisplayName = "Hard"),
    Expert      UMETA(DisplayName = "Expert")
};

UENUM(BlueprintType)
enum class EAIPersonalityType : uint8
{
    Aggressive      UMETA(DisplayName = "Aggressive"),
    Defensive       UMETA(DisplayName = "Defensive"),
    Balanced        UMETA(DisplayName = "Balanced"),
    Adaptive        UMETA(DisplayName = "Adaptive"),
    Unpredictable   UMETA(DisplayName = "Unpredictable")
};

UENUM(BlueprintType, meta = (Bitflags))
enum class EAIStateFlags : uint8
{
    None        UMETA(DisplayName = "None"),
    IsAlerted   UMETA(DisplayName = "IsAlerted"),
    IsBlocking  UMETA(DisplayName = "IsBlocking"),
    IsAttacking UMETA(DisplayName = "IsAttacking"),
    IsStunned   UMETA(DisplayName = "IsStunned"),
    IsRecovering UMETA(DisplayName = "IsRecovering"),
    HasAdvantage UMETA(DisplayName = "HasAdvantage"),
    IsCornered  UMETA(DisplayName = "IsCornered")
};

UENUM(BlueprintType)
enum class EAIActionType : uint8
{
    LightAttack     UMETA(DisplayName = "LightAttack"),
    HeavyAttack     UMETA(DisplayName = "HeavyAttack"),
    Block           UMETA(DisplayName = "Block"),
    Dodge           UMETA(DisplayName = "Dodge"),
    Dash            UMETA(DisplayName = "Dash"),
    Jump            UMETA(DisplayName = "Jump"),
    SpecialMove     UMETA(DisplayName = "SpecialMove"),
    Grab            UMETA(DisplayName = "Grab"),
    Counter         UMETA(DisplayName = "Counter"),
    Retreat         UMETA(DisplayName = "Retreat"),
    Approach        UMETA(DisplayName = "Approach"),
    Wait            UMETA(DisplayName = "Wait"),
    Combo           UMETA(DisplayName = "Combo"),
    Taunt           UMETA(DisplayName = "Taunt")
};

USTRUCT(BlueprintType)
struct FAIPerceptionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* TargetActor = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DistanceToTarget = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TargetHealth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TargetStamina = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SelfHealth = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SelfStamina = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ThreatLevel = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTargetAttacking = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTargetBlocking = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimeSinceLastHit = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIBehaviorMode CurrentState = EAIBehaviorMode::Idle;
};

USTRUCT(BlueprintType)
struct FAIDecisionContext
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIActionType Action = EAIActionType::Wait;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Score = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Confidence = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AActor* Target = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReactionTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, float> ContextWeights;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIBehaviorMode ResultingMode = EAIBehaviorMode::Idle;
};

USTRUCT(BlueprintType)
struct FAIStyleBehaviorProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AggressionWeight = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DefensivenessWeight = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MobilityWeight = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RiskTolerance = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReactionMultiplier = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ComboPropensity = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SpacingPreference = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EAIActionType, float> ActionWeights;
};

USTRUCT(BlueprintType)
struct FAIDifficultySettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReactionSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DecisionAccuracy = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InputLatency = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PerfectBlockChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PunishChance = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxComboLength = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanReadInputs = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ErrorRate = 0.0f;
};
