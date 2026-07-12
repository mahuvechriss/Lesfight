#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightEnvironmentalCombat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnvironmentInteraction, EEnvironmentInteraction, InteractionType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWallBounce, AActor*, Target, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWallSlam, AActor*, Target, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDestroyed, AActor*, Object);

UCLASS(Blueprintable)
class ULesFightEnvironmentalCombat : public UObject
{
    GENERATED_BODY()

public:
    ULesFightEnvironmentalCombat();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    bool ExecuteInteraction(EEnvironmentInteraction InteractionType, AActor* Target = nullptr);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    bool CanExecuteInteraction(EEnvironmentInteraction InteractionType) const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    void DetectNearbyObjects(float SearchRadius);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    void SetEnvironmentData(const TMap<EEnvironmentInteraction, FEnvironmentInteractionData>& Data);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    void SetAvailableInteractions(const TArray<EEnvironmentInteraction>& Interactions);

    UFUNCTION(BlueprintPure, Category = "MartialArts|Environment")
    bool IsNearWall() const { return bNearWall; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Environment")
    bool IsNearObject() const { return bNearObject; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Environment")
    AActor* GetNearestWall() const { return NearestWall.Get(); }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Environment")
    AActor* GetNearestObject() const { return NearestObject.Get(); }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Environment")
    TArray<EEnvironmentInteraction> GetAvailableInteractions() const { return AvailableInteractions; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    float GetWallBounceDamage() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    float GetWallSlamDamage() const;

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Environment")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnEnvironmentInteraction OnEnvironmentInteraction;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnWallBounce OnWallBounce;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnWallSlam OnWallSlam;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnObjectDestroyed OnObjectDestroyed;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bNearWall;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bNearObject;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TWeakObjectPtr<AActor> NearestWall;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TWeakObjectPtr<AActor> NearestObject;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TArray<EEnvironmentInteraction> AvailableInteractions;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TMap<EEnvironmentInteraction, FEnvironmentInteractionData> EnvironmentDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float InteractionCooldown;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float EnvironmentSearchRadius;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    float CurrentCooldown;
    TWeakObjectPtr<AActor> CurrentTarget;

    void ProcessWallBounce(AActor* Target);
    void ProcessWallSlam(AActor* Target);
    void ProcessFinisher(AActor* Target);
    void ProcessDestruction(AActor* Object);
    void TraceForEnvironment();
};
