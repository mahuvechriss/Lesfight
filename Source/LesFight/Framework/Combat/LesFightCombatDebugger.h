#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightCombatDebugger.generated.h"

class ALesFightBaseFighter;
class ULesFightCombatComponent;

USTRUCT(BlueprintType)
struct FCombatDebugFrameData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 FrameNumber;

    UPROPERTY(BlueprintReadOnly)
    FName AttackName;

    UPROPERTY(BlueprintReadOnly)
    FString FrameState;

    UPROPERTY(BlueprintReadOnly)
    float CurrentDamage;

    UPROPERTY(BlueprintReadOnly)
    float GuardMeter;

    UPROPERTY(BlueprintReadOnly)
    int32 ComboCount;

    UPROPERTY(BlueprintReadOnly)
    float Scaling;

    UPROPERTY(BlueprintReadOnly)
    FVector HitboxPosition;

    UPROPERTY(BlueprintReadOnly)
    FVector HitboxExtents;

    FCombatDebugFrameData()
        : FrameNumber(0)
        , AttackName(NAME_None)
        , CurrentDamage(0.0f)
        , GuardMeter(0.0f)
        , ComboCount(0)
        , Scaling(1.0f)
        , HitboxPosition(FVector::ZeroVector)
        , HitboxExtents(FVector::ZeroVector)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDebugFrameUpdated, const FCombatDebugFrameData&, FrameData);

UCLASS(Blueprintable)
class ULesFightCombatDebugger : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCombatDebugger();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void RegisterCombatComponent(ULesFightCombatComponent* CombatComp);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SetDebugMode(bool bEnabled) { bDebugMode = bEnabled; }

    UFUNCTION(BlueprintPure, Category = "Debug")
    bool IsDebugMode() const { return bDebugMode; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ShowHitboxes(bool bShow) { bShowHitboxes = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ShowHurtboxes(bool bShow) { bShowHurtboxes = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ShowFrameData(bool bShow) { bShowFrameData = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ShowComboDebug(bool bShow) { bShowComboDebug = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ShowDamageLog(bool bShow) { bShowDamageLog = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ShowInputHistory(bool bShow) { bShowInputHistory = bShow; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void LogDamageEvent(AActor* Target, float Damage, FName AttackID);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void LogFrameData(const FCombatDebugFrameData& FrameData);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void LogString(const FString& Message, FColor Color = FColor::White);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ClearLog();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ToggleDebugDisplay();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SetGodMode(bool bEnabled) { bGodMode = bEnabled; }

    UFUNCTION(BlueprintPure, Category = "Debug")
    bool IsGodMode() const { return bGodMode; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SetInfiniteMeter(bool bEnabled) { bInfiniteMeter = bEnabled; }

    UFUNCTION(BlueprintPure, Category = "Debug")
    bool HasInfiniteMeter() const { return bInfiniteMeter; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SetInfiniteHealth(bool bEnabled) { bInfiniteHealth = bEnabled; }

    UFUNCTION(BlueprintPure, Category = "Debug")
    bool HasInfiniteHealth() const { return bInfiniteHealth; }

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SpawnDebugFighter(TSubclassOf<ALesFightBaseFighter> FighterClass, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ExecuteAttackByName(FName AttackID);

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SetComboWindowMultiplier(float Multiplier) { ComboWindowMultiplier = Multiplier; }

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnDebugFrameUpdated OnDebugFrameUpdated;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
    float ComboWindowMultiplier;

private:
    TArray<TObjectPtr<ULesFightCombatComponent>> RegisteredComponents;
    bool bDebugMode;
    bool bShowHitboxes;
    bool bShowHurtboxes;
    bool bShowFrameData;
    bool bShowComboDebug;
    bool bShowDamageLog;
    bool bShowInputHistory;
    bool bGodMode;
    bool bInfiniteMeter;
    bool bInfiniteHealth;
    TArray<FString> DebugLog;

    void DrawDebugOverlay(UWorld* World);
};
