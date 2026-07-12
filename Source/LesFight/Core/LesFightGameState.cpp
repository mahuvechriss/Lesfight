#include "LesFightGameState.h"
#include "Net/UnrealNetwork.h"
#include "LesFight.h"

ALesFightGameState::ALesFightGameState()
	: RoundNumber(1)
	, RoundTimeRemaining(99.0f)
	, MatchTimer(0.0f)
	, bIsMatchActive(false)
	, MaxRounds(3)
	, ElapsedTime(0.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;
	bReplicates = true;
}

void ALesFightGameState::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogLesFight, Log, TEXT("LesFightGameState initialized"));
}

void ALesFightGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMatchActive)
	{
		ElapsedTime += DeltaTime;
		MatchTimer += DeltaTime;
		RoundTimeRemaining = FMath::Max(0.0f, RoundTimeRemaining - DeltaTime);
	}
}

void ALesFightGameState::SetRoundNumber(int32 NewRound)
{
	if (RoundNumber != NewRound)
	{
		RoundNumber = NewRound;
		OnRoundStateChanged.Broadcast(RoundNumber);
		UE_LOG(LogLesFight, Log, TEXT("Round changed to %d"), RoundNumber);
	}
}

void ALesFightGameState::SetRoundTimeRemaining(float NewTime)
{
	RoundTimeRemaining = NewTime;
	OnMatchTimeUpdated.Broadcast();
}

void ALesFightGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALesFightGameState, RoundNumber);
	DOREPLIFETIME(ALesFightGameState, RoundTimeRemaining);
	DOREPLIFETIME(ALesFightGameState, MatchTimer);
	DOREPLIFETIME(ALesFightGameState, bIsMatchActive);
}
