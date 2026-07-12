#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/LevelStreaming.h"
#include "LesFightLevelManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoadStarted, const FString&, LevelName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelLoadComplete, const FString&, LevelName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUnloadComplete, const FString&, LevelName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelTransitionComplete);

USTRUCT(BlueprintType)
struct FLevelTransitionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LevelName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FadeOutDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FadeInDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinimumLoadScreenTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor FadeColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShowLoadingScreen;

    FLevelTransitionData()
        : LevelName(NAME_None)
        , FadeOutDuration(0.5f)
        , FadeInDuration(0.5f)
        , MinimumLoadScreenTime(1.0f)
        , FadeColor(FLinearColor::Black)
        , bShowLoadingScreen(true)
    {}
};

UCLASS(Blueprintable, Config = Game)
class ULesFightLevelManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightLevelManager();

    UFUNCTION(BlueprintCallable, Category = "Level")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Level")
    void LoadLevel(const FLevelTransitionData& TransitionData);

    UFUNCTION(BlueprintCallable, Category = "Level")
    void LoadLevelByName(const FString& LevelName, bool bShowLoading = true);

    UFUNCTION(BlueprintCallable, Category = "Level")
    void AsyncLoadLevel(const FString& LevelName);

    UFUNCTION(BlueprintCallable, Category = "Level")
    void UnloadLevel(const FString& LevelName);

    UFUNCTION(BlueprintCallable, Category = "Level")
    void OpenMainMenu();

    UFUNCTION(BlueprintCallable, Category = "Level")
    void OpenTrainingArena();

    UFUNCTION(BlueprintCallable, Category = "Level")
    void RestartCurrentLevel();

    UFUNCTION(BlueprintPure, Category = "Level")
    FString GetCurrentLevelName() const;

    UFUNCTION(BlueprintPure, Category = "Level")
    float GetLoadProgress() const { return LoadProgress; }

    UFUNCTION(BlueprintPure, Category = "Level")
    bool IsLevelLoading() const { return bIsLoading; }

    UFUNCTION(BlueprintPure, Category = "Level")
    TArray<FString> GetAvailableArenas() const { return AvailableArenas; }

    UFUNCTION(BlueprintCallable, Category = "Level")
    void OnLevelLoaded();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Maps")
    FString MainMenuMap;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Maps")
    FString TrainingArenaMap;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Maps")
    TArray<FString> AvailableArenas;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Maps")
    TArray<FString> AvailableMaps;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLevelLoadStarted OnLevelLoadStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLevelLoadComplete OnLevelLoadComplete;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLevelUnloadComplete OnLevelUnloadComplete;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnLevelTransitionComplete OnLevelTransitionComplete;

private:
    float LoadProgress;
    bool bIsLoading;

    TMap<FString, TObjectPtr<ULevelStreaming>> LoadedStreamingLevels;
    TArray<FString> LevelsToLoad;

    void BeginLevelTransition(const FLevelTransitionData& Data);
    void OnAsyncLoadComplete();
    void PerformLevelTransition(const FString& LevelName);
};
