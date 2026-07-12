#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LesFightGameMode.generated.h"

class ALesFightPlayerController;
class ALesFightBaseCharacter;

UENUM(BlueprintType)
enum class EGameMatchState : uint8
{
    None,
    WaitingForPlayers,
    CharacterSelect,
    MatchIntro,
    RoundActive,
    RoundPaused,
    KOResult,
    MatchResult,
    PostMatch
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChanged, EGameMatchState, NewState);

UCLASS()
class ALesFightGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ALesFightGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual void Logout(AController* Exiting) override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Match")
    void SetMatchState(EGameMatchState NewState);

    UFUNCTION(BlueprintPure, Category = "LesFight|Match")
    EGameMatchState GetMatchState() const { return CurrentMatchState; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Match")
    int32 GetConnectedPlayerCount() const { return ConnectedPlayers.Num(); }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Match")
    float GetMatchTime() const { return MatchTime; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Round")
    int32 GetCurrentRound() const { return CurrentRound; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Round")
    int32 GetMaxRounds() const { return MaxRounds; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Round")
    float GetRoundTimeLimit() const { return RoundTimeLimit; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Round")
    int32 MaxRounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Round")
    float RoundTimeLimit;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnMatchStateChanged OnMatchStateChanged;

    UPROPERTY()
    TArray<ALesFightPlayerController*> ConnectedPlayers;

private:
    EGameMatchState CurrentMatchState;
    int32 CurrentRound;
    float MatchTime;

    void OnRoundStart();
    void OnRoundEnd();
    void OnMatchEnd();
};
