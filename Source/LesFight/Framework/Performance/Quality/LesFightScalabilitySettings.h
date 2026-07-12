#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightScalabilitySettings.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightScalabilitySettings : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void LoadScalabilitySettings();

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void SaveScalabilitySettings();

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	TArray<FString> GetScalabilityPresets() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void ApplyScalabilityPreset(FName PresetName);

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	FName GetCurrentPreset() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void SetResolutionScale(int32 Percent);

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void SetGlobalQualityLevel(int32 Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	int32 GetGlobalQualityLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void CreateCustomPreset(const FQualitySettings& Settings, FName PresetName);

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void DeleteCustomPreset(FName PresetName);

	UFUNCTION(BlueprintCallable, Category = "Performance|Scalability")
	void ResetToDefaults();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Performance|Scalability")
	TMap<FName, FQualitySettings> ScalabilityPresets;

	UPROPERTY(VisibleAnywhere, Category = "Performance|Scalability")
	FName CurrentPreset = TEXT("High");

	UPROPERTY(VisibleAnywhere, Category = "Performance|Scalability")
	int32 GlobalQuality = 3;

	void BuildDefaultPresets();
};
