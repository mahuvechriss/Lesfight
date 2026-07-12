#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightRootMotionHandler.generated.h"

class ULesFightCharacterAnimationComponent;
class UCharacterMovementComponent;

USTRUCT(BlueprintType)
struct FRootMotionParams
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableRootMotion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ERootMotionMode RootMotionMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TranslationMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RotationMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIgnoreTranslation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIgnoreRotation;

    FRootMotionParams()
        : bEnableRootMotion(true)
        , RootMotionMode(ERootMotionMode::Full)
        , TranslationMultiplier(1.0f), RotationMultiplier(1.0f)
        , bIgnoreTranslation(false), bIgnoreRotation(false)
    {}
};

USTRUCT(BlueprintType)
struct FRootMotionSnapshot
{
    GENERATED_BODY()

    UPROPERTY()
    FTransform StartTransform;

    UPROPERTY()
    FTransform AccumulatedTransform;

    UPROPERTY()
    float TotalDistance;

    UPROPERTY()
    bool bActive;

    FRootMotionSnapshot()
        : StartTransform(FTransform::Identity)
        , AccumulatedTransform(FTransform::Identity)
        , TotalDistance(0.0f)
        , bActive(false)
    {}
};

UCLASS(Blueprintable)
class ULesFightRootMotionHandler : public UObject
{
    GENERATED_BODY()

public:
    ULesFightRootMotionHandler();

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void EnableRootMotion(bool bEnable);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void SetRootMotionMode(ERootMotionMode Mode);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void SetTranslationMultiplier(float Multiplier);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void SetRotationMultiplier(float Multiplier);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void SetRootMotionParams(const FRootMotionParams& Params);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    FRootMotionSnapshot CaptureSnapshot();

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void RestoreSnapshot(const FRootMotionSnapshot& Snapshot);

    UFUNCTION(BlueprintCallable, Category = "Root Motion")
    void ResetRootMotion();

    UFUNCTION(BlueprintPure, Category = "Root Motion")
    bool IsRootMotionEnabled() const { return bRootMotionEnabled; }

    UFUNCTION(BlueprintPure, Category = "Root Motion")
    FRootMotionParams GetCurrentParams() const { return CurrentParams; }

    UFUNCTION(BlueprintPure, Category = "Root Motion")
    FVector GetAccumulatedTranslation() const { return AccumulatedTranslation; }

    UFUNCTION(BlueprintPure, Category = "Root Motion")
    FRotator GetAccumulatedRotation() const { return AccumulatedRotation; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Root Motion")
    FRootMotionParams CurrentParams;

    UPROPERTY(BlueprintReadOnly, Category = "Root Motion")
    FVector AccumulatedTranslation;

    UPROPERTY(BlueprintReadOnly, Category = "Root Motion")
    FRotator AccumulatedRotation;

    UPROPERTY(BlueprintReadOnly, Category = "Root Motion")
    bool bRootMotionEnabled;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;
};
