#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightEnergyEffectSystem.generated.h"

class ULesFightVFXWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightEnergyEffectSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SpawnEnergyWave(FVector Origin, FVector Direction, float Distance, EFightingStyle Style);

    UFUNCTION(BlueprintCallable)
    void SpawnShockwave(FVector Location, float Radius, float Force, EWaveType Type);

    UFUNCTION(BlueprintCallable)
    void SpawnAuraBurst(AActor* Character, float Radius);

    UFUNCTION(BlueprintCallable)
    void SpawnEnergyProjectile(FVector Start, FVector End, FLinearColor Color);

    UFUNCTION(BlueprintCallable)
    void SpawnImpactRing(FVector Location, float Radius, FLinearColor Color);

    UFUNCTION(BlueprintCallable)
    void ClearEnergyEffects();

    UFUNCTION(BlueprintCallable)
    void SetEnergyIntensity(float Intensity);

protected:
    UPROPERTY()
    TMap<EWaveType, FString> WaveNiagaraPaths;

    UPROPERTY()
    TArray<FName> ActiveEnergyEffects;

    UPROPERTY()
    float EnergyIntensity = 0.5f;

    UPROPERTY()
    int32 MaxEnergyEffects = 30;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;

public:
    void Initialize(ULesFightVFXWorldManager* InManager);
};
