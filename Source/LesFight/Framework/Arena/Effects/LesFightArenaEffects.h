#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaEffects.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaEffects : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Effects")
    void InitializeEffects(FArenaInfo Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Effects")
    void PlayImpactEffect(FVector Location, FVector Normal, ETerrainType Surface);

    UFUNCTION(BlueprintCallable, Category = "Arena|Effects")
    void PlayDestructionEffect(FVector Location, EDestructionLevel Level);

    UFUNCTION(BlueprintCallable, Category = "Arena|Effects")
    void PlayWeatherEffect(EWeatherType Weather);

    UFUNCTION(BlueprintCallable, Category = "Arena|Effects")
    void StopWeatherEffect();

    UFUNCTION(BlueprintCallable, Category = "Arena|Effects")
    void UpdateEffects(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Arena|Effects")
    void ClearAllEffects();

protected:
    UPROPERTY()
    TArray<FString> ActiveEffects;

    UPROPERTY()
    TMap<ETerrainType, FString> ImpactEffectPaths;

    UPROPERTY()
    TMap<EDestructionLevel, FString> DestructionEffectPaths;

    UPROPERTY()
    TMap<EWeatherType, FString> WeatherEffectPaths;

private:
    TWeakObjectPtr<class ULesFightArenaWorldManager> OwnerManager;
};
