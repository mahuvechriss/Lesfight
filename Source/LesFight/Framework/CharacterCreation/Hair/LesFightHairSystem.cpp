#include "LesFightHairSystem.h"
#include "LesFightCharCreationManager.h"

ULesFightHairSystem::ULesFightHairSystem()
    : DefaultLength(0.5f)
    , MinLength(0.0f)
    , MaxLength(1.0f)
{
    CurrentHairData.Style = EHairStyle::Short;
    CurrentHairData.HairColor = FLinearColor(0.1f, 0.1f, 0.1f);
    CurrentHairData.Length = DefaultLength;
    CurrentHairData.Shine = 0.5f;
    CurrentHairData.bPhysicsEnabled = true;

    for (int32 i = 0; i < static_cast<int32>(EHairStyle::MAX); i++)
    {
        UnlockedStyles.Add(static_cast<EHairStyle>(i));
    }
}

void ULesFightHairSystem::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightHairSystem::SetHairStyle(EHairStyle Style)
{
    CurrentHairData.Style = Style;
}

EHairStyle ULesFightHairSystem::GetHairStyle() const
{
    return CurrentHairData.Style;
}

void ULesFightHairSystem::SetHairColor(FLinearColor Color)
{
    CurrentHairData.HairColor = Color;
}

FLinearColor ULesFightHairSystem::GetHairColor() const
{
    return CurrentHairData.HairColor;
}

void ULesFightHairSystem::SetHairLength(float Length)
{
    CurrentHairData.Length = FMath::Clamp(Length, MinLength, MaxLength);
}

float ULesFightHairSystem::GetHairLength() const
{
    return CurrentHairData.Length;
}

void ULesFightHairSystem::SetHairShine(float Shine)
{
    CurrentHairData.Shine = FMath::Clamp(Shine, 0.0f, 1.0f);
}

void ULesFightHairSystem::SetPhysicsEnabled(bool bEnabled)
{
    CurrentHairData.bPhysicsEnabled = bEnabled;
}

void ULesFightHairSystem::SetCustomizationData(const FHairCustomizationData& Data)
{
    CurrentHairData = Data;
}

FHairCustomizationData ULesFightHairSystem::GetCustomizationData() const
{
    return CurrentHairData;
}

TArray<EHairStyle> ULesFightHairSystem::GetAvailableStyles() const
{
    return UnlockedStyles;
}

void ULesFightHairSystem::ApplyToCharacter(AActor* CharacterActor)
{
}

void ULesFightHairSystem::ResetToDefault()
{
    CurrentHairData.Style = EHairStyle::Short;
    CurrentHairData.HairColor = FLinearColor(0.1f, 0.1f, 0.1f);
    CurrentHairData.Length = DefaultLength;
    CurrentHairData.Shine = 0.5f;
    CurrentHairData.bPhysicsEnabled = true;
}
