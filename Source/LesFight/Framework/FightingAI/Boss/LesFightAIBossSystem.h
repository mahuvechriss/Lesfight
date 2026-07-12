#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIBossSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossPhaseChanged, EAIBossPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossSpecialAttack, FName, AttackName);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIBossSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    void InitializeBoss(EAIBossPhase StartPhase);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    void SetBossPhase(EAIBossPhase Phase);

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    EAIBossPhase GetBossPhase() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    void AdvancePhase();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    TArray<FName> GetBossSpecialAbilities() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    bool CanUseSpecialAbility(FName AbilityName) const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    bool IsBossMode() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    TMap<EAIBossPhase, float> GetPhaseHealthThresholds() const;

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    void TriggerPhaseTransition();

    UFUNCTION(BlueprintCallable, Category = "FightingAI|Boss")
    FString GetBossDescription() const;

    UPROPERTY(BlueprintAssignable, Category = "FightingAI|Boss")
    FOnBossPhaseChanged OnBossPhaseChanged;

    UPROPERTY(BlueprintAssignable, Category = "FightingAI|Boss")
    FOnBossSpecialAttack OnBossSpecialAttack;

    void Initialize(ULesFightAIFighterController* InController);

protected:
    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Boss")
    EAIBossPhase CurrentPhase;

    UPROPERTY(EditDefaultsOnly, Category = "FightingAI|Boss")
    TMap<EAIBossPhase, float> PhaseHealthThresholds;

    UPROPERTY(EditDefaultsOnly, Category = "FightingAI|Boss")
    TMap<EAIBossPhase, TArray<FName>> PhaseAbilities;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Boss")
    bool bBossMode;

    UPROPERTY(VisibleAnywhere, Category = "FightingAI|Boss")
    TArray<FString> PhaseDescriptions;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;

    void BuildPhaseThresholds();
    void BuildPhaseAbilities();
    void BuildPhaseDescriptions();
};
