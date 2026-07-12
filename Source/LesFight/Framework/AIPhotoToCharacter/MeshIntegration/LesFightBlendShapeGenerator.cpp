#include "LesFightBlendShapeGenerator.h"
#include "Pipeline/LesFightAIPipelineManager.h"

void ULesFightBlendShapeGenerator::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bBlendShapesGenerated = false;
    BlendShapeNames.Empty();
    BlendShapeDeltas.Empty();
    BlendShapeRanges.Empty();
    BaseVertexPositions.Empty();
}

TArray<FVector> ULesFightBlendShapeGenerator::GenerateSimulatedDeltas(int32 VertexCount, float Magnitude, int32 Seed) const
{
    TArray<FVector> Deltas;
    Deltas.Reserve(VertexCount);
    FRandomStream Stream(Seed);
    for (int32 i = 0; i < VertexCount; ++i)
    {
        Deltas.Add(FVector(
            Stream.FRandRange(-Magnitude, Magnitude),
            Stream.FRandRange(-Magnitude, Magnitude),
            Stream.FRandRange(-Magnitude, Magnitude)
        ));
    }
    return Deltas;
}

void ULesFightBlendShapeGenerator::AddBlendShape(FName Name, const TArray<FVector>& Deltas, float Range)
{
    BlendShapeNames.Add(Name);
    BlendShapeDeltas.Add(Name, Deltas);
    BlendShapeRanges.Add(Name, Range);
}

void ULesFightBlendShapeGenerator::GenerateBlendShapesFromFace(const F3DFaceReconstructionData& FaceData)
{
    BaseVertexPositions = FaceData.VertexPositions;
    int32 VertCount = BaseVertexPositions.Num();
    if (VertCount == 0) VertCount = 5184;

    BlendShapeNames.Empty();
    BlendShapeDeltas.Empty();
    BlendShapeRanges.Empty();

    int32 SeedBase = 100;

    TArray<FName> JawCheekNames = {
        TEXT("JawOpen"), TEXT("JawClamp"), TEXT("JawLeft"), TEXT("JawRight"),
        TEXT("JawForward"), TEXT("CheekPuffLeft"), TEXT("CheekPuffRight"),
        TEXT("CheekSuckLeft"), TEXT("CheekSuckRight"), TEXT("JawCheekBlend_L"),
        TEXT("JawCheekBlend_R"), TEXT("CheekRaise_L"), TEXT("CheekRaise_R"),
        TEXT("JawThrust"), TEXT("MouthStretch"), TEXT("JawSideways")
    };
    for (int32 i = 0; i < JawCheekNames.Num(); ++i)
    {
        AddBlendShape(JawCheekNames[i], GenerateSimulatedDeltas(VertCount, 0.8f, SeedBase + i), 1.0f);
    }

    TArray<FName> MouthLipNames = {
        TEXT("LipPucker"), TEXT("LipFunnel"), TEXT("LipRollUpper"), TEXT("LipRollLower"),
        TEXT("LipStretch"), TEXT("LipCornerPuller_L"), TEXT("LipCornerPuller_R"),
        TEXT("LipCornerDepressor_L"), TEXT("LipCornerDepressor_R"),
        TEXT("UpperLipRaise_L"), TEXT("UpperLipRaise_R"),
        TEXT("LowerLipDepressor_L"), TEXT("LowerLipDepressor_R")
    };
    for (int32 i = 0; i < MouthLipNames.Num(); ++i)
    {
        AddBlendShape(MouthLipNames[i], GenerateSimulatedDeltas(VertCount, 0.6f, SeedBase + 16 + i), 1.0f);
    }

    TArray<FName> EyeNames = {
        TEXT("EyeBlinkLeft"), TEXT("EyeBlinkRight"), TEXT("EyeSquint_L"), TEXT("EyeSquint_R"),
        TEXT("EyeWide_L"), TEXT("EyeWide_R"), TEXT("EyeLookUp"), TEXT("EyeLookDown")
    };
    for (int32 i = 0; i < EyeNames.Num(); ++i)
    {
        AddBlendShape(EyeNames[i], GenerateSimulatedDeltas(VertCount, 0.4f, SeedBase + 28 + i), 1.0f);
    }

    TArray<FName> EyebrowNames = {
        TEXT("BrowRaiseInner_L"), TEXT("BrowRaiseInner_R"),
        TEXT("BrowRaiseOuter_L"), TEXT("BrowRaiseOuter_R"),
        TEXT("BrowLower_L"), TEXT("BrowLower_R"),
        TEXT("BrowKnitting"), TEXT("BrowCompression")
    };
    for (int32 i = 0; i < EyebrowNames.Num(); ++i)
    {
        AddBlendShape(EyebrowNames[i], GenerateSimulatedDeltas(VertCount, 0.3f, SeedBase + 36 + i), 1.0f);
    }

    TArray<FName> NoseEarNames = {
        TEXT("NoseScrunch"), TEXT("NoseWrinkle"), TEXT("NoseFlare_L"), TEXT("NoseFlare_R"),
        TEXT("NoseSneer_L"), TEXT("NoseSneer_R"),
        TEXT("EarPull_L"), TEXT("EarPull_R")
    };
    for (int32 i = 0; i < NoseEarNames.Num(); ++i)
    {
        AddBlendShape(NoseEarNames[i], GenerateSimulatedDeltas(VertCount, 0.3f, SeedBase + 44 + i), 1.0f);
    }

    bBlendShapesGenerated = true;
}

