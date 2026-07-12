#include "Framework/Performance/Core/LesFightPerformanceManager.h"
#include "Framework/Performance/Core/LesFightFPSMonitor.h"
#include "Framework/Performance/Core/LesFightMemoryTracker.h"
#include "Framework/Performance/Core/LesFightPerformanceMonitor.h"

void ULesFightPerformanceManager::Initialize()
{
	if (bInitialized)
	{
		return;
	}

	FPSMonitor = CreateSubsystem<ULesFightFPSMonitor>();
	MemoryTracker = CreateSubsystem<ULesFightMemoryTracker>();
	PerformanceMonitor = CreateSubsystem<ULesFightPerformanceMonitor>();

	FPSMonitor->Initialize();
	MemoryTracker->Initialize();
	PerformanceMonitor->Initialize();

	CurrentQuality = EPerformanceQualityLevel::High;

	bInitialized = true;
	UE_LOG(LogTemp, Log, TEXT("[PerformanceManager] Initialized with quality: %d"),
		static_cast<int32>(CurrentQuality));
}

void ULesFightPerformanceManager::Shutdown()
{
	if (!bInitialized)
	{
		return;
	}

	if (FPSMonitor)
	{
		FPSMonitor->Shutdown();
	}
	if (MemoryTracker)
	{
		MemoryTracker->Shutdown();
	}
	if (PerformanceMonitor)
	{
		PerformanceMonitor->Shutdown();
	}

	bInitialized = false;
	UE_LOG(LogTemp, Log, TEXT("[PerformanceManager] Shutdown"));
}

void ULesFightPerformanceManager::Tick(float DeltaTime)
{
	if (!bInitialized)
	{
		return;
	}

	if (FPSMonitor)
	{
		FPSMonitor->Tick(DeltaTime);
	}
	if (MemoryTracker)
	{
		MemoryTracker->Tick(DeltaTime);
	}
	if (PerformanceMonitor)
	{
		PerformanceMonitor->Tick(DeltaTime);
	}
}

ULesFightFPSMonitor* ULesFightPerformanceManager::GetFPSMonitor() const
{
	return FPSMonitor;
}

ULesFightMemoryTracker* ULesFightPerformanceManager::GetMemoryTracker() const
{
	return MemoryTracker;
}

ULesFightPerformanceMonitor* ULesFightPerformanceManager::GetPerformanceMonitor() const
{
	return PerformanceMonitor;
}

ULesFightGraphicsQualityManager* ULesFightPerformanceManager::GetGraphicsQualityManager() const
{
	return GraphicsQualityManager;
}

ULesFightTextureOptimizer* ULesFightPerformanceManager::GetTextureOptimizer() const
{
	return TextureOptimizer;
}

ULesFightScalabilitySettings* ULesFightPerformanceManager::GetScalabilitySettings() const
{
	return ScalabilitySettings;
}

ULesFightHardwareDetector* ULesFightPerformanceManager::GetHardwareDetector() const
{
	return HardwareDetector;
}

ULesFightCharacterOptimizer* ULesFightPerformanceManager::GetCharacterOptimizer() const
{
	return CharacterOptimizer;
}

ULesFightAnimationOptimizer* ULesFightPerformanceManager::GetAnimationOptimizer() const
{
	return AnimationOptimizer;
}

ULesFightVFXOptimizer* ULesFightPerformanceManager::GetVFXOptimizer() const
{
	return VFXOptimizer;
}

ULesFightAudioOptimizer* ULesFightPerformanceManager::GetAudioOptimizer() const
{
	return AudioOptimizer;
}

ULesFightAIOptimizer* ULesFightPerformanceManager::GetAIOptimizer() const
{
	return AIOptimizer;
}

ULesFightPhysicsOptimizer* ULesFightPerformanceManager::GetPhysicsOptimizer() const
{
	return PhysicsOptimizer;
}

ULesFightLoadingOptimizer* ULesFightPerformanceManager::GetLoadingOptimizer() const
{
	return LoadingOptimizer;
}

ULesFightMultiplayerOptimizer* ULesFightPerformanceManager::GetMultiplayerOptimizer() const
{
	return MultiplayerOptimizer;
}

ULesFightPerformanceDevTools* ULesFightPerformanceManager::GetPerformanceDevTools() const
{
	return PerformanceDevTools;
}

void ULesFightPerformanceManager::SetQualityLevel(EPerformanceQualityLevel Level)
{
	if (CurrentQuality == Level)
	{
		return;
	}

	CurrentQuality = Level;

	if (GraphicsQualityManager)
	{
		GraphicsQualityManager->Optimize();
	}
	if (TextureOptimizer)
	{
		TextureOptimizer->Optimize();
	}
	if (ScalabilitySettings)
	{
		ScalabilitySettings->Optimize();
	}
	if (CharacterOptimizer)
	{
		CharacterOptimizer->Optimize();
	}
	if (AnimationOptimizer)
	{
		AnimationOptimizer->Optimize();
	}
	if (VFXOptimizer)
	{
		VFXOptimizer->Optimize();
	}
	if (AudioOptimizer)
	{
		AudioOptimizer->Optimize();
	}
	if (AIOptimizer)
	{
		AIOptimizer->Optimize();
	}
	if (PhysicsOptimizer)
	{
		PhysicsOptimizer->Optimize();
	}
	if (LoadingOptimizer)
	{
		LoadingOptimizer->Optimize();
	}
	if (MultiplayerOptimizer)
	{
		MultiplayerOptimizer->Optimize();
	}

	OnQualityChanged.Broadcast(CurrentQuality);
	UE_LOG(LogTemp, Log, TEXT("[PerformanceManager] Quality changed to: %d"),
		static_cast<int32>(CurrentQuality));
}

