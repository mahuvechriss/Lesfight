#include "LesFightAIPipelineManager.h"
#include "HAL/PlatformTime.h"

ULesFightAIPipelineManager::ULesFightAIPipelineManager()
{
    StageWeights =
    {
        {EAIPipelineStage::ImageUploaded, 0.05f},
        {EAIPipelineStage::Validating, 0.05f},
        {EAIPipelineStage::ValidationComplete, 0.02f},
        {EAIPipelineStage::Preprocessing, 0.08f},
        {EAIPipelineStage::FaceDetection, 0.10f},
        {EAIPipelineStage::LandmarkDetection, 0.08f},
        {EAIPipelineStage::FeatureExtraction, 0.07f},
        {EAIPipelineStage::BodyEstimation, 0.10f},
        {EAIPipelineStage::FaceReconstruction, 0.12f},
        {EAIPipelineStage::BodyReconstruction, 0.10f},
        {EAIPipelineStage::TextureGeneration, 0.08f},
        {EAIPipelineStage::HairGeneration, 0.05f},
        {EAIPipelineStage::MeshIntegration, 0.05f},
        {EAIPipelineStage::SkeletonMapping, 0.05f},
        {EAIPipelineStage::BlendShapeGeneration, 0.03f},
        {EAIPipelineStage::PreviewReady, 0.02f},
        {EAIPipelineStage::Finalizing, 0.05f}
    };

    PipelineStages =
    {
        EAIPipelineStage::ImageUploaded,
        EAIPipelineStage::Validating,
        EAIPipelineStage::ValidationComplete,
        EAIPipelineStage::Preprocessing,
        EAIPipelineStage::FaceDetection,
        EAIPipelineStage::LandmarkDetection,
        EAIPipelineStage::FeatureExtraction,
        EAIPipelineStage::BodyEstimation,
        EAIPipelineStage::FaceReconstruction,
        EAIPipelineStage::BodyReconstruction,
        EAIPipelineStage::TextureGeneration,
        EAIPipelineStage::HairGeneration,
        EAIPipelineStage::MeshIntegration,
        EAIPipelineStage::SkeletonMapping,
        EAIPipelineStage::BlendShapeGeneration,
        EAIPipelineStage::PreviewReady,
        EAIPipelineStage::Finalizing,
        EAIPipelineStage::Complete
    };
}

ULesFightAIPipelineManager::~ULesFightAIPipelineManager()
{
}

void ULesFightAIPipelineManager::Initialize(ULesFightAIManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;

    UploadSystem = NewObject<ULesFightImageUploadSystem>(this);
    UploadSystem->Initialize(this);

    Validator = NewObject<ULesFightImageValidator>(this);
    Validator->Initialize(this);

    Preprocessor = NewObject<ULesFightImagePreprocessor>(this);
    Preprocessor->Initialize(this);
}

void ULesFightAIPipelineManager::StartPipeline(EImageType Type)
{
    if (bPipelineRunning)
    {
        return;
    }

    bPipelineRunning = true;
    CurrentStageIndex = 0;
    PipelineStartTime = FPlatformTime::Seconds();

    CurrentProgress = FAIPipelineProgress();
    CurrentProgress.bIsProcessing = true;
    CurrentProgress.CurrentStage = EAIPipelineStage::Idle;

    CurrentResult = FAICharacterGenerationResult();
    CurrentResult.bSuccess = false;

    RunStage(PipelineStages[0]);
}

void ULesFightAIPipelineManager::CancelPipeline()
{
    bPipelineRunning = false;
    CurrentProgress.bIsProcessing = false;
    CurrentProgress.StageLog.Add(TEXT("Pipeline cancelled by user"));

    if (UploadSystem.IsValid())
    {
        UploadSystem->CancelUpload();
    }

    OnPipelineComplete.Broadcast(false);
}

FAIPipelineProgress ULesFightAIPipelineManager::GetProgress() const
{
    return CurrentProgress;
}

bool ULesFightAIPipelineManager::IsPipelineRunning() const
{
    return bPipelineRunning;
}

FAICharacterGenerationResult ULesFightAIPipelineManager::GetResult() const
{
    return CurrentResult;
}

void ULesFightAIPipelineManager::SetQuality(EAIGenerationQuality Quality)
{
    GenerationQuality = Quality;
}

EAIPipelineStage ULesFightAIPipelineManager::GetStage() const
{
    return CurrentProgress.CurrentStage;
}

