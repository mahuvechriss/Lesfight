#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LesFightPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundsWonChanged, int32, NewRoundsWon);

UCLASS()
class ALesFightPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ALesFightPlayerState();

    virtual void BeginPlay() override;
    virtual void Reset() override;
    virtual void CopyProperties(APlayerState* PlayerState) override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Player")
    void SetPlayerHealth(float NewHealth);

    UFUNCTION(BlueprintPure, Category = "LesFight|Player")
    float GetPlayerHealth() const { return Health; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Player")
    float GetMaxHealth() const { return MaxHealth; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Player")
    void SetCharacterName(const FName& NewName) { CharacterName = NewName; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Player")
    FName GetCharacterName() const { return CharacterName; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Score")
    void AddRoundWin();

    UFUNCTION(BlueprintPure, Category = "LesFight|Score")
    int32 GetRoundsWon() const { return RoundsWon; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Score")
    int32 GetTotalWins() const { return TotalWins; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Score")
    void SetTotalWins(int32 Wins) { TotalWins = Wins; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Stats")
    float GetDamageDealt() const { return DamageDealt; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Stats")
    void AddDamageDealt(float Amount) { DamageDealt += Amount; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Player")
    float MaxHealth;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnHealthChanged OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnRoundsWonChanged OnRoundsWonChanged;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Player")
    FName CharacterName;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Player")
    int32 PlayerIndex;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Score")
    int32 RoundsWon;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Score")
    int32 TotalWins;

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "LesFight|Stats")
    float DamageDealt;

private:
    UPROPERTY()
    float Health;

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
