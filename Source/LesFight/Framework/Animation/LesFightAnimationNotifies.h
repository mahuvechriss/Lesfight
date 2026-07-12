#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "LesFightAnimationNotifies.generated.h"

UCLASS(meta = (DisplayName = "Footstep Notify"))
class ULesFightAnimNotify_Footstep : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
    FName FootBone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
    bool bIsRightFoot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Footstep")
    float VolumeMultiplier;
};

UCLASS(meta = (DisplayName = "Hit Notify"))
class ULesFightAnimNotify_Hit : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
    FName HitBone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
    float HitDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit")
    bool bIsStrongHit;
};

UCLASS(meta = (DisplayName = "Sound Notify"))
class ULesFightAnimNotify_Sound : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundBase> Sound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    float VolumeMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    float PitchMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    FName AttachSocketName;
};

UCLASS(meta = (DisplayName = "Camera Shake Notify"))
class ULesFightAnimNotify_CameraShake : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    TSubclassOf<UCameraShakeBase> ShakeClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float Scale;
};

UCLASS(meta = (DisplayName = "VFX Notify"))
class ULesFightAnimNotify_VFX : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UParticleSystem> ParticleSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UNiagaraSystem> NiagaraSystem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    FName AttachSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    FVector LocationOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    FRotator RotationOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    FVector Scale;
};

UCLASS(meta = (DisplayName = "Combo Window Notify"))
class ULesFightAnimNotifyState_ComboWindow : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
    int32 ComboStep;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo")
    FName NextAttackID;
};

UCLASS(meta = (DisplayName = "Ultimate Trigger Notify"))
class ULesFightAnimNotify_UltimateTrigger : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate")
    FName UltimateID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate")
    bool bTriggerCinematic;
};

UCLASS(meta = (DisplayName = "Root Motion Notify"))
class ULesFightAnimNotify_RootMotion : public UAnimNotify
{
    GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root Motion")
    bool bEnableRootMotion;
};

UCLASS(meta = (DisplayName = "Motion Warp Notify"))
class ULesFightAnimNotifyState_MotionWarp : public UAnimNotifyState
{
    GENERATED_BODY()

public:
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
    virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
    virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Warp")
    FName WarpTargetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Warp")
    EMotionWarpTarget WarpTargetType;
};
