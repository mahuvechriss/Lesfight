#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "LesFightAttackData.generated.h"

class UAnimMontage;

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    LightPunch,
    HeavyPunch,
    LightKick,
    HeavyKick,
    JumpPunch,
    JumpKick,
    CrouchPunch,
    CrouchKick,
    DashAttack,
    Special,
    Ultimate,
    Throw
};

UENUM(BlueprintType)
enum class EAttackCategory : uint8
{
    Normal,
    Special,
    Throw,
    Ultimate
};

UENUM(BlueprintType)
enum class EBlockType : uint8
{
    None,
    Standing,
    Crouching,
    Air,
    Perfect
};

UENUM(BlueprintType)
enum class EAntiBlock : uint8
{
    None,
    StandOnly,
    CrouchOnly,
    Unblockable,
    GuardBreak
};

UENUM(BlueprintType)
enum class EAttackHeight : uint8
{
    Low,
    Mid,
    High,
    Standing,
    Crouching,
    Air,
    Special
};

UENUM(BlueprintType)
enum class EDodgeType : uint8
{
    None,
    ForwardDash,
    BackDash,
    SideStep
};

UENUM(BlueprintType)
enum class EHitReaction : uint8
{
    None,
    LightStun,
    HeavyStun,
    Knockback,
    Launch,
    Knockdown,
    AirHit,
    WallBounce
};

USTRUCT(BlueprintType)
struct FAttackFrameData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")
    int32 StartupFrames;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")
    int32 ActiveFrames;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")
    int32 RecoveryFrames;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")
    int32 HitstunFrames;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")
    int32 BlockstunFrames;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")
    int32 CancelWindowStart;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frames")
    int32 CancelWindowEnd;

    FAttackFrameData()
        : StartupFrames(5), ActiveFrames(3), RecoveryFrames(10)
        , HitstunFrames(12), BlockstunFrames(6)
        , CancelWindowStart(0), CancelWindowEnd(0)
    {}
};

USTRUCT(BlueprintType)
struct FAttackDamageData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float BaseDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float ScalingFactor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float KnockbackForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float LaunchForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float StaminaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float EnergyGain;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float GuardDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    bool bCanCrit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float CritMultiplier;

    FAttackDamageData()
        : BaseDamage(50.0f), ScalingFactor(1.0f)
        , KnockbackForce(300.0f), LaunchForce(0.0f)
        , StaminaCost(5.0f), EnergyGain(10.0f)
        , GuardDamage(0.0f)
        , bCanCrit(false), CritMultiplier(1.5f)
    {}
};

USTRUCT(BlueprintType)
struct FAttackProperties
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bIsOverhead;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bIsLow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bIsUnblockable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bIsArmored;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bCanBeCancelled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bLaunches;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bKnocksDown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    bool bHasInvincibility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    EAttackHeight AttackHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    EAntiBlock AntiBlock;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    EBlockType BlockableBy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
    EHitReaction HitReaction;

    FAttackProperties()
        : bIsOverhead(false), bIsLow(false), bIsUnblockable(false)
        , bIsArmored(false), bCanBeCancelled(true)
        , bLaunches(false), bKnocksDown(false), bHasInvincibility(false)
        , AttackRange(80.0f)
        , AttackHeight(EAttackHeight::Standing)
        , AntiBlock(EAntiBlock::None)
        , BlockableBy(EBlockType::Standing)
        , HitReaction(EHitReaction::LightStun)
    {}
};

USTRUCT(BlueprintType)
struct FAttackDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FName AttackID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    EAttackType AttackType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FString AttackName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    TObjectPtr<UAnimMontage> AttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FAttackFrameData FrameData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FAttackDamageData DamageData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FAttackProperties Properties;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    FGameplayTagContainer AttackTags;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
    TArray<FName> ComboRoutes;
};

USTRUCT(BlueprintType)
struct FHitboxShape
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Extents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator Rotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveStartFrame;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActiveEndFrame;

    FHitboxShape()
        : Location(FVector::ZeroVector)
        , Extents(FVector(20.0f, 20.0f, 20.0f))
        , Rotation(FRotator::ZeroRotator)
        , BoneName(NAME_None)
        , ActiveStartFrame(0)
        , ActiveEndFrame(0)
    {}
};

USTRUCT(BlueprintType)
struct FHurtboxShape
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Extents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BoneName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsVulnerable;

    FHurtboxShape()
        : Location(FVector::ZeroVector)
        , Extents(FVector(30.0f, 20.0f, 40.0f))
        , BoneName(NAME_None)
        , bIsVulnerable(true)
    {}
};
