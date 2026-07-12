#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightLightingSystem.generated.h"

class ULesFightArenaWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLightingChanged, ELightingPreset, NewPreset);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightLightingSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    void ApplyLightingPreset(ELightingPreset Preset);

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    void TransitionLighting(ELightingPreset Target, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    void UpdateLighting(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    ELightingPreset GetCurrentPreset() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    FLinearColor GetAmbientColor() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    void SetLightIntensity(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    void SetShadowQuality(int32 Quality);

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    void EnableLumen(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    void EnableVirtualShadowMaps(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Arena|Lighting")
    FString GetLightingDescription() const;

    UPROPERTY(BlueprintAssignable, Category = "Arena|Lighting")
    FOnLightingChanged OnLightingChanged;

    void Initialize(ULesFightArenaWorldManager* InOwnerManager);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Arena|Lighting")
    ELightingPreset CurrentPreset;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Lighting")
    FArenaLightingState TargetState;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Lighting")
    FArenaLightingState CurrentState;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Lighting")
    float TransitionDuration;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Lighting")
    float TransitionProgress;

    UPROPERTY(BlueprintReadOnly, Category = "Arena|Lighting")
    bool bTransitioning;

private:
    TWeakObjectPtr<ULesFightArenaWorldManager> OwnerManager;

    UPROPERTY()
    TMap<ELightingPreset, FArenaLightingState> Presets;

    void InitializePresets();
};
