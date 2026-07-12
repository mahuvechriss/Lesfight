#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightMartialArtsPerformance.generated.h"

USTRUCT(BlueprintType)
struct FPerformanceMetrics
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    float AnimationBudgetMs;

    UPROPERTY(BlueprintReadOnly)
    float PhysicsBudgetMs;

    UPROPERTY(BlueprintReadOnly)
    float VFXBudgetMs;

    UPROPERTY(BlueprintReadOnly)
    float CameraBudgetMs;

    UPROPERTY(BlueprintReadOnly)
    float TotalFrameTimeMs;

    UPROPERTY(BlueprintReadOnly)
    int32 ActiveAnimations;

    UPROPERTY(BlueprintReadOnly)
    int32 ActiveVFX;

    UPROPERTY(BlueprintReadOnly)
    float AnimationLODDistance;

    UPROPERTY(BlueprintReadOnly)
    float PhysicsLODDistance;

    UPROPERTY(BlueprintReadOnly)
    float VFXLODDistance;

    FPerformanceMetrics()
        : AnimationBudgetMs(5.0f), PhysicsBudgetMs(3.0f)
        , VFXBudgetMs(2.0f), CameraBudgetMs(1.0f)
        , TotalFrameTimeMs(0.0f)
        , ActiveAnimations(0), ActiveVFX(0)
        , AnimationLODDistance(1500.0f)
        , PhysicsLODDistance(1000.0f)
        , VFXLODDistance(2000.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightMartialArtsPerformance : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMartialArtsPerformance();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Performance")
    void SetAnimationLOD(float Distance);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Performance")
    void SetPhysicsLOD(float Distance);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Performance")
    void SetVFXLOD(float Distance);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Performance")
    void SetTargetFrameRate(int32 FPS);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Performance")
    void EnableDynamicLOD(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Performance")
    void SetQualityPreset(int32 PresetLevel);

    UFUNCTION(BlueprintPure, Category = "MartialArts|Performance")
    FPerformanceMetrics GetMetrics() const { return CurrentMetrics; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Performance")
    float GetAnimationBudgetMs() const { return CurrentMetrics.AnimationBudgetMs; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Performance")
    float GetPhysicsBudgetMs() const { return CurrentMetrics.PhysicsBudgetMs; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Performance")
    int32 GetActiveAnimationCount() const { return CurrentMetrics.ActiveAnimations; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|Performance")
    int32 GetActiveVFXCount() const { return CurrentMetrics.ActiveVFX; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Performance")
    void Reset();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    FPerformanceMetrics CurrentMetrics;

    UPROPERTY(Write, BlueprintReadOnly, Category = "Configuration")
    float TargetFrameRate;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bDynamicLODEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    int32 CurrentQualityPreset;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    float FrameTimeHistory;
    int32 FrameCount;

    void UpdateMetrics(float DeltaTime);
    void ApplyDynamicLOD(float DeltaTime);
    void ApplyQualityPreset(int32 Preset);
};
