#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightCameraEffects.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCameraEffects : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void PlayCameraShake(EImpactVFXType Type, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void PlayImpactShake(float Intensity, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void PlayZoomEffect(float TargetFOV, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void PlayImpactZoom(float Duration);

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void PlayDynamicFOV(float Fighter1Dist, float Fighter2Dist);

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void PlayRotationEffect(FRotator Offset, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void ResetCamera();

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    void SetCameraShakeEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Camera Effects")
    bool IsCameraShakeEnabled() const;

    void Initialize(ULesFightVFXWorldManager* InOwner);

protected:
    UPROPERTY()
    FCameraEffectDef CurrentEffect;

    UPROPERTY()
    TMap<EImpactVFXType, FCameraEffectDef> CameraEffectDefs;

    UPROPERTY()
    bool bShakeEnabled;

    UPROPERTY()
    float DefaultFOV;

private:
    TWeakObjectPtr<class ULesFightVFXWorldManager> OwnerManager;
};
