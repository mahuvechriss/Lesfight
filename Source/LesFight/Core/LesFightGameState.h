#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LesFightGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchTimeUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStateChanged, int32, NewRound);

UCLASS()
class ALesFightGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    ALesFightGameState();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Match")
    void SetRoundNumber(int32 NewRound);

    UFUNCTION(BlueprintPure, Category = "LesFight|Match")
    int32 GetRoundNumber() const { return RoundNumber; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Match")
    float GetRoundTimeRemaining() const { return RoundTimeRemaining; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Match")
    void SetRoundTimeRemaining(float NewTime);

    UFUNCTION(BlueprintPure, Category = "LesFight|Match")
    int32 GetMaxRounds() const { return MaxRounds; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Match")
    void SetMaxRounds(int32 NewMax) { MaxRounds = NewMax; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Match")
    float GetMatchTimer() const { return MatchTimer; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Match")
    bool IsMatchActive() const { return bIsMatchActive; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Match")
    void SetMatchActive(bool bActive) { bIsMatchActive = bActive; }

protected:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Match")
    int32 RoundNumber;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Match")
    float RoundTimeRemaining;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Match")
    float MatchTimer;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Match")
    bool bIsMatchActive;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Match")
    int32 MaxRounds;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnMatchTimeUpdated OnMatchTimeUpdated;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnRoundStateChanged OnRoundStateChanged;

private:
    float ElapsedTime;
};
