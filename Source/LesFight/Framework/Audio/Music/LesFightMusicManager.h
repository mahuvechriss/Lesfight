#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightMusicManager.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightMusicManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void PlayMusic(EMusicState State, float FadeDuration = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void StopMusic(float FadeDuration);

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void PauseMusic();

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void ResumeMusic();

    UFUNCTION(BlueprintPure, Category = "Audio|Music")
    EMusicState GetCurrentState() const;

    UFUNCTION(BlueprintPure, Category = "Audio|Music")
    bool IsMusicPlaying() const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void SetIntensity(float Intensity);

    UFUNCTION(BlueprintPure, Category = "Audio|Music")
    float GetIntensity() const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Music")
    void CrossfadeTo(EMusicState TargetState, float Duration);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    EMusicState CurrentState;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    float CurrentIntensity;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    float MasterMusicVolume;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    bool bMusicPlaying;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Music")
    TMap<EMusicState, FMusicStateData> MusicDatabase;

private:
    void BuildMusicDatabase();

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
