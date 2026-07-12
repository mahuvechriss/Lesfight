#include "LesFightFaceCustomization.h"
#include "LesFightCharCreationManager.h"

ULesFightFaceCustomization::ULesFightFaceCustomization()
    : CurrentEyeColor(FLinearColor(0.2f, 0.4f, 0.8f))
{
    for (int32 i = 0; i < static_cast<int32>(EFaceMorphType::MAX); i++)
    {
        EFaceMorphType Type = static_cast<EFaceMorphType>(i);
        CurrentMorphs.Add(Type, 0.5f);
        MorphRanges.Add(Type, 1.0f);
    }
}

void ULesFightFaceCustomization::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightFaceCustomization::SetMorphValue(EFaceMorphType MorphType, float Value)
{
    if (CurrentMorphs.Contains(MorphType))
    {
        float* Range = MorphRanges.Find(MorphType);
        float MaxRange = Range ? *Range : 1.0f;
        CurrentMorphs[MorphType] = FMath::Clamp(Value, 0.0f, MaxRange);
    }
}

float ULesFightFaceCustomization::GetMorphValue(EFaceMorphType MorphType) const
{
    const float* Value = CurrentMorphs.Find(MorphType);
    return Value ? *Value : 0.0f;
}

void ULesFightFaceCustomization::SetAllMorphs(const TMap<EFaceMorphType, float>& Morphs)
{
    for (const auto& Pair : Morphs)
    {
        SetMorphValue(Pair.Key, Pair.Value);
    }
}

void ULesFightFaceCustomization::ResetToDefault()
{
    for (auto& Pair : CurrentMorphs)
    {
        Pair.Value = 0.5f;
    }
    CurrentEyeColor = FLinearColor(0.2f, 0.4f, 0.8f);
}

void ULesFightFaceCustomization::ApplyToCharacter(AActor* CharacterActor)
{
}

float ULesFightFaceCustomization::GetMorphRange(EFaceMorphType MorphType) const
{
    const float* Range = MorphRanges.Find(MorphType);
    return Range ? *Range : 1.0f;
}

void ULesFightFaceCustomization::SetEyeColor(FLinearColor Color)
{
    CurrentEyeColor = Color;
}

TArray<EFaceMorphType> ULesFightFaceCustomization::GetAvailableMorphs() const
{
    TArray<EFaceMorphType> Types;
    CurrentMorphs.GetKeys(Types);
    return Types;
}
