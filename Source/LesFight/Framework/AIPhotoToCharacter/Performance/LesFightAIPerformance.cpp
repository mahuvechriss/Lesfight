#include "LesFightAIPerformance.h"
#include "Framework/AIPhotoToCharacter/Manager/LesFightAIManager.h"

ULesFightAIPerformance::ULesFightAIPerformance()
    : ProcessingPriority(5)
    , MaxMemoryMB(2048)
    , ThreadCount(4)
    , TextureResolutionLimit(4096)
    , bAsyncProcessing(false)
    , bTracking(false)
{
}

void ULesFightAIPerformance::Initialize(ULesFightAIManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightAIPerformance::SetProcessingPriority(int32 Priority)
{
    ProcessingPriority = FMath::Clamp(Priority, 1, 10);
}

int32 ULesFightAIPerformance::GetProcessingPriority() const
{
    return ProcessingPriority;
}

void ULesFightAIPerformance::SetMaxMemoryMB(int32 MB)
{
    MaxMemoryMB = FMath::Max(256, MB);
}

int32 ULesFightAIPerformance::GetMaxMemoryMB() const
{
    return MaxMemoryMB;
}

float ULesFightAIPerformance::EstimateProcessingTime(EAIPipelineStage Stage) const
{
    switch (Stage)
    {
    case EAIPipelineStage::ImageUploaded:       return 0.5f;
    case EAIPipelineStage::Validating:          return 0.3f;
    case EAIPipelineStage::ValidationComplete:  return 0.1f;
    case EAIPipelineStage::Preprocessing:       return 0.8f;
    case EAIPipelineStage::FaceDetection:       return 1.0f;
    case EAIPipelineStage::LandmarkDetection:   return 0.7f;
    case EAIPipelineStage::FeatureExtraction:   return 0.6f;
    case EAIPipelineStage::BodyEstimation:      return 0.8f;
    case EAIPipelineStage::FaceReconstruction:  return 5.0f;
    case EAIPipelineStage::BodyReconstruction:  return 3.0f;
    case EAIPipelineStage::TextureGeneration:   return 8.0f;
    case EAIPipelineStage::HairGeneration:      return 2.0f;
    case EAIPipelineStage::MeshIntegration:     return 2.0f;
    case EAIPipelineStage::SkeletonMapping:     return 1.0f;
    case EAIPipelineStage::BlendShapeGeneration:return 2.0f;
    case EAIPipelineStage::PreviewReady:        return 0.5f;
    case EAIPipelineStage::UserEditing:         return 0.0f;
    case EAIPipelineStage::Finalizing:          return 0.3f;
    case EAIPipelineStage::Complete:            return 0.1f;
    case EAIPipelineStage::Failed:              return 0.0f;
    default:                                    return 0.0f;
    }
}

void ULesFightAIPerformance::SetThreadCount(int32 Count)
{
    ThreadCount = FMath::Clamp(Count, 1, 16);
}

int32 ULesFightAIPerformance::GetThreadCount() const
{
    return ThreadCount;
}

void ULesFightAIPerformance::EnableAsyncProcessing(bool bEnable)
{
    bAsyncProcessing = bEnable;
}

bool ULesFightAIPerformance::IsAsyncProcessingEnabled() const
{
    return bAsyncProcessing;
}

FString ULesFightAIPerformance::GetPerformanceReport() const
{
    FString Report;
    Report += TEXT("=== AI Performance Report ===\n");
    Report += FString::Printf(TEXT("Processing Priority: %d\n"), ProcessingPriority);
    Report += FString::Printf(TEXT("Max Memory: %d MB\n"), MaxMemoryMB);
    Report += FString::Printf(TEXT("Thread Count: %d\n"), ThreadCount);
    Report += FString::Printf(TEXT("Texture Resolution Limit: %d\n"), TextureResolutionLimit);
    Report += FString::Printf(TEXT("Async Processing: %s\n"), bAsyncProcessing ? TEXT("Enabled") : TEXT("Disabled"));
    Report += FString::Printf(TEXT("Performance Tracking: %s\n"), bTracking ? TEXT("Active") : TEXT("Inactive"));

    if (bTracking && StageTimings.Num() > 0)
    {
        Report += TEXT("\nStage Averages:\n");
        for (const auto& Entry : StageTimings)
        {
            FString StageName = StaticEnum<EAIPipelineStage>()->GetNameStringByValue((int64)Entry.Key);
            float Avg = 0.0f;
            for (float Time : Entry.Value)
            {
                Avg += Time;
            }
            if (Entry.Value.Num() > 0)
            {
                Avg /= Entry.Value.Num();
            }
            Report += FString::Printf(TEXT("  %s: %.2f s\n"), *StageName, Avg);
        }
    }

    return Report;
}

void ULesFightAIPerformance::LimitTextureResolution(int32 MaxResolution)
{
    TextureResolutionLimit = FMath::Clamp(MaxResolution, 256, 16384);
}

int32 ULesFightAIPerformance::GetTextureResolutionLimit() const
{
    return TextureResolutionLimit;
}

void ULesFightAIPerformance::OptimizeForPlatform()
{
#if PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX
    ProcessingPriority = 5;
    MaxMemoryMB = 4096;
    ThreadCount = 8;
    TextureResolutionLimit = 8192;
    bAsyncProcessing = true;
#elif PLATFORM_XBOXONE || PLATFORM_PS4 || PLATFORM_PS5 || PLATFORM_SWITCH
    ProcessingPriority = 7;
    MaxMemoryMB = 3072;
    ThreadCount = 6;
    TextureResolutionLimit = 4096;
    bAsyncProcessing = true;
#else
    ProcessingPriority = 8;
    MaxMemoryMB = 1024;
    ThreadCount = 2;
    TextureResolutionLimit = 2048;
    bAsyncProcessing = false;
#endif
}

void ULesFightAIPerformance::StartPerformanceTracking()
{
    bTracking = true;
    StageTimings.Empty();
}

void ULesFightAIPerformance::StopPerformanceTracking()
{
    bTracking = false;

    FString Summary = TEXT("=== Performance Tracking Summary ===\n");
    for (const auto& Entry : StageTimings)
    {
        FString StageName = StaticEnum<EAIPipelineStage>()->GetNameStringByValue((int64)Entry.Key);
        float Avg = 0.0f;
        for (float Time : Entry.Value)
        {
            Avg += Time;
        }
        if (Entry.Value.Num() > 0)
        {
            Avg /= Entry.Value.Num();
        }
        Summary += FString::Printf(TEXT("  %s - Average: %.2f s (Sampled %d times)\n"), *StageName, Avg, Entry.Value.Num());
    }
    UE_LOG(LogTemp, Log, TEXT("%s"), *Summary);
}

float ULesFightAIPerformance::GetAverageStageTime(EAIPipelineStage Stage) const
{
    const TArray<float>* Timings = StageTimings.Find(Stage);
    if (!Timings || Timings->Num() == 0)
    {
        return 0.0f;
    }

    float Total = 0.0f;
    for (float Time : *Timings)
    {
        Total += Time;
    }
    return Total / Timings->Num();
}
