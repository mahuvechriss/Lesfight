#include "LesFightBodyCustomization.h"
#include "LesFightCharCreationManager.h"

ULesFightBodyCustomization::ULesFightBodyCustomization()
    : CurrentHeight(175.0f)
    , CurrentBuild(ECharacterBuild::Athletic)
    , MinHeight(140.0f)
    , MaxHeight(220.0f)
    , DefaultHeight(175.0f)
{
    for (int32 i = 0; i < static_cast<int32>(EBodyMorphType::MAX); i++)
    {
        EBodyMorphType Type = static_cast<EBodyMorphType>(i);
        CurrentBodyMorphs.Add(Type, 0.5f);
        MorphRanges.Add(Type, 1.0f);
    }
}

void ULesFightBodyCustomization::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightBodyCustomization::SetBodyMorph(EBodyMorphType MorphType, float Value)
{
    if (CurrentBodyMorphs.Contains(MorphType))
    {
        float* Range = MorphRanges.Find(MorphType);
        float MaxRange = Range ? *Range : 1.0f;
        CurrentBodyMorphs[MorphType] = FMath::Clamp(Value, 0.0f, MaxRange);
    }
}

float ULesFightBodyCustomization::GetBodyMorph(EBodyMorphType MorphType) const
{
    const float* Value = CurrentBodyMorphs.Find(MorphType);
    return Value ? *Value : 0.0f;
}

void ULesFightBodyCustomization::SetAllBodyMorphs(
    const TMap<EBodyMorphType, float>& Morphs)
{
    for (const auto& Pair : Morphs)
    {
        SetBodyMorph(Pair.Key, Pair.Value);
    }
}

TMap<EBodyMorphType, float> ULesFightBodyCustomization::GetAllBodyMorphs() const
{
    return CurrentBodyMorphs;
}

void ULesFightBodyCustomization::SetHeight(float Height)
{
    CurrentHeight = FMath::Clamp(Height, MinHeight, MaxHeight);
}

float ULesFightBodyCustomization::GetHeight() const
{
    return CurrentHeight;
}

void ULesFightBodyCustomization::SetBuild(ECharacterBuild Build)
{
    CurrentBuild = Build;
}

ECharacterBuild ULesFightBodyCustomization::GetBuild() const
{
    return CurrentBuild;
}

TArray<EBodyMorphType> ULesFightBodyCustomization::GetAvailableMorphs() const
{
    TArray<EBodyMorphType> Types;
    CurrentBodyMorphs.GetKeys(Types);
    return Types;
}

void ULesFightBodyCustomization::ApplyToCharacter(AActor* CharacterActor)
{
}

void ULesFightBodyCustomization::ResetToDefault()
{
    for (auto& Pair : CurrentBodyMorphs)
    {
        Pair.Value = 0.5f;
    }
    CurrentHeight = DefaultHeight;
    CurrentBuild = ECharacterBuild::Athletic;
}
