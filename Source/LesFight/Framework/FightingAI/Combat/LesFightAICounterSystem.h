#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAICounterSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCounterExecuted, EAIActionType, CounterType);

UCLASS(Blueprintable)
class ULesFightAICounterSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Counter")
    bool CanCounter(const FAIPerceptionData& Perception) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Counter")
    void ExecuteCounter(FAIDecisionContext& Context);

    UFUNCTION(BlueprintCallable, Category = "AI|Counter")
    EAIActionType GetCounterType() const { return CounterType; }

    UFUNCTION(BlueprintCallable, Category = "AI|Counter")
    void LearnCounterTiming(EAIActionType AttackType, float SuccessTime);

    UFUNCTION(BlueprintCallable, Category = "AI|Counter")
    float GetCounterRate() const { return CounterRate; }

    UFUNCTION(BlueprintCallable, Category = "AI|Counter")
    void SetCounterAggression(float Aggression);

    UFUNCTION(BlueprintCallable, Category = "AI|Counter")
    void Initialize(class ULesFightAIFighterController* InController);

    UPROPERTY(BlueprintAssignable, Category = "AI|Counter")
    FOnCounterExecuted OnCounterExecuted;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Counter")
    EAIActionType CounterType;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Counter")
    float CounterRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    float CounterAggression;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Counter")
    TMap<EAIActionType, float> CounterTimings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Counter")
    float CounterWindow;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
