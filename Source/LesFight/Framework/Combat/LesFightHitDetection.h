#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightHitDetection.generated.h"

class ALesFightBaseFighter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHitConfirmed, AActor*, Target, const FHitResult&, HitResult);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitMissed);

USTRUCT(BlueprintType)
struct FHitResultData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    bool bHit;

    UPROPERTY(BlueprintReadOnly)
    TObjectPtr<AActor> HitActor;

    UPROPERTY(BlueprintReadOnly)
    FVector HitLocation;

    UPROPERTY(BlueprintReadOnly)
    FVector HitNormal;

    UPROPERTY(BlueprintReadOnly)
    FName HitBone;

    UPROPERTY(BlueprintReadOnly)
    EBlockType BlockType;

    FHitResultData()
        : bHit(false), HitActor(nullptr)
        , HitLocation(FVector::ZeroVector)
        , HitNormal(FVector::ZeroVector)
        , HitBone(NAME_None)
        , BlockType(EBlockType::None)
    {}
};

UCLASS(Blueprintable)
class ULesFightHitDetection : public UObject
{
    GENERATED_BODY()

public:
    ULesFightHitDetection();

    UFUNCTION(BlueprintCallable, Category = "HitDetection")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "HitDetection")
    FHitResultData PerformHitCheck(FName AttackID);

    UFUNCTION(BlueprintCallable, Category = "HitDetection")
    FHitResultData PerformThrowCheck();

    UFUNCTION(BlueprintCallable, Category = "HitDetection")
    void SetHitboxEnabled(bool bEnabled) { bHitboxEnabled = bEnabled; }

    UFUNCTION(BlueprintCallable, Category = "HitDetection")
    void SetHitboxVisible(bool bVisible) { bDebugDrawHitbox = bVisible; }

    UFUNCTION(BlueprintPure, Category = "HitDetection")
    TArray<AActor*> GetHitActorsThisAttack() const { return HitActorsThisAttack; }

    UFUNCTION(BlueprintCallable, Category = "HitDetection")
    void ResetHitActors();

    UFUNCTION(BlueprintPure, Category = "HitDetection")
    FHitboxShape GetCurrentHitbox() const { return CurrentHitbox; }

    UFUNCTION(BlueprintPure, Category = "HitDetection")
    TArray<FHurtboxShape> GetCurrentHurtboxes() const { return CurrentHurtboxes; }

    UFUNCTION(BlueprintPure, Category = "HitDetection")
    bool HasHitThisAttack(AActor* Actor) const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHitConfirmed OnHitConfirmed;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnHitMissed OnHitMissed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitDetection")
    float HitboxForwardOffset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitDetection")
    float HitboxRadius;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitDetection")
    float HitboxHalfHeight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitDetection")
    float ThrowRange;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HitDetection")
    TArray<TEnumAsByte<ECollisionChannel>> HitDetectionChannels;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    TArray<AActor*> HitActorsThisAttack;
    FHitboxShape CurrentHitbox;
    TArray<FHurtboxShape> CurrentHurtboxes;
    bool bHitboxEnabled;
    bool bDebugDrawHitbox;

    FHitResultData CheckHitboxCollision(const FHitboxShape& Hitbox);
    void DrawDebugHitbox(const FHitboxShape& Hitbox);
    bool IsAttackBlocked(ALesFightBaseFighter* Target) const;
};
