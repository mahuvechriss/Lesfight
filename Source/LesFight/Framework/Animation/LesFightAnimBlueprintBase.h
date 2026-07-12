#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimBlueprintBase.generated.h"

class ALesFightBaseFighter;
class ULesFightCharacterAnimationComponent;

UCLASS(Blueprintable)
class ULesFightAnimBlueprintBase : public UAnimInstance
{
    GENERATED_BODY()

public:
    ULesFightAnimBlueprintBase();

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
    virtual void NativePostEvaluateAnimation() override;
    virtual void NativeUninitializeAnimation() override;

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void InitializeWithCharacter(ALesFightBaseFighter* InFighter);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void SetLocomotionState(ELocomotionState NewState);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void SetCombatAnimType(ECombatAnimType NewType);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void SetHitReactionAnim(EHitReactionAnimType NewReaction);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void PlayMontageFromData(const FAnimationMontageData& MontageData);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void StopAllMontages(float BlendOut = 0.2f);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void SetBlendValues(float Speed, float Direction, float Acceleration);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void TriggerAdditiveAnimation(FName SlotName, UAnimSequence* AdditiveAnim, float BlendIn);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void SetFacialExpression(EFacialExpression Expression, float BlendTime = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void EnableRootMotion(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    virtual void SetAnimationQuality(EAnimationQuality Quality);

    UFUNCTION(BlueprintPure, Category = "Animation")
    virtual bool IsPlayingMontage() const;

    UFUNCTION(BlueprintPure, Category = "Animation")
    virtual float GetPlayRate() const { return PlayRate; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    TObjectPtr<ALesFightBaseFighter> OwnerFighter;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    TObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    ELocomotionState CurrentLocomotionState;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    ECombatAnimType CurrentCombatAnimType;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EHitReactionAnimType CurrentHitReactionAnim;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EFacialExpression CurrentFacialExpression;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float Speed;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float Direction;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float Acceleration;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsInAir;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsCrouching;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsBlocking;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsAttacking;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsHitReacting;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float PlayRate;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    EAnimationQuality AnimQuality;
};
