#include "Framework/Release/Updates/LesFightChangelogGenerator.h"
#include "Misc/FileHelper.h"

void ULesFightChangelogGenerator::Initialize()
{
	PendingAdditions.Empty();
	PendingFixes.Empty();
	PendingChanges.Empty();
	PendingRemovals.Empty();
	PendingKnownIssues.Empty();
	ChangelogHistory.Empty();
}

void ULesFightChangelogGenerator::Shutdown()
{
	PendingAdditions.Empty();
	PendingFixes.Empty();
	PendingChanges.Empty();
	PendingRemovals.Empty();
	PendingKnownIssues.Empty();
}

void ULesFightChangelogGenerator::RecordAddition(const FString& Addition)
{
	PendingAdditions.Add(Addition);
}

void ULesFightChangelogGenerator::RecordFix(const FString& Fix)
{
	PendingFixes.Add(Fix);
}

void ULesFightChangelogGenerator::RecordChange(const FString& Change)
{
	PendingChanges.Add(Change);
}

void ULesFightChangelogGenerator::RecordRemoval(const FString& Removal)
{
	PendingRemovals.Add(Removal);
}

void ULesFightChangelogGenerator::RecordKnownIssue(const FString& Issue)
{
	PendingKnownIssues.Add(Issue);
}

FChangelogEntry ULesFightChangelogGenerator::FinalizeEntry(const FVersionInfo& Version)
{
	FChangelogEntry Entry;
	Entry.Version = Version;
	Entry.ReleaseDate = FDateTime::Now();
	Entry.Additions = PendingAdditions;
	Entry.Fixes = PendingFixes;
	Entry.Changes = PendingChanges;
	Entry.Removals = PendingRemovals;
	Entry.KnownIssues = PendingKnownIssues;

	ChangelogHistory.Add(Entry);

	PendingAdditions.Empty();
	PendingFixes.Empty();
	PendingChanges.Empty();
	PendingRemovals.Empty();
	PendingKnownIssues.Empty();

	return Entry;
}

FString ULesFightChangelogGenerator::GenerateChangelogText(const TArray<FChangelogEntry>& History)
{
	FString Output;
	Output += TEXT("# LesFight Changelog\n\n");

	for (const FChangelogEntry& Entry : History)
	{
		Output += FString::Printf(TEXT("## Version %s (%s)\n\n"),
			*Entry.Version.ToString(), *Entry.ReleaseDate.ToString());

		if (Entry.Additions.Num() > 0)
		{
			Output += TEXT("### Added\n");
			for (const FString& Item : Entry.Additions)
			{
				Output += FString::Printf(TEXT("- %s\n"), *Item);
			}
			Output += TEXT("\n");
		}

		if (Entry.Fixes.Num() > 0)
		{
			Output += TEXT("### Fixed\n");
			for (const FString& Item : Entry.Fixes)
			{
				Output += FString::Printf(TEXT("- %s\n"), *Item);
			}
			Output += TEXT("\n");
		}

		if (Entry.Changes.Num() > 0)
		{
			Output += TEXT("### Changed\n");
			for (const FString& Item : Entry.Changes)
			{
				Output += FString::Printf(TEXT("- %s\n"), *Item);
			}
			Output += TEXT("\n");
		}

		if (Entry.Removals.Num() > 0)
		{
			Output += TEXT("### Removed\n");
			for (const FString& Item : Entry.Removals)
			{
				Output += FString::Printf(TEXT("- %s\n"), *Item);
			}
			Output += TEXT("\n");
		}

		if (Entry.KnownIssues.Num() > 0)
		{
			Output += TEXT("### Known Issues\n");
			for (const FString& Item : Entry.KnownIssues)
			{
				Output += FString::Printf(TEXT("- %s\n"), *Item);
			}
			Output += TEXT("\n");
		}
	}

	return Output;
}

TArray<FChangelogEntry> ULesFightChangelogGenerator::GetChangelogHistory() const
{
	return ChangelogHistory;
}

bool ULesFightChangelogGenerator::ExportChangelog(const FString& FilePath)
{
	FString Content = GenerateChangelogText(ChangelogHistory);
	return FFileHelper::SaveStringToFile(Content, *FilePath);
}
