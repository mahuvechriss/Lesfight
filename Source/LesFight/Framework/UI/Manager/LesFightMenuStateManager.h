#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightMenuStateManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMenuStateChanged, EUIMenuState, OldState, EUIMenuState, NewState);

UCLASS(Blueprintable)
class ULesFightMenuStateManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void Shutdown();

	UFUNCTION(BlueprintCallable)
	void SetState(EUIMenuState NewState);

	UFUNCTION(BlueprintCallable)
	EUIMenuState GetState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable)
	EUIMenuState GetPreviousState() const { return PreviousState; }

	UFUNCTION(BlueprintCallable)
	bool CanTransitionTo(EUIMenuState TargetState) const;

	UFUNCTION(BlueprintCallable)
	bool IsStateValid(EUIMenuState State) const;

	UPROPERTY(BlueprintAssignable)
	FOnMenuStateChanged OnMenuStateChanged;

	UFUNCTION(BlueprintCallable)
	TArray<EUIMenuState> GetAvailableStates() const;

protected:
	UPROPERTY()
	EUIMenuState CurrentState = EUIMenuState::MainMenu;

	UPROPERTY()
	EUIMenuState PreviousState = EUIMenuState::MainMenu;

	UPROPERTY()
	TMap<EUIMenuState, TArray<EUIMenuState>> ValidTransitions;
};
