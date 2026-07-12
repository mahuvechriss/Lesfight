#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightReleaseConfigurator.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightReleaseConfigurator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	void LoadDefaultSettings();

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	void ConfigurePackaging();

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	void ConfigureCompression();

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	void ConfigureCooking();

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	TArray<FString> GetConfigurationSummary();

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	bool ExportConfig(const FString& FilePath);

	UFUNCTION(BlueprintCallable, Category = "Release|Config")
	bool ImportConfig(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Config")
	TMap<FString, FString> ConfigSettings;
};
