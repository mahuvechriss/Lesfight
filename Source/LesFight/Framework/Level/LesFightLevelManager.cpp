#include "LesFightLevelManager.h"
#include "LesFight.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ULesFightLevelManager::ULesFightLevelManager()
    : LoadProgress(0.0f)
    , bIsLoading(false)
    , MainMenuMap(TEXT("/Game/Maps/MainMenu"))
    , TrainingArenaMap(TEXT("/Game/Maps/TrainingArena"))
{
}

void ULesFightLevelManager::Initialize()
{
    AvailableMaps.Add(MainMenuMap);
    AvailableMaps.Add(TrainingArenaMap);
    AvailableArenas.Add(TrainingArenaMap);
    UE_LOG(LogLesFight, Log, TEXT("LevelManager initialized"));
}

void ULesFightLevelManager::LoadLevel(const FLevelTransitionData& TransitionData)
{
    if (bIsLoading) return;

    bIsLoading = true;
    LoadProgress = 0.0f;

    OnLevelLoadStarted.Broadcast(TransitionData.LevelName.ToString());
    UE_LOG(LogLesFight, Log, TEXT("Loading level: %s"), *TransitionData.LevelName.ToString());

    PerformLevelTransition(TransitionData.LevelName.ToString());
}

void ULesFightLevelManager::LoadLevelByName(const FString& LevelName, bool bShowLoading)
{
    if (bIsLoading) return;

    FLevelTransitionData TransitionData;
    TransitionData.LevelName = FName(*LevelName);
    TransitionData.bShowLoadingScreen = bShowLoading;

    LoadLevel(TransitionData);
}

void ULesFightLevelManager::AsyncLoadLevel(const FString& LevelName)
{
    if (!GetWorld()) return;

    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.ExecutionFunction = "OnAsyncLoadComplete";
    LatentInfo.Linkage = 0;
    LatentInfo.UUID = __LINE__;

    UGameplayStatics::LoadStreamLevel(this, FName(*LevelName), true, true, LatentInfo);
}

void ULesFightLevelManager::UnloadLevel(const FString& LevelName)
{
    if (!GetWorld()) return;

    FLatentActionInfo LatentInfo;
    UGameplayStatics::UnloadStreamLevel(this, FName(*LevelName), LatentInfo);
}

void ULesFightLevelManager::OpenMainMenu()
{
    LoadLevelByName(MainMenuMap);
}

void ULesFightLevelManager::OpenTrainingArena()
{
    LoadLevelByName(TrainingArenaMap);
}

void ULesFightLevelManager::RestartCurrentLevel()
{
    if (!GetWorld()) return;
    FString CurrentLevel = GetCurrentLevelName();
    LoadLevelByName(CurrentLevel);
}

FString ULesFightLevelManager::GetCurrentLevelName() const
{
    if (!GetWorld()) return TEXT("");
    return UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
}

void ULesFightLevelManager::OnLevelLoaded()
{
    bIsLoading = false;
    LoadProgress = 1.0f;

    FString CurrentLevel = GetCurrentLevelName();
    OnLevelLoadComplete.Broadcast(CurrentLevel);
    OnLevelTransitionComplete.Broadcast();

    UE_LOG(LogLesFight, Log, TEXT("Level loaded: %s"), *CurrentLevel);
}

void ULesFightLevelManager::BeginLevelTransition(const FLevelTransitionData& Data)
{
}

void ULesFightLevelManager::OnAsyncLoadComplete()
{
    OnLevelLoaded();
}

void ULesFightLevelManager::PerformLevelTransition(const FString& LevelName)
{
    if (!GetWorld()) return;

    UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName));
}
