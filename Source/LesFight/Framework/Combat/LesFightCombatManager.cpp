#include "LesFightCombatManager.h"
#include "LesFightCombatComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightCombatManager::ULesFightCombatManager()
    : bCombatActive(false)
    , bCombatPaused(false)
    , RoundTimer(0.0f)
    , RoundTimeLimit(99.0f)
{
}

void ULesFightCombatManager::Initialize()
{
    bCombatActive = false;
    bCombatPaused = false;
    RoundTimer = 0.0f;
    ActiveFighters.Empty();
    DefeatedFighters.Empty();
    FighterCombatMap.Empty();
    UE_LOG(LogLesFight, Log, TEXT("CombatManager initialized"));
    OnCombatInitialized.Broadcast();
}

void ULesFightCombatManager::RegisterFighter(ALesFightBaseFighter* Fighter,
    ULesFightCombatDataAsset* CombatData)
{
    if (!Fighter) return;

    ULesFightCombatComponent* CombatComp = Fighter->FindComponentByClass<ULesFightCombatComponent>();
    if (!CombatComp)
    {
        CombatComp = NewObject<ULesFightCombatComponent>(Fighter);
        CombatComp->RegisterComponent();
    }

    CombatComp->Initialize(CombatData);
    ActiveFighters.Add(Fighter);
    FighterCombatMap.Add(Fighter, CombatComp);
    BindFighterEvents(Fighter, CombatComp);

    UE_LOG(LogLesFight, Log, TEXT("Fighter registered: %s"), *Fighter->GetName());
}

void ULesFightCombatManager::UnregisterFighter(ALesFightBaseFighter* Fighter)
{
    if (!Fighter) return;

    ActiveFighters.Remove(Fighter);
    DefeatedFighters.Remove(Fighter);
    FighterCombatMap.Remove(Fighter);
}

void ULesFightCombatManager::StartRound()
{
    bCombatActive = true;
    bCombatPaused = false;
    RoundTimer = 0.0f;

    for (ALesFightBaseFighter* Fighter : ActiveFighters)
    {
        if (ULesFightCombatComponent* CombatComp = FighterCombatMap.FindRef(Fighter))
        {
            CombatComp->OnRoundStart();
        }
    }

    UE_LOG(LogLesFight, Log, TEXT("Round started"));
    OnRoundStart.Broadcast();
}

void ULesFightCombatManager::EndRound()
{
    bCombatActive = false;
    bCombatPaused = false;

    for (ALesFightBaseFighter* Fighter : ActiveFighters)
    {
        if (ULesFightCombatComponent* CombatComp = FighterCombatMap.FindRef(Fighter))
        {
            CombatComp->OnRoundEnd();
        }
    }

    UE_LOG(LogLesFight, Log, TEXT("Round ended"));
    OnRoundEnd.Broadcast();
}

void ULesFightCombatManager::OnFighterDefeated(ALesFightBaseFighter* Fighter)
{
    if (!Fighter) return;

    ActiveFighters.Remove(Fighter);
    DefeatedFighters.Add(Fighter);
    OnFighterKOd.Broadcast(Fighter);

    CheckRoundEnd();
}

void ULesFightCombatManager::PauseCombat()
{
    bCombatPaused = true;
}

void ULesFightCombatManager::ResumeCombat()
{
    bCombatPaused = false;
}

ULesFightCombatComponent* ULesFightCombatManager::GetFighterCombatComponent(
    ALesFightBaseFighter* Fighter) const
{
    return FighterCombatMap.FindRef(Fighter);
}

void ULesFightCombatManager::BindFighterEvents(ALesFightBaseFighter* Fighter,
    ULesFightCombatComponent* CombatComp)
{
    if (!CombatComp) return;
    CombatComp->OnFighterHit.AddUniqueDynamic(this, &ULesFightCombatManager::OnFighterHitData);
}

void ULesFightCombatManager::CheckRoundEnd()
{
    int32 AliveCount = 0;
    ALesFightBaseFighter* LastAlive = nullptr;

    for (ALesFightBaseFighter* Fighter : ActiveFighters)
    {
        if (!DefeatedFighters.Contains(Fighter))
        {
            AliveCount++;
            LastAlive = Fighter;
        }
    }

    if (AliveCount <= 1 || DefeatedFighters.Num() >= ActiveFighters.Num())
    {
        if (LastAlive)
        {
            UE_LOG(LogLesFight, Log, TEXT("Match point for %s"), *LastAlive->GetName());
            OnMatchPoint.Broadcast(LastAlive);
        }
        EndRound();
    }
}
