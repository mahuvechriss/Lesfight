#include "LesFightMatchResultWidget.h"
#include "Framework/UI/Data/LesFightUIData.h"

void ULesFightMatchResultWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    PerformanceRating = 0.0f;
}

void ULesFightMatchResultWidget::SetWinnerInfo(FText Name, UTexture2D* Portrait, FText Title)
{
    WinnerName = Name;
    WinnerPortrait = Portrait;
    WinnerTitle = Title;
}

void ULesFightMatchResultWidget::SetLoserInfo(FText Name, UTexture2D* Portrait, FText Title)
{
    LoserName = Name;
    LoserPortrait = Portrait;
    LoserTitle = Title;
}

void ULesFightMatchResultWidget::SetMatchDuration(float Seconds)
{
    MatchDuration = Seconds;
}

void ULesFightMatchResultWidget::SetComboStats(int32 MaxCombo, int32 TotalCombos, float ComboAccuracy)
{
    MaxCombo = MaxCombo;
    TotalCombos = TotalCombos;
    ComboAccuracy = ComboAccuracy;
}

void ULesFightMatchResultWidget::SetDamageStats(float TotalDamage, float DamagePerSecond, int32 HitsLanded, int32 HitsReceived)
{
    TotalDamage = TotalDamage;
    DamagePerSecond = DamagePerSecond;
    HitsLanded = HitsLanded;
    HitsReceived = HitsReceived;
}

void ULesFightMatchResultWidget::SetPerformanceRating(float Rating)
{
    PerformanceRating = FMath::Clamp(Rating, 0.0f, 100.0f);
}

void ULesFightMatchResultWidget::SetRewards(int32 XP, int32 Currency, TArray<FText> UnlockedItems)
{
    RewardXP = XP;
    RewardCurrency = Currency;
    UnlockedItems = UnlockedItems;
}

void ULesFightMatchResultWidget::PlayVictoryAnimation_Implementation()
{
}

void ULesFightMatchResultWidget::PlayDefeatAnimation_Implementation()
{
}

void ULesFightMatchResultWidget::RequestRematch()
{
    OnRematchRequested.Broadcast();
}

void ULesFightMatchResultWidget::ReturnToMainMenu()
{
    OnReturnToMainMenu.Broadcast();
}

void ULesFightMatchResultWidget::ReturnToCharacterSelect()
{
    OnReturnToCharacterSelect.Broadcast();
}
