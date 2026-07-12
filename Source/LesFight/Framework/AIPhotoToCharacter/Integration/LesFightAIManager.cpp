#include "LesFightAIManager.h"
#include "Pipeline/LesFightAIPipelineManager.h"
#include "Pipeline/LesFightImageUploadSystem.h"
#include "Pipeline/LesFightImageValidator.h"
#include "Pipeline/LesFightImagePreprocessor.h"
#include "ComputerVision/LesFightFaceDetector.h"
#include "ComputerVision/LesFightLandmarkDetector.h"
#include "ComputerVision/LesFightFeatureExtractor.h"
#include "ComputerVision/LesFightBodyEstimator.h"
#include "Reconstruction/LesFightFaceReconstructor.h"
#include "Reconstruction/LesFightBodyReconstructor.h"
#include "Reconstruction/LesFightTextureGenerator.h"
#include "MeshIntegration/LesFightMeshAdapter.h"
#include "MeshIntegration/LesFightSkeletonMapper.h"
#include "MeshIntegration/LesFightBlendShapeGenerator.h"
#include "MeshIntegration/LesFightHairGenerator.h"
#include "UserEditing/LesFightAIResultEditor.h"
#include "UserEditing/LesFightStyleRecommender.h"
#include "Privacy/LesFightPrivacyManager.h"
#include "Privacy/LesFightImageStore.h"
#include "Multiplayer/LesFightAICharReplication.h"
#include "Performance/LesFightAIPerformance.h"
#include "Testing/LesFightAIDevTools.h"
#include "Framework/CharacterCreation/Integration/LesFightCharCreationManager.h"

ULesFightAIManager::ULesFightAIManager()
    : PipelineManager(nullptr)
    , UploadSystem(nullptr)
    , Validator(nullptr)
    , Preprocessor(nullptr)
    , FaceDetector(nullptr)
    , LandmarkDetector(nullptr)
    , FeatureExtractor(nullptr)
    , BodyEstimator(nullptr)
    , FaceReconstructor(nullptr)
    , BodyReconstructor(nullptr)
    , TextureGenerator(nullptr)
    , MeshAdapter(nullptr)
    , SkeletonMapper(nullptr)
    , BlendShapeGenerator(nullptr)
    , HairGenerator(nullptr)
    , ResultEditor(nullptr)
    , StyleRecommender(nullptr)
    , PrivacyManager(nullptr)
    , ImageStore(nullptr)
    , Replication(nullptr)
    , Performance(nullptr)
    , DevTools(nullptr)
    , CharCreationManager(nullptr)
    , bInitialized(false)
    , GenerationQuality(EAIGenerationQuality::Standard)
{
}

