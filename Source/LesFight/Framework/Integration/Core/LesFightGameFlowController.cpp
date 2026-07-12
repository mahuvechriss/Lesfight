#include "Framework/Integration/Core/LesFightGameFlowController.h"

static FText GetStateText(EGameFlowState State)
{
    switch (State)
    {
        case EGameFlowState::Init:             return NSLOCTEXT("GameFlow", "Init", "Init");
        case EGameFlowState::Loading:          return NSLOCTEXT("GameFlow", "Loading", "Loading");
        case EGameFlowState::ProfileSelect:    return NSLOCTEXT("GameFlow", "ProfileSelect", "Profile Select");
        case EGameFlowState::MainMenu:         return NSLOCTEXT("GameFlow", "MainMenu", "Main Menu");
        case EGameFlowState::CharacterSelect:  return NSLOCTEXT("GameFlow", "CharacterSelect", "Character Select");
        case EGameFlowState::CharacterCreator: return NSLOCTEXT("GameFlow", "CharacterCreator", "Character Creator");
        case EGameFlowState::AIGeneration:     return NSLOCTEXT("GameFlow", "AIGeneration", "AI Generation");
        case EGameFlowState::MatchPrep:        return NSLOCTEXT("GameFlow", "MatchPrep", "Match Preparation");
        case EGameFlowState::ArenaLoading:     return NSLOCTEXT("GameFlow", "ArenaLoading", "Arena Loading");
        case EGameFlowState::FightIntro:       return NSLOCTEXT("GameFlow", "FightIntro", "Fight Intro");
        case EGameFlowState::Fighting:         return NSLOCTEXT("GameFlow", "Fighting", "Fighting");
        case EGameFlowState::RoundEnd:         return NSLOCTEXT("GameFlow", "RoundEnd", "Round End");
        case EGameFlowState::MatchResult:      return NSLOCTEXT("GameFlow", "MatchResult", "Match Result");
        case EGameFlowState::PauseMenu:        return NSLOCTEXT("GameFlow", "PauseMenu", "Pause Menu");
        case EGameFlowState::Options:          return NSLOCTEXT("GameFlow", "Options", "Options");
        case EGameFlowState::Exiting:          return NSLOCTEXT("GameFlow", "Exiting", "Exiting");
        default:                               return NSLOCTEXT("GameFlow", "Unknown", "Unknown");
    }
}

void ULesFightGameFlowController::Initialize()
{
    CurrentState = EGameFlowState::Init;
    PreviousState = EGameFlowState::Init;

    ValidTransitions.Empty();
    StateDisplayNames.Empty();

    ValidTransitions.Add(EGameFlowState::Init,             { EGameFlowState::Loading });
    ValidTransitions.Add(EGameFlowState::Loading,          { EGameFlowState::ProfileSelect });
    ValidTransitions.Add(EGameFlowState::ProfileSelect,    { EGameFlowState::MainMenu, EGameFlowState::ProfileSelect });
    ValidTransitions.Add(EGameFlowState::MainMenu,         { EGameFlowState::CharacterSelect, EGameFlowState::Options, EGameFlowState::MultiplayerLobby, EGameFlowState::ProfileSelect, EGameFlowState::Exiting });
    ValidTransitions.Add(EGameFlowState::CharacterSelect,  { EGameFlowState::CharacterCreator, EGameFlowState::AIGeneration, EGameFlowState::MatchPrep, EGameFlowState::MainMenu });
    ValidTransitions.Add(EGameFlowState::CharacterCreator, { EGameFlowState::CharacterSelect, EGameFlowState::MainMenu });
    ValidTransitions.Add(EGameFlowState::AIGeneration,     { EGameFlowState::CharacterSelect, EGameFlowState::MainMenu });
    ValidTransitions.Add(EGameFlowState::MatchPrep,        { EGameFlowState::ArenaLoading, EGameFlowState::CharacterSelect });
    ValidTransitions.Add(EGameFlowState::ArenaLoading,     { EGameFlowState::FightIntro, EGameFlowState::MainMenu });
    ValidTransitions.Add(EGameFlowState::FightIntro,       { EGameFlowState::Fighting });
    ValidTransitions.Add(EGameFlowState::Fighting,         { EGameFlowState::RoundEnd, EGameFlowState::PauseMenu });
    ValidTransitions.Add(EGameFlowState::RoundEnd,         { EGameFlowState::Fighting, EGameFlowState::MatchResult });
    ValidTransitions.Add(EGameFlowState::MatchResult,      { EGameFlowState::MainMenu, EGameFlowState::CharacterSelect });
    ValidTransitions.Add(EGameFlowState::PauseMenu,        { EGameFlowState::Fighting, EGameFlowState::Options, EGameFlowState::MainMenu });
    ValidTransitions.Add(EGameFlowState::Options,          { EGameFlowState::MainMenu, EGameFlowState::PauseMenu });
    ValidTransitions.Add(EGameFlowState::Exiting,          { });

    for (EGameFlowState State = EGameFlowState::Init; State <= EGameFlowState::Exiting; State = static_cast<EGameFlowState>(static_cast<uint8>(State) + 1))
    {
        if (!ValidTransitions.Contains(State))
        {
            ValidTransitions.Add(State, { });
        }
        if (!StateDisplayNames.Contains(State))
        {
            StateDisplayNames.Add(State, GetStateText(State));
        }
    }
}

void ULesFightGameFlowController::Shutdown()
{
    ValidTransitions.Empty();
    StateDisplayNames.Empty();
}

void ULesFightGameFlowController::SetState(EGameFlowState NewState)
{
    if (!CanTransitionTo(NewState))
    {
        return;
    }

    PreviousState = CurrentState;
    CurrentState = NewState;

    OnGameFlowStateChanged.Broadcast(PreviousState, CurrentState);
}

bool ULesFightGameFlowController::CanTransitionTo(EGameFlowState Target) const
{
    if (const TArray<EGameFlowState>* Transitions = ValidTransitions.Find(CurrentState))
    {
        return Transitions->Contains(Target);
    }
    return false;
}

TArray<EGameFlowState> ULesFightGameFlowController::GetValidTransitions() const
{
    if (const TArray<EGameFlowState>* Transitions = ValidTransitions.Find(CurrentState))
    {
        return *Transitions;
    }
    return { };
}

void ULesFightGameFlowController::TransitionToNextState()
{
    if (const TArray<EGameFlowState>* Transitions = ValidTransitions.Find(CurrentState))
    {
        if (Transitions->Num() > 0)
        {
            SetState((*Transitions)[0]);
        }
    }
}

void ULesFightGameFlowController::TransitionToPreviousState()
{
    if (PreviousState != CurrentState)
    {
        SetState(PreviousState);
    }
}

void ULesFightGameFlowController::ResetToState(EGameFlowState State)
{
    PreviousState = CurrentState;
    CurrentState = State;

    OnGameFlowStateChanged.Broadcast(PreviousState, CurrentState);
}

bool ULesFightGameFlowController::IsStateValid(EGameFlowState State) const
{
    return ValidTransitions.Contains(State);
}

FText ULesFightGameFlowController::GetStateDisplayName(EGameFlowState State) const
{
    if (const FText* Name = StateDisplayNames.Find(State))
    {
        return *Name;
    }
    return GetStateText(State);
}
