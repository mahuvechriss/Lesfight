#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightPhysicsMotion.generated.h"

UCLASS(Blueprintable)
class ULesFightPhysicsMotion : public UObject
{
    GENERATED_BODY()

public:
    ULesFightPhysicsMotion();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void ApplyMomentum(FVector Impulse, float Weight = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void ApplyBodyWeight(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void RecoverFromHit(float RecoveryRate);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void SetPhysicsSettings(const FPhysicsMotionSettings& Settings);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void ToggleClothPhysics(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void ToggleHairPhysics(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void ToggleAccessoryPhysics(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Physics")
    void ResetPhysics();

    UFUNCTION(BlueprintPure, Category = "MartialArts|Physics")
    bool IsClothEnabled() const { return Settings.bClothEnabled; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Physics")
    bool IsHairEnabled() const { return Settings.bHairEnabled; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Physics")
    FVector GetCurrentMomentum() const { return CurrentMomentum; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Physics")
    float GetBodyWeightInfluence() const { return Settings.BodyWeightInfluence; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Physics")
    FPhysicsMotionSettings GetSettings() const { return Settings; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    FVector CurrentMomentum;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float CurrentRecovery;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FPhysicsMotionSettings Settings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MomentumDecayRate;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    TWeakObjectPtr<class ACharacter> OwnerCharacter;

    void ApplyClothPhysics(float DeltaTime);
    void ApplyHairPhysics(float DeltaTime);
    void ApplyAccessoryPhysics(float DeltaTime);
    void ApplySecondaryMotion(float DeltaTime);
    void UpdateMomentum(float DeltaTime);
    void UpdateRecovery(float DeltaTime);
    void ApplySimulationLevel(EPhysicsSimulation Level);
};
