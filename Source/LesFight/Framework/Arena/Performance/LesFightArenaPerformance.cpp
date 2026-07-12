#include "LesFightArenaPerformance.h"
#include "Framework/Arena/Manager/LesFightArenaWorldManager.h"

void ULesFightArenaPerformance::Initialize(ULesFightArenaWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    QualityLevel = 3;
    bNanite = true;
    bLumen = true;
    TexturePoolMB = 4096;
    PerformanceScore = 0.0f;
    FrameTimeHistory.Empty();
}

void ULesFightArenaPerformance::SetQualityLevel(int32 Level)
{
    QualityLevel = FMath::Clamp(Level, 1, 5);

    switch (QualityLevel)
    {
    case 1:
        SetNaniteEnabled(false);
        SetLumenEnabled(false);
        SetTexturePoolSize(1024);
        break;
    case 2:
        SetNaniteEnabled(true);
        SetLumenEnabled(false);
        SetTexturePoolSize(2048);
        break;
    case 3:
        SetNaniteEnabled(true);
        SetLumenEnabled(true);
        SetTexturePoolSize(4096);
        break;
    case 4:
        SetNaniteEnabled(true);
        SetLumenEnabled(true);
        SetTexturePoolSize(8192);
        break;
    case 5:
        SetNaniteEnabled(true);
        SetLumenEnabled(true);
        SetTexturePoolSize(16384);
        break;
    }

    Metrics.QualityLevel = QualityLevel;
    Metrics.bNaniteEnabled = bNanite;
    Metrics.bLumenEnabled = bLumen;
    Metrics.TexturePoolSizeMB = TexturePoolMB;
}

int32 ULesFightArenaPerformance::GetQualityLevel() const
{
    return QualityLevel;
}

void ULesFightArenaPerformance::SetNaniteEnabled(bool bEnabled)
{
    bNanite = bEnabled;
    Metrics.bNaniteEnabled = bNanite;
}

void ULesFightArenaPerformance::SetLumenEnabled(bool bEnabled)
{
    bLumen = bEnabled;
    Metrics.bLumenEnabled = bLumen;
}

void ULesFightArenaPerformance::SetTexturePoolSize(int32 MB)
{
    TexturePoolMB = FMath::Max(256, MB);
    Metrics.TexturePoolSizeMB = TexturePoolMB;
}

FArenaPerformanceMetrics ULesFightArenaPerformance::GetCurrentMetrics() const
{
    return Metrics;
}

float ULesFightArenaPerformance::GetAverageFPS() const
{
    if (FrameTimeHistory.Num() == 0) return 0.0f;

    float TotalFrameTime = 0.0f;
    for (float FrameTime : FrameTimeHistory)
    {
        TotalFrameTime += FrameTime;
    }

    float AvgFrameTime = TotalFrameTime / FrameTimeHistory.Num();
    return AvgFrameTime > 0.0f ? 1.0f / AvgFrameTime : 0.0f;
}

FArenaPerformanceMetrics ULesFightArenaPerformance::GetRecommendedSettings() const
{
    FArenaPerformanceMetrics Recommended;

    int32 CPUCores = FPlatformMisc::NumberOfCoresIncludingHyperthreads();
    int32 RAMGB = FPlatformMemory::GetPhysicalGBRam();

    if (CPUCores >= 8 && RAMGB >= 32)
    {
        Recommended.QualityLevel = 5;
        Recommended.bNaniteEnabled = true;
        Recommended.bLumenEnabled = true;
        Recommended.TexturePoolSizeMB = 16384;
    }
    else if (CPUCores >= 6 && RAMGB >= 16)
    {
        Recommended.QualityLevel = 3;
        Recommended.bNaniteEnabled = true;
        Recommended.bLumenEnabled = true;
        Recommended.TexturePoolSizeMB = 4096;
    }
    else
    {
        Recommended.QualityLevel = 1;
        Recommended.bNaniteEnabled = false;
        Recommended.bLumenEnabled = false;
        Recommended.TexturePoolSizeMB = 1024;
    }

    return Recommended;
}

void ULesFightArenaPerformance::OptimizeForArena(EArenaType Arena)
{
    switch (Arena)
    {
    case EArenaType::Training:
        SetQualityLevel(3);
        break;
    case EArenaType::Standard:
        SetQualityLevel(4);
        break;
    case EArenaType::Dynamic:
        SetQualityLevel(3);
        break;
    case EArenaType::Destructible:
        SetQualityLevel(2);
        break;
    default:
        SetQualityLevel(3);
        break;
    }
}

float ULesFightArenaPerformance::RunPerformanceBenchmark()
{
    FrameTimeHistory.Empty();

    for (int32 i = 0; i < 100; i++)
    {
        float SimulatedFrameTime = FMath::FRandRange(0.008f, 0.033f);
        FrameTimeHistory.Add(SimulatedFrameTime);
    }

    float AvgFrameTime = 0.0f;
    for (float FT : FrameTimeHistory)
    {
        AvgFrameTime += FT;
    }
    AvgFrameTime /= FrameTimeHistory.Num();

    float FPS = AvgFrameTime > 0.0f ? 1.0f / AvgFrameTime : 0.0f;
    PerformanceScore = FMath::Clamp(FPS / 120.0f, 0.0f, 1.0f);

    Metrics.AverageFPS = FPS;
    Metrics.PerformanceScore = PerformanceScore;

    return PerformanceScore;
}
