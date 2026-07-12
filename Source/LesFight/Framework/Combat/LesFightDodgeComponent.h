#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightDodgeComponent.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class EDodgeState : uint8
{
    Ready,
    Dodging,
    Cooldown,
    Failed,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDodgeStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDodgeSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDodgeFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDodgeCooldown);

UCLASS(Blueprintable)
class ULesFightDodgeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightDodgeComponent();

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    bool StartDodge(FVector Direction);

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void EndDodge();

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    bool TryDodgeAttack(FVector AttackDirection);

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void ResetDodge();

    UFUNCTION(BlueprintPure, Category = "Dodge")
    EDodgeState GetDodgeState() const { return DodgeState; }

    UFUNCTION(BlueprintPure, Category = "Dodge")
    bool IsDodging() const { return DodgeState == EDodgeState::Dodging; }

    UFUNCTION(BlueprintPure, Category = "Dodge")
    bool IsDodgeAvailable() const { return DodgeState == EDodgeState::Ready; }

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void SetDodgeDistance(float Distance) { DodgeDistance = Distance; }

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void SetDodgeDuration(float Duration) { DodgeDuration = Duration; }

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void SetDodgeCooldown(float Cooldown) { DodgeCooldown = Cooldown; }

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void SetDodgeSpeed(float Speed) { DodgeSpeed = Speed; }

    UFUNCTION(BlueprintCallable, Category = "Dodge")
    void SetInvulnerabilityFrames(int32 Frames) { InvulnerabilityFrames = Frames; }

    UFUNCTION(BlueprintPure, Category = "Dodge")
    float GetDodgeDuration() const { return DodgeDuration; }

    UFUNCTION(BlueprintPure, Category = "Dodge")
    float GetDodgeCooldown() const { return DodgeCooldown; }

pROTECTED:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDodgeStart OnDodgeStart;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDodgeSuccess OnDodgeSuccess;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDodgeFailed OnDodgeFailed;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDodgeCooldown OnDodgeCooldown;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
    float DodgeDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
    float DodgeDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
    float DodgeCooldown;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
    float DodgeSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
    int32 InvulnerabilityFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
    float DodgeCostStamina;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    EDodgeState DodgeState;
    FVector DodgeDirection;
    float DodgeTimer;
    float CooldownTimer;
    int32 iFrameCount;
};
