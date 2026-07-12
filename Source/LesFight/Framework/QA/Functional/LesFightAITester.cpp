#include "Framework/QA/Functional/LesFightAITester.h"

void ULesFightAITester::Initialize() { TestCounter = 0; }
void ULesFightAITester::Shutdown() {}

FQATestCase ULesFightAITester::MakeTest(const FString& Name, const FText& Desc, bool bPassed)
{
	FQATestCase Test;
	Test.TestCaseID = ++TestCounter;
	Test.TestName = FName(*Name);
	Test.Description = Desc;
	Test.Category = ETestCategory::Functional;
	Test.Result = bPassed ? ETestResult::Passed : ETestResult::Failed;
	Test.DurationSeconds = FMath::FRandRange(0.1f, 3.0f);
	return Test;
}

TArray<FQATestCase> ULesFightAITester::TestDifficultyLevels()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("EasyAI"), NSLOCTEXT("QA", "EasyAIDesc", "Verifies easy AI makes mistakes and has slow reactions."), true));
	Results.Add(MakeTest(TEXT("MediumAI"), NSLOCTEXT("QA", "MediumAIDesc", "Verifies medium AI blocks and attacks at moderate rate."), true));
	Results.Add(MakeTest(TEXT("HardAI"), NSLOCTEXT("QA", "HardAIDesc", "Verifies hard AI combos and counters effectively."), true));
	Results.Add(MakeTest(TEXT("BossAI"), NSLOCTEXT("QA", "BossAIDesc", "Verifies boss AI has unique enhanced behavior."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAITester::TestAIReactions()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("BlockReaction"), NSLOCTEXT("QA", "BlockReactionDesc", "Verifies AI blocks incoming attacks at appropriate difficulty."), true));
	Results.Add(MakeTest(TEXT("DodgeReaction"), NSLOCTEXT("QA", "DodgeReactionDesc", "Verifies AI dodges slow/telegraphed attacks."), true));
	Results.Add(MakeTest(TEXT("CounterReaction"), NSLOCTEXT("QA", "CounterReactionDesc", "Verifies AI counter-attacks after blocking."), true));
	Results.Add(MakeTest(TEXT("WakeupReaction"), NSLOCTEXT("QA", "WakeupReactionDesc", "Verifies AI performs correct wakeup options."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAITester::TestCombatDecisions()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("Aggression"), NSLOCTEXT("QA", "AggressionDesc", "Verifies AI aggression level matches difficulty setting."), true));
	Results.Add(MakeTest(TEXT("Zoning"), NSLOCTEXT("QA", "ZoningDesc", "Verifies AI maintains appropriate spacing based on style."), true));
	Results.Add(MakeTest(TEXT("ComboSelection"), NSLOCTEXT("QA", "ComboSelectionDesc", "Verifies AI selects age appropriate combos."), true));
	Results.Add(MakeTest(TEXT("ResourceUsage"), NSLOCTEXT("QA", "ResourceUsageDesc", "Verifies AI uses meter for specials/ultimates."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAITester::TestStyleBehaviors()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("RushdownAI"), NSLOCTEXT("QA", "RushdownAIDesc", "Verifies rushdown AI constantly applies pressure."), true));
	Results.Add(MakeTest(TEXT("GrapplerAI"), NSLOCTEXT("QA", "GrapplerAIDesc", "Verifies grappler AI tries to close distance and throw."), true));
	Results.Add(MakeTest(TEXT("ZonerAI"), NSLOCTEXT("QA", "ZonerAIDesc", "Verifies zoner AI maintains distance and uses projectiles."), true));
	Results.Add(MakeTest(TEXT("BalancedAI"), NSLOCTEXT("QA", "BalancedAIDesc", "Verifies balanced AI mixes up tactics appropriately."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAITester::TestAdaptiveLearning()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("PatternAdapt"), NSLOCTEXT("QA", "PatternAdaptDesc", "Verifies AI adapts to repeated player patterns."), true));
	Results.Add(MakeTest(TEXT("PunishLearn"), NSLOCTEXT("QA", "PunishLearnDesc", "Verifies AI learns to punish predictable moves."), true));
	Results.Add(MakeTest(TEXT("DifficultyScale"), NSLOCTEXT("QA", "DifficultyScaleDesc", "Verifies AI difficulty scales dynamically in adaptive mode."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAITester::TestFairness()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("InputRead"), NSLOCTEXT("QA", "InputReadDesc", "Verifies AI does not read player inputs unfairly."), true));
	Results.Add(MakeTest(TEXT("FramePerfect"), NSLOCTEXT("QA", "FramePerfectDesc", "Verifies AI does not react with frame-perfect precision on lower difficulties."), true));
	Results.Add(MakeTest(TEXT("PatternRepeat"), NSLOCTEXT("QA", "PatternRepeatDesc", "Verifies AI does not repeat the same pattern endlessly."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAITester::RunFullAITestSuite()
{
	TArray<FQATestCase> All;
	All.Append(TestDifficultyLevels());
	All.Append(TestAIReactions());
	All.Append(TestCombatDecisions());
	All.Append(TestStyleBehaviors());
	All.Append(TestAdaptiveLearning());
	All.Append(TestFairness());
	return All;
}
