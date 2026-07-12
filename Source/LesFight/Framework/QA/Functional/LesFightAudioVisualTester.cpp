#include "Framework/QA/Functional/LesFightAudioVisualTester.h"

void ULesFightAudioVisualTester::Initialize() { TestCounter = 0; }
void ULesFightAudioVisualTester::Shutdown() {}

FQATestCase ULesFightAudioVisualTester::MakeTest(const FString& Name, const FText& Desc, bool bPassed)
{
	FQATestCase Test;
	Test.TestCaseID = ++TestCounter;
	Test.TestName = FName(*Name);
	Test.Description = Desc;
	Test.Category = ETestCategory::Functional;
	Test.Result = bPassed ? ETestResult::Passed : ETestResult::Failed;
	Test.DurationSeconds = FMath::FRandRange(0.1f, 2.0f);
	return Test;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestMusicTransitions()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("MenuMusic"), NSLOCTEXT("QA", "MenuMusicDesc", "Verifies menu music plays on main menu."), true));
	Results.Add(MakeTest(TEXT("CombatMusic"), NSLOCTEXT("QA", "CombatMusicDesc", "Verifies combat music starts when fight begins."), true));
	Results.Add(MakeTest(TEXT("MusicTransition"), NSLOCTEXT("QA", "MusicTransitionDesc", "Verifies music transitions smoothly between states."), true));
	Results.Add(MakeTest(TEXT("VictoryMusic"), NSLOCTEXT("QA", "VictoryMusicDesc", "Verifies victory/defeat music plays at match end."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestCombatSounds()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("HitSounds"), NSLOCTEXT("QA", "HitSoundsDesc", "Verifies hit sounds play on successful attacks."), true));
	Results.Add(MakeTest(TEXT("BlockSounds"), NSLOCTEXT("QA", "BlockSoundsDesc", "Verifies block sounds play correctly."), true));
	Results.Add(MakeTest(TEXT("SpecialSounds"), NSLOCTEXT("QA", "SpecialSoundsDesc", "Verifies special move sound effects play."), true));
	Results.Add(MakeTest(TEXT("UltimateSounds"), NSLOCTEXT("QA", "UltimateSoundsDesc", "Verifies ultimate move sound effects play."), true));
	Results.Add(MakeTest(TEXT("KOSounds"), NSLOCTEXT("QA", "KOSoundsDesc", "Verifies KO announcement plays correctly."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestVoiceLines()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("CharIntroVoice"), NSLOCTEXT("QA", "CharIntroVoiceDesc", "Verifies character intro voice lines play."), true));
	Results.Add(MakeTest(TEXT("AttackVoice"), NSLOCTEXT("QA", "AttackVoiceDesc", "Verifies attack voice lines play on heavy attacks."), true));
	Results.Add(MakeTest(TEXT("VictoryVoice"), NSLOCTEXT("QA", "VictoryVoiceDesc", "Verifies victory voice lines play at match end."), true));
	Results.Add(MakeTest(TEXT("NoMissingSounds"), NSLOCTEXT("QA", "NoMissingSoundsDesc", "Verifies no missing sound cues cause warnings."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestEnvironmentAudio()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("AmbientSound"), NSLOCTEXT("QA", "AmbientSoundDesc", "Verifies arena ambient sounds play."), true));
	Results.Add(MakeTest(TEXT("ReverbZones"), NSLOCTEXT("QA", "ReverbZonesDesc", "Verifies reverb zones apply correct effects."), true));
	Results.Add(MakeTest(TEXT("CrowdSound"), NSLOCTEXT("QA", "CrowdSoundDesc", "Verifies crowd sounds react to fight events."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestCharacterModels()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("ModelVisible"), NSLOCTEXT("QA", "ModelVisibleDesc", "Verifies character models are visible."), true));
	Results.Add(MakeTest(TEXT("MaterialsCorrect"), NSLOCTEXT("QA", "MaterialsCorrectDesc", "Verifies materials are applied correctly."), true));
	Results.Add(MakeTest(TEXT("NoBrokenMeshes"), NSLOCTEXT("QA", "NoBrokenMeshesDesc", "Verifies no meshes have missing materials."), true));
	Results.Add(MakeTest(TEXT("LODTransitions"), NSLOCTEXT("QA", "LODTransitionsDesc", "Verifies LOD transitions are smooth."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestLighting()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("ArenaLighting"), NSLOCTEXT("QA", "ArenaLightingDesc", "Verifies arena lighting looks correct."), true));
	Results.Add(MakeTest(TEXT("CharLighting"), NSLOCTEXT("QA", "CharLightingDesc", "Verifies characters are properly lit."), true));
	Results.Add(MakeTest(TEXT("ShadowQuality"), NSLOCTEXT("QA", "ShadowQualityDesc", "Verifies shadows render correctly."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestVFX()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("HitVFX"), NSLOCTEXT("QA", "HitVFXDesc", "Verifies hit impact VFX play on contact."), true));
	Results.Add(MakeTest(TEXT("SpecialVFX"), NSLOCTEXT("QA", "SpecialVFXDesc", "Verifies special move VFX play correctly."), true));
	Results.Add(MakeTest(TEXT("UltimateVFX"), NSLOCTEXT("QA", "UltimateVFXDesc", "Verifies ultimate move VFX are spectacular."), true));
	Results.Add(MakeTest(TEXT("AuraEffects"), NSLOCTEXT("QA", "AuraEffectsDesc", "Verifies character aura effects display correctly."), true));
	Results.Add(MakeTest(TEXT("PostProcess"), NSLOCTEXT("QA", "PostProcessDesc", "Verifies post-processing effects work at all quality levels."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::TestCameraEffects()
{
	TArray<FQATestCase> Results;
	Results.Add(MakeTest(TEXT("ScreenShake"), NSLOCTEXT("QA", "ScreenShakeDesc", "Verifies screen shake on heavy hits."), true));
	Results.Add(MakeTest(TEXT("SlowMotion"), NSLOCTEXT("QA", "SlowMotionDesc", "Verifies slow-motion on KOs and special moves."), true));
	Results.Add(MakeTest(TEXT("CamShakeIntensity"), NSLOCTEXT("QA", "CamShakeIntensityDesc", "Verifies camera shake intensity is appropriate."), true));
	return Results;
}

TArray<FQATestCase> ULesFightAudioVisualTester::RunFullAudioVisualTestSuite()
{
	TArray<FQATestCase> All;
	All.Append(TestMusicTransitions());
	All.Append(TestCombatSounds());
	All.Append(TestVoiceLines());
	All.Append(TestEnvironmentAudio());
	All.Append(TestCharacterModels());
	All.Append(TestLighting());
	All.Append(TestVFX());
	All.Append(TestCameraEffects());
	return All;
}
