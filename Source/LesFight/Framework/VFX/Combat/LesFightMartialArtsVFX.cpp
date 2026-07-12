#include "Framework/VFX/Combat/LesFightMartialArtsVFX.h"
#include "Framework/VFX/Combat/LesFightImpactEffectSystem.h"
#include "Framework/VFX/Core/LesFightVFXWorldManager.h"

ULesFightMartialArtsVFX::ULesFightMartialArtsVFX()
{
}

void ULesFightMartialArtsVFX::Initialize()
{
    CurrentStyle = EFightingStyle::None;
    StyleMode = EVFXStyleMode::Realistic;

    StyleColors.Empty();
    StyleColors.Add(EFightingStyle::Karate, FLinearColor::Red);
    StyleColors.Add(EFightingStyle::MuayThai, FLinearColor(FColor::Orange));
    StyleColors.Add(EFightingStyle::Boxing, FLinearColor::Yellow);
    StyleColors.Add(EFightingStyle::Taekwondo, FLinearColor::Blue);
    StyleColors.Add(EFightingStyle::Judo, FLinearColor::Green);
    StyleColors.Add(EFightingStyle::Wushu, FLinearColor(FColor::Purple));
    StyleColors.Add(EFightingStyle::Kickboxing, FLinearColor::Red);
    StyleColors.Add(EFightingStyle::ShaolinKungFu, FLinearColor(FColor::Yellow));

    StyleImpactOverrides.Empty();

    TMap<EImpactVFXType, FString> KarateOverrides;
    KarateOverrides.Add(EImpactVFXType::LightPunch, TEXT("WindTrail_Sharp"));
    KarateOverrides.Add(EImpactVFXType::HeavyPunch, TEXT("WindTrail_Heavy"));
    KarateOverrides.Add(EImpactVFXType::LightKick, TEXT("WindTrail_Kick"));
    StyleImpactOverrides.Add(EFightingStyle::Karate, KarateOverrides);

    TMap<EImpactVFXType, FString> MuayThaiOverrides;
    MuayThaiOverrides.Add(EImpactVFXType::HeavyPunch, TEXT("Shockwave_Heavy"));
    MuayThaiOverrides.Add(EImpactVFXType::HeavyKick, TEXT("Shockwave_Ring"));
    MuayThaiOverrides.Add(EImpactVFXType::SpecialAttack, TEXT("Shockwave_Elbow"));
    StyleImpactOverrides.Add(EFightingStyle::MuayThai, MuayThaiOverrides);

    TMap<EImpactVFXType, FString> WushuOverrides;
    WushuOverrides.Add(EImpactVFXType::LightPunch, TEXT("EnergyRibbon_Punch"));
    WushuOverrides.Add(EImpactVFXType::LightKick, TEXT("EnergyRibbon_Kick"));
    WushuOverrides.Add(EImpactVFXType::SpecialAttack, TEXT("EnergyRibbon_Flourish"));
    StyleImpactOverrides.Add(EFightingStyle::Wushu, WushuOverrides);
}

void ULesFightMartialArtsVFX::SetStyle(EFightingStyle Style)
{
    CurrentStyle = Style;
}

EFightingStyle ULesFightMartialArtsVFX::GetStyle() const
{
    return CurrentStyle;
}

void ULesFightMartialArtsVFX::PlayStyleImpact(EFightingStyle Style, EImpactVFXType Type, FVector Location)
{
    const TMap<EImpactVFXType, FString>* Overrides = StyleImpactOverrides.Find(Style);
    if (Overrides)
    {
        const FString* OverrideEffect = Overrides->Find(Type);
        if (OverrideEffect)
        {
        }
    }
}

void ULesFightMartialArtsVFX::PlayStyleMotionTrail(EFightingStyle Style, EMotionVFXType Trail, FTransform Transform)
{
}

FLinearColor ULesFightMartialArtsVFX::GetStyleAuraDef(EFightingStyle Style) const
{
    const FLinearColor* Color = StyleColors.Find(Style);
    if (Color)
    {
        return *Color;
    }
    return FLinearColor::White;
}

void ULesFightMartialArtsVFX::SetVFXStyleMode(EVFXStyleMode Mode)
{
    StyleMode = Mode;
}
