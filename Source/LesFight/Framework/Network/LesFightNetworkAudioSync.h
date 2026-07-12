#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkAudioSync.generated.h"

USTRUCT(BlueprintType)
struct FNetworkAudioEvent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FName SoundID;

    UPROPERTY(BlueprintReadOnly)
    FVector Location;

    UPROPERTY(BlueprintReadOnly)
    float Volume;

    UPROPERTY(BlueprintReadOnly)
    float Pitch;

    UPROPERTY(BlueprintReadOnly)
    int32 PlayerIndex;

    UPROPERTY(BlueprintReadOnly)
    float Timestamp;

    FNetworkAudioEvent()
        : SoundID(NAME_None)
        , Location(FVector::ZeroVector)
        , Volume(1.0f), Pitch(1.0f)
        , PlayerIndex(-1)
        , Timestamp(0.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightNetworkAudioSync : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkAudioSync();

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void PlaySyncedSound(FName SoundID, FVector Location, float Volume = 1.0f, float Pitch = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void PlaySyncedSoundForPlayer(int32 PlayerIndex, FName SoundID, FVector Location, float Volume = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void StopSyncedSound(FName SoundID);

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void SetVolumeMultiplier(float Multiplier);

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void SyncAudioState(float GlobalVolume, TArray<FName> ActiveSounds);

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void ClearPendingAudio();

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    int32 GetPendingAudioCount() const { return PendingAudioEvents.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Network|Audio")
    void SetEnabled(bool bInEnabled) { bEnabled = bInEnabled; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    bool bEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FNetworkAudioEvent> PendingAudioEvents;

private:
    void BroadcastAudioEvent(const FNetworkAudioEvent& Event);
};
