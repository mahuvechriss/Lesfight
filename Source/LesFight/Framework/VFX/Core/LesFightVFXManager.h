#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightVFXManager.generated.h"

class ULesFightVFXWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVFXInitialized);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVFXError, FString, Error);

UCLASS(Blueprintable)
class ULesFightVFXManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightVFXManager();

    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void PlayEffect(FName EffectName, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable)
    void StopEffect(FName EffectName);

    UFUNCTION(BlueprintCallable)
    void StopAllEffects();

    UFUNCTION(BlueprintCallable)
    void PauseAllEffects();

    UFUNCTION(BlueprintCallable)
    void ResumeAllEffects();

    UFUNCTION(BlueprintCallable)
    int32 GetActiveEffectCount() const;

    UFUNCTION(BlueprintCallable)
    void SetGlobalVFXScale(float Scale);

    UFUNCTION(BlueprintCallable)
    bool IsEffectPlaying(FName EffectName) const;

    UPROPERTY(BlueprintAssignable)
    FOnVFXInitialized OnVFXInitialized;

    UPROPERTY(BlueprintAssignable)
    FOnVFXError OnVFXError;

protected:
    UPROPERTY()
    TMap<FName, float> ActiveEffects;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 MaxActiveEffects = 100;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float GlobalVFXScale = 1.0f;

    UPROPERTY()
    bool bPaused = false;

    UPROPERTY()
    bool bInitialized = false;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;
};
