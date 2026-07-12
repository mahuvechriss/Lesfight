#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaAudio.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaAudio : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void InitializeAudio(FArenaInfo Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void SetWeatherAudio(EWeatherType Weather);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void PlayFootstepSound(ETerrainType Surface);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void PlayDestructionSound(EDestructionLevel Level);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void PlayAmbientSound(FName SoundName);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void SetAmbientVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void SetWeatherVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void SetCrowdVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void PlayCrowdReaction(FName ReactionType);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void StopAllSounds();

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    void SetMusicTrack(FName TrackName);

    UFUNCTION(BlueprintCallable, Category = "Arena|Audio")
    FArenaAudioState GetAudioState() const;

protected:
    UPROPERTY()
    FArenaAudioState CurrentAudio;

    UPROPERTY()
    TMap<ETerrainType, FString> FootstepLibraries;

    UPROPERTY()
    TArray<FString> ActiveAmbientSounds;

    UPROPERTY()
    float MasterVolume = 1.0f;

private:
    TWeakObjectPtr<class ULesFightArenaWorldManager> OwnerManager;
};
