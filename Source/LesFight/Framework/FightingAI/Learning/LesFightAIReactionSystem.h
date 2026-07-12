#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIReactionSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReactionTriggered, EAIActionType, Reaction);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIReactionSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAIReactionSystem();

    UFUNCTION(BlueprintCallable)
    void ReactToEvent(EAIAnimationEvent Event, const FAIPerceptionData& Perception);

    UFUNCTION(BlueprintCallable)
    EAIActionType GetReactionAction() const { return ReactionAction; }

    UFUNCTION(BlueprintCallable)
    float GetReactionDelay() const { return ReactionDelay; }

    UFUNCTION(BlueprintCallable)
    void SetBaseReactionTime(float Min, float Max);

    UFUNCTION(BlueprintCallable)
    float GetCurrentReactionTime() const;

    UFUNCTION(BlueprintCallable)
    void ReactToPlayerAttack(const FAIPerceptionData& Perception);

    UFUNCTION(BlueprintCallable)
    void ReactToMissedAttack();

    UFUNCTION(BlueprintCallable)
    void ReactToLowHealth();

    UFUNCTION(BlueprintCallable)
    void ReactToStaminaExhausted();

    UFUNCTION(BlueprintCallable)
    void ReactToUltimateOpportunity();

    UPROPERTY(BlueprintAssignable, Category = "Reaction")
    FOnReactionTriggered OnReactionTriggered;

protected:
    UPROPERTY()
    EAIActionType ReactionAction;

    UPROPERTY()
    float ReactionDelay;

    UPROPERTY(EditDefaultsOnly, Category = "Reaction")
    float BaseReactionMin;

    UPROPERTY(EditDefaultsOnly, Category = "Reaction")
    float BaseReactionMax;

    UPROPERTY()
    TMap<EAIAnimationEvent, EAIActionType> DefaultReactions;

    UPROPERTY()
    TArray<float> RecentReactionTimes;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
