#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LesFightAnimInstance.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
    Idle,
    Walking,
    Running,
    Sprinting,
    Jumping,
    Falling,
    Landing,
    Crouching
};

UCLASS()
class ULesFightAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    ULesFightAnimInstance();

    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetLocomotionSpeed(float Speed) { LocomotionSpeed = Speed; }

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetLocomotionDirection(float Direction) { LocomotionDirection = Direction; }

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetBlendSpaceParameter(const FName& ParameterName, float Value);

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetIsInAir(bool bInAir) { bIsInAir = bInAir; }

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetIsCrouching(bool bCrouching) { bIsCrouching = bCrouching; }

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetIsSprinting(bool bSprinting) { bIsSprinting = bSprinting; }

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetCharacterYaw(float Yaw) { CharacterYaw = Yaw; }

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void SetCharacterPitch(float Pitch) { CharacterPitch = Pitch; }

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerPunch();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerKick();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerBlock();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerHitReaction();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerVictory();

    UFUNCTION(BlueprintCallable, Category = "Animation")
    void TriggerDefeat();

    UFUNCTION(BlueprintPure, Category = "Animation")
    float GetLocomotionSpeed() const { return LocomotionSpeed; }

    UFUNCTION(BlueprintPure, Category = "Animation")
    float GetLocomotionDirection() const { return LocomotionDirection; }

    UFUNCTION(BlueprintPure, Category = "Animation")
    ELocomotionState GetLocomotionState() const { return CurrentLocomotionState; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float LocomotionSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float LocomotionDirection;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float CharacterYaw;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    float CharacterPitch;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsInAir;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsCrouching;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    bool bIsSprinting;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    ELocomotionState CurrentLocomotionState;

    UPROPERTY(BlueprintReadOnly, Category = "Animation")
    TObjectPtr<ALesFightBaseFighter> OwnerFighter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TMap<FName, float> BlendSpaceParameters;

private:
    void UpdateLocomotionState();
    void UpdateCharacterReferences();
};
