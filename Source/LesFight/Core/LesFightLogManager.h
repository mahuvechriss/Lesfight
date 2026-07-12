#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightLogManager.generated.h"

UENUM(BlueprintType)
enum class ELoggingLevel : uint8
{
    Debug,
    Verbose,
    Info,
    Warning,
    Error,
    Fatal
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLogMessage, const FString&, Message, ELoggingLevel, Level);

UCLASS(Blueprintable, Config = Game)
class ULesFightLogManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightLogManager();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    static void Log(const FString& Message, ELoggingLevel Level = ELoggingLevel::Info);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    static void LogDebug(const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    static void LogWarning(const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    static void LogError(const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    void SetLoggingLevel(ELoggingLevel NewLevel);

    UFUNCTION(BlueprintPure, Category = "LesFight|Logging")
    ELoggingLevel GetLoggingLevel() const { return CurrentLogLevel; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    void EnableFileLogging(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    void SetLogFilePath(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Logging")
    void FlushLogs();

protected:
    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnLogMessage OnLogMessage;

private:
    static ELoggingLevel CurrentLogLevel;
    static bool bFileLoggingEnabled;
    static FString LogFilePath;
    static TArray<FString> LogBuffer;
};
