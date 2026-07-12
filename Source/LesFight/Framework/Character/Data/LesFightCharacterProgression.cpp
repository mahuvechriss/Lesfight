#include "LesFightCharacterProgression.h"
#include "LesFight.h"

ULesFightCharacterProgression::ULesFightCharacterProgression()
    : CurrentLevel(1)
    , CurrentExperience(0.0f)
    , ProgressionMultiplier(1.0f)
{
    PrimaryActorTick.bCanEverTick = false;
}

void ULesFightCharacterProgression::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightCharacterProgression::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULesFightCharacterProgression::Initialize(int32 StartLevel)
{
    CurrentLevel = StartLevel;
    CurrentExperience = 0.0f;

    LevelThresholds = {0.0f, 100.0f, 300.0f, 600.0f, 1000.0f, 1500.0f, 2100.0f, 2800.0f, 3600.0f, 4500.0f};
    for (int32 i = 10; i <= 100; i++)
    {
        LevelThresholds.Add(LevelThresholds[i - 1] + 500.0f + (i * 50.0f));
    }

    UE_LOG(LogLesFight, Log, TEXT("Progression initialized at level %d"), CurrentLevel);
}

void ULesFightCharacterProgression::AddExperience(float Amount)
{
    float AdjustedAmount = Amount * ProgressionMultiplier;
    CurrentExperience += AdjustedAmount;
    OnExperienceGained.Broadcast(AdjustedAmount);
    CheckLevelUp();
}

void ULesFightCharacterProgression::SetLevel(int32 NewLevel)
{
    CurrentLevel = FMath::Max(1, NewLevel);
    CurrentExperience = GetExperienceForLevel(CurrentLevel);
    OnLevelUp.Broadcast(CurrentLevel);
}

float ULesFightCharacterProgression::GetExperienceToNextLevel() const
{
    float CurrentThreshold = GetExperienceForLevel(CurrentLevel);
    float NextThreshold = GetExperienceForLevel(CurrentLevel + 1);
    return NextThreshold - CurrentThreshold;
}

float ULesFightCharacterProgression::GetExperienceProgress() const
{
    float CurrentThreshold = GetExperienceForLevel(CurrentLevel);
    float NextThreshold = GetExperienceForLevel(CurrentLevel + 1);
    float Progress = (CurrentExperience - CurrentThreshold) / (NextThreshold - CurrentThreshold);
    return FMath::Clamp(Progress, 0.0f, 1.0f);
}

void ULesFightCharacterProgression::UnlockAbility(FName AbilityID)
{
    if (!UnlockedAbilities.Contains(AbilityID))
    {
        UnlockedAbilities.Add(AbilityID);
        OnAbilityUnlocked.Broadcast(AbilityID);
        UE_LOG(LogLesFight, Log, TEXT("Ability unlocked: %s"), *AbilityID.ToString());
    }
}

bool ULesFightCharacterProgression::IsAbilityUnlocked(FName AbilityID) const
{
    return UnlockedAbilities.Contains(AbilityID);
}

float ULesFightCharacterProgression::GetExperienceForLevel(int32 Level) const
{
    if (Level <= 0) return 0.0f;
    if (Level <= LevelThresholds.Num())
        return LevelThresholds[Level - 1];
    return LevelThresholds.Last();
}

void ULesFightCharacterProgression::CheckLevelUp()
{
    while (CurrentExperience >= GetExperienceForLevel(CurrentLevel + 1))
    {
        CurrentLevel++;
        OnLevelUp.Broadcast(CurrentLevel);
        UE_LOG(LogLesFight, Log, TEXT("Level up! New level: %d"), CurrentLevel);
    }
}
