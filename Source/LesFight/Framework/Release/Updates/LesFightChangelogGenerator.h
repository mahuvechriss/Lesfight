#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightChangelogGenerator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightChangelogGenerator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	void RecordAddition(const FString& Addition);

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	void RecordFix(const FString& Fix);

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	void RecordChange(const FString& Change);

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	void RecordRemoval(const FString& Removal);

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	void RecordKnownIssue(const FString& Issue);

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	FChangelogEntry FinalizeEntry(const FVersionInfo& Version);

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	FString GenerateChangelogText(const TArray<FChangelogEntry>& History);

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	TArray<FChangelogEntry> GetChangelogHistory() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Changelog")
	bool ExportChangelog(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Changelog")
	TArray<FString> PendingAdditions;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Changelog")
	TArray<FString> PendingFixes;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Changelog")
	TArray<FString> PendingChanges;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Changelog")
	TArray<FString> PendingRemovals;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Changelog")
	TArray<FString> PendingKnownIssues;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Changelog")
	TArray<FChangelogEntry> ChangelogHistory;
};
