#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightAnimationCameraSync.generated.h"

class ULesFightCharacterAnimationComponent;
class UCameraComponent;

USTRUCT(BlueprintType)
struct FCameraAnimSyncData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FieldOfView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector CameraOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator CameraRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseDynamicZoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ZoomDistance;

    FCameraAnimSyncData()
        : EventName(NAME_None), FieldOfView(90.0f)
        , CameraOffset(FVector::ZeroVector)
        , CameraRotation(FRotator::ZeroRotator)
        , BlendSpeed(5.0f), Duration(0.5f)
        , bUseDynamicZoom(false), ZoomDistance(0.0f)
    {}
};

UCLASS(Blueprintable)
class ULesFightAnimationCameraSync : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAnimationCameraSync();

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent);

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void TriggerCombatZoom(float Distance = 200.0f, float Duration = 0.5f);

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void TriggerImpactZoom(float Intensity = 1.0f);

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void TriggerCinematicCamera(const FCameraAnimSyncData& CameraData);

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void ResetToDefaultCamera(float BlendTime = 0.5f);

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void SetCameraShakeEnabled(bool bEnable) { bCameraShakeEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Camera Sync")
    void SetDynamicZoomEnabled(bool bEnable) { bDynamicZoomEnabled = bEnable; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Camera Sync")
    FCameraAnimSyncData CurrentCameraData;

    UPROPERTY(BlueprintReadOnly, Category = "Camera Sync")
    FCameraAnimSyncData DefaultCameraData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Sync")
    float CombatZoomSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera Sync")
    float ImpactZoomIntensity;

    UPROPERTY(BlueprintReadOnly, Category = "Camera Sync")
    bool bCameraShakeEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "Camera Sync")
    bool bDynamicZoomEnabled;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<UCameraComponent> CameraComponent;
    float CurrentZoom;
    float TargetZoom;
    float ZoomTimer;
};
