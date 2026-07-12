#include "LesFightAnimationPerformance.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"

ULesFightAnimationPerformance::ULesFightAnimationPerformance()
    : AnimationBudgetMs(5.0f)
    , LODNearDistance(500.0f)
    , LODMediumDistance(1500.0f)
    , LODFarDistance(3000.0f)
    , bLODEnabled(true)
    , bOverBudget(false)
    , CurrentOptimization(EAnimOptimizationLevel::None)
    , FrameTimeAccumulator(0.0f)
    , FrameCount(0)
{
}

void ULesFightAnimationPerformance::Initialize()
{
    UE_LOG(LogLesFight, Log, TEXT("AnimationPerformance initialized"));
}

void ULesFightAnimationPerformance::Update(float DeltaTime)
{
    if (RegisteredComponents.Num() == 0) return;

    CalculateMetrics(DeltaTime);

    if (bLODEnabled)
    {
        CalculateLODLevels();
    }

    if (bOverBudget)
    {
        OptimizeAnimations();
    }
}

void ULesFightAnimationPerformance::RegisterAnimComponent(
    ULesFightCharacterAnimationComponent* AnimComp)
{
    if (AnimComp)
    {
        RegisteredComponents.AddUnique(AnimComp);
    }
}

void ULesFightAnimationPerformance::UnregisterAnimComponent(
    ULesFightCharacterAnimationComponent* AnimComp)
{
    RegisteredComponents.Remove(AnimComp);
}

void ULesFightAnimationPerformance::SetLODDistanceThresholds(float Near, float Medium,
    float Far)
{
    LODNearDistance = Near;
    LODMediumDistance = Medium;
    LODFarDistance = Far;
}

void ULesFightAnimationPerformance::SetOptimizationLevel(EAnimOptimizationLevel Level)
{
    CurrentOptimization = Level;

    for (ULesFightCharacterAnimationComponent* Comp : RegisteredComponents)
    {
        if (!Comp) continue;

        switch (Level)
        {
        case EAnimOptimizationLevel::Aggressive:
            Comp->SetAnimationQuality(EAnimationQuality::Low);
            break;
        case EAnimOptimizationLevel::Advanced:
            Comp->SetAnimationQuality(EAnimationQuality::Medium);
            break;
        case EAnimOptimizationLevel::Basic:
            Comp->SetAnimationQuality(EAnimationQuality::High);
            break;
        default:
            Comp->SetAnimationQuality(EAnimationQuality::Epic);
            break;
        }
    }
}

void ULesFightAnimationPerformance::ForceOptimization(EAnimOptimizationLevel Level)
{
    SetOptimizationLevel(Level);
}

float ULesFightAnimationPerformance::GetBudgetUsage() const
{
    return AnimationBudgetMs > 0.0f
        ? (CurrentMetrics.AnimationUsage / AnimationBudgetMs) * 100.0f
        : 0.0f;
}

void ULesFightAnimationPerformance::CalculateLODLevels()
{
    for (ULesFightCharacterAnimationComponent* Comp : RegisteredComponents)
    {
        if (!Comp) continue;

        AActor* Owner = Comp->GetOwner();
        if (!Owner) continue;

        float Distance = 0.0f;
        APlayerController* PC = Cast<APlayerController>(
            Owner->GetInstigatorController());
        if (PC && PC->GetPawn())
        {
            Distance = FVector::Dist(Owner->GetActorLocation(),
                PC->GetPawn()->GetActorLocation());
        }

        if (Distance > LODFarDistance)
        {
            Comp->SetAnimationQuality(EAnimationQuality::Low);
        }
        else if (Distance > LODMediumDistance)
        {
            Comp->SetAnimationQuality(EAnimationQuality::Medium);
        }
        else if (Distance > LODNearDistance)
        {
            Comp->SetAnimationQuality(EAnimationQuality::High);
        }
        else
        {
            Comp->SetAnimationQuality(EAnimationQuality::Epic);
        }
    }
}

void ULesFightAnimationPerformance::CalculateMetrics(float DeltaTime)
{
    FrameTimeAccumulator += DeltaTime * 1000.0f;
    FrameCount++;

    if (FrameCount >= 60)
    {
        CurrentMetrics.AverageFrameTime = FrameTimeAccumulator / FrameCount;
        CurrentMetrics.ActiveAnimInstances = RegisteredComponents.Num();
        CurrentMetrics.LODLevel = bLODEnabled ? 1 : 0;
        CurrentMetrics.bLODActive = bLODEnabled;
        CurrentMetrics.AnimationUsage = CurrentMetrics.AverageFrameTime;
        CurrentMetrics.CurrentOptimization = CurrentOptimization;

        bOverBudget = CurrentMetrics.AverageFrameTime > AnimationBudgetMs;

        FrameTimeAccumulator = 0.0f;
        FrameCount = 0;
    }
}

void ULesFightAnimationPerformance::OptimizeAnimations()
{
    for (ULesFightCharacterAnimationComponent* Comp : RegisteredComponents)
    {
        if (!Comp) continue;
        Comp->SetGlobalPlayRate(1.0f);
        Comp->SetAnimationQuality(EAnimationQuality::Medium);
    }
}
