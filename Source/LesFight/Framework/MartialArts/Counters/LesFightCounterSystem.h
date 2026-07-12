#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightCounterSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCounterExecuted, ECounterType, CounterType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCounterFailed, ECounterType, CounterType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerfectCounter, ECounterType, CounterType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlowMotionCounter);

UCLASS(Blueprintable)
class ULesFightCounterSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCounterSystem();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    bool AttemptCounter(ECounterType CounterType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    void OpenCounterWindow(ECounterType CounterType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    void CloseCounterWindow();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    bool IsCounterWindowOpen() const { return bCounterWindowOpen; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    ECounterType GetOpenCounterType() const { return OpenCounterType; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Counters")
    bool CanCounter(ECounterType CounterType) const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Counters")
    float GetCounterWindowRemaining() const;

    UFUNCTION(BlueprintPure, Category = "MartialArts|Counters")
    float GetCounterDamageMultiplier(ECounterType CounterType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    void SetCounterData(const TMap<ECounterType, FCounterWindowData>& Data);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    void SetAvailableCounters(const TArray<ECounterType>& Counters);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    void TriggerSlowMotionCounter();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Counters")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCounterExecuted OnCounterExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCounterFailed OnCounterFailed;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPerfectCounter OnPerfectCounter;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSlowMotionCounter OnSlowMotionCounter;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bCounterWindowOpen;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECounterType OpenCounterType;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float WindowTimer;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float GlobalCounterMultiplier;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TMap<ECounterType, FCounterWindowData> CounterDefinitions;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TArray<ECounterType> AvailableCounters;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    ECounterType LastCounterAttempt;
    float LastCounterTime;
    int32 ConsecutiveCounters;
    bool bSlowMotionActive;

    void ProcessCounterResult(ECounterType CounterType, bool bSuccess);
    bool IsPerfectCounter(ECounterType CounterType) const;
    void ApplyCounterEffects(ECounterType CounterType);
};
