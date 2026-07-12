#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/QA/Core/LesFightQADataTypes.h"
#include "LesFightReleaseValidator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightReleaseValidator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	void BuildDefaultChecklist();

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	TArray<FQAReleaseChecklistItem> GetChecklist() const;

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	bool SetItemCompleted(const FString& ItemName, bool bCompleted);

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	bool IsReadyForRelease() const;

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	float GetCompletionPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	TArray<FString> GetIncompleteCriticalItems() const;

	UFUNCTION(BlueprintCallable, Category = "QA|ReleaseValidator")
	void ResetChecklist();

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "QA|ReleaseValidator")
	TArray<FQAReleaseChecklistItem> Checklist;
};
