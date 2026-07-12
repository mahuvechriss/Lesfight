#include "LesFightTextureOptimizer.h"
#include "Kismet/KismetSystemLibrary.h"

void ULesFightTextureOptimizer::Initialize()
{
	CurrentQuality = ETextureQualityLevel::High;
	CurrentMemoryMB = 0.0f;
	ResolutionScale = 100;
	bStreamingEnabled = true;
	TextureRegistry.Empty();
}

void ULesFightTextureOptimizer::Shutdown()
{
	TextureRegistry.Empty();
}

void ULesFightTextureOptimizer::SetTextureQuality(ETextureQualityLevel Level)
{
	CurrentQuality = Level;

	switch (Level)
	{
	case ETextureQualityLevel::Full:
		MemoryBudgetMB = 4096.0f;
		ResolutionScale = 100;
		break;
	case ETextureQualityLevel::High:
		MemoryBudgetMB = 2048.0f;
		ResolutionScale = 100;
		break;
	case ETextureQualityLevel::Medium:
		MemoryBudgetMB = 1024.0f;
		ResolutionScale = 75;
		break;
	case ETextureQualityLevel::Low:
		MemoryBudgetMB = 512.0f;
		ResolutionScale = 50;
		break;
	case ETextureQualityLevel::Mobile:
		MemoryBudgetMB = 256.0f;
		ResolutionScale = 25;
		break;
	}

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.StreamingPoolSize %d"), static_cast<int32>(MemoryBudgetMB)));

	ApplyTextureScale(ResolutionScale);
	OptimizeTexturePool();
}

ETextureQualityLevel ULesFightTextureOptimizer::GetTextureQuality() const
{
	return CurrentQuality;
}

void ULesFightTextureOptimizer::SetMemoryBudget(float BudgetMB)
{
	MemoryBudgetMB = FMath::Max(64.0f, BudgetMB);
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.StreamingPoolSize %d"), static_cast<int32>(MemoryBudgetMB)));
}

float ULesFightTextureOptimizer::GetMemoryBudget() const
{
	return MemoryBudgetMB;
}

void ULesFightTextureOptimizer::EnableTextureStreaming(bool bEnabled)
{
	bStreamingEnabled = bEnabled;
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		bEnabled ? TEXT("r.TextureStreaming 1") : TEXT("r.TextureStreaming 0"));
}

void ULesFightTextureOptimizer::OptimizeTexturePool()
{
	int32 MipBias = 0;
	switch (CurrentQuality)
	{
	case ETextureQualityLevel::Full:   MipBias = 0; break;
	case ETextureQualityLevel::High:   MipBias = 0; break;
	case ETextureQualityLevel::Medium: MipBias = 1; break;
	case ETextureQualityLevel::Low:    MipBias = 2; break;
	case ETextureQualityLevel::Mobile: MipBias = 3; break;
	}

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.Streaming.MipBias %d"), MipBias));

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("r.Streaming.FullyLoadUsedTextures 1"));
}

float ULesFightTextureOptimizer::GetCurrentTextureMemoryMB() const
{
	return CurrentMemoryMB;
}

float ULesFightTextureOptimizer::GetTexturePoolSizeMB() const
{
	return MemoryBudgetMB;
}

TArray<FString> ULesFightTextureOptimizer::GetStreamedTextures() const
{
	TArray<FString> Result;
	for (const auto& Entry : TextureRegistry)
	{
		if (Entry.Value.bStreamed)
		{
			Result.Add(Entry.Key.ToString());
		}
	}
	return Result;
}

void ULesFightTextureOptimizer::ReportTextureUsage(FName TextureName, int32 Width, int32 Height, float SizeMB)
{
	FTextureInfo Info;
	Info.Width = Width;
	Info.Height = Height;
	Info.SizeMB = SizeMB;
	Info.bStreamed = true;

	TextureRegistry.Add(TextureName, Info);
	CurrentMemoryMB += SizeMB;

	if (CurrentMemoryMB >= MemoryBudgetMB)
	{
		OnTextureBudgetExceeded.Broadcast(CurrentMemoryMB);
	}
}

void ULesFightTextureOptimizer::ApplyTextureScale(int32 Percent)
{
	ResolutionScale = FMath::Clamp(Percent, 10, 200);

	int32 MipBias;
	if (ResolutionScale >= 100)    MipBias = 0;
	else if (ResolutionScale >= 75) MipBias = 1;
	else if (ResolutionScale >= 50) MipBias = 2;
	else if (ResolutionScale >= 25) MipBias = 3;
	else                            MipBias = 4;

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
		FString::Printf(TEXT("r.Streaming.MipBias %d"), MipBias));
}
