#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LesFightFollowCameraComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ALesFightPlayerCharacter;

USTRUCT(BlueprintType)
struct FCameraFollowSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TargetArmLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraLagSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraRotationLagSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraLagMaxDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SocketOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FieldOfView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraCollisionRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnableCameraLag;

    FCameraFollowSettings()
        : TargetArmLength(300.0f)
        , CameraLagSpeed(10.0f)
        , CameraRotationLagSpeed(10.0f)
        , CameraLagMaxDistance(100.0f)
        , SocketOffset(FVector(0.0f, 60.0f, 80.0f))
        , FieldOfView(90.0f)
        , CameraCollisionRadius(10.0f)
        , bEnableCameraLag(true)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraDistanceChanged, float, NewDistance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraFOVChanged, float, NewFOV);

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class ULesFightFollowCameraComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    ULesFightFollowCameraComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void InitializeCamera(ALesFightPlayerCharacter* Owner, USpringArmComponent* SpringArm, UCameraComponent* Camera);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void UpdateCamera(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void SetCameraDistance(float NewDistance);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void SetFieldOfView(float NewFOV);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ResetCamera();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ZoomIn(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ZoomOut(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void SetCameraFollowEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Camera|LockOn")
    void SetLockOnTarget(AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "Camera|LockOn")
    void ClearLockOnTarget();

    UFUNCTION(BlueprintPure, Category = "Camera|LockOn")
    bool IsLockedOn() const { return LockOnTarget != nullptr; }

    UFUNCTION(BlueprintPure, Category = "Camera|LockOn")
    AActor* GetLockOnTarget() const { return LockOnTarget; }

    UFUNCTION(BlueprintPure, Category = "Camera")
    float GetCurrentDistance() const { return CurrentCameraDistance; }

    UFUNCTION(BlueprintPure, Category = "Camera")
    FCameraFollowSettings GetCameraSettings() const { return CurrentSettings; }

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void SetCameraSettings(const FCameraFollowSettings& NewSettings);

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ApplyCinematicPreset();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ApplyCombatPreset();

    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ApplyDefaultPreset();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
    FCameraFollowSettings DefaultSettings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
    FCameraFollowSettings CombatSettings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
    FCameraFollowSettings CinematicSettings;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCameraDistanceChanged OnCameraDistanceChanged;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnCameraFOVChanged OnCameraFOVChanged;

private:
    TWeakObjectPtr<ALesFightPlayerCharacter> OwnerCharacter;
    TWeakObjectPtr<USpringArmComponent> CameraBoom;
    TWeakObjectPtr<UCameraComponent> PlayerCamera;
    FCameraFollowSettings CurrentSettings;
    float CurrentCameraDistance;
    float CurrentFOV;
    float TargetCameraDistance;
    float TargetFOV;
    bool bCameraFollowEnabled;
    TObjectPtr<AActor> LockOnTarget;

    void HandleCameraCollision();
    void HandleLockOnCamera(float DeltaTime);
    void InterpolateCamera(float DeltaTime);
};
