#include "LesFightCharacterLifecycleManager.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightCharacterLifecycleManager::ULesFightCharacterLifecycleManager()
    : ReadyFighterCount(0)
{
}

void ULesFightCharacterLifecycleManager::Initialize()
{
    UE_LOG(LogLesFight, Log, TEXT("CharacterLifecycleManager initialized"));
}

void ULesFightCharacterLifecycleManager::RegisterFighter(ALesFightBaseFighter* Fighter)
{
    if (!Fighter || RegisteredFighters.Contains(Fighter)) return;

    RegisteredFighters.Add(Fighter);
    FighterStates.Add(Fighter, EFighterLifecycleState::Loading);
    OnFighterLifecycleChanged.Broadcast(Fighter, EFighterLifecycleState::Loading);

    UE_LOG(LogLesFight, Log, TEXT("Fighter registered: %s"), *Fighter->GetName());
}

void ULesFightCharacterLifecycleManager::UnregisterFighter(ALesFightBaseFighter* Fighter)
{
    if (!Fighter || !RegisteredFighters.Contains(Fighter)) return;

    RegisteredFighters.Remove(Fighter);
    FighterStates.Remove(Fighter);
}

void ULesFightCharacterLifecycleManager::SetFighterState(ALesFightBaseFighter* Fighter, EFighterLifecycleState NewState)
{
    if (!Fighter || !FighterStates.Contains(Fighter)) return;

    EFighterLifecycleState PreviousState = FighterStates[Fighter];
    FighterStates[Fighter] = NewState;

    OnFighterLifecycleChanged.Broadcast(Fighter, NewState);

    UE_LOG(LogLesFight, Verbose, TEXT("Fighter %s lifecycle: %d -> %d"),
        *Fighter->GetName(), static_cast<int32>(PreviousState), static_cast<int32>(NewState));
}

void ULesFightCharacterLifecycleManager::MarkFighterReady(ALesFightBaseFighter* Fighter)
{
    SetFighterState(Fighter, EFighterLifecycleState::Ready);
    ReadyFighterCount++;

    if (AreAllFightersReady())
    {
        OnAllFightersReady.Broadcast(RegisteredFighters);
    }
}

void ULesFightCharacterLifecycleManager::MarkFighterDefeated(ALesFightBaseFighter* Fighter)
{
    SetFighterState(Fighter, EFighterLifecycleState::Defeated);
}

void ULesFightCharacterLifecycleManager::RemoveFighter(ALesFightBaseFighter* Fighter)
{
    if (!Fighter) return;

    SetFighterState(Fighter, EFighterLifecycleState::Removed);
    UnregisterFighter(Fighter);
}

void ULesFightCharacterLifecycleManager::ResetAllFighters()
{
    for (auto& Pair : FighterStates)
    {
        Pair.Value = EFighterLifecycleState::Loading;
    }
    ReadyFighterCount = 0;
}

TArray<ALesFightBaseFighter*> ULesFightCharacterLifecycleManager::GetActiveFighters() const
{
    TArray<ALesFightBaseFighter*> Active;
    for (auto& Pair : FighterStates)
    {
        if (Pair.Value == EFighterLifecycleState::Active || Pair.Value == EFighterLifecycleState::Ready)
        {
            Active.Add(Pair.Key);
        }
    }
    return Active;
}

int32 ULesFightCharacterLifecycleManager::GetActiveFighterCount() const
{
    return GetActiveFighters().Num();
}

EFighterLifecycleState ULesFightCharacterLifecycleManager::GetFighterState(ALesFightBaseFighter* Fighter) const
{
    if (FighterStates.Contains(Fighter))
        return FighterStates[Fighter];
    return EFighterLifecycleState::Uninitialized;
}

bool ULesFightCharacterLifecycleManager::AreAllFightersReady() const
{
    return ReadyFighterCount >= 2;
}

bool ULesFightCharacterLifecycleManager::IsFighterRegistered(ALesFightBaseFighter* Fighter) const
{
    return RegisteredFighters.Contains(Fighter);
}
