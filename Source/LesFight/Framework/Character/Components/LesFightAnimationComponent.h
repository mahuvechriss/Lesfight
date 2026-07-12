#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightAnimationComponent.generated.h"

class ULesFightAnimInstance;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationStateChanged, const FString&, StateName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageCompleted, FName, MontageName);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightAnimationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightAnimationComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void Initialize(USkeletalMeshComponent* InMesh);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void PlayMontage(UAnimMontage* Montage, float PlayRate = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void StopMontage(UAnimMontage* Montage);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetAnimationState(const FString& StateName);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetBlendSpaceParameter(const FName& ParameterName, float Value);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void PlayIdleVariation();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetAnimationSpeed(float SpeedMultiplier);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetLocomotionValues(float Speed, float Direction);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerPunchPlaceholder();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerKickPlaceholder();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerBlockPlaceholder();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerHitReactionPlaceholder();

    UFUNCTION(BlueprintPure, Category = "Animation")
    ULesFightAnimInstance* GetFighterAnimInstance() const;

    UFUNCTION(BlueprintPure, Category = "Animation")
    bool IsMontagePlaying() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TArray<TObjectPtr<UAnimMontage>> PunchMontages;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TArray<TObjectPtr<UAnimMontage>> KickMontages;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> BlockMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> HitReactionMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TArray<TObjectPtr<UAnimSequence>> IdleVariations;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimationStateChanged OnAnimationStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMontageCompleted OnMontageCompleted;

private:
    TWeakObjectPtr<USkeletalMeshComponent> SkeletalMesh;
    float AnimationSpeedMultiplier;
    FString CurrentAnimationState;
};
