#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightImpactEffectSystem.generated.h"

class ULesFightVFXWorldManager;

UCLASS(Blueprintable)
class ULesFightImpactEffectSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightImpactEffectSystem();

    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void PlayImpactEffect(EImpactVFXType Type, FVector Location, FVector Normal, float Scale = 1.0f);

    UFUNCTION(BlueprintCallable)
    void PlayImpactAttached(EImpactVFXType Type, AActor* Target, FName BoneName);

    UFUNCTION(BlueprintCallable)
    FImpactVFXDef GetImpactDefinition(EImpactVFXType Type) const;

    UFUNCTION(BlueprintCallable)
    void SetImpactScale(float Scale);

    UFUNCTION(BlueprintCallable)
    float GetImpactScale() const;

    UFUNCTION(BlueprintCallable)
    void PreloadImpactEffects();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TMap<EImpactVFXType, FImpactVFXDef> ImpactDefinitions;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float GlobalImpactScale = 1.0f;

    UPROPERTY()
    TMap<EImpactVFXType, float> ImpactCooldowns;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;
};
