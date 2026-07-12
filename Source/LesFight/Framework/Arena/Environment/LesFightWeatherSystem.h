#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightWeatherSystem.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightWeatherSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    void ActivateWeather(EWeatherType Type, EWeatherIntensity Intensity);

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    void DeactivateWeather();

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    void UpdateWeather(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    EWeatherType GetActiveWeather() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    EWeatherIntensity GetIntensity() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    void GetWindParams(FVector& Direction, float& Speed) const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    void SetWind(FVector Direction, float Speed);

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    FString GenerateRainParticles() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    FString GenerateSnowParticles() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    FString GenerateFog() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    bool IsWeatherActive() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Weather")
    float GetVisibilityModifier() const;

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Weather")
    EWeatherType ActiveWeather;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Weather")
    EWeatherIntensity Intensity;

    UPROPERTY(BlueprintReadWrite, Category = "Arena|Weather")
    FVector WindDirection;

    UPROPERTY(BlueprintReadWrite, Category = "Arena|Weather")
    float WindSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Weather")
    float VisibilityModifier;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Weather")
    float ParticleDensity;

    UPROPERTY(BlueprintReadWrite, Category = "Arena|Weather")
    TMap<EWeatherType, float> IntensityScales;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;
};
