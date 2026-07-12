#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaEnvironmentState.generated.h"

class ULesFightArenaWorldManager;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaEnvironmentState : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void InitializeState(FArenaInfo Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void SetWeather(const FWeatherState& Weather);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void SetLighting(const FArenaLightingState& Lighting);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    FArenaEnvironmentState GetCurrentState() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void UpdateState(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    FArenaEnvironmentState SerializeState() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void DeserializeState(const FArenaEnvironmentState& State);

    UFUNCTION(BlueprintCallable, Category = "Arena|Environment")
    void ResetToDefaults();

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Environment")
    FArenaEnvironmentState CurrentState;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Environment")
    TArray<FDestructibleObjectState> ObjectStateCache;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;

    FWeatherState DefaultWeather;
    FArenaLightingState DefaultLighting;

    void LoadDefaultsFromArenaInfo(const FArenaInfo& Arena);
};
