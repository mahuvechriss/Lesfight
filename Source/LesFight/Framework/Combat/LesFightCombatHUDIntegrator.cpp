#include "LesFightCombatHUDIntegrator.h"
#include "LesFightCombatComponent.h"
#include "LesFightUIManager.h"
#include "LesFightHUD.h"
#include "LesFight.h"

ULesFightCombatHUDIntegrator::ULesFightCombatHUDIntegrator()
{
}

void ULesFightCombatHUDIntegrator::Initialize(ULesFightCombatComponent* CombatComp,
    ULesFightUIManager* UIMgr)
{
    CombatComponent = CombatComp;
    UIManager = UIMgr;

    if (CombatComp)
    {
        CombatComp->OnAttackHit.AddDynamic(this, &ULesFightCombatHUDIntegrator::OnAttackHitEvent);
        CombatComp->OnComboUpdated.AddDynamic(this, &ULesFightCombatHUDIntegrator::OnComboUpdatedEvent);
        CombatComp->OnComboBroken.AddDynamic(this, &ULesFightCombatHUDIntegrator::OnComboBrokenEvent);
        CombatComp->OnFighterHit.AddDynamic(this, &ULesFightCombatHUDIntegrator::OnFighterHitEvent);
        CombatComp->OnRoundStartEvent.AddDynamic(this, &ULesFightCombatHUDIntegrator::OnRoundStartEvent);
        CombatComp->OnRoundEndEvent.AddDynamic(this, &ULesFightCombatHUDIntegrator::OnRoundEndEvent);
        CombatComp->OnAttackStarted.AddDynamic(this, &ULesFightCombatHUDIntegrator::OnAttackStartedEvent);
    }
}

void ULesFightCombatHUDIntegrator::SetHUD(ULesFightHUD* HUDWidget)
{
    HUD = HUDWidget;
}

void ULesFightCombatHUDIntegrator::ShowCombatHUD()
{
    if (UIManager.IsValid())
    {
        UIManager->ShowScreen(EGameScreen::HUD);
    }
}

void ULesFightCombatHUDIntegrator::HideCombatHUD()
{
    if (UIManager.IsValid())
    {
        UIManager->HideScreen(EGameScreen::HUD);
    }
}

void ULesFightCombatHUDIntegrator::OnAttackHitEvent(FName AttackID, AActor* Target)
{
}

void ULesFightCombatHUDIntegrator::OnComboUpdatedEvent(int32 NewComboCount)
{
    if (HUD.IsValid())
    {
        HUD->OnComboUpdated(NewComboCount);
    }
}

void ULesFightCombatHUDIntegrator::OnComboBrokenEvent()
{
    if (HUD.IsValid())
    {
        HUD->OnComboUpdated(0);
    }
}

void ULesFightCombatHUDIntegrator::OnFighterHitEvent(AActor* Attacker,
    const FDamageResult& DamageResult)
{
    if (HUD.IsValid())
    {
        FVector HitDirection = FVector::ZeroVector;
        if (Attacker)
        {
            HitDirection = (Attacker->GetActorLocation() - HUD->GetOwningPlayerPawn()->GetActorLocation()).GetSafeNormal();
        }
        HUD->OnDamageIndicator(DamageResult.FinalDamage, HitDirection);
    }
}

void ULesFightCombatHUDIntegrator::OnRoundStartEvent(int32 RoundNumber)
{
    if (UIManager.IsValid())
    {
        UIManager->ShowScreen(EGameScreen::HUD);
    }
    if (HUD.IsValid())
    {
        HUD->OnRoundAnnouncement(RoundNumber);
    }
}

void ULesFightCombatHUDIntegrator::OnRoundEndEvent(bool bWon)
{
    if (HUD.IsValid())
    {
        APlayerController* PC = HUD->GetOwningPlayer();
        FString PlayerName = PC ? PC->GetName() : TEXT("Player");
        HUD->OnMatchResult(PlayerName, bWon);
    }
}

void ULesFightCombatHUDIntegrator::OnFighterKOd(AActor* Fighter)
{
    if (HUD.IsValid() && Fighter)
    {
        HUD->OnKOAnnouncement(Fighter->GetName());
    }
}

void ULesFightCombatHUDIntegrator::OnAttackStartedEvent(FName AttackID, EAttackType AttackType)
{
}
