#include "LesFightAnimationStateMachine.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightAnimBlueprintBase.h"
#include "LesFightAnimationDataAsset.h"
#include "LesFight.h"

ULesFightAnimationStateMachine::ULesFightAnimationStateMachine()
    : CurrentState(NAME_None)
    , PreviousState(NAME_None)
    , PendingState(NAME_None)
    , StateTimer(0.0f)
    , TransitionBlendTime(0.2f)
    , bTransitionPending(false)
    , PendingBlendTime(0.2f)
{
}

void ULesFightAnimationStateMachine::Initialize(ULesFightCharacterAnimationComponent* InComponent,
    ULesFightAnimationDataAsset* AnimData)
{
    AnimComponent = InComponent;

    if (AnimData)
    {
        for (const FAnimTransitionRule& Rule : AnimData->TransitionRules)
        {
            FAnimStateInfo StateInfo;
            StateInfo.StateName = Rule.FromState;
            StateInfo.Transitions.Add(Rule);
            if (!RegisteredStates.Contains(Rule.FromState))
            {
                RegisteredStates.Add(Rule.FromState, StateInfo);
            }
            else
            {
                RegisteredStates[Rule.FromState].Transitions.Add(Rule);
            }
        }
    }

    if (!CurrentState.IsNone())
    {
        OnStateEnter(CurrentState);
    }
}

void ULesFightAnimationStateMachine::Update(float DeltaTime)
{
    StateTimer += DeltaTime;
}

bool ULesFightAnimationStateMachine::RequestTransition(FName TargetState)
{
    if (CurrentState == TargetState) return true;
    if (bTransitionPending && PendingState == TargetState) return true;

    const FAnimStateInfo* CurrentStateInfo = RegisteredStates.Find(CurrentState);
    if (!CurrentStateInfo) return false;

    if (!CurrentStateInfo->bCanBeInterrupted && StateTimer < CurrentStateInfo->MinStateTime)
    {
        PendingState = TargetState;
        bTransitionPending = true;
        return false;
    }

    for (const FAnimTransitionRule& Rule : CurrentStateInfo->Transitions)
    {
        if (Rule.ToState == TargetState)
        {
            ExecuteTransition(Rule);
            return true;
        }
    }

    for (auto& Pair : RegisteredStates)
    {
        if (Pair.Key == TargetState)
        {
            FAnimTransitionRule DefaultRule;
            DefaultRule.FromState = CurrentState;
            DefaultRule.ToState = TargetState;
            DefaultRule.BlendDuration = TransitionBlendTime;
            ExecuteTransition(DefaultRule);
            return true;
        }
    }

    return false;
}

void ULesFightAnimationStateMachine::ForceTransition(FName TargetState)
{
    FAnimTransitionRule Rule;
    Rule.FromState = CurrentState;
    Rule.ToState = TargetState;
    Rule.BlendDuration = TransitionBlendTime;
    ExecuteTransition(Rule);
}

void ULesFightAnimationStateMachine::RegisterState(const FAnimStateInfo& StateInfo)
{
    if (!StateInfo.StateName.IsNone())
    {
        RegisteredStates.Add(StateInfo.StateName, StateInfo);
    }
}

void ULesFightAnimationStateMachine::SetAnimationQuality(EAnimationQuality Quality)
{
    switch (Quality)
    {
    case EAnimationQuality::Low:
        TransitionBlendTime = 0.1f;
        break;
    case EAnimationQuality::Medium:
        TransitionBlendTime = 0.15f;
        break;
    case EAnimationQuality::High:
    case EAnimationQuality::Epic:
    case EAnimationQuality::Cinematic:
        TransitionBlendTime = 0.2f;
        break;
    }
}

float ULesFightAnimationStateMachine::GetNormalizedStateTime() const
{
    const FAnimStateInfo* StateInfo = RegisteredStates.Find(CurrentState);
    if (!StateInfo || StateInfo->MinStateTime <= 0.0f) return 0.0f;
    return FMath::Clamp(StateTimer / StateInfo->MinStateTime, 0.0f, 1.0f);
}

bool ULesFightAnimationStateMachine::CanTransitionTo(FName TargetState) const
{
    if (CurrentState == TargetState) return true;

    const FAnimStateInfo* StateInfo = RegisteredStates.Find(CurrentState);
    if (!StateInfo) return false;

    for (const FAnimTransitionRule& Rule : StateInfo->Transitions)
    {
        if (Rule.ToState == TargetState) return true;
    }
    return false;
}

void ULesFightAnimationStateMachine::ExecuteTransition(const FAnimTransitionRule& Rule)
{
    PreviousState = CurrentState;
    CurrentState = Rule.ToState;
    StateTimer = 0.0f;
    bTransitionPending = false;
    PendingState = NAME_None;

    OnStateExit(PreviousState);
    OnStateEnter(CurrentState);
    OnAnimStateChanged.Broadcast(PreviousState, CurrentState);
}

void ULesFightAnimationStateMachine::OnStateEnter(FName StateName)
{
    OnAnimStateEntered.Broadcast(StateName);
}

void ULesFightAnimationStateMachine::OnStateExit(FName StateName)
{
    OnAnimStateExited.Broadcast(StateName);
}
