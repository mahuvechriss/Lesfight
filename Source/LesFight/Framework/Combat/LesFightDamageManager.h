#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightDamageManager.generated.h"

USTRUCT(BlueprintType)
struct FDamageResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    float BaseDamage;

    UPROPERTY(BlueprintReadOnly)
    float ScaledDamage;

    UPROPERTY(BlueprintReadOnly)
    float FinalDamage;

    UPROPERTY(BlueprintReadOnly)
    float KnockbackForce;

    UPROPERTY(BlueprintReadOnly)
    float LaunchForce;

    UPROPERTY(BlueprintReadOnly)
    int32 HitstunFrames;

    UPROPERTY(BlueprintReadOnly)
    int32 BlockstunFrames;

    UPROPERTY(BlueprintReadOnly)
    bool bWasCrit;

    UPROPERTY(BlueprintReadOnly)
    EHitReaction HitReaction;

    FDamageResult()
        : BaseDamage(0.0f), ScaledDamage(0.0f), FinalDamage(0.0f)
        , KnockbackForce(0.0f), LaunchForce(0.0f)
        , HitstunFrames(0), BlockstunFrames(0)
        , bWasCrit(false)
        , HitReaction(EHitReaction::LightStun)
    {}
};

UCLASS(Blueprintable)
class ULesFightDamageManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightDamageManager();

    UFUNCTION(BlueprintCallable, Category = "Damage")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Damage")
    float CalculateDamage(const FAttackDefinition& Attack, int32 ComboCount = 0);

    UFUNCTION(BlueprintCallable, Category = "Damage")
    FDamageResult CalculateFullDamage(const FAttackDefinition& Attack, int32 ComboCount = 0, bool bIsBlocked = false);

    UFUNCTION(BlueprintCallable, Category = "Damage")
    float ApplyDamageScaling(float BaseDamage, int32 ComboCount) const;

    UFUNCTION(BlueprintCallable, Category = "Damage")
    bool RollCriticalHit(const FAttackDefinition& Attack) const;

    UFUNCTION(BlueprintCallable, Category = "Damage")
    float GetKnockbackDistance(float BaseKnockback, float TargetWeight) const;

    UFUNCTION(BlueprintCallable, Category = "Damage")
    int32 GetHitstunDuration(float Damage, EHitReaction ReactionType) const;

    UFUNCTION(BlueprintCallable, Category = "Damage")
    void SetDamageMultiplier(float Multiplier) { GlobalDamageMultiplier = Multiplier; }

    UFUNCTION(BlueprintPure, Category = "Damage")
    float GetDamageMultiplier() const { return GlobalDamageMultiplier; }

    UFUNCTION(BlueprintCallable, Category = "Damage")
    void SetComboScalingEnabled(bool bEnabled) { bComboScalingEnabled = bEnabled; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float GlobalDamageMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float ComboScalingReduction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float MinimumScaling;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float BlockDamageReduction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float CritChanceMultiplier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float WeightKnockbackFactor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    bool bComboScalingEnabled;

private:
    float KnockbackForceMultiplier;
    int32 BaseHitstun;
};