EPerformanceQualityLevel ULesFightPerformanceManager::GetQualityLevel() const
{
	return CurrentQuality;
}

FOptimizationMetrics ULesFightPerformanceManager::GetOptimizationMetrics() const
{
	FOptimizationMetrics Metrics;

	if (FPSMonitor)
	{
		Metrics.AverageFPS = FPSMonitor->GetAverageFPS();
		Metrics.MinFPS = FPSMonitor->GetMinFPS();
		Metrics.MaxFPS = FPSMonitor->GetMaxFPS();
		Metrics.AverageFrameTime = FPSMonitor->GetFrameTime();
		Metrics.P1FrameTime = FPSMonitor->GetP1FrameTime();
	}

	if (MemoryTracker)
	{
		Metrics.MemoryPeakMB = MemoryTracker->GetPeakMemoryMB();
	}

	if (PerformanceMonitor)
	{
		Metrics.AverageLoadTimeMs = PerformanceMonitor->GetAverageLoadTime();
		Metrics.TotalDrawCalls = PerformanceMonitor->GetAverageDrawCalls();
		Metrics.NetworkBandwidthKbps = PerformanceMonitor->GetAverageLatency();
	}

	return Metrics;
}

void ULesFightPerformanceManager::ApplyOptimizations()
{
	if (GraphicsQualityManager)
	{
		GraphicsQualityManager->Optimize();
	}
	if (TextureOptimizer)
	{
		TextureOptimizer->Optimize();
	}
	if (ScalabilitySettings)
	{
		ScalabilitySettings->Optimize();
	}
	if (HardwareDetector)
	{
		HardwareDetector->Optimize();
	}
	if (CharacterOptimizer)
	{
		CharacterOptimizer->Optimize();
	}
	if (AnimationOptimizer)
	{
		AnimationOptimizer->Optimize();
	}
	if (VFXOptimizer)
	{
		VFXOptimizer->Optimize();
	}
	if (AudioOptimizer)
	{
		AudioOptimizer->Optimize();
	}
	if (AIOptimizer)
	{
		AIOptimizer->Optimize();
	}
	if (PhysicsOptimizer)
	{
		PhysicsOptimizer->Optimize();
	}
	if (LoadingOptimizer)
	{
		LoadingOptimizer->Optimize();
	}
	if (MultiplayerOptimizer)
	{
		MultiplayerOptimizer->Optimize();
	}

	bOptimized = true;
	UE_LOG(LogTemp, Log, TEXT("[PerformanceManager] All optimizations applied"));
}

TArray<FString> ULesFightPerformanceManager::RunFullDiagnostic()
{
	TArray<FString> Report;

	Report.Add(TEXT("=== Performance Diagnostic Report ==="));

	if (FPSMonitor)
	{
		Report.Add(FString::Printf(TEXT("FPS: Current=%.2f, Avg=%.2f, Min=%.2f, Max=%.2f, Target=%.2f"),
			FPSMonitor->GetCurrentFPS(), FPSMonitor->GetAverageFPS(),
			FPSMonitor->GetMinFPS(), FPSMonitor->GetMaxFPS(),
			FPSMonitor->GetFPSTarget()));
		Report.Add(FString::Printf(TEXT("FPS Quality: %s"), *FPSMonitor->GetFPSQualityRating().ToString()));
	}

	if (MemoryTracker)
	{
		Report.Add(FString::Printf(TEXT("Memory: Current=%.2f MB, Peak=%.2f MB, Budget=%.2f MB"),
			MemoryTracker->GetCurrentMemoryMB(), MemoryTracker->GetPeakMemoryMB(),
			MemoryTracker->GetMemoryBudget().TotalBudgetMB));
		Report.Add(FString::Printf(TEXT("Memory Usage: %.2f%%"),
			MemoryTracker->GetMemoryUsagePercentage()));

		TArray<FString> LargestAssets = MemoryTracker->GetLargestAssets(5);
		Report.Add(TEXT("Largest Assets:"));
		for (const FString& Asset : LargestAssets)
		{
			Report.Add(FString::Printf(TEXT("  - %s"), *Asset));
		}

		TArray<FString> Leaks = MemoryTracker->DetectMemoryLeaks();
		if (Leaks.Num() > 0)
		{
			Report.Add(TEXT("Potential Memory Leaks:"));
			for (const FString& Leak : Leaks)
			{
				Report.Add(FString::Printf(TEXT("  - %s"), *Leak));
			}
		}
	}

	if (PerformanceMonitor)
	{
		Report.Add(FString::Printf(TEXT("CPU Avg: %.2f%%, GPU Avg: %.2f%%"),
			PerformanceMonitor->GetAverageCPUUsage(),
			PerformanceMonitor->GetAverageGPUUsage()));
		Report.Add(FString::Printf(TEXT("Overall Score: %.2f / 100"), PerformanceMonitor->GetOverallScore()));
		Report.Add(FString::Printf(TEXT("Rating: %s"), *PerformanceMonitor->GetPerformanceRating().ToString()));
	}

	Report.Add(FString::Printf(TEXT("Quality Level: %d"), static_cast<int32>(CurrentQuality)));
	Report.Add(FString::Printf(TEXT("Optimized: %s"), bOptimized ? TEXT("Yes") : TEXT("No")));
	Report.Add(TEXT("=== End of Report ==="));

	return Report;
}

bool ULesFightPerformanceManager::IsOptimized() const
{
	return bOptimized;
}

template<typename T>
T* ULesFightPerformanceManager::CreateSubsystem()
{
	T* NewSubsystem = NewObject<T>(this);
	if (NewSubsystem)
	{
		UE_LOG(LogTemp, Verbose, TEXT("[PerformanceManager] Created subsystem: %s"), *NewSubsystem->GetName());
	}
	return NewSubsystem;
}
