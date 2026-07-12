#include "LesFightStyleRecommender.h"
#include "Pipeline/LesFightAIPipelineManager.h"

ULesFightStyleRecommender::ULesFightStyleRecommender()
    : Aggressiveness(0.5f)
    , StyleConfidence(0.0f)
{
}

void ULesFightStyleRecommender::Initialize(ULesFightAIManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightStyleRecommender::AnalyzePhotosForStyle(const TArray<FString>& PhotoPaths)
{
    StyleMatchScores.Empty();

    TArray<EFightingStyle> AllStyles = {
        EFightingStyle::ShaolinKungFu,
        EFightingStyle::WingChun,
        EFightingStyle::TaiChi,
        EFightingStyle::Wushu,
        EFightingStyle::DrunkenFist,
        EFightingStyle::JeetKuneDo,
        EFightingStyle::MuayThai,
        EFightingStyle::Taekwondo,
        EFightingStyle::Karate,
        EFightingStyle::Judo,
        EFightingStyle::BrazilianJiuJitsu,
        EFightingStyle::Boxing,
        EFightingStyle::Kickboxing
    };

    for (EFightingStyle Style : AllStyles)
    {
        StyleMatchScores.Add(Style, FMath::FRandRange(0.0f, 1.0f));
    }

    EFightingStyle BestStyle = EFightingStyle::None;
    float BestScore = -1.0f;
    for (const auto& Pair : StyleMatchScores)
    {
        if (Pair.Value > BestScore)
        {
            BestScore = Pair.Value;
            BestStyle = Pair.Key;
        }
    }
    TopStyle = BestStyle;

    RecommendedStyles.Empty();
    StyleScores.Empty();
    for (const auto& Pair : StyleMatchScores)
    {
        RecommendedStyles.Add(Pair.Key);
        StyleScores.Add(Pair.Value);
    }

    StyleConfidence = FMath::FRandRange(0.7f, 0.9f);
}

EFightingStyle ULesFightStyleRecommender::RecommendFightingStyle() const
{
    if (UserPreferences.Num() > 0)
    {
        TMap<EFightingStyle, float> AdjustedScores = StyleMatchScores;
        for (EFightingStyle Preferred : UserPreferences)
        {
            if (float* Score = AdjustedScores.Find(Preferred))
            {
                *Score += 0.3f;
            }
        }

        EFightingStyle Best = EFightingStyle::None;
        float Highest = -1.0f;
        for (const auto& Pair : AdjustedScores)
        {
            if (Pair.Value > Highest)
            {
                Highest = Pair.Value;
                Best = Pair.Key;
            }
        }
        return Best;
    }

    return TopStyle;
}

TArray<EClothingSlot> ULesFightStyleRecommender::RecommendClothingStyle() const
{
    TArray<EClothingSlot> AllSlots = {
        EClothingSlot::Headwear,
        EClothingSlot::Mask,
        EClothingSlot::Glasses,
        EClothingSlot::NeckAccessory,
        EClothingSlot::UpperBody,
        EClothingSlot::Gloves,
        EClothingSlot::Belt,
        EClothingSlot::LowerBody,
        EClothingSlot::Shoes,
        EClothingSlot::BackAccessory,
        EClothingSlot::WristAccessory,
        EClothingSlot::LegAccessory
    };

    int32 Count = FMath::RandRange(3, 5);
    TArray<EClothingSlot> Result;
    for (int32 i = 0; i < Count && AllSlots.Num() > 0; ++i)
    {
        int32 Idx = FMath::RandRange(0, AllSlots.Num() - 1);
        Result.Add(AllSlots[Idx]);
        AllSlots.RemoveAt(Idx);
    }
    return Result;
}

EHairStyle ULesFightStyleRecommender::RecommendHairStyle() const
{
    TArray<EHairStyle> HairStyles = {
        EHairStyle::Bald,
        EHairStyle::Short,
        EHairStyle::Long,
        EHairStyle::Braided,
        EHairStyle::Curly,
        EHairStyle::Straight,
        EHairStyle::Afro,
        EHairStyle::Ponytail,
        EHairStyle::Bun
    };
    return HairStyles[FMath::RandRange(0, HairStyles.Num() - 1)];
}

TArray<FLinearColor> ULesFightStyleRecommender::RecommendColorPalette() const
{
    TArray<FLinearColor> Palette;
    Palette.Add(FLinearColor(FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f)));
    Palette.Add(FLinearColor(FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f)));
    Palette.Add(FLinearColor(FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f)));
    Palette.Add(FLinearColor(FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f), FMath::FRandRange(0.0f, 1.0f)));
    return Palette;
}

float ULesFightStyleRecommender::GetStyleConfidence() const
{
    return StyleConfidence;
}

FString ULesFightStyleRecommender::GenerateStyleProfile() const
{
    FString Profile;
    Profile += TEXT("{\n");
    Profile += FString::Printf(TEXT("  \"TopStyle\": \"%s\",\n"), *UEnum::GetValueAsString(TopStyle));
    Profile += FString::Printf(TEXT("  \"Confidence\": %.2f,\n"), StyleConfidence);
    Profile += FString::Printf(TEXT("  \"Aggressiveness\": %.2f,\n"), Aggressiveness);
    Profile += TEXT("  \"StyleScores\": {\n");
    for (const auto& Pair : StyleMatchScores)
    {
        Profile += FString::Printf(TEXT("    \"%s\": %.2f,\n"), *UEnum::GetValueAsString(Pair.Key), Pair.Value);
    }
    Profile += TEXT("  },\n");
    Profile += TEXT("  \"UserPreferences\": [\n");
    for (EFightingStyle Pref : UserPreferences)
    {
        Profile += FString::Printf(TEXT("    \"%s\",\n"), *UEnum::GetValueAsString(Pref));
    }
    Profile += TEXT("  ]\n");
    Profile += TEXT("}");
    return Profile;
}

void ULesFightStyleRecommender::SetAggressiveness(float InAggressiveness)
{
    Aggressiveness = InAggressiveness;
}

void ULesFightStyleRecommender::SetStylePreferences(const TArray<EFightingStyle>& Preferred)
{
    UserPreferences = Preferred;
}
