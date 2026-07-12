#include "LesFightCharacterRandomizer.h"
#include "LesFightCharCreationManager.h"

ULesFightCharacterRandomizer::ULesFightCharacterRandomizer()
    : RandomizationIntensity(1.0f)
{
    RandomFirstNames = {
        TEXT("Alex"), TEXT("Maya"), TEXT("Kai"), TEXT("Sora"),
        TEXT("Ryu"), TEXT("Lena"), TEXT("Jin"), TEXT("Yuna"),
        TEXT("Zhao"), TEXT("Iris"), TEXT("Taro"), TEXT("Mei")
    };
    RandomLastNames = {
        TEXT("Tanaka"), TEXT("Chen"), TEXT("Patel"), TEXT("O'Brien"),
        TEXT("Johansson"), TEXT("Kim"), TEXT("Singh"), TEXT("Garcia"),
        TEXT("Nakamura"), TEXT("Smith"), TEXT("Lee"), TEXT("Park")
    };
    RandomCountries = {
        TEXT("Japan"), TEXT("China"), TEXT("Korea"), TEXT("Thailand"),
        TEXT("Brazil"), TEXT("USA"), TEXT("France"), TEXT("Russia")
    };
}

void ULesFightCharacterRandomizer::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
    RandomStream.Initialize(FMath::Rand());
}

FCharacterCustomizationPreset ULesFightCharacterRandomizer::GenerateRandomCharacter()
{
    FCharacterCustomizationPreset Preset;
    RandomizeBiography(Preset.Biography);
    RandomizeFace(Preset.FaceMorphs);
    RandomizeHair(Preset.Hair);
    RandomizeBody(Preset.BodyMorphs);
    RandomizeSkin(Preset.Skin);
    RandomizeClothing(Preset.Clothing);
    RandomizeAccessories(Preset.Accessories);
    RandomizeVoice(Preset.Voice);

    TArray<EFightingStyle> Styles = {
        EFightingStyle::Karate, EFightingStyle::MuayThai,
        EFightingStyle::Boxing, EFightingStyle::Taekwondo,
        EFightingStyle::Judo, EFightingStyle::Wushu
    };
    Preset.AssignedStyle = Styles[RandomIndex(Styles.Num())];

    return Preset;
}

void ULesFightCharacterRandomizer::RandomizeFace(
    TMap<EFaceMorphType, float>& FaceMorphs)
{
    for (int32 i = 0; i < static_cast<int32>(EFaceMorphType::MAX); i++)
    {
        EFaceMorphType Type = static_cast<EFaceMorphType>(i);
        FaceMorphs.Add(Type, RandomMorphValue(0.0f, 1.0f));
    }
}

void ULesFightCharacterRandomizer::RandomizeHair(FHairCustomizationData& HairData)
{
    HairData.Style = static_cast<EHairStyle>(RandomIndex(
        static_cast<int32>(EHairStyle::MAX)));
    HairData.HairColor = FLinearColor(
        RandomStream.FRand(), RandomStream.FRand(), RandomStream.FRand());
    HairData.Length = RandomStream.FRand();
    HairData.Shine = RandomStream.FRand();
    HairData.bPhysicsEnabled = true;
}

void ULesFightCharacterRandomizer::RandomizeBody(
    TMap<EBodyMorphType, float>& BodyMorphs)
{
    for (int32 i = 0; i < static_cast<int32>(EBodyMorphType::MAX); i++)
    {
        EBodyMorphType Type = static_cast<EBodyMorphType>(i);
        BodyMorphs.Add(Type, RandomMorphValue(0.0f, 1.0f));
    }
}

void ULesFightCharacterRandomizer::RandomizeSkin(FSkinCustomizationData& SkinData)
{
    SkinData.SkinTone = FLinearColor(
        0.5f + RandomStream.FRand() * 0.5f,
        0.3f + RandomStream.FRand() * 0.5f,
        0.2f + RandomStream.FRand() * 0.4f);
    SkinData.SkinDetail = static_cast<ESkinDetail>(
        RandomIndex(static_cast<int32>(ESkinDetail::MAX)));
    SkinData.Glossiness = RandomStream.FRand();
}

