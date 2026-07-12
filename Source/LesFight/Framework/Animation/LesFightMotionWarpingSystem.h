#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightMotionWarpingSystem.generated.h"

class ULesFightCharacterAnimationComponent;

USTRUCT(BlueprintType)
struct FWarpRequest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FMotionWarpTargetData TargetData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WarpStartTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WarpEndTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WarpProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bComplete;

    FWarpRequest()
        : WarpStartTime(0.0f), WarpEndTime(1.0f)
        , WarpProgress(0.0f)
        , bActive(false), bComplete(false)
    {}
};

UCLASS(Blueprintable)
class ULesFightMotionWarpingSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMotionWarpingSystem();

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent);

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void SetWarpTarget(const FMotionWarpTargetData& Target);

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void ClearWarpTarget(FName TargetName);

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void ClearAllWarpTargets();

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void SetWarpEnabled(bool bEnable) { bWarpEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void SetWarpSpeed(float Speed) { WarpSpeed = Speed; }

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void WarpToTarget(const FMotionWarpTargetData& Target, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Motion Warping")
    void CancelActiveWarp();

    UFUNCTION(BlueprintPure, Category = "Motion Warping")
    bool IsWarping() const;

    UFUNCTION(BlueprintPure, Category = "Motion Warping")
    bool HasWarpTarget(FName TargetName) const;

    UFUNCTION(BlueprintPure, Category = "Motion Warping")
    FVector GetWarpTargetLocation(FName TargetName) const;

    UFUNCTION(BlueprintPure, Category = "Motion Warping")
    TArray<FWarpRequest> GetActiveWarps() const { return ActiveWarps; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Motion Warping")
    TArray<FWarpRequest> ActiveWarps;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion Warping")
    float WarpSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion Warping")
    float MaxWarpDistance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion Warping")
    float MaxWarpAngle;

    UPROPERTY(BlueprintReadOnly, Category = "Motion Warping")
    bool bWarpEnabled;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;

    void ApplyWarp(FWarpRequest& Warp);
    FVector CalculateWarpPosition(const FWarpRequest& Warp) const;
    FRotator CalculateWarpRotation(const FWarpRequest& Warp) const;
};
