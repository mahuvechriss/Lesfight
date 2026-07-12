#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightMartialArtsVFX.generated.h"

UCLASS(Blueprintable)
class ULesFightMartialArtsVFX : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMartialArtsVFX();

    void Initialize(class ULesFightMartialArtsManager* InOwner);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayAttackTrail(EFightingStyle Style, int32 ComboStep);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayImpactEffect(FVector Location, float Force);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayDodgeTrail(EAdvancedDodgeType DodgeType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayCounterEffect(ECounterType CounterType);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayUltimateEffect(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayDustEffect(FVector Location, float Intensity);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayShockwave(FVector Location, float Radius);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayAura(EFightingStyle Style, bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void PlayFootstepDust(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void SetVFXProfile(EFightingStyle Style, const FStyleVFXProfile& Profile);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void SetVFXIntensity(EMartialArtsVFXIntensity Intensity);

    UFUNCTION(BlueprintCallable, Category = "MartialArts|VFX")
    void Reset();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    TMap<EFightingStyle, FStyleVFXProfile> StyleVFXProfiles;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    EMartialArtsVFXIntensity CurrentIntensity;

private:
    TWeakObjectPtr<class ULesFightMartialArtsManager> OwnerManager;
    EFightingStyle CurrentStyle;

    void SpawnEffect(FName EffectName, FVector Location, FRotator Rotation = FRotator::ZeroRotator);
    void SpawnTrailEffect(const TArray<FName>& TrailEffects);
    void SpawnNiagaraSystem(FName SystemName, FVector Location);
    void ApplyDynamicLighting(FVector Location, FLinearColor Color, float Intensity);
    void ApplyCameraShake(float Intensity);
};
