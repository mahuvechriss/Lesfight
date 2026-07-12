#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightSaveManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSaveOperationDelegate, EDataCategory, Category, FName, Identifier);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSaveManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	ESaveResult SaveProfile(const FPlayerProfileData& ProfileData);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	ESaveResult SaveCharacter(const FCharacterSaveData& CharacterData);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	ESaveResult SaveSettings(const FSettingsData& Settings);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	ESaveResult SaveStatistics(const FMatchStatisticsData& Stats);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	ESaveResult SaveProgression(const FProgressionData& Progression);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	ESaveResult SaveMatchHistory(const TArray<FMatchHistoryEntry>& History);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	ESaveResult SaveAll(const FPlayerProfileData& Profile, const TArray<FCharacterSaveData>& Characters, const FSettingsData& Settings);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	FPlayerProfileData LoadProfile(const FName& ProfileID);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	FCharacterSaveData LoadCharacter(const FName& CharacterID);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	FSettingsData LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	FMatchStatisticsData LoadStatistics();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	FProgressionData LoadProgression();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	TArray<FMatchHistoryEntry> LoadMatchHistory();

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	bool DoesSaveExist(EDataCategory Category, const FName& Identifier);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	bool DeleteSave(EDataCategory Category, const FName& Identifier);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	FString GetSaveDirectory() const;

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	void SetSaveSlot(int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	int32 GetCurrentSlot() const { return CurrentSlotIndex; }

	UFUNCTION(BlueprintCallable, Category = "Save Manager")
	TArray<int32> GetAvailableSlots() const;

	UPROPERTY(BlueprintAssignable, Category = "Save Manager")
	FOnSaveOperationDelegate OnSaveCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Save Manager")
	FOnSaveOperationDelegate OnLoadCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Save Manager")
	FOnSaveOperationDelegate OnSaveFailed;

	UPROPERTY(BlueprintAssignable, Category = "Save Manager")
	FOnSaveOperationDelegate OnLoadFailed;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Save Manager")
	int32 CurrentSlotIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Save Manager")
	int32 MaxSlots = 3;

	UPROPERTY(VisibleAnywhere, Category = "Save Manager")
	FString BaseSaveDirectory;

	UPROPERTY(VisibleAnywhere, Category = "Save Manager")
	bool bInitialized = false;

	UPROPERTY(EditDefaultsOnly, Category = "Save Manager")
	int32 SaveVersion = 1;

private:
	FString GetCategoryFileName(EDataCategory Category, const FName& Identifier) const;
	bool CreateSlotDirectory(int32 SlotIndex) const;
	ESaveResult SaveDataToFile(EDataCategory Category, const FName& Identifier, const TArray<uint8>& Data);
	bool LoadDataFromFile(EDataCategory Category, const FName& Identifier, TArray<uint8>& OutData) const;
};
