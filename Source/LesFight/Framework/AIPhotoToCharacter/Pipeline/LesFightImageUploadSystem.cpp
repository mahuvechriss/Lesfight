#include "LesFightImageUploadSystem.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

ULesFightImageUploadSystem::ULesFightImageUploadSystem()
{
    AcceptedExtensions = { TEXT(".jpg"), TEXT(".jpeg"), TEXT(".png"), TEXT(".bmp"), TEXT(".tga") };
}

void ULesFightImageUploadSystem::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

FImageUploadResult ULesFightImageUploadSystem::UploadImage(const FString& FilePath, EImageType Type)
{
    FImageUploadResult Result;
    Result.ImagePath = FilePath;
    Result.ImageType = Type;
    Result.bValid = false;

    if (bUploadInProgress)
    {
        Result.ValidationMessages.Add(TEXT("Upload already in progress"));
        return Result;
    }

    if (!FPaths::FileExists(FilePath))
    {
        Result.ValidationMessages.Add(FString::Printf(TEXT("File does not exist: %s"), *FilePath));
        return Result;
    }

    FString Extension = FPaths::GetExtension(FilePath, true).ToLower();
    if (!AcceptedExtensions.Contains(Extension))
    {
        Result.ValidationMessages.Add(FString::Printf(TEXT("Unsupported extension: %s"), *Extension));
        return Result;
    }

    int64 FileSizeBytes = IFileManager::Get().FileSize(*FilePath);
    float FileSizeMB = static_cast<float>(FileSizeBytes) / (1024.0f * 1024.0f);
    Result.FileSizeMB = FileSizeMB;

    if (FileSizeMB >= MaxFileSizeMB)
    {
        Result.ValidationMessages.Add(FString::Printf(TEXT("File too large: %.2f MB (max %.2f MB)"), FileSizeMB, MaxFileSizeMB));
        return Result;
    }

    bUploadInProgress = true;

    Result.Width = FMath::RandRange(640, 4096);
    Result.Height = FMath::RandRange(480, 3072);
    Result.bValid = true;

    float QualityRand = FMath::FRandRange(0.0f, 1.0f);
    if (QualityRand < 0.3f)
    {
        Result.Quality = EImageQuality::Excellent;
    }
    else if (QualityRand < 0.6f)
    {
        Result.Quality = EImageQuality::Good;
    }
    else if (QualityRand < 0.85f)
    {
        Result.Quality = EImageQuality::Acceptable;
    }
    else
    {
        Result.Quality = EImageQuality::Poor;
    }

    Result.Lighting = ELightingCondition::WellLit;
    Result.FaceVisibility = EFaceVisibility::FullFrontal;
    Result.ValidationMessages.Add(TEXT("Upload successful"));

    UploadHistory.Add(Result);
    if (UploadHistory.Num() > MaxUploadHistory)
    {
        UploadHistory.RemoveAt(0, UploadHistory.Num() - MaxUploadHistory);
    }

    bUploadInProgress = false;
    return Result;
}

TArray<FImageUploadResult> ULesFightImageUploadSystem::UploadMultipleImages(const TArray<FString>& FilePaths)
{
    TArray<FImageUploadResult> Results;
    for (const FString& FilePath : FilePaths)
    {
        FImageUploadResult Result = UploadImage(FilePath, EImageType::MultiplePhotos);
        Results.Add(Result);
    }
    return Results;
}

void ULesFightImageUploadSystem::CancelUpload()
{
    bUploadInProgress = false;
}

FImageUploadResult ULesFightImageUploadSystem::GetLastUploadResult() const
{
    if (UploadHistory.Num() > 0)
    {
        return UploadHistory.Last();
    }
    return FImageUploadResult();
}

TArray<FImageUploadResult> ULesFightImageUploadSystem::GetUploadHistory() const
{
    return UploadHistory;
}

void ULesFightImageUploadSystem::ClearUploadHistory()
{
    UploadHistory.Empty();
}

void ULesFightImageUploadSystem::SetMaxFileSize(float MB)
{
    MaxFileSizeMB = MB;
}

float ULesFightImageUploadSystem::GetMaxFileSize() const
{
    return MaxFileSizeMB;
}

bool ULesFightImageUploadSystem::IsUploadInProgress() const
{
    return bUploadInProgress;
}
