#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioManager.generated.h"

class ULesFightAudioWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAudioError, FString, Error);

UCLASS(Blueprintable)
class ULesFightAudioManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|Manager")
    void Initialize(ULesFightAudioWorldManager* InOwnerManager);

    UFUNCTION(BlueprintCallable, Category = "Audio|Manager")
    void PlaySound(FName SoundName, FVector Location, AActor* Instigator);

    UFUNCTION(BlueprintCallable, Category = "Audio|Manager")
    void StopSound(FName SoundName);

    UFUNCTION(BlueprintCallable, Category = "Audio|Manager")
    void StopAllSounds();

    UFUNCTION(BlueprintCallable, Category = "Audio|Manager")
    void SetBusVolume(EAudioBusType Bus, float Volume);

    UFUNCTION(BlueprintPure, Category = "Audio|Manager")
    float GetBusVolume(EAudioBusType Bus) const;

    UFUNCTION(BlueprintCallable, Category = "Audio|Manager")
    void PauseAudio();

    UFUNCTION(BlueprintCallable, Category = "Audio|Manager")
    void ResumeAudio();

    UFUNCTION(BlueprintPure, Category = "Audio|Manager")
    bool IsPaused() const;

    UFUNCTION(BlueprintPure, Category = "Audio|Manager")
    int32 GetActiveSoundCount() const;

    UPROPERTY(BlueprintAssignable, Category = "Audio|Events")
    FOnAudioInitialized OnAudioInitialized;

    UPROPERTY(BlueprintAssignable, Category = "Audio|Events")
    FOnAudioError OnAudioError;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|Manager")
    TMap<EAudioBusType, float> BusVolumes;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Manager")
    int32 ActiveSoundCount;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Manager")
    bool bPaused;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Manager")
    bool bInitialized;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|Manager")
    TMap<FName, float> SoundTimers;

private:
    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
