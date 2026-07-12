#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkPlayerController.generated.h"

UCLASS(Blueprintable)
class ALesFightNetworkPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ALesFightNetworkPlayerController();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupInputComponent() override;

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSetPlayerReady(bool bReady);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSendCombatAction(const FNetworkCombatAction& Action);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSendInput(const FName& InputAction, float InputValue);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerSelectCharacter(const FName& CharacterID);

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerRequestFullStateSync();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerReportPing(int32 PingMs);

    UFUNCTION(Client, Reliable)
    void ClientUpdateMatchState(ENetworkMatchState NewState);

    UFUNCTION(Client, Reliable)
    void ClientReceiveCombatAction(int32 SenderIndex, const FNetworkCombatAction& Action);

    UFUNCTION(Client, Reliable)
    void ClientReceiveAnimationSync(int32 SenderIndex, const FNetworkAnimSyncData& AnimData);

    UFUNCTION(Client, Reliable)
    void ClientReceiveChatMessage(const FString& SenderName, const FString& Message);

    UFUNCTION(Client, Reliable)
    void ClientReceiveSystemMessage(const FString& Message);

    UFUNCTION(Client, Reliable)
    void ClientForceStateSync(const FNetworkMatchData& MatchData);

    UFUNCTION(Client, Reliable)
    void ClientNotifyMatchStarted();

    UFUNCTION(Client, Reliable)
    void ClientNotifyRoundStarted(int32 RoundNumber);

    UFUNCTION(Client, Reliable)
    void ClientNotifyRoundEnded(int32 WinnerIndex);

    UFUNCTION(Client, Reliable)
    void ClientNotifyMatchEnded(int32 WinnerIndex);

    UFUNCTION(Client, Reliable)
    void ClientNotifyCountdown(int32 SecondsRemaining);

    UFUNCTION(Client, Reliable)
    void ClientPlayVFX(FName EffectID, FVector Location, FRotator Rotation);

    UFUNCTION(Client, Reliable)
    void ClientPlayAudio(FName SoundID, FVector Location, float Volume);

    UFUNCTION(Client, Reliable)
    void ClientShowError(const FString& ErrorMessage);

    UFUNCTION(Client, Reliable)
    void ClientReplicateHealthChange(int32 PlayerIndex, float NewHealth, float MaxHealth);

    UFUNCTION(Client, Reliable)
    void ClientReplicateStaminaChange(int32 PlayerIndex, float NewStamina, float MaxStamina);

    UFUNCTION(Client, Reliable)
    void ClientReplicateMeterChange(int32 PlayerIndex, float NewMeter, float MaxMeter);

    UFUNCTION(Client, Reliable)
    void ClientReplicateKnockdown(int32 PlayerIndex, int32 AttackerIndex);

    UFUNCTION(Client, Reliable)
    void ClientReplicatePlayerTransform(int32 PlayerIndex, FTransform Transform);

    UFUNCTION(BlueprintPure, Category = "Network|PlayerController")
    bool IsLocalPlayerHost() const;

    UFUNCTION(BlueprintPure, Category = "Network|PlayerController")
    int32 GetPlayerIndex() const;

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerController")
    void SetMultiplayerManager(class ULesFightMultiplayerManager* InManager);

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerController")
    void RequestCombatActionReplication(const FNetworkCombatAction& Action);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float InputReplicationRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float CombatActionCooldown;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;
    float LastInputReplicationTime;
    float LastCombatActionTime;
    TArray<FNetworkCombatAction> PendingCombatActions;

    void SendPendingCombatActions();
};
