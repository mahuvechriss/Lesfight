#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightAssetAuditor.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAssetAuditor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	TArray<FAssetAuditEntry> AuditAllAssets();

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	TArray<FAssetAuditEntry> FindUnusedAssets();

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	TArray<FAssetAuditEntry> FindBrokenReferences();

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	int32 RemoveUnusedAssets();

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	TArray<FString> GetAuditReport() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	int64 GetTotalAssetSize() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	int32 GetAssetCount() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Assets")
	bool ExportAuditReport(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Assets")
	TArray<FAssetAuditEntry> AuditedAssets;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Assets")
	TArray<FString> AuditLog;
};
