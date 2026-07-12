#include "LesFightAIStateManager.h"
#include "Data/LesFightAIData.h"

ULesFightAIStateManager::ULesFightAIStateManager()
{
    BuildValidTransitions();
}

void ULesFightAIStateManager::BuildValidTransitions()
{
    ValidTransitions.Empty();

    ValidTransitions.Add(EAIBehaviorMode::Idle, { EAIBehaviorMode::Patrol });
    ValidTransitions.Add(EAIBehaviorMode::Patrol, { EAIBehaviorMode::Engage });
    ValidTransitions.Add(EAIBehaviorMode::Engage, { EAIBehaviorMode::Combat });
    ValidTransitions.Add(EAIBehaviorMode::Combat, { EAIBehaviorMode::Retreat, EAIBehaviorMode::Recovery });
    ValidTransitions.Add(EAIBehaviorMode::Retreat, { EAIBehaviorMode::Engage });
    ValidTransitions.Add(EAIBehaviorMode::Recovery, { EAIBehaviorMode::Engage });
}

void ULesFightAIStateManager::SetState(EAIBehaviorMode NewMode)
{
    if (!CanTransitionTo(NewMode))
    {
        return;
    }

    if (UWorld* World = GetWorld())
    {
        StateTimers.Emplace(CurrentState, World->GetTimeSeconds() - StateStartTime);
    }

    CurrentState = NewMode;
    StateStartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
}

EAIBehaviorMode ULesFightAIStateManager::GetState() const
{
    return CurrentState;
}

void ULesFightAIStateManager::SetFlag(EAIStateFlags Flag, bool bValue)
{
    if (bValue)
    {
        StateFlags |= static_cast<int32>(Flag);
    }
    else
    {
        StateFlags &= ~static_cast<int32>(Flag);
    }
}

bool ULesFightAIStateManager::HasFlag(EAIStateFlags Flag) const
{
    return (StateFlags & static_cast<int32>(Flag)) != 0;
}

float ULesFightAIStateManager::GetStateTime() const
{
    if (!GetWorld())
    {
        return 0.0f;
    }
    return GetWorld()->GetTimeSeconds() - StateStartTime;
}

bool ULesFightAIStateManager::CanTransitionTo(EAIBehaviorMode Target) const
{
    const TArray<EAIBehaviorMode>* Transitions = ValidTransitions.Find(CurrentState);
    if (!Transitions)
    {
        return false;
    }
    return Transitions->Contains(Target);
}

void ULesFightAIStateManager::Reset()
{
    CurrentState = EAIBehaviorMode::Idle;
    StateStack.Empty();
    StateTimers.Empty();
    StateFlags = 0;
    StateStartTime = 0.0f;
}

void ULesFightAIStateManager::PushState(EAIBehaviorMode State)
{
    StateStack.Push(CurrentState);
    SetState(State);
}

void ULesFightAIStateManager::PopState()
{
    if (StateStack.Num() > 0)
    {
        EAIBehaviorMode PreviousState = StateStack.Pop();
        SetState(PreviousState);
    }
}

TArray<EAIBehaviorMode> ULesFightAIStateManager::GetStateStack() const
{
    return StateStack;
}
