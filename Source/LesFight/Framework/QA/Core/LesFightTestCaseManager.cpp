#include "Framework/QA/Core/LesFightTestCaseManager.h"

void ULesFightTestCaseManager::Initialize()
{
	TestCaseDatabase.Empty();
	SuiteResults.Empty();
	NextTestCaseID = 1;
}

void ULesFightTestCaseManager::Shutdown()
{
	TestCaseDatabase.Empty();
	SuiteResults.Empty();
}

int32 ULesFightTestCaseManager::AddTestCase(const FString& Name, const FText& Description, ETestCategory Category, const TArray<FString>& Steps, const FText& ExpectedOutcome)
{
	FQATestCase TestCase;
	TestCase.TestCaseID = NextTestCaseID++;
	TestCase.TestName = FName(*Name);
	TestCase.Description = Description;
	TestCase.Category = Category;
	TestCase.Steps = Steps;
	TestCase.ExpectedOutcome = ExpectedOutcome;
	TestCase.Result = ETestResult::NotRun;

	TestCaseDatabase.Add(TestCase);
	return TestCase.TestCaseID;
}

FQATestCase ULesFightTestCaseManager::GetTestCase(int32 ID) const
{
	for (const FQATestCase& TestCase : TestCaseDatabase)
	{
		if (TestCase.TestCaseID == ID)
		{
			return TestCase;
		}
	}
	return FQATestCase();
}

TArray<FQATestCase> ULesFightTestCaseManager::GetAllTestCases() const
{
	return TestCaseDatabase;
}

TArray<FQATestCase> ULesFightTestCaseManager::GetTestCasesByCategory(ETestCategory Category) const
{
	TArray<FQATestCase> Filtered;
	for (const FQATestCase& TestCase : TestCaseDatabase)
	{
		if (TestCase.Category == Category)
		{
			Filtered.Add(TestCase);
		}
	}
	return Filtered;
}

TArray<FQATestCase> ULesFightTestCaseManager::GetTestCasesByResult(ETestResult Result) const
{
	TArray<FQATestCase> Filtered;
	for (const FQATestCase& TestCase : TestCaseDatabase)
	{
		if (TestCase.Result == Result)
		{
			Filtered.Add(TestCase);
		}
	}
	return Filtered;
}

bool ULesFightTestCaseManager::UpdateTestResult(int32 TestCaseID, ETestResult Result, const FText& ActualOutcome)
{
	for (FQATestCase& TestCase : TestCaseDatabase)
	{
		if (TestCase.TestCaseID == TestCaseID)
		{
			TestCase.Result = Result;
			TestCase.ActualOutcome = ActualOutcome;
			TestCase.LastRunDate = FDateTime::Now();
			TestCase.LastRunBy = TEXT("QA Tester");
			return true;
		}
	}
	return false;
}

int32 ULesFightTestCaseManager::GetTotalCount() const
{
	return TestCaseDatabase.Num();
}

int32 ULesFightTestCaseManager::GetPassCount() const
{
	int32 Count = 0;
	for (const FQATestCase& TestCase : TestCaseDatabase)
	{
		if (TestCase.Result == ETestResult::Passed)
		{
			Count++;
		}
	}
	return Count;
}

int32 ULesFightTestCaseManager::GetFailCount() const
{
	int32 Count = 0;
	for (const FQATestCase& TestCase : TestCaseDatabase)
	{
		if (TestCase.Result == ETestResult::Failed)
		{
			Count++;
		}
	}
	return Count;
}

float ULesFightTestCaseManager::GetPassRate() const
{
	int32 Total = GetTotalCount();
	if (Total == 0) return 0.0f;
	return (static_cast<float>(GetPassCount()) / static_cast<float>(Total)) * 100.0f;
}

void ULesFightTestCaseManager::ClearAllResults()
{
	for (FQATestCase& TestCase : TestCaseDatabase)
	{
		TestCase.Result = ETestResult::NotRun;
	}
}

TArray<FATestSuiteResult> ULesFightTestCaseManager::GetSuiteResults() const
{
	return SuiteResults;
}
