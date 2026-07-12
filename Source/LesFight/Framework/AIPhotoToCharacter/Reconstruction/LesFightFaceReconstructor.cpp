#include "LesFightFaceReconstructor.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightFaceReconstructor::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bReconstructionComplete = false;
    VertexCount = 0;
    TriangleCount = 0;
}

void ULesFightFaceReconstructor::ReconstructFace(const FFaceFeatureData& Features, const FFacialLandmarkData& Landmarks)
{
    F3DFaceReconstructionData Data;

    const int32 GridX = 72;
    const int32 GridY = 72;
    const float Scale = 10.0f;

    Data.VertexPositions.Reserve(GridX * GridY);
    for (int32 Y = 0; Y < GridY; ++Y)
    {
        for (int32 X = 0; X < GridX; ++X)
        {
            float U = (float)X / (float)(GridX - 1);
            float V = (float)Y / (float)(GridY - 1);

            float Theta = U * PI;
            float Phi = V * 2.0f * PI;

            float R = Scale * (0.9f + 0.1f * FMath::Sin(Theta * 3.0f) * FMath::Cos(Phi * 2.0f));

            FVector Vertex(
                R * FMath::Sin(Theta) * FMath::Cos(Phi),
                R * FMath::Sin(Theta) * FMath::Sin(Phi),
                R * FMath::Cos(Theta)
            );

            Vertex.X += Features.FaceWidth * 0.5f;
            Vertex.Y += Features.FaceHeight * 0.3f;
            Vertex.Z += Features.NoseLength * 0.4f;

            Data.VertexPositions.Add(Vertex);
            Data.UVCoordinates.Add(FVector2D(U, V));
        }
    }

    Data.TriangleIndices.Reserve((GridX - 1) * (GridY - 1) * 6);
    for (int32 Y = 0; Y < GridY - 1; ++Y)
    {
        for (int32 X = 0; X < GridX - 1; ++X)
        {
            int32 TL = Y * GridX + X;
            int32 TR = Y * GridX + X + 1;
            int32 BL = (Y + 1) * GridX + X;
            int32 BR = (Y + 1) * GridX + X + 1;

            Data.TriangleIndices.Add(TL);
            Data.TriangleIndices.Add(BL);
            Data.TriangleIndices.Add(TR);

            Data.TriangleIndices.Add(TR);
            Data.TriangleIndices.Add(BL);
            Data.TriangleIndices.Add(BR);
        }
    }

    Data.Normals.Reserve(Data.VertexPositions.Num());
    for (const FVector& Vert : Data.VertexPositions)
    {
        Data.Normals.Add(Vert.GetSafeNormal());
    }

    switch (ReconstructionQuality)
    {
    case EAIGenerationQuality::Draft:   Data.Quality = 0.6f; break;
    case EAIGenerationQuality::Standard: Data.Quality = 0.8f; break;
    case EAIGenerationQuality::High:    Data.Quality = 0.9f; break;
    case EAIGenerationQuality::Ultra:   Data.Quality = 1.0f; break;
    default:                            Data.Quality = 0.8f; break;
    }

    Data.MorphTargetValues.Add(EFaceMorphType::FaceShape, Features.FaceWidth / 100.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::Jaw, Features.JawWidth / 100.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::Chin, Features.ChinLength / 50.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::Cheekbones, Features.CheekboneWidth / 100.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::Forehead, Features.ForeheadHeight / 50.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::NoseWidth, Features.NoseWidth / 50.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::NoseHeight, Features.NoseLength / 60.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::NoseBridge, Features.NoseLength / 60.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::Lips, Features.MouthHeight / 30.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::MouthWidth, Features.MouthWidth / 80.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::EyeShape, Features.EyeDistance / 60.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::EyeSize, Features.EyeShapeScore);
    Data.MorphTargetValues.Add(EFaceMorphType::Eyebrows, Features.BrowHeight / 40.0f);
    Data.MorphTargetValues.Add(EFaceMorphType::Wrinkles, 0.3f);
    Data.MorphTargetValues.Add(EFaceMorphType::Freckles, 0.1f);

    ReconstructedFace = Data;
    VertexCount = Data.VertexPositions.Num();
    TriangleCount = Data.TriangleIndices.Num() / 3;
    bReconstructionComplete = true;
}

void ULesFightFaceReconstructor::SetReconstructionQuality(EAIGenerationQuality Quality)
{
    ReconstructionQuality = Quality;
}

