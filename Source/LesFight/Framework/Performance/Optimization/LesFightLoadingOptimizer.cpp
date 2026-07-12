#include "Framework/Performance/Optimization/LesFightLoadingOptimizer.h"

void ULesFightLoadingOptimizer::Initialize()
{
}

void ULesFightLoadingOptimizer::Shutdown()
{
}

void ULesFightLoadingOptimizer::SetQualityLevel(EPerformanceQualityLevel Level)
{
	switch (Level)
	{
	case EPerformanceQualityLevel::Ultra:
		bAsyncLoading = true;
		bBackgroundStreaming = true;
		MaxConcurrentLoads = 8;
		TexturePoolMB = 2048.0f;
		break;

	case EPerformanceQualityLevel::High:
		bAsyncLoading = true;
		bBackgroundStreaming = true;
		MaxConcurrentLoads = 4;
		TexturePoolMB = 1024.0f;
		break;

	case EPerformanceQualityLevel::Medium:
		bAsyncLoading = true;
		bBackgroundStreaming = true;
		MaxConcurrentLoads = 2;
		TexturePoolMB = 512.0f;
		break;

	case EPerformanceQualityLevel::Low:
		bAsyncLoading = true;
		bBackgroundStreaming = false;
		MaxConcurrentLoads = 1;
		TexturePoolMB = 256.0f;
		break;

	default:
		break;
	}
}

void ULesFightLoadingOptimizer::EnableAsyncLoading(bool bEnable)
{
	bAsyncLoading = bEnable;
}

void ULesFightLoadingOptimizer::SetMaxConcurrentLoads(int32 Count)
{
	MaxConcurrentLoads = Count;
}

void ULesFightLoadingOptimizer::EnableBackgroundAssetStreaming(bool bEnable)
{
	bBackgroundStreaming = bEnable;
}

void ULesFightLoadingOptimizer::PreloadCommonAssets()
{
	PreloadedAssets.Empty();

	TArray<FName> FighterMeshes = {
		TEXT("SkeletalMesh/Fighter_01"),
		TEXT("SkeletalMesh/Fighter_02"),
		TEXT("SkeletalMesh/Fighter_03"),
		TEXT("SkeletalMesh/Fighter_04")
	};

	for (const FName& Mesh : FighterMeshes)
	{
		PreloadedAssets.Add(Mesh);
		OnAssetPreloaded.Broadcast(Mesh);
	}

	TArray<FName> MainMenuTextures = {
		TEXT("Texture/MainMenu_BG"),
		TEXT("Texture/MainMenu_Logo"),
		TEXT("Texture/MainMenu_Title")
	};

	for (const FName& Tex : MainMenuTextures)
	{
		PreloadedAssets.Add(Tex);
		OnAssetPreloaded.Broadcast(Tex);
	}

	TArray<FName> CommonSounds = {
		TEXT("Sound/Menu_Select"),
		TEXT("Sound/Menu_Confirm"),
		TEXT("Sound/Menu_Back"),
		TEXT("Sound/Countdown"),
		TEXT("Sound/Round_Start"),
		TEXT("Sound/Round_End"),
		TEXT("Sound/KO_Horn")
	};

	for (const FName& Sound : CommonSounds)
	{
		PreloadedAssets.Add(Sound);
		OnAssetPreloaded.Broadcast(Sound);
	}

	TArray<FName> UITextures = {
		TEXT("Texture/UI_HealthBar"),
		TEXT("Texture/UI_EnergyBar"),
		TEXT("Texture/UI_ComboCounter"),
		TEXT("Texture/UI_Timer"),
		TEXT("Texture/UI_Buttons"),
		TEXT("Texture/UI_Icons")
	};

	for (const FName& UITex : UITextures)
	{
		PreloadedAssets.Add(UITex);
		OnAssetPreloaded.Broadcast(UITex);
	}

	TArray<FName> Arenas = {
		TEXT("Level/Arena_Dojo"),
		TEXT("Level/Arena_Stadium"),
		TEXT("Level/Arena_Rooftop"),
		TEXT("Level/Arena_Underground")
	};

	for (const FName& Arena : Arenas)
	{
		PreloadedAssets.Add(Arena);
		OnAssetPreloaded.Broadcast(Arena);
	}
}

void ULesFightLoadingOptimizer::SetTextureStreamingPool(float SizeMB)
{
	TexturePoolMB = SizeMB;
}

void ULesFightLoadingOptimizer::OptimizeLevelLoadOrder()
{
}

float ULesFightLoadingOptimizer::GetAverageLoadTimeMs() const
{
	if (LoadTimes.Num() == 0)
	{
		return 0.0f;
	}

	float Total = 0.0f;
	for (const TPair<FName, float>& Entry : LoadTimes)
	{
		Total += Entry.Value;
	}
	return Total / static_cast<float>(LoadTimes.Num());
}

float ULesFightLoadingOptimizer::GetTotalLoadTimeMs() const
{
	float Total = 0.0f;
	for (const TPair<FName, float>& Entry : LoadTimes)
	{
		Total += Entry.Value;
	}
	return Total;
}

int32 ULesFightLoadingOptimizer::GetLoadedAssetCount() const
{
	return LoadTimes.Num();
}

TArray<FString> ULesFightLoadingOptimizer::GetOptimizationStatus() const
{
	TArray<FString> Status;
	Status.Add(FString::Printf(TEXT("Async Loading: %s"), bAsyncLoading ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Background Streaming: %s"), bBackgroundStreaming ? TEXT("Enabled") : TEXT("Disabled")));
	Status.Add(FString::Printf(TEXT("Max Concurrent Loads: %d"), MaxConcurrentLoads));
	Status.Add(FString::Printf(TEXT("Texture Pool MB: %.1f"), TexturePoolMB));
	Status.Add(FString::Printf(TEXT("Preloaded Assets: %d"), PreloadedAssets.Num()));
	Status.Add(FString::Printf(TEXT("Loaded Assets: %d"), LoadTimes.Num()));
	return Status;
}
