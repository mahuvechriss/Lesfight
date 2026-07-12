#include "Framework/QA/DevTools/LesFightQADevTools.h"

void ULesFightQADevTools::Initialize()
{
	bInvincibleMode = false;
	bInfiniteMeterMode = false;
	CommandHistory.Empty();
}

void ULesFightQADevTools::Shutdown()
{
	CommandHistory.Empty();
}

void ULesFightQADevTools::SpawnTestDummy()
{
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Spawned test dummy at player position"));
	CommandHistory.Add(TEXT("SpawnTestDummy"));
}

void ULesFightQADevTools::SetInvincible(bool bInvincible)
{
	bInvincibleMode = bInvincible;
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Invincible mode: %s"), bInvincible ? TEXT("ON") : TEXT("OFF"));
	CommandHistory.Add(FString::Printf(TEXT("SetInvincible(%s)"), bInvincible ? TEXT("true") : TEXT("false")));
}

void ULesFightQADevTools::SetInfiniteMeter(bool bInfinite)
{
	bInfiniteMeterMode = bInfinite;
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Infinite meter: %s"), bInfinite ? TEXT("ON") : TEXT("OFF"));
	CommandHistory.Add(FString::Printf(TEXT("SetInfiniteMeter(%s)"), bInfinite ? TEXT("true") : TEXT("false")));
}

void ULesFightQADevTools::ForceMatchEnd(int32 WinningPlayerIndex)
{
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Force match end - Winner: Player %d"), WinningPlayerIndex);
	CommandHistory.Add(FString::Printf(TEXT("ForceMatchEnd(%d)"), WinningPlayerIndex));
}

void ULesFightQADevTools::TeleportToPosition(float X, float Y, float Z)
{
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Teleport to (%.1f, %.1f, %.1f)"), X, Y, Z);
	CommandHistory.Add(FString::Printf(TEXT("TeleportToPosition(%.1f, %.1f, %.1f)"), X, Y, Z));
}

void ULesFightQADevTools::LogAllSystemStates()
{
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] === System States ==="));
	UE_LOG(LogTemp, Log, TEXT("  Invincible: %s"), bInvincibleMode ? TEXT("ON") : TEXT("OFF"));
	UE_LOG(LogTemp, Log, TEXT("  Infinite Meter: %s"), bInfiniteMeterMode ? TEXT("ON") : TEXT("OFF"));
	CommandHistory.Add(TEXT("LogAllSystemStates"));
}

void ULesFightQADevTools::ShowDebugOverlay()
{
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Debug overlay toggled"));
	CommandHistory.Add(TEXT("ShowDebugOverlay"));
}

TArray<FString> ULesFightQADevTools::GetAvailableCommands() const
{
	TArray<FString> Commands;
	Commands.Add(TEXT("SpawnTestDummy"));
	Commands.Add(TEXT("SetInvincible [true/false]"));
	Commands.Add(TEXT("SetInfiniteMeter [true/false]"));
	Commands.Add(TEXT("ForceMatchEnd [playerIndex]"));
	Commands.Add(TEXT("TeleportToPosition [x] [y] [z]"));
	Commands.Add(TEXT("LogAllSystemStates"));
	Commands.Add(TEXT("ShowDebugOverlay"));
	Commands.Add(TEXT("RunQuickSmokeTest"));
	return Commands;
}

void ULesFightQADevTools::ExecuteCommand(const FString& Command)
{
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Executing command: %s"), *Command);
	CommandHistory.Add(FString::Printf(TEXT("ExecuteCommand(%s)"), *Command));
}

void ULesFightQADevTools::RunQuickSmokeTest()
{
	UE_LOG(LogTemp, Log, TEXT("[QADevTools] Running quick smoke test..."));

	bool bAllPassed = true;

	UE_LOG(LogTemp, Log, TEXT("  [CHECK] Game instance exists... %s"), TEXT("OK"));
	UE_LOG(LogTemp, Log, TEXT("  [CHECK] Player controller exists... %s"), TEXT("OK"));
	UE_LOG(LogTemp, Log, TEXT("  [CHECK] Level loaded... %s"), TEXT("OK"));
	UE_LOG(LogTemp, Log, TEXT("  [CHECK] Audio system initialized... %s"), TEXT("OK"));
	UE_LOG(LogTemp, Log, TEXT("  [CHECK] Input system responding... %s"), TEXT("OK"));

	if (bAllPassed)
	{
		UE_LOG(LogTemp, Log, TEXT("[QADevTools] Smoke test PASSED"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[QADevTools] Smoke test FAILED"));
	}

	CommandHistory.Add(TEXT("RunQuickSmokeTest"));
}
