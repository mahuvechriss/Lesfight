#include "LesFightAIBossSystem.h"
#include "Framework/FightingAI/LesFightAIFighterController.h"

void ULesFightAIBossSystem::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;
    bBossMode = true;

    BuildPhaseThresholds();
    BuildPhaseAbilities();
    BuildPhaseDescriptions();

    InitializeBoss(EAIBossPhase::Phase1);
}

void ULesFightAIBossSystem::BuildPhaseThresholds()
{
    PhaseHealthThresholds.Empty();

    PhaseHealthThresholds.Add(EAIBossPhase::Phase1, 1.00f);
    PhaseHealthThresholds.Add(EAIBossPhase::Phase2, 0.75f);
    PhaseHealthThresholds.Add(EAIBossPhase::Phase3, 0.50f);
    PhaseHealthThresholds.Add(EAIBossPhase::Enrage, 0.25f);
    PhaseHealthThresholds.Add(EAIBossPhase::Final, 0.10f);
}

void ULesFightAIBossSystem::BuildPhaseAbilities()
{
    PhaseAbilities.Empty();

    PhaseAbilities.Add(EAIBossPhase::Phase1, {
        FName(TEXT("BasicAttack")),
        FName(TEXT("LightCombo")),
        FName(TEXT("StepDash"))
    });

    PhaseAbilities.Add(EAIBossPhase::Phase2, {
        FName(TEXT("BasicAttack")),
        FName(TEXT("LightCombo")),
        FName(TEXT("UnblockableStrike")),
        FName(TEXT("StepDash"))
    });

    PhaseAbilities.Add(EAIBossPhase::Phase3, {
        FName(TEXT("BasicAttack")),
        FName(TEXT("LightCombo")),
        FName(TEXT("UnblockableStrike")),
        FName(TEXT("AreaSlam")),
        FName(TEXT("GroundPound"))
    });

    PhaseAbilities.Add(EAIBossPhase::Enrage, {
        FName(TEXT("BasicAttack")),
        FName(TEXT("EnragedCombo")),
        FName(TEXT("UnblockableStrike")),
        FName(TEXT("AreaSlam")),
        FName(TEXT("GroundPound")),
        FName(TEXT("RapidStrikes"))
    });

    PhaseAbilities.Add(EAIBossPhase::Final, {
        FName(TEXT("BasicAttack")),
        FName(TEXT("EnragedCombo")),
        FName(TEXT("UnblockableStrike")),
        FName(TEXT("AreaSlam")),
        FName(TEXT("GroundPound")),
        FName(TEXT("RapidStrikes")),
        FName(TEXT("UltimateAttack"))
    });
}

void ULesFightAIBossSystem::BuildPhaseDescriptions()
{
    PhaseDescriptions.Empty();
    PhaseDescriptions.SetNum(5);

    PhaseDescriptions[0] = TEXT("Phase 1 - Learning: Basic attacks and light combos");
    PhaseDescriptions[1] = TEXT("Phase 2 - Escalation: Unblockable strikes introduced");
    PhaseDescriptions[2] = TEXT("Phase 3 - Devastation: Area attacks unlock");
    PhaseDescriptions[3] = TEXT("Enrage - Fury: Enraged combos and rapid strikes");
    PhaseDescriptions[4] = TEXT("Final - Desperation: Ultimate attack available");
}

void ULesFightAIBossSystem::InitializeBoss(EAIBossPhase StartPhase)
{
    CurrentPhase = StartPhase;
    bBossMode = true;

    if (OwnerController.IsValid())
    {
        OwnerController->OnBossInitialized(CurrentPhase);
    }

    OnBossPhaseChanged.Broadcast(CurrentPhase);
}

void ULesFightAIBossSystem::SetBossPhase(EAIBossPhase Phase)
{
    if (CurrentPhase != Phase)
    {
        CurrentPhase = Phase;

        if (OwnerController.IsValid())
        {
            OwnerController->OnBossPhaseChanged(CurrentPhase);
        }

        OnBossPhaseChanged.Broadcast(CurrentPhase);
    }
}

EAIBossPhase ULesFightAIBossSystem::GetBossPhase() const
{
    return CurrentPhase;
}

void ULesFightAIBossSystem::AdvancePhase()
{
    TArray<EAIBossPhase> PhaseOrder;
    PhaseHealthThresholds.GetKeys(PhaseOrder);

    int32 CurrentIndex = PhaseOrder.IndexOfByKey(CurrentPhase);
    if (CurrentIndex >= 0 && CurrentIndex < PhaseOrder.Num() - 1)
    {
        SetBossPhase(PhaseOrder[CurrentIndex + 1]);
    }
}

TArray<FName> ULesFightAIBossSystem::GetBossSpecialAbilities() const
{
    if (const TArray<FName>* Abilities = PhaseAbilities.Find(CurrentPhase))
    {
        return *Abilities;
    }

    return TArray<FName>();
}

bool ULesFightAIBossSystem::CanUseSpecialAbility(FName AbilityName) const
{
    if (const TArray<FName>* Abilities = PhaseAbilities.Find(CurrentPhase))
    {
        return Abilities->Contains(AbilityName);
    }

    return false;
}

bool ULesFightAIBossSystem::IsBossMode() const
{
    return bBossMode;
}

TMap<EAIBossPhase, float> ULesFightAIBossSystem::GetPhaseHealthThresholds() const
{
    return PhaseHealthThresholds;
}

void ULesFightAIBossSystem::TriggerPhaseTransition()
{
    if (!OwnerController.IsValid())
    {
        return;
    }

    float HealthPercent = OwnerController->GetHealthPercent();

    TArray<EAIBossPhase> Phases;
    PhaseHealthThresholds.GetKeys(Phases);

    EAIBossPhase TargetPhase = EAIBossPhase::Phase1;
    float ClosestThreshold = 0.0f;

    for (EAIBossPhase Phase : Phases)
    {
        float Threshold = PhaseHealthThresholds[Phase];
        if (HealthPercent <= Threshold && Threshold > ClosestThreshold)
        {
            ClosestThreshold = Threshold;
            TargetPhase = Phase;
        }
    }

    if (TargetPhase != CurrentPhase)
    {
        SetBossPhase(TargetPhase);
    }
}

FString ULesFightAIBossSystem::GetBossDescription() const
{
    int32 PhaseIndex = static_cast<int32>(CurrentPhase);
    if (PhaseIndex >= 0 && PhaseIndex < PhaseDescriptions.Num())
    {
        return PhaseDescriptions[PhaseIndex];
    }

    return TEXT("Unknown boss phase");
}
