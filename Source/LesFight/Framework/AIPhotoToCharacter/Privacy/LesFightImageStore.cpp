#include "LesFightImageStore.h"
#include "AI/LesFightAIPipelineManager.h"
#include "Misc/DateTime.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"
#include "Misc/Guid.h"

static constexpr int32 DefaultRetentionMinutes = 30;

ULesFightImageStore::ULesFightImageStore()
{
    StorageDirectory = FPaths::ProjectSavedDir() / TEXT("ImageStore");
}

void ULesFightImageStore::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.DirectoryExists(*StorageDirectory))
    {
        PlatformFile.CreateDirectoryTree(*StorageDirectory);
    }
}

bool ULesFightImageStore::StoreImage(const FString& SourcePath, FString& OutStoredPath)
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    if (!PlatformFile.FileExists(*SourcePath))
    {
        return false;
    }

    FString Extension = FPaths::GetExtension(SourcePath);
    FString GuidName = FGuid::NewGuid().ToString(EGuidFormats::Digits) + TEXT(".") + Extension;
    FString DestPath = StorageDirectory / GuidName;

    if (!PlatformFile.CopyFile(*DestPath, *SourcePath))
    {
        return false;
    }

    int64 FileSize = PlatformFile.FileSize(*DestPath);
    TotalSizeMB += FileSize / (1024.0f * 1024.0f);

    StoredImagePaths.Add(DestPath);
    ImageTimestamps.Add(DestPath, FDateTime::Now());
    OutStoredPath = DestPath;

    return true;
}

bool ULesFightImageStore::RetrieveImage(const FString& StoredPath, FString& OutPath)
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    if (!PlatformFile.FileExists(*StoredPath))
    {
        return false;
    }

    if (IsImageExpired(StoredPath))
    {
        return false;
    }

    OutPath = StoredPath;
    return true;
}

bool ULesFightImageStore::DeleteImage(const FString& StoredPath)
{
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    if (!PlatformFile.FileExists(*StoredPath))
    {
        StoredImagePaths.Remove(StoredPath);
        ImageTimestamps.Remove(StoredPath);
        return false;
    }

    int64 FileSize = PlatformFile.FileSize(*StoredPath);
    TotalSizeMB -= FileSize / (1024.0f * 1024.0f);

    PlatformFile.DeleteFile(*StoredPath);
    StoredImagePaths.Remove(StoredPath);
    ImageTimestamps.Remove(StoredPath);

    return true;
}

void ULesFightImageStore::DeleteAllImages()
{
    for (const FString& Path : StoredImagePaths)
    {
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        if (PlatformFile.FileExists(*Path))
        {
            PlatformFile.DeleteFile(*Path);
        }
    }

    StoredImagePaths.Empty();
    ImageTimestamps.Empty();
    TotalSizeMB = 0.0f;
}

int32 ULesFightImageStore::GetStoredImageCount() const
{
    return StoredImagePaths.Num();
}

float ULesFightImageStore::GetTotalStorageSizeMB() const
{
    return TotalSizeMB;
}

bool ULesFightImageStore::IsImageExpired(const FString& StoredPath) const
{
    const FDateTime* Timestamp = ImageTimestamps.Find(StoredPath);
    if (!Timestamp)
    {
        return true;
    }

    FDateTime ExpiryTime = *Timestamp + FTimespan::FromMinutes(DefaultRetentionMinutes);
    return FDateTime::Now() > ExpiryTime;
}

void ULesFightImageStore::CleanExpiredImages()
{
    TArray<FString> ExpiredPaths;
    for (const auto& Pair : ImageTimestamps)
    {
        FDateTime ExpiryTime = Pair.Value + FTimespan::FromMinutes(DefaultRetentionMinutes);
        if (FDateTime::Now() > ExpiryTime)
        {
            ExpiredPaths.Add(Pair.Key);
        }
    }

    for (const FString& Path : ExpiredPaths)
    {
        DeleteImage(Path);
    }
}

FString ULesFightImageStore::GetStorageDirectory() const
{
    return StorageDirectory;
}

void ULesFightImageStore::SetStorageDirectory(const FString& Dir)
{
    StorageDirectory = Dir;
}
