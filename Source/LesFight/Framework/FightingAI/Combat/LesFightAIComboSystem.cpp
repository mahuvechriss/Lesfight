#include "LesFightAIComboSystem.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"
#include "Math/UnrealMathUtility.h"

void ULesFightAIComboSystem::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;
    MaxComboLength = 6;
    CurrentIndex = 0;
    BuildComboDatabase();
}

void ULesFightAIComboSystem::BuildComboDatabase()
{
    ComboList.Empty();
    ComboDatabase.Empty();

    ComboList.Add("JabCross");
    ComboDatabase.Add("JabCross", { EAIActionType::LightAttack, EAIActionType::LightAttack });

    ComboList.Add("JabCrossHook");
    ComboDatabase.Add("JabCrossHook", { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack });

    ComboList.Add("JabCrossUppercut");
    ComboDatabase.Add("JabCrossUppercut", { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack });

    ComboList.Add("BodyBlow");
    ComboDatabase.Add("BodyBlow", { EAIActionType::LightAttack, EAIActionType::HeavyAttack });

    ComboList.Add("KickCombo");
    ComboDatabase.Add("KickCombo", { EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::HeavyAttack });

    ComboList.Add("ElbowKneePunch");
    ComboDatabase.Add("ElbowKneePunch", { EAIActionType::HeavyAttack, EAIActionType::HeavyAttack, EAIActionType::LightAttack });

    ComboList.Add("PunchPunchKick");
    ComboDatabase.Add("PunchPunchKick", { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack });

    ComboList.Add("JabJabCrossHook");
    ComboDatabase.Add("JabJabCrossHook", { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack });

    ComboList.Add("ThreeHitSpecial");
    ComboDatabase.Add("ThreeHitSpecial", { EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::SpecialMove });

    ComboList.Add("FullCombo");
    ComboDatabase.Add("FullCombo", { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::ComboAttack, EAIActionType::SpecialMove });

    ComboList.Add("GrapplerCombo");
    ComboDatabase.Add("GrapplerCombo", { EAIActionType::LightAttack, EAIActionType::Grab, EAIActionType::HeavyAttack });

    ComboList.Add("AgileStrike");
    ComboDatabase.Add("AgileStrike", { EAIActionType::LightAttack, EAIActionType::Dodge, EAIActionType::LightAttack, EAIActionType::HeavyAttack });
}

void ULesFightAIComboSystem::StartCombo(FName ComboName, const FAIStyleBehaviorProfile& Style)
{
    if (const TArray<EAIActionType>* Found = ComboDatabase.Find(ComboName))
    {
        if (Found->Num() <= MaxComboLength && Found->Num() > 0)
        {
            CurrentCombo = *Found;
            CurrentIndex = 0;
            ComboList.AddUnique(ComboName);
        }
    }
}

void ULesFightAIComboSystem::ExecuteNextAction(FAIDecisionContext& Context)
{
    if (IsComboComplete() || CurrentCombo.IsEmpty())
    {
        Context.ChosenAction = EAIActionType::Wait;
        Context.ActionScore = 0.0f;
        return;
    }

    Context.ChosenAction = CurrentCombo[CurrentIndex];
    Context.ActionScore = 1.0f;
    Context.Priority = EAIDecisionPriority::High;
    CurrentIndex++;
}

bool ULesFightAIComboSystem::IsComboComplete() const
{
    return CurrentIndex >= CurrentCombo.Num();
}

int32 ULesFightAIComboSystem::GetRemainingComboLength() const
{
    return FMath::Max(0, CurrentCombo.Num() - CurrentIndex);
}

void ULesFightAIComboSystem::CancelCombo()
{
    CurrentCombo.Empty();
    CurrentIndex = 0;
}

void ULesFightAIComboSystem::GenerateComboFromStyle(const FAIStyleBehaviorProfile& Style)
{
    CurrentCombo.Empty();
    CurrentIndex = 0;

    switch (Style.FightingStyle)
    {
    case EFightingStyle::Karate:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack };
        break;
    case EFightingStyle::MuayThai:
        CurrentCombo = { EAIActionType::HeavyAttack, EAIActionType::HeavyAttack, EAIActionType::LightAttack };
        break;
    case EFightingStyle::Boxing:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack };
        break;
    case EFightingStyle::Taekwondo:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::HeavyAttack };
        break;
    case EFightingStyle::ShaolinKungFu:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::SpecialMove };
        break;
    case EFightingStyle::WingChun:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::LightAttack };
        break;
    case EFightingStyle::JeetKuneDo:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack };
        break;
    case EFightingStyle::Judo:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::Grab, EAIActionType::HeavyAttack };
        break;
    case EFightingStyle::BrazilianJiuJitsu:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::Grab, EAIActionType::Grab };
        break;
    case EFightingStyle::Kickboxing:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::LightAttack, EAIActionType::HeavyAttack, EAIActionType::HeavyAttack };
        break;
    default:
        CurrentCombo = { EAIActionType::LightAttack, EAIActionType::HeavyAttack };
        break;
    }

    if (CurrentCombo.Num() > MaxComboLength)
    {
        CurrentCombo.SetNum(MaxComboLength);
    }
}

bool ULesFightAIComboSystem::HasComboOfLength(int32 MinLength, int32 MaxLength) const
{
    for (const auto& Elem : ComboDatabase)
    {
        const int32 Len = Elem.Value.Num();
        if (Len >= MinLength && Len <= MaxLength)
            return true;
    }
    return false;
}
