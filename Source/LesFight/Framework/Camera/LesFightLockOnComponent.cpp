#include "LesFightLockOnComponent.h"
#include "LesFight.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ULesFightLockOnComponent::ULesFightLockOnComponent()
    : LockOnRange(1000.0f)
    , LockOnAngle(45.0f)
    , LockOnBreakRange(1500.0f)
    , CurrentTarget(nullptr)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.1f;
}

void ULesFightLockOnComponent::BeginPlay()
{
    Super::BeginPlay();
}

void ULesFightLockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (IsLockedOn())
    {
        BreakLockOnIfOutOfRange();
    }
}

bool ULesFightLockOnComponent::TryLockOnTarget()
{
    FindTargetsInRange();

    if (CachedTargets.Num() == 0) return false;

    AActor* ClosestTarget = nullptr;
    float ClosestDistance = FLT_MAX;

    FVector OwnerLocation = GetOwner()->GetActorLocation();
    FVector OwnerForward = GetOwner()->GetActorForwardVector();

    for (AActor* Target : CachedTargets)
    {
        if (!IsValidTarget(Target)) continue;

        FVector DirectionToTarget = (Target->GetActorLocation() - OwnerLocation).GetSafeNormal();
        float DotProduct = FVector::DotProduct(OwnerForward, DirectionToTarget);
        float Distance = FVector::Distance(OwnerLocation, Target->GetActorLocation());

        if (DotProduct > FMath::Cos(FMath::DegreesToRadians(LockOnAngle)) && Distance < ClosestDistance)
        {
            ClosestTarget = Target;
            ClosestDistance = Distance;
        }
    }

    if (ClosestTarget)
    {
        if (CurrentTarget && CurrentTarget != ClosestTarget)
        {
            OnLockOnLost.Broadcast();
        }
        CurrentTarget = ClosestTarget;
        OnLockOnTargetChanged.Broadcast(CurrentTarget);
        return true;
    }

    return false;
}

void ULesFightLockOnComponent::ClearLockOn()
{
    if (CurrentTarget)
    {
        CurrentTarget = nullptr;
        OnLockOnLost.Broadcast();
    }
}

void ULesFightLockOnComponent::CycleTarget(int32 Direction)
{
    if (!IsLockedOn()) return;

    FindTargetsInRange();
    if (CachedTargets.Num() == 0)
    {
        ClearLockOn();
        return;
    }

    int32 CurrentIndex = CachedTargets.IndexOfByKey(CurrentTarget);
    int32 NewIndex = CurrentIndex + Direction;

    if (NewIndex < 0) NewIndex = CachedTargets.Num() - 1;
    if (NewIndex >= CachedTargets.Num()) NewIndex = 0;

    if (CachedTargets.IsValidIndex(NewIndex) && CachedTargets[NewIndex] != CurrentTarget)
    {
        CurrentTarget = CachedTargets[NewIndex];
        OnLockOnTargetChanged.Broadcast(CurrentTarget);
    }
}

TArray<AActor*> ULesFightLockOnComponent::GetPotentialTargets() const
{
    return CachedTargets;
}

void ULesFightLockOnComponent::FindTargetsInRange()
{
    CachedTargets.Empty();

    if (!GetWorld()) return;

    FVector OwnerLocation = GetOwner()->GetActorLocation();
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        if (Actor == GetOwner()) continue;
        if (!IsValidTarget(Actor)) continue;

        float Distance = FVector::Distance(OwnerLocation, Actor->GetActorLocation());
        if (Distance <= LockOnRange)
        {
            CachedTargets.Add(Actor);
        }
    }
}

bool ULesFightLockOnComponent::IsValidTarget(AActor* Target) const
{
    if (!Target || !Target->IsValidLowLevel()) return false;
    if (!Target->GetRootComponent()) return false;

    for (TSubclassOf<AActor> ClassType : LockableClasses)
    {
        if (Target->IsA(ClassType))
            return true;
    }

    return LockableClasses.Num() == 0;
}

void ULesFightLockOnComponent::BreakLockOnIfOutOfRange()
{
    if (!CurrentTarget || !GetOwner()) return;

    float Distance = FVector::Distance(GetOwner()->GetActorLocation(), CurrentTarget->GetActorLocation());
    if (Distance > LockOnBreakRange)
    {
        ClearLockOn();
    }
}
