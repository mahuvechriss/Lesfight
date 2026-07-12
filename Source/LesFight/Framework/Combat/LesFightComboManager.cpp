#include "LesFightComboManager.h"
#include "LesFightCombatComponent.h"
#include "LesFightCombatDataAsset.h"
#include "LesFight.h"

ULesFightComboManager::ULesFightComboManager()
    : bComboActive(false)
    , ComboCount(0)
    , CurrentComboStep(-1)
    , CurrentScaling(1.0f)
    , ComboTimer(0.0f)
    , ComboWindow(0.3f)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.05f;
}

void ULesFightComboManager::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightComboManager::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bComboActive)
    {
        ComboTimer += DeltaTime;
        if (ComboTimer >= ComboWindow)
        {
            EndCombo();
        }
    }
}

void ULesFightComboManager::Initialize(ULesFightCombatComponent* InCombat,
    ULesFightCombatDataAsset* CombatData)
{
    CombatComponent = InCombat;

    if (CombatData)
    {
        ComboDefinitions = CombatData->Combos;
    }
}

bool ULesFightComboManager::RegisterHit(FName AttackID)
{
    ComboHistory.Add(AttackID);
    ComboCount++;
    ComboTimer = 0.0f;

    if (!bComboActive)
    {
        const FComboDefinition* MatchingCombo = FindMatchingCombo(AttackID);
        if (MatchingCombo)
        {
            StartCombo(*MatchingCombo);
            return true;
        }
    }
    else
    {
        if (CurrentComboStep + 1 < ComboDefinitions.Num())
        {
            const FComboDefinition& ActiveCombo = ComboDefinitions[CurrentComboStep];
            if (ActiveCombo.ComboSequence.IsValidIndex(CurrentComboStep + 1))
            {
                const FComboEntry& NextEntry = ActiveCombo.ComboSequence[CurrentComboStep + 1];
                if (NextEntry.AttackID == AttackID)
                {
                    ProgressCombo(CurrentComboStep + 1);
                    return true;
                }
            }
        }
    }

    return false;
}

void ULesFightComboManager::BreakCombo()
{
    EndCombo();
}

void ULesFightComboManager::ResetCombo()
{
    ComboCount = 0;
    ComboHistory.Empty();
    CurrentScaling = 1.0f;
    bComboActive = false;
    ActiveComboID = NAME_None;
    CurrentComboStep = -1;
}

bool ULesFightComboManager::CanCancelInto(FName NextAttackID) const
{
    return false;
}

const FComboDefinition* ULesFightComboManager::FindMatchingCombo(FName LastAttackID) const
{
    for (const FComboDefinition& Combo : ComboDefinitions)
    {
        if (Combo.ComboSequence.Num() > 0 && Combo.ComboSequence[0].AttackID == LastAttackID)
        {
            return &Combo;
        }
    }
    return nullptr;
}

void ULesFightComboManager::StartCombo(const FComboDefinition& Combo)
{
    bComboActive = true;
    ActiveComboID = Combo.ComboID;
    CurrentComboStep = 0;
    ComboTimer = 0.0f;
    CurrentScaling = Combo.ScalingStartingPoint;

    OnComboStarted.Broadcast(Combo.ComboID);
    UE_LOG(LogLesFight, Verbose, TEXT("Combo started: %s"), *Combo.ComboName);
}

void ULesFightComboManager::ProgressCombo(int32 StepIndex)
{
    CurrentComboStep = StepIndex;
    ComboTimer = 0.0f;
    CurrentScaling = CalculateScaling(ComboCount);

    OnComboProgressed.Broadcast(StepIndex);
}

void ULesFightComboManager::EndCombo()
{
    if (bComboActive)
    {
        bComboActive = false;
        ActiveComboID = NAME_None;
        CurrentComboStep = -1;
        ComboCount = 0;
        OnComboEnded.Broadcast();
    }
}

float ULesFightComboManager::CalculateScaling(int32 HitCount) const
{
    return FMath::Max(1.0f - (HitCount * 0.1f), 0.1f);
}
