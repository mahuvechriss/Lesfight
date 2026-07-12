#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkPlayerState.generated.h"

UCLASS(Blueprintable)
class ALesFightNetworkPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ALesFightNetworkPlayerState();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void SetPlayerIndex(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void SetPlayerReady(bool bReady);

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void IncrementRoundWins();

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void ResetRoundWins();

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void SetCharacterSelection(const FName& CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void SetPingMs(int32 Ping);

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void SetPlayerTeam(int32 TeamIndex);

    UFUNCTION(BlueprintPure, Category = "Network|PlayerState")
    int32 GetPlayerIndex() const { return PlayerIndex; }

    UFUNCTION(BlueprintPure, Category = "Network|PlayerState")
    bool IsReady() const { return bReady; }

    UFUNCTION(BlueprintPure, Category = "Network|PlayerState")
    int32 GetRoundWins() const { return RoundWins; }

    UFUNCTION(BlueprintPure, Category = "Network|PlayerState")
    FName GetCharacterSelection() const { return SelectedCharacterID; }

    UFUNCTION(BlueprintPure, Category = "Network|PlayerState")
    int32 GetPingMs() const { return PingMs; }

    UFUNCTION(BlueprintPure, Category = "Network|PlayerState")
    int32 GetPlayerTeam() const { return TeamIndex; }

    UFUNCTION(BlueprintPure, Category = "Network|PlayerState")
    ENetworkPlayerRole GetPlayerRole() const { return Role; }

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void SetPlayerRole(ENetworkPlayerRole NewRole);

    UFUNCTION(BlueprintCallable, Category = "Network|PlayerState")
    void Reset();

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 PlayerIndex;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    bool bReady;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 RoundWins;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    FName SelectedCharacterID;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 PingMs;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    int32 TeamIndex;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "State")
    ENetworkPlayerRole Role;
};
