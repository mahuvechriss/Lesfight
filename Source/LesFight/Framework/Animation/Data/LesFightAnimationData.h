#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "LesFightAnimationData.generated.h"

class UAnimMontage;
class UAnimSequence;
class UBlendSpace;
class UAnimInstance;
class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
    None,
    Idle,
    Walk,
    Jog,
    Sprint,
    TurnLeft,
    TurnRight,
    StartMoving,
    StopMoving,
    Crouch,
    CrouchWalk,
    JumpStart,
    JumpLoop,
    JumpLand,
    Falling,
    Recovery,
    MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ECombatAnimType : uint8
{
    None,
    LightPunch,
    HeavyPunch,
    LightKick,
    HeavyKick,
    AirAttack,
    CrouchAttack,
    DashAttack,
    SpecialAttack,
    UltimateAttack,
    Block,
    PerfectBlock,
    Dodge,
    Throw,
    BeingThrown,
    Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EHitReactionAnimType : uint8
{
    None,
    HeadHit,
    BodyHit,
    LegHit,
    AirHit,
    HeavyImpact,
    Knockback,
    Launch,
    WallImpact,
    GroundImpact,
    Stagger,
    LightStun,
    HeavyStun,
    Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAnimationLayer : uint8
{
    BasePose,
    Locomotion,
    UpperBody,
    LowerBody,
    FullBody,
    Overlay,
    Additive,
    Facial,
    Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EBlendSpaceType : uint8
{
    None,
    DirectionalMovement,
    SpeedBlending,
    AimOffset,
    TurnInPlace,
    CrouchTransition,
    Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMotionWarpTarget : uint8
{
    None,
    TargetActor,
    TargetLocation,
    ThrowDirection,
    FinisherTarget,
    WallBounce,
    GroundPosition,
    Custom UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EIKType : uint8
{
    None,
    FootIK,
    HandIK,
    GroundAdaptation,
    WeaponPropIK,
    FullBodyIK,
    Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ERootMotionMode : uint8
{
    Disabled,
    Enabled,
    PartialTranslation,
    PartialRotation,
    Full UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAnimTransitionMethod : uint8
{
    None,
    Inertialization,
    StandardBlend,
    CustomCurve,
    Snap,
    Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EFacialExpression : uint8
{
    Neutral,
    Happy,
    Angry,
    Sad,
    Surprised,
    Pained,
    Determined,
    Taunting,
    Focused,
    Defeated,
    Max UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAnimationQuality : uint8
{
    Low,
    Medium,
    High,
    Epic,
    Cinematic,
    Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FAnimSlotInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendInTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendOutTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SlotPriority;

    FAnimSlotInfo()
        : SlotName(NAME_None)
        , BlendInTime(0.2f)
        , BlendOutTime(0.2f)
        , SlotPriority(0)
    {}
};

USTRUCT(BlueprintType)
struct FAnimTransitionRule
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName RuleName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName FromState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ToState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAnimTransitionMethod TransitionMethod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseInertialization;

    FAnimTransitionRule()
        : RuleName(NAME_None), FromState(NAME_None), ToState(NAME_None)
        , BlendDuration(0.2f)
        , TransitionMethod(EAnimTransitionMethod::StandardBlend)
        , bUseInertialization(false)
    {}
};

USTRUCT(BlueprintType)
struct FAnimBlendEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> Animation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UBlendSpace> BlendSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendInTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAnimationLayer TargetLayer;

    FAnimBlendEntry()
        : Animation(nullptr), BlendSpace(nullptr)
        , SlotName(NAME_None)
        , BlendWeight(1.0f)
        , BlendInTime(0.2f)
        , TargetLayer(EAnimationLayer::FullBody)
    {}
};

USTRUCT(BlueprintType)
struct FLocomotionAnimSet
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> Idle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<UAnimSequence>> IdleVariations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UBlendSpace> WalkBlendSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UBlendSpace> JogBlendSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UBlendSpace> SprintBlendSpace;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> TurnLeft;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> TurnRight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> StartMoving;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> StopMoving;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> CrouchIdle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> CrouchWalk;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> JumpStart;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> JumpLoop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> JumpLand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> Falling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimSequence> Recovery;
};

USTRUCT(BlueprintType)
struct FCombatAnimSet
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, TObjectPtr<UAnimMontage>> AttackAnimations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> BlockMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> PerfectBlockMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> DodgeMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> ThrowMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> BeingThrownMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EHitReactionAnimType, TObjectPtr<UAnimMontage>> HitReactionMontages;
};

USTRUCT(BlueprintType)
struct FMotionWarpTargetData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName TargetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMotionWarpTarget TargetType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TargetLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator TargetRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TWeakObjectPtr<AActor> TargetActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WarpWeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bWarpPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bWarpRotation;

    FMotionWarpTargetData()
        : TargetName(NAME_None)
        , TargetType(EMotionWarpTarget::None)
        , TargetLocation(FVector::ZeroVector)
        , TargetRotation(FRotator::ZeroRotator)
        , TargetActor(nullptr)
        , WarpWeight(1.0f)
        , bWarpPosition(true)
        , bWarpRotation(true)
    {}
};

USTRUCT(BlueprintType)
struct FIKChainSetup
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ChainStartBone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ChainEndBone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EIKType IKType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float IKAlpha;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float IKBlendSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableLimits;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableFootLocking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector TraceOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TraceDistance;

    FIKChainSetup()
        : ChainStartBone(NAME_None), ChainEndBone(NAME_None)
        , IKType(EIKType::None)
        , IKAlpha(1.0f), IKBlendSpeed(5.0f)
        , bEnableLimits(true), bEnableFootLocking(true)
        , TraceOffset(FVector::ZeroVector)
        , TraceDistance(50.0f)
    {}
};

USTRUCT(BlueprintType)
struct FAnimationMontageData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> Montage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SectionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLoop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableRootMotion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseMotionWarping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FMotionWarpTargetData> WarpTargets;

    FAnimationMontageData()
        : Montage(nullptr), SectionName(NAME_None)
        , PlayRate(1.0f), StartPosition(0.0f)
        , bLoop(false)
        , bEnableRootMotion(true)
        , bUseMotionWarping(false)
    {}
};

UCLASS(BlueprintType)
class ULesFightAnimationDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion")
    FLocomotionAnimSet LocomotionSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    FCombatAnimSet CombatSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blending")
    TArray<FAnimTransitionRule> TransitionRules;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IK")
    TArray<FIKChainSetup> IKChains;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Facial")
    TMap<EFacialExpression, TObjectPtr<UAnimSequence>> FacialAnimations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
    float DefaultBlendInTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
    float DefaultBlendOutTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quality")
    EAnimationQuality AnimationQuality;

    ULesFightAnimationDataAsset()
        : DefaultBlendInTime(0.2f)
        , DefaultBlendOutTime(0.2f)
        , AnimationQuality(EAnimationQuality::High)
    {}
};
