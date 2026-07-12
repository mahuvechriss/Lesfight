#include "LesFightCombatSoundSystem.h"
#include "LesFightSoundEffectManager.h"
#include "Framework/Audio/Data/LesFightAudioData.h"

ULesFightCombatSoundSystem::ULesFightCombatSoundSystem()
{
    CurrentStyle = EFightingStyle::Karate;

    TMap<ECombatSoundType, FString> KarateOverrides;
    KarateOverrides.Emplace(ECombatSoundType::LightPunch, "/Game/Audio/Styles/Karate/LightPunch");
    KarateOverrides.Emplace(ECombatSoundType::HeavyPunch, "/Game/Audio/Styles/Karate/HeavyPunch");
    KarateOverrides.Emplace(ECombatSoundType::LightKick, "/Game/Audio/Styles/Karate/LightKick");
    KarateOverrides.Emplace(ECombatSoundType::CounterImpact, "/Game/Audio/Styles/Karate/CounterSnap");
    StyleSoundOverrides.Emplace(EFightingStyle::Karate, KarateOverrides);
    StyleAudioDescriptions.Emplace(EFightingStyle::Karate, "Sharp snaps and traditional strikes");

    TMap<ECombatSoundType, FString> MuayThaiOverrides;
    MuayThaiOverrides.Emplace(ECombatSoundType::HeavyPunch, "/Game/Audio/Styles/MuayThai/HeavyPunch");
    MuayThaiOverrides.Emplace(ECombatSoundType::HeavyKick, "/Game/Audio/Styles/MuayThai/HeavyKick");
    MuayThaiOverrides.Emplace(ECombatSoundType::BodyImpact, "/Game/Audio/Styles/MuayThai/BodyThud");
    MuayThaiOverrides.Emplace(ECombatSoundType::BlockImpact, "/Game/Audio/Styles/MuayThai/BlockThud");
    StyleSoundOverrides.Emplace(EFightingStyle::MuayThai, MuayThaiOverrides);
    StyleAudioDescriptions.Emplace(EFightingStyle::MuayThai, "Heavy thuds and powerful strikes");

    TMap<ECombatSoundType, FString> BoxingOverrides;
    BoxingOverrides.Emplace(ECombatSoundType::LightPunch, "/Game/Audio/Styles/Boxing/FastJab");
    BoxingOverrides.Emplace(ECombatSoundType::HeavyPunch, "/Game/Audio/Styles/Boxing/HeavyCross");
    BoxingOverrides.Emplace(ECombatSoundType::BodyImpact, "/Game/Audio/Styles/Boxing/BodyPop");
    BoxingOverrides.Emplace(ECombatSoundType::CounterImpact, "/Game/Audio/Styles/Boxing/CounterPop");
    StyleSoundOverrides.Emplace(EFightingStyle::Boxing, BoxingOverrides);
    StyleAudioDescriptions.Emplace(EFightingStyle::Boxing, "Fast pops and rhythmic combinations");

    TMap<ECombatSoundType, FString> TaekwondoOverrides;
    TaekwondoOverrides.Emplace(ECombatSoundType::LightKick, "/Game/Audio/Styles/Taekwondo/CrispKick");
    TaekwondoOverrides.Emplace(ECombatSoundType::HeavyKick, "/Game/Audio/Styles/Taekwondo/PowerKick");
    TaekwondoOverrides.Emplace(ECombatSoundType::LightPunch, "/Game/Audio/Styles/Taekwondo/LightStrike");
    StyleSoundOverrides.Emplace(EFightingStyle::Taekwondo, TaekwondoOverrides);
    StyleAudioDescriptions.Emplace(EFightingStyle::Taekwondo, "Crisp kicks and light strikes");

    TMap<ECombatSoundType, FString> JudoOverrides;
    JudoOverrides.Emplace(ECombatSoundType::BodyImpact, "/Game/Audio/Styles/Judo/ThrowThud");
    JudoOverrides.Emplace(ECombatSoundType::GroundImpact, "/Game/Audio/Styles/Judo/GroundSlap");
    JudoOverrides.Emplace(ECombatSoundType::Knockdown, "/Game/Audio/Styles/Judo/Takedown");
    JudoOverrides.Emplace(ECombatSoundType::GetUp, "/Game/Audio/Styles/Judo/Recovery");
    StyleSoundOverrides.Emplace(EFightingStyle::Judo, JudoOverrides);
    StyleAudioDescriptions.Emplace(EFightingStyle::Judo, "Thuds and grapple impacts");

    TMap<ECombatSoundType, FString> WushuOverrides;
    WushuOverrides.Emplace(ECombatSoundType::SpecialAttack, "/Game/Audio/Styles/Wushu/AcrobaticSwoosh");
    WushuOverrides.Emplace(ECombatSoundType::LightKick, "/Game/Audio/Styles/Wushu/QuickKick");
    WushuOverrides.Emplace(ECombatSoundType::Dodge, "/Game/Audio/Styles/Wushu/EvadeSwoosh");
    WushuOverrides.Emplace(ECombatSoundType::UltimateAttack, "/Game/Audio/Styles/Wushu/UltimateSwoosh");
    StyleSoundOverrides.Emplace(EFightingStyle::Wushu, WushuOverrides);
    StyleAudioDescriptions.Emplace(EFightingStyle::Wushu, "Acrobatic swooshes and fluid motions");
}