void ULesFightAIPipelineManager::Tick(float DeltaTime)
{
    if (!bPipelineRunning)
    {
        return;
    }

    float Elapsed = static_cast<float>(FPlatformTime::Seconds() - PipelineStartTime);

    float TotalWeight = 0.0f;
    for (const auto& Pair : StageWeights)
    {
        TotalWeight += Pair.Value;
    }

    if (TotalWeight <= 0.0f)
    {
        return;
    }

    float CurrentCumulative = 0.0f;
    EAIPipelineStage TargetStage = EAIPipelineStage::Complete;
    bool bFound = false;

    for (const EAIPipelineStage& Stage : PipelineStages)
    {
        if (Stage == EAIPipelineStage::Complete)
        {
            if (!bFound)
            {
                TargetStage = Stage;
            }
            break;
        }

        CurrentCumulative += StageWeights[Stage];
        float StageEndTime = (CurrentCumulative / TotalWeight) * TotalPipelineDuration;

        if (Elapsed <= StageEndTime)
        {
            TargetStage = Stage;
            bFound = true;
            break;
        }
    }

    if (TargetStage != CurrentProgress.CurrentStage)
    {
        if (TargetStage == EAIPipelineStage::Complete)
        {
            CompletePipeline(true);
        }
        else
        {
            RunStage(TargetStage);
        }
    }
}

ETickableTickType ULesFightAIPipelineManager::GetTickableTickType() const
{
    return ETickableTickType::Conditional;
}

bool ULesFightAIPipelineManager::IsTickable() const
{
    return bPipelineRunning;
}

TStatId ULesFightAIPipelineManager::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(ULesFightAIPipelineManager, STATGROUP_Tickables);
}

void ULesFightAIPipelineManager::RunStage(EAIPipelineStage Stage)
{
    CurrentProgress.CurrentStage = Stage;
    CurrentProgress.bIsProcessing = true;

    float StageWeight = StageWeights.Contains(Stage) ? StageWeights[Stage] : 0.0f;
    float TotalWeight = 0.0f;
    for (const auto& Pair : StageWeights)
    {
        TotalWeight += Pair.Value;
    }

    float CompletedWeight = 0.0f;
    for (const EAIPipelineStage& S : PipelineStages)
    {
        if (S == Stage)
        {
            break;
        }
        CompletedWeight += StageWeights.Contains(S) ? StageWeights[S] : 0.0f;
    }

    CurrentProgress.ProgressPercent = TotalWeight > 0.0f ? (CompletedWeight / TotalWeight) * 100.0f : 0.0f;

    float RemainingWeight = TotalWeight - CompletedWeight;
    float Elapsed = static_cast<float>(FPlatformTime::Seconds() - PipelineStartTime);
    float CompletedFraction = TotalWeight > 0.0f ? CompletedWeight / TotalWeight : 0.0f;
    if (CompletedFraction > 0.0f)
    {
        float TotalEstimated = Elapsed / CompletedFraction;
        CurrentProgress.EstimatedTimeRemaining = TotalEstimated - Elapsed;
    }
    else
    {
        CurrentProgress.EstimatedTimeRemaining = TotalPipelineDuration;
    }

    CurrentProgress.StageDescription = UEnum::GetValueAsString(Stage);
    CurrentProgress.StageLog.Add(FString::Printf(TEXT("Entering stage: %s"), *CurrentProgress.StageDescription));

    OnPipelineStageChanged.Broadcast(Stage);
}

void ULesFightAIPipelineManager::CompletePipeline(bool bSuccess)
{
    CurrentResult.bSuccess = bSuccess;
    CurrentResult.GenerationTime = static_cast<float>(FPlatformTime::Seconds() - PipelineStartTime);
    CurrentResult.ProcessingLog = Preprocessor.IsValid() ? Preprocessor->GetPreprocessingLog() : TArray<FString>();

    CurrentProgress.bIsProcessing = false;
    CurrentProgress.ProgressPercent = 100.0f;
    CurrentProgress.CurrentStage = EAIPipelineStage::Complete;
    CurrentProgress.StageDescription = TEXT("Complete");
    CurrentProgress.StageLog.Add(TEXT("Pipeline completed"));

    bPipelineRunning = false;

    OnPipelineStageChanged.Broadcast(EAIPipelineStage::Complete);
    OnPipelineComplete.Broadcast(bSuccess);
}

void ULesFightAIPipelineManager::FailPipeline(const FString& Error)
{
    CurrentResult.bSuccess = false;
    CurrentResult.ErrorMessage = Error;

    CurrentProgress.bIsProcessing = false;
    CurrentProgress.CurrentStage = EAIPipelineStage::Failed;
    CurrentProgress.StageDescription = TEXT("Failed: ") + Error;
    CurrentProgress.StageLog.Add(FString::Printf(TEXT("Pipeline failed: %s"), *Error));

    bPipelineRunning = false;

    OnPipelineStageChanged.Broadcast(EAIPipelineStage::Failed);
    OnPipelineComplete.Broadcast(false);
}
