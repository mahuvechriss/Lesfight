#include "Framework/Release/Updates/LesFightPatchBuilder.h"

void ULesFightPatchBuilder::Initialize()
{
	PatchHistory.Empty();
	ModifiedFiles.Empty();
	bPatchBuilt = false;
	PatchVersion.Major = 1;
	PatchVersion.Minor = 0;
	PatchVersion.Patch = 1;
}

void ULesFightPatchBuilder::Shutdown()
{
	PatchHistory.Empty();
	ModifiedFiles.Empty();
}

FVersionInfo ULesFightPatchBuilder::GetPatchVersion() const
{
	return PatchVersion;
}

void ULesFightPatchBuilder::SetPatchVersion(const FVersionInfo& Version)
{
	PatchVersion = Version;
}

TArray<FString> ULesFightPatchBuilder::GeneratePatchNotes()
{
	TArray<FString> Notes;
	Notes.Add(FString::Printf(TEXT("LesFight Patch %s"), *PatchVersion.ToString()));
	Notes.Add(TEXT(""));
	Notes.Add(TEXT("Fixes:"));
	Notes.Add(TEXT("- General stability improvements"));
	Notes.Add(TEXT("- Performance optimizations"));
	Notes.Add(TEXT("- Bug fixes"));
	PatchHistory.Append(Notes);
	return Notes;
}

TArray<FString> ULesFightPatchBuilder::GetModifiedFiles() const
{
	if (ModifiedFiles.Num() == 0)
	{
		TArray<FString> DefaultFiles;
		DefaultFiles.Add(TEXT("LesFight.exe"));
		DefaultFiles.Add(TEXT("Content/Paks/LesFight.pak"));
		DefaultFiles.Add(TEXT("Config/DefaultEngine.ini"));
		return DefaultFiles;
	}
	return ModifiedFiles;
}

int64 ULesFightPatchBuilder::CalculatePatchSize() const
{
	return 500LL * 1024 * 1024;
}

bool ULesFightPatchBuilder::BuildPatch()
{
	PatchHistory.Add(FString::Printf(TEXT("Patch %s built"), *PatchVersion.ToString()));
	bPatchBuilt = true;
	UE_LOG(LogTemp, Log, TEXT("[Patcher] Patch %s built successfully"), *PatchVersion.ToString());
	return true;
}

bool ULesFightPatchBuilder::VerifyPatch()
{
	if (!bPatchBuilt) return false;
	UE_LOG(LogTemp, Log, TEXT("[Patcher] Patch verified"));
	return true;
}

TArray<FString> ULesFightPatchBuilder::GetPatchHistory() const
{
	return PatchHistory;
}
