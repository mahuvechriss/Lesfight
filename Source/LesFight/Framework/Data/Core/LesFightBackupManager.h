#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Data/Core/LesFightDataTypes.h"
#include "LesFightBackupManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBackupOperationDelegate, int32, BackupIndex);

USTRUCT(BlueprintType)
struct FBackupEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backup")
	int32 BackupIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backup")
	FDateTime Timestamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backup")
	EDataCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backup")
	FName Identifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backup")
	int32 FileSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Backup")
	FString Checksum;
};

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightBackupManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	ESaveResult CreateBackup(EDataCategory Category, FName Identifier);

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	ESaveResult CreateFullBackup();

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	ESaveResult RestoreFromBackup(EDataCategory Category, FName Identifier, int32 BackupIndex);

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	ESaveResult RestoreFullBackup(int32 BackupIndex);

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	TArray<FBackupEntry> ListBackups(EDataCategory Category) const;

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	TArray<FBackupEntry> ListAllBackups() const { return Backups; }

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	bool DeleteBackup(int32 BackupIndex);

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	int32 GetLatestBackup(EDataCategory Category, FName Identifier) const;

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	bool DetectCorruption(FName Identifier) const;

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	ESaveResult AttemptRecovery(FName Identifier);

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	void SetAutoBackupInterval(float IntervalMinutes) { AutoBackupInterval = IntervalMinutes; }

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	float GetAutoBackupInterval() const { return AutoBackupInterval; }

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	void SetMaxBackups(int32 Count) { MaxBackups = Count; }

	UFUNCTION(BlueprintCallable, Category = "Backup Manager")
	int32 GetMaxBackups() const { return MaxBackups; }

	UPROPERTY(BlueprintAssignable, Category = "Backup Manager")
	FOnBackupOperationDelegate OnBackupCreated;

	UPROPERTY(BlueprintAssignable, Category = "Backup Manager")
	FOnBackupOperationDelegate OnBackupRestored;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Backup Manager")
	TArray<FBackupEntry> Backups;

	UPROPERTY(EditDefaultsOnly, Category = "Backup Manager")
	float AutoBackupInterval = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Backup Manager")
	int32 MaxBackups = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Backup Manager")
	bool bAutoBackupEnabled = true;

	UPROPERTY(VisibleAnywhere, Category = "Backup Manager")
	float TimeSinceLastBackup = 0.0f;

private:
	static constexpr int32 MaxBackupEntries = 50;
	FString GetBackupDirectory() const;
	FString GetBackupFilePath(int32 BackupIndex, EDataCategory Category, FName Identifier) const;
	FString GetBackupMetaFilePath() const;
	void SaveBackupMetadata();
	void LoadBackupMetadata();
	int32 GetNextBackupIndex();
	void EnforceMaxBackups();
};
