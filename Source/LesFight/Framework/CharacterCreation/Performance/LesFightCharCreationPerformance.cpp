#include "LesFightCharCreationPerformance.h"
#include "LesFightCharCreationManager.h"

ULesFightCharCreationPerformance::ULesFightCharCreationPerformance()
    : CurrentDetailLevel(3)
    , CurrentPreviewQuality(3)
    , CurrentLODBias(0)
    , bDynamicResolution(true)
    , TextureScale(1.0f)
    , PerformanceScore(100.0f)
    , TargetFrameRate(60)
    , CurrentFrameRate(60)
    , DefaultDetailLevel(3)
    , DefaultPreviewQuality(3)
    , MaxDetailLevel(5)
    , MaxPreviewQuality(5)
    , FrameTimeIndex(0)
{
    for (int32 i = 0; i < 60; i++)
    {
        FrameTimeHistory[i] = 1.0f / 60.0f;
    }
}

void ULesFightCharCreationPerformance::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightCharCreationPerformance::Tick(float DeltaTime)
{
    FrameTimeHistory[FrameTimeIndex % 60] = DeltaTime;
    FrameTimeIndex++;

    float AvgFrameTime = 0.0f;
    int32 Count = FMath::Min(FrameTimeIndex, 60);
    for (int32 i = 0; i < Count; i++)
    {
        AvgFrameTime += FrameTimeHistory[i];
    }
    AvgFrameTime /= Count;

    CurrentFrameRate = AvgFrameTime > 0.0f ?
        FMath::RoundToInt(1.0f / AvgFrameTime) : 60;

    PerformanceScore = FMath::Clamp(
        (CurrentFrameRate / static_cast<float>(TargetFrameRate)) * 100.0f,
        0.0f, 100.0f);
}

void ULesFightCharCreationPerformance::SetDetailLevel(int32 DetailLevel)
{
    CurrentDetailLevel = FMath::Clamp(DetailLevel, 0, MaxDetailLevel);
}

void ULesFightCharCreationPerformance::SetPreviewQuality(int32 Quality)
{
    CurrentPreviewQuality = FMath::Clamp(Quality, 0, MaxPreviewQuality);
}

void ULesFightCharCreationPerformance::SetTextureResolutionScale(float Scale)
{
    TextureScale = FMath::Clamp(Scale, 0.1f, 2.0f);
}

float ULesFightCharCreationPerformance::GetTextureResolutionScale() const
{
    return TextureScale;
}

void ULesFightCharCreationPerformance::SetLODBias(int32 Bias)
{
    CurrentLODBias = FMath::Max(Bias, 0);
}

void ULesFightCharCreationPerformance::EnableDynamicResolution(bool bEnable)
{
    bDynamicResolution = bEnable;
}

void ULesFightCharCreationPerformance::SetTargetFrameRate(int32 FPS)
{
    TargetFrameRate = FMath::Clamp(FPS, 15, 240);
}

void ULesFightCharCreationPerformance::OptimizeForPlatform()
{
#if PLATFORM_DESKTOP
    CurrentDetailLevel = MaxDetailLevel;
    CurrentPreviewQuality = MaxPreviewQuality;
    TextureScale = 1.0f;
    bDynamicResolution = false;
#elif PLATFORM_CONSOLE
    CurrentDetailLevel = 3;
    CurrentPreviewQuality = 3;
    TextureScale = 0.8f;
    bDynamicResolution = true;
#else
    CurrentDetailLevel = 2;
    CurrentPreviewQuality = 2;
    TextureScale = 0.5f;
    bDynamicResolution = true;
#endif
}

void ULesFightCharCreationPerformance::ApplyOptimizations()
{
}

void ULesFightCharCreationPerformance::ResetToDefault()
{
    CurrentDetailLevel = DefaultDetailLevel;
    CurrentPreviewQuality = DefaultPreviewQuality;
    CurrentLODBias = 0;
    TextureScale = 1.0f;
    bDynamicResolution = true;
}
