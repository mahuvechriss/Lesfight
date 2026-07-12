#include "LesFightPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "LesFight.h"

ALesFightPlayerState::ALesFightPlayerState()
    : MaxHealth(1000.0f)
    , Health(MaxHealth)
    , RoundsWon(0)
    , TotalWins(0)
    , DamageDealt(0.0f)
    , PlayerIndex(-1)
{
    bReplicates = true;
}

void ALesFightPlayerState::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
}

void ALesFightPlayerState::Reset()
{
    Super::Reset();
    Health = MaxHealth;
    RoundsWon = 0;
    DamageDealt = 0.0f;
}

void ALesFightPlayerState::CopyProperties(APlayerState* PlayerState)
{
    Super::CopyProperties(PlayerState);

    ALesFightPlayerState* LesFightPS = Cast<ALesFightPlayerState>(PlayerState);
    if (LesFightPS)
    {
        LesFightPS->CharacterName = CharacterName;
        LesFightPS->PlayerIndex = PlayerIndex;
        LesFightPS->RoundsWon = RoundsWon;
        LesFightPS->TotalWins = TotalWins;
        LesFightPS->DamageDealt = DamageDealt;
    }
}

void ALesFightPlayerState::SetPlayerHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health, MaxHealth);

    if (Health <= 0.0f)
    {
        UE_LOG(LogLesFight, Log, TEXT("Player %s has been defeated"), *GetPlayerName());
    }
}

void ALesFightPlayerState::AddRoundWin()
{
    RoundsWon++;
    OnRoundsWonChanged.Broadcast(RoundsWon);
    UE_LOG(LogLesFight, Log, TEXT("Player %s won round. Total: %d"), *GetPlayerName(), RoundsWon);
}

void ALesFightPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALesFightPlayerState, CharacterName);
    DOREPLIFETIME(ALesFightPlayerState, PlayerIndex);
    DOREPLIFETIME(ALesFightPlayerState, RoundsWon);
    DOREPLIFETIME(ALesFightPlayerState, TotalWins);
    DOREPLIFETIME(ALesFightPlayerState, DamageDealt);
}
