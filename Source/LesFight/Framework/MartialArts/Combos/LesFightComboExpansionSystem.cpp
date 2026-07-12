#include "LesFightComboExpansionSystem.h"
#include "LesFightMartialArtsManager.h"

ULesFightComboExpansionSystem::ULesFightComboExpansionSystem()
    : bInCombo(false)
    , CurrentChainLength(0)
    , MaxChainLength(5)
    , ChainTimer(0.0f)
    , CurrentExpansion(EComboExpansionType::None)
    , bTargetLaunched(false)
    , bNearWall(false)
    , bTargetOnGround(true)
    , TotalHitsInCombo(0)
    , BranchIndex(0)
{
}

void ULesFightComboExpansionSystem::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;

    AvailableExpansions = {
        EComboExpansionType::Branching,
        EComboExpansionType::Launcher,
        EComboExpansionType::CancelCombo
    };
}

void ULesFightComboExpansionSystem::Tick(float DeltaTime)
{
    if (bInCombo)
    {
        ChainTimer -= DeltaTime;
        if (ChainTimer <= 0.0f)
        {
            OnComboTimeout();
        }
    }
}

bool ULesFightComboExpansionSystem::StartComboExpansion(EComboExpansionType ExpansionType)
{
    if (!AvailableExpansions.Contains(ExpansionType)) return false;
    if (!CanChain(ExpansionType)) return false;

    const FComboExpansionData* Data = ExpansionDefinitions.Find(ExpansionType);
    if (!Data) return false;

    bInCombo = true;
    CurrentChainLength = 1;
    CurrentExpansion = ExpansionType;
    ChainTimer = Data->ChainWindow;
    MaxChainLength = Data->MaxChainLength;
    BranchHistory.Empty();

    OnComboExpansion.Broadcast(ExpansionType);
    return true;
}

bool ULesFightComboExpansionSystem::ChainNextAttack(int32 InBranchIndex)
{
    if (!bInCombo) return false;
    if (CurrentChainLength >= MaxChainLength) return false;
    if (ChainTimer <= 0.0f) return false;

    CurrentChainLength++;
    BranchIndex = InBranchIndex;
    BranchHistory.Add(InBranchIndex);

    const FComboExpansionData* Data = ExpansionDefinitions.Find(CurrentExpansion);
    ChainTimer = Data ? Data->ChainWindow : 0.3f;

    OnComboBranch.Broadcast(InBranchIndex);
    return true;
}

void ULesFightComboExpansionSystem::CancelCombo()
{
    bInCombo = false;
    CurrentChainLength = 0;
    CurrentExpansion = EComboExpansionType::None;
    ChainTimer = 0.0f;
}

void ULesFightComboExpansionSystem::RegisterHit()
{
    TotalHitsInCombo++;
}

void ULesFightComboExpansionSystem::SetLaunched(bool bLaunched)
{
    bTargetLaunched = bLaunched;
}

void ULesFightComboExpansionSystem::SetNearWall(bool bNear)
{
    bNearWall = bNear;
}

void ULesFightComboExpansionSystem::SetOnGround(bool bOnGround)
{
    bTargetOnGround = bOnGround;
}

void ULesFightComboExpansionSystem::SetExpansionData(
    const TMap<EComboExpansionType, FComboExpansionData>& Data)
{
    ExpansionDefinitions = Data;
}

void ULesFightComboExpansionSystem::SetAvailableExpansions(
    const TArray<EComboExpansionType>& Expansions)
{
    AvailableExpansions = Expansions;
}

bool ULesFightComboExpansionSystem::CanEndWithUltimate() const
{
    const FComboExpansionData* Data = ExpansionDefinitions.Find(CurrentExpansion);
    return Data && Data->bCanEndWithUltimate && CurrentChainLength >= 3;
}

void ULesFightComboExpansionSystem::Reset()
{
    CancelCombo();
    bTargetLaunched = false;
    bNearWall = false;
    bTargetOnGround = true;
    TotalHitsInCombo = 0;
}

bool ULesFightComboExpansionSystem::CanChain(EComboExpansionType ExpansionType) const
{
    const FComboExpansionData* Data = ExpansionDefinitions.Find(ExpansionType);
    if (!Data) return false;
    if (Data->bRequiresLauncher && !bTargetLaunched) return false;
    if (Data->bRequiresWall && !bNearWall) return false;
    return true;
}

void ULesFightComboExpansionSystem::OnComboTimeout()
{
    CancelCombo();
}

float ULesFightComboExpansionSystem::GetChainWindow() const
{
    const FComboExpansionData* Data = ExpansionDefinitions.Find(CurrentExpansion);
    return Data ? Data->ChainWindow : 0.3f;
}
