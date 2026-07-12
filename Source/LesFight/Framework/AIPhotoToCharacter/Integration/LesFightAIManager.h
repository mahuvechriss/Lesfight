#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightAIManager.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ULesFightAIManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAIManager();

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    bool StartGenerationFromPhoto(const FString& PhotoPath, EImageType Type = EImageType::FrontFace);

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    bool StartGenerationFromMultiplePhotos(const TArray<FString>& PhotoPaths);

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void CancelGeneration();

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    bool IsGenerating() const;

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    FAIPipelineProgress GetGenerationProgress() const;

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    FAICharacterGenerationResult GetGenerationResult() const;

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    bool ApplyResultToCharacter(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    bool HasGenerationResult() const;

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void SetGenerationQuality(EAIGenerationQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    EAIGenerationQuality GetGenerationQuality() const;

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void EnablePrivacyMode(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    bool IsPrivacyModeEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void SetReferenceHeight(float HeightCM);

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightAIPipelineManager* GetPipelineManager() const { return PipelineManager; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightFaceDetector* GetFaceDetector() const { return FaceDetector; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightLandmarkDetector* GetLandmarkDetector() const { return LandmarkDetector; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightFeatureExtractor* GetFeatureExtractor() const { return FeatureExtractor; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightBodyEstimator* GetBodyEstimator() const { return BodyEstimator; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightFaceReconstructor* GetFaceReconstructor() const { return FaceReconstructor; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightBodyReconstructor* GetBodyReconstructor() const { return BodyReconstructor; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightTextureGenerator* GetTextureGenerator() const { return TextureGenerator; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightMeshAdapter* GetMeshAdapter() const { return MeshAdapter; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightSkeletonMapper* GetSkeletonMapper() const { return SkeletonMapper; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightBlendShapeGenerator* GetBlendShapeGenerator() const { return BlendShapeGenerator; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightHairGenerator* GetHairGenerator() const { return HairGenerator; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightAIResultEditor* GetResultEditor() const { return ResultEditor; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightPrivacyManager* GetPrivacyManager() const { return PrivacyManager; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightImageStore* GetImageStore() const { return ImageStore; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightAICharReplication* GetReplication() const { return Replication; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightAIPerformance* GetPerformance() const { return Performance; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightAIDevTools* GetDevTools() const { return DevTools; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightImageUploadSystem* GetUploadSystem() const { return UploadSystem; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightImageValidator* GetValidator() const { return Validator; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightImagePreprocessor* GetPreprocessor() const { return Preprocessor; }

    UFUNCTION(BlueprintPure, Category = "AICharacter|Subsystems")
    class ULesFightStyleRecommender* GetStyleRecommender() const { return StyleRecommender; }

    UFUNCTION(BlueprintCallable, Category = "AICharacter|Manager")
    void SetCharCreationManager(class ULesFightCharCreationManager* InCharManager);

    UFUNCTION(BlueprintPure, Category = "AICharacter|Manager")
    class ULesFightCharCreationManager* GetCharCreationManager() const { return CharCreationManager; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightAIPipelineManager* PipelineManager;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightImageUploadSystem* UploadSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightImageValidator* Validator;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightImagePreprocessor* Preprocessor;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightFaceDetector* FaceDetector;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightLandmarkDetector* LandmarkDetector;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightFeatureExtractor* FeatureExtractor;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightBodyEstimator* BodyEstimator;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightFaceReconstructor* FaceReconstructor;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightBodyReconstructor* BodyReconstructor;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightTextureGenerator* TextureGenerator;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightMeshAdapter* MeshAdapter;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightSkeletonMapper* SkeletonMapper;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightBlendShapeGenerator* BlendShapeGenerator;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightHairGenerator* HairGenerator;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightAIResultEditor* ResultEditor;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightStyleRecommender* StyleRecommender;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightPrivacyManager* PrivacyManager;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightImageStore* ImageStore;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightAICharReplication* Replication;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightAIPerformance* Performance;

    UPROPERTY(BlueprintReadOnly, Category = "Subsystems")
    class ULesFightAIDevTools* DevTools;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    class ULesFightCharCreationManager* CharCreationManager;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bInitialized;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FAICharacterGenerationResult LastGenerationResult;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EAIGenerationQuality GenerationQuality;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightAIPipelineManager> PipelineManagerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightFaceDetector> FaceDetectorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightLandmarkDetector> LandmarkDetectorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightFeatureExtractor> FeatureExtractorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightBodyEstimator> BodyEstimatorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightFaceReconstructor> FaceReconstructorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightBodyReconstructor> BodyReconstructorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightTextureGenerator> TextureGeneratorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightMeshAdapter> MeshAdapterClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightSkeletonMapper> SkeletonMapperClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightBlendShapeGenerator> BlendShapeGeneratorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightHairGenerator> HairGeneratorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightAIResultEditor> ResultEditorClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightStyleRecommender> StyleRecommenderClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightPrivacyManager> PrivacyManagerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightImageStore> ImageStoreClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightAICharReplication> ReplicationClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightAIPerformance> PerformanceClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    TSubclassOf<class ULesFightAIDevTools> DevToolsClass;

private:
    template<typename T>
    T* CreateSubsystem(TSubclassOf<T> Class, T*& OutPtr);
};
