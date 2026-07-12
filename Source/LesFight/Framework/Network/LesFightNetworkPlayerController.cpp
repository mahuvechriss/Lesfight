#include "LesFightNetworkPlayerController.h"
#include "LesFightNetworkPlayerState.h"
#include "LesFightMultiplayerManager.h"
#include "Engine/World.h"

ALesFightNetworkPlayerController::ALesFightNetworkPlayerController()
    : InputReplicationRate(0.033f)
    , CombatActionCooldown(0.05f)
    , LastInputReplicationTime(0.0f)
    , LastCombatActionTime(0.0f)
{
    bReplicates = true;
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.033f;
}

void ALesFightNetworkPlayerController::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ALesFightNetworkPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogLesFightNetwork, Log, TEXT("PlayerController spawned for %s"),
        HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"));
}

void ALesFightNetworkPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        SendPendingCombatActions();
    }
}

void ALesFightNetworkPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

bool ALesFightNetworkPlayerController::ServerSetPlayerReady_Validate(bool bReady) { return true; }
void ALesFightNetworkPlayerController::ServerSetPlayerReady_Implementation(bool bReady)
{
    if (ALesFightNetworkPlayerState* PS = GetPlayerState<ALesFightNetworkPlayerState>())
    {
        PS->SetPlayerReady(bReady);
    }
}

bool ALesFightNetworkPlayerController::ServerSendCombatAction_Validate(
    const FNetworkCombatAction& Action) { return true; }
void ALesFightNetworkPlayerController::ServerSendCombatAction_Implementation(
    const FNetworkCombatAction& Action)
{
    if (ALesFightNetworkGameMode* GM = GetWorld()->GetAuthGameMode<ALesFightNetworkGameMode>())
    {
        ALesFightNetworkPlayerState* PS = GetPlayerState<ALesFightNetworkPlayerState>();
        int32 PlayerIndex = PS ? PS->GetPlayerIndex() : -1;
        GM->HandleCombatActionFromPlayer(PlayerIndex, Action);
    }
}

bool ALesFightNetworkPlayerController::ServerSendInput_Validate(
    const FName& InputAction, float InputValue) { return true; }
void ALesFightNetworkPlayerController::ServerSendInput_Implementation(
    const FName& InputAction, float InputValue)
{
}

bool ALesFightNetworkPlayerController::ServerSelectCharacter_Validate(
    const FName& CharacterID) { return true; }
void ALesFightNetworkPlayerController::ServerSelectCharacter_Implementation(
    const FName& CharacterID)
{
    if (ALesFightNetworkPlayerState* PS = GetPlayerState<ALesFightNetworkPlayerState>())
    {
        PS->SetCharacterSelection(CharacterID);
    }
}

bool ALesFightNetworkPlayerController::ServerRequestFullStateSync_Validate() { return true; }
void ALesFightNetworkPlayerController::ServerRequestFullStateSync_Implementation()
{
    if (ALesFightNetworkGameMode* GM = GetWorld()->GetAuthGameMode<ALesFightNetworkGameMode>())
    {
        GM->RequestFullStateSync();
    }
}

bool ALesFightNetworkPlayerController::ServerReportPing_Validate(int32 PingMs) { return true; }
void ALesFightNetworkPlayerController::ServerReportPing_Implementation(int32 InPingMs)
{
    if (ALesFightNetworkPlayerState* PS = GetPlayerState<ALesFightNetworkPlayerState>())
    {
        PS->SetPingMs(InPingMs);
    }
}

void ALesFightNetworkPlayerController::ClientUpdateMatchState_Implementation(
    ENetworkMatchState NewState)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("Match state updated: %d"), static_cast<int32>(NewState));
}

void ALesFightNetworkPlayerController::ClientReceiveCombatAction_Implementation(
    int32 SenderIndex, const FNetworkCombatAction& Action)
{
    if (MultiplayerManager.IsValid())
    {
        MultiplayerManager->OnCombatAction(Action);
    }
}

