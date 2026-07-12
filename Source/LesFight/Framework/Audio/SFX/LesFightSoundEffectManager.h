#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightSoundEffectManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSoundEffectManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "SFX")
    void PlayCombatSound(ECombatSoundType Type, FVector Location, float VolumeMod = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "SFX")
    void PlayMovementSound(EMovementSoundType Type, FVector Location, float VolumeMod = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "SFX")
    void PreloadSoundBank(FName BankName);

    UFUNCTION(BlueprintCallable, Category = "SFX")
    int32 GetActiveSFXCount() const;

    UFUNCTION(BlueprintCallable, Category = "SFX")
    void SetSFXPoolSize(int32 Size);

    UFUNCTION(BlueprintCallable, Category = "SFX")
    void StopAllSFX();

    UFUNCTION(BlueprintCallable, Category = "SFX")
    bool IsSoundPlaying(FName SoundName) const;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "SFX")
    TMap<ECombatSoundType, FCombatSoundDef> CombatSounds;

    UPROPERTY(BlueprintReadWrite, Category = "SFX")
    TMap<EMovementSoundType, FCombatSoundDef> MovementSounds;

    UPROPERTY(BlueprintReadWrite, Category = "SFX")
    int32 SFXPoolSize = 64;

    UPROPERTY(BlueprintReadWrite, Category = "SFX")
    TArray<FName> ActiveSounds;

    UPROPERTY(BlueprintReadWrite, Category = "SFX")
    TMap<FName, int32> SoundUsageCount;

private:
    TWeakObjectPtr<class ULesFightAudioWorldManager> OwnerManager;
};
