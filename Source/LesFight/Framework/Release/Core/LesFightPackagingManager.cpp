#include "Framework/Release/Core/LesFightPackagingManager.h"
#include "Misc/FileHelper.h"

void ULesFightPackagingManager::Initialize()
{
	Manifest.Empty();
	PackageOutputPath = TEXT("../../Packaged/LesFight/");
	BuildPackageManifest();
}

void ULesFightPackagingManager::Shutdown()
{
	Manifest.Empty();
}

void ULesFightPackagingManager::BuildPackageManifest()
{
	Manifest.Empty();

	auto AddEntry = [this](const FString& Name, EPackageComponent Component, bool bRequired)
	{
		FPackageManifestEntry Entry;
		Entry.FileName = Name;
		Entry.FileSizeBytes = 0;
		Entry.MD5Hash = TEXT("pending");
		Entry.Component = Component;
		Entry.bRequired = bRequired;
		Manifest.Add(Entry);
	};

	AddEntry(TEXT("LesFight.exe"), EPackageComponent::GameExecutable, true);
	AddEntry(TEXT("LesFight/Binaries/Win64/LesFightGame-Win64-Shipping.exe"), EPackageComponent::GameExecutable, true);
	AddEntry(TEXT("LesFight/Content/Paks/LesFight.pak"), EPackageComponent::Content, true);
	AddEntry(TEXT("LesFight/Content/Paks/LesFight-Project.pak"), EPackageComponent::Content, true);
	AddEntry(TEXT("LesFight/Plugins/"), EPackageComponent::Plugins, true);
	AddEntry(TEXT("LesFight/Config/DefaultEngine.ini"), EPackageComponent::Config, true);
	AddEntry(TEXT("LesFight/Config/DefaultGame.ini"), EPackageComponent::Config, true);
	AddEntry(TEXT("LesFight/Config/DefaultInput.ini"), EPackageComponent::Config, true);
	AddEntry(TEXT("LesFight/Config/DefaultScalability.ini"), EPackageComponent::Config, true);
	AddEntry(TEXT("Engine/Content/EngineMaterials/"), EPackageComponent::Engine, true);
	AddEntry(TEXT("Engine/Content/EngineFonts/"), EPackageComponent::Engine, true);
	AddEntry(TEXT("README.txt"), EPackageComponent::Documentation, false);
	AddEntry(TEXT("Manual.pdf"), EPackageComponent::Documentation, false);
	AddEntry(TEXT("EULA.txt"), EPackageComponent::Support, true);
	AddEntry(TEXT("Credits.txt"), EPackageComponent::Support, false);

	UE_LOG(LogTemp, Log, TEXT("[Packaging] Manifest built: %d entries"), Manifest.Num());
}

TArray<FPackageManifestEntry> ULesFightPackagingManager::GetManifest() const
{
	return Manifest;
}

int64 ULesFightPackagingManager::CalculatePackageSize() const
{
	int64 TotalSize = 0;
	for (const FPackageManifestEntry& Entry : Manifest)
	{
		TotalSize += Entry.FileSizeBytes;
	}
	return TotalSize;
}

bool ULesFightPackagingManager::ValidateManifest()
{
	for (const FPackageManifestEntry& Entry : Manifest)
	{
		if (Entry.bRequired && Entry.MD5Hash.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("[Packaging] Missing hash for required file: %s"), *Entry.FileName);
			return false;
		}
	}
	return true;
}

TArray<FString> ULesFightPackagingManager::GetPackagingSteps()
{
	TArray<FString> Steps;
	Steps.Add(TEXT("1. Build game executable (Shipping config)"));
	Steps.Add(TEXT("2. Cook all content for target platform"));
	Steps.Add(TEXT("3. Compress cooked packages"));
	Steps.Add(TEXT("4. Build package manifest"));
	Steps.Add(TEXT("5. Copy executables to output directory"));
	Steps.Add(TEXT("6. Copy cooked content to output directory"));
	Steps.Add(TEXT("7. Copy engine dependencies"));
	Steps.Add(TEXT("8. Copy configuration files"));
	Steps.Add(TEXT("9. Generate installer (optional)"));
	Steps.Add(TEXT("10. Validate package integrity"));
	return Steps;
}

TArray<FString> ULesFightPackagingManager::GetRequiredFiles() const
{
	TArray<FString> Required;
	for (const FPackageManifestEntry& Entry : Manifest)
	{
		if (Entry.bRequired)
		{
			Required.Add(Entry.FileName);
		}
	}
	return Required;
}

FString ULesFightPackagingManager::GetPackageSummary() const
{
	int32 RequiredCount = 0;
	for (const FPackageManifestEntry& Entry : Manifest)
	{
		if (Entry.bRequired) RequiredCount++;
	}
	return FString::Printf(TEXT("Package: %d total entries (%d required) - ~%.1f GB"),
		Manifest.Num(), RequiredCount, CalculatePackageSize() / (1024.0 * 1024.0 * 1024.0));
}

bool ULesFightPackagingManager::ExportManifest(const FString& FilePath)
{
	FString Output;
	Output += TEXT("LesFight Package Manifest\n");
	Output += TEXT("========================\n\n");

	for (const FPackageManifestEntry& Entry : Manifest)
	{
		Output += FString::Printf(TEXT("[%s] %s (%lld bytes) - %s\n"),
			Entry.bRequired ? TEXT("REQ") : TEXT("OPT"),
			*Entry.FileName,
			Entry.FileSizeBytes,
			*Entry.MD5Hash);
	}

	Output += TEXT("\n---\n");
	Output += GetPackageSummary();

	return FFileHelper::SaveStringToFile(Output, *FilePath);
}
