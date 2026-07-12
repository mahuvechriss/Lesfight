#include "LesFightCombatAIHooks.h"
#include "LesFightMartialArtsManager.h"
#include "GameFramework/Actor.h"

ULesFightCombatAIHooks::ULesFightCombatAIHooks()
{
}

void ULesFightCombatAIHooks::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    ResetToDefaults();
}

void ULesFightCombatAIHooks::Tick(float DeltaTime)
{
}

void ULesFightCombatAIHooks::SetAIProfile(const FCombatAIHooks& Profile)
{
    CurrentProfile = Profile;
}

FAICombatDecisionContext ULesFightCombatAIHooks::CreateDecisionContext(
    AActor* Self, AActor* Target)
{
    FAICombatDecisionContext Context;
    Context.Self = Self;
    Context.Target = Target;
    Context.AIProfile = CurrentProfile;

    if (Self && Target)
    {
        Context.DistanceToTarget = Self->GetDistanceTo(Target);
    }

    return Context;
}

void ULesFightCombatAIHooks::SetPreferredDistance(EPreferredDistance Distance)
{
    CurrentProfile.PreferredDistance = Distance;
}

void ULesFightCombatAIHooks::SetAggressionLevel(EAggressionLevel Level)
{
    CurrentProfile.AggressionLevel = Level;
    switch (Level)
    {
    case EAggressionLevel::Passive:
        CurrentProfile.CounterProbability = 0.8f;
        CurrentProfile.ComboLengthPreference = 1.0f;
        break;
    case EAggressionLevel::Defensive:
        CurrentProfile.CounterProbability = 0.6f;
        CurrentProfile.ComboLengthPreference = 2.0f;
        break;
    case EAggressionLevel::Balanced:
        CurrentProfile.CounterProbability = 0.4f;
        CurrentProfile.ComboLengthPreference = 3.0f;
        break;
    case EAggressionLevel::Aggressive:
        CurrentProfile.CounterProbability = 0.2f;
        CurrentProfile.ComboLengthPreference = 4.0f;
        break;
    case EAggressionLevel::Relentless:
        CurrentProfile.CounterProbability = 0.1f;
        CurrentProfile.ComboLengthPreference = 5.0f;
        break;
    }
}

void ULesFightCombatAIHooks::SetCounterProbability(float Probability)
{
    CurrentProfile.CounterProbability = FMath::Clamp(Probability, 0.0f, 1.0f);
}

void ULesFightCombatAIHooks::SetDodgeProbability(float Probability)
{
    CurrentProfile.DodgeProbability = FMath::Clamp(Probability, 0.0f, 1.0f);
}

void ULesFightCombatAIHooks::ResetToDefaults()
{
    CurrentProfile = FCombatAIHooks();
}