void ALesFightNetworkPlayerController::ClientReceiveAnimationSync_Implementation(
    int32 SenderIndex, const FNetworkAnimSyncData& AnimData)
{
}

void ALesFightNetworkPlayerController::ClientReceiveChatMessage_Implementation(
    const FString& SenderName, const FString& Message)
{
}

void ALesFightNetworkPlayerController::ClientReceiveSystemMessage_Implementation(
    const FString& Message)
{
    UE_LOG(LogLesFightNetwork, Log, TEXT("System: %s"), *Message);
}

void ALesFightNetworkPlayerController::ClientForceStateSync_Implementation(
    const FNetworkMatchData& MatchData)
{
}

void ALesFightNetworkPlayerController::ClientNotifyMatchStarted_Implementation()
{
}

void ALesFightNetworkPlayerController::ClientNotifyRoundStarted_Implementation(
    int32 RoundNumber)
{
}

void ALesFightNetworkPlayerController::ClientNotifyRoundEnded_Implementation(
    int32 WinnerIndex)
{
}

void ALesFightNetworkPlayerController::ClientNotifyMatchEnded_Implementation(
    int32 WinnerIndex)
{
}

void ALesFightNetworkPlayerController::ClientNotifyCountdown_Implementation(
    int32 SecondsRemaining)
{
}

void ALesFightNetworkPlayerController::ClientPlayVFX_Implementation(
    FName EffectID, FVector Location, FRotator Rotation)
{
}

void ALesFightNetworkPlayerController::ClientPlayAudio_Implementation(
    FName SoundID, FVector Location, float Volume)
{
}

void ALesFightNetworkPlayerController::ClientShowError_Implementation(
    const FString& ErrorMessage)
{
    UE_LOG(LogLesFightNetwork, Error, TEXT("Server error: %s"), *ErrorMessage);
}

void ALesFightNetworkPlayerController::ClientReplicateHealthChange_Implementation(
    int32 PlayerIndex, float NewHealth, float MaxHealth)
{
}

void ALesFightNetworkPlayerController::ClientReplicateStaminaChange_Implementation(
    int32 PlayerIndex, float NewStamina, float MaxStamina)
{
}

void ALesFightNetworkPlayerController::ClientReplicateMeterChange_Implementation(
    int32 PlayerIndex, float NewMeter, float MaxMeter)
{
}

void ALesFightNetworkPlayerController::ClientReplicateKnockdown_Implementation(
    int32 PlayerIndex, int32 AttackerIndex)
{
}

void ALesFightNetworkPlayerController::ClientReplicatePlayerTransform_Implementation(
    int32 PlayerIndex, FTransform Transform)
{
}

bool ALesFightNetworkPlayerController::IsLocalPlayerHost() const
{
    return HasAuthority();
}

int32 ALesFightNetworkPlayerController::GetPlayerIndex() const
{
    ALesFightNetworkPlayerState* PS = GetPlayerState<ALesFightNetworkPlayerState>();
    return PS ? PS->GetPlayerIndex() : -1;
}

void ALesFightNetworkPlayerController::SetMultiplayerManager(
    ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
}

void ALesFightNetworkPlayerController::RequestCombatActionReplication(
    const FNetworkCombatAction& Action)
{
    if (HasAuthority())
    {
        PendingCombatActions.Add(Action);
    }
    else
    {
        ServerSendCombatAction(Action);
    }
}

void ALesFightNetworkPlayerController::SendPendingCombatActions()
{
    if (PendingCombatActions.Num() > 0)
    {
        for (const FNetworkCombatAction& Action : PendingCombatActions)
        {
            if (ALesFightNetworkGameMode* GM = GetWorld()->GetAuthGameMode<ALesFightNetworkGameMode>())
            {
                ALesFightNetworkPlayerState* PS = GetPlayerState<ALesFightNetworkPlayerState>();
                GM->HandleCombatActionFromPlayer(PS ? PS->GetPlayerIndex() : -1, Action);
            }
        }
        PendingCombatActions.Empty();
    }
}
