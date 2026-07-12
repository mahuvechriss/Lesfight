#include "LesFightCombatHUD.h"
#include "Framework/UI/Data/LesFightUIData.h"

void ULesFightCombatHUD::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    PlayerHealth = PlayerMaxHealth = 100.0f;
    OpponentHealth = OpponentMaxHealth = 100.0f;
    PlayerStamina = PlayerStaminaMax = 100.0f;
    PlayerUltimate = 0.0f;
    PlayerUltimateMax = 100.0f;
    bHUDVisible = true;
    bTimerWarning = false;
    PlayerHealthColor = FLinearColor::Green;
    OpponentHealthColor = FLinearColor::Red;
}

void ULesFightCombatHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    for (int32 i = ActiveStatusEffects.Num() - 1; i >= 0; --i)
    {
        FStatusEffectEntry& Entry = ActiveStatusEffects[i];
        Entry.Timer -= InDeltaTime;
        if (Entry.Timer <= 0.0f)
        {
            ActiveStatusEffects.RemoveAt(i);
        }
    }
}

void ULesFightCombatHUD::SetPlayerHealth(float Current, float Max)
{
    PlayerHealth = FMath::Clamp(Current, 0.0f, Max);
    PlayerMaxHealth = Max;

    float Percent = GetHealthPercent(true);
    if (Percent < 0.25f)
    {
        PlayerHealthColor = FLinearColor::Red;
    }
    else if (Percent < 0.5f)
    {
        PlayerHealthColor = FLinearColor::Yellow;
    }
    else
    {
        PlayerHealthColor = FLinearColor::Green;
    }
}

void ULesFightCombatHUD::SetOpponentHealth(float Current, float Max)
{
    OpponentHealth = FMath::Clamp(Current, 0.0f, Max);
    OpponentMaxHealth = Max;

    float Percent = GetHealthPercent(false);
    if (Percent < 0.25f)
    {
        OpponentHealthColor = FLinearColor::Red;
    }
    else if (Percent < 0.5f)
    {
        OpponentHealthColor = FLinearColor::Yellow;
    }
    else
    {
        OpponentHealthColor = FLinearColor::Green;
    }
}

void ULesFightCombatHUD::SetPlayerStamina(float Current, float Max)
{
    PlayerStamina = FMath::Clamp(Current, 0.0f, Max);
    PlayerStaminaMax = Max;
}

void ULesFightCombatHUD::SetPlayerUltimate(float Current, float Max)
{
    PlayerUltimate = FMath::Clamp(Current, 0.0f, Max);
    PlayerUltimateMax = Max;
}

void ULesFightCombatHUD::SetComboCounter(int32 Count, FText ComboName)
{
    ComboCount = Count;
}

void ULesFightCombatHUD::SetTimer(float SecondsRemaining)
{
    RoundTimeRemaining = SecondsRemaining;
}

void ULesFightCombatHUD::SetRound(int32 Round, int32 TotalRounds)
{
    CurrentRound = Round;
    TotalRounds = TotalRounds;
}

void ULesFightCombatHUD::SetFightingStyle(EFightingStyle Style)
{
    PlayerStyle = Style;
}

void ULesFightCombatHUD::SetOpponentFightingStyle(EFightingStyle Style)
{
    OpponentStyle = Style;
}

void ULesFightCombatHUD::ShowStatusEffect(FText EffectName, float Duration, bool bPositive)
{
    FStatusEffectEntry* Existing = ActiveStatusEffects.FindByPredicate([&](const FStatusEffectEntry& Entry)
    {
        return Entry.EffectName.EqualTo(EffectName);
    });

    if (Existing)
    {
        Existing->Duration = Duration;
        Existing->Timer = Duration;
        Existing->bPositive = bPositive;
    }
    else if (ActiveStatusEffects.Num() < MaxStatusEffects)
    {
        FStatusEffectEntry NewEntry;
        NewEntry.EffectName = EffectName;
        NewEntry.Duration = Duration;
        NewEntry.Timer = Duration;
        NewEntry.bPositive = bPositive;
        ActiveStatusEffects.Add(NewEntry);
    }
}

void ULesFightCombatHUD::RemoveStatusEffect(FText EffectName)
{
    ActiveStatusEffects.RemoveAll([&](const FStatusEffectEntry& Entry)
    {
        return Entry.EffectName.EqualTo(EffectName);
    });
}

void ULesFightCombatHUD::SetRoundResult(FText Result)
{
}

void ULesFightCombatHUD::ShowRoundIntro_Implementation(int32 RoundNumber)
{
}

void ULesFightCombatHUD::ShowKoEffect_Implementation()
{
}

void ULesFightCombatHUD::ShowTimerWarning_Implementation(bool bWarning)
{
    bTimerWarning = bWarning;
}

void ULesFightCombatHUD::SetHUDVisibility(bool bVisible)
{
    bHUDVisible = bVisible;
}

bool ULesFightCombatHUD::IsHUDVisible() const
{
    return bHUDVisible;
}

float ULesFightCombatHUD::GetHealthPercent(bool bPlayer) const
{
    float Max = bPlayer ? PlayerMaxHealth : OpponentMaxHealth;
    float Current = bPlayer ? PlayerHealth : OpponentHealth;
    return Max > 0.0f ? Current / Max : 0.0f;
}

float ULesFightCombatHUD::GetStaminaPercent() const
{
    return PlayerStaminaMax > 0.0f ? PlayerStamina / PlayerStaminaMax : 0.0f;
}

float ULesFightCombatHUD::GetUltimatePercent() const
{
    return PlayerUltimateMax > 0.0f ? PlayerUltimate / PlayerUltimateMax : 0.0f;
}
