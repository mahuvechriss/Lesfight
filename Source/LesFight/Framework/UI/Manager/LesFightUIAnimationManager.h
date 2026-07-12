#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/UI/Data/LesFightUIData.h"
#include "Blueprint/UserWidget.h"
#include "LesFightUIAnimationManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimationStarted, FName, AnimationID, UUserWidget*, TargetWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnimationCompleted, FName, AnimationID, UUserWidget*, TargetWidget);

UCLASS(Blueprintable)
class ULesFightUIAnimationManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void Shutdown();

	UFUNCTION(BlueprintCallable)
	void PlayAnimation(FName AnimationID, UUserWidget* TargetWidget);

	UFUNCTION(BlueprintCallable)
	void StopAnimation(FName AnimationID, UUserWidget* TargetWidget);

	UFUNCTION(BlueprintCallable)
	void StopAllAnimations(UUserWidget* TargetWidget);

	UFUNCTION(BlueprintCallable)
	bool IsAnimating(UUserWidget* TargetWidget) const;

	UFUNCTION(BlueprintCallable)
	void RegisterAnimation(FName AnimationID, const FUIAnimationDef& Definition);

	UFUNCTION(BlueprintCallable)
	void UnregisterAnimation(FName AnimationID);

	UFUNCTION(BlueprintCallable)
	const FUIAnimationDef* GetAnimationDef(FName AnimationID) const;

	UFUNCTION(BlueprintCallable)
	void SetGlobalSpeedMultiplier(float Multiplier) { GlobalSpeedMultiplier = FMath::Max(0.01f, Multiplier); }

	UFUNCTION(BlueprintCallable)
	float GetGlobalSpeedMultiplier() const { return GlobalSpeedMultiplier; }

	UFUNCTION(BlueprintCallable)
	void Tick(float DeltaTime);

	UPROPERTY(BlueprintAssignable)
	FOnAnimationStarted OnAnimationStarted;

	UPROPERTY(BlueprintAssignable)
	FOnAnimationCompleted OnAnimationCompleted;

protected:
	UPROPERTY()
	TMap<FName, FUIAnimationDef> AnimationDefinitions;

	UPROPERTY()
	TMap<TObjectPtr<UUserWidget>, TArray<FName>> ActiveAnimations;

	UPROPERTY()
	TMap<FName, float> AnimationTimers;

	UPROPERTY()
	float GlobalSpeedMultiplier = 1.0f;
};
