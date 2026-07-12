#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightSlowMotionSystem.generated.h"

class ULesFightVFXWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlowMotionStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlowMotionEnd);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightSlowMotionSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void TriggerSlowMotion(ECinematicVFXEvent Event);

    UFUNCTION(BlueprintCallable)
    void BeginSlowMotion(float Dilation, float InEnterDuration, float InHoldDuration, float InExitDuration);

    UFUNCTION(BlueprintCallable)
    void EndSlowMotion();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsSlowMotionActive() const;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetCurrentDilation() const;

    UFUNCTION(BlueprintCallable)
    void SetSlowMotionPriority(int32 NewPriority);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetSlowMotionProgress() const;

    UPROPERTY(BlueprintAssignable)
    FOnSlowMotionStart OnSlowMotionStart;

    UPROPERTY(BlueprintAssignable)
    FOnSlowMotionEnd OnSlowMotionEnd;

protected:
    UPROPERTY()
    bool bSlowMotionActive = false;

    UPROPERTY()
    float CurrentDilation = 1.0f;

    UPROPERTY()
    float EnterDuration = 0.0f;

    UPROPERTY()
    float HoldDuration = 0.0f;

    UPROPERTY()
    float ExitDuration = 0.0f;

    UPROPERTY()
    float ElapsedTime = 0.0f;

    UPROPERTY()
    int32 Priority = 0;

    UPROPERTY()
    bool bExiting = false;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;

public:
    void Initialize(ULesFightVFXWorldManager* InManager);
    void TickSlowMotion(float DeltaTime);
};
