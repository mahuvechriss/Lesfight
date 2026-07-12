#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightUpdateManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightUpdateManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	bool CheckForUpdate();

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	FVersionInfo GetLatestAvailableVersion() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	TArray<FString> GetUpdateNotes() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	int64 GetUpdateSizeBytes() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	bool DownloadUpdate();

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	bool ApplyUpdate();

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	bool VerifyUpdateIntegrity();

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	void RollbackUpdate();

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	TArray<FVersionInfo> GetUpdateHistory() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Updates")
	FString GetUpdateStatus() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Updates")
	FVersionInfo LatestVersion;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Updates")
	TArray<FString> UpdateNotes;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Updates")
	TArray<FVersionInfo> UpdateHistory;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Updates")
	bool bUpdateAvailable = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Updates")
	bool bUpdateDownloaded = false;
};
