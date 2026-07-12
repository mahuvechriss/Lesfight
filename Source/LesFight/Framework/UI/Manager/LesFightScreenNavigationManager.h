#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "LesFightScreenNavigationManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScreenChanged, FName, OldScreen, FName, NewScreen);

UCLASS(Blueprintable)
class ULesFightScreenNavigationManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void Shutdown();

	UFUNCTION(BlueprintCallable)
	void NavigateTo(FName ScreenID, EScreenTransitionType TransitionType, float TransitionDuration);

	UFUNCTION(BlueprintCallable)
	void GoBack();

	UFUNCTION(BlueprintCallable)
	FName GetCurrentScreen() const { return CurrentScreen; }

	UFUNCTION(BlueprintCallable)
	FName GetPreviousScreen() const { return PreviousScreen; }

	UFUNCTION(BlueprintCallable)
	const TArray<FName>& GetNavigationHistory() const { return NavigationHistory; }

	UFUNCTION(BlueprintCallable)
	void ClearHistory();

	UFUNCTION(BlueprintCallable)
	bool IsNavigationInProgress() const { return bNavigationInProgress; }

	UPROPERTY(BlueprintAssignable)
	FOnScreenChanged OnScreenChanged;

	UFUNCTION(BlueprintCallable)
	void SetTransition(EScreenTransitionType Type, float Duration);

protected:
	UPROPERTY()
	TArray<FName> NavigationHistory;

	UPROPERTY()
	FName PreviousScreen;

	UPROPERTY()
	FName CurrentScreen;

	UPROPERTY()
	bool bNavigationInProgress = false;

	UPROPERTY()
	EScreenTransitionType CurrentTransition = EScreenTransitionType::Fade;

	UPROPERTY()
	float TransitionDuration = 0.5f;
};
