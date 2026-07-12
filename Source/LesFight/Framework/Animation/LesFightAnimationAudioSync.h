#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationAudioSync.generated.h"

class ULesFightCharacterAnimationComponent;
class ULesFightAudioManager;

USTRUCT(BlueprintType)
struct FAnimAudioEvent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USoundBase> Sound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float VolumeMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PitchMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAttached;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AttachSocket;

    FAnimAudioEvent()
        : EventName(NAME_None), Sound(nullptr)
        , VolumeMultiplier(1.0f), PitchMultiplier(1.0f)
        , bAttached(false), AttachSocket(NAME_None)
    {}
};

UCLASS(Blueprintable)
class ULesFightAnimationAudioSync : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationAudioSync();

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void PlayFootstepSound(bool bIsRightFoot);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void PlayVoiceLine(ECharacterVoiceType VoiceType);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void PlayPunchSound(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void PlayKickSound(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void PlayClothingSound();

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void PlayLandingSound(float ImpactVelocity);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void PlayWhooshSound(float Speed);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void RegisterAudioEvent(const FAnimAudioEvent& AudioEvent);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void TriggerAudioEvent(FName EventName);

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void SetAudioEnabled(bool bEnable) { bAudioEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Animation Audio")
    void SetGlobalVolumeMultiplier(float Multiplier)
        { GlobalVolumeMultiplier = Multiplier; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Animation Audio")
    TMap<FName, FAnimAudioEvent> RegisteredAudioEvents;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Audio")
    float FootstepVolume;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Audio")
    float PunchVolume;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Audio")
    float KickVolume;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Audio")
    float LandingVolume;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Audio")
    float GlobalVolumeMultiplier;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Audio")
    bool bAudioEnabled;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<ULesFightAudioManager> AudioManager;
    USoundBase* GetFootstepSound(bool bRightFoot) const;
};
