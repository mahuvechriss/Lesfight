#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightGraphicsQualityManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualitySettingsApplied);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightGraphicsQualityManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	EPerformanceQualityLevel GetQualityLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void ApplyGraphicsSettings(const FQualitySettings& Settings);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	FQualitySettings GetCurrentSettings() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	FQualitySettings GetRecommendedSettings() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void SetTextureQuality(ETextureQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void SetShadowQuality(EShadowQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void SetVFXQuality(EVFXQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void SetResolutionScale(int32 Percent);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void SetViewDistance(int32 Percent);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void ToggleNanite(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void ToggleLumen(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void ToggleMotionBlur(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void ToggleBloom(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void ToggleSSR(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	void TogglePostProcessing(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Performance|Quality")
	FString GetScalabilityString() const;

	UPROPERTY(BlueprintAssignable, Category = "Performance|Quality")
	FOnQualitySettingsApplied OnQualitySettingsApplied;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Performance|Quality")
	FQualitySettings CurrentSettings;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Quality")
	FQualitySettings RecommendedSettings;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Quality")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;

	UPROPERTY(EditDefaultsOnly, Category = "Performance|Quality")
	TMap<EPerformanceQualityLevel, FQualitySettings> QualityPresets;

	void BuildDefaultPresets();
};
