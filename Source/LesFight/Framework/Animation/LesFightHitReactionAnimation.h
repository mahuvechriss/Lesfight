#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightHitReactionAnimation.generated.h"

class ULesFightCharacterAnimationComponent;
class ULesFightAnimBlueprintBase;

USTRUCT(BlueprintType)
struct FHitReactionAnimData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EHitReactionAnimType ReactionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> ReactionMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendInTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendOutTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReactivateTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanBeInterrupted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseRootMotion;

    FHitReactionAnimData()
        : ReactionType(EHitReactionAnimType::None)
        , ReactionMontage(nullptr)
        , BlendInTime(0.1f), BlendOutTime(0.2f)
        , ReactivateTime(0.5f)
        , bCanBeInterrupted(false)
        , bUseRootMotion(false)
    {}
};

UCLASS(Blueprintable)
class ULesFightHitReactionAnimation : public UObject
{
    GENERATED_BODY()

public:
    ULesFightHitReactionAnimation();

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void PlayHitReaction(EHitReactionAnimType ReactionType);

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void PlayReactionForBone(FName HitBone, float Damage, FVector HitDirection);

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void StopHitReaction(float BlendOut = 0.2f);

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void QueueHitReaction(EHitReactionAnimType ReactionType);

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void CancelQueuedReactions();

    UFUNCTION(BlueprintCallable, Category = "Hit Reactions")
    void SetReactionIntensityMultiplier(float Multiplier)
        { ReactionIntensityMultiplier = Multiplier; }

    UFUNCTION(BlueprintPure, Category = "Hit Reactions")
    bool IsReacting() const { return bIsReacting; }

    UFUNCTION(BlueprintPure, Category = "Hit Reactions")
    EHitReactionAnimType GetCurrentReaction() const { return CurrentReaction; }

    UFUNCTION(BlueprintPure, Category = "Hit Reactions")
    float GetRemainingReactionTime() const { return FMath::Max(0.0f, ReactionTimer); }

    UFUNCTION(BlueprintPure, Category = "Hit Reactions")
    EHitReactionAnimType GetBoneHitReaction(FName HitBone, float Damage) const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Hit Reactions")
    TMap<EHitReactionAnimType, FHitReactionAnimData> ReactionAnimData;

    UPROPERTY(BlueprintReadOnly, Category = "Hit Reactions")
    TQueue<EHitReactionAnimType> QueuedReactions;

    UPROPERTY(BlueprintReadOnly, Category = "Hit Reactions")
    EHitReactionAnimType CurrentReaction;

    UPROPERTY(BlueprintReadOnly, Category = "Hit Reactions")
    float ReactionTimer;

    UPROPERTY(BlueprintReadOnly, Category = "Hit Reactions")
    bool bIsReacting;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit Reactions")
    float ReactionIntensityMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit Reactions")
    float LightReactionThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit Reactions")
    float HeavyReactionThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit Reactions")
    float KnockbackReactionThreshold;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<ULesFightAnimBlueprintBase> AnimBP;

    void SelectReactionByDamage(float Damage, EHitReactionAnimType& OutType);
};
