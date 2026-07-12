#include "LesFightFeatureExtractor.h"
#include "Pipeline/LesFightAIPipelineManager.h"
#include "Math/UnrealMathUtility.h"

void ULesFightFeatureExtractor::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightFeatureExtractor::ExtractFeatures(const FString& ImagePath)
{
    bFeaturesExtracted = false;

    if (ImagePath.IsEmpty())
    {
        return;
    }

    ExtractedFeatures.FaceWidth = 0.14f;
    ExtractedFeatures.FaceHeight = 0.18f;
    ExtractedFeatures.EyeDistance = 0.07f;
    ExtractedFeatures.NoseLength = 0.05f;
    ExtractedFeatures.NoseWidth = 0.03f;
    ExtractedFeatures.MouthWidth = 0.06f;
    ExtractedFeatures.MouthHeight = 0.02f;
    ExtractedFeatures.JawWidth = 0.11f;
    ExtractedFeatures.ChinLength = 0.04f;
    ExtractedFeatures.CheekboneWidth = 0.12f;
    ExtractedFeatures.ForeheadHeight = 0.06f;
    ExtractedFeatures.EyeShapeScore = 0.5f;
    ExtractedFeatures.BrowHeight = 0.03f;
    ExtractedFeatures.AverageSkinTone = FLinearColor(0.8f, 0.6f, 0.5f);
    ExtractedFeatures.SkinRoughnessEstimate = 0.5f;
    ExtractedFeatures.SkinGlossEstimate = 0.3f;
    ExtractedFeatures.Confidence = 0.85f;

    const int32 RandomIndex = FMath::RandRange(0, static_cast<int32>(EFacialExpression::MAX) - 2);
    ExtractedFeatures.DetectedExpression = static_cast<EFacialExpression>(RandomIndex);

    ExtractedFeatures.SkinToneSamples = ExtractSkinTone(ImagePath);

    HairFeatures.DetectedStyle = static_cast<EHairDetectionType>(FMath::RandRange(1, 8));
    HairFeatures.DetectedColor = FLinearColor(0.2f, 0.1f, 0.05f);
    HairFeatures.HairLengthEstimate = 0.5f;
    HairFeatures.HairDensity = 0.8f;
    HairFeatures.HairRegionTop = FVector2D(0.5f, 0.05f);
    HairFeatures.HairRegionBottom = FVector2D(0.5f, 0.25f);
    HairFeatures.Confidence = 0.75f;

    bFeaturesExtracted = true;
}

FFaceFeatureData ULesFightFeatureExtractor::GetFaceFeatures() const
{
    return ExtractedFeatures;
}

FHairDetectionData ULesFightFeatureExtractor::GetHairDetection() const
{
    return HairFeatures;
}

EFacialExpression ULesFightFeatureExtractor::GetExpression() const
{
    return ExtractedFeatures.DetectedExpression;
}

TArray<FLinearColor> ULesFightFeatureExtractor::ExtractSkinTone(const FString& ImagePath)
{
    TArray<FLinearColor> Samples;
    if (ImagePath.IsEmpty())
    {
        return Samples;
    }

    const FLinearColor BaseTone(0.8f, 0.6f, 0.5f);
    Samples.Add(BaseTone);
    Samples.Add(FLinearColor(0.78f, 0.58f, 0.48f));
    Samples.Add(FLinearColor(0.82f, 0.62f, 0.52f));
    Samples.Add(FLinearColor(0.77f, 0.57f, 0.47f));
    Samples.Add(FLinearColor(0.83f, 0.63f, 0.53f));

    ExtractedFeatures.AverageSkinTone = BaseTone;
    ExtractedFeatures.SkinToneSamples = Samples;

    return Samples;
}

int32 ULesFightFeatureExtractor::EstimateAge(const FString& ImagePath)
{
    if (ImagePath.IsEmpty())
    {
        return 0;
    }
    return FMath::RandRange(20, 40);
}

FString ULesFightFeatureExtractor::EstimateGender(const FString& ImagePath)
{
    if (ImagePath.IsEmpty())
    {
        return TEXT("Unknown");
    }
    return FMath::RandBool() ? TEXT("Male") : TEXT("Female");
}
