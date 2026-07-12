#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LesFightCombatHUD.generated.h"

UENUM(BlueprintType)
enum class EFightingStyle : uint8
{
    Balanced,
    Aggressive,
    Defensive,
    Technical,
    Rushdown
};

USTRUCT(BlueprintType)
struct FStatusEffectEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "StatusEffect")
    FText EffectName;

    UPROPERTY(BlueprintReadOnly, Category = "StatusEffect")
    float Duration = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "StatusEffect")
    float Timer = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "StatusEffect")
    bool bPositive = true;
};

DECLARE_MULTICAST_DELEGATE(FOnMatchPaused)
DECLARE_MULTICAST_DELEGATE(FOnMatchQuit)

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCombatHUD : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetPlayerHealth(float Current, float Max);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetOpponentHealth(float Current, float Max);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetPlayerStamina(float Current, float Max);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetPlayerUltimate(float Current, float Max);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetComboCounter(int32 Count, FText ComboName);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetTimer(float SecondsRemaining);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetRound(int32 Round, int32 TotalRounds);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetFightingStyle(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetOpponentFightingStyle(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void ShowStatusEffect(FText EffectName, float Duration, bool bPositive);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void RemoveStatusEffect(FText EffectName);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetRoundResult(FText Result);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatHUD")
    void ShowRoundIntro(int32 RoundNumber);
    virtual void ShowRoundIntro_Implementation(int32 RoundNumber);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatHUD")
    void ShowKoEffect();
    virtual void ShowKoEffect_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CombatHUD")
    void ShowTimerWarning(bool bWarning);
    virtual void ShowTimerWarning_Implementation(bool bWarning);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    void SetHUDVisibility(bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    bool IsHUDVisible() const;

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    float GetHealthPercent(bool bPlayer) const;

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    float GetStaminaPercent() const;

    UFUNCTION(BlueprintCallable, Category = "CombatHUD")
    float GetUltimatePercent() const;

    FOnMatchPaused OnMatchPaused;
    FOnMatchQuit OnMatchQuit;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float PlayerHealth = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float PlayerMaxHealth = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float OpponentHealth = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float OpponentMaxHealth = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float PlayerStamina = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float PlayerStaminaMax = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float PlayerUltimate = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float PlayerUltimateMax = 100.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    int32 ComboCount = 0;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float MatchTimer = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    float RoundTimeRemaining = 99.0f;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    int32 CurrentRound = 1;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    int32 TotalRounds = 3;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    EFightingStyle PlayerStyle = EFightingStyle::Balanced;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    EFightingStyle OpponentStyle = EFightingStyle::Balanced;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    TArray<FStatusEffectEntry> ActiveStatusEffects;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    bool bHUDVisible = true;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    bool bTimerWarning = false;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    FLinearColor PlayerHealthColor = FLinearColor::Green;

    UPROPERTY(BlueprintReadOnly, Category = "CombatHUD")
    FLinearColor OpponentHealthColor = FLinearColor::Red;

    static constexpr int32 MaxStatusEffects = 10;
};
