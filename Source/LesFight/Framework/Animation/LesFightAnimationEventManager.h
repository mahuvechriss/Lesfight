#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationEventManager.generated.h"

class ULesFightCharacterAnimationComponent;

USTRUCT(BlueprintType)
struct FAnimEventInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EventTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EventDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bTriggered;

    FAnimEventInfo()
        : EventName(NAME_None)
        , EventTime(0.0f)
        , EventDuration(0.0f)
        , bTriggered(false)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAnimEventTriggered, FName, EventName,
    float, EventTime, AActor*, Instigator);

UCLASS(Blueprintable)
class ULesFightAnimationEventManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationEventManager();

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void RegisterEvent(FName EventName, float TriggerTime);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void RegisterTimedEvent(FName EventName, float TriggerTime, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void TriggerEvent(FName EventName);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void TriggerComboWindow(bool bOpen);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void TriggerFootstep();

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void TriggerHitEvent(FName HitBone);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void TriggerSoundEvent(USoundBase* Sound, float Volume = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void TriggerCameraShake(TSubclassOf<UCameraShakeBase> Shake);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void TriggerEffectEvent(UParticleSystem* Effect, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void ResetAllEvents();

    UFUNCTION(BlueprintCallable, Category = "Animation Events")
    void SetEventTimingMultiplier(float Multiplier) { EventTimingMultiplier = Multiplier; }

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimEventTriggered OnAnimEventTriggered;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Events")
    TArray<FAnimEventInfo> RegisteredEvents;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Events")
    float EventTimingMultiplier;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    float CurrentAnimTime;
    TArray<FName> TriggeredEvents;
};
