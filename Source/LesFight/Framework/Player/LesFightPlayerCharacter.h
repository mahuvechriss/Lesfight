#pragma once

#include "CoreMinimal.h"
#include "Core/LesFightBaseCharacter.h"
#include "LesFightCharacterMovementComponent.h"
#include "LesFightCharacterStateMachine.h"
#include "LesFightPlayerCharacter.generated.h"

class ULesFightFollowCameraComponent;
class ULesFightLockOnComponent;

UCLASS()
class ALesFightPlayerCharacter : public ALesFightBaseCharacter
{
    GENERATED_BODY()

public:
    ALesFightPlayerCharacter(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Landed(const FHitResult& Hit) override;

    UFUNCTION(BlueprintCallable, Category = "Player")
    void MoveForward(float Value);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void MoveRight(float Value);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void Turn(float Rate);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void LookUp(float Rate);

    UFUNCTION(BlueprintCallable, Category = "Player")
    void StartSprint();

    UFUNCTION(BlueprintCallable, Category = "Player")
    void StopSprint();

    UFUNCTION(BlueprintCallable, Category = "Player")
    void StartCrouch();

    UFUNCTION(BlueprintCallable, Category = "Player")
    void StopCrouch();

    UFUNCTION(BlueprintCallable, Category = "Player")
    void JumpPressed();

    UFUNCTION(BlueprintCallable, Category = "Player")
    void JumpReleased();

    UFUNCTION(BlueprintPure, Category = "Player")
    ULesFightCharacterMovementComponent* GetLesFightMovement() const;

    UFUNCTION(BlueprintPure, Category = "Player")
    ULesFightCharacterStateMachine* GetStateMachine() const { return StateMachine; }

    UFUNCTION(BlueprintPure, Category = "Player|Camera")
    ULesFightFollowCameraComponent* GetFollowCamera() const { return FollowCameraComponent; }

    UFUNCTION(BlueprintPure, Category = "Player|Camera")
    ULesFightLockOnComponent* GetLockOnComponent() const { return LockOnComponent; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
    TObjectPtr<ULesFightFollowCameraComponent> FollowCameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|Camera")
    TObjectPtr<ULesFightLockOnComponent> LockOnComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player|State")
    TObjectPtr<ULesFightCharacterStateMachine> StateMachine;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Movement")
    float TurnRateGamepad;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player|Movement")
    float LookUpRateGamepad;

private:
    float InputForward;
    float InputRight;
    bool bJumpHeld;
    bool bSprintHeld;
};