void ULesFightFaceReconstructor::GenerateBlendShapes(int32 Count)
{
    BlendShapeNames.Empty();
    BlendShapeNames.Reserve(Count);
    for (int32 i = 0; i < Count; ++i)
    {
        BlendShapeNames.Add(FName(*FString::Printf(TEXT("BlendShape_%d"), i)));
    }

    ReconstructedFace.BlendShapeWeights.Empty();
    ReconstructedFace.BlendShapeWeights.Reserve(Count);
    for (const FName& Name : BlendShapeNames)
    {
        ReconstructedFace.BlendShapeWeights.Add(Name, 0.0f);
    }
}

void ULesFightFaceReconstructor::RefineFaceFromMultipleImages(const TArray<FFaceFeatureData>& MultiViews)
{
    if (MultiViews.Num() == 0)
    {
        return;
    }

    FFaceFeatureData AveragedFeatures = MultiViews[0];
    for (int32 i = 1; i < MultiViews.Num(); ++i)
    {
        AveragedFeatures.FaceWidth += MultiViews[i].FaceWidth;
        AveragedFeatures.FaceHeight += MultiViews[i].FaceHeight;
        AveragedFeatures.EyeDistance += MultiViews[i].EyeDistance;
        AveragedFeatures.NoseLength += MultiViews[i].NoseLength;
        AveragedFeatures.NoseWidth += MultiViews[i].NoseWidth;
        AveragedFeatures.MouthWidth += MultiViews[i].MouthWidth;
        AveragedFeatures.MouthHeight += MultiViews[i].MouthHeight;
        AveragedFeatures.JawWidth += MultiViews[i].JawWidth;
        AveragedFeatures.ChinLength += MultiViews[i].ChinLength;
        AveragedFeatures.CheekboneWidth += MultiViews[i].CheekboneWidth;
        AveragedFeatures.ForeheadHeight += MultiViews[i].ForeheadHeight;
        AveragedFeatures.BrowHeight += MultiViews[i].BrowHeight;
    }

    const float InvCount = 1.0f / MultiViews.Num();
    AveragedFeatures.FaceWidth *= InvCount;
    AveragedFeatures.FaceHeight *= InvCount;
    AveragedFeatures.EyeDistance *= InvCount;
    AveragedFeatures.NoseLength *= InvCount;
    AveragedFeatures.NoseWidth *= InvCount;
    AveragedFeatures.MouthWidth *= InvCount;
    AveragedFeatures.MouthHeight *= InvCount;
    AveragedFeatures.JawWidth *= InvCount;
    AveragedFeatures.ChinLength *= InvCount;
    AveragedFeatures.CheekboneWidth *= InvCount;
    AveragedFeatures.ForeheadHeight *= InvCount;
    AveragedFeatures.BrowHeight *= InvCount;

    FFacialLandmarkData Dummy;
    ReconstructFace(AveragedFeatures, Dummy);
    ReconstructedFace.Quality = FMath::Min(ReconstructedFace.Quality + 0.1f, 1.0f);
}

void ULesFightFaceReconstructor::EstimateMissingFeatures(const FFaceFeatureData& PartialData)
{
    FFaceFeatureData Estimated = PartialData;

    if (FMath::IsNearlyZero(Estimated.FaceWidth))
    {
        Estimated.FaceWidth = Estimated.JawWidth * 1.6f;
    }
    if (FMath::IsNearlyZero(Estimated.FaceHeight))
    {
        Estimated.FaceHeight = Estimated.NoseLength * 3.5f;
    }
    if (FMath::IsNearlyZero(Estimated.EyeDistance))
    {
        Estimated.EyeDistance = Estimated.FaceWidth * 0.3f;
    }
    if (FMath::IsNearlyZero(Estimated.MouthWidth))
    {
        Estimated.MouthWidth = Estimated.FaceWidth * 0.4f;
    }
    if (FMath::IsNearlyZero(Estimated.CheekboneWidth))
    {
        Estimated.CheekboneWidth = Estimated.FaceWidth * 0.8f;
    }
    if (FMath::IsNearlyZero(Estimated.JawWidth))
    {
        Estimated.JawWidth = Estimated.FaceWidth * 0.7f;
    }

    FFacialLandmarkData Dummy;
    ReconstructFace(Estimated, Dummy);
}
