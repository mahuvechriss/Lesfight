#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightAudioComponent.generated.h"

UENUM(BlueprintType)
enum class ECharacterVoiceType : uint8
{
    None,
    Victory,
    Defeat,
    Grunt,
    Taunt,
    BreathHeavy,
    BreathNormal
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoicePlayed, ECharacterVoiceType, VoiceType);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightAudioComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightAudioComponent();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void Initialize(const TArray<TSoftObjectPtr<USoundBase>>& InFootsteps,
                    const TArray<TSoftObjectPtr<USoundBase>>& InBreathing,
                    const TArray<TSoftObjectPtr<USoundBase>>& InGruntSounds,
                    USoundBase* InVictoryVoice,
                    USoundBase* InDefeatVoice,
                    const TArray<TSoftObjectPtr<USoundBase>>& InTauntSounds);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayFootstep();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayBreath(bool bHeavy = false);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayVoice(ECharacterVoiceType VoiceType);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayVictoryVoice();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayDefeatVoice();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayGrunt();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayTaunt();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetVoicePitch(float Pitch) { VoicePitchMultiplier = Pitch; }

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetFootstepVolume(float Volume) { FootstepVolume = Volume; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> FootstepSounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> BreathingSounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> GruntSounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> TauntSounds;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> VictoryVoice;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> DefeatVoice;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnVoicePlayed OnVoicePlayed;

private:
    float VoicePitchMultiplier;
    float FootstepVolume;
    int32 LastFootstepIndex;

    USoundBase* GetRandomSound(const TArray<TSoftObjectPtr<USoundBase>>& Sounds) const;
    void PlaySoundAtCharacter(USoundBase* Sound, float VolumeMultiplier = 1.0f);
};
