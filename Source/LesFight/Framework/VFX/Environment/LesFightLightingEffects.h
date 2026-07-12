#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightLightingEffects.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightLightingEffects : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Lighting Effects")
    void SetCombatLighting(FVector Location, FLinearColor Color, float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Lighting Effects")
    void FlashLight(FLinearColor Color, float Duration, float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Lighting Effects")
    void PulseLight(FLinearColor Color, float Speed, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Lighting Effects")
    void SetCharacterGlow(AActor* Character, FLinearColor Color, float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Lighting Effects")
    void ResetLighting();

    UFUNCTION(BlueprintCallable, Category = "Lighting Effects")
    void SetLightingIntensity(float Intensity);

    void Initialize(ULesFightVFXWorldManager* InOwner);

protected:
    UPROPERTY()
    bool bCustomLightingActive;

    UPROPERTY()
    float CustomLightingIntensity;

    UPROPERTY()
    FLinearColor CurrentFlashColor;

    UPROPERTY()
    float FlashTimer;

    UPROPERTY()
    TMap<AActor*, FLinearColor> CharacterGlows;

private:
    TWeakObjectPtr<class ULesFightVFXWorldManager> OwnerManager;
};
