#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkSecurity.generated.h"

USTRUCT(BlueprintType)
struct FSecurityValidationResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    bool bIsValid;

    UPROPERTY(BlueprintReadOnly)
    FString ValidationMessage;

    UPROPERTY(BlueprintReadOnly)
    float SeverityScore;

    FSecurityValidationResult()
        : bIsValid(true)
        , ValidationMessage(TEXT(""))
        , SeverityScore(0.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightNetworkSecurity : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkSecurity();

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    FSecurityValidationResult ValidateCombatAction(int32 PlayerIndex, const FNetworkCombatAction& Action);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    FSecurityValidationResult ValidatePlayerState(int32 PlayerIndex, float Health, float Stamina, float Meter);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    FSecurityValidationResult ValidatePosition(int32 PlayerIndex, FVector Position, FVector LastPosition);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    FSecurityValidationResult ValidateAnimationState(int32 PlayerIndex, const FNetworkAnimSyncData& AnimData);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    void ReportSuspiciousActivity(int32 PlayerIndex, const FString& Reason, float Severity);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    bool IsPlayerSuspicious(int32 PlayerIndex) const;

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    TArray<int32> GetSuspiciousPlayers() const;

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    void EnableValidation(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    bool IsValidationEnabled() const { return bValidationEnabled; }

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    void SetMaxPositionDelta(float MaxDelta);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    void SetMaxHealthChange(float MaxChange);

    UFUNCTION(BlueprintCallable, Category = "Network|Security")
    void ResetPlayerTracking(int32 PlayerIndex);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxPositionDeltaPerTick;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxHealthChangePerAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxStaminaChangePerAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float MaxMeterChangePerAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float SuspiciousThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxActionsPerSecond;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bValidationEnabled;

private:
    struct FPlayerSecurityState
    {
        float SuspicionScore;
        int32 ActionsThisSecond;
        float ActionTimer;
        float LastHealth;
        float LastStamina;
        float LastMeter;
        FVector LastPosition;
        TArray<FString> Violations;

        FPlayerSecurityState()
            : SuspicionScore(0.0f)
            , ActionsThisSecond(0)
            , ActionTimer(0.0f)
            , LastHealth(-1.0f)
            , LastStamina(-1.0f)
            , LastMeter(-1.0f)
            , LastPosition(FVector::ZeroVector)
        {}
    };

    TMap<int32, FPlayerSecurityState> PlayerSecurityStates;

    FPlayerSecurityState& GetOrCreateState(int32 PlayerIndex);
    void CheckRateLimit(int32 PlayerIndex);
};
