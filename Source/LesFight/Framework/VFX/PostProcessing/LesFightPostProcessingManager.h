#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightPostProcessingManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPostProcessChanged, EPostProcessingPreset, NewPreset);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPostProcessingManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void ApplyPreset(EPostProcessingPreset Preset, float TransitionTime = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void SetMotionBlur(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void SetDepthOfField(float Strength);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void SetBloom(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void SetColorGrading(FLinearColor Grade);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void SetVignette(float Intensity);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void SetSaturation(float Saturation);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void SetContrast(float Contrast);

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    EPostProcessingPreset GetCurrentPreset() const;

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void ResetToDefault();

    UFUNCTION(BlueprintCallable, Category = "Post Processing")
    void UpdatePostProcess(float DeltaTime);

    void Initialize(ULesFightVFXWorldManager* InOwner);

    UPROPERTY(BlueprintAssignable, Category = "Post Processing")
    FOnPostProcessChanged OnPostProcessChanged;

protected:
    UPROPERTY()
    EPostProcessingPreset CurrentPreset;

    UPROPERTY()
    FPostProcessingState CurrentState;

    UPROPERTY()
    FPostProcessingState TargetState;

    UPROPERTY()
    float TransitionTime;

    UPROPERTY()
    float TransitionProgress;

    UPROPERTY()
    bool bTransitioning;

    UPROPERTY()
    TMap<EPostProcessingPreset, FPostProcessingState> PostProcessingPresets;

private:
    TWeakObjectPtr<class ULesFightVFXWorldManager> OwnerManager;
};
