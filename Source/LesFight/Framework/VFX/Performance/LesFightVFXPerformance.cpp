#include "LesFightVFXPerformance.h"
#include "Framework/VFX/Manager/LesFightVFXWorldManager.h"

void ULesFightVFXPerformance::Initialize(ULesFightVFXWorldManager* InOwner)
{
    OwnerManager = InOwner;
    bProfiling = false;
    CurrentQuality = EVFXQualityLevel::High;

    MaxParticlesByQuality.Empty();
    MaxParticlesByQuality.Add(EVFXQualityLevel::Low, 1000);
    MaxParticlesByQuality.Add(EVFXQualityLevel::Medium, 5000);
    MaxParticlesByQuality.Add(EVFXQualityLevel::High, 20000);
    MaxParticlesByQuality.Add(EVFXQualityLevel::Ultra, 50000);

    MaxSystemsByQuality.Empty();
    MaxSystemsByQuality.Add(EVFXQualityLevel::Low, 10);
    MaxSystemsByQuality.Add(EVFXQualityLevel::Medium, 25);
    MaxSystemsByQuality.Add(EVFXQualityLevel::High, 50);
    MaxSystemsByQuality.Add(EVFXQualityLevel::Ultra, 100);

    Metrics.MaxParticles = MaxParticlesByQuality[CurrentQuality];
    Metrics.MaxSystems = MaxSystemsByQuality[CurrentQuality];
    Metrics.AverageFrameTime = 16.67f;
    Metrics.GPUTime = 8.0f;
    Metrics.ParticleCount = 0;
}

void ULesFightVFXPerformance::SetQualityLevel(EVFXQualityLevel Level)
{
    CurrentQuality = Level;

    if (const int32* MaxParticles = MaxParticlesByQuality.Find(Level))
    {
        Metrics.MaxParticles = *MaxParticles;
    }
    if (const int32* MaxSystems = MaxSystemsByQuality.Find(Level))
    {
        Metrics.MaxSystems = *MaxSystems;
    }
}

EVFXQualityLevel ULesFightVFXPerformance::GetQualityLevel() const
{
    return CurrentQuality;
}

FVFXPerformanceMetrics ULesFightVFXPerformance::GetCurrentMetrics() const
{
    return Metrics;
}

void ULesFightVFXPerformance::OptimizeForPlatform()
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    SetQualityLevel(EVFXQualityLevel::Low);
#elif PLATFORM_SWITCH
    SetQualityLevel(EVFXQualityLevel::Medium);
#elif PLATFORM_XBOXONE || PLATFORM_PS4
    SetQualityLevel(EVFXQualityLevel::High);
#else
    SetQualityLevel(EVFXQualityLevel::Ultra);
#endif
}

EVFXQualityLevel ULesFightVFXPerformance::GetRecommendedQuality() const
{
#if PLATFORM_IOS || PLATFORM_ANDROID
    return EVFXQualityLevel::Low;
#elif PLATFORM_SWITCH
    return EVFXQualityLevel::Medium;
#elif PLATFORM_XBOXONE || PLATFORM_PS4
    return EVFXQualityLevel::High;
#else
    return EVFXQualityLevel::Ultra;
#endif
}

float ULesFightVFXPerformance::RunVFXBenchmark()
{
    StartProfiling();

    float TotalGPUTime = 0.0f;
    int32 SampleCount = 60;

    for (int32 i = 0; i < SampleCount; i++)
    {
        float SimulatedTime = FMath::FRandRange(4.0f, 16.0f);
        FrameGPUTimes.Add(SimulatedTime);
        TotalGPUTime += SimulatedTime;
    }

    StopProfiling();

    float AvgGPUTime = TotalGPUTime / SampleCount;
    Metrics.GPUTime = AvgGPUTime;
    Metrics.AverageFrameTime = AvgGPUTime + 8.0f;

    return AvgGPUTime;
}

void ULesFightVFXPerformance::StartProfiling()
{
    bProfiling = true;
    FrameGPUTimes.Empty();
}

void ULesFightVFXPerformance::StopProfiling()
{
    bProfiling = false;
}

FString ULesFightVFXPerformance::GetPerformanceReport() const
{
    return FString::Printf(TEXT(
        "VFX Performance Report:\n"
        "  Quality Level: %d\n"
        "  Max Particles: %d\n"
        "  Max Systems: %d\n"
        "  Avg Frame Time: %.2f ms\n"
        "  GPU Time: %.2f ms\n"
        "  Active Particles: %d\n"
        "  Sample Frames: %d"
    ),
        (int32)CurrentQuality,
        Metrics.MaxParticles,
        Metrics.MaxSystems,
        Metrics.AverageFrameTime,
        Metrics.GPUTime,
        Metrics.ParticleCount,
        FrameGPUTimes.Num()
    );
}
