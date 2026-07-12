#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightPlayerManualGenerator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightPlayerManualGenerator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateInstallationSection();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateControlsSection();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateGameModesSection();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateCharacterCreationSection();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateMultiplayerSection();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateSettingsSection();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	FString GenerateFullManual();

	UFUNCTION(BlueprintCallable, Category = "Release|Docs")
	bool ExportManual(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Docs")
	TArray<FString> ManualSections;
};
