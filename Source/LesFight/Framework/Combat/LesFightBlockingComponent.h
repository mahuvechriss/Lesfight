#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightAttackData.h"
#include "LesFightBlockingComponent.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class EBlockState : uint8
{
    None,
    Standing UMETA(DisplayName = "Standing Block"),
    Crouching UMETA(DisplayName = "Crouching Block"),
    AirBlock UMETA(DisplayName = "Air Block"),
    GuardBreak UMETA(DisplayName = "Guard Break"),
    GuardCrush UMETA(DisplayName = "Guard Crush"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBlockStateChanged, EBlockState, NewBlockState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBlockedAttack, AActor*, Attacker, const FAttackDefinition&, Attack);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGuardBreak);

UCLASS(Blueprintable)
class ULesFightBlockingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightBlockingComponent();

    UFUNCTION(BlueprintCallable, Category = "Blocking")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "Blocking")
    void StartBlocking(EBlockState BlockState);

    UFUNCTION(BlueprintCallable, Category = "Blocking")
    void StopBlocking();

    UFUNCTION(BlueprintCallable, Category = "Blocking")
    bool TryBlock(const FAttackDefinition& Attack, AActor* Attacker);

    UFUNCTION(BlueprintCallable, Category = "Blocking")
    void ResetGuardMeter();

    UFUNCTION(BlueprintCallable, Category = "Blocking")
    void AddGuardDamage(float Damage);

    UFUNCTION(BlueprintCallable, Category = "Blocking")
    void ApplyGuardRegen(float DeltaTime);

    UFUNCTION(BlueprintPure, Category = "Blocking")
    bool IsBlocking() const { return bIsBlocking; }

    UFUNCTION(BlueprintPure, Category = "Blocking")
    EBlockState GetBlockState() const { return CurrentBlockState; }

    UFUNCTION(BlueprintPure, Category = "Blocking")
    float GetGuardMeter() const { return GuardMeter; }

    UFUNCTION(BlueprintPure, Category = "Blocking")
    float GetGuardMeterMax() const { return GuardMeterMax; }

    UFUNCTION(BlueprintPure, Category = "Blocking")
    bool CanBlockAttack(const FAttackDefinition& Attack) const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnBlockStateChanged OnBlockStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnBlockedAttack OnBlockedAttack;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnGuardBreak OnGuardBreak;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float GuardMeterMax;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float GuardRegenRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float GuardRegenDelay;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float ChipDamageMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float PushbackDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float BlockstunDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float GuardBreakThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Blocking")
    float GuardCrushDuration;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    bool bIsBlocking;
    EBlockState CurrentBlockState;
    float GuardMeter;
    float LastGuardDamageTime;

    bool IsAttackBlockable(const FAttackDefinition& Attack) const;
};
