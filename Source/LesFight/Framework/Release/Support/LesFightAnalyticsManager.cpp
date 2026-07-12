#include "Framework/Release/Support/LesFightAnalyticsManager.h"

void ULesFightAnalyticsManager::Initialize()
{
	PendingEvents.Empty();
	bEnabled = false;
	bConsentGiven = false;
}

void ULesFightAnalyticsManager::Shutdown()
{
	PendingEvents.Empty();
}

void ULesFightAnalyticsManager::SetAnalyticsEnabled(bool bEnabled)
{
	this->bEnabled = bEnabled;
	UE_LOG(LogTemp, Log, TEXT("[Analytics] %s"), bEnabled ? TEXT("Enabled") : TEXT("Disabled"));
}

bool ULesFightAnalyticsManager::IsAnalyticsEnabled() const
{
	return bEnabled && bConsentGiven;
}

void ULesFightAnalyticsManager::RecordCrashReport(const FString& CrashData)
{
	if (!IsAnalyticsEnabled()) return;

	FAnalyticsEvent Event;
	Event.EventName = TEXT("crash_report");
	Event.Properties.Add(TEXT("data"), CrashData);
	Event.Timestamp = FDateTime::Now();
	PendingEvents.Add(Event);
}

void ULesFightAnalyticsManager::RecordPerformanceReport(float FPS, float FrameTime, float MemoryMB)
{
	if (!IsAnalyticsEnabled()) return;

	FAnalyticsEvent Event;
	Event.EventName = TEXT("performance_report");
	Event.Properties.Add(TEXT("fps"), FString::SanitizeFloat(FPS));
	Event.Properties.Add(TEXT("frametime"), FString::SanitizeFloat(FrameTime));
	Event.Properties.Add(TEXT("memory_mb"), FString::SanitizeFloat(MemoryMB));
	Event.Timestamp = FDateTime::Now();
	PendingEvents.Add(Event);
}

void ULesFightAnalyticsManager::RecordGameplayEvent(const FString& EventName, const TMap<FString, FString>& Properties)
{
	if (!IsAnalyticsEnabled()) return;

	FAnalyticsEvent Event;
	Event.EventName = EventName;
	Event.Properties = Properties;
	Event.Timestamp = FDateTime::Now();
	PendingEvents.Add(Event);
}

TArray<FAnalyticsEvent> ULesFightAnalyticsManager::GetPendingEvents() const
{
	return PendingEvents;
}

int32 ULesFightAnalyticsManager::FlushEvents()
{
	int32 Count = PendingEvents.Num();
	PendingEvents.Empty();
	UE_LOG(LogTemp, Log, TEXT("[Analytics] Flushed %d events"), Count);
	return Count;
}

void ULesFightAnalyticsManager::RequestConsent()
{
	bConsentGiven = false;
	UE_LOG(LogTemp, Log, TEXT("[Analytics] Consent requested - awaiting player response"));
}

bool ULesFightAnalyticsManager::HasConsent() const
{
	return bConsentGiven;
}
