#include "LesFightCharacterStateMachine.h"
#include "LesFight.h"

ULesFightCharacterStateMachine::ULesFightCharacterStateMachine()
    : CurrentState(ECharacterGameplayState::None)
    , PreviousState(ECharacterGameplayState::None)
    , TimeInCurrentState(0.0f)
    , StateStartTime(0.0f)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.05f;
    bWantsInitializeComponent = true;

    AllowedStateTransitions = {
        ECharacterGameplayState::Spawning,
        ECharacterGameplayState::Idle,
        ECharacterGameplayState::Moving,
        ECharacterGameplayState::Sprinting,
        ECharacterGameplayState::Jumping,
        ECharacterGameplayState::Falling,
        ECharacterGameplayState::Landing,
        ECharacterGameplayState::Crouching,
        ECharacterGameplayState::Attacking,
        ECharacterGameplayState::Blocking,
        ECharacterGameplayState::HitStun,
        ECharacterGameplayState::KnockedDown,
        ECharacterGameplayState::GettingUp,
        ECharacterGameplayState::Dead,
        ECharacterGameplayState::Respawning,
        ECharacterGameplayState::Cinematic
    };
}

void ULesFightCharacterStateMachine::BeginPlay()
{
    Super::BeginPlay();
    SetState(ECharacterGameplayState::Spawning);
}

void ULesFightCharacterStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TimeInCurrentState = GetWorld()->GetTimeSeconds() - StateStartTime;
    OnStateTick(DeltaTime);
}

void ULesFightCharacterStateMachine::SetState(ECharacterGameplayState NewState)
{
    if (!CanTransitionTo(NewState))
    {
        UE_LOG(LogLesFight, Verbose, TEXT("State transition %d -> %d not allowed"),
            static_cast<int32>(CurrentState), static_cast<int32>(NewState));
        return;
    }

    if (CurrentState == NewState) return;

    OnStateExit(CurrentState);
    PreviousState = CurrentState;
    CurrentState = NewState;
    StateStartTime = GetWorld()->GetTimeSeconds();
    TimeInCurrentState = 0.0f;
    OnStateEnter(CurrentState);

    OnGameplayStateChanged.Broadcast(CurrentState, PreviousState);
    UE_LOG(LogLesFight, Verbose, TEXT("State changed: %d -> %d"),
        static_cast<int32>(PreviousState), static_cast<int32>(CurrentState));
}

bool ULesFightCharacterStateMachine::CanTransitionTo(ECharacterGameplayState NewState) const
{
    if (CurrentState == ECharacterGameplayState::None) return true;
    if (CurrentState == ECharacterGameplayState::Dead && NewState != ECharacterGameplayState::Respawning) return false;
    if (CurrentState == ECharacterGameplayState::Cinematic) return false;

    return IsStateTransitionAllowed(CurrentState, NewState);
}

void ULesFightCharacterStateMachine::ForceState(ECharacterGameplayState NewState)
{
    PreviousState = CurrentState;
    ECharacterGameplayState OldState = CurrentState;
    CurrentState = NewState;
    StateStartTime = GetWorld()->GetTimeSeconds();
    TimeInCurrentState = 0.0f;

    OnStateExit(OldState);
    OnStateEnter(NewState);
    OnGameplayStateChanged.Broadcast(CurrentState, PreviousState);
}

void ULesFightCharacterStateMachine::SetStateTransitionDuration(ECharacterGameplayState State, float Duration)
{
    StateTransitionDurations.Add(State, Duration);
}

void ULesFightCharacterStateMachine::OnStateEnter(ECharacterGameplayState NewState)
{
    switch (NewState)
    {
    case ECharacterGameplayState::Spawning:
        UE_LOG(LogLesFight, Log, TEXT("Character spawning"));
        break;
    case ECharacterGameplayState::Dead:
        UE_LOG(LogLesFight, Log, TEXT("Character died"));
        break;
    case ECharacterGameplayState::Respawning:
        UE_LOG(LogLesFight, Log, TEXT("Character respawning"));
        break;
    default:
        break;
    }
}

void ULesFightCharacterStateMachine::OnStateExit(ECharacterGameplayState OldState)
{
}

void ULesFightCharacterStateMachine::OnStateTick(float DeltaTime)
{
    if (CurrentState == ECharacterGameplayState::Spawning)
    {
        float* Duration = StateTransitionDurations.Find(ECharacterGameplayState::Spawning);
        if (Duration && TimeInCurrentState >= *Duration)
        {
            SetState(ECharacterGameplayState::Idle);
        }
    }

    if (CurrentState == ECharacterGameplayState::Landing)
    {
        float* Duration = StateTransitionDurations.Find(ECharacterGameplayState::Landing);
        if (Duration && TimeInCurrentState >= *Duration)
        {
            SetState(ECharacterGameplayState::Idle);
        }
    }
}

bool ULesFightCharacterStateMachine::IsStateTransitionAllowed(ECharacterGameplayState From, ECharacterGameplayState To) const
{
    return true;
}
