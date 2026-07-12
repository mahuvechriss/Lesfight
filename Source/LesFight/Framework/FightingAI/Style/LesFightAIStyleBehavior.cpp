#include "Framework/FightingAI/Style/LesFightAIStyleBehavior.h"

ULesFightAIStyleBehavior::ULesFightAIStyleBehavior()
{
    CurrentStyle = EFightingStyle::None;
    CurrentProfile = FAIStyleBehaviorProfile();

    FAIStyleBehaviorProfile KarateProfile;
    KarateProfile.FightingStyle = EFightingStyle::Karate;
    KarateProfile.AggressionWeight = 0.7f;
    KarateProfile.DefenseWeight = 0.5f;
    KarateProfile.CounterWeight = 0.3f;
    KarateProfile.MovementWeight = 0.4f;
    KarateProfile.ComboFrequency = 0.6f;
    KarateProfile.SpecialMoveFrequency = 0.3f;
    KarateProfile.PreferredRange = 0.7f;
    KarateProfile.PreferredCombos = { FName("KarateCombo1"), FName("KarateCombo2") };
    KarateProfile.FavoriteActions = { EAIActionType::HeavyAttack, EAIActionType::ComboAttack };
    KarateProfile.Reactivity = 0.5f;
    KarateProfile.RiskTolerance = 0.6f;
    StyleProfiles.Add(EFightingStyle::Karate, KarateProfile);

    FAIStyleBehaviorProfile MuayThaiProfile;
    MuayThaiProfile.FightingStyle = EFightingStyle::MuayThai;
    MuayThaiProfile.AggressionWeight = 0.8f;
    MuayThaiProfile.DefenseWeight = 0.4f;
    MuayThaiProfile.CounterWeight = 0.2f;
    MuayThaiProfile.MovementWeight = 0.3f;
    MuayThaiProfile.ComboFrequency = 0.5f;
    MuayThaiProfile.SpecialMoveFrequency = 0.4f;
    MuayThaiProfile.PreferredRange = 0.6f;
    MuayThaiProfile.PreferredCombos = { FName("MuayThaiCombo1"), FName("MuayThaiCombo2") };
    MuayThaiProfile.FavoriteActions = { EAIActionType::HeavyAttack, EAIActionType::Grab };
    MuayThaiProfile.Reactivity = 0.4f;
    MuayThaiProfile.RiskTolerance = 0.7f;
    StyleProfiles.Add(EFightingStyle::MuayThai, MuayThaiProfile);

    FAIStyleBehaviorProfile BoxingProfile;
    BoxingProfile.FightingStyle = EFightingStyle::Boxing;
    BoxingProfile.AggressionWeight = 0.6f;
    BoxingProfile.DefenseWeight = 0.6f;
    BoxingProfile.CounterWeight = 0.4f;
    BoxingProfile.MovementWeight = 0.7f;
    BoxingProfile.ComboFrequency = 0.7f;
    BoxingProfile.SpecialMoveFrequency = 0.2f;
    BoxingProfile.PreferredRange = 0.8f;
    BoxingProfile.PreferredCombos = { FName("BoxingCombo1"), FName("BoxingCombo2") };
    BoxingProfile.FavoriteActions = { EAIActionType::LightAttack, EAIActionType::Dodge };
    BoxingProfile.Reactivity = 0.7f;
    BoxingProfile.RiskTolerance = 0.5f;
    StyleProfiles.Add(EFightingStyle::Boxing, BoxingProfile);

    FAIStyleBehaviorProfile TaekwondoProfile;
    TaekwondoProfile.FightingStyle = EFightingStyle::Taekwondo;
    TaekwondoProfile.AggressionWeight = 0.5f;
    TaekwondoProfile.DefenseWeight = 0.5f;
    TaekwondoProfile.CounterWeight = 0.6f;
    TaekwondoProfile.MovementWeight = 0.8f;
    TaekwondoProfile.ComboFrequency = 0.6f;
    TaekwondoProfile.SpecialMoveFrequency = 0.3f;
    TaekwondoProfile.PreferredRange = 0.5f;
    TaekwondoProfile.PreferredCombos = { FName("TaekwondoCombo1"), FName("TaekwondoCombo2") };
    TaekwondoProfile.FavoriteActions = { EAIActionType::ComboAttack, EAIActionType::Sidestep };
    TaekwondoProfile.Reactivity = 0.6f;
    TaekwondoProfile.RiskTolerance = 0.5f;
    StyleProfiles.Add(EFightingStyle::Taekwondo, TaekwondoProfile);

    FAIStyleBehaviorProfile JudoProfile;
    JudoProfile.FightingStyle = EFightingStyle::Judo;
    JudoProfile.AggressionWeight = 0.3f;
    JudoProfile.DefenseWeight = 0.7f;
    JudoProfile.CounterWeight = 0.5f;
    JudoProfile.MovementWeight = 0.5f;
    JudoProfile.ComboFrequency = 0.3f;
    JudoProfile.SpecialMoveFrequency = 0.2f;
    JudoProfile.PreferredRange = 0.2f;
    JudoProfile.PreferredCombos = { FName("JudoCombo1") };
    JudoProfile.FavoriteActions = { EAIActionType::Counter, EAIActionType::Grab };
    JudoProfile.Reactivity = 0.8f;
    JudoProfile.RiskTolerance = 0.3f;
    StyleProfiles.Add(EFightingStyle::Judo, JudoProfile);

    FAIStyleBehaviorProfile WushuProfile;
    WushuProfile.FightingStyle = EFightingStyle::Wushu;
    WushuProfile.AggressionWeight = 0.6f;
    WushuProfile.DefenseWeight = 0.5f;
    WushuProfile.CounterWeight = 0.5f;
    WushuProfile.MovementWeight = 0.9f;
    WushuProfile.ComboFrequency = 0.7f;
    WushuProfile.SpecialMoveFrequency = 0.5f;
    WushuProfile.PreferredRange = 0.4f;
    WushuProfile.PreferredCombos = { FName("WushuCombo1"), FName("WushuCombo2") };
    WushuProfile.FavoriteActions = { EAIActionType::ComboAttack, EAIActionType::Jump };
    WushuProfile.Reactivity = 0.6f;
    WushuProfile.RiskTolerance = 0.6f;
    StyleProfiles.Add(EFightingStyle::Wushu, WushuProfile);

    FAIStyleBehaviorProfile KickboxingProfile;
    KickboxingProfile.FightingStyle = EFightingStyle::Kickboxing;
    KickboxingProfile.AggressionWeight = 0.65f;
    KickboxingProfile.DefenseWeight = 0.45f;
    KickboxingProfile.CounterWeight = 0.35f;
    KickboxingProfile.MovementWeight = 0.6f;
    KickboxingProfile.ComboFrequency = 0.6f;
    KickboxingProfile.SpecialMoveFrequency = 0.35f;
    KickboxingProfile.PreferredRange = 0.65f;
    KickboxingProfile.PreferredCombos = { FName("KickboxingCombo1"), FName("KickboxingCombo2") };
    KickboxingProfile.FavoriteActions = { EAIActionType::LightAttack, EAIActionType::HeavyAttack };
    KickboxingProfile.Reactivity = 0.5f;
    KickboxingProfile.RiskTolerance = 0.55f;
    StyleProfiles.Add(EFightingStyle::Kickboxing, KickboxingProfile);

    FAIStyleBehaviorProfile ShaolinProfile;
    ShaolinProfile.FightingStyle = EFightingStyle::ShaolinKungFu;
    ShaolinProfile.AggressionWeight = 0.55f;
    ShaolinProfile.DefenseWeight = 0.55f;
    ShaolinProfile.CounterWeight = 0.45f;
    ShaolinProfile.MovementWeight = 0.75f;
    ShaolinProfile.ComboFrequency = 0.65f;
    ShaolinProfile.SpecialMoveFrequency = 0.45f;
    ShaolinProfile.PreferredRange = 0.5f;
    ShaolinProfile.PreferredCombos = { FName("ShaolinCombo1"), FName("ShaolinCombo2") };
    ShaolinProfile.FavoriteActions = { EAIActionType::ComboAttack, EAIActionType::SpecialMove };
    ShaolinProfile.Reactivity = 0.6f;
    ShaolinProfile.RiskTolerance = 0.5f;
    StyleProfiles.Add(EFightingStyle::ShaolinKungFu, ShaolinProfile);

    StyleDescriptions = {
        TEXT("A disciplined close-range style focused on powerful strikes and relentless pressure."),
        TEXT("An aggressive style utilizing devastating elbows, knees, and clinch techniques."),
        TEXT("A balanced style emphasizing footwork, precise punches, and defensive maneuvers."),
        TEXT("A dynamic kicking style with fast, flashy attacks and excellent reach management."),
        TEXT("A defensive, counter-focused style built on throws, trips, and grappling control."),
        TEXT("An acrobatic style combining fluid movement with unpredictable attack patterns."),
        TEXT("A hybrid style mixing powerful punches and kicks with aggressive forward pressure."),
        TEXT("A versatile martial art blending speed, technique, and spiritual discipline.")
    };
}

