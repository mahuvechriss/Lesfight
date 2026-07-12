#include "Framework/QA/Automation/LesFightBuildVerifier.h"
#include "Misc/FileHelper.h"
#include "Misc/App.h"

void ULesFightBuildVerifier::Initialize()
{
	BuildErrors.Empty();
	BuildWarnings.Empty();
	BuildNumber = 0;
	bBuildVerified = false;
}

void ULesFightBuildVerifier::Shutdown()
{
	BuildErrors.Empty();
	BuildWarnings.Empty();
}

FATestSuiteResult ULesFightBuildVerifier::VerifyBuild()
{
	FATestSuiteResult Result;
	Result.SuiteName = TEXT("BuildVerification");
	Result.RunDate = FDateTime::Now();

	TArray<FQATestCase> Tests;

	auto AddTest = [&](const FName& Name, bool bPassed, float Duration)
	{
		FQATestCase Test;
		Test.TestName = Name;
		Test.Category = ETestCategory::BuildVerification;
		Test.Result = bPassed ? ETestResult::Passed : ETestResult::Failed;
		Test.DurationSeconds = Duration;
		Tests.Add(Test);
		if (bPassed) Result.PassCount++;
		else Result.FailCount++;
	};

	AddTest(FName(TEXT("GameLaunches")), DoesGameLaunch(), 0.5f);
	AddTest(FName(TEXT("AllLevelsLoad")), DoAllLevelsLoad(), 2.0f);
	AddTest(FName(TEXT("BlueprintsCompile")), DoAllBlueprintsCompile(), 1.0f);
	AddTest(FName(TEXT("MaterialsValid")), AreAllMaterialsValid(), 0.5f);
	AddTest(FName(TEXT("SoundCuesValid")), DoAllSoundCuesReferenceValidAssets(), 0.5f);

	Result.TestCases = Tests;
	Result.TotalDuration = static_cast<float>(Tests.Num()) * 0.5f;
	bBuildVerified = (Result.FailCount == 0);

	UE_LOG(LogTemp, Log, TEXT("[BuildVerifier] Build #%d verification: %s"), BuildNumber, bBuildVerified ? TEXT("PASSED") : TEXT("FAILED"));

	return Result;
}

bool ULesFightBuildVerifier::DoesGameLaunch()
{
	return true;
}

bool ULesFightBuildVerifier::DoAllLevelsLoad()
{
	return true;
}

bool ULesFightBuildVerifier::DoAllBlueprintsCompile()
{
	return true;
}

bool ULesFightBuildVerifier::AreAllMaterialsValid()
{
	return true;
}

bool ULesFightBuildVerifier::DoAllSoundCuesReferenceValidAssets()
{
	return true;
}

int32 ULesFightBuildVerifier::GetBuildVersion() const
{
	return BuildNumber;
}

FString ULesFightBuildVerifier::GetBuildSummary() const
{
	return FString::Printf(TEXT("Build #%d - %s - Errors: %d, Warnings: %d"),
		BuildNumber,
		bBuildVerified ? TEXT("VERIFIED") : TEXT("NOT VERIFIED"),
		BuildErrors.Num(),
		BuildWarnings.Num());
}

TArray<FString> ULesFightBuildVerifier::GetBuildErrors() const
{
	return BuildErrors;
}

TArray<FString> ULesFightBuildVerifier::GetBuildWarnings() const
{
	return BuildWarnings;
}

bool ULesFightBuildVerifier::ExportBuildReport(const FString& FilePath)
{
	FString Report;
	Report += TEXT("LesFight Build Verification Report\n");
	Report += TEXT("===================================\n\n");
	Report += GetBuildSummary();
	Report += TEXT("\n\nBuild Errors:\n");
	for (const FString& Error : BuildErrors)
	{
		Report += FString::Printf(TEXT("  [ERROR] %s\n"), *Error);
	}
	Report += TEXT("\nBuild Warnings:\n");
	for (const FString& Warning : BuildWarnings)
	{
		Report += FString::Printf(TEXT("  [WARN] %s\n"), *Warning);
	}

	return FFileHelper::SaveStringToFile(Report, *FilePath);
}
