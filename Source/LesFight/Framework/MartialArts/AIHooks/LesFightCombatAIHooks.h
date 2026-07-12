#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightCombatAIHooks.generated.h"

USTRUCT(BlueprintType)
struct FAICombatDecisionContext
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    AActor* Self;

    UPROPERTY(BlueprintReadOnly)
    AActor* Target;

    UPROPERTY(BlueprintReadOnly)
    float DistanceToTarget;

    UPROPERTY(BlueprintReadOnly)
    float HealthPercent;

    UPROPERTY(BlueprintReadOnly)
    float StaminaPercent;

    UPROPERTY(BlueprintReadOnly)
    float UltimatePercent;

    UPROPERTY(BlueprintReadOnly)
    bool bTargetInAir;

    UPROPERTY(BlueprintReadOnly)
    bool bTargetNearWall;

    UPROPERTY(BlueprintReadOnly)
    bool bTargetAttacking;

    UPROPERTY(BlueprintReadOnly)
    bool bSelfInCombo;

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentComboCount;

    UPROPERTY(BlueprintReadOnly)
    FCombatAIHooks AIProfile;

    FAICombatDecisionContext()
        : Self(nullptr), Target(nullptr)
        , DistanceToTarget(0.0f), HealthPercent(1.0f)
        , StaminaPercent(1.0f), UltimatePercent(0.0f)
        , bTargetInAir(false), bTargetNearWall(false)
        , bTargetAttacking(false), bSelfInCombo(false)
        , CurrentComboCount(0)
    {}
};

UCLASS(Blueprintable)
class ULesFightCombatAIHooks : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCombatAIHooks();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    void SetAIProfile(const FCombatAIHooks& Profile);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    FCombatAIHooks GetAIProfile() const { return CurrentProfile; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    FAICombatDecisionContext CreateDecisionContext(AActor* Self, AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    void SetPreferredStyle(EFightingStyle Style) { CurrentProfile.PreferredStyle = Style; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    void SetPreferredDistance(EPreferredDistance Distance);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    void SetAggressionLevel(EAggressionLevel Level);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    void SetCounterProbability(float Probability);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    void SetDodgeProbability(float Probability);

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    EFightingStyle GetPreferredStyle() const { return CurrentProfile.PreferredStyle; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    EPreferredDistance GetPreferredDistance() const { return CurrentProfile.PreferredDistance; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    EAggressionLevel GetAggressionLevel() const { return CurrentProfile.AggressionLevel; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    float GetCounterProbability() const { return CurrentProfile.CounterProbability; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    float GetDodgeProbability() const { return CurrentProfile.DodgeProbability; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    float GetComboLengthPreference() const { return CurrentProfile.ComboLengthPreference; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    float GetDefensiveReactionTime() const { return CurrentProfile.DefensiveReactionTime; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    float GetOffensiveReactionTime() const { return CurrentProfile.OffensiveReactionTime; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    bool ShouldUseUltimate() const { return CurrentProfile.bUsesUltimate; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|AI")
    bool ShouldUseEnvironmental() const { return CurrentProfile.bUsesEnvironmental; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|AI")
    void ResetToDefaults();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    FCombatAIHooks CurrentProfile;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
};