void ULesFightAIStyleBehavior::SetStyle(EFightingStyle Style)
{
    if (StyleProfiles.Contains(Style))
    {
        CurrentStyle = Style;
        CurrentProfile = StyleProfiles[Style];
    }
}

void ULesFightAIStyleBehavior::ModifyAggression(float Delta)
{
    CurrentProfile.AggressionWeight = FMath::Clamp(CurrentProfile.AggressionWeight + Delta, 0.0f, 1.0f);
}

void ULesFightAIStyleBehavior::ModifyDefense(float Delta)
{
    CurrentProfile.DefenseWeight = FMath::Clamp(CurrentProfile.DefenseWeight + Delta, 0.0f, 1.0f);
}

FAIStyleBehaviorProfile ULesFightAIStyleBehavior::GetBehaviorForSituation(const FAIPerceptionData& Perception) const
{
    FAIStyleBehaviorProfile AdjustedProfile = CurrentProfile;

    float HealthRatio = Perception.PlayerHealthPercent;
    float StaminaRatio = Perception.PlayerStaminaPercent;

    if (HealthRatio < 0.3f)
    {
        AdjustedProfile.DefenseWeight = FMath::Min(AdjustedProfile.DefenseWeight + 0.2f, 1.0f);
        AdjustedProfile.AggressionWeight = FMath::Max(AdjustedProfile.AggressionWeight - 0.15f, 0.0f);
        AdjustedProfile.RiskTolerance = FMath::Max(AdjustedProfile.RiskTolerance - 0.2f, 0.0f);
    }

    if (StaminaRatio < 0.25f)
    {
        AdjustedProfile.AggressionWeight = FMath::Max(AdjustedProfile.AggressionWeight - 0.2f, 0.0f);
        AdjustedProfile.ComboFrequency = FMath::Max(AdjustedProfile.ComboFrequency - 0.2f, 0.0f);
        AdjustedProfile.MovementWeight = FMath::Max(AdjustedProfile.MovementWeight - 0.1f, 0.0f);
    }
    else if (StaminaRatio > 0.75f)
    {
        AdjustedProfile.AggressionWeight = FMath::Min(AdjustedProfile.AggressionWeight + 0.1f, 1.0f);
    }

    if (Perception.bPlayerIsVulnerable)
    {
        AdjustedProfile.AggressionWeight = FMath::Min(AdjustedProfile.AggressionWeight + 0.25f, 1.0f);
        AdjustedProfile.RiskTolerance = FMath::Min(AdjustedProfile.RiskTolerance + 0.2f, 1.0f);
    }

    if (Perception.bNearArenaEdge && Perception.DistanceToArenaEdge < 100.0f)
    {
        AdjustedProfile.DefenseWeight = FMath::Min(AdjustedProfile.DefenseWeight + 0.15f, 1.0f);
        AdjustedProfile.PreferredRange = FMath::Max(AdjustedProfile.PreferredRange - 0.2f, 0.0f);
    }

    return AdjustedProfile;
}

FName ULesFightAIStyleBehavior::GetPreferredCombo() const
{
    if (CurrentProfile.PreferredCombos.Num() > 0)
    {
        return CurrentProfile.PreferredCombos[0];
    }
    return NAME_None;
}

FString ULesFightAIStyleBehavior::GetStyleDescription() const
{
    int32 Index = static_cast<int32>(CurrentStyle);
    if (Index >= 0 && Index < StyleDescriptions.Num())
    {
        return StyleDescriptions[Index];
    }
    return TEXT("Unknown fighting style.");
}