void ULesFightCombatSoundSystem::HandleCombatEvent(ECombatSoundType Event, AActor* Instigator, AActor* Target)
{
    if (!OwnerManager.IsValid() || !OwnerManager->GetSoundEffectManager().IsValid())
    {
        return;
    }

    FName OverridePath;
    TMap<ECombatSoundType, FString>* StyleOverrides = StyleSoundOverrides.Find(CurrentStyle);
    if (StyleOverrides != nullptr)
    {
        FString* Path = StyleOverrides->Find(Event);
        if (Path != nullptr)
        {
            OverridePath = FName(**Path);
        }
    }

    FVector Location = Instigator != nullptr ? Instigator->GetActorLocation() : FVector::ZeroVector;
    OwnerManager->GetSoundEffectManager()->PlayCombatSound(Event, Location, 1.0f);

    if (OwnerManager->GetSoundEffectManager().IsValid())
    {
        OwnerManager->GetSoundEffectManager()->PlayCombatSound(Event, Location, 1.0f);
    }
}

void ULesFightCombatSoundSystem::HandleImpact(FVector Location, FVector Normal, float Force)
{
    if (!OwnerManager.IsValid())
    {
        return;
    }

    ECombatSoundType Type = Force > 50.0f ? ECombatSoundType::HeavyPunch : ECombatSoundType::LightPunch;
    float VolMod = FMath::Clamp(Force / 100.0f, 0.5f, 1.5f);

    if (OwnerManager->GetSoundEffectManager().IsValid())
    {
        OwnerManager->GetSoundEffectManager()->PlayCombatSound(Type, Location, VolMod);
    }
}

void ULesFightCombatSoundSystem::HandleBlock(AActor* Defender)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        FVector Loc = Defender != nullptr ? Defender->GetActorLocation() : FVector::ZeroVector;
        OwnerManager->GetSoundEffectManager()->PlayCombatSound(ECombatSoundType::BlockImpact, Loc, 1.0f);
    }
}

void ULesFightCombatSoundSystem::HandleCounter(AActor* Attacker)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        FVector Loc = Attacker != nullptr ? Attacker->GetActorLocation() : FVector::ZeroVector;
        OwnerManager->GetSoundEffectManager()->PlayCombatSound(ECombatSoundType::CounterImpact, Loc, 1.0f);
    }
}

void ULesFightCombatSoundSystem::HandleKnockdown(AActor* Target)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        FVector Loc = Target != nullptr ? Target->GetActorLocation() : FVector::ZeroVector;
        OwnerManager->GetSoundEffectManager()->PlayCombatSound(ECombatSoundType::Knockdown, Loc, 1.0f);
    }
}

void ULesFightCombatSoundSystem::HandleGetUp(AActor* Target)
{
    if (OwnerManager.IsValid() && OwnerManager->GetSoundEffectManager().IsValid())
    {
        FVector Loc = Target != nullptr ? Target->GetActorLocation() : FVector::ZeroVector;
        OwnerManager->GetSoundEffectManager()->PlayCombatSound(ECombatSoundType::GetUp, Loc, 1.0f);
    }
}

void ULesFightCombatSoundSystem::SetStyleAudioProfile(EFightingStyle Style)
{
    CurrentStyle = Style;
}

EFightingStyle ULesFightCombatSoundSystem::GetStyleAudioProfile() const
{
    return CurrentStyle;
}
