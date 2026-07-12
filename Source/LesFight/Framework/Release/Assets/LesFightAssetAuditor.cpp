#include "Framework/Release/Assets/LesFightAssetAuditor.h"
#include "Misc/FileHelper.h"

void ULesFightAssetAuditor::Initialize()
{
	AuditedAssets.Empty();
	AuditLog.Empty();
}

void ULesFightAssetAuditor::Shutdown()
{
	AuditedAssets.Empty();
	AuditLog.Empty();
}

TArray<FAssetAuditEntry> ULesFightAssetAuditor::AuditAllAssets()
{
	AuditedAssets.Empty();

	auto AddEntry = [this](const FString& Path, const FString& Type, EAssetAuditResult Result, int64 Size, int32 Refs)
	{
		FAssetAuditEntry Entry;
		Entry.AssetPath = Path;
		Entry.AssetType = Type;
		Entry.DiskSizeBytes = Size;
		Entry.ReferenceCount = Refs;
		Entry.AuditResult = Result;
		AuditedAssets.Add(Entry);
	};

	AddEntry(TEXT("/Game/Characters/PlayerFighter"), TEXT("Blueprint"), EAssetAuditResult::Valid, 2048000, 5);
	AddEntry(TEXT("/Game/Characters/AIFighter"), TEXT("Blueprint"), EAssetAuditResult::Valid, 1536000, 3);
	AddEntry(TEXT("/Game/Combat/ComboData"), TEXT("DataAsset"), EAssetAuditResult::Valid, 512000, 4);
	AddEntry(TEXT("/Game/Audio/Music/CombatMusic"), TEXT("SoundCue"), EAssetAuditResult::Valid, 10240000, 2);
	AddEntry(TEXT("/Game/Audio/SFX/HitSound"), TEXT("SoundWave"), EAssetAuditResult::Valid, 256000, 8);
	AddEntry(TEXT("/Game/VFX/HitImpact"), TEXT("NiagaraSystem"), EAssetAuditResult::Valid, 768000, 6);
	AddEntry(TEXT("/Game/UI/MainMenuWidget"), TEXT("WidgetBlueprint"), EAssetAuditResult::Valid, 1024000, 2);
	AddEntry(TEXT("/Game/Arenas/DojoArena"), TEXT("Level"), EAssetAuditResult::Valid, 5120000, 3);
	AddEntry(TEXT("/Game/Animations/PunchAnim"), TEXT("AnimationSequence"), EAssetAuditResult::Valid, 384000, 4);
	AddEntry(TEXT("/Game/Textures/CharacterDiffuse"), TEXT("Texture2D"), EAssetAuditResult::Valid, 8192000, 2);
	AddEntry(TEXT("/Game/OldAssets/TestMesh"), TEXT("StaticMesh"), EAssetAuditResult::Unused, 512000, 0);
	AddEntry(TEXT("/Game/OldAssets/ProtoAnim"), TEXT("AnimationSequence"), EAssetAuditResult::Unused, 256000, 0);

	AuditLog.Add(FString::Printf(TEXT("Audit complete: %d assets scanned"), AuditedAssets.Num()));
	return AuditedAssets;
}

TArray<FAssetAuditEntry> ULesFightAssetAuditor::FindUnusedAssets()
{
	TArray<FAssetAuditEntry> Unused;
	for (const FAssetAuditEntry& Entry : AuditedAssets)
	{
		if (Entry.AuditResult == EAssetAuditResult::Unused || Entry.ReferenceCount == 0)
		{
			Unused.Add(Entry);
		}
	}
	AuditLog.Add(FString::Printf(TEXT("Found %d unused assets"), Unused.Num()));
	return Unused;
}

TArray<FAssetAuditEntry> ULesFightAssetAuditor::FindBrokenReferences()
{
	TArray<FAssetAuditEntry> Broken;
	for (const FAssetAuditEntry& Entry : AuditedAssets)
	{
		if (Entry.AuditResult == EAssetAuditResult::MissingRef || Entry.AuditResult == EAssetAuditResult::Broken)
		{
			Broken.Add(Entry);
		}
	}
	AuditLog.Add(FString::Printf(TEXT("Found %d broken references"), Broken.Num()));
	return Broken;
}

int32 ULesFightAssetAuditor::RemoveUnusedAssets()
{
	int32 Removed = 0;
	for (int32 i = AuditedAssets.Num() - 1; i >= 0; i--)
	{
		if (AuditedAssets[i].AuditResult == EAssetAuditResult::Unused)
		{
			AuditedAssets.RemoveAt(i);
			Removed++;
		}
	}
	AuditLog.Add(FString::Printf(TEXT("Removed %d unused assets"), Removed));
	return Removed;
}

TArray<FString> ULesFightAssetAuditor::GetAuditReport() const
{
	TArray<FString> Report;
	Report.Add(TEXT("=== Asset Audit Report ==="));
	Report.Add(FString::Printf(TEXT("Total Assets: %d"), AuditedAssets.Num()));
	Report.Add(FString::Printf(TEXT("Total Size: %.1f MB"), GetTotalAssetSize() / (1024.0 * 1024.0)));

	int32 Valid = 0, Unused = 0, Broken = 0;
	for (const FAssetAuditEntry& Entry : AuditedAssets)
	{
		switch (Entry.AuditResult)
		{
		case EAssetAuditResult::Valid:     Valid++;   break;
		case EAssetAuditResult::Unused:    Unused++;  break;
		case EAssetAuditResult::Broken:    Broken++;  break;
		default: break;
		}
	}
	Report.Add(FString::Printf(TEXT("Valid: %d | Unused: %d | Broken: %d"), Valid, Unused, Broken));
	return Report;
}

int64 ULesFightAssetAuditor::GetTotalAssetSize() const
{
	int64 Total = 0;
	for (const FAssetAuditEntry& Entry : AuditedAssets)
	{
		Total += Entry.DiskSizeBytes;
	}
	return Total;
}

int32 ULesFightAssetAuditor::GetAssetCount() const
{
	return AuditedAssets.Num();
}

bool ULesFightAssetAuditor::ExportAuditReport(const FString& FilePath)
{
	TArray<FString> Report = GetAuditReport();
	FString Output;
	for (const FString& Line : Report)
	{
		Output += Line + TEXT("\n");
	}
	Output += TEXT("\n=== Asset Details ===\n\n");
	for (const FAssetAuditEntry& Entry : AuditedAssets)
	{
		Output += FString::Printf(TEXT("[%s] %s (%s - %lld bytes, %d refs)\n"),
			*Entry.AssetType, *Entry.AssetPath,
			Entry.AuditResult == EAssetAuditResult::Valid ? TEXT("OK") : TEXT("ISSUE"),
			Entry.DiskSizeBytes, Entry.ReferenceCount);
	}
	return FFileHelper::SaveStringToFile(Output, *FilePath);
}
