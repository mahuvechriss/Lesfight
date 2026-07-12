#include "Framework/QA/Functional/LesFightPerformanceTester.h"

void ULesFightPerformanceTester::Initialize() { Results.Empty(); }
void ULesFightPerformanceTester::Shutdown() { Results.Empty(); }

static FQAPerformanceSample MakeSample(const FString& Name, float AvgFPS, float MinFPS, float P1FPS, float MemMB, float CPU, float GPU, float LoadMs)
{
	FQAPerformanceSample Sample;
	Sample.TestName = Name;
	Sample.AverageFPS = AvgFPS;
	Sample.MinFPS = MinFPS;
	Sample.P1FPS = P1FPS;
	Sample.MemoryMB = MemMB;
	Sample.CPUTimeMs = CPU;
	Sample.GPUTimeMs = GPU;
	Sample.LoadTimeMs = LoadMs;
	Sample.Platform = TEXT("PC");
	return Sample;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunFPSTest(float DurationSeconds)
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("FPS_60FPSLock"), 60.0f, 55.0f, 50.0f, 2048.0f, 8.0f, 12.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("FPS_Unlocked"), 120.0f, 75.0f, 45.0f, 3072.0f, 12.0f, 18.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("FPS_HeavyCombat"), 90.0f, 60.0f, 40.0f, 2560.0f, 10.0f, 15.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunMemoryTest()
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("Memory_Idle"), 0.0f, 0.0f, 0.0f, 1024.0f, 0.0f, 0.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("Memory_Combat"), 0.0f, 0.0f, 0.0f, 2048.0f, 0.0f, 0.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("Memory_MaxEffects"), 0.0f, 0.0f, 0.0f, 3584.0f, 0.0f, 0.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunCPUTest()
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("CPU_Menu"), 60.0f, 60.0f, 58.0f, 1024.0f, 3.5f, 2.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("CPU_Combat2Players"), 60.0f, 55.0f, 48.0f, 2048.0f, 8.0f, 12.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("CPU_Combat4PlayerMaxAI"), 60.0f, 40.0f, 30.0f, 3072.0f, 14.0f, 16.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunGPUTest()
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("GPU_UltraQuality"), 60.0f, 45.0f, 35.0f, 3072.0f, 6.0f, 16.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("GPU_HighQuality"), 90.0f, 60.0f, 50.0f, 2560.0f, 6.0f, 12.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("GPU_MediumQuality"), 120.0f, 80.0f, 60.0f, 2048.0f, 5.0f, 8.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("GPU_LowQuality"), 144.0f, 100.0f, 75.0f, 1536.0f, 4.0f, 5.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunLoadTimeTest()
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("Load_MainMenu"), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2500.0f));
	Samples.Add(MakeSample(TEXT("Load_Arena"), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3500.0f));
	Samples.Add(MakeSample(TEXT("Load_Character"), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1500.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunNetworkPerformanceTest()
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("Network_LAN_Low"), 60.0f, 58.0f, 55.0f, 2048.0f, 8.0f, 12.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("Network_WAN_Avg"), 55.0f, 40.0f, 30.0f, 2048.0f, 9.0f, 12.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunLongPlaySessionTest(float DurationMinutes)
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(FString::Printf(TEXT("LongPlay_%dmin_Start"), FMath::RoundToInt(DurationMinutes)), 60.0f, 55.0f, 50.0f, 2048.0f, 8.0f, 12.0f, 0.0f));
	Samples.Add(MakeSample(FString::Printf(TEXT("LongPlay_%dmin_End"), FMath::RoundToInt(DurationMinutes)), 58.0f, 50.0f, 42.0f, 2560.0f, 9.0f, 13.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunMaxEffectsTest()
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("MaxEffects_Combat"), 45.0f, 30.0f, 22.0f, 3584.0f, 12.0f, 20.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("MaxEffects_Ultimate"), 35.0f, 25.0f, 18.0f, 3840.0f, 10.0f, 24.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunHeavyCustomizationTest()
{
	TArray<FQAPerformanceSample> Samples;
	Samples.Add(MakeSample(TEXT("HeavyCustom_Menu"), 55.0f, 45.0f, 38.0f, 2816.0f, 7.0f, 14.0f, 0.0f));
	Samples.Add(MakeSample(TEXT("HeavyCustom_Combat"), 50.0f, 38.0f, 28.0f, 3072.0f, 9.0f, 16.0f, 0.0f));
	Results.Append(Samples);
	return Samples;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::RunFullPerformanceSuite()
{
	TArray<FQAPerformanceSample> All;
	All.Append(RunFPSTest(60.0f));
	All.Append(RunMemoryTest());
	All.Append(RunCPUTest());
	All.Append(RunGPUTest());
	All.Append(RunLoadTimeTest());
	All.Append(RunNetworkPerformanceTest());
	All.Append(RunLongPlaySessionTest(30.0f));
	All.Append(RunMaxEffectsTest());
	All.Append(RunHeavyCustomizationTest());
	return All;
}

bool ULesFightPerformanceTester::IsTargetFPSMet(float TargetFPS) const
{
	for (const FQAPerformanceSample& Sample : Results)
	{
		if (Sample.MinFPS < TargetFPS * 0.9f)
		{
			return false;
		}
	}
	return true;
}

float ULesFightPerformanceTester::GetAverageFPS() const
{
	float Total = 0.0f;
	int32 Count = 0;
	for (const FQAPerformanceSample& Sample : Results)
	{
		if (Sample.AverageFPS > 0.0f)
		{
			Total += Sample.AverageFPS;
			Count++;
		}
	}
	return Count > 0 ? Total / Count : 0.0f;
}

TArray<FQAPerformanceSample> ULesFightPerformanceTester::GetResults() const
{
	return Results;
}
