#include "LesFightArenaLoader.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaDataSystem.h"
#include "Kismet/GameplayStatics.h"

void ULesFightArenaLoader::Initialize(ULesFightArenaWorldManager* InOwnerManager, ULesFightArenaDataSystem* InDataSystem)
{
    OwnerManager = InOwnerManager;
    DataSystem = InDataSystem;
    CurrentArena = EArenaType::MAX;
    LoadProgress = 0.0f;
    LoadingTime = 0.0f;
    bArenaLoaded = false;
    bStreaming = false;
}

void ULesFightArenaLoader::LoadArena(EArenaType Arena)
{
    if (Arena == EArenaType::MAX)
    {
        OnArenaLoadFailed.Broadcast(TEXT("Invalid arena type"));
        return;
    }

    if (!DataSystem.IsValid())
    {
        OnArenaLoadFailed.Broadcast(TEXT("Arena data system not available"));
        return;
    }

    FArenaInfo Info = DataSystem->GetArenaInfo(Arena);
    if (Info.ArenaType == EArenaType::MAX)
    {
        OnArenaLoadFailed.Broadcast(FString::Printf(TEXT("Arena %d not found in database"), (uint8)Arena));
        return;
    }

    CurrentArena = Arena;
    CurrentLevelPath = Info.LevelPath;
    LoadProgress = 0.0f;
    LoadingTime = 0.0f;
    bArenaLoaded = false;
    bStreaming = false;

    OnArenaLoadStarted.Broadcast(Arena);

    UGameplayStatics::OpenLevel(GetWorld(), FName(*Info.LevelPath));

    bArenaLoaded = true;
    LoadProgress = 1.0f;
    OnArenaLoadComplete.Broadcast(Arena);
}

void ULesFightArenaLoader::UnloadCurrentArena()
{
    if (bArenaLoaded && CurrentArena != EArenaType::MAX)
    {
        OnArenaLoadStarted.Broadcast(CurrentArena);

        UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Entry")));

        CurrentArena = EArenaType::MAX;
        CurrentLevelPath.Empty();
        LoadProgress = 0.0f;
        LoadingTime = 0.0f;
        bArenaLoaded = false;
        bStreaming = false;
    }
}

void ULesFightArenaLoader::ReloadArena()
{
    if (CurrentArena != EArenaType::MAX)
    {
        LoadArena(CurrentArena);
    }
}

EArenaType ULesFightArenaLoader::GetCurrentArenaType() const
{
    return CurrentArena;
}

bool ULesFightArenaLoader::IsArenaLoaded() const
{
    return bArenaLoaded;
}

float ULesFightArenaLoader::GetLoadProgress() const
{
    return LoadProgress;
}

void ULesFightArenaLoader::LoadArenaAsync(EArenaType Arena)
{
    if (Arena == EArenaType::MAX)
    {
        OnArenaLoadFailed.Broadcast(TEXT("Invalid arena type"));
        return;
    }

    if (!DataSystem.IsValid())
    {
        OnArenaLoadFailed.Broadcast(TEXT("Arena data system not available"));
        return;
    }

    FArenaInfo Info = DataSystem->GetArenaInfo(Arena);
    if (Info.ArenaType == EArenaType::MAX)
    {
        OnArenaLoadFailed.Broadcast(FString::Printf(TEXT("Arena %d not found in database"), (uint8)Arena));
        return;
    }

    CurrentArena = Arena;
    CurrentLevelPath = Info.LevelPath;
    LoadProgress = 0.0f;
    LoadingTime = 0.0f;
    bArenaLoaded = false;
    bStreaming = true;

    OnArenaLoadStarted.Broadcast(Arena);

    FLatentActionInfo LatentInfo;
    UGameplayStatics::LoadStreamLevel(GetWorld(), FName(*Info.LevelPath), true, false, LatentInfo);
}

float ULesFightArenaLoader::GetLoadingTime() const
{
    return LoadingTime;
}

bool ULesFightArenaLoader::IsStreaming() const
{
    return bStreaming;
}

void ULesFightArenaLoader::Tick(float DeltaTime)
{
    if (!bArenaLoaded)
    {
        LoadingTime += DeltaTime;
        SimulateLoadProgress(DeltaTime);
    }
}

void ULesFightArenaLoader::SimulateLoadProgress(float DeltaTime)
{
    if (LoadProgress < 1.0f)
    {
        LoadProgress = FMath::Clamp(LoadProgress + DeltaTime * 0.5f, 0.0f, 1.0f);

        if (LoadProgress >= 1.0f && !bArenaLoaded)
        {
            bArenaLoaded = true;
            bStreaming = false;
            OnArenaLoadComplete.Broadcast(CurrentArena);
        }
    }
}
