#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightQADevTools.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightQADevTools : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void SpawnTestDummy();

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void SetInvincible(bool bInvincible);

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void SetInfiniteMeter(bool bInfinite);

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void ForceMatchEnd(int32 WinningPlayerIndex);

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void TeleportToPosition(float X, float Y, float Z);

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void LogAllSystemStates();

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void ShowDebugOverlay();

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	TArray<FString> GetAvailableCommands() const;

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void ExecuteCommand(const FString& Command);

	UFUNCTION(BlueprintCallable, Category = "QA|DevTools")
	void RunQuickSmokeTest();

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|DevTools")
	bool bInvincibleMode = false;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|DevTools")
	bool bInfiniteMeterMode = false;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|DevTools")
	TArray<FString> CommandHistory;
};
