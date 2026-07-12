#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "Data/LesFightAIPhotoData.h"
#include "LesFightImageUploadSystem.h"
#include "LesFightImageValidator.h"
#include "LesFightImagePreprocessor.h"
#include "LesFightAIPipelineManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPipelineStageChanged, EAIPipelineStage, NewStage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPipelineComplete, bool, bSuccess);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIPipelineManager : public UObject, public FTickableGameObject
{
    GENERATED_BODY()

public:
    ULesFightAIPipelineManager();
    virtual ~ULesFightAIPipelineManager();

    void Initialize(class ULesFightAIManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Pipeline")
    void StartPipeline(EImageType Type);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Pipeline")
    void CancelPipeline();

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Pipeline")
    FAIPipelineProgress GetProgress() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Pipeline")
    bool IsPipelineRunning() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Pipeline")
    FAICharacterGenerationResult GetResult() const;

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Pipeline")
    void SetQuality(EAIGenerationQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "AI Photo|Pipeline")
    EAIPipelineStage GetStage() const;

    UPROPERTY(BlueprintAssignable, Category = "AI Photo|Pipeline")
    FOnPipelineStageChanged OnPipelineStageChanged;

    UPROPERTY(BlueprintAssignable, Category = "AI Photo|Pipeline")
    FOnPipelineComplete OnPipelineComplete;

    virtual void Tick(float DeltaTime) override;
    virtual ETickableTickType GetTickableTickType() const override;
    virtual bool IsTickable() const override;
    virtual TStatId GetStatId() const override;

protected:
    UPROPERTY(VisibleInstanceOnly, Category = "Pipeline")
    TObjectPtr<ULesFightImageUploadSystem> UploadSystem;

    UPROPERTY(VisibleInstanceOnly, Category = "Pipeline")
    TObjectPtr<ULesFightImageValidator> Validator;

    UPROPERTY(VisibleInstanceOnly, Category = "Pipeline")
    TObjectPtr<ULesFightImagePreprocessor> Preprocessor;

    UPROPERTY(VisibleInstanceOnly, Category = "Pipeline")
    FAIPipelineProgress CurrentProgress;

    UPROPERTY(VisibleInstanceOnly, Category = "Pipeline")
    FAICharacterGenerationResult CurrentResult;

    UPROPERTY(EditDefaultsOnly, Category = "Pipeline")
    EAIGenerationQuality GenerationQuality = EAIGenerationQuality::Standard;

    UPROPERTY(Transient)
    bool bPipelineRunning = false;

    UPROPERTY(EditDefaultsOnly, Category = "Pipeline")
    TMap<EAIPipelineStage, float> StageWeights;

    void RunStage(EAIPipelineStage Stage);
    void CompletePipeline(bool bSuccess);
    void FailPipeline(const FString& Error);

private:
    TWeakObjectPtr<class ULesFightAIManager> OwnerManager;
    float PipelineStartTime = 0.0f;
    int32 CurrentStageIndex = 0;
    TArray<EAIPipelineStage> PipelineStages;
    float TotalPipelineDuration = 30.0f;
};
