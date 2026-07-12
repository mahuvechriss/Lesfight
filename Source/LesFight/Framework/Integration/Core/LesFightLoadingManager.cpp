#include "Framework/Integration/Core/LesFightLoadingManager.h"
#include "Blueprint/UserWidget.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

void ULesFightLoadingManager::Initialize()
{
    PendingTasks.Empty();
    ActiveTasks.Empty();
    CompletedTasks.Empty();
    CurrentPhase = ELoadingPhase::Prerequisites;
    OverallProgress = 0.0f;
    MinimumLoadTime = 1.0f;
    bLoading = false;
    CurrentContext = NAME_None;
    LoadedLevels.Empty();
    ActiveLoadingWidget = nullptr;
    LoadStartTime = 0.0;
}

void ULesFightLoadingManager::Shutdown()
{
    HideLoadingScreen();
    PendingTasks.Empty();
    ActiveTasks.Empty();
    CompletedTasks.Empty();
    bLoading = false;
}

void ULesFightLoadingManager::BeginLoading(FName ContextName)
{
    PendingTasks.Empty();
    ActiveTasks.Empty();
    CompletedTasks.Empty();
    OverallProgress = 0.0f;
    bLoading = true;
    CurrentContext = ContextName;
    CurrentPhase = ELoadingPhase::Prerequisites;
    LoadStartTime = FPlatformTime::Seconds();

    OnLoadingStarted.Broadcast(ContextName);
}

void ULesFightLoadingManager::AddTask(const FLoadingTask& Task)
{
    PendingTasks.Add(Task);
}

void ULesFightLoadingManager::UpdateTask(FName TaskName, float Progress, FText Status)
{
    auto UpdateInArray = [&](TArray<FLoadingTask>& Array)
    {
        for (FLoadingTask& Task : Array)
        {
            if (Task.TaskName == TaskName)
            {
                Task.Progress = Progress;
                if (!Status.IsEmpty())
                {
                    Task.Description = Status;
                }
                return true;
            }
        }
        return false;
    };

    if (!UpdateInArray(ActiveTasks))
    {
        UpdateInArray(PendingTasks);
    }
}

void ULesFightLoadingManager::CompleteTask(FName TaskName)
{
    for (int32 i = ActiveTasks.Num() - 1; i >= 0; i--)
    {
        if (ActiveTasks[i].TaskName == TaskName)
        {
            FLoadingTask Task = ActiveTasks[i];
            Task.Progress = 1.0f;
            Task.Phase = ELoadingPhase::Complete;
            CompletedTasks.Add(Task);
            ActiveTasks.RemoveAt(i);
            return;
        }
    }
}

float ULesFightLoadingManager::GetOverallProgress() const
{
    int32 TotalTasks = PendingTasks.Num() + ActiveTasks.Num() + CompletedTasks.Num();
    if (TotalTasks == 0)
    {
        return 1.0f;
    }

    float TotalWeight = 0.0f;
    float CompletedWeight = 0.0f;

    for (const FLoadingTask& Task : PendingTasks)
    {
        TotalWeight += 1.0f;
    }
    for (const FLoadingTask& Task : ActiveTasks)
    {
        TotalWeight += 1.0f;
        CompletedWeight += Task.Progress;
    }
    for (const FLoadingTask& Task : CompletedTasks)
    {
        TotalWeight += 1.0f;
        CompletedWeight += 1.0f;
    }

    return TotalWeight > 0.0f ? CompletedWeight / TotalWeight : 1.0f;
}

ELoadingPhase ULesFightLoadingManager::GetCurrentPhase() const
{
    return CurrentPhase;
}

void ULesFightLoadingManager::SetPhase(ELoadingPhase NewPhase)
{
    CurrentPhase = NewPhase;
}

TArray<FLoadingTask> ULesFightLoadingManager::GetTasks() const
{
    TArray<FLoadingTask> AllTasks;
    AllTasks.Append(PendingTasks);
    AllTasks.Append(ActiveTasks);
    AllTasks.Append(CompletedTasks);
    return AllTasks;
}

TArray<FLoadingTask> ULesFightLoadingManager::GetActiveTasks() const
{
    return ActiveTasks;
}

TArray<FLoadingTask> ULesFightLoadingManager::GetCompletedTasks() const
{
    return CompletedTasks;
}

void ULesFightLoadingManager::ShowLoadingScreen(UUserWidget* LoadingWidget)
{
    if (!LoadingWidget)
    {
        return;
    }

    ActiveLoadingWidget = LoadingWidget;

    APlayerController* PC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
    if (PC)
    {
        LoadingWidget->AddToViewport(10000);
    }
}

void ULesFightLoadingManager::HideLoadingScreen()
{
    if (ActiveLoadingWidget && ActiveLoadingWidget->IsValidLowLevel())
    {
        ActiveLoadingWidget->RemoveFromParent();
    }
    ActiveLoadingWidget = nullptr;
}

bool ULesFightLoadingManager::IsLoading() const
{
    return bLoading;
}

void ULesFightLoadingManager::PreloadAssets(const TArray<TSoftObjectPtr<UObject>>& Assets)
{
    if (Assets.Num() == 0)
    {
        return;
    }

    TArray<FSoftObjectPath> Paths;
    for (const TSoftObjectPtr<UObject>& Asset : Assets)
    {
        Paths.Add(Asset.ToSoftObjectPath());
    }

    UAssetManager& AssetManager = UAssetManager::Get();
    FStreamableManager& StreamableManager = AssetManager.GetStreamableManager();
    StreamableManager.RequestAsyncLoad(Paths);
}

void ULesFightLoadingManager::SetMinimumLoadTime(float Seconds)
{
    MinimumLoadTime = Seconds;
}

void ULesFightLoadingManager::AsyncLoadLevel(FName LevelName)
{
    if (UWorld* World = GetWorld())
    {
        UGameplayStatics::OpenLevel(World, LevelName);
        LoadedLevels.Add(LevelName.ToString());
    }
}
