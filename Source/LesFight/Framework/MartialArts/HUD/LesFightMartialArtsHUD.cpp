#include "LesFightMartialArtsHUD.h"
#include "LesFightMartialArtsManager.h"

ULesFightMartialArtsHUD::ULesFightMartialArtsHUD()
    : CurrentDisplayedStyle(EFightingStyle::None)
    , CurrentDisplayedStance(ECombatStance::Neutral)
    , CurrentComboCount(0)
    , CurrentUltimateMeter(0.0f)
    , MaxUltimateMeter(100.0f)
    , NotificationDisplayTime(2.0f)
    , ComboDisplayTimer(0.0f)
{
}

void ULesFightMartialArtsHUD::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
}

void ULesFightMartialArtsHUD::Tick(float DeltaTime)
{
    if (ComboDisplayTimer > 0.0f)
    {
        ComboDisplayTimer -= DeltaTime;
        if (ComboDisplayTimer <= 0.0f)
        {
            UpdateComboCounter(0);
        }
    }

    TArray<FName> ExpiredNotifications;
    for (auto& Pair : NotificationTimers)
    {
        Pair.Value -= DeltaTime;
        if (Pair.Value <= 0.0f)
        {
            ExpiredNotifications.Add(Pair.Key);
        }
    }
    for (FName Key : ExpiredNotifications)
    {
        NotificationTimers.Remove(Key);
    }
}

void ULesFightMartialArtsHUD::UpdateStyleDisplay(EFightingStyle Style)
{
    CurrentDisplayedStyle = Style;
    OnStyleDisplayChanged.Broadcast(Style);
}

void ULesFightMartialArtsHUD::UpdateStanceDisplay(ECombatStance Stance)
{
    CurrentDisplayedStance = Stance;
    OnStanceDisplayChanged.Broadcast(Stance);
}

void ULesFightMartialArtsHUD::UpdateComboCounter(int32 ComboCount)
{
    CurrentComboCount = ComboCount;
    if (ComboCount > 0)
    {
        ComboDisplayTimer = NotificationDisplayTime;
    }

    FText ComboText = FText::AsNumber(ComboCount);
    BroadcastElementUpdate(FName(TEXT("ComboCounter")), ComboText);
}

void ULesFightMartialArtsHUD::ShowCounterNotification(ECounterType CounterType)
{
    FText NotificationText = FText::FromString(UEnum::GetValueAsString(TEXT("ECounterType"), static_cast<int32>(CounterType)));
    BroadcastElementUpdate(FName(TEXT("CounterNotification")), NotificationText);
}

void ULesFightMartialArtsHUD::UpdateUltimateMeter(float CurrentMeter, float MaxMeter)
{
    CurrentUltimateMeter = CurrentMeter;
    MaxUltimateMeter = MaxMeter;
}

void ULesFightMartialArtsHUD::ShowSpecialTechniqueIndicator(
    FName TechniqueName, float Cooldown)
{
    TechniqueCooldowns.Add(TechniqueName, Cooldown);
}

void ULesFightMartialArtsHUD::ShowEnvironmentalInteractionPrompt(
    EEnvironmentInteraction InteractionType)
{
}

void ULesFightMartialArtsHUD::ShowCinematicOverlay(
    ECinematicEffect EffectType, bool bShow)
{
}

void ULesFightMartialArtsHUD::ShowSlowMotionIndicator(bool bActive)
{
}

void ULesFightMartialArtsHUD::UpdateHitNotification(float Damage, bool bWasCounter)
{
    BroadcastElementUpdate(FName(TEXT("HitNotification")),
        FText::FromString(FString::Printf(TEXT("%.0f"), Damage)));
}

void ULesFightMartialArtsHUD::UpdateStanceModifiers(
    const FStanceAttributes& Attributes)
{
}

void ULesFightMartialArtsHUD::ClearAllNotifications()
{
    NotificationTimers.Empty();
    UpdateComboCounter(0);
}

void ULesFightMartialArtsHUD::Reset()
{
    CurrentDisplayedStyle = EFightingStyle::None;
    CurrentDisplayedStance = ECombatStance::Neutral;
    CurrentComboCount = 0;
    CurrentUltimateMeter = 0.0f;
    TechniqueCooldowns.Empty();
    NotificationTimers.Empty();
    ComboDisplayTimer = 0.0f;
}

void ULesFightMartialArtsHUD::BroadcastElementUpdate(FName ElementName, FText Value)
{
    OnHUDElementUpdated.Broadcast(ElementName, Value);
}
