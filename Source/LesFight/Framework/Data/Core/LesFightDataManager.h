#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightDataManager.generated.h"

class ULesFightSaveManager;
class ULesFightBackupManager;
class ULesFightDataSecurity;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataLoadedDelegate, bool, bSuccess);

UCLASS(Blueprintable, BlueprintType)
class LESFIGHT_API ULesFightDataManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	ULesFightSaveManager* GetSaveManager() const { return SaveManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	ULesFightBackupManager* GetBackupManager() const { return BackupManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	ULesFightDataSecurity* GetDataSecurity() const { return DataSecurity; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetProfileManager() const { return ProfileManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetCharacterDataManager() const { return CharacterDataManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetProgressionManager() const { return ProgressionManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetUnlockManager() const { return UnlockManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetAchievementManager() const { return AchievementManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetStatisticsManager() const { return StatisticsManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetMatchHistoryManager() const { return MatchHistoryManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetSettingsManager() const { return SettingsManager; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	UObject* GetDataDevTools() const { return DataDevTools; }

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	ESaveResult SaveAllData();

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	ESaveResult LoadAllData(const FName& ProfileID);

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	bool ResetAllData();

	UFUNCTION(BlueprintCallable, Category = "Data Manager")
	int32 GetDataVersion() const { return DataVersion; }

	UPROPERTY(BlueprintAssignable, Category = "Data Manager")
	FOnDataLoadedDelegate OnDataLoaded;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	ULesFightSaveManager* SaveManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	ULesFightBackupManager* BackupManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	ULesFightDataSecurity* DataSecurity = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* ProfileManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* CharacterDataManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* ProgressionManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* UnlockManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* AchievementManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* StatisticsManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* MatchHistoryManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* SettingsManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	UObject* DataDevTools = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Data Manager")
	bool bInitialized = false;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	int32 DataVersion = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<ULesFightSaveManager> SaveManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<ULesFightBackupManager> BackupManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<ULesFightDataSecurity> DataSecurityClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> ProfileManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> CharacterDataManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> ProgressionManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> UnlockManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> AchievementManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> StatisticsManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> MatchHistoryManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> SettingsManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Data Manager")
	TSubclassOf<UObject> DataDevToolsClass;

private:
	template<typename T>
	T* CreateSubsystem(TSubclassOf<T> Class, UObject* Outer)
	{
		if (Class)
		{
			return NewObject<T>(Outer, Class);
		}
		return nullptr;
	}
};
