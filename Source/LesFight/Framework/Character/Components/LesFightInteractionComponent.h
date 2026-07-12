#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "LesFightInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableFound, AActor*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableLost, AActor*, Interactable);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionPerformed, AActor*, Target);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightInteractionComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Initialize(float InDetectionRadius);

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void PerformInteraction();

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void SetDetectionRadius(float Radius);

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void SetInteractionEnabled(bool bEnabled);

    UFUNCTION(BlueprintPure, Category = "Interaction")
    AActor* GetClosestInteractable() const { return ClosestInteractable.Get(); }

    UFUNCTION(BlueprintPure, Category = "Interaction")
    TArray<AActor*> GetDetectedInteractables() const { return DetectedInteractables; }

    UFUNCTION(BlueprintPure, Category = "Interaction")
    bool HasInteractable() const { return ClosestInteractable.IsValid(); }

    UFUNCTION(BlueprintPure, Category = "Interaction")
    float GetDetectionRadius() const { return DetectionRadius; }

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void SetInteractableClass(TSubclassOf<AActor> ClassType) { InteractableClass = ClassType; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
    float DetectionRadius;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interaction")
    TSubclassOf<AActor> InteractableClass;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInteractableFound OnInteractableFound;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInteractableLost OnInteractableLost;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnInteractionPerformed OnInteractionPerformed;

private:
    UPROPERTY()
    TArray<AActor*> DetectedInteractables;

    UPROPERTY()
    TWeakObjectPtr<AActor> ClosestInteractable;

    bool bInteractionEnabled;

    void ScanForInteractables();
    void UpdateClosestInteractable();
    bool IsValidInteractable(AActor* Actor) const;
};
