#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAmbientAudioManager.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightAmbientAudioManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Ambient")
    void PlayAmbientSound(FName SoundName, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Ambient")
    void StopAmbientSound(FName SoundName);

    UFUNCTION(BlueprintCallable, Category = "Ambient")
    void StopAllAmbient();

    UFUNCTION(BlueprintCallable, Category = "Ambient")
    void SetAmbientZone(FName ZoneName);

    UFUNCTION(BlueprintCallable, Category = "Ambient")
    void SetAmbientVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Ambient")
    void CrossfadeAmbient(FName FromSound, FName ToSound, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Ambient")
    TMap<FName, float> GetActiveAmbientSounds() const;

    UFUNCTION(BlueprintCallable, Category = "Ambient")
    bool IsAmbientPlaying(FName SoundName) const;

protected:
    UPROPERTY()
    TMap<FName, float> ActiveAmbients;

    UPROPERTY()
    TArray<FString> AmbientSoundLibrary;

    UPROPERTY()
    float GlobalAmbientVolume = 0.6f;

    UPROPERTY()
    int32 MaxAmbientSounds = 8;

private:
    friend class ULesFightAudioWorldManager;

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
