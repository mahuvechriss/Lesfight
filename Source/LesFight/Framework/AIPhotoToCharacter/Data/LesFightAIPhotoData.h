#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UObject/NoExportTypes.h"
#include "Framework/CharacterCreation/Data/LesFightCharacterCreationData.h"
#include "LesFightAIPhotoData.generated.h"

UENUM(BlueprintType)
enum class EAIPipelineStage : uint8
{
    Idle,
    ImageUploaded,
    Validating,
    ValidationComplete,
    Preprocessing,
    FaceDetection,
    LandmarkDetection,
    FeatureExtraction,
    BodyEstimation,
    FaceReconstruction,
    BodyReconstruction,
    TextureGeneration,
    HairGeneration,
    MeshIntegration,
    SkeletonMapping,
    BlendShapeGeneration,
    PreviewReady,
    UserEditing,
    Finalizing,
    Complete,
    Failed,
    MAX
};

UENUM(BlueprintType)
enum class EImageType : uint8
{
    FrontFace,
    SideProfile,
    FullBody,
    MultiplePhotos,
    VideoCapture,
    MAX
};

UENUM(BlueprintType)
enum class EImageQuality : uint8
{
    Poor,
    Acceptable,
    Good,
    Excellent,
    MAX
};

UENUM(BlueprintType)
enum class ELightingCondition : uint8
{
    Unknown,
    WellLit,
    LowLight,
    Backlit,
    HarshShadow,
    Mixed,
    MAX
};

UENUM(BlueprintType)
enum class EFaceVisibility : uint8
{
    NotVisible,
    Partial,
    Profile,
    FullFrontal,
    MAX
};

UENUM(BlueprintType)
enum class EAIGenerationQuality : uint8
{
    Draft,
    Standard,
    High,
    Ultra,
    MAX
};

UENUM(BlueprintType)
enum class EFacialExpression : uint8
{
    Neutral,
    Happy,
    Angry,
    Sad,
    Surprised,
    Fearful,
    Disgusted,
    Contempt,
    MAX
};

UENUM(BlueprintType)
enum class EHairDetectionType : uint8
{
    Unknown,
    Short,
    Medium,
    Long,
    Bald,
    Curly,
    Straight,
    Wavy,
    Ponytail,
    Bun,
    Braids,
    Shaved,
    MAX
};

UENUM(BlueprintType)
enum class ESkinDetailLevel : uint8
{
    Low,
    Medium,
    High,
    Ultra,
    MAX
};

USTRUCT(BlueprintType)
struct FImageUploadResult
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ImagePath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EImageType ImageType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EImageQuality Quality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ELightingCondition Lighting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFaceVisibility FaceVisibility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Width;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Height;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FileSizeMB;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bValid;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ValidationMessages;
};

USTRUCT(BlueprintType)
struct FFacialLandmarkData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D LeftEyeCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D RightEyeCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D NoseTip;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D NoseBridge;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D MouthCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D MouthLeftCorner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D MouthRightCorner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D ChinTip;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D LeftJawCorner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D RightJawCorner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D LeftEyebrowInner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D LeftEyebrowOuter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D RightEyebrowInner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D RightEyebrowOuter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> FaceContour;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> LeftEyeContour;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> RightEyeContour;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> LipsContour;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Confidence;
};

USTRUCT(BlueprintType)
struct FFaceFeatureData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FaceWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FaceHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EyeDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float NoseLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float NoseWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MouthWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MouthHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float JawWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChinLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CheekboneWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ForeheadHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EyeShapeScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BrowHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FLinearColor> SkinToneSamples;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor AverageSkinTone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkinRoughnessEstimate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SkinGlossEstimate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Confidence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EFacialExpression DetectedExpression;
};

USTRUCT(BlueprintType)
struct FHairDetectionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EHairDetectionType DetectedStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor DetectedColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HairLengthEstimate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HairDensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D HairRegionTop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D HairRegionBottom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Confidence;
};

USTRUCT(BlueprintType)
struct FBodyProportionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EstimatedHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ShoulderWidth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ChestCircumference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WaistCircumference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HipCircumference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ArmLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LegLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float NeckLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TorsoLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Confidence;
};

USTRUCT(BlueprintType)
struct F3DFaceReconstructionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> VertexPositions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<int32> TriangleIndices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> UVCoordinates;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector> Normals;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, float> BlendShapeWeights;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EFaceMorphType, float> MorphTargetValues;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MeshDataReference;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Quality;
};

USTRUCT(BlueprintType)
struct FGeneratedTextureData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DiffuseMapPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NormalMapPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RoughnessMapPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SpecularMapPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SubsurfaceMapPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TextureResolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasScars;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasMarks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVector2D> BlemishPositions;
};

USTRUCT(BlueprintType)
struct FAICharacterGenerationResult
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSuccess;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FCharacterCustomizationPreset CharacterPreset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    F3DFaceReconstructionData FaceData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGeneratedTextureData Textures;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBodyProportionData BodyProportions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FHairDetectionData HairData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> GeneratedMeshPaths;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName GeneratedCharacterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GenerationTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ProcessingLog;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ErrorMessage;
};

USTRUCT(BlueprintType)
struct FAIPipelineProgress
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAIPipelineStage CurrentStage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ProgressPercent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StageDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EstimatedTimeRemaining;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsProcessing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> StageLog;
};

USTRUCT(BlueprintType)
struct FPrivacySettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUserConsentGiven;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAutoDeleteImages;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLocalProcessingOnly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ImageRetentionMinutes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime ConsentTimestamp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAnonymizeData;
};

USTRUCT(BlueprintType)
struct FAIDevReportEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Timestamp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Message;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Category;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bWarning;
};

UCLASS(BlueprintType)
class ULesFightAIPhotoDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    ULesFightAIPhotoDataAsset();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Generation")
    EAIGenerationQuality DefaultQuality;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Generation")
    int32 MaxTextureResolution;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Generation")
    int32 MaxImageFileSizeMB;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Generation")
    TArray<EImageType> SupportedImageTypes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Generation")
    float MinFaceVisibilityThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Generation")
    float MinImageQualityThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Privacy")
    int32 DefaultImageRetentionMinutes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Privacy")
    bool bRequireConsent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    int32 MaxMeshTriangles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Performance")
    float ProcessingTimeoutSeconds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reconstruction")
    bool bGenerateBlendShapes;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reconstruction")
    bool bGenerateBody;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reconstruction")
    bool bGenerateHair;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Reconstruction")
    int32 BlendShapeCount;
};
