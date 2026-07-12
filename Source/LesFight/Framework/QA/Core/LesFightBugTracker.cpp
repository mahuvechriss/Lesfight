#include "Framework/QA/Core/LesFightBugTracker.h"
#include "Misc/FileHelper.h"

void ULesFightBugTracker::Initialize()
{
	BugDatabase.Empty();
	NextBugID = 1;
}

void ULesFightBugTracker::Shutdown()
{
	BugDatabase.Empty();
}

int32 ULesFightBugTracker::ReportBug(const FString& Title, const FText& Description, const FString& Area, EBugSeverity Severity, const TArray<FString>& StepsToReproduce)
{
	FQABugEntry Entry;
	Entry.BugID = NextBugID++;
	Entry.Title = Title;
	Entry.Description = Description;
	Entry.Area = Area;
	Entry.Severity = Severity;
	Entry.Status = EBugStatus::New;
	Entry.ReportedBy = TEXT("QA Tester");
	Entry.ReportDate = FDateTime::Now();
	Entry.StepsToReproduce = StepsToReproduce;

	BugDatabase.Add(Entry);
	OnBugReported.Broadcast(Entry);

	UE_LOG(LogTemp, Log, TEXT("[BugTracker] Bug #%d reported: %s (%s)"), Entry.BugID, *Title, *Area);
	return Entry.BugID;
}

bool ULesFightBugTracker::UpdateBugStatus(int32 BugID, EBugStatus NewStatus)
{
	for (FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.BugID == BugID)
		{
			Bug.Status = NewStatus;
			OnBugStatusChanged.Broadcast(Bug);
			UE_LOG(LogTemp, Log, TEXT("[BugTracker] Bug #%d status updated to %d"), BugID, static_cast<int32>(NewStatus));
			return true;
		}
	}
	return false;
}

bool ULesFightBugTracker::AssignBug(int32 BugID, const FString& Assignee)
{
	for (FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.BugID == BugID)
		{
			Bug.AssignedTo = Assignee;
			if (Bug.Status == EBugStatus::New)
			{
				Bug.Status = EBugStatus::Confirmed;
			}
			UE_LOG(LogTemp, Log, TEXT("[BugTracker] Bug #%d assigned to %s"), BugID, *Assignee);
			return true;
		}
	}
	return false;
}

FQABugEntry ULesFightBugTracker::GetBugByID(int32 BugID) const
{
	for (const FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.BugID == BugID)
		{
			return Bug;
		}
	}
	return FQABugEntry();
}

TArray<FQABugEntry> ULesFightBugTracker::GetAllBugs() const
{
	return BugDatabase;
}

TArray<FQABugEntry> ULesFightBugTracker::GetBugsByArea(const FString& Area) const
{
	TArray<FQABugEntry> Filtered;
	for (const FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.Area == Area)
		{
			Filtered.Add(Bug);
		}
	}
	return Filtered;
}

TArray<FQABugEntry> ULesFightBugTracker::GetBugsByStatus(EBugStatus Status) const
{
	TArray<FQABugEntry> Filtered;
	for (const FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.Status == Status)
		{
			Filtered.Add(Bug);
		}
	}
	return Filtered;
}

TArray<FQABugEntry> ULesFightBugTracker::GetBugsByAssignee(const FString& Assignee) const
{
	TArray<FQABugEntry> Filtered;
	for (const FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.AssignedTo == Assignee)
		{
			Filtered.Add(Bug);
		}
	}
	return Filtered;
}

TArray<FQABugEntry> ULesFightBugTracker::GetCriticalBugs() const
{
	TArray<FQABugEntry> Filtered;
	for (const FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.Severity == EBugSeverity::Critical)
		{
			Filtered.Add(Bug);
		}
	}
	return Filtered;
}

int32 ULesFightBugTracker::GetBugCount() const
{
	return BugDatabase.Num();
}

int32 ULesFightBugTracker::GetOpenBugCount() const
{
	int32 Count = 0;
	for (const FQABugEntry& Bug : BugDatabase)
	{
		if (Bug.Status != EBugStatus::Closed && Bug.Status != EBugStatus::WontFix)
		{
			Count++;
		}
	}
	return Count;
}

bool ULesFightBugTracker::ExportBugsToFile(const FString& FilePath)
{
	FString Output;
	Output += TEXT("LesFight Bug Report\n");
	Output += TEXT("==================\n\n");

	for (const FQABugEntry& Bug : BugDatabase)
	{
		FString SeverityStr;
		switch (Bug.Severity)
		{
		case EBugSeverity::Critical:  SeverityStr = TEXT("CRITICAL"); break;
		case EBugSeverity::Major:     SeverityStr = TEXT("MAJOR");    break;
		case EBugSeverity::Minor:     SeverityStr = TEXT("MINOR");    break;
		case EBugSeverity::Cosmetic:  SeverityStr = TEXT("COSMETIC"); break;
		case EBugSeverity::Suggestion:SeverityStr = TEXT("SUGGESTION");break;
		}

		FString StatusStr;
		switch (Bug.Status)
		{
		case EBugStatus::New:		 StatusStr = TEXT("New");		break;
		case EBugStatus::Confirmed:	 StatusStr = TEXT("Confirmed");	break;
		case EBugStatus::InProgress: StatusStr = TEXT("In Progress");break;
		case EBugStatus::Fixed:		 StatusStr = TEXT("Fixed");		break;
		case EBugStatus::Verified:	 StatusStr = TEXT("Verified");	break;
		case EBugStatus::Closed:	 StatusStr = TEXT("Closed");	break;
		case EBugStatus::WontFix:	 StatusStr = TEXT("Won't Fix");	break;
		}

		Output += FString::Printf(TEXT("[#%d][%s][%s] %s\n"), Bug.BugID, *SeverityStr, *StatusStr, *Bug.Title);
		Output += FString::Printf(TEXT("  Area: %s | Reported: %s | Assigned: %s\n"), *Bug.Area, *Bug.ReportedBy, *Bug.AssignedTo);
		Output += TEXT("\n");
	}

	return FFileHelper::SaveStringToFile(Output, *FilePath);
}
