#include "Framework/Performance/Optimization/LesFightAudioOptimizer.h"

void ULesFightAudioOptimizer::Initialize()
{
	MaxConcurrentSounds = 32;
	VoiceChannels = 2;
	MusicChannels = 2;
	AudioPoolSizeMB = 256.0f;
	bSpatialAudio = true;
	bStreamingEnabled = true;
	CurrentLevel = EPerformanceQualityLevel::High;
}

void ULesFightAudioOptimizer::Shutdown()
{
}

void ULesFightAudioOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	CurrentLevel = Level;

	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		MaxConcurrentSounds = 64;
		VoiceChannels = 4;
		MusicChannels = 4;
		AudioPoolSizeMB = 512.0f;
		bSpatialAudio = true;
		bStreamingEnabled = true;
		break;

	case EPerformanceQualityLevel::High:
		MaxConcurrentSounds = 32;
		VoiceChannels = 2;
		MusicChannels = 2;
		AudioPoolSizeMB = 256.0f;
		bSpatialAudio = true;
		bStreamingEnabled = true;
		break;

	case EPerformanceQualityLevel::Medium:
		MaxConcurrentSounds = 16;
		VoiceChannels = 1;
		MusicChannels = 2;
		AudioPoolSizeMB = 128.0f;
		bSpatialAudio = false;
		bStreamingEnabled = true;
		break;

	case EPerformanceQualityLevel::Low:
		MaxConcurrentSounds = 8;
		VoiceChannels = 1;
		MusicChannels = 1;
		AudioPoolSizeMB = 64.0f;
		bSpatialAudio = false;
		bStreamingEnabled = false;
		break;

	default:
		break;
	}
}

void ULesFightAudioOptimizer::SetMaxConcurrentSounds(int32 Count)
{
	MaxConcurrentSounds = FMath::Clamp(Count, 4, 128);
}

int32 ULesFightAudioOptimizer::GetMaxConcurrentSounds() const
{
	return MaxConcurrentSounds;
}

void ULesFightAudioOptimizer::SetVoiceChannelCount(int32 Count)
{
	VoiceChannels = FMath::Clamp(Count, 1, 8);
}

int32 ULesFightAudioOptimizer::GetVoiceChannelCount() const
{
	return VoiceChannels;
}

void ULesFightAudioOptimizer::EnableSpatialAudio(bool bEnable)
{
	bSpatialAudio = bEnable;

	if (bSpatialAudio)
	{
		UE_LOG(LogTemp, Log, TEXT("Spatial audio enabled"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Spatial audio disabled"));
	}
}

void ULesFightAudioOptimizer::EnableStreamingForLargeSounds(bool bEnable)
{
	bStreamingEnabled = bEnable;

	if (bStreamingEnabled)
	{
		UE_LOG(LogTemp, Log, TEXT("Audio streaming enabled for large sounds"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Audio streaming disabled"));
	}
}

void ULesFightAudioOptimizer::SetAudioPoolSize(float SizeMB)
{
	AudioPoolSizeMB = FMath::Clamp(SizeMB, 16.0f, 2048.0f);
}

float ULesFightAudioOptimizer::GetAudioPoolSize() const
{
	return AudioPoolSizeMB;
}

void ULesFightAudioOptimizer::SetMusicChannelCount(int32 Count)
{
	MusicChannels = FMath::Clamp(Count, 1, 8);
}

void ULesFightAudioOptimizer::OptimizeAudioMixer()
{
	UE_LOG(LogTemp, Log, TEXT("ULesFightAudioOptimizer: Optimizing audio mixer..."));
	UE_LOG(LogTemp, Log, TEXT("  Max Concurrent Sounds: %d"), MaxConcurrentSounds);
	UE_LOG(LogTemp, Log, TEXT("  Voice Channels: %d"), VoiceChannels);
	UE_LOG(LogTemp, Log, TEXT("  Music Channels: %d"), MusicChannels);
	UE_LOG(LogTemp, Log, TEXT("  Audio Pool: %.1f MB"), AudioPoolSizeMB);
	UE_LOG(LogTemp, Log, TEXT("  Spatial Audio: %s"), bSpatialAudio ? TEXT("Enabled") : TEXT("Disabled"));
	UE_LOG(LogTemp, Log, TEXT("  Streaming: %s"), bStreamingEnabled ? TEXT("Enabled") : TEXT("Disabled"));
}

float ULesFightAudioOptimizer::GetAudioMemoryMB() const
{
	return 0.0f;
}

int32 ULesFightAudioOptimizer::GetActiveSoundCount() const
{
	return 0;
}

TArray<FString> ULesFightAudioOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentLevel)));
	Status.Add(FString::Printf(TEXT("Max Concurrent Sounds: %d"), MaxConcurrentSounds));
	Status.Add(FString::Printf(TEXT("Voice Channels: %d"), VoiceChannels));
	Status.Add(FString::Printf(TEXT("Music Channels: %d"), MusicChannels));
	Status.Add(FString::Printf(TEXT("Audio Pool: %.1f MB"), AudioPoolSizeMB));
	Status.Add(FString::Printf(TEXT("Spatial Audio: %s"), bSpatialAudio ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Streaming: %s"), bStreamingEnabled ? TEXT("Enabled") : TEXT("Disabled")));
	return Status;
}
