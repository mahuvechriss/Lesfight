#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationManager.generated.h"

class ALesFightBaseFighter;
class ULesFightCharacterAnimationComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGlobalAnimationEvent, FName, EventName, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationQualityChanged, EAnimationQuality, NewQuality);

UCLASS(Blueprintable)
class ULesFightAnimationManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationManager();

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void RegisterCharacter(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void UnregisterCharacter(ALesFightBaseFighter* Fighter);

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void SetGlobalAnimationQuality(EAnimationQuality Quality);

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void SetGlobalPlayRate(float Rate);

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void BroadcastGlobalEvent(FName EventName, AActor* Instigator);

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void PauseAllAnimations();

    UFUNCTION(BlueprintCallable, Category = "Animation Manager")
    void ResumeAllAnimations();

    UFUNCTION(BlueprintBlueprintCallable, Category = "Animation Manager")
    void SetSlowMotion(float TimeDilation, float Duration);

    UFUNCTION(BlueprintPure, Category = "Animation Manager")
    TArray<ALesFightBaseFighter*> GetRegisteredFighters() const { return RegisteredFighters; }

    UFUNCTION(BlueprintPure, Category = "Animation Manager")
    EAnimationQuality GetCurrentQuality() const { return CurrentQuality; }

    UFUNCTION(BlueprintPure, Category = "Animation Manager")
    float GetGlobalPlayRate() const { return GlobalPlayRate; }

    UFUNCTION(BlueprintPure, Category = "Animation Manager")
    bool IsGlobalPaused() const { return bGlobalPaused; }

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnGlobalAnimationEvent OnGlobalAnimationEvent;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnAnimationQualityChanged OnAnimationQualityChanged;

    UPROPERTY(BlueprintReadOnly, Category = "Animation Manager")
    TArray<TObjectPtr<ALesFightBaseFighter>> RegisteredFighters;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Manager")
    EAnimationQuality CurrentQuality;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Manager")
    float GlobalPlayRate;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation Manager")
    int32 MaxAnimatedCharacters;

private:
    bool bGlobalPaused;
    float SlowMotionTimer;
    float SlowMotionDuration;
    float OriginalTimeDilation;
};
