#include "LesFightPlayerProfileWidget.h"

void ULesFightPlayerProfileWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void ULesFightPlayerProfileWidget::LoadProfile(FName ProfileID)
{
    CurrentProfileID = ProfileID;
    OnProfileLoaded.Broadcast(ProfileID);
}

void ULesFightPlayerProfileWidget::SaveCurrentProfile()
{
    OnProfileSaved.Broadcast(CurrentProfileID);
}

void ULesFightPlayerProfileWidget::CreateNewProfile(FText ProfileName)
{
    FName NewProfileID = FName(*ProfileName.ToString());
    CurrentProfileID = NewProfileID;
    PlayerName = ProfileName;
    PlayerStats.Empty();
    MatchHistory.Empty();
    AchievementProgress.Empty();
    OnProfileCreated.Broadcast(NewProfileID);
    SaveCurrentProfile();
}

void ULesFightPlayerProfileWidget::SetPlayerAvatar(UTexture2D* Avatar)
{
    PlayerAvatar = Avatar;
}

void ULesFightPlayerProfileWidget::SetPlayerName(FText Name)
{
    PlayerName = Name;
}

void ULesFightPlayerProfileWidget::SetPlayerTitle(FText Title)
{
    PlayerTitle = Title;
}

void ULesFightPlayerProfileWidget::AddStat(FText StatName, float Value)
{
    if (PlayerStats.Num() >= 20)
    {
        return;
    }

    FStatEntry Entry;
    Entry.StatName = StatName;
    Entry.Value = Value;
    PlayerStats.Add(Entry);
}

void ULesFightPlayerProfileWidget::UpdateStat(FText StatName, float NewValue)
{
    for (FStatEntry& Entry : PlayerStats)
    {
        if (Entry.StatName.EqualTo(StatName))
        {
            Entry.Value = NewValue;
            return;
        }
    }
}

void ULesFightPlayerProfileWidget::AddMatchHistoryEntry(FText OpponentName, bool bWon, float Duration, int32 RoundCount)
{
    FMatchEntry Entry;
    Entry.OpponentName = OpponentName;
    Entry.bWon = bWon;
    Entry.Duration = Duration;
    Entry.RoundCount = RoundCount;
    MatchHistory.Insert(Entry, 0);

    if (MatchHistory.Num() > 50)
    {
        MatchHistory.SetNum(50);
    }
}

void ULesFightPlayerProfileWidget::ClearMatchHistory()
{
    MatchHistory.Empty();
}

void ULesFightPlayerProfileWidget::SetAchievementProgress(int32 AchievementIndex, float Progress)
{
    if (AchievementIndex >= 0)
    {
        if (AchievementIndex >= AchievementProgress.Num())
        {
            AchievementProgress.SetNum(AchievementIndex + 1);
        }
        AchievementProgress[AchievementIndex] = FMath::Clamp(Progress, 0.0f, 100.0f);
    }
}

void ULesFightPlayerProfileWidget::DisplayProfileSelection(TArray<FName> AvailableProfiles)
{
}

void ULesFightPlayerProfileWidget::NavigateToEdit()
{
}

void ULesFightPlayerProfileWidget::NavigateToSelect()
{
}

void ULesFightPlayerProfileWidget::NavigateBack()
{
    OnNavigateBack.Broadcast();
}
