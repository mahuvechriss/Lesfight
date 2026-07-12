#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightCinematicCombat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinematicTriggered, ECinematicEffect, EffectType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCinematicEnded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlowMotionChanged, float, TimeScale);

UCLASS(Blueprintable)
class ULesFightCinematicCombat : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCinematicCombat();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void TriggerCinematicEffect(ECinematicEffect EffectType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void StartSlowMotion(float TimeScale = 0.25f, float Duration = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void StopSlowMotion();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    bool IsSlowMotionActive() const { return bSlowMotionActive; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    float GetCurrentTimeScale() const { return CurrentTimeScale; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void SetActiveCamera(ECinematicEffect EffectType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void ResetCamera();

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void PlayUltimateCinematic(FName UltimateMontageName);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void PlaySignatureMove(FName SignatureMontageName);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void PlayVictoryCutscene(int32 WinnerIndex);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void TriggerDramaticImpact(FVector ImpactLocation, float Radius = 300.0f);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void SetCinematicData(const TMap<ECinematicEffect, FCinematicEffectData>& Data);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|Cinematic")
    void Reset();

protected:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCinematicTriggered OnCinematicTriggered;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCinematicStarted OnCinematicStarted;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCinematicEnded OnCinematicEnded;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnSlowMotionChanged OnSlowMotionChanged;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bSlowMotionActive;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float CurrentTimeScale;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    float SlowMotionTimer;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bCinematicActive;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TMap<ECinematicEffect, FCinematicEffectData> CinematicDefinitions;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    ECinematicEffect ActiveEffect;
    ECinematicEffect LastCameraEffect;
    float DefaultTimeScale;
    float CameraBlendTimer;

    void ApplySlowMotion(float TimeScale, float Duration);
    void RevertTimeScale();
    void UpdateCamera(float DeltaTime);
    void PlayCameraShake(ECinematicEffect EffectType);
};
