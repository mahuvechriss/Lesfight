#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightAnimationData.h"
#include "LesFightCharacterAnimationComponent.generated.h"

class ALesFightBaseFighter;
class ULesFightAnimBlueprintBase;
class ULesFightAnimationStateMachine;
class ULesFightAnimationLayerSystem;
class ULesFightAnimationEventManager;
class ULesFightLocomotionSystem;
class ULesFightCombatAnimHandler;
class ULesFightBlendingSystem;
class ULesFightRootMotionHandler;
class ULesFightMotionWarpingSystem;
class ULesFightIKSystem;
class ULesFightHitReactionAnimation;
class ULesFightFacialAnimationSystem;
class ULesFightCombatComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageStarted, UAnimMontage*, Montage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageCompleted, UAnimMontage*, Montage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageBlendedOut, UAnimMontage*, Montage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimationEvent, FName, EventName, float, EventTime);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightCharacterAnimationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightCharacterAnimationComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void Initialize(ALesFightBaseFighter* InOwner, ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void PlayAnimationMontage(const FAnimationMontageData& MontageData);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void StopAnimationMontage(float BlendOut = 0.2f);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetLocomotionState(ELocomotionState State);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetCombatAnimType(ECombatAnimType Type);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetHitReactionAnim(EHitReactionAnimType ReactionType);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetMotionWarpTarget(const FMotionWarpTargetData& WarpTarget);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetFacialExpression(EFacialExpression Expression, float BlendTime = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerAdditiveAnimation(FName SlotName, UAnimSequence* AdditiveAnim, float BlendIn);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetAnimationQuality(EAnimationQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetGlobalPlayRate(float Rate);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void PauseAnimation();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void ResumeAnimation();

    UFUNCTION(BlueprintPure, Category = "Animation")
    ULesFightAnimBlueprintBase* GetAnimBlueprintInstance() const;

    UFUNCTION(BlueprintPure, Category = "Animation")
    ELocomotionState GetCurrentLocomotionState() const { return CurrentLocomotionState; }

    UFUNCTION(BlueprintPure, Category = "Animation")
    ECombatAnimType GetCurrentCombatAnimType() const { return CurrentCombatAnimType; }

    UFUNCTION(BlueprintPure, Category = "Animation")
    EHitReactionAnimType GetCurrentHitReactionAnim() const { return CurrentHitReactionAnim; }

    UFUNCTION(BlueprintPure, Category = "Animation")
    bool IsPlayingMontage() const;

    UFUNCTION(BlueprintPure, Category = "Animation")
    float GetCurrentMontagePlayTime() const;

    UFUNCTION(BlueprintPure, Category = "Animation")
    float GetNormalizedMontageTime() const;

    UFUNCTION(BlueprintPure, Category = "Animation")
    USkeletalMeshComponent* GetMesh() const;

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerPlayMontage(const FAnimationMontageData& MontageData);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerStopMontage(float BlendOut);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSetLocomotionState(ELocomotionState State);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSetHitReaction(EHitReactionAnimType ReactionType);

    UFUNCTION(Client, Reliable)
    void ClientSyncAnimationState(const FNetworkAnimSyncData& AnimData);

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMontageStarted OnMontageStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMontageCompleted OnMontageCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMontageBlendedOut OnMontageBlendedOut;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimationEvent OnAnimationEvent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightAnimationStateMachine> StateMachine;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightAnimationLayerSystem> LayerSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightAnimationEventManager> EventManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightLocomotionSystem> LocomotionSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightCombatAnimHandler> CombatAnimHandler;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightBlendingSystem> BlendingSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightRootMotionHandler> RootMotionHandler;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightMotionWarpingSystem> MotionWarpingSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightIKSystem> IKSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightHitReactionAnimation> HitReactionAnimation;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubSystems")
    TObjectPtr<ULesFightFacialAnimationSystem> FacialSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
    TObjectPtr<ULesFightAnimationDataAsset> AnimationDataAsset;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    ELocomotionState CurrentLocomotionState;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECombatAnimType CurrentCombatAnimType;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EHitReactionAnimType CurrentHitReactionAnim;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float GlobalPlayRate;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bAnimationsPaused;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    TWeakObjectPtr<ULesFightCombatComponent> CombatComponentWeak;

    void CreateSubSystems(ALesFightBaseFighter* Owner);
    void UpdateAnimationStates(float DeltaTime);
    void BindCombatEvents();
};
