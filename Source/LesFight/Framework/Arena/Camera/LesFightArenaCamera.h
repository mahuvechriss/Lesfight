#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaCamera.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraBehaviorChanged, ECameraBehavior, NewBehavior);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightArenaCamera : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    void SetCameraBehavior(ECameraBehavior Behavior);

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    void PlayIntroSequence();

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    void PlayFinisherCamera(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    void UpdateCombatCamera(FVector Fighter1Pos, FVector Fighter2Pos, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    void SetArenaBounds(FVector Bounds);

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    ECameraBehavior GetCurrentBehavior() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    FVector GetCameraTarget() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    void SetCameraCollisionEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Arena|Camera")
    void ResetCamera();

    UPROPERTY(BlueprintAssignable, Category = "Arena|Camera")
    FOnCameraBehaviorChanged OnCameraBehaviorChanged;

protected:
    UPROPERTY()
    ECameraBehavior CurrentBehavior;

    UPROPERTY()
    FVector CameraTarget;

    UPROPERTY()
    FVector ArenaBounds;

    UPROPERTY()
    float CameraDistance = 400.0f;

    UPROPERTY()
    float CameraHeight = 150.0f;

    UPROPERTY()
    float CameraSmoothSpeed = 5.0f;

    UPROPERTY()
    bool bCollisionEnabled = true;

    UPROPERTY()
    TMap<ECameraBehavior, FVector> CameraOffsets;

private:
    TWeakObjectPtr<class ULesFightArenaWorldManager> OwnerManager;
};
