#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationPerformance.generated.h"

class ULesFightCharacterAnimationComponent;

UENUM(BlueprintType)
enum class EAnimOptimizationLevel : uint8
{
    None,
    Basic,
    Advanced,
    Aggressive,
    Max UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FAnimPerformanceMetrics
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    float AverageFrameTime;

    UPROPERTY(BlueprintReadOnly)
    float MaxFrameTime;

    UPROPERTY(BlueprintReadOnly)
    float AnimationBudget;

    UPROPERTY(BlueprintReadOnly)
    float AnimationUsage;

    UPROPERTY(BlueprintReadOnly)
    int32 ActiveAnimInstances;

    UPROPERTY(BlueprintReadOnly)
    int32 LODLevel;

    UPROPERTY(BlueprintReadOnly)
    bool bLODActive;

    UPROPERTY(BlueprintReadOnly)
    EAnimOptimizationLevel CurrentOptimization;

    FAnimPerformanceMetrics()
        : AverageFrameTime(0.0f), MaxFrameTime(0.0f)
        , AnimationBudget(5.0f), AnimationUsage(0.0f)
        , ActiveAnimInstances(0), LODLevel(0)
        , bLODActive(false)
        , CurrentOptimization(EAnimOptimizationLevel::None)
    {}
};

UCLASS(Blueprintable)
class ULesFightAnimationPerformance : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationPerformance();

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void RegisterAnimComponent(ULesFightCharacterAnimationComponent* AnimComp);

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void UnregisterAnimComponent(ULesFightCharacterAnimationComponent* AnimComp);

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void SetAnimationBudget(float BudgetMs) { AnimationBudgetMs = BudgetMs; }

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void SetLODEnabled(bool bEnable) { bLODEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void SetLODDistanceThresholds(float Near, float Medium, float Far);

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void SetOptimizationLevel(EAnimOptimizationLevel Level);

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    FAnimPerformanceMetrics GetMetrics() const { return CurrentMetrics; }

    UFUNCTION(BlueprintCallable, Category = "Animation Performance")
    void ForceOptimization(EAnimOptimizationLevel Level);

    UFUNCTION(BlueprintPure, Category = "Animation Performance")
    bool IsOverBudget() const { return bOverBudget; }

    UFUNCTION(BlueprintPure, Category = "Animation Performance")
    float GetBudgetUsage() const;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Animation Performance")
    TArray<TObjectPtr<ULesFightCharacterAnimationComponent>> RegisteredComponents;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Performance")
    FAnimPerformanceMetrics CurrentMetrics;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Performance")
    float AnimationBudgetMs;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Performance")
    float LODNearDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Performance")
    float LODMediumDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Performance")
    float LODFarDistance;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Performance")
    bool bLODEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Performance")
    bool bOverBudget;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Performance")
    EAnimOptimizationLevel CurrentOptimization;

private:
    float FrameTimeAccumulator;
    int32 FrameCount;
    TMap<TObjectPtr<ULesFightCharacterAnimationComponent>, float> ComponentFrameTimes;

    void CalculateLODLevels();
    void CalculateMetrics(float DeltaTime);
    void OptimizeAnimations();
};
