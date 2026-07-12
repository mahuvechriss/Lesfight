#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightNotificationManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotificationShown, const FNotificationDef&, Notification);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotificationHidden, const FNotificationDef&, Notification);

UCLASS(Blueprintable)
class ULesFightNotificationManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void Shutdown();

	UFUNCTION(BlueprintCallable)
	void ShowNotification(const FNotificationDef& Notification);

	UFUNCTION(BlueprintCallable)
	void QueueNotification(const FNotificationDef& Notification);

	UFUNCTION(BlueprintCallable)
	void HideCurrentNotification();

	UFUNCTION(BlueprintCallable)
	void ClearQueue();

	UFUNCTION(BlueprintCallable)
	const FNotificationDef* GetCurrentNotification() const { return CurrentNotification.IsSet() ? &CurrentNotification.GetValue() : nullptr; }

	UFUNCTION(BlueprintCallable)
	const TArray<FNotificationDef>& GetNotificationQueue() const { return NotificationQueue; }

	UFUNCTION(BlueprintCallable)
	bool IsNotificationActive() const { return CurrentNotification.IsSet(); }

	UFUNCTION(BlueprintCallable)
	void SetNotificationDurationOverride(float Duration) { DefaultDuration = Duration; }

	UPROPERTY(BlueprintAssignable)
	FOnNotificationShown OnNotificationShown;

	UPROPERTY(BlueprintAssignable)
	FOnNotificationHidden OnNotificationHidden;

	UFUNCTION(BlueprintCallable)
	void Tick(float DeltaTime);

protected:
	TOptional<FNotificationDef> CurrentNotification;

	UPROPERTY()
	TArray<FNotificationDef> NotificationQueue;

	UPROPERTY()
	float Timer = 0.0f;

	UPROPERTY()
	float DefaultDuration = 3.0f;

	UPROPERTY()
	int32 MaxConcurrent = 1;
};