void ULesFightAIManager::Initialize()
{
    if (bInitialized) return;

    PipelineManager = CreateSubsystem(PipelineManagerClass, PipelineManager);
    UploadSystem = CreateSubsystem(TSubclassOf<ULesFightImageUploadSystem>(), UploadSystem);
    Validator = CreateSubsystem(TSubclassOf<ULesFightImageValidator>(), Validator);
    Preprocessor = CreateSubsystem(TSubclassOf<ULesFightImagePreprocessor>(), Preprocessor);
    FaceDetector = CreateSubsystem(FaceDetectorClass, FaceDetector);
    LandmarkDetector = CreateSubsystem(LandmarkDetectorClass, LandmarkDetector);
    FeatureExtractor = CreateSubsystem(FeatureExtractorClass, FeatureExtractor);
    BodyEstimator = CreateSubsystem(BodyEstimatorClass, BodyEstimator);
    FaceReconstructor = CreateSubsystem(FaceReconstructorClass, FaceReconstructor);
    BodyReconstructor = CreateSubsystem(BodyReconstructorClass, BodyReconstructor);
    TextureGenerator = CreateSubsystem(TextureGeneratorClass, TextureGenerator);
    MeshAdapter = CreateSubsystem(MeshAdapterClass, MeshAdapter);
    SkeletonMapper = CreateSubsystem(SkeletonMapperClass, SkeletonMapper);
    BlendShapeGenerator = CreateSubsystem(BlendShapeGeneratorClass, BlendShapeGenerator);
    HairGenerator = CreateSubsystem(HairGeneratorClass, HairGenerator);
    ResultEditor = CreateSubsystem(ResultEditorClass, ResultEditor);
    StyleRecommender = CreateSubsystem(StyleRecommenderClass, StyleRecommender);
    PrivacyManager = CreateSubsystem(PrivacyManagerClass, PrivacyManager);
    ImageStore = CreateSubsystem(ImageStoreClass, ImageStore);
    Replication = CreateSubsystem(ReplicationClass, Replication);
    Performance = CreateSubsystem(PerformanceClass, Performance);
    DevTools = CreateSubsystem(DevToolsClass, DevTools);

    if (PipelineManager) PipelineManager->Initialize(this);
    if (UploadSystem) UploadSystem->Initialize(PipelineManager);
    if (Validator) Validator->Initialize(PipelineManager);
    if (Preprocessor) Preprocessor->Initialize(PipelineManager);
    if (FaceDetector) FaceDetector->Initialize(PipelineManager);
    if (LandmarkDetector) LandmarkDetector->Initialize(PipelineManager);
    if (FeatureExtractor) FeatureExtractor->Initialize(PipelineManager);
    if (BodyEstimator) BodyEstimator->Initialize(PipelineManager);
    if (FaceReconstructor) FaceReconstructor->Initialize(PipelineManager);
    if (BodyReconstructor) BodyReconstructor->Initialize(PipelineManager);
    if (TextureGenerator) TextureGenerator->Initialize(PipelineManager);
    if (MeshAdapter) MeshAdapter->Initialize(PipelineManager);
    if (SkeletonMapper) SkeletonMapper->Initialize(PipelineManager);
    if (BlendShapeGenerator) BlendShapeGenerator->Initialize(PipelineManager);
    if (HairGenerator) HairGenerator->Initialize(PipelineManager);
    if (ResultEditor) ResultEditor->Initialize(this);
    if (StyleRecommender) StyleRecommender->Initialize(this);
    if (PrivacyManager) PrivacyManager->Initialize(this);
    if (ImageStore) ImageStore->Initialize(PipelineManager);
    if (Replication) Replication->Initialize(this);
    if (Performance) Performance->Initialize(this);
    if (DevTools) DevTools->Initialize(this);

    bInitialized = true;
}

void ULesFightAIManager::Shutdown()
{
    if (!bInitialized) return;
    bInitialized = false;
}

void ULesFightAIManager::Tick(float DeltaTime)
{
    if (!bInitialized) return;

    if (PipelineManager) PipelineManager->Tick(DeltaTime);
    if (Performance) Performance->StartPerformanceTracking();
}

bool ULesFightAIManager::StartGenerationFromPhoto(
    const FString& PhotoPath, EImageType Type)
{
    if (!bInitialized || !PipelineManager || !UploadSystem) return false;

    FImageUploadResult UploadResult = UploadSystem->UploadImage(PhotoPath, Type);
    if (!UploadResult.bValid) return false;

    if (Validator && !Validator->ValidateImage(UploadResult))
    {
        return false;
    }

    if (!PrivacyManager || !PrivacyManager->HasUserConsent())
    {
        if (PrivacyManager) PrivacyManager->RequestUserConsent();
    }

    if (ImageStore)
    {
        FString StoredPath;
        ImageStore->StoreImage(PhotoPath, StoredPath);
    }

    PipelineManager->SetQuality(GenerationQuality);
    PipelineManager->StartPipeline(Type);
    return true;
}

