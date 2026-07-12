#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaLoader.generated.h"

class ULesFightArenaWorldManager;
class ULesFightArenaDataSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArenaLoadStarted, EArenaType, Arena);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArenaLoadComplete, EArenaType, Arena);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArenaLoadFailed, FString, Error);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaLoader : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    void LoadArena(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    void UnloadCurrentArena();

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    void ReloadArena();

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    EArenaType GetCurrentArenaType() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    bool IsArenaLoaded() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    float GetLoadProgress() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    void LoadArenaAsync(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    float GetLoadingTime() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Loading")
    bool IsStreaming() const;

    UPROPERTY(BlueprintAssignable, Category = "Arena|Loading")
    FOnArenaLoadStarted OnArenaLoadStarted;

    UPROPERTY(BlueprintAssignable, Category = "Arena|Loading")
    FOnArenaLoadComplete OnArenaLoadComplete;

    UPROPERTY(BlueprintAssignable, Category = "Arena|Loading")
    FOnArenaLoadFailed OnArenaLoadFailed;

    void Initialize(ULesFightArenaWorldManager* InOwnerManager, ULesFightArenaDataSystem* InDataSystem);

    virtual void Tick(float DeltaTime);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Loading")
    EArenaType CurrentArena;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Loading")
    float LoadProgress;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Loading")
    float LoadingTime;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Loading")
    bool bArenaLoaded;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Loading")
    bool bStreaming;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Loading")
    FString CurrentLevelPath;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
    TWeakObjectPtr<ULesFightArenaDataSystem> DataSystem;

    void SimulateLoadProgress(float DeltaTime);
};
