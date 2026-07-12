#include "LesFightMenuStateManager.h"

void ULesFightMenuStateManager::Initialize()
{
	CurrentState = EUIMenuState::MainMenu;
	PreviousState = EUIMenuState::MainMenu;

	ValidTransitions.Empty();

	ValidTransitions.Add(EUIMenuState::MainMenu, {
		EUIMenuState::CharacterSelect,
		EUIMenuState::Options,
		EUIMenuState::Profile,
		EUIMenuState::MultiplayerLobby,
		EUIMenuState::Credits,
		EUIMenuState::Exiting
	});

	ValidTransitions.Add(EUIMenuState::CharacterSelect, {
		EUIMenuState::MainMenu,
		EUIMenuState::CharacterCreator,
		EUIMenuState::AIGeneration,
		EUIMenuState::MultiplayerLobby
	});

	ValidTransitions.Add(EUIMenuState::CharacterCreator, {
		EUIMenuState::CharacterSelect,
		EUIMenuState::MainMenu
	});

	ValidTransitions.Add(EUIMenuState::AIGeneration, {
		EUIMenuState::CharacterSelect,
		EUIMenuState::MainMenu
	});

	ValidTransitions.Add(EUIMenuState::MultiplayerLobby, {
		EUIMenuState::MainMenu,
		EUIMenuState::CharacterSelect
	});

	ValidTransitions.Add(EUIMenuState::Options, {
		EUIMenuState::MainMenu
	});

	ValidTransitions.Add(EUIMenuState::Profile, {
		EUIMenuState::MainMenu
	});

	ValidTransitions.Add(EUIMenuState::Credits, {
		EUIMenuState::MainMenu
	});

	ValidTransitions.Add(EUIMenuState::Exiting, {});
}

void ULesFightMenuStateManager::Shutdown()
{
	ValidTransitions.Empty();
}

void ULesFightMenuStateManager::SetState(EUIMenuState NewState)
{
	if (!CanTransitionTo(NewState))
	{
		return;
	}

	PreviousState = CurrentState;
	CurrentState = NewState;

	OnMenuStateChanged.Broadcast(PreviousState, CurrentState);
}

bool ULesFightMenuStateManager::CanTransitionTo(EUIMenuState TargetState) const
{
	const TArray<EUIMenuState>* Transitions = ValidTransitions.Find(CurrentState);
	if (!Transitions)
	{
		return false;
	}

	return Transitions->Contains(TargetState);
}

bool ULesFightMenuStateManager::IsStateValid(EUIMenuState State) const
{
	return ValidTransitions.Contains(State);
}

TArray<EUIMenuState> ULesFightMenuStateManager::GetAvailableStates() const
{
	const TArray<EUIMenuState>* Transitions = ValidTransitions.Find(CurrentState);
	if (Transitions)
	{
		return *Transitions;
	}
	return {};
}
