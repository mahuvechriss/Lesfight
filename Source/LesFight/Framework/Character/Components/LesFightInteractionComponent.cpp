#include "LesFightInteractionComponent.h"
#include "LesFight.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ULesFightInteractionComponent::ULesFightInteractionComponent()
    : DetectionRadius(200.0f)
    , bInteractionEnabled(true)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.2f;
}

void ULesFightInteractionComponent::BeginPlay()
{
    Super::BeginPlay();
    InteractableClass = AActor::StaticClass();
}

void ULesFightInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bInteractionEnabled)
    {
        ScanForInteractables();
    }
}

void ULesFightInteractionComponent::Initialize(float InDetectionRadius)
{
    DetectionRadius = InDetectionRadius;
}

void ULesFightInteractionComponent::PerformInteraction()
{
    if (!bInteractionEnabled || !ClosestInteractable.IsValid()) return;

    OnInteractionPerformed.Broadcast(ClosestInteractable.Get());

    UE_LOG(LogLesFight, Verbose, TEXT("Interaction performed with %s"),
        *ClosestInteractable->GetName());
}

void ULesFightInteractionComponent::SetDetectionRadius(float Radius)
{
    DetectionRadius = Radius;
}

void ULesFightInteractionComponent::SetInteractionEnabled(bool bEnabled)
{
    bInteractionEnabled = bEnabled;
    if (!bEnabled)
    {
        DetectedInteractables.Empty();
        ClosestInteractable = nullptr;
    }
}

void ULesFightInteractionComponent::ScanForInteractables()
{
    if (!GetWorld() || !GetOwner()) return;

    TArray<AActor*> PreviouslyDetected = DetectedInteractables;
    DetectedInteractables.Empty();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), InteractableClass, FoundActors);

    FVector OwnerLocation = GetOwner()->GetActorLocation();

    for (AActor* Actor : FoundActors)
    {
        if (Actor == GetOwner()) continue;
        if (!IsValidInteractable(Actor)) continue;

        float Distance = FVector::Distance(OwnerLocation, Actor->GetActorLocation());
        if (Distance <= DetectionRadius)
        {
            DetectedInteractables.Add(Actor);

            if (!PreviouslyDetected.Contains(Actor))
            {
                OnInteractableFound.Broadcast(Actor);
            }
        }
    }

    for (AActor* Actor : PreviouslyDetected)
    {
        if (!DetectedInteractables.Contains(Actor))
        {
            OnInteractableLost.Broadcast(Actor);
        }
    }

    UpdateClosestInteractable();
}

void ULesFightInteractionComponent::UpdateClosestInteractable()
{
    if (DetectedInteractables.Num() == 0)
    {
        ClosestInteractable = nullptr;
        return;
    }

    AActor* Closest = nullptr;
    float ClosestDistance = FLT_MAX;
    FVector OwnerLocation = GetOwner()->GetActorLocation();

    for (AActor* Actor : DetectedInteractables)
    {
        float Distance = FVector::Distance(OwnerLocation, Actor->GetActorLocation());
        if (Distance < ClosestDistance)
        {
            ClosestDistance = Distance;
            Closest = Actor;
        }
    }

    ClosestInteractable = Closest;
}

bool ULesFightInteractionComponent::IsValidInteractable(AActor* Actor) const
{
    return Actor && Actor->IsValidLowLevel() && Actor->GetRootComponent();
}
