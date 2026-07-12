#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightStaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, CurrentStamina, float, MaxStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExhausted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaRecovered);

UENUM(BlueprintType)
enum class EStaminaState : uint8
{
    Ready,
    Recovering,
    Exhausted,
    Regenerating
};

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightStaminaComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightStaminaComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void Initialize(float InMaxStamina, float InRecoveryRate);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    bool ConsumeStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void RecoverStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void SetCurrentStamina(float NewStamina);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void SetMaxStamina(float NewMaxStamina);

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void ResetStamina();

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void SetRecoveryRate(float NewRate) { RecoveryRate = NewRate; }

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    void SetRecoveryDelay(float Delay) { RecoveryDelay = Delay; }

    UFUNCTION(BlueprintPure, Category = "Stamina")
    float GetCurrentStamina() const { return CurrentStamina; }

    UFUNCTION(BlueprintPure, Category = "Stamina")
    float GetMaxStamina() const { return MaxStamina; }

    UFUNCTION(BlueprintPure, Category = "Stamina")
    float GetStaminaPercent() const;

    UFUNCTION(BlueprintPure, Category = "Stamina")
    bool IsExhausted() const { return StaminaState == EStaminaState::Exhausted; }

    UFUNCTION(BlueprintPure, Category = "Stamina")
    bool HasStaminaFor(float Cost) const { return CurrentStamina >= Cost; }

    UFUNCTION(BlueprintPure, Category = "Stamina")
    EStaminaState GetStaminaState() const { return StaminaState; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Stamina")
    float CurrentStamina;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
    float MaxStamina;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
    float RecoveryRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
    float RecoveryDelay;

    UPROPERTY(BlueprintReadOnly, Category = "Stamina")
    EStaminaState StaminaState;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStaminaChanged OnStaminaChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnExhausted OnExhausted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnStaminaRecovered OnStaminaRecovered;

private:
    float TimeSinceLastConsumption;
    bool bRecoveryPaused;
};
