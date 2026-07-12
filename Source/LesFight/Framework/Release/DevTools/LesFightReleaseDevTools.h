#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightReleaseDevTools.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightReleaseDevTools : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	TArray<FString> ShowBuildInfo();

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	TArray<FString> VerifyBuildIntegrity();

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	TArray<FString> RunPreReleaseValidation();

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	void LogReleaseEvent(const FString& Event);

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	TArray<FString> GetReleaseLog() const;

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	void ClearReleaseLog();

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	TArray<FString> GetAvailableCommands() const;

	UFUNCTION(BlueprintCallable, Category = "Release|DevTools")
	void ExecuteCommand(const FString& Command);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|DevTools")
	TArray<FString> ReleaseLog;

	static constexpr int32 MaxLogEntries = 500;
};
