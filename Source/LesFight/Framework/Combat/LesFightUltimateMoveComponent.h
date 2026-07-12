#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightComboData.h"
#include "LesFightUltimateMoveComponent.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class EUltimateState : uint8
{
    Ready,
    Startup,
    Active,
    Recovery,
    Cooldown,
    Interrupted,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateExecuted, FName, UltimateID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateInterrupted, FName, UltimateID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateReady);

UCLASS(Blueprintable)
class ULesFightUltimateMoveComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightUltimateMoveComponent();

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void Initialize(ALesFightBaseFighter* InOwner);

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void RegisterUltimateMove(const FUltimateMoveDefinition& UltimateDef);

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    bool TryExecuteUltimate(FName UltimateID);

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void StartUltimate(FName UltimateID);

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void EndUltimate();

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void InterruptUltimate();

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void AddMeter(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void ResetMeter();

    UFUNCTION(BlueprintCallable, Category = "Ultimate")
    void SetSuperMeterMax(float Max) { SuperMeterMax = Max; }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    EUltimateState GetUltimateState() const { return CurrentState; }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    bool IsExecutingUltimate() const { return CurrentState == EUltimateState::Active; }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    bool IsUltimateReady() const { return CurrentState == EUltimateState::Ready && HasFullMeter(); }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    float GetSuperMeter() const { return SuperMeter; }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    float GetSuperMeterMax() const { return SuperMeterMax; }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    bool HasFullMeter() const { return SuperMeter >= SuperMeterMax; }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    float GetMeterRatio() const { return SuperMeterMax > 0.0f ? SuperMeter / SuperMeterMax : 0.0f; }

    UFUNCTION(BlueprintPure, Category = "Ultimate")
    TArray<FName> GetAvailableUltimates() const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnUltimateExecuted OnUltimateExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnUltimateInterrupted OnUltimateInterrupted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnUltimateReady OnUltimateReady;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
    float SuperMeterMax;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
    float MeterBuildRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
    int32 StartupFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
    int32 RecoveryFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
    bool bInvulnerableDuringUltimate;

private:
    TWeakObjectPtr<ALesFightBaseFighter> OwnerFighter;
    TMap<FName, FUltimateMoveDefinition> RegisteredUltimates;
    EUltimateState CurrentState;
    float SuperMeter;
    FName CurrentUltimateID;
    int32 FrameCounter;
};
