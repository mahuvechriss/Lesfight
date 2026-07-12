#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightThrowComponent.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class EThrowState : uint8
{
    Ready,
    Startup,
    Active,
    Recovery,
    Cooldown,
    TechWindow,
};

UENUM(BlueprintType)
enum class EThrowResult : uint8
{
    Whiff,
    Hit,
    Teched,
    Countered,
    Broken,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThrowStart, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThrowHit, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThrowWhiffed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThrowTeched);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnThrowBroken, AActor*, Breaker, EThrowResult, Result);

UCLASS(Blueprintable)
class ULesFightThrowComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightThrowComponent();

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "Throw")
    bool StartThrow();

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void PerformThrow();

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void EndThrow();

    UFUNCTION(BlueprintCallable, Category = "Throw")
    bool CanTechThrow() const;

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void TryTechThrow();

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void BreakThrow(ALesFightBaseFighter* Breaker);

    UFUNCTION(BlueprintPure, Category = "Throw")
    EThrowState GetThrowState() const { return ThrowState; }

    UFUNCTION(BlueprintPure, Category = "Throw")
    bool IsThrowing() const { return ThrowState == EThrowState::Active; }

    UFUNCTION(BlueprintPure, Category = "Throw")
    float GetThrowRange() const { return ThrowRange; }

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void SetThrowRange(float Range) { ThrowRange = Range; }

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void SetThrowDamage(float Damage) { ThrowDamage = Damage; }

    UFUNCTION(BlueprintCallable, Category = "Throw")
    void SetStartupFrames(int32 Frames) { StartupFrames = Frames; }

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnThrowStart OnThrowStart;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnThrowHit OnThrowHit;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnThrowWhiffed OnThrowWhiffed;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnThrowTeched OnThrowTeched;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnThrowBroken OnThrowBroken;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw")
    float ThrowRange;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw")
    float ThrowDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw")
    int32 StartupFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw")
    int32 ActiveFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw")
    int32 RecoveryFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Throw")
    float TechWindowDuration;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    TWeakObjectPtr<AActor> ThrowTarget;
    EThrowState ThrowState;
    int32 FrameCounter;
};
