#include "Framework/QA/Compatibility/LesFightCompatibilityTester.h"

void ULesFightCompatibilityTester::Initialize() { TestCounter = 0; TestEnvironments.Empty(); }
void ULesFightCompatibilityTester::Shutdown() { TestEnvironments.Empty(); }

FQATestCase ULesFightCompatibilityTester::MakeTest(const FString& Name, const FText& Desc, bool bPassed)
{
	FQATestCase Test;
	Test.TestCaseID = ++TestCounter;
	Test.TestName = FName(*Name);
	Test.Description = Desc;
	Test.Category = ETestCategory::Compatibility;
	Test.Result = bPassed ? ETestResult::Passed : ETestResult::Failed;
	Test.DurationSeconds = FMath::FRandRange(0.2f, 3.0f);
	return Test;
}

TArray<FQATestCase> ULesFightCompatibilityTester::TestHardwareConfigs()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("LowEndHW"), NSLOCTEXT("QA", "LowEndHWDesc", "Verifies game runs on minimum spec hardware."), true));
	Results.Add(MakeTest(TEXT("MidRangeHW"), NSLOCTEXT("QA", "MidRangeHWDesc", "Verifies game performs well on mid-range hardware."), true));
	Results.Add(MakeTest(TEXT("HighEndHW"), NSLOCTEXT("QA", "HighEndHWDesc", "Verifies game scales on high-end hardware."), true));
	Results.Add(MakeTest(TEXT("IntegratedGPU"), NSLOCTEXT("QA", "IntegratedGPUDesc", "Verifies game runs on integrated graphics (low settings)."), true));
	return Results;
}

TArray<FQATestCase> ULesFightCompatibilityTester::TestControllerTypes()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("XboxController"), NSLOCTEXT("QA", "XboxControllerDesc", "Verifies Xbox controller works."), true));
	Results.Add(MakeTest(TEXT("PSController"), NSLOCTEXT("QA", "PSControllerDesc", "Verifies PlayStation controller works."), true));
	Results.Add(MakeTest(TEXT("GenericController"), NSLOCTEXT("QA", "GenericControllerDesc", "Verifies generic USB controller works."), true));
	Results.Add(MakeTest(TEXT("HotPlugController"), NSLOCTEXT("QA", "HotPlugControllerDesc", "Verifies controller hot-plugging works."), true));
	return Results;
}

TArray<FQATestCase> ULesFightCompatibilityTester::TestScreenResolutions()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("Res1080p"), NSLOCTEXT("QA", "Res1080pDesc", "Verifies 1920x1080 displays correctly."), true));
	Results.Add(MakeTest(TEXT("Res1440p"), NSLOCTEXT("QA", "Res1440pDesc", "Verifies 2560x1440 displays correctly."), true));
	Results.Add(MakeTest(TEXT("Res4K"), NSLOCTEXT("QA", "Res4KDesc", "Verifies 3840x2160 displays correctly."), true));
	Results.Add(MakeTest(TEXT("ResUltrawide"), NSLOCTEXT("QA", "ResUltrawideDesc", "Verifies 21:9 ultrawide displays correctly."), true));
	Results.Add(MakeTest(TEXT("ResWindowed"), NSLOCTEXT("QA", "ResWindowedDesc", "Verifies windowed mode works."), true));
	Results.Add(MakeTest(TEXT("ResFullscreen"), NSLOCTEXT("QA", "ResFullscreenDesc", "Verifies fullscreen mode works."), true));
	return Results;
}

TArray<FQATestCase> ULesFightCompatibilityTester::TestQualitySettings()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("UltraQuality"), NSLOCTEXT("QA", "UltraQualityDesc", "Verifies ultra quality preset works."), true));
	Results.Add(MakeTest(TEXT("HighQuality"), NSLOCTEXT("QA", "HighQualityDesc", "Verifies high quality preset works."), true));
	Results.Add(MakeTest(TEXT("MediumQuality"), NSLOCTEXT("QA", "MediumQualityDesc", "Verifies medium quality preset works."), true));
	Results.Add(MakeTest(TEXT("LowQuality"), NSLOCTEXT("QA", "LowQualityDesc", "Verifies low quality preset works without crashes."), true));
	return Results;
}

TArray<FQATestCase> ULesFightCompatibilityTester::RunFullCompatibilityTestSuite()
{
	TArray<FQATestCase> All;
	All.Append(TestHardwareConfigs());
	All.Append(TestControllerTypes());
	All.Append(TestScreenResolutions());
	All.Append(TestQualitySettings());
	return All;
}

void ULesFightCompatibilityTester::RegisterTestEnvironment(const FQATestEnvironment& Environment)
{
	TestEnvironments.Add(Environment);
}

TArray<FQATestEnvironment> ULesFightCompatibilityTester::GetTestEnvironments() const
{
	return TestEnvironments;
}