TArray<FVector> ULesFightBlendShapeGenerator::GetBlendShapeData(int32 Index) const
{
    if (BlendShapeNames.IsValidIndex(Index))
    {
        FName Name = BlendShapeNames[Index];
        if (const TArray<FVector>* Deltas = BlendShapeDeltas.Find(Name))
        {
            return *Deltas;
        }
    }
    return TArray<FVector>();
}

void ULesFightBlendShapeGenerator::ApplyBlendShapeToMesh(int32 ShapeIndex, float Weight)
{
}

void ULesFightBlendShapeGenerator::GenerateExpressionBlendShapes()
{
    int32 VertCount = BaseVertexPositions.Num();
    if (VertCount == 0) VertCount = 5184;

    TMap<FName, int32> Expressions;
    Expressions.Add(TEXT("Expression_Happy"), 200);
    Expressions.Add(TEXT("Expression_Angry"), 201);
    Expressions.Add(TEXT("Expression_Sad"), 202);
    Expressions.Add(TEXT("Expression_Surprised"), 203);
    Expressions.Add(TEXT("Expression_Fearful"), 204);
    Expressions.Add(TEXT("Expression_Disgusted"), 205);
    Expressions.Add(TEXT("Expression_Contempt"), 206);

    for (const auto& Entry : Expressions)
    {
        AddBlendShape(Entry.Key, GenerateSimulatedDeltas(VertCount, 1.2f, Entry.Value), 1.5f);
    }
}

void ULesFightBlendShapeGenerator::GenerateVisemeBlendShapes()
{
    int32 VertCount = BaseVertexPositions.Num();
    if (VertCount == 0) VertCount = 5184;

    TArray<FName> Visemes = {
        TEXT("Viseme_Silence"), TEXT("Viseme_AA"), TEXT("Viseme_EH"), TEXT("Viseme_IH"),
        TEXT("Viseme_OH"), TEXT("Viseme_UW"), TEXT("Viseme_MBP"), TEXT("Viseme_FV"),
        TEXT("Viseme_TH"), TEXT("Viseme_SS"), TEXT("Viseme_KK"), TEXT("Viseme_NG"),
        TEXT("Viseme_SH"), TEXT("Viseme_W"), TEXT("Viseme_L")
    };

    for (int32 i = 0; i < Visemes.Num(); ++i)
    {
        AddBlendShape(Visemes[i], GenerateSimulatedDeltas(VertCount, 0.9f, 300 + i), 1.2f);
    }
}

bool ULesFightBlendShapeGenerator::TestBlendShapeCompatibility() const
{
    return BlendShapeNames.Num() > 0 && BlendShapeNames.Num() == BlendShapeDeltas.Num();
}
