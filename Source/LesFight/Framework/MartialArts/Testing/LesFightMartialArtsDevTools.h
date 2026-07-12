#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightMartialArtsDevTools.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDevToolExecuted, FName, ToolName, FString, Result);

UCLASS(Blueprintable)
class ULesFightMartialArtsDevTools : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMartialArtsDevTools();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void SwitchFightingStyle(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void DisplayActiveStance();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void TestComboPath(const TArray<FName>& ComboSequence);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void VisualizeCounterWindows();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void InspectMotionMatching();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void MonitorAnimationTiming();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void SetDebugMode(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    bool IsDebugMode() const { return bDebugMode; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void ToggleDebugOverlay();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void LogAllStyles();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void LogStanceData();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void SimulatePerfectCounter();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void SimulatePerfectDodge();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void SetInfiniteStamina(bool bInfinite);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void SetOneHitKO(bool bOneHit);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|DevTools")
    void ResetDevSettings();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDevToolExecuted OnDevToolExecuted;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bDebugMode;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bInfiniteStamina;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bOneHitKO;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bShowOverlay;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FString> DebugLog;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    int32 MaxLogEntries;

    void AddToLog(const FString& Message);
    void BroadcastResult(FName ToolName, const FString& Result);
};