void ULesFightCharacterRandomizer::RandomizeClothing(
    TMap<EClothingSlot, FClothingItemData>& Clothing)
{
    for (int32 i = 0; i < static_cast<int32>(EClothingSlot::MAX); i++)
    {
        EClothingSlot Slot = static_cast<EClothingSlot>(i);
        if (RandomBool(0.7f))
        {
            FClothingItemData Item;
            Item.Slot = Slot;
            Item.bEquipped = true;
            Item.PrimaryColor = FLinearColor(
                RandomStream.FRand(), RandomStream.FRand(), RandomStream.FRand());
            Clothing.Add(Slot, Item);
        }
    }
}

void ULesFightCharacterRandomizer::RandomizeAccessories(
    TMap<EAccessorySlot, FAccessoryData>& Accessories)
{
    for (int32 i = 0; i < static_cast<int32>(EAccessorySlot::MAX); i++)
    {
        EAccessorySlot Slot = static_cast<EAccessorySlot>(i);
        if (RandomBool(0.3f))
        {
            FAccessoryData Acc;
            Acc.Slot = Slot;
            Acc.bEquipped = true;
            Acc.Color = FLinearColor(
                RandomStream.FRand(), RandomStream.FRand(), RandomStream.FRand());
            Accessories.Add(Slot, Acc);
        }
    }
}

void ULesFightCharacterRandomizer::RandomizeVoice(FVoiceSelectionData& VoiceData)
{
    VoiceData.VoicePack = static_cast<EVoicePack>(
        RandomIndex(static_cast<int32>(EVoicePack::MAX)));
    VoiceData.Pitch = 0.8f + RandomStream.FRand() * 0.4f;
    VoiceData.Tone = 0.8f + RandomStream.FRand() * 0.4f;
}

void ULesFightCharacterRandomizer::RandomizeBiography(FCharacterBiographyData& BioData)
{
    BioData.CharacterName = RandomFromArray(RandomFirstNames) + TEXT(" ") +
        RandomFromArray(RandomLastNames);
    if (RandomBool(0.6f))
    {
        BioData.Nickname = RandomFromArray(RandomNicknames);
    }
    BioData.Country = RandomFromArray(RandomCountries);
    BioData.Age = 18 + FMath::FloorToInt(RandomStream.FRand() * 40);
}

void ULesFightCharacterRandomizer::SetRandomSeed(int32 Seed)
{
    RandomStream.Initialize(Seed);
}

TArray<FCharacterCustomizationPreset> ULesFightCharacterRandomizer::GenerateBatch(
    int32 Count)
{
    TArray<FCharacterCustomizationPreset> Batch;
    for (int32 i = 0; i < Count; i++)
    {
        Batch.Add(GenerateRandomCharacter());
    }
    return Batch;
}

float ULesFightCharacterRandomizer::RandomMorphValue(float Min, float Max) const
{
    return Min + (RandomStream.FRand() * (Max - Min)) * RandomizationIntensity;
}

FLinearColor ULesFightCharacterRandomizer::RandomColorFromPalette(
    const TArray<FLinearColor>& Palette) const
{
    if (Palette.Num() == 0) return FLinearColor::White;
    return Palette[RandomIndex(Palette.Num())];
}

FString ULesFightCharacterRandomizer::RandomFromArray(
    const TArray<FString>& Array) const
{
    if (Array.Num() == 0) return TEXT("");
    return Array[RandomIndex(Array.Num())];
}

int32 ULesFightCharacterRandomizer::RandomIndex(int32 Max) const
{
    return Max > 0 ? FMath::FloorToInt(RandomStream.FRand() * Max) : 0;
}

bool ULesFightCharacterRandomizer::RandomBool(float TrueChance) const
{
    return RandomStream.FRand() < TrueChance;
}
