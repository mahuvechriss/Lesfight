#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "LesFightCameraManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraTransitionComplete, AActor*, CameraTarget);

USTRUCT(BlueprintType)
struct FCameraSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraLagSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FieldOfView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CameraCollisionRadius;

    FCameraSettings()
        : CameraDistance(300.0f)
        , CameraHeight(80.0f)
        , CameraLagSpeed(10.0f)
        , FieldOfView(90.0f)
        , CameraCollisionRadius(10.0f)
    {}
};

UENUM(BlueprintType)
enum class ECameraMode : uint8
{
    Default,
    Combat,
    Cinematic,
    CharacterSelect,
    Spectator
};

UCLASS()
class ALesFightCameraManager : public APlayerCameraManager
{
    GENERATED_BODY()

public:
    ALesFightCameraManager();

    virtual void BeginPlay() override;
    virtual void UpdateCamera(float DeltaTime) override;
    virtual void ProcessViewRotation(float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot) override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void SetCameraMode(ECameraMode NewMode);

    UFUNCTION(BlueprintPure, Category = "LesFight|Camera")
    ECameraMode GetCameraMode() const { return CurrentCameraMode; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void SetCameraTarget(AActor* NewTarget);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void SetCameraDistance(float NewDistance);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void SetFieldOfView(float NewFOV);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void SetCameraLagEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void PlayCinematicTransition(float Duration);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void ZoomIn(float TargetFOV, float Duration);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Camera")
    void ZoomOut(float TargetFOV, float Duration);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Camera")
    FCameraSettings DefaultCameraSettings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Camera")
    FCameraSettings CombatCameraSettings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Camera")
    FCameraSettings CinematicCameraSettings;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnCameraTransitionComplete OnCameraTransitionComplete;

private:
    ECameraMode CurrentCameraMode;
    TObjectPtr<AActor> CameraTargetActor;
    FCameraSettings CurrentSettings;
    FCameraSettings TargetSettings;
    float TransitionProgress;
    float TransitionDuration;
    bool bIsTransitioning;
    bool bCameraLagEnabled;

    FCameraSettings GetSettingsForMode(ECameraMode Mode) const;
    void UpdateCameraCollision();
};
