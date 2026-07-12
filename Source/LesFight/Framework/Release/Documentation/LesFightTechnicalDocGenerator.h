#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightTechnicalDocGenerator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightTechnicalDocGenerator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateArchitectureSection();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateDevelopmentNotes();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateMaintenanceGuide();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateFullTechnicalDoc();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	bool ExportTechnicalDoc(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Docs")
	TArray<FString> TechDocSections;
};
