#include "LesFightBodyReconstructor.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightBodyReconstructor::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bBodyGenerated = false;
    BodyVertexPositions.Empty();
    BodyTriangles.Empty();
    BodyMorphValues.Empty();
}

void ULesFightBodyReconstructor::ReconstructBody(const FBodyProportionData& Proportions)
{
    BodyVertexPositions.Empty();
    BodyTriangles.Empty();

    TMap<EBodyMorphType, float> Adjustments;
    Adjustments.Add(EBodyMorphType::Height, Proportions.EstimatedHeight / 180.0f);
    Adjustments.Add(EBodyMorphType::ShoulderWidth, Proportions.ShoulderWidth / 60.0f);
    Adjustments.Add(EBodyMorphType::ChestSize, Proportions.ChestCircumference / 130.0f);
    Adjustments.Add(EBodyMorphType::WaistSize, Proportions.WaistCircumference / 120.0f);
    Adjustments.Add(EBodyMorphType::HipWidth, Proportions.HipCircumference / 120.0f);
    Adjustments.Add(EBodyMorphType::ArmLength, Proportions.ArmLength / 100.0f);
    Adjustments.Add(EBodyMorphType::LegLength, Proportions.LegLength / 120.0f);
    Adjustments.Add(EBodyMorphType::NeckSize, Proportions.NeckLength / 20.0f);
    AdjustBodyProportions(Adjustments);

    const int32 Segments = 24 + DetailLevel * 4;
    const int32 Rings = 12 + DetailLevel * 2;
    const float BodyHeight = Proportions.EstimatedHeight > 0.0f ? Proportions.EstimatedHeight : 170.0f;
    const float BodyRadius = 15.0f;

    BodyVertexPositions.Reserve(Segments * Rings);
    for (int32 Ring = 0; Ring < Rings; ++Ring)
    {
        float V = (float)Ring / (float)(Rings - 1);
        float Y = (V - 0.5f) * BodyHeight;
        float RadiusScale = 1.0f - 0.3f * FMath::Abs(V - 0.5f) * 2.0f;

        if (V < 0.3f)
        {
            RadiusScale *= 0.6f + 0.4f * (V / 0.3f);
        }
        else if (V > 0.7f)
        {
            RadiusScale *= 0.5f + 0.5f * ((1.0f - V) / 0.3f);
        }

        float MorphY = BodyMorphValues.FindRef(EBodyMorphType::Height);
        float MorphShoulder = BodyMorphValues.FindRef(EBodyMorphType::ShoulderWidth);

        for (int32 Seg = 0; Seg < Segments; ++Seg)
        {
            float U = (float)Seg / (float)(Segments - 1);
            float Angle = U * 2.0f * PI;

            float FinalRadius = BodyRadius * RadiusScale * (1.0f + 0.2f * MorphShoulder);
            if (V > 0.4f && V < 0.6f)
            {
                float WaistVal = BodyMorphValues.FindRef(EBodyMorphType::WaistSize);
                FinalRadius *= 1.0f + 0.3f * WaistVal;
            }

            FVector Vertex(
                FinalRadius * FMath::Cos(Angle),
                Y * (1.0f + 0.5f * MorphY),
                FinalRadius * FMath::Sin(Angle)
            );

            BodyVertexPositions.Add(Vertex);
        }
    }

    BodyTriangles.Reserve((Segments - 1) * (Rings - 1) * 6);
    for (int32 Ring = 0; Ring < Rings - 1; ++Ring)
    {
        for (int32 Seg = 0; Seg < Segments - 1; ++Seg)
        {
            int32 TL = Ring * Segments + Seg;
            int32 TR = Ring * Segments + Seg + 1;
            int32 BL = (Ring + 1) * Segments + Seg;
            int32 BR = (Ring + 1) * Segments + Seg + 1;

            BodyTriangles.Add(TL);
            BodyTriangles.Add(BL);
            BodyTriangles.Add(TR);

            BodyTriangles.Add(TR);
            BodyTriangles.Add(BL);
            BodyTriangles.Add(BR);
        }
    }

    bBodyGenerated = true;
}

FBodyMeshData ULesFightBodyReconstructor::GetBodyMeshData() const
{
    FBodyMeshData MeshData;
    MeshData.VertexPositions = BodyVertexPositions;
    MeshData.TriangleIndices = BodyTriangles;

    MeshData.UVCoordinates.Reserve(BodyVertexPositions.Num());
    for (int32 i = 0; i < BodyVertexPositions.Num(); ++i)
    {
        MeshData.UVCoordinates.Add(FVector2D(0.0f, 0.0f));
    }

    MeshData.Normals.Reserve(BodyVertexPositions.Num());
    for (const FVector& Vert : BodyVertexPositions)
    {
        MeshData.Normals.Add(Vert.GetSafeNormal());
    }

    MeshData.MeshDataReference = TEXT("BodyMesh_Generated");
    return MeshData;
}

void ULesFightBodyReconstructor::AdjustBodyProportions(const TMap<EBodyMorphType, float>& Adjustments)
{
    for (const auto& Entry : Adjustments)
    {
        BodyMorphValues.Add(Entry.Key, Entry.Value);
    }
}

FString ULesFightBodyReconstructor::GenerateCharacterMesh(const F3DFaceReconstructionData& Face, const FBodyProportionData& Body)
{
    ReconstructBody(Body);

    TArray<FVector> CombinedVerts;
    CombinedVerts.Append(Face.VertexPositions);
    CombinedVerts.Append(BodyVertexPositions);

    int32 FaceVertCount = Face.VertexPositions.Num();
    TArray<int32> CombinedTris;
    CombinedTris.Append(Face.TriangleIndices);
    for (int32 Tri : BodyTriangles)
    {
        CombinedTris.Add(Tri + FaceVertCount);
    }

    FString MeshRef = FString::Printf(TEXT("CombinedMesh_Face%d_Body%d"), FaceVertCount, BodyVertexPositions.Num());
    return MeshRef;
}

void ULesFightBodyReconstructor::SetBodyDetailLevel(int32 Level)
{
    DetailLevel = FMath::Clamp(Level, 1, 10);
}
