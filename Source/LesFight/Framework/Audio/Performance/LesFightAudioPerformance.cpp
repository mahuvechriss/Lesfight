#include "Framework/Audio/Performance/LesFightAudioPerformance.h"

void ULesFightAudioPerformance::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    MaxActiveSounds = 64;
    SoundPoolMB = 256;
    bProfiling = false;
    FrameAudioCPUTimes.Empty();
    Stats = FAudioPerformanceStats();
}

void ULesFightAudioPerformance::SetMaxActiveSounds(int32 Max)
{
    MaxActiveSounds = FMath::Max(1, Max);
}

int32 ULesFightAudioPerformance::GetMaxActiveSounds() const
{
    return MaxActiveSounds;
}

void ULesFightAudioPerformance::SetSoundPoolSize(int32 MB)
{
    SoundPoolMB = FMath::Max(16, MB);
}

int32 ULesFightAudioPerformance::GetSoundPoolSize() const
{
    return SoundPoolMB;
}

FAudioPerformanceStats ULesFightAudioPerformance::GetCurrentStats() const
{
    return Stats;
}

void ULesFightAudioPerformance::OptimizeForQuality(int32 QualityLevel)
{
    switch (QualityLevel)
    {
    case 1:
        MaxActiveSounds = 16;
        SoundPoolMB = 32;
        break;
    case 2:
        MaxActiveSounds = 32;
        SoundPoolMB = 64;
        break;
    case 3:
        MaxActiveSounds = 64;
        SoundPoolMB = 128;
        break;
    case 4:
        MaxActiveSounds = 64;
        SoundPoolMB = 256;
        break;
    case 5:
        MaxActiveSounds = 128;
        SoundPoolMB = 512;
        break;
    default:
        break;
    }
}

void ULesFightAudioPerformance::StartProfiling()
{
    bProfiling = true;
    FrameAudioCPUTimes.Empty();
}

void ULesFightAudioPerformance::StopProfiling()
{
    bProfiling = false;
}

FString ULesFightAudioPerformance::GetPerformanceReport() const
{
    return FString::Printf(TEXT("ActiveSounds: %d | MaxSounds: %d | PoolSize: %dMB | CPU: %.2f | Memory: %.2fMB"),
        Stats.ActiveSounds, MaxActiveSounds, SoundPoolMB, Stats.AudioCPUUsage, Stats.EstimatedAudioMemoryMB);
}
