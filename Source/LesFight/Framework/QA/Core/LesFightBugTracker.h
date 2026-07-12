#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightBugTracker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBugReported, const FQABugEntry&, Bug);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBugStatusChanged, const FQABugEntry&, Bug);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightBugTracker : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	int32 ReportBug(const FString& Title, const FText& Description, const FString& Area, EBugSeverity Severity, const TArray<FString>& StepsToReproduce);

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	bool UpdateBugStatus(int32 BugID, EBugStatus NewStatus);

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	bool AssignBug(int32 BugID, const FString& Assignee);

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	FQABugEntry GetBugByID(int32 BugID) const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	TArray<FQABugEntry> GetAllBugs() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	TArray<FQABugEntry> GetBugsByArea(const FString& Area) const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	TArray<FQABugEntry> GetBugsByStatus(EBugStatus Status) const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	TArray<FQABugEntry> GetBugsByAssignee(const FString& Assignee) const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	TArray<FQABugEntry> GetCriticalBugs() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	int32 GetBugCount() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	int32 GetOpenBugCount() const;

	UFUNCTION(BlueprintCallable, Category = "QA|BugTracker")
	bool ExportBugsToFile(const FString& FilePath);

	UPROPERTY(BlueprintAssignable, Category = "QA|BugTracker")
	FOnBugReported OnBugReported;

	UPROPERTY(BlueprintAssignable, Category = "QA|BugTracker")
	FOnBugStatusChanged OnBugStatusChanged;

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|BugTracker")
	TArray<FQABugEntry> BugDatabase;

	UPROPERTY(VisibleInstanceOnly, Category = "QA|BugTracker")
	int32 NextBugID = 1;
};
