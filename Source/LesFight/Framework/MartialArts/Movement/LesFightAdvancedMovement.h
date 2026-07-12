#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightAdvancedMovement.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementExecuted, EAdvancedMovementType, MovementType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementCompleted, EAdvancedMovementType, MovementType);

UCLASS(Blueprintable)
class ULesFightAdvancedMovement : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAdvancedMovement();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    bool ExecuteMovement(EAdvancedMovementType MovementType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    bool CanExecuteMovement(EAdvancedMovementType MovementType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    void CancelCurrentMovement();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    void SetMovementData(const TMap<EAdvancedMovementType, FAdvancedMovementData>& Data);

    UFUNCTION(BlueprintPure, Category = "MartialArts|Movement")
    bool IsMoving() const { return bIsMoving; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Movement")
    EAdvancedMovementType GetCurrentMovement() const { return CurrentMovement; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Movement")
    TArray<EAdvancedMovementType> GetAvailableMovements() const { return AvailableMovements; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    void SetAvailableMovements(const TArray<EAdvancedMovementType>& Movements);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    float GetMovementSpeed(EAdvancedMovementType MovementType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    float GetMovementDistance(EAdvancedMovementType MovementType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    float GetMovementDuration(EAdvancedMovementType MovementType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    void ClearCooldowns();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Movement")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMovementExecuted OnMovementExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMovementCompleted OnMovementCompleted;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bIsMoving;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EAdvancedMovementType CurrentMovement;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<EAdvancedMovementType> AvailableMovements;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TMap<EAdvancedMovementType, FAdvancedMovementData> MovementDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float CooldownMultiplier;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    EAdvancedMovementType PendingMovement;
    TMap<EAdvancedMovementType, float> CooldownTimers;
    float MovementTimer;
    int32 WallJumpCount;
    bool bOnWall;
    FVector MovementDirection;
    FVector StartPosition;

    void ProcessMovement(float DeltaTime);
    void OnMovementFinished();
    void ApplyMovementPhysics(EAdvancedMovementType MovementType);
    void UpdateCooldowns(float DeltaTime);
    bool IsOnCooldown(EAdvancedMovementType MovementType) const;
};
