#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightReleaseDataTypes.generated.h"

UENUM(BlueprintType)
enum class EBuildType : uint8
{
	Development	UMETA(DisplayName = "Development"),
	QA			UMETA(DisplayName = "QA"),
	Release		UMETA(DisplayName = "Release"),
	Shipping	UMETA(DisplayName = "Shipping")
};

UENUM(BlueprintType)
enum class EReleasePlatform : uint8
{
	Windows		UMETA(DisplayName = "Windows PC"),
	Console		UMETA(DisplayName = "Console"),
	Cloud		UMETA(DisplayName = "Cloud"),
	MAX			UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class EPackageComponent : uint8
{
	GameExecutable	UMETA(DisplayName = "Game Executable"),
	Content			UMETA(DisplayName = "Content"),
	Engine			UMETA(DisplayName = "Engine"),
	Plugins			UMETA(DisplayName = "Plugins"),
	Config			UMETA(DisplayName = "Configuration"),
	Documentation	UMETA(DisplayName = "Documentation"),
	Support			UMETA(DisplayName = "Support")
};

UENUM(BlueprintType)
enum class EInstallAction : uint8
{
	Install		UMETA(DisplayName = "Install"),
	Update		UMETA(DisplayName = "Update"),
	Repair		UMETA(DisplayName = "Repair"),
	Uninstall	UMETA(DisplayName = "Uninstall")
};

UENUM(BlueprintType)
enum class EAssetAuditResult : uint8
{
	Valid		UMETA(DisplayName = "Valid"),
	Unused		UMETA(DisplayName = "Unused"),
	MissingRef	UMETA(DisplayName = "Missing Reference"),
	Broken		UMETA(DisplayName = "Broken"),
	Optimized	UMETA(DisplayName = "Optimized")
};

USTRUCT(BlueprintType)
struct FBuildConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	EBuildType BuildType = EBuildType::Development;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	EReleasePlatform TargetPlatform = EReleasePlatform::Windows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString BuildDirectory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString OutputDirectory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	bool bEnableDebugSymbols = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	bool bEnableOptimization = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	bool bCookContent = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	bool bCompressPackages = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int32 BuildNumber = 0;
};

USTRUCT(BlueprintType)
struct FVersionInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int32 Major = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int32 Minor = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int32 Patch = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int32 BuildNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString VersionSuffix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString BuildDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString CommitHash;

	FString ToString() const
	{
		if (VersionSuffix.IsEmpty())
		{
			return FString::Printf(TEXT("%d.%d.%d.%d"), Major, Minor, Patch, BuildNumber);
		}
		return FString::Printf(TEXT("%d.%d.%d.%d-%s"), Major, Minor, Patch, BuildNumber, *VersionSuffix);
	}
};

USTRUCT(BlueprintType)
struct FChangelogEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FVersionInfo Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FDateTime ReleaseDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	TArray<FString> Additions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	TArray<FString> Fixes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	TArray<FString> Changes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	TArray<FString> Removals;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	TArray<FString> KnownIssues;
};

USTRUCT(BlueprintType)
struct FPackageManifestEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString FileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int64 FileSizeBytes = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString MD5Hash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	EPackageComponent Component = EPackageComponent::Content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	bool bRequired = true;
};

USTRUCT(BlueprintType)
struct FAssetAuditEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString AssetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString AssetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int64 DiskSizeBytes = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	int32 ReferenceCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	EAssetAuditResult AuditResult = EAssetAuditResult::Valid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	TArray<FString> ReferencedBy;
};

USTRUCT(BlueprintType)
struct FReleaseChecklist
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	bool bCompleted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FText Notes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Release")
	FString VerifiedBy;
};
