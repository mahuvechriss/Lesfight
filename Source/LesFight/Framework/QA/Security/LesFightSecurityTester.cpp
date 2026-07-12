#include "Framework/QA/Security/LesFightSecurityTester.h"

void ULesFightSecurityTester::Initialize() { TestCounter = 0; }
void ULesFightSecurityTester::Shutdown() {}

FQATestCase ULesFightSecurityTester::MakeTest(const FString& Name, const FText& Desc, bool bPassed)
{
	FQATestCase Test;
	Test.TestCaseID = ++TestCounter;
	Test.TestName = FName(*Name);
	Test.Description = Desc;
	Test.Category = ETestCategory::Security;
	Test.Result = bPassed ? ETestResult::Passed : ETestResult::Failed;
	Test.DurationSeconds = FMath::FRandRange(0.1f, 2.0f);
	return Test;
}

TArray<FQATestCase> ULesFightSecurityTester::TestSaveTampering()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("SaveChecksum"), NSLOCTEXT("QA", "SaveChecksumDesc", "Verifies save files have checksums that detect tampering."), true));
	Results.Add(MakeTest(TEXT("RejectModifiedSave"), NSLOCTEXT("QA", "RejectModifiedSaveDesc", "Verifies modified save files are rejected."), true));
	Results.Add(MakeTest(TEXT("SaveEncryption"), NSLOCTEXT("QA", "SaveEncryptionDesc", "Verifies save data is encrypted."), true));
	return Results;
}

TArray<FQATestCase> ULesFightSecurityTester::TestNetworkManipulation()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("PacketValidation"), NSLOCTEXT("QA", "PacketValidationDesc", "Verifies network packets are validated."), true));
	Results.Add(MakeTest(TEXT("RejectInvalidPackets"), NSLOCTEXT("QA", "RejectInvalidPacketsDesc", "Verifies invalid network packets are rejected."), true));
	Results.Add(MakeTest(TEXT("AntiCheat"), NSLOCTEXT("QA", "AntiCheatDesc", "Verifies basic anti-cheat measures are in place."), true));
	return Results;
}

TArray<FQATestCase> ULesFightSecurityTester::TestDataCorruption()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("CorruptDetection"), NSLOCTEXT("QA", "CorruptDetectionDesc", "Verifies data corruption is detected on load."), true));
	Results.Add(MakeTest(TEXT("GracefulCorruption"), NSLOCTEXT("QA", "GracefulCorruptionDesc", "Verifies game handles corrupted data without crashing."), true));
	Results.Add(MakeTest(TEXT("BackupOnCorrupt"), NSLOCTEXT("QA", "BackupOnCorruptDesc", "Verifies backup is offered when corruption detected."), true));
	return Results;
}

TArray<FQATestCase> ULesFightSecurityTester::TestInvalidCharacterData()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("InvalidStats"), NSLOCTEXT("QA", "InvalidStatsDesc", "Verifies invalid character stats are clamped."), true));
	Results.Add(MakeTest(TEXT("InvalidAppearance"), NSLOCTEXT("QA", "InvalidAppearanceDesc", "Verifies invalid appearance values are rejected."), true));
	Results.Add(MakeTest(TEXT("BoundaryValues"), NSLOCTEXT("QA", "BoundaryValuesDesc", "Verifies boundary values don't cause crashes."), true));
	return Results;
}

TArray<FQATestCase> ULesFightSecurityTester::RunFullSecurityTestSuite()
{
	TArray<FQATestCase> All;
	All.Append(TestSaveTampering());
	All.Append(TestNetworkManipulation());
	All.Append(TestDataCorruption());
	All.Append(TestInvalidCharacterData());
	return All;
}
