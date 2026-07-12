#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightMotionEffectSystem.generated.h"

class ULesFightVFXWorldManager;

UCLASS(Blueprintable)
class ULesFightMotionEffectSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMotionEffectSystem();

    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void PlayMotionTrail(EMotionVFXType Type, FTransform Transform);

    UFUNCTION(BlueprintCallable)
    void PlayPunchTrail(FVector Start, FVector End);

    UFUNCTION(BlueprintCallable)
    void PlayKickTrail(FVector Start, FVector End);

    UFUNCTION(BlueprintCallable)
    void PlayDodgeTrail(AActor* Character);

    UFUNCTION(BlueprintCallable)
    void SpawnAfterimage(AActor* Character, float Duration);

    UFUNCTION(BlueprintCallable)
    void PlaySpeedLines(FVector Direction, float Speed);

    UFUNCTION(BlueprintCallable)
    void PlayAirDistortion(FVector Location);

    UFUNCTION(BlueprintCallable)
    void ClearAllTrails();

    UFUNCTION(BlueprintCallable)
    void SetTrailIntensity(float Intensity);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TMap<EMotionVFXType, FMotionTrailDef> MotionDefinitions;

    UPROPERTY()
    TArray<FName> ActiveTrails;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float TrailIntensity = 0.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 MaxAfterimages = 5;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 MaxActiveTrails = 20;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;
};
