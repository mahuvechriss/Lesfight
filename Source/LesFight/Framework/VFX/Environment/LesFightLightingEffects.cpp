#include "LesFightLightingEffects.h"
#include "Framework/VFX/Manager/LesFightVFXWorldManager.h"
#include "Components/PointLightComponent.h"
#include "Engine/World.h"

void ULesFightLightingEffects::Initialize(ULesFightVFXWorldManager* InOwner)
{
    OwnerManager = InOwner;
    bCustomLightingActive = false;
    CustomLightingIntensity = 1.0f;
    FlashTimer = 0.0f;
    CurrentFlashColor = FLinearColor::White;
}

void ULesFightLightingEffects::SetCombatLighting(FVector Location, FLinearColor Color, float Intensity)
{
    bCustomLightingActive = true;
    CustomLightingIntensity = Intensity;
}

void ULesFightLightingEffects::FlashLight(FLinearColor Color, float Duration, float Intensity)
{
    CurrentFlashColor = Color;
    FlashTimer = Duration;
}

void ULesFightLightingEffects::PulseLight(FLinearColor Color, float Speed, float Duration)
{
    CurrentFlashColor = Color;
    FlashTimer = Duration;
}

void ULesFightLightingEffects::SetCharacterGlow(AActor* Character, FLinearColor Color, float Intensity)
{
    if (!Character) return;

    if (Color.A < 0.01f)
    {
        CharacterGlows.Remove(Character);
    }
    else
    {
        CharacterGlows.Add(Character, Color);
    }
}

void ULesFightLightingEffects::ResetLighting()
{
    bCustomLightingActive = false;
    CustomLightingIntensity = 1.0f;
    FlashTimer = 0.0f;
    CurrentFlashColor = FLinearColor::White;
    CharacterGlows.Empty();
}

void ULesFightLightingEffects::SetLightingIntensity(float Intensity)
{
    CustomLightingIntensity = FMath::Clamp(Intensity, 0.0f, 10.0f);
}
