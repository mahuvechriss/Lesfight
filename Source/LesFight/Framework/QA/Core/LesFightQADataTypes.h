#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightQADataTypes.generated.h"

UENUM(BlueprintType)
enum class EBugSeverity : uint8
{
	Critical	UMETA(DisplayName = "Critical"),
	Major		UMETA(DisplayName = "Major"),
	Minor		UMETA(DisplayName = "Minor"),
	Cosmetic	UMETA(DisplayName = "Cosmetic"),
	Suggestion	UMETA(DisplayName = "Suggestion")
};

UENUM(BlueprintType)
enum class EBugStatus : uint8
{
	New			UMETA(DisplayName = "New"),
	Confirmed	UMETA(DisplayName = "Confirmed"),
	InProgress	UMETA(DisplayName = "In Progress"),
	Fixed		UMETA(DisplayName = "Fixed"),
	Verified	UMETA(DisplayName = "Verified"),
	Closed		UMETA(DisplayName = "Closed"),
	WontFix		UMETA(DisplayName = "Won't Fix")
};

UENUM(BlueprintType)
enum class ETestResult : uint8
{
	Passed	UMETA(DisplayName = "Passed"),
	Failed	UMETA(DisplayName = "Failed"),
	Skipped	UMETA(DisplayName = "Skipped"),
	Blocked	UMETA(DisplayName = "Blocked"),
	NotRun	UMETA(DisplayName = "Not Run")
};

UENUM(BlueprintType)
enum class ETestCategory : uint8
{
	Functional		UMETA(DisplayName = "Functional"),
	Regression		UMETA(DisplayName = "Regression"),
	Performance		UMETA(DisplayName = "Performance"),
	Security		UMETA(DisplayName = "Security"),
	Compatibility	UMETA(DisplayName = "Compatibility"),
	UX				UMETA(DisplayName = "UX"),
	Automation		UMETA(DisplayName = "Automation"),
	BuildVerification UMETA(DisplayName = "Build Verification")
};

UENUM(BlueprintType)
enum class EReleaseChecklistItem : uint8
{
	Critical	UMETA(DisplayName = "Critical"),
	Required	UMETA(DisplayName = "Required"),
	Recommended	UMETA(DisplayName = "Recommended"),
	Optional	UMETA(DisplayName = "Optional")
};

USTRUCT(BlueprintType)
struct FQABugEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 BugID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString Area;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	EBugSeverity Severity = EBugSeverity::Minor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	EBugStatus Status = EBugStatus::New;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString ReportedBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FDateTime ReportDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString AssignedTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString Environment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	TArray<FString> StepsToReproduce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FText ExpectedResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FText ActualResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString FixVersion;
};

USTRUCT(BlueprintType)
struct FQATestCase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 TestCaseID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FName TestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	ETestCategory Category = ETestCategory::Functional;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	TArray<FString> Prerequisites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	TArray<FString> Steps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FText ExpectedOutcome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	ETestResult Result = ETestResult::NotRun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FText ActualOutcome;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float DurationSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 RelatedBugID = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString LastRunBy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FDateTime LastRunDate;
};

USTRUCT(BlueprintType)
struct FATestSuiteResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FName SuiteName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	TArray<FQATestCase> TestCases;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 PassCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 FailCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 SkipCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float TotalDuration = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FDateTime RunDate;
};

USTRUCT(BlueprintType)
struct FQAReleaseChecklistItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	EReleaseChecklistItem Priority = EReleaseChecklistItem::Required;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	bool bCompleted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FText Notes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString VerifiedBy;
};

USTRUCT(BlueprintType)
struct FQAPerformanceSample
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString TestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float AverageFPS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float MinFPS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float P1FPS = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float MemoryMB = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float CPUTimeMs = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float GPUTimeMs = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	float LoadTimeMs = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString Platform;
};

USTRUCT(BlueprintType)
struct FQATestEnvironment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString PlatformName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString GPUName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString CPUName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 RAM_GB = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString OSVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString GraphicsAPI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	FString Resolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "QA")
	int32 TargetFPS = 60;
};
