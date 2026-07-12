#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightSpatialAudioSystem.generated.h"

class ULesFightAudioWorldManager;

UCLASS(Blueprintable)
class ULesFightSpatialAudioSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Spatial")
    void SetSoundSpatialization(FName SoundName, bool bEnable3D);

    UFUNCTION(BlueprintCallable, Category = "Spatial")
    void SetAttenuation(FName SoundName, float MinDist, float MaxDist);

    UFUNCTION(BlueprintCallable, Category = "Spatial")
    void SetSpatialBlend(FName SoundName, float Blend3D);

    UFUNCTION(BlueprintCallable, Category = "Spatial")
    void UpdateListenerPosition(FVector Position, FVector Forward, FVector Up);

    UFUNCTION(BlueprintCallable, Category = "Spatial")
    float CalculateOcclusion(FVector ListenerPos, FVector SoundPos) const;

    UFUNCTION(BlueprintCallable, Category = "Spatial")
    float GetOcclusionValue() const;

    UFUNCTION(BlueprintCallable, Category = "Spatial")
    void EnableDoppler(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Spatial")
    int32 GetSpatialQuality() const;

protected:
    UPROPERTY()
    FVector ListenerPosition;

    UPROPERTY()
    FVector ListenerForward;

    UPROPERTY()
    bool bDopplerEnabled = false;

    UPROPERTY()
    float OcclusionValue = 0.0f;

    UPROPERTY()
    int32 SpatialQuality = 3;

    UPROPERTY()
    float DefaultMinDist = 100.0f;

    UPROPERTY()
    float DefaultMaxDist = 2000.0f;

private:
    friend class ULesFightAudioWorldManager;

    TWeakObjectPtr<ULesFightAudioWorldManager> OwnerManager;
};
