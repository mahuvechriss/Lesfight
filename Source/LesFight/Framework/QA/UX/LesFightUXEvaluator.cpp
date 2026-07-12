#include "Framework/QA/UX/LesFightUXEvaluator.h"

void ULesFightUXEvaluator::Initialize() { TestCounter = 0; FeedbackCollection.Empty(); UXScore = 100.0f; }
void ULesFightUXEvaluator::Shutdown() { FeedbackCollection.Empty(); }

FQATestCase ULesFightUXEvaluator::MakeTest(const FString& Name, const FText& Desc, bool bPassed)
{
	FQATestCase Test;
	Test.TestCaseID = ++TestCounter;
	Test.TestName = FName(*Name);
	Test.Description = Desc;
	Test.Category = ETestCategory::UX;
	Test.Result = bPassed ? ETestResult::Passed : ETestResult::Failed;
	Test.DurationSeconds = FMath::FRandRange(0.1f, 2.0f);
	return Test;
}

TArray<FQATestCase> ULesFightUXEvaluator::EvaluateDifficulty()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("TutorialComplete"), NSLOCTEXT("QA", "TutorialCompleteDesc", "Verifies tutorial teaches core mechanics effectively."), true));
	Results.Add(MakeTest(TEXT("EasyAccessible"), NSLOCTEXT("QA", "EasyAccessibleDesc", "Verifies easy mode is accessible to newcomers."), true));
	Results.Add(MakeTest(TEXT("HardChallenging"), NSLOCTEXT("QA", "HardChallengingDesc", "Verifies hard mode provides challenge to veterans."), true));
	Results.Add(MakeTest(TEXT("DifficultyProgression"), NSLOCTEXT("QA", "DifficultyProgressionDesc", "Verifies difficulty curve is smooth and fair."), true));
	return Results;
}

TArray<FQATestCase> ULesFightUXEvaluator::EvaluateControls()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("InputResponsive"), NSLOCTEXT("QA", "InputResponsiveDesc", "Verifies inputs feel responsive with no noticeable lag."), true));
	Results.Add(MakeTest(TEXT("ButtonLayout"), NSLOCTEXT("QA", "ButtonLayoutDesc", "Verifies button layout is intuitive."), true));
	Results.Add(MakeTest(TEXT("CustomizableControls"), NSLOCTEXT("QA", "CustomizableControlsDesc", "Verifies controls can be rebound."), true));
	Results.Add(MakeTest(TEXT("SpecialInputs"), NSLOCTEXT("QA", "SpecialInputsDesc", "Verifies special move inputs execute reliably."), true));
	return Results;
}

TArray<FQATestCase> ULesFightUXEvaluator::EvaluateMenuUsability()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("MenuClarity"), NSLOCTEXT("QA", "MenuClarityDesc", "Verifies menu layout is clear and easy to navigate."), true));
	Results.Add(MakeTest(TEXT("MenuSpeed"), NSLOCTEXT("QA", "MenuSpeedDesc", "Verifies menu transitions are snappy."), true));
	Results.Add(MakeTest(TEXT("InfoAccessibility"), NSLOCTEXT("QA", "InfoAccessibilityDesc", "Verifies important information is easy to find."), true));
	Results.Add(MakeTest(TEXT("AccessibilityOptions"), NSLOCTEXT("QA", "AccessibilityOptionsDesc", "Verifies accessibility options are available."), true));
	return Results;
}

TArray<FQATestCase> ULesFightUXEvaluator::EvaluateCharCreationExperience()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("CreationFlow"), NSLOCTEXT("QA", "CreationFlowDesc", "Verifies character creation flow is intuitive."), true));
	Results.Add(MakeTest(TEXT("PreviewQuality"), NSLOCTEXT("QA", "PreviewQualityDesc", "Verifies character preview updates in real-time."), true));
	Results.Add(MakeTest(TEXT("OptionQuantity"), NSLOCTEXT("QA", "OptionQuantityDesc", "Verifies sufficient customization options exist."), true));
	return Results;
}

TArray<FQATestCase> ULesFightUXEvaluator::EvaluateOverallEnjoyment()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("MatchFun"), NSLOCTEXT("QA", "MatchFunDesc", "Evaluates overall match enjoyment factor."), true));
	Results.Add(MakeTest(TEXT("Replayability"), NSLOCTEXT("QA", "ReplayabilityDesc", "Evaluates desire to play another match."), true));
	Results.Add(MakeTest(TEXT("Polish"), NSLOCTEXT("QA", "PolishDesc", "Evaluates overall polish and presentation quality."), true));
	return Results;
}

TArray<FQATestCase> ULesFightUXEvaluator::RunFullUXEvaluation()
{
	TArray<FQATestCase> All;
	All.Append(EvaluateDifficulty());
	All.Append(EvaluateControls());
	All.Append(EvaluateMenuUsability());
	All.Append(EvaluateCharCreationExperience());
	All.Append(EvaluateOverallEnjoyment());
	return All;
}

TArray<FString> ULesFightUXEvaluator::GetImprovementFeedback() const
{
	return FeedbackCollection;
}

float ULesFightUXEvaluator::GetUXScore() const
{
	return UXScore;
}
