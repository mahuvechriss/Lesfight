#include "LesFightEnvironmentalCombat.h"
#include "LesFightMartialArtsManager.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ULesFightEnvironmentalCombat::ULesFightEnvironmentalCombat()
    : bNearWall(false)
    , bNearObject(false)
    , InteractionCooldown(1.0f)
    , EnvironmentSearchRadius(200.0f)
    , CurrentCooldown(0.0f)
{
}

void ULesFightEnvironmentalCombat::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    AvailableInteractions = { EEnvironmentInteraction::WallBounce, EEnvironmentInteraction::WallSlam };
}

void ULesFightEnvironmentalCombat::Tick(float DeltaTime)
{
    if (CurrentCooldown > 0.0f)
    {
        CurrentCooldown -= DeltaTime;
    }

    if (OwnerManager.IsValid())
    {
        TraceForEnvironment();
    }
}

bool ULesFightEnvironmentalCombat::ExecuteInteraction(
    EEnvironmentInteraction InteractionType, AActor* Target)
{
    if (CurrentCooldown > 0.0f) return false;
    if (!AvailableInteractions.Contains(InteractionType)) return false;

    CurrentTarget = Target;
    CurrentCooldown = InteractionCooldown;

    switch (InteractionType)
    {
    case EEnvironmentInteraction::WallBounce:
        ProcessWallBounce(Target);
        break;
    case EEnvironmentInteraction::WallSlam:
        ProcessWallSlam(Target);
        break;
    case EEnvironmentInteraction::EnvironmentalFinisher:
        ProcessFinisher(Target);
        break;
    case EEnvironmentInteraction::ObjectDestruction:
        ProcessDestruction(Target);
        break;
    default:
        return false;
    }

    OnEnvironmentInteraction.Broadcast(InteractionType);
    return true;
}

bool ULesFightEnvironmentalCombat::CanExecuteInteraction(
    EEnvironmentInteraction InteractionType) const
{
    if (CurrentCooldown > 0.0f) return false;
    if (!AvailableInteractions.Contains(InteractionType)) return false;

    switch (InteractionType)
    {
    case EEnvironmentInteraction::WallBounce:
    case EEnvironmentInteraction::WallSlam:
        return bNearWall;
    case EEnvironmentInteraction::EnvironmentalFinisher:
        return bNearObject;
    case EEnvironmentInteraction::ObjectDestruction:
        return bNearObject;
    default:
        return false;
    }
}

void ULesFightEnvironmentalCombat::DetectNearbyObjects(float SearchRadius)
{
    EnvironmentSearchRadius = SearchRadius;
    TraceForEnvironment();
}

void ULesFightEnvironmentalCombat::SetEnvironmentData(
    const TMap<EEnvironmentInteraction, FEnvironmentInteractionData>& Data)
{
    EnvironmentDefinitions = Data;
}

void ULesFightEnvironmentalCombat::SetAvailableInteractions(
    const TArray<EEnvironmentInteraction>& Interactions)
{
    AvailableInteractions = Interactions;
}

float ULesFightEnvironmentalCombat::GetWallBounceDamage() const
{
    const FEnvironmentInteractionData* Data = EnvironmentDefinitions.Find(EEnvironmentInteraction::WallBounce);
    return Data ? Data->BounceDamage : 0.0f;
}

float ULesFightEnvironmentalCombat::GetWallSlamDamage() const
{
    const FEnvironmentInteractionData* Data = EnvironmentDefinitions.Find(EEnvironmentInteraction::WallSlam);
    return Data ? Data->SlamDamage : 0.0f;
}

void ULesFightEnvironmentalCombat::Reset()
{
    bNearWall = false;
    bNearObject = false;
    NearestWall = nullptr;
    NearestObject = nullptr;
    CurrentTarget = nullptr;
    CurrentCooldown = 0.0f;
}

void ULesFightEnvironmentalCombat::ProcessWallBounce(AActor* Target)
{
    if (Target)
    {
        const FEnvironmentInteractionData* Data = EnvironmentDefinitions.Find(EEnvironmentInteraction::WallBounce);
        float Damage = Data ? Data->BounceDamage : 10.0f;
        OnWallBounce.Broadcast(Target, Damage);
    }
}

void ULesFightEnvironmentalCombat::ProcessWallSlam(AActor* Target)
{
    if (Target)
    {
        const FEnvironmentInteractionData* Data = EnvironmentDefinitions.Find(EEnvironmentInteraction::WallSlam);
        float Damage = Data ? Data->SlamDamage : 20.0f;
        OnWallSlam.Broadcast(Target, Damage);
    }
}

void ULesFightEnvironmentalCombat::ProcessFinisher(AActor* Target)
{
}

void ULesFightEnvironmentalCombat::ProcessDestruction(AActor* Object)
{
    if (Object)
    {
        OnObjectDestroyed.Broadcast(Object);
    }
}

void ULesFightEnvironmentalCombat::TraceForEnvironment()
{
    if (!OwnerManager.IsValid()) return;

    AActor* Owner = Cast<AActor>(OwnerManager->GetOuter());
    if (!Owner) return;

    UWorld* World = Owner->GetWorld();
    if (!World) return;

    FVector OwnerLoc = Owner->GetActorLocation();

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(Owner);

    TArray<FHitResult> Hits;
    if (World->SweepMultiByChannel(Hits, OwnerLoc, OwnerLoc + FVector(0, 0, 10),
        FQuat::Identity, ECC_WorldStatic, FCollisionShape::MakeSphere(EnvironmentSearchRadius), QueryParams))
    {
        for (const FHitResult& Hit : Hits)
        {
            if (Hit.bBlockingHit)
            {
                bNearWall = true;
                NearestWall = Hit.GetActor();
                return;
            }
        }
    }

    bNearWall = false;
    NearestWall = nullptr;
}
