#include "LesFightLogManager.h"
#include "LesFight.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"

ELoggingLevel ULesFightLogManager::CurrentLogLevel = ELoggingLevel::Info;
bool ULesFightLogManager::bFileLoggingEnabled = false;
FString ULesFightLogManager::LogFilePath = TEXT("LesFight.log");
TArray<FString> ULesFightLogManager::LogBuffer;

ULesFightLogManager::ULesFightLogManager()
{
}

void ULesFightLogManager::Log(const FString& Message, ELoggingLevel Level)
{
    if (Level < CurrentLogLevel) return;

    FString LevelStr;
    switch (Level)
    {
    case ELoggingLevel::Debug:   LevelStr = TEXT("DEBUG");   break;
    case ELoggingLevel::Verbose: LevelStr = TEXT("VERBOSE"); break;
    case ELoggingLevel::Info:    LevelStr = TEXT("INFO");    break;
    case ELoggingLevel::Warning: LevelStr = TEXT("WARN");    break;
    case ELoggingLevel::Error:   LevelStr = TEXT("ERROR");   break;
    case ELoggingLevel::Fatal:   LevelStr = TEXT("FATAL");   break;
    }

    FString FormattedMessage = FString::Printf(TEXT("[%s] %s"), *LevelStr, *Message);

    switch (Level)
    {
    case ELoggingLevel::Warning:
        UE_LOG(LogLesFight, Warning, TEXT("%s"), *Message);
        break;
    case ELoggingLevel::Error:
    case ELoggingLevel::Fatal:
        UE_LOG(LogLesFight, Error, TEXT("%s"), *Message);
        break;
    default:
        UE_LOG(LogLesFight, Log, TEXT("%s"), *Message);
        break;
    }

    if (bFileLoggingEnabled)
    {
        LogBuffer.Add(FormattedMessage);
        if (LogBuffer.Num() >= 100)
        {
            FlushLogs();
        }
    }
}

void ULesFightLogManager::LogDebug(const FString& Message)
{
    Log(Message, ELoggingLevel::Debug);
}

void ULesFightLogManager::LogWarning(const FString& Message)
{
    Log(Message, ELoggingLevel::Warning);
}

void ULesFightLogManager::LogError(const FString& Message)
{
    Log(Message, ELoggingLevel::Error);
}

void ULesFightLogManager::SetLoggingLevel(ELoggingLevel NewLevel)
{
    CurrentLogLevel = NewLevel;
}

void ULesFightLogManager::EnableFileLogging(bool bEnable)
{
    bFileLoggingEnabled = bEnable;
}

void ULesFightLogManager::SetLogFilePath(const FString& FilePath)
{
    LogFilePath = FilePath;
}

void ULesFightLogManager::FlushLogs()
{
    if (bFileLoggingEnabled && LogBuffer.Num() > 0)
    {
        FFileHelper::SaveStringToFile(
            FString::Join(LogBuffer, TEXT("\n")),
            *LogFilePath,
            FFileHelper::EEncodingOptions::AutoDetect,
            &IFileManager::Get(),
            FILEWRITE_Append
        );
        LogBuffer.Empty();
    }
}
