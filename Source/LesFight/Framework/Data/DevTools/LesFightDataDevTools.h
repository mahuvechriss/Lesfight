#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightDataDevTools.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightDataDevTools : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> InspectSaveFile(FString FilePath);

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> ViewProfileData(FName ProfileID);

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> ViewCharacterData(FName CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> ViewSettingsData();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> ViewStatisticsData();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> ViewProgressionData();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	bool ResetProfile(FName ProfileID);

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	bool ResetAllProfiles();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	bool ResetAllCharacters();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	bool ResetAllData();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	bool TestSaveCorruption(FName Identifier);

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	bool TestBackupRestore(FName Identifier);

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	FName GenerateTestProfile();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	FName GenerateTestCharacter();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> RunFullDataTest();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	void EnableDataLogging(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	bool IsDataLoggingEnabled();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	TArray<FString> GetDataLog();

	UFUNCTION(BlueprintCallable, Category = "Data Dev Tools")
	void ClearDataLog();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Data Dev Tools")
	bool bDataLogging = false;

	UPROPERTY(VisibleAnywhere, Category = "Data Dev Tools")
	TArray<FString> DataLog;
};
