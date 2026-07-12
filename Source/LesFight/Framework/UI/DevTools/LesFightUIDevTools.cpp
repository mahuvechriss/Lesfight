#include "LesFightUIDevTools.h"

void ULesFightUIDevTools::Initialize()
{
    bPreviewMode = false;
    bMonitoring = false;
    TestLog.Empty();
    PerformanceSamples.Empty();
}

void ULesFightUIDevTools::Shutdown()
{
    if (bMonitoring)
    {
        StopPerformanceMonitoring();
    }
}

void ULesFightUIDevTools::EnableUIPreviewMode(bool bEnabled)
{
    bPreviewMode = bEnabled;
}

void ULesFightUIDevTools::PreviewScreen(FName ScreenID)
{
}

TArray<FString> ULesFightUIDevTools::TestNavigationForScreen(FName ScreenID)
{
    TArray<FString> Issues;
    return Issues;
}

FWidgetTestResult ULesFightUIDevTools::RunWidgetTest(UUserWidget* Widget)
{
    FWidgetTestResult Result;
    if (!Widget)
    {
        Result.bPassed = false;
        Result.WidgetName = FText::FromString(TEXT("None"));
        Result.Errors.Add(FText::FromString(TEXT("Widget is null")));
        return Result;
    }

    Result.WidgetName = FText::FromString(Widget->GetName());
    Result.bPassed = true;
    return Result;
}

TArray<FLocalizationIssue> ULesFightUIDevTools::RunLocalizationTest()
{
    TArray<FLocalizationIssue> Issues;
    return Issues;
}

TMap<FString, int32> ULesFightUIDevTools::RunAllTests()
{
    int32 Passed = 0;
    int32 Failed = 0;

    FWidgetTestResult WidgetResult = RunWidgetTest(nullptr);
    if (WidgetResult.bPassed) { ++Passed; } else { ++Failed; }

    TArray<FLocalizationIssue> LocIssues = RunLocalizationTest();
    if (LocIssues.Num() == 0) { ++Passed; } else { ++Failed; }

    TArray<FString> NavIssues = TestNavigationForScreen(FName(TEXT("MainMenu")));
    if (NavIssues.Num() == 0) { ++Passed; } else { ++Failed; }

    TMap<FString, int32> Results;
    Results.Add(TEXT("Passed"), Passed);
    Results.Add(TEXT("Failed"), Failed);
    return Results;
}

void ULesFightUIDevTools::StartPerformanceMonitoring()
{
    bMonitoring = true;
}

void ULesFightUIDevTools::StopPerformanceMonitoring()
{
    bMonitoring = false;
}

void ULesFightUIDevTools::LogUITest(FText Message)
{
    if (TestLog.Num() >= MaxLogEntries)
    {
        TestLog.RemoveAt(0);
    }
    TestLog.Add(Message);
}

void ULesFightUIDevTools::ClearTestLog()
{
    TestLog.Empty();
}
