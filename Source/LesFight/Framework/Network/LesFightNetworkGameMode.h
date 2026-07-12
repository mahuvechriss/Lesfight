#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LesFightNetworkData.h"
#include "LesFightNetworkGameMode.generated.h"

UCLASS(Blueprintable)
class ALesFightNetworkGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    ALesFightNetworkGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;
    virtual void PreInitializeComponents() override;

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void StartNetworkMatch();

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void EndNetworkMatch(int32 WinnerPlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void StartNetworkRound(int32 RoundNumber);

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void EndNetworkRound(int32 WinnerPlayerIndex);

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void HandleCombatActionFromPlayer(int32 PlayerIndex, const FNetworkCombatAction& Action);

    UFUNCTION(BlueprintExec, Category = "Network|GameMode")
    void SetMaxPlayers(int32 Count);

    UFUNCTION(BlueprintPure, Category = "Network|GameMode")
    int32 GetMaxPlayers() const { return MaxPlayers; }

    UFUNCTION(BlueprintPure, Category = "Network|GameMode")
    int32 GetConnectedPlayerCount() const;

    UFUNCTION(BlueprintPure, Category = "Network|GameMode")
    bool AreMinPlayersConnected() const;

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void OnPlayerReady(int32 PlayerIndex, bool bReady);

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void RequestFullStateSync();

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    ENetworkMatchState GetMatchState() const { return CurrentMatchState; }

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void SetMatchManager(class ULesFightMatchManager* InMatchManager);

    UFUNCTION(BlueprintCallable, Category = "Network|GameMode")
    void SetMultiplayerManager(class ULesFightMultiplayerManager* InMultiplayerManager);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxPlayers;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    ENetworkMatchState CurrentMatchState;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<class APlayerController*> ConnectedPlayers;

    UPROPERTY(BlueprintReadOnly, Category = "References")
    class ULesFightMatchManager* MatchManager;

    UPROPERTY(BlueprintReadOnly, Category = "References")
    class ULesFightMultiplayerManager* MultiplayerManager;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float RoundTimeLimit;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxRounds;

private:
    TMap<int32, bool> PlayerReadyMap;
    TMap<int32, class ALesFightNetworkPlayerController*> PlayerControllers;

    void BroadcastMatchStateToAll(ENetworkMatchState NewState);
    void SpawnPlayerCharacters();
    class ALesFightNetworkGameState* GetNetworkGameState() const;
};
