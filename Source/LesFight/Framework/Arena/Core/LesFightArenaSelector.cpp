#include "LesFightArenaSelector.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaDataSystem.h"

void ULesFightArenaSelector::Initialize(ULesFightArenaWorldManager* InOwnerManager, ULesFightArenaDataSystem* InDataSystem)
{
    OwnerManager = InOwnerManager;
    DataSystem = InDataSystem;
    SelectedArena = EArenaType::MAX;
    PreviewArena = EArenaType::MAX;
    bRandomSelection = false;
    FilterCategory = EArenaEnvironmentCategory::Ancient;
    bFilterActive = false;
}

void ULesFightArenaSelector::SelectArena(EArenaType Arena)
{
    SelectedArena = Arena;
    PreviewArena = Arena;
    OnArenaSelected.Broadcast(Arena);
}

EArenaType ULesFightArenaSelector::GetSelectedArena() const
{
    return SelectedArena;
}

FArenaInfo ULesFightArenaSelector::GetSelectedArenaInfo() const
{
    if (DataSystem.IsValid() && SelectedArena != EArenaType::MAX)
    {
        return DataSystem->GetArenaInfo(SelectedArena);
    }
    return FArenaInfo();
}

void ULesFightArenaSelector::SetRandomSelection(bool bRandom)
{
    bRandomSelection = bRandom;
}

void ULesFightArenaSelector::SelectRandomArena()
{
    TArray<FArenaInfo> Available = GetFilteredArenas();
    if (Available.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, Available.Num() - 1);
        SelectArena(Available[Index].ArenaType);
    }
}

void ULesFightArenaSelector::SetFilterCategory(EArenaEnvironmentCategory Category)
{
    FilterCategory = Category;
    bFilterActive = true;
}

void ULesFightArenaSelector::ClearFilter()
{
    bFilterActive = false;
}

TArray<FArenaInfo> ULesFightArenaSelector::GetFilteredArenas() const
{
    TArray<FArenaInfo> Result;
    if (!DataSystem.IsValid())
    {
        return Result;
    }

    if (bFilterActive)
    {
        return DataSystem->GetArenasByCategory(FilterCategory);
    }

    return DataSystem->GetAllArenaInfos();
}

void ULesFightArenaSelector::PreviewArena(EArenaType Arena)
{
    PreviewArena = Arena;
}

void ULesFightArenaSelector::ConfirmSelection()
{
    if (bRandomSelection)
    {
        SelectRandomArena();
    }
    OnArenaSelected.Broadcast(SelectedArena);
}
