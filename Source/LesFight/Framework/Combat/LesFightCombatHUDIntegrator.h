#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightCombatHUDIntegrator.generated.h"

class ULesFightCombatComponent;
class ULesFightUIManager;
class ULesFightHUD;

UCLASS(Blueprintable)
class ULesFightCombatHUDIntegrator : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCombatHUDIntegrator();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void Initialize(ULesFightCombatComponent* CombatComp, ULesFightUIManager* UIMgr);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void SetHUD(ULesFightHUD* HUDWidget);

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowCombatHUD();

    UFUNCTION(BlueprintCallable, Category = "HUD")
    void HideCombatHUD();

protected:
    UFUNCTION()
    void OnAttackHitEvent(FName AttackID, AActor* Target);

    UFUNCTION()
    void OnComboUpdatedEvent(int32 NewComboCount);

    UFUNCTION()
    void OnComboBrokenEvent();

    UFUNCTION()
    void OnFighterHitEvent(AActor* Attacker, const FDamageResult& DamageResult);

    UFUNCTION()
    void OnRoundStartEvent(int32 RoundNumber);

    UFUNCTION()
    void OnRoundEndEvent(bool bWon);

    UFUNCTION()
    void OnFighterKOd(AActor* Fighter);

    UFUNCTION()
    void OnAttackStartedEvent(FName AttackID, EAttackType AttackType);

private:
    TWeakObjectPtr<ULesFightCombatComponent> CombatComponent;
    TWeakObjectPtr<ULesFightUIManager> UIManager;
    TWeakObjectPtr<ULesFightHUD> HUD;
};
