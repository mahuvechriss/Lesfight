#include "LesFightPrivacyManager.h"
#include "AI/LesFightAIManager.h"
#include "Misc/DateTime.h"

ULesFightPrivacyManager::ULesFightPrivacyManager()
{
    CurrentSettings.bUserConsentGiven = false;
    CurrentSettings.bAutoDeleteImages = true;
    CurrentSettings.bLocalProcessingOnly = true;
    CurrentSettings.ImageRetentionMinutes = 30;
    CurrentSettings.bAnonymizeData = true;
}

void ULesFightPrivacyManager::Initialize(ULesFightAIManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bPrivacyInitialized = true;
}

void ULesFightPrivacyManager::RequestUserConsent()
{
    CurrentSettings.bUserConsentGiven = true;
    CurrentSettings.ConsentTimestamp = FDateTime::Now();
    bPrivacyInitialized = true;
    LogPrivacyEvent(TEXT("User consent granted"));
}

bool ULesFightPrivacyManager::HasUserConsent() const
{
    return CurrentSettings.bUserConsentGiven;
}

void ULesFightPrivacyManager::RevokeConsent()
{
    CurrentSettings.bUserConsentGiven = false;
    PurgeAllUserData();
    LogPrivacyEvent(TEXT("User consent revoked"));
}

void ULesFightPrivacyManager::SetAutoDeleteImages(bool bAutoDelete)
{
    CurrentSettings.bAutoDeleteImages = bAutoDelete;
}

bool ULesFightPrivacyManager::GetAutoDeleteImages() const
{
    return CurrentSettings.bAutoDeleteImages;
}

void ULesFightPrivacyManager::SetRetentionPeriod(int32 Minutes)
{
    CurrentSettings.ImageRetentionMinutes = Minutes;
}

int32 ULesFightPrivacyManager::GetRetentionPeriod() const
{
    return CurrentSettings.ImageRetentionMinutes;
}

void ULesFightPrivacyManager::SetLocalProcessingOnly(bool bLocalOnly)
{
    CurrentSettings.bLocalProcessingOnly = bLocalOnly;
}

bool ULesFightPrivacyManager::IsLocalProcessingOnly() const
{
    return CurrentSettings.bLocalProcessingOnly;
}

void ULesFightPrivacyManager::PurgeAllUserData()
{
    if (OwnerManager.IsValid())
    {
        OwnerManager->ClearAllStoredImages();
    }
    CurrentSettings = FPrivacySettings();
    CurrentSettings.bUserConsentGiven = false;
    CurrentSettings.bAutoDeleteImages = true;
    CurrentSettings.bLocalProcessingOnly = true;
    CurrentSettings.ImageRetentionMinutes = 30;
    CurrentSettings.bAnonymizeData = true;
    LogPrivacyEvent(TEXT("All user data purged"));
}

const FPrivacySettings& ULesFightPrivacyManager::GetPrivacySettings() const
{
    return CurrentSettings;
}

void ULesFightPrivacyManager::ApplyPrivacySettings(const FPrivacySettings& Settings)
{
    CurrentSettings = Settings;
    LogPrivacyEvent(TEXT("Privacy settings applied"));
}

void ULesFightPrivacyManager::LogPrivacyEvent(const FString& Event)
{
    FString TimestampedEvent = FDateTime::Now().ToString(TEXT("[%Y-%m-%d %H:%M:%S] ")) + Event;
    PrivacyEventLog.Add(TimestampedEvent);
    if (PrivacyEventLog.Num() > MaxLogEntries)
    {
        PrivacyEventLog.RemoveAt(0);
    }
}

TArray<FString> ULesFightPrivacyManager::GetPrivacyLog() const
{
    return PrivacyEventLog;
}

bool ULesFightPrivacyManager::IsDataAnonymized() const
{
    return CurrentSettings.bAnonymizeData;
}