bool ULesFightAIManager::StartGenerationFromMultiplePhotos(
    const TArray<FString>& PhotoPaths)
{
    if (!bInitialized || !PipelineManager || !UploadSystem) return false;

    bool bAnySuccess = false;
    for (const FString& Path : PhotoPaths)
    {
        FImageUploadResult Result = UploadSystem->UploadImage(Path, EImageType::MultiplePhotos);
        if (Result.bValid)
        {
            bAnySuccess = true;
            if (ImageStore)
            {
                FString StoredPath;
                ImageStore->StoreImage(Path, StoredPath);
            }
        }
    }

    if (bAnySuccess)
    {
        PipelineManager->SetQuality(GenerationQuality);
        PipelineManager->StartPipeline(EImageType::MultiplePhotos);
    }
    return bAnySuccess;
}

void ULesFightAIManager::CancelGeneration()
{
    if (PipelineManager) PipelineManager->CancelPipeline();
}

bool ULesFightAIManager::IsGenerating() const
{
    return PipelineManager ? PipelineManager->IsPipelineRunning() : false;
}

FAIPipelineProgress ULesFightAIManager::GetGenerationProgress() const
{
    return PipelineManager ? PipelineManager->GetProgress() : FAIPipelineProgress();
}

FAICharacterGenerationResult ULesFightAIManager::GetGenerationResult() const
{
    if (PipelineManager)
    {
        return PipelineManager->GetResult();
    }
    return LastGenerationResult;
}

bool ULesFightAIManager::ApplyResultToCharacter(FName CharacterID)
{
    if (!PipelineManager || !CharCreationManager) return false;

    FAICharacterGenerationResult Result = PipelineManager->GetResult();
    if (!Result.bSuccess) return false;

    FCharacterCustomizationPreset Preset = Result.CharacterPreset;

    if (FaceReconstructor)
    {
        Preset.FaceMorphs = FaceReconstructor->GetReconstructedData().MorphTargetValues;
    }
    if (HairGenerator)
    {
        Preset.Hair.HairColor = HairGenerator->GetHairColor();
    }
    if (BodyEstimator)
    {
        TMap<EBodyMorphType, float> BodyMorphs = BodyEstimator->GenerateBodyMorphTargets();
        Preset.BodyMorphs = BodyMorphs;
    }

    CharCreationManager->GetCreator()->SetCharacterData(CharacterID, Preset);
    CharCreationManager->SetActiveCharacter(CharacterID);

    if (ResultEditor)
    {
        ResultEditor->Initialize(this);
    }

    return true;
}

bool ULesFightAIManager::HasGenerationResult() const
{
    return PipelineManager ? PipelineManager->GetResult().bSuccess : false;
}

void ULesFightAIManager::SetGenerationQuality(EAIGenerationQuality Quality)
{
    GenerationQuality = Quality;
    if (PipelineManager) PipelineManager->SetQuality(Quality);
}

EAIGenerationQuality ULesFightAIManager::GetGenerationQuality() const
{
    return GenerationQuality;
}

void ULesFightAIManager::EnablePrivacyMode(bool bEnable)
{
    if (PrivacyManager)
    {
        PrivacyManager->SetLocalProcessingOnly(bEnable);
        PrivacyManager->SetAutoDeleteImages(bEnable);
    }
}

bool ULesFightAIManager::IsPrivacyModeEnabled() const
{
    return PrivacyManager ? PrivacyManager->IsLocalProcessingOnly() : true;
}

void ULesFightAIManager::SetReferenceHeight(float HeightCM)
{
    if (BodyEstimator) BodyEstimator->SetReferenceHeight(HeightCM);
}

void ULesFightAIManager::SetCharCreationManager(ULesFightCharCreationManager* InCharManager)
{
    CharCreationManager = InCharManager;
}

template<typename T>
T* ULesFightAIManager::CreateSubsystem(TSubclassOf<T> Class, T*& OutPtr)
{
    if (!Class)
    {
        Class = T::StaticClass();
    }
    OutPtr = NewObject<T>(this, Class);
    return OutPtr;
}
