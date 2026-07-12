#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightLoadingManager.generated.h"

class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingStarted, FName, Context);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoadingProgress, float, Progress, FText, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingComplete, FName, Context);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightLoadingManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void BeginLoading(FName ContextName);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void AddTask(const FLoadingTask& Task);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void UpdateTask(FName TaskName, float Progress, FText Status);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void CompleteTask(FName TaskName);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    float GetOverallProgress() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    ELoadingPhase GetCurrentPhase() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void SetPhase(ELoadingPhase NewPhase);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    TArray<FLoadingTask> GetTasks() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    TArray<FLoadingTask> GetActiveTasks() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    TArray<FLoadingTask> GetCompletedTasks() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void ShowLoadingScreen(UUserWidget* LoadingWidget);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void HideLoadingScreen();

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    bool IsLoading() const;

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void PreloadAssets(const TArray<TSoftObjectPtr<UObject>>& Assets);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void SetMinimumLoadTime(float Seconds);

    UFUNCTION(BlueprintCallable, Category = "Integration|LoadingManager")
    void AsyncLoadLevel(FName LevelName);

    UPROPERTY(BlueprintAssignable, Category = "Integration|LoadingManager")
    FOnLoadingStarted OnLoadingStarted;

    UPROPERTY(BlueprintAssignable, Category = "Integration|LoadingManager")
    FOnLoadingProgress OnLoadingProgress;

    UPROPERTY(BlueprintAssignable, Category = "Integration|LoadingManager")
    FOnLoadingComplete OnLoadingComplete;

protected:
    UPROPERTY()
    TArray<FLoadingTask> PendingTasks;

    UPROPERTY()
    TArray<FLoadingTask> ActiveTasks;

    UPROPERTY()
    TArray<FLoadingTask> CompletedTasks;

    UPROPERTY()
    ELoadingPhase CurrentPhase;

    UPROPERTY()
    float OverallProgress;

    UPROPERTY()
    float MinimumLoadTime;

    UPROPERTY()
    bool bLoading;

    UPROPERTY()
    FName CurrentContext;

    UPROPERTY()
    TArray<FString> LoadedLevels;

    UPROPERTY()
    UUserWidget* ActiveLoadingWidget;

    float LoadStartTime;
};
