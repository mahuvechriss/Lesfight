#pragma once

#include "CoreMinimal.h"
#include "Framework/Application/IInputProcessor.h"
#include "LesFightTouchInputProcessor.generated.h"

class ALesFightPlayerCharacter;

USTRUCT(BlueprintType)
struct FVirtualJoystickState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FVector2D CurrentValue;

    UPROPERTY(BlueprintReadOnly)
    FVector2D StartPosition;

    UPROPERTY(BlueprintReadOnly)
    FVector2D CurrentPosition;

    UPROPERTY(BlueprintReadOnly)
    float DeadZone;

    UPROPERTY(BlueprintReadOnly)
    int32 FingerIndex;

    UPROPERTY(BlueprintReadOnly)
    bool bIsActive;

    FVirtualJoystickState()
        : CurrentValue(FVector2D::ZeroVector)
        , StartPosition(FVector2D::ZeroVector)
        , CurrentPosition(FVector2D::ZeroVector)
        , DeadZone(0.15f)
        , FingerIndex(-1)
        , bIsActive(false)
    {}
};

UCLASS(Blueprintable)
class ULesFightTouchInputProcessor : public UObject
{
    GENERATED_BODY()

public:
    ULesFightTouchInputProcessor();

    UFUNCTION(BlueprintCallable, Category = "Touch Input")
    void Initialize(APlayerController* InPC);

    UFUNCTION(BlueprintCallable, Category = "Touch Input")
    void ProcessTouchInput(int32 FingerIndex, const FVector2D& ScreenPosition, bool bPressed, bool bReleased);

    UFUNCTION(BlueprintCallable, Category = "Touch Input")
    void SimulateAxisInput(const FString& AxisName, float Value);

    UFUNCTION(BlueprintCallable, Category = "Touch Input")
    void SimulateActionInput(const FString& ActionName, bool bPressed);

    UFUNCTION(BlueprintPure, Category = "Touch Input")
    FVector2D GetLeftJoystickValue() const { return LeftJoystick.CurrentValue; }

    UFUNCTION(BlueprintPure, Category = "Touch Input")
    FVector2D GetRightJoystickValue() const { return RightJoystick.CurrentValue; }

    UFUNCTION(BlueprintPure, Category = "Touch Input")
    bool IsTouchSupported() const;

    UFUNCTION(BlueprintCallable, Category = "Touch Input")
    void SetJoystickDeadZone(float NewDeadZone);

    UFUNCTION(BlueprintCallable, Category = "Touch Input")
    void ConfigureForScreenSize(const FVector2D& ScreenSize);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Touch Input")
    FVirtualJoystickState LeftJoystick;

    UPROPERTY(BlueprintReadOnly, Category = "Touch Input")
    FVirtualJoystickState RightJoystick;

    UPROPERTY(BlueprintReadOnly, Category = "Touch Input")
    TArray<bool> ActionButtonStates;

    UPROPERTY(BlueprintReadOnly, Category = "Touch Input")
    FVector2D ScreenResolution;

private:
    TWeakObjectPtr<APlayerController> PlayerController;
    TWeakObjectPtr<ALesFightPlayerCharacter> ControlledCharacter;

    void UpdateJoystick(FVirtualJoystickState& Joystick, const FVector2D& TouchPosition);
    void MapJoystickToMovement(const FVirtualJoystickState& Joystick);
};
