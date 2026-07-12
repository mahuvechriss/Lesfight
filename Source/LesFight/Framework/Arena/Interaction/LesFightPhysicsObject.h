#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightPhysicsObject.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class ULesFightPhysicsObject : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void InitializePhysics(AActor* Actor, float InMass, bool bSimulatePhysics);

    UFUNCTION(BlueprintCallable)
    void ApplyForce(FVector Force);

    UFUNCTION(BlueprintCallable)
    void ApplyImpulse(FVector Impulse, FVector Location);

    UFUNCTION(BlueprintCallable)
    void ApplyTorque(FVector Torque);

    UFUNCTION(BlueprintCallable)
    void EnablePhysics(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsPhysicsEnabled() const;

    UFUNCTION(BlueprintCallable)
    float GetMass() const;

    UFUNCTION(BlueprintCallable)
    void SetMass(float InMass);

    UFUNCTION(BlueprintCallable)
    void SetLinearDamping(float Damping);

    UFUNCTION(BlueprintCallable)
    void SetAngularDamping(float Damping);

    UFUNCTION(BlueprintCallable)
    void Sleep();

    UFUNCTION(BlueprintCallable)
    void WakeUp();

    UFUNCTION(BlueprintCallable)
    bool IsAsleep() const;

    UFUNCTION(BlueprintCallable)
    void ResetPhysicsState();

    void Initialize(ULesFightArenaWorldManager* InManager);

protected:
    UPROPERTY()
    float Mass = 50.0f;

    UPROPERTY()
    float LinearDamping = 0.05f;

    UPROPERTY()
    float AngularDamping = 0.1f;

    UPROPERTY()
    bool bPhysicsEnabled = false;

    UPROPERTY()
    bool bAsleep = false;

    UPROPERTY()
    AActor* OwnerActor;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;

    FVector AccumulatedForces;
};
