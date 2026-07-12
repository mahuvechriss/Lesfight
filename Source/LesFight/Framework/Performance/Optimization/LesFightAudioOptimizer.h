#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Performance/Core/LesFightPerformanceDataTypes.h"
#include "LesFightAudioOptimizer.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAudioOptimizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void SetQualityLevel(EPerformanceQualityLevel Level);

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void SetMaxConcurrentSounds(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	int32 GetMaxConcurrentSounds() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void SetVoiceChannelCount(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	int32 GetVoiceChannelCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void EnableSpatialAudio(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void EnableStreamingForLargeSounds(bool bEnable);

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void SetAudioPoolSize(float SizeMB);

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	float GetAudioPoolSize() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void SetMusicChannelCount(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	void OptimizeAudioMixer();

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	float GetAudioMemoryMB() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	int32 GetActiveSoundCount() const;

	UFUNCTION(BlueprintCallable, Category = "Performance|Audio")
	TArray<FString> GetOptimizationStatus() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Audio")
	int32 MaxConcurrentSounds = 32;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Audio")
	int32 VoiceChannels = 2;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Audio")
	int32 MusicChannels = 2;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Audio")
	float AudioPoolSizeMB = 256.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Audio")
	bool bSpatialAudio = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Audio")
	bool bStreamingEnabled = true;

	UPROPERTY(VisibleInstanceOnly, Category = "Performance|Audio")
	EPerformanceQualityLevel CurrentLevel = EPerformanceQualityLevel::High;
};
