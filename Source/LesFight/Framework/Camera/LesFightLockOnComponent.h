#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightLockOnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLockOnTargetChanged, AActor*, NewTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLockOnLost);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightLockOnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightLockOnComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    bool TryLockOnTarget();

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void ClearLockOn();

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void CycleTarget(int32 Direction);

    UFUNCTION(BlueprintPure, Category = "LockOn")
    bool IsLockedOn() const { return CurrentTarget != nullptr; }

    UFUNCTION(BlueprintPure, Category = "LockOn")
    AActor* GetCurrentTarget() const { return CurrentTarget; }

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void SetLockOnRange(float NewRange) { LockOnRange = NewRange; }

    UFUNCTION(BlueprintCallable, Category = "LockOn")
    void SetLockOnAngle(float NewAngle) { LockOnAngle = NewAngle; }

    UFUNCTION(BlueprintPure, Category = "LockOn")
    float GetLockOnRange() const { return LockOnRange; }

    UFUNCTION(BlueprintPure, Category = "LockOn")
    TArray<AActor*> GetPotentialTargets() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn")
    float LockOnRange;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn")
    float LockOnAngle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn")
    float LockOnBreakRange;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn")
    TArray<TSubclassOf<AActor>> LockableClasses;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLockOnTargetChanged OnLockOnTargetChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLockOnLost OnLockOnLost;

    UPROPERTY()
    TObjectPtr<AActor> CurrentTarget;

private:
    UPROPERTY()
    TArray<AActor*> CachedTargets;

    void FindTargetsInRange();
    bool IsValidTarget(AActor* Target) const;
    void BreakLockOnIfOutOfRange();
};
