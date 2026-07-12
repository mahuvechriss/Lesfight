#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAttackData.h"
#include "LesFightCombatAudioHandler.generated.h"

class ULesFightCombatComponent;
class ULesFightAudioManager;

UCLASS(Blueprintable)
class ULesFightCombatAudioHandler : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCombatAudioHandler();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void Initialize(ULesFightCombatComponent* CombatComp, ULesFightAudioManager* AudioMgr);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayHitSound(EHitReaction ReactionType);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayBlockSound();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayWhiffSound();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayKOSound();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayRoundStartSound();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayRoundEndSound();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayUltimateSound();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlaySpecialSound();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayHitSoundByType(EAttackType AttackType);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetCombatMusic(USoundBase* CombatMusic);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void StopCombatMusic();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetHitSoundVolume(float Volume) { HitSoundVolume = Volume; }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> HitSoundLight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> HitSoundHeavy;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> HitSoundKnockback;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> HitSoundLaunch;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> BlockSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> WhiffSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> KOSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> RoundStartSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> RoundEndSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> UltimateSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> SpecialSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    TObjectPtr<USoundBase> CombatMusic;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
    float HitSoundVolume;

private:
    TWeakObjectPtr<ULesFightAudioManager> AudioManager;
    TWeakObjectPtr<ULesFightCombatComponent> CombatComponent;

    USoundBase* GetHitSoundForReaction(EHitReaction ReactionType) const;
};
