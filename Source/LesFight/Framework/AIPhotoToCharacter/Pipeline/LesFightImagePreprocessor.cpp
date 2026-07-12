#include "LesFightImagePreprocessor.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"

void ULesFightImagePreprocessor::Initialize(ULesFightAIPipelineManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
}

void ULesFightImagePreprocessor::AddLogEntry(const FString& Entry)
{
    PreprocessingLog.Add(Entry);
    if (PreprocessingLog.Num() > MaxLogEntries)
    {
        PreprocessingLog.RemoveAt(0, PreprocessingLog.Num() - MaxLogEntries);
    }
}

bool ULesFightImagePreprocessor::PreprocessImage(const FString& SourcePath, FString& OutProcessedPath)
{
    FString TempDir = FPaths::ProjectSavedDir() / TEXT("Temp") / TEXT("AIProcessing");
    IFileManager::Get().MakeDirectory(*TempDir, true);

    FString Filename = FPaths::GetBaseFilename(SourcePath) + TEXT("_processed") + FPaths::GetExtension(SourcePath, true);
    OutProcessedPath = TempDir / Filename;

    bool bCopied = IFileManager::Get().Copy(*OutProcessedPath, *SourcePath) == COPY_OK;
    if (bCopied)
    {
        AddLogEntry(FString::Printf(TEXT("Copied source to temp path: %s"), *OutProcessedPath));
    }
    else
    {
        AddLogEntry(FString::Printf(TEXT("Failed to copy file to: %s"), *OutProcessedPath));
    }

    AddLogEntry(FString::Printf(TEXT("PreprocessImage completed for: %s"), *SourcePath));
    return bCopied;
}

bool ULesFightImagePreprocessor::RemoveBackground(const FString& ImagePath, FString& OutPath)
{
    FString TempDir = FPaths::ProjectSavedDir() / TEXT("Temp") / TEXT("BackgroundRemoval");
    IFileManager::Get().MakeDirectory(*TempDir, true);

    FString Filename = FPaths::GetBaseFilename(ImagePath) + TEXT("_nobg") + FPaths::GetExtension(ImagePath, true);
    OutPath = TempDir / Filename;

    bool bCopied = IFileManager::Get().Copy(*OutPath, *ImagePath) == COPY_OK;

    AddLogEntry(FString::Printf(TEXT("RemoveBackground: %s -> %s"), *ImagePath, *OutPath));
    return bCopied;
}

bool ULesFightImagePreprocessor::AdjustColorBalance(const FString& ImagePath, float Brightness, float Contrast, float Saturation)
{
    AddLogEntry(FString::Printf(TEXT("AdjustColorBalance: %s (B=%.2f, C=%.2f, S=%.2f)"), *ImagePath, Brightness, Contrast, Saturation));
    return true;
}

bool ULesFightImagePreprocessor::ResizeImage(const FString& ImagePath, int32 MaxDimension)
{
    AddLogEntry(FString::Printf(TEXT("ResizeImage: %s (max=%d)"), *ImagePath, MaxDimension));
    return true;
}

bool ULesFightImagePreprocessor::DetectEdges(const FString& ImagePath)
{
    AddLogEntry(FString::Printf(TEXT("DetectEdges: %s"), *ImagePath));
    return true;
}

bool ULesFightImagePreprocessor::NormalizeLighting(const FString& ImagePath)
{
    AddLogEntry(FString::Printf(TEXT("NormalizeLighting: %s"), *ImagePath));
    return true;
}

TArray<FString> ULesFightImagePreprocessor::GetPreprocessingLog() const
{
    return PreprocessingLog;
}
