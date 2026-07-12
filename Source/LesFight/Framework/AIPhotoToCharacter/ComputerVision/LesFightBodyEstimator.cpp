#include "LesFightBodyEstimator.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightBodyEstimator::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightBodyEstimator::EstimateBodyProportions(const FString& ImagePath)
{
    if (ImagePath.IsEmpty())
    {
        return;
    }

    EstimatedProportions.EstimatedHeight = ReferenceHeight;
    EstimatedProportions.ShoulderWidth = 40.0f;
    EstimatedProportions.ChestCircumference = 95.0f;
    EstimatedProportions.WaistCircumference = 80.0f;
    EstimatedProportions.HipCircumference = 95.0f;
    EstimatedProportions.ArmLength = 75.0f;
    EstimatedProportions.LegLength = 85.0f;
    EstimatedProportions.NeckLength = 10.0f;
    EstimatedProportions.TorsoLength = 55.0f;
    EstimationConfidence = 0.8f;
    EstimatedProportions.Confidence = EstimationConfidence;
}

FBodyProportionData ULesFightBodyEstimator::GetBodyProportions() const
{
    return EstimatedProportions;
}

float ULesFightBodyEstimator::GetEstimatedHeight() const
{
    return EstimatedProportions.EstimatedHeight;
}

float ULesFightBodyEstimator::GetConfidence() const
{
    return EstimationConfidence;
}

void ULesFightBodyEstimator::SetReferenceHeight(float HeightCM)
{
    ReferenceHeight = FMath::Clamp(HeightCM, 100.0f, 250.0f);
}

TMap<EBodyMorphType, float> ULesFightBodyEstimator::GenerateBodyMorphTargets() const
{
    TMap<EBodyMorphType, float> Morphs;

    const float HeightNorm = (EstimatedProportions.EstimatedHeight - 100.0f) / 150.0f;
    Morphs.Add(EBodyMorphType::Height, HeightNorm);
    Morphs.Add(EBodyMorphType::ShoulderWidth, EstimatedProportions.ShoulderWidth / 60.0f);
    Morphs.Add(EBodyMorphType::ChestSize, EstimatedProportions.ChestCircumference / 130.0f);
    Morphs.Add(EBodyMorphType::WaistSize, EstimatedProportions.WaistCircumference / 120.0f);
    Morphs.Add(EBodyMorphType::HipWidth, EstimatedProportions.HipCircumference / 120.0f);
    Morphs.Add(EBodyMorphType::ArmLength, EstimatedProportions.ArmLength / 100.0f);
    Morphs.Add(EBodyMorphType::LegLength, EstimatedProportions.LegLength / 120.0f);
    Morphs.Add(EBodyMorphType::NeckSize, EstimatedProportions.NeckLength / 20.0f);

    return Morphs;
}

void ULesFightBodyEstimator::CorrectProportionsManually(const FBodyProportionData& Corrections)
{
    EstimatedProportions = Corrections;
    EstimatedProportions.Confidence = 1.0f;
    EstimationConfidence = 1.0f;
}
