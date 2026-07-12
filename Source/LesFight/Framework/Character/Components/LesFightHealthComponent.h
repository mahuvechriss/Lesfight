#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRevived);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageTaken, float, DamageAmount, AActor*, DamageInstigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealingReceived, float, HealAmount, AActor*, Healer);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightHealthComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Initialize(float InMaxHealth);

    UFUNCTION(BlueprintCallable, Category = "Health")
    float TakeDamage(float DamageAmount, AActor* DamageInstigator = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Health")
    float Heal(float HealAmount, AActor* Healer = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetCurrentHealth(float NewHealth);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetMaxHealth(float NewMaxHealth);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void ResetHealth();

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Kill();

    UFUNCTION(BlueprintCallable, Category = "Health")
    void Revive(float HealthPercent = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void SetInvulnerable(bool bInvulnerable, float Duration = 0.0f);

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetCurrentHealth() const { return CurrentHealth; }

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintPure, Category = "Health")
    bool IsAlive() const { return CurrentHealth > 0.0f; }

    UFUNCTION(BlueprintPure, Category = "Health")
    bool IsDead() const { return bIsDead; }

    UFUNCTION(BlueprintPure, Category = "Health")
    bool IsInvulnerable() const { return bIsInvulnerable; }

    UFUNCTION(BlueprintPure, Category = "Health")
    float GetDamageTaken() const { return TotalDamageTaken; }

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Health")
    float CurrentHealth;

    UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    float MaxHealth;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHealthChanged OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDeath OnDeath;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRevived OnRevived;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDamageTaken OnDamageTaken;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHealingReceived OnHealingReceived;

private:
    bool bIsDead;
    bool bIsInvulnerable;
    float TotalDamageTaken;
    float TotalHealingReceived;
    FTimerHandle InvulnerabilityTimer;

    UFUNCTION()
    void EndInvulnerability();
};
