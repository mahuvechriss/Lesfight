#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "Components/InputComponent.h"
#include "LesFightInputNavigationManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputAction, FName, ActionName);

UCLASS(Blueprintable)
class ULesFightInputNavigationManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void Shutdown();

	UFUNCTION(BlueprintCallable)
	void BindAction(FName ActionName, FKey Key, EInputDeviceType DeviceType);

	UFUNCTION(BlueprintCallable)
	void UnbindAction(FName ActionName);

	UFUNCTION(BlueprintCallable)
	void ProcessInput(FKey Key, EInputEvent InputEvent);

	UFUNCTION(BlueprintCallable)
	bool SupportsAction(FName ActionName) const;

	UFUNCTION(BlueprintCallable)
	void SetInputDevice(EInputDeviceType Device) { ActiveDevice = Device; }

	UFUNCTION(BlueprintCallable)
	EInputDeviceType GetInputDevice() const { return ActiveDevice; }

	UFUNCTION(BlueprintCallable)
	bool IsInputAllowed() const { return bInputAllowed; }

	UFUNCTION(BlueprintCallable)
	void SetInputAllowed(bool bAllowed) { bInputAllowed = bAllowed; }

	UPROPERTY(BlueprintAssignable)
	FOnInputAction OnInputAction;

	UFUNCTION(BlueprintCallable)
	TArray<FUINavigationAction> GetBoundActions() const;

protected:
	UPROPERTY()
	TMap<FKey, FUINavigationAction> KeyBindings;

	UPROPERTY()
	TMap<EInputDeviceType, TArray<FUINavigationAction>> DeviceBindings;

	UPROPERTY()
	EInputDeviceType ActiveDevice = EInputDeviceType::Keyboard;

	UPROPERTY()
	bool bInputAllowed = true;
};
