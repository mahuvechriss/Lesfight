#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LesFightHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHUDVisibilityChanged, bool, bIsVisible);

UCLASS()
class ULesFightHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "LesFight|HUD")
    void Show();

    UFUNCTION(BlueprintCallable, Category = "LesFight|HUD")
    void Hide();

    UFUNCTION(BlueprintPure, Category = "LesFight|HUD")
    bool IsVisible() const { return bIsHUDVisible; }

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnHealthUpdated(float CurrentHealth, float MaxHealth);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnRoundsUpdated(int32 CurrentRound, int32 MaxRounds);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnTimerUpdated(float TimeRemaining);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnComboUpdated(int32 ComboCount);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnSuperMeterUpdated(float CurrentMeter, float MaxMeter);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnMatchResult(const FString& WinnerName, bool bIsVictory);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnDamageIndicator(float Damage, FVector Direction);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnRoundAnnouncement(int32 RoundNumber);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnKOAnnouncement(const FString& LoserName);

    UFUNCTION(BlueprintImplementableEvent, Category = "LesFight|HUD")
    void OnCharacterSelectUpdated(int32 PlayerIndex, const FString& CharacterName);

    UFUNCTION(BlueprintPure, Category = "LesFight|HUD")
    bool IsHUDVisible() const { return bIsHUDVisible; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "LesFight|HUD")
    bool bIsHUDVisible;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnHUDVisibilityChanged OnHUDVisibilityChanged;

    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
};
