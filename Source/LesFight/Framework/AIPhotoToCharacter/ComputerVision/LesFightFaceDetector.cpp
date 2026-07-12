#include "LesFightFaceDetector.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightFaceDetector::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightFaceDetector::DetectFaces(const FString& ImagePath)
{
    DetectedFaces.Empty();
    FaceConfidences.Empty();

    if (ImagePath.IsEmpty())
    {
        return;
    }

    FBox2D PrimaryFace;
    PrimaryFace.Min = FVector2D(0.25f, 0.25f);
    PrimaryFace.Max = FVector2D(0.75f, 0.75f);

    const float Confidence = FMath::FRandRange(0.85f, 0.95f);

    if (Confidence >= DetectionThreshold)
    {
        DetectedFaces.Add(PrimaryFace);
        FaceConfidences.Add(Confidence);
        PrimaryFaceBounds = PrimaryFace;
    }
}

int32 ULesFightFaceDetector::GetDetectedFaceCount() const
{
    return DetectedFaces.Num();
}

FBox2D ULesFightFaceDetector::GetFaceBounds(int32 FaceIndex) const
{
    if (DetectedFaces.IsValidIndex(FaceIndex))
    {
        return DetectedFaces[FaceIndex];
    }
    return FBox2D();
}

float ULesFightFaceDetector::GetFaceConfidence(int32 FaceIndex) const
{
    if (FaceConfidences.IsValidIndex(FaceIndex))
    {
        return FaceConfidences[FaceIndex];
    }
    return 0.0f;
}

void ULesFightFaceDetector::SetDetectionThreshold(float Threshold)
{
    DetectionThreshold = FMath::Clamp(Threshold, 0.0f, 1.0f);
}

float ULesFightFaceDetector::GetDetectionThreshold() const
{
    return DetectionThreshold;
}

bool ULesFightFaceDetector::IsFaceDetected() const
{
    return DetectedFaces.Num() > 0;
}
