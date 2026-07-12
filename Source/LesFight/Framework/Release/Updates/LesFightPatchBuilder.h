#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightPatchBuilder.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPatchBuilder : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	FVersionInfo GetPatchVersion() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	void SetPatchVersion(const FVersionInfo& Version);

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	TArray<FString> GeneratePatchNotes();

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	TArray<FString> GetModifiedFiles() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	int64 CalculatePatchSize() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	bool BuildPatch();

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	bool VerifyPatch();

	UFUNCTION(BlueprintCallable, Category = "Release|Patches")
	TArray<FString> GetPatchHistory() const;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Patches")
	FVersionInfo PatchVersion;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Patches")
	TArray<FString> PatchHistory;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Patches")
	TArray<FString> ModifiedFiles;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Patches")
	bool bPatchBuilt = false;
};
