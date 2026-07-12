#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightFightingStyle.generated.h"

UCLASS(Blueprintable, Abstract)
class ULesFightFightingStyle : public UObject
{
    GENERATED_BODY()

public:
    ULesFightFightingStyle();

    virtual void Initialize(EFightingStyle InStyleID);
    virtual void OnEquip();
    virtual void OnUnequip();
    virtual void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Style")
    EFightingStyle GetStyleID() const { return StyleID; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Style")
    FStyleAttributes GetAttributes() const { return Attributes; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Style")
    void SetAttributes(const FStyleAttributes& NewAttributes);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Style")
    FStyleAudioProfile GetAudioProfile() const { return AudioProfile; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Style")
    void SetAudioProfile(const FStyleAudioProfile& Profile) { AudioProfile = Profile; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Style")
    FStyleVFXProfile GetVFXProfile() const { return VFXProfile; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Style")
    void SetVFXProfile(const FStyleVFXProfile& Profile) { VFXProfile = Profile; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual TArray<ECombatStance> GetAvailableStances() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual TArray<EAdvancedMovementType> GetAvailableMovements() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual TArray<ECounterType> GetAvailableCounters() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual TArray<EAdvancedDodgeType> GetAvailableDodges() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual TArray<EComboExpansionType> GetAvailableCombos() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual TArray<EEnvironmentInteraction> GetAvailableInteractions() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual TArray<ECinematicEffect> GetAvailableCinematics() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual FName GetStanceAnimation(ECombatStance Stance) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual FName GetAttackAnimation(int32 ComboStep) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual FName GetCounterAnimation(ECounterType CounterType) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual FName GetDodgeAnimation(EAdvancedDodgeType DodgeType) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual FName GetMovementAnimation(EAdvancedMovementType MovementType) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Style")
    virtual FName GetUltimateAnimation() const;

    virtual float GetDamageMultiplier() const;
    virtual float GetSpeedMultiplier() const;
    virtual float GetDefenseMultiplier() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Style")
    EFightingStyle StyleID;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    FStyleAttributes Attributes;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    FStyleAudioProfile AudioProfile;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    FStyleVFXProfile VFXProfile;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    TArray<ECombatStance> AvailableStances;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    TArray<EAdvancedMovementType> AvailableMovements;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    TArray<ECounterType> AvailableCounters;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    TArray<EAdvancedDodgeType> AvailableDodges;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    TArray<EComboExpansionType> AvailableCombos;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    TArray<EEnvironmentInteraction> AvailableInteractions;

    UPROPERTY(BlueprintReadOnly, Category = "Style")
    TArray<ECinematicEffect> AvailableCinematics;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
    TMap<ECombatStance, FName> StanceAnimations;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
    TMap<int32, FName> AttackAnimations;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
    TMap<ECounterType, FName> CounterAnimations;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
    TMap<EAdvancedDodgeType, FName> DodgeAnimations;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
    TMap<EAdvancedMovementType, FName> MovementAnimations;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
    FName UltimateMontageName;
};
