#include "LesFightGameMode.h"
#include "LesFightPlayerController.h"
#include "LesFightGameState.h"
#include "LesFightPlayerState.h"
#include "LesFightBaseCharacter.h"
#include "LesFight.h"
#include "Engine/World.h"

ALesFightGameMode::ALesFightGameMode()
	: MaxRounds(3)
	, RoundTimeLimit(99.0f)
	, CurrentMatchState(EGameMatchState::None)
	, CurrentRound(1)
	, MatchTime(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f;

	PlayerControllerClass = ALesFightPlayerController::StaticClass();
	GameStateClass = ALesFightGameState::StaticClass();
	PlayerStateClass = ALesFightPlayerState::StaticClass();
	DefaultPawnClass = ALesFightBaseCharacter::StaticClass();
}

void ALesFightGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogLesFight, Log, TEXT("LesFightGameMode initialized"));
	SetMatchState(EGameMatchState::WaitingForPlayers);
}

void ALesFightGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentMatchState == EGameMatchState::RoundActive)
	{
		MatchTime += DeltaTime;
	}
}

void ALesFightGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ALesFightPlayerController* LesFightPC = Cast<ALesFightPlayerController>(NewPlayer);
	if (LesFightPC)
	{
		ConnectedPlayers.Add(LesFightPC);
		UE_LOG(LogLesFight, Log, TEXT("Player connected. Total players: %d"), ConnectedPlayers.Num());
	}
}

void ALesFightGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	ALesFightPlayerController* LesFightPC = Cast<ALesFightPlayerController>(Exiting);
	if (LesFightPC)
	{
		ConnectedPlayers.Remove(LesFightPC);
		UE_LOG(LogLesFight, Log, TEXT("Player disconnected. Total players: %d"), ConnectedPlayers.Num());
	}
}

void ALesFightGameMode::SetMatchState(EGameMatchState NewState)
{
	if (CurrentMatchState != NewState)
	{
		EGameMatchState PreviousState = CurrentMatchState;
		CurrentMatchState = NewState;
		OnMatchStateChanged.Broadcast(NewState);

		UE_LOG(LogLesFight, Log, TEXT("Match state changed: %d -> %d"),
			static_cast<int32>(PreviousState), static_cast<int32>(NewState));

		switch (NewState)
		{
		case EGameMatchState::RoundActive:
			OnRoundStart();
			break;
		case EGameMatchState::KOResult:
			OnRoundEnd();
			break;
		case EGameMatchState::MatchResult:
			OnMatchEnd();
			break;
		default:
			break;
		}
	}
}

void ALesFightGameMode::OnRoundStart()
{
	MatchTime = 0.0f;
	UE_LOG(LogLesFight, Log, TEXT("Round %d started"), CurrentRound);
}

void ALesFightGameMode::OnRoundEnd()
{
	UE_LOG(LogLesFight, Log, TEXT("Round %d ended"), CurrentRound);

	if (CurrentRound >= MaxRounds)
	{
		SetMatchState(EGameMatchState::MatchResult);
	}
	else
	{
		CurrentRound++;
	}
}

void ALesFightGameMode::OnMatchEnd()
{
	UE_LOG(LogLesFight, Log, TEXT("Match ended"));
}
