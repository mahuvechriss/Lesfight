#include "Framework/Audio/Testing/LesFightAudioDevTools.h"

void ULesFightAudioDevTools::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bDebugMode = false;
    MaxLogEntries = 200;
    TestLog.Empty();
    BenchmarkResults.Empty();
}

void ULesFightAudioDevTools::EnableDebugMode(bool bEnabled)
{
    bDebugMode = bEnabled;
}

void ULesFightAudioDevTools::PlayTestSound(FName SoundName)
{
    if (TestLog.Num() >= MaxLogEntries) TestLog.RemoveAt(0);
    TestLog.Add(FString::Printf(TEXT("PlayTestSound: %s"), *SoundName.ToString()));
}

void ULesFightAudioDevTools::PlayTestMusicState(EMusicState State)
{
    if (TestLog.Num() >= MaxLogEntries) TestLog.RemoveAt(0);
    TestLog.Add(FString::Printf(TEXT("PlayTestMusicState: %s"), *UEnum::GetValueAsString(State)));
}

void ULesFightAudioDevTools::PlayTestVoiceLine(EVoiceContext Context)
{
    if (TestLog.Num() >= MaxLogEntries) TestLog.RemoveAt(0);
    TestLog.Add(FString::Printf(TEXT("PlayTestVoiceLine: %s"), *UEnum::GetValueAsString(Context)));
}

void ULesFightAudioDevTools::TestSpatialAudio(FVector SoundPosition)
{
    if (TestLog.Num() >= MaxLogEntries) TestLog.RemoveAt(0);
    TestLog.Add(FString::Printf(TEXT("TestSpatialAudio at (%.2f, %.2f, %.2f)"), SoundPosition.X, SoundPosition.Y, SoundPosition.Z));
}

void ULesFightAudioDevTools::DisplayAudioStats()
{
    if (TestLog.Num() >= MaxLogEntries) TestLog.RemoveAt(0);
    TestLog.Add(TEXT("DisplayAudioStats requested"));
}

void ULesFightAudioDevTools::LogActiveSounds()
{
    if (TestLog.Num() >= MaxLogEntries) TestLog.RemoveAt(0);
    TestLog.Add(TEXT("LogActiveSounds requested"));
}

void ULesFightAudioDevTools::RunAudioBenchmark()
{
    BenchmarkResults.Empty();
    BenchmarkResults.Add(TEXT("Benchmark_Start"), GetWorld()->GetTimeSeconds());
    if (TestLog.Num() >= MaxLogEntries) TestLog.RemoveAt(0);
    TestLog.Add(TEXT("RunAudioBenchmark started"));
}

FString ULesFightAudioDevTools::GenerateAudioReport() const
{
    FString Report = TEXT("=== Audio Dev Report ===\n");
    Report += FString::Printf(TEXT("Debug Mode: %s\n"), bDebugMode ? TEXT("Enabled") : TEXT("Disabled"));
    Report += FString::Printf(TEXT("Log Entries: %d\n"), TestLog.Num());
    Report += FString::Printf(TEXT("Benchmark Results: %d\n"), BenchmarkResults.Num());
    return Report;
}
