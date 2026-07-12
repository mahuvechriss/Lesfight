#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightMartialArtsAudio.generated.h"

UCLASS(Blueprintable)
class ULesFightMartialArtsAudio : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMartialArtsAudio();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayAttackSound(EFightingStyle Style, int32 ComboStep);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayHitSound(float ImpactForce);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayCounterSound(ECounterType CounterType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayUltimateSound(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayVictorySound(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayDefeatSound(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayFootstep(float Speed);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayClothingSound(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void PlayBreathingSound(float ExertionLevel);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void SetAudioProfile(EFightingStyle Style, const FStyleAudioProfile& Profile);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Audio")
    void Reset();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<EFightingStyle, FStyleAudioProfile> StyleAudioProfiles;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float BreathTimer;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float BreathInterval;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float VoiceCooldown;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    EFightingStyle CurrentStyle;
    float LastVoiceTime;
    float LastFootstepTime;

    void PlayVoiceFromSet(const TArray<FName>& VoiceSet);
    void PlaySoundFromSet(const TArray<FName>& SoundSet, FVector Location);
    FName GetRandomFromArray(const TArray<FName>& Array) const;
};
