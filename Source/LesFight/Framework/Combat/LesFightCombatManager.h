#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightCombatManager.generated.h"

class ALesFightBaseFighter;
class ULesFightCombatComponent;
class ULesFightCombatDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchPoint, ALesFightBaseFighter*, Fighter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFighterHit, ALesFightBaseFighter*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFighterKOd, ALesFightBaseFighter*, Fighter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCombatInitialized);

UCLASS(Blueprintable)
class ULesFightCombatManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCombatManager();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void RegisterFighter(ALesFightBaseFighter* Fighter, ULesFightCombatDataAsset* CombatData);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UnregisterFighter(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void StartRound();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void EndRound();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void OnFighterDefeated(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void PauseCombat();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ResumeCombat();

    UFUNCTION(BlueprintPure, Category = "Combat")
    TArray<ALesFightBaseFighter*> GetActiveFighters() const { return ActiveFighters; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    TArray<ALesFightBaseFighter*> GetDefeatedFighters() const { return DefeatedFighters; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsCombatActive() const { return bCombatActive; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    bool IsCombatPaused() const { return bCombatPaused; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    float GetRoundTime() const { return RoundTimer; }

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void SetRoundTimeLimit(float Seconds) { RoundTimeLimit = Seconds; }

    UFUNCTION(BlueprintPure, Category = "Combat")
    ULesFightCombatComponent* GetFighterCombatComponent(ALesFightBaseFighter* Fighter) const;

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRoundStart OnRoundStart;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnRoundEnd OnRoundEnd;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnMatchPoint OnMatchPoint;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFighterHit OnFighterHit;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFighterKOd OnFighterKOd;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCombatInitialized OnCombatInitialized;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    TArray<TObjectPtr<ALesFightBaseFighter>> ActiveFighters;

    UPROPERTY(BlueprintReadOnly, Category = "Combat")
    TArray<TObjectPtr<ALesFightBaseFighter>> DefeatedFighters;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
    float RoundTimeLimit;

private:
    UPROPERTY()
    TMap<TObjectPtr<ALesFightBaseFighter>, TObjectPtr<ULesFightCombatComponent>> FighterCombatMap;

    bool bCombatActive;
    bool bCombatPaused;
    float RoundTimer;

    void BindFighterEvents(ALesFightBaseFighter* Fighter, ULesFightCombatComponent* CombatComp);
    void CheckRoundEnd();
};
