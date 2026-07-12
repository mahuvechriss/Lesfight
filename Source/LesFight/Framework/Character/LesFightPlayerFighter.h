#pragma once

#include "CoreMinimal.h"
#include "LesFightBaseFighter.h"
#include "LesFightPlayerFighter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerFighterReady, ALesFightPlayerFighter*, Fighter);

UCLASS()
class ALesFightPlayerFighter : public ALesFightBaseFighter
{
    GENERATED_BODY()

public:
    ALesFightPlayerFighter(const FObjectInitializer& ObjectInitializer);

    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "PlayerFighter")
    void SetPlayerIndex(int32 Index) { PlayerIndex = Index; }

    UFUNCTION(BlueprintPure, Category = "PlayerFighter")
    int32 GetPlayerIndex() const { return PlayerIndex; }

    UFUNCTION(BlueprintPure, Category = "PlayerFighter")
    bool IsLocalPlayer() const { return bIsLocalPlayer; }

    UFUNCTION(BlueprintCallable, Category = "PlayerFighter")
    void SetLocalPlayer(bool bLocal) { bIsLocalPlayer = bLocal; }

    UFUNCTION(BlueprintCallable, Category = "PlayerFighter")
    void ReadyFighter();

    UFUNCTION(BlueprintCallable, Category = "PlayerFighter")
    void UnreadyFighter();

    UFUNCTION(BlueprintPure, Category = "PlayerFighter")
    bool IsReady() const { return bIsReady; }

    UFUNCTION(BlueprintCallable, Category = "PlayerFighter")
    void OnInputDeviceChanged(int32 DeviceID);

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnPlayerFighterReady OnPlayerFighterReady;

    UPROPERTY(BlueprintReadOnly, Category = "PlayerFighter")
    int32 PlayerIndex;

    UPROPERTY(BlueprintReadOnly, Category = "PlayerFighter")
    bool bIsLocalPlayer;

    UPROPERTY(BlueprintReadOnly, Category = "PlayerFighter")
    bool bIsReady;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerFighter")
    TSubclassOf<ALesFightBaseFighter> DefaultFighterClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerFighter")
    FName DefaultFighterID;

private:
    void BindFighterInput();
};
