#include "LesFightNetworkSecurity.h"

ULesFightNetworkSecurity::ULesFightNetworkSecurity()
    : MaxPositionDeltaPerTick(500.0f)
    , MaxHealthChangePerAction(50.0f)
    , MaxStaminaChangePerAction(30.0f)
    , MaxMeterChangePerAction(20.0f)
    , SuspiciousThreshold(10.0f)
    , MaxActionsPerSecond(30)
    , bValidationEnabled(true)
{
}

void ULesFightNetworkSecurity::Initialize()
{
    PlayerSecurityStates.Empty();
    UE_LOG(LogLesFightNetwork, Log, TEXT("NetworkSecurity initialized"));
}

FSecurityValidationResult ULesFightNetworkSecurity::ValidateCombatAction(
    int32 PlayerIndex, const FNetworkCombatAction& Action)
{
    FSecurityValidationResult Result;
    if (!bValidationEnabled) return Result;

    FPlayerSecurityState& State = GetOrCreateState(PlayerIndex);
    CheckRateLimit(PlayerIndex);

    if (State.ActionsThisSecond > MaxActionsPerSecond)
    {
        return FSecurityValidationResult{false, TEXT("Action rate limit exceeded"), 8.0f};
    }

    State.ActionsThisSecond++;

    if (Action.ActionID == FName(TEXT("HEALTH_CHANGE")))
    {
        if (FMath::Abs(Action.ActionIndex) > MaxHealthChangePerAction)
        {
            ReportSuspiciousActivity(PlayerIndex,
                TEXT("Invalid health change"), 6.0f);
            return FSecurityValidationResult{false,
                TEXT("Health change exceeds maximum"), 6.0f};
        }
    }

    return Result;
}

FSecurityValidationResult ULesFightNetworkSecurity::ValidatePlayerState(
    int32 PlayerIndex, float Health, float Stamina, float Meter)
{
    FSecurityValidationResult Result;
    if (!bValidationEnabled) return Result;

    FPlayerSecurityState& State = GetOrCreateState(PlayerIndex);

    if (State.LastHealth >= 0.0f)
    {
        float HealthDiff = FMath::Abs(Health - State.LastHealth);
        if (HealthDiff > MaxHealthChangePerAction)
        {
            ReportSuspiciousActivity(PlayerIndex,
                TEXT("Health changed too rapidly"), 5.0f);
            return FSecurityValidationResult{false,
                TEXT("Suspicious health change"), 5.0f};
        }
    }

    if (State.LastStamina >= 0.0f)
    {
        float StaminaDiff = FMath::Abs(Stamina - State.LastStamina);
        if (StaminaDiff > MaxStaminaChangePerAction)
        {
            ReportSuspiciousActivity(PlayerIndex,
                TEXT("Stamina changed too rapidly"), 4.0f);
            return FSecurityValidationResult{false,
                TEXT("Suspicious stamina change"), 4.0f};
        }
    }

    if (State.LastMeter >= 0.0f)
    {
        float MeterDiff = FMath::Abs(Meter - State.LastMeter);
        if (MeterDiff > MaxMeterChangePerAction)
        {
            ReportSuspiciousActivity(PlayerIndex,
                TEXT("Meter changed too rapidly"), 4.0f);
            return FSecurityValidationResult{false,
                TEXT("Suspicious meter change"), 4.0f};
        }
    }

    State.LastHealth = Health;
    State.LastStamina = Stamina;
    State.LastMeter = Meter;

    return Result;
}

FSecurityValidationResult ULesFightNetworkSecurity::ValidatePosition(
    int32 PlayerIndex, FVector Position, FVector LastPosition)
{
    FSecurityValidationResult Result;
    if (!bValidationEnabled) return Result;

    float Delta = FVector::Dist(Position, LastPosition);
    if (Delta > MaxPositionDeltaPerTick)
    {
        ReportSuspiciousActivity(PlayerIndex,
            TEXT("Position changed too rapidly"), 7.0f);
        return FSecurityValidationResult{false,
            TEXT("Invalid position delta"), 7.0f};
    }

    return Result;
}

FSecurityValidationResult ULesFightNetworkSecurity::ValidateAnimationState(
    int32 PlayerIndex, const FNetworkAnimSyncData& AnimData)
{
    FSecurityValidationResult Result;
    return Result;
}

void ULesFightNetworkSecurity::ReportSuspiciousActivity(
    int32 PlayerIndex, const FString& Reason, float Severity)
{
    FPlayerSecurityState& State = GetOrCreateState(PlayerIndex);
    State.SuspicionScore += Severity;
    State.Violations.Add(Reason);

    UE_LOG(LogLesFightNetwork, Warning, TEXT("Suspicious activity - Player %d: %s (Severity: %.1f)"),
        PlayerIndex, *Reason, Severity);
}

bool ULesFightNetworkSecurity::IsPlayerSuspicious(int32 PlayerIndex) const
{
    const FPlayerSecurityState* State = PlayerSecurityStates.Find(PlayerIndex);
    return State && State->SuspicionScore >= SuspiciousThreshold;
}

TArray<int32> ULesFightNetworkSecurity::GetSuspiciousPlayers() const
{
    TArray<int32> Result;
    for (const auto& Pair : PlayerSecurityStates)
    {
        if (Pair.Value.SuspicionScore >= SuspiciousThreshold)
        {
            Result.Add(Pair.Key);
        }
    }
    return Result;
}

void ULesFightNetworkSecurity::EnableValidation(bool bEnable)
{
    bValidationEnabled = bEnable;
}

void ULesFightNetworkSecurity::SetMaxPositionDelta(float MaxDelta)
{
    MaxPositionDeltaPerTick = MaxDelta;
}

void ULesFightNetworkSecurity::SetMaxHealthChange(float MaxChange)
{
    MaxHealthChangePerAction = MaxChange;
}

void ULesFightNetworkSecurity::ResetPlayerTracking(int32 PlayerIndex)
{
    PlayerSecurityStates.Remove(PlayerIndex);
}

ULesFightNetworkSecurity::FPlayerSecurityState&
ULesFightNetworkSecurity::GetOrCreateState(int32 PlayerIndex)
{
    return PlayerSecurityStates.FindOrAdd(PlayerIndex);
}

void ULesFightNetworkSecurity::CheckRateLimit(int32 PlayerIndex)
{
    FPlayerSecurityState& State = GetOrCreateState(PlayerIndex);
    State.ActionTimer += 0.016f;
    if (State.ActionTimer >= 1.0f)
    {
        State.ActionsThisSecond = 0;
        State.ActionTimer = 0.0f;
    }
}
