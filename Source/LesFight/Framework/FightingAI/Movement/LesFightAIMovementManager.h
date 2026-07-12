#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIMovementManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIMovementManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void UpdateMovement(const FAIPerceptionData& Perception, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void SetDesiredRange(EAICombatRange Range);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    EAICombatRange GetDesiredRange() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void MoveTowardTarget(float Speed);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void RetreatFromTarget(float Speed);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void StrafeAroundTarget(float Direction);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void CloseDistance();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void CreateDistance();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    float GetCurrentSpeed() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    bool IsMoving() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void StopMovement();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Movement")
    void SetNavigationEnabled(bool bEnabled);

    void Initialize(ULesFightAIFighterController* InController);

protected:
    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Movement")
    EAICombatRange DesiredRange;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Movement")
    EAICombatRange CurrentRange;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Movement")
    float CurrentSpeed;

    UPROPERTY(EditDefaultsOnly, Category = "FightingAI|Movement")
    float MovementSpeed = 600.0f;

    UPROPERTY()
    FVector MoveTarget;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Movement")
    bool bNavigationEnabled;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Movement")
    bool bIsMoving;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
