#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightReactionSystem.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class EReactionState : uint8
{
    None,
    Hitstun,
    Blockstun,
    Knockback,
    Knockdown,
    Getup,
    Launched,
    Airborne,
    Staggered,
    Frozen,
};

USTRUCT(BlueprintType)
struct FReactionTransitionData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    EReactionState FromState;

    UPROPERTY(BlueprintReadOnly)
    EReactionState ToState;

    UPROPERTY(BlueprintReadOnly)
    float Duration;

    UPROPERTY(BlueprintReadOnly)
    FVector Force;

    UPROPERTY(BlueprintReadOnly)
    FName AttackID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReactionStateChanged, EReactionState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReactionEnded);

UCLASS(Blueprintable)
class ULesFightReactionSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightReactionSystem();

    UFUNCTION(BlueprintCallable, Category = "Reaction")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "Reaction")
    void ApplyHitReaction(const FAttackDefinition& Attack, FVector HitDirection, float Damage);

    UFUNCTION(BlueprintCallable, Category = "Reaction")
    void ApplyBlockReaction(const FAttackDefinition& Attack, FVector HitDirection);

    UFUNCTION(BlueprintCallable, Category = "Reaction")
    void EndCurrentReaction();

    UFUNCTION(BlueprintCallable, Category = "Reaction")
    void Freeze(float Duration);

    UFUNCTION(BlueprintCallable, Category = "Reaction")
    void Unfreeze();

    UFUNCTION(BlueprintPure, Category = "Reaction")
    EReactionState GetCurrentReactionState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "Reaction")
    bool IsInHitstun() const;

    UFUNCTION(BlueprintPure, Category = "Reaction")
    bool IsInBlockstun() const;

    UFUNCTION(BlueprintPure, Category = "Reaction")
    bool IsKnockedDown() const;

    UFUNCTION(BlueprintPure, Category = "Reaction")
    bool IsLaunched() const;

    UFUNCTION(BlueprintPure, Category = "Reaction")
    bool IsStaggered() const;

    UFUNCTION(BlueprintPure, Category = "Reaction")
    bool IsFrozen() const { return CurrentState == EReactionState::Frozen; }

    UFUNCTION(BlueprintPure, Category = "Reaction")
    float GetReactionTimeRemaining() const { return ReactionTimer; }

    UFUNCTION(BlueprintPure, Category = "Reaction")
    float GetRemainingReactionRatio() const;

    UFUNCTION(BlueprintPure, Category = "Reaction")
    bool CanAct() const;

    UFUNCTION(BlueprintCallable, Category = "Reaction")
    void SetStaggerThreshold(float Threshold) { StaggerThreshold = Threshold; }

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnReactionStateChanged OnReactionStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnReactionEnded OnReactionEnded;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    float StaggerThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    float KnockbackDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    float KnockdownDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    float GetupDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    float LaunchHeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    float LaunchDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reaction")
    TArray<FAttackDefinition> QueuedReactions;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    EReactionState CurrentState;
    float ReactionTimer;
    float ReactionDuration;
    FVector ReactionForce;
    FName CurrentReactionID;

    void SetReactionState(EReactionState NewState);
    void ApplyKnockback(FVector Direction, float Force);
    void ApplyLaunch(FVector Direction, float Force);
    void ApplyDisplacement(FVector Offset);
    void PlayReactionAnimation(FName AnimationID);
};
