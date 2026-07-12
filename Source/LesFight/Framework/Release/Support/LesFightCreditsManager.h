#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Release/Core/LesFightReleaseDataTypes.h"
#include "LesFightCreditsManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCreditsManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	void Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	TArray<FString> GetDeveloperCredits() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	TArray<FString> GetThirdPartyCredits() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	TArray<FString> GetLicenseInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	TArray<FString> GetSpecialThanks() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	TArray<FString> GetFullCreditsText() const;

	UFUNCTION(BlueprintCallable, Category = "Release|Credits")
	bool ExportCredits(const FString& FilePath);

protected:
	UPROPERTY(VisibleInstanceOnly, Category = "Release|Credits")
	TArray<FString> DeveloperCredits;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Credits")
	TArray<FString> ThirdPartyCredits;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Credits")
	TArray<FString> LicenseInfo;

	UPROPERTY(VisibleInstanceOnly, Category = "Release|Credits")
	TArray<FString> SpecialThanks;
};
