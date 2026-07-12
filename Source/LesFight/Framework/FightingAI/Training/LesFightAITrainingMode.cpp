#include "LesFightAITrainingMode.h"
#include "Framework/FightingAI/LesFightAIFighterController.h"

void ULesFightAITrainingMode::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;
    CurrentMode = EAITrainingMode::FullPractice;
    TrainingIntensity = 0.5f;
    bTrainingEnabled = false;

    BuildAllowedActions();
    BuildModeDescriptions();
}

void ULesFightAITrainingMode::BuildAllowedActions()
{
    AllowedActions.Empty();

    AllowedActions.Add(EAITrainingMode::Passive, TArray<EAIActionType>());

    AllowedActions.Add(EAITrainingMode::BlockingPractice, {
        EAIActionType::Block,
        EAIActionType::Parry
    });

    AllowedActions.Add(EAITrainingMode::ComboPractice, {
        EAIActionType::MeleeAttack,
        EAIActionType::LightAttack,
        EAIActionType::HeavyAttack,
        EAIActionType::SpecialAttack,
        EAIActionType::Combo
    });

    AllowedActions.Add(EAITrainingMode::CounterPractice, {
        EAIActionType::CounterAttack,
        EAIActionType::Parry,
        EAIActionType::Block
    });

    AllowedActions.Add(EAITrainingMode::DodgePractice, {
        EAIActionType::Dodge,
        EAIActionType::StepDash
    });

    AllowedActions.Add(EAITrainingMode::FullPractice, {
        EAIActionType::MeleeAttack,
        EAIActionType::LightAttack,
        EAIActionType::HeavyAttack,
        EAIActionType::SpecialAttack,
        EAIActionType::Combo,
        EAIActionType::Block,
        EAIActionType::Parry,
        EAIActionType::Dodge,
        EAIActionType::StepDash,
        EAIActionType::CounterAttack
    });
}

void ULesFightAITrainingMode::BuildModeDescriptions()
{
    ModeDescriptions.Empty();

    ModeDescriptions.Add(EAITrainingMode::Passive, TEXT("Passive - AI will not attack, only move defensively"));
    ModeDescriptions.Add(EAITrainingMode::BlockingPractice, TEXT("Blocking Practice - AI will only block and parry"));
    ModeDescriptions.Add(EAITrainingMode::ComboPractice, TEXT("Combo Practice - AI performs full offense with pauses between combos"));
    ModeDescriptions.Add(EAITrainingMode::CounterPractice, TEXT("Counter Practice - AI only uses counter attacks"));
    ModeDescriptions.Add(EAITrainingMode::DodgePractice, TEXT("Dodge Practice - AI only dodges and dashes"));
    ModeDescriptions.Add(EAITrainingMode::FullPractice, TEXT("Full Practice - AI uses all available actions"));
}

void ULesFightAITrainingMode::SetTrainingMode(EAITrainingMode Mode)
{
    CurrentMode = Mode;

    if (OwnerController.IsValid() && bTrainingEnabled)
    {
        OwnerController->RestrictActions(AllowedActions[Mode]);
    }
}

EAITrainingMode ULesFightAITrainingMode::GetTrainingMode() const
{
    return CurrentMode;
}

void ULesFightAITrainingMode::SetTrainingIntensity(float Intensity)
{
    TrainingIntensity = FMath::Clamp(Intensity, 0.0f, 1.0f);

    if (OwnerController.IsValid())
    {
        OwnerController->SetAggressionLevel(TrainingIntensity);
    }
}

void ULesFightAITrainingMode::EnableTraining(bool bEnabled)
{
    bTrainingEnabled = bEnabled;

    if (OwnerController.IsValid())
    {
        if (bEnabled)
        {
            OwnerController->RestrictActions(AllowedActions[CurrentMode]);
            OwnerController->SetAggressionLevel(TrainingIntensity);
        }
        else
        {
            OwnerController->ClearActionRestrictions();
            OwnerController->SetAggressionLevel(1.0f);
        }
    }
}

bool ULesFightAITrainingMode::IsTrainingEnabled() const
{
    return bTrainingEnabled;
}

FString ULesFightAITrainingMode::GetTrainingDescription() const
{
    if (const FString* Desc = ModeDescriptions.Find(CurrentMode))
    {
        return *Desc;
    }

    return TEXT("Unknown training mode");
}

void ULesFightAITrainingMode::SetPassiveBehavior()
{
    SetTrainingMode(EAITrainingMode::Passive);
}

void ULesFightAITrainingMode::SetBlockingOnly()
{
    SetTrainingMode(EAITrainingMode::BlockingPractice);
}

void ULesFightAITrainingMode::SetComboPractice()
{
    SetTrainingMode(EAITrainingMode::ComboPractice);
}

void ULesFightAITrainingMode::SetCounterPractice()
{
    SetTrainingMode(EAITrainingMode::CounterPractice);
}

void ULesFightAITrainingMode::SetDodgePractice()
{
    SetTrainingMode(EAITrainingMode::DodgePractice);
}

void ULesFightAITrainingMode::ResetTrainingSettings()
{
    CurrentMode = EAITrainingMode::FullPractice;
    TrainingIntensity = 0.5f;
    bTrainingEnabled = false;

    if (OwnerController.IsValid())
    {
        OwnerController->ClearActionRestrictions();
        OwnerController->SetAggressionLevel(1.0f);
    }
}
