#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LesFightBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ULesFightBasePawn;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
    Idle,
    Walking,
    Running,
    Jumping,
    Falling,
    Attacking,
    Blocking,
    HitStun,
    KnockedDown,
    GettingUp,
    Dead
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStateChanged, ECharacterState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageReceived, float, DamageAmount, AActor*, DamageInstigator);

UCLASS()
class ALesFightBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ALesFightBaseCharacter(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
        class AController* EventInstigator, AActor* DamageCauser) override;
    virtual void Destroyed() override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Character")
    void SetCharacterState(ECharacterState NewState);

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    ECharacterState GetCharacterState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Character")
    void SetHealth(float NewHealth);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Character")
    void ResetCharacter();

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    bool IsAlive() const { return Health > 0.0f; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    bool IsInvulnerable() const { return bIsInvulnerable; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Character")
    void SetInvulnerable(bool bInvulnerable, float Duration = 0.0f);

    UFUNCTION(BlueprintPure, Category = "LesFight|Camera")
    UCameraComponent* GetFollowCamera() const { return FollowCamera; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Camera")
    USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Character")
    float MaxHealth;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Character")
    float Health;

    UPROPERTY(BlueprintReadOnly, Category = "LesFight|Character")
    ECharacterState CurrentState;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnCharacterStateChanged OnCharacterStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnDamageReceived OnDamageReceived;

private:
    UPROPERTY()
    bool bIsInvulnerable;

    FTimerHandle InvulnerabilityTimer;

    UFUNCTION()
    void EndInvulnerability();

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
