#include "LesFightMartialArtsPerformance.h"
#include "LesFightMartialArtsManager.h"

ULesFightMartialArtsPerformance::ULesFightMartialArtsPerformance()
    : TargetFrameRate(60.0f)
    , bDynamicLODEnabled(true)
    , CurrentQualityPreset(2)
    , FrameTimeHistory(0.0f)
    , FrameCount(0)
{
}

void ULesFightMartialArtsPerformance::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    CurrentMetrics = FPerformanceMetrics();
}

void ULesFightMartialArtsPerformance::Tick(float DeltaTime)
{
    UpdateMetrics(DeltaTime);

    if (bDynamicLODEnabled)
    {
        ApplyDynamicLOD(DeltaTime);
    }
}

void ULesFightMartialArtsPerformance::SetAnimationLOD(float Distance)
{
    CurrentMetrics.AnimationLODDistance = FMath::Clamp(Distance, 500.0f, 5000.0f);
}

void ULesFightMartialArtsPerformance::SetPhysicsLOD(float Distance)
{
    CurrentMetrics.PhysicsLODDistance = FMath::Clamp(Distance, 500.0f, 5000.0f);
}

void ULesFightMartialArtsPerformance::SetVFXLOD(float Distance)
{
    CurrentMetrics.VFXLODDistance = FMath::Clamp(Distance, 500.0f, 5000.0f);
}

void ULesFightMartialArtsPerformance::SetTargetFrameRate(int32 FPS)
{
    TargetFrameRate = FMath::Clamp(FPS, 30, 240);
}

void ULesFightMartialArtsPerformance::EnableDynamicLOD(bool bEnable)
{
    bDynamicLODEnabled = bEnable;
}

void ULesFightMartialArtsPerformance::SetQualityPreset(int32 PresetLevel)
{
    CurrentQualityPreset = FMath::Clamp(PresetLevel, 0, 3);
    ApplyQualityPreset(CurrentQualityPreset);
}

void ULesFightMartialArtsPerformance::Reset()
{
    CurrentMetrics = FPerformanceMetrics();
    FrameTimeHistory = 0.0f;
    FrameCount = 0;
}

void ULesFightMartialArtsPerformance::UpdateMetrics(float DeltaTime)
{
    FrameCount++;
    FrameTimeHistory += DeltaTime;

    if (FrameCount >= 60)
    {
        CurrentMetrics.TotalFrameTimeMs = (FrameTimeHistory / FrameCount) * 1000.0f;
        FrameCount = 0;
        FrameTimeHistory = 0.0f;
    }
}

void ULesFightMartialArtsPerformance::ApplyDynamicLOD(float DeltaTime)
{
    float FrameBudget = 1000.0f / TargetFrameRate;
    float CurrentFrameMs = DeltaTime * 1000.0f;

    if (CurrentFrameMs > FrameBudget * 0.9f)
    {
        CurrentMetrics.AnimationLODDistance *= 0.95f;
        CurrentMetrics.VFXLODDistance *= 0.95f;
    }
    else if (CurrentFrameMs < FrameBudget * 0.5f)
    {
        CurrentMetrics.AnimationLODDistance *= 1.02f;
        CurrentMetrics.VFXLODDistance *= 1.02f;
    }
}

void ULesFightMartialArtsPerformance::ApplyQualityPreset(int32 Preset)
{
    switch (Preset)
    {
    case 0:
        CurrentMetrics.AnimationLODDistance = 1000.0f;
        CurrentMetrics.PhysicsLODDistance = 500.0f;
        CurrentMetrics.VFXLODDistance = 1000.0f;
        break;
    case 1:
        CurrentMetrics.AnimationLODDistance = 1500.0f;
        CurrentMetrics.PhysicsLODDistance = 1000.0f;
        CurrentMetrics.VFXLODDistance = 1500.0f;
        break;
    case 2:
        CurrentMetrics.AnimationLODDistance = 2000.0f;
        CurrentMetrics.PhysicsLODDistance = 1500.0f;
        CurrentMetrics.VFXLODDistance = 2000.0f;
        break;
    case 3:
        CurrentMetrics.AnimationLODDistance = 3000.0f;
        CurrentMetrics.PhysicsLODDistance = 2000.0f;
        CurrentMetrics.VFXLODDistance = 3000.0f;
        break;
    }
}
