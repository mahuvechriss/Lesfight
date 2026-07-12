#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightCinematicAudio.generated.h"

class ULesFightAudioWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinematicMoment, FString, MomentName);

UCLASS(Blueprintable)
class ULesFightCinematicAudio : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void BeginSlowMotion(float TimeDilation);

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void EndSlowMotion();

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void PlayUltimateAttackSequence(FName AttackerID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void PlayFinisherSequence(FName WinnerID);

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void PlayDramaticSilence(float Duration);

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void PlayImpactEmphasis(FVector Location, float Force);

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void PlayRoundStartSequence();

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void PlayRoundEndSequence();

    UFUNCTION(BlueprintCallable, Category = "Audio|Cinematic")
    void SetCinematicMode(bool bEnabled);

    UFUNCTION(BlueprintPure, Category = "Audio|Cinematic")
    bool IsCinematicMode() const;

    UPROPERTY(BlueprintAssignable, Category = "Audio|Cinematic|Events")
    FOnCinematicMoment OnCinematicMoment;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Cinematic")
    bool bCinematicMode;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Cinematic")
    bool bSlowMotion;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Cinematic")
    float OriginalTimeDilation;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Cinematic")
    TMap<FString, FString> CinematicSoundPaths;

private:
    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
