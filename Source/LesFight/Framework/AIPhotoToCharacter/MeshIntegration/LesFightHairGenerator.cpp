#include "LesFightHairGenerator.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightHairGenerator::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bHairGenerated = false;
    bHairPhysicsEnabled = false;
    HairQuality = 3;
    AppliedStyle = EHairStyle::Short;
    AppliedColor = FLinearColor::White;
}

EHairStyle ULesFightHairGenerator::MapDetectionToStyle(EHairDetectionType Detected) const
{
    switch (Detected)
    {
    case EHairDetectionType::Short:   return EHairStyle::Short;
    case EHairDetectionType::Long:    return EHairStyle::Long;
    case EHairDetectionType::Curly:   return EHairStyle::Curly;
    case EHairDetectionType::Straight: return EHairStyle::Straight;
    case EHairDetectionType::Bald:    return EHairStyle::Bald;
    case EHairDetectionType::Ponytail: return EHairStyle::Ponytail;
    case EHairDetectionType::Bun:     return EHairStyle::Bun;
    case EHairDetectionType::Braids:  return EHairStyle::Braided;
    case EHairDetectionType::Wavy:    return EHairStyle::Curly;
    default:                           return EHairStyle::Short;
    }
}

void ULesFightHairGenerator::GenerateHair(const FHairDetectionData& DetectedHair)
{
    HairData = DetectedHair;
    AppliedStyle = MapDetectionToStyle(DetectedHair.DetectedStyle);
    AppliedColor = DetectedHair.DetectedColor;

    GeneratedHairPath = FString::Printf(TEXT("/Game/Generated/Hair/AI_Hair_%s"), *UEnum::GetValueAsString(DetectedHair.DetectedStyle));
    bHairGenerated = true;
}

void ULesFightHairGenerator::SetHairQuality(int32 Quality)
{
    HairQuality = FMath::Clamp(Quality, 1, 5);
}

TArray<EHairStyle> ULesFightHairGenerator::GetAvailableHairStyles() const
{
    TArray<EHairStyle> Styles;
    for (int32 i = 0; i < static_cast<int32>(EHairStyle::MAX); ++i)
    {
        Styles.Add(static_cast<EHairStyle>(i));
    }
    return Styles;
}

void ULesFightHairGenerator::OverrideHairStyle(EHairStyle Style)
{
    AppliedStyle = Style;
}

void ULesFightHairGenerator::SetHairColor(FLinearColor Color)
{
    AppliedColor = Color;
}

void ULesFightHairGenerator::SetHairPhysicsEnabled(bool bEnabled)
{
    bHairPhysicsEnabled = bEnabled;
}

void ULesFightHairGenerator::ApplyHairToCharacter(AActor* CharacterActor)
{
}
