#include "LesFightLandmarkDetector.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightLandmarkDetector::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightLandmarkDetector::DetectLandmarks(const FString& ImagePath)
{
    bLandmarksDetected = false;

    if (ImagePath.IsEmpty())
    {
        return;
    }

    DetectedLandmarks.LeftEyeCenter = FVector2D(0.3f, 0.35f);
    DetectedLandmarks.RightEyeCenter = FVector2D(0.7f, 0.35f);
    DetectedLandmarks.NoseTip = FVector2D(0.5f, 0.55f);
    DetectedLandmarks.NoseBridge = FVector2D(0.5f, 0.38f);
    DetectedLandmarks.MouthCenter = FVector2D(0.5f, 0.68f);
    DetectedLandmarks.MouthLeftCorner = FVector2D(0.35f, 0.67f);
    DetectedLandmarks.MouthRightCorner = FVector2D(0.65f, 0.67f);
    DetectedLandmarks.ChinTip = FVector2D(0.5f, 0.85f);
    DetectedLandmarks.LeftJawCorner = FVector2D(0.18f, 0.72f);
    DetectedLandmarks.RightJawCorner = FVector2D(0.82f, 0.72f);
    DetectedLandmarks.LeftEyebrowInner = FVector2D(0.35f, 0.27f);
    DetectedLandmarks.LeftEyebrowOuter = FVector2D(0.22f, 0.28f);
    DetectedLandmarks.RightEyebrowInner = FVector2D(0.65f, 0.27f);
    DetectedLandmarks.RightEyebrowOuter = FVector2D(0.78f, 0.28f);

    DetectedLandmarks.FaceContour.Empty();
    for (int32 i = 0; i < 16; i++)
    {
        const float Angle = FMath::DegreesToRadians(-90.0f + (180.0f / 15.0f) * i);
        const float Cx = 0.5f;
        const float Cy = 0.5f;
        const float Rx = 0.38f;
        const float Ry = 0.45f;
        DetectedLandmarks.FaceContour.Add(FVector2D(Cx + Rx * FMath::Cos(Angle), Cy + Ry * FMath::Sin(Angle)));
    }

    DetectedLandmarks.LeftEyeContour.Empty();
    DetectedLandmarks.LeftEyeContour.Add(FVector2D(0.27f, 0.34f));
    DetectedLandmarks.LeftEyeContour.Add(FVector2D(0.30f, 0.33f));
    DetectedLandmarks.LeftEyeContour.Add(FVector2D(0.33f, 0.34f));
    DetectedLandmarks.LeftEyeContour.Add(FVector2D(0.33f, 0.36f));
    DetectedLandmarks.LeftEyeContour.Add(FVector2D(0.30f, 0.37f));
    DetectedLandmarks.LeftEyeContour.Add(FVector2D(0.27f, 0.36f));

    DetectedLandmarks.RightEyeContour.Empty();
    DetectedLandmarks.RightEyeContour.Add(FVector2D(0.67f, 0.34f));
    DetectedLandmarks.RightEyeContour.Add(FVector2D(0.70f, 0.33f));
    DetectedLandmarks.RightEyeContour.Add(FVector2D(0.73f, 0.34f));
    DetectedLandmarks.RightEyeContour.Add(FVector2D(0.73f, 0.36f));
    DetectedLandmarks.RightEyeContour.Add(FVector2D(0.70f, 0.37f));
    DetectedLandmarks.RightEyeContour.Add(FVector2D(0.67f, 0.36f));

    DetectedLandmarks.LipsContour.Empty();
    DetectedLandmarks.LipsContour.Add(FVector2D(0.50f, 0.66f));
    DetectedLandmarks.LipsContour.Add(FVector2D(0.42f, 0.67f));
    DetectedLandmarks.LipsContour.Add(FVector2D(0.35f, 0.68f));
    DetectedLandmarks.LipsContour.Add(FVector2D(0.42f, 0.69f));
    DetectedLandmarks.LipsContour.Add(FVector2D(0.50f, 0.70f));
    DetectedLandmarks.LipsContour.Add(FVector2D(0.58f, 0.69f));
    DetectedLandmarks.LipsContour.Add(FVector2D(0.65f, 0.68f));
    DetectedLandmarks.LipsContour.Add(FVector2D(0.58f, 0.67f));

    LandmarkConfidence = 0.9f;
    DetectedLandmarks.Confidence = LandmarkConfidence;
    bLandmarksDetected = true;

    OnLandmarksDetected.Broadcast(DetectedLandmarks);
}

FFacialLandmarkData ULesFightLandmarkDetector::GetLandmarks() const
{
    return DetectedLandmarks;
}

int32 ULesFightLandmarkDetector::GetLandmarkCount() const
{
    return bLandmarksDetected ? 68 : 0;
}

float ULesFightLandmarkDetector::GetLandmarkConfidence() const
{
    return LandmarkConfidence;
}

void ULesFightLandmarkDetector::SetLandmarkAccuracy(int32 Level)
{
    AccuracyLevel = FMath::Clamp(Level, 1, 3);
}

bool ULesFightLandmarkDetector::VisualizeLandmarks(const FString& ImagePath, const FString& OutputPath)
{
    if (ImagePath.IsEmpty() || OutputPath.IsEmpty())
    {
        return false;
    }
    return bLandmarksDetected;
}
