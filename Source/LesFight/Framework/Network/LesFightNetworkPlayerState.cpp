#include "LesFightNetworkPlayerState.h"
#include "Net/UnrealNetwork.h"

ALesFightNetworkPlayerState::ALesFightNetworkPlayerState()
    : PlayerIndex(-1)
    , bReady(false)
    , RoundWins(0)
    , SelectedCharacterID(NAME_None)
    , PingMs(0)
    , TeamIndex(0)
    , Role(ENetworkPlayerRole::Client)
{
    bReplicates = true;
}

void ALesFightNetworkPlayerState::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALesFightNetworkPlayerState, PlayerIndex);
    DOREPLIFETIME(ALesFightNetworkPlayerState, bReady);
    DOREPLIFETIME(ALesFightNetworkPlayerState, RoundWins);
    DOREPLIFETIME(ALesFightNetworkPlayerState, SelectedCharacterID);
    DOREPLIFETIME(ALesFightNetworkPlayerState, PingMs);
    DOREPLIFETIME(ALesFightNetworkPlayerState, TeamIndex);
    DOREPLIFETIME(ALesFightNetworkPlayerState, Role);
}

void ALesFightNetworkPlayerState::SetPlayerIndex(int32 Index)
{
    PlayerIndex = Index;
}

void ALesFightNetworkPlayerState::SetPlayerReady(bool bNewReady)
{
    bReady = bNewReady;
}

void ALesFightNetworkPlayerState::IncrementRoundWins()
{
    RoundWins++;
}

void ALesFightNetworkPlayerState::ResetRoundWins()
{
    RoundWins = 0;
}

void ALesFightNetworkPlayerState::SetCharacterSelection(const FName& CharacterID)
{
    SelectedCharacterID = CharacterID;
}

void ALesFightNetworkPlayerState::SetPingMs(int32 Ping)
{
    PingMs = FMath::Clamp(Ping, 0, 999);
}

void ALesFightNetworkPlayerState::SetPlayerTeam(int32 InTeamIndex)
{
    TeamIndex = InTeamIndex;
}

void ALesFightNetworkPlayerState::SetPlayerRole(ENetworkPlayerRole NewRole)
{
    Role = NewRole;
}

void ALesFightNetworkPlayerState::Reset()
{
    bReady = false;
    RoundWins = 0;
    SelectedCharacterID = NAME_None;
    PingMs = 0;
}
