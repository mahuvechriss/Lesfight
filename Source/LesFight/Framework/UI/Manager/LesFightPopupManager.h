#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightPopupManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPopupShown, const FPopupRequest&, Popup);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPopupHidden, const FPopupRequest&, Popup);

UCLASS(Blueprintable)
class ULesFightPopupManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void Shutdown();

	UFUNCTION(BlueprintCallable)
	void ShowPopup(const FPopupRequest& Request);

	UFUNCTION(BlueprintCallable)
	void CloseCurrentPopup();

	UFUNCTION(BlueprintCallable)
	const FPopupRequest* GetCurrentPopup() const;

	UFUNCTION(BlueprintCallable)
	bool IsPopupActive() const { return bPopupActive; }

	UFUNCTION(BlueprintCallable)
	void SetPopupQueueEnabled(bool bEnabled) { bQueueEnabled = bEnabled; }

	UPROPERTY(BlueprintAssignable)
	FOnPopupShown OnPopupShown;

	UPROPERTY(BlueprintAssignable)
	FOnPopupHidden OnPopupHidden;

	UFUNCTION(BlueprintCallable)
	const TArray<FPopupRequest>& GetPopupQueue() const { return PopupQueue; }

protected:
	UPROPERTY()
	TArray<FPopupRequest> PopupQueue;

	TOptional<FPopupRequest> CurrentPopup;

	UPROPERTY()
	bool bPopupActive = false;

	UPROPERTY()
	bool bQueueEnabled = true;

	UPROPERTY()
	int32 MaxQueueSize = 5;
};
