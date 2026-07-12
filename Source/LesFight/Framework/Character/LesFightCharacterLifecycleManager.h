#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightCharacterLifecycleManager.generated.h"

class ALesFightBaseFighter;

UENUM(BlueprintType)
enum class EFighterLifecycleState : uint8
{
    Uninitialized,
    Loading,
    Ready,
    Active,
    Defeated,
    Respawning,
    Removed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFighterLifecycleChanged, ALesFightBaseFighter*, Fighter, EFighterLifecycleState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllFightersReady, const TArray<ALesFightBaseFighter*>&, Fighters);

UCLASS(Blueprintable)
class ULesFightCharacterLifecycleManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterLifecycleManager();

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void RegisterFighter(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void UnregisterFighter(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void SetFighterState(ALesFightBaseFighter* Fighter, EFighterLifecycleState NewState);

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void MarkFighterReady(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void MarkFighterDefeated(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void RemoveFighter(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Lifecycle")
    void ResetAllFighters();

    UFUNCTION(BlueprintPure, Category = "Lifecycle")
    TArray<ALesFightBaseFighter*> GetActiveFighters() const;

    UFUNCTION(BlueprintPure, Category = "Lifecycle")
    TArray<ALesFightBaseFighter*> GetAllFighters() const { return RegisteredFighters; }

    UFUNCTION(BlueprintPure, Category = "Lifecycle")
    int32 GetActiveFighterCount() const;

    UFUNCTION(BlueprintPure, Category = "Lifecycle")
    EFighterLifecycleState GetFighterState(ALesFightBaseFighter* Fighter) const;

    UFUNCTION(BlueprintPure, Category = "Lifecycle")
    bool AreAllFightersReady() const;

    UFUNCTION(BlueprintPure, Category = "Lifecycle")
    bool IsFighterRegistered(ALesFightBaseFighter* Fighter) const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Lifecycle")
    TArray<TObjectPtr<ALesFightBaseFighter>> RegisteredFighters;

    UPROPERTY(BlueprintReadOnly, Category = "Lifecycle")
    TMap<TObjectPtr<ALesFightBaseFighter>, EFighterLifecycleState> FighterStates;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFighterLifecycleChanged OnFighterLifecycleChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAllFightersReady OnAllFightersReady;

private:
    int32 ReadyFighterCount;
};
