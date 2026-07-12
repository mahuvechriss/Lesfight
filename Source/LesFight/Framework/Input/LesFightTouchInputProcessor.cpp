#include "LesFightTouchInputProcessor.h"
#include "LesFightPlayerCharacter.h"
#include "LesFight.h"
#include "GameFramework/PlayerController.h"

ULesFightTouchInputProcessor::ULesFightTouchInputProcessor()
    : ScreenResolution(FVector2D(1920.0f, 1080.0f))
{
    ActionButtonStates.SetNum(10);
}

void ULesFightTouchInputProcessor::Initialize(APlayerController* InPC)
{
    PlayerController = InPC;
    if (InPC)
    {
        ControlledCharacter = Cast<ALesFightPlayerCharacter>(InPC->GetPawn());
    }
}

void ULesFightTouchInputProcessor::ProcessTouchInput(int32 FingerIndex, const FVector2D& ScreenPosition,
    bool bPressed, bool bReleased)
{
    if (!PlayerController.IsValid()) return;

    float HalfScreenWidth = ScreenResolution.X * 0.5f;

    if (ScreenPosition.X < HalfScreenWidth)
    {
        if (bPressed)
        {
            LeftJoystick.StartPosition = ScreenPosition;
            LeftJoystick.CurrentPosition = ScreenPosition;
            LeftJoystick.FingerIndex = FingerIndex;
            LeftJoystick.bIsActive = true;
        }
        else if (bReleased && LeftJoystick.FingerIndex == FingerIndex)
        {
            LeftJoystick.bIsActive = false;
            LeftJoystick.CurrentValue = FVector2D::ZeroVector;
            LeftJoystick.FingerIndex = -1;
            SimulateAxisInput("MoveForward", 0.0f);
            SimulateAxisInput("MoveRight", 0.0f);
        }
        else if (LeftJoystick.bIsActive && LeftJoystick.FingerIndex == FingerIndex)
        {
            UpdateJoystick(LeftJoystick, ScreenPosition);
            MapJoystickToMovement(LeftJoystick);
        }
    }
    else
    {
        if (bPressed)
        {
            RightJoystick.StartPosition = ScreenPosition;
            RightJoystick.CurrentPosition = ScreenPosition;
            RightJoystick.FingerIndex = FingerIndex;
            RightJoystick.bIsActive = true;
        }
        else if (bReleased && RightJoystick.FingerIndex == FingerIndex)
        {
            RightJoystick.bIsActive = false;
            RightJoystick.CurrentValue = FVector2D::ZeroVector;
            RightJoystick.FingerIndex = -1;
            SimulateAxisInput("Turn", 0.0f);
            SimulateAxisInput("LookUp", 0.0f);
        }
        else if (RightJoystick.bIsActive && RightJoystick.FingerIndex == FingerIndex)
        {
            UpdateJoystick(RightJoystick, ScreenPosition);
        }
    }
}

void ULesFightTouchInputProcessor::SimulateAxisInput(const FString& AxisName, float Value)
{
    if (!PlayerController.IsValid() || !PlayerController->InputComponent) return;
    PlayerController->InputComponent->AxisKeyValue(FName(*AxisName), Value);
}

void ULesFightTouchInputProcessor::SimulateActionInput(const FString& ActionName, bool bPressed)
{
    if (!PlayerController.IsValid() || !PlayerController->InputComponent) return;

    FName ActionFName(*ActionName);
    if (bPressed)
    {
        PlayerController->InputComponent->BindAction(ActionFName, IE_Pressed, nullptr, nullptr);
    }
    else
    {
        PlayerController->InputComponent->BindAction(ActionFName, IE_Released, nullptr, nullptr);
    }
}

bool ULesFightTouchInputProcessor::IsTouchSupported() const
{
    return FPlatformMisc::GetMaxUIDesignResolution().X > 0;
}

void ULesFightTouchInputProcessor::SetJoystickDeadZone(float NewDeadZone)
{
    LeftJoystick.DeadZone = NewDeadZone;
    RightJoystick.DeadZone = NewDeadZone;
}

void ULesFightTouchInputProcessor::ConfigureForScreenSize(const FVector2D& ScreenSize)
{
    ScreenResolution = ScreenSize;
}

void ULesFightTouchInputProcessor::UpdateJoystick(FVirtualJoystickState& Joystick, const FVector2D& TouchPosition)
{
    Joystick.CurrentPosition = TouchPosition;

    FVector2D Delta = TouchPosition - Joystick.StartPosition;
    float MaxRadius = FMath::Min(ScreenResolution.X, ScreenResolution.Y) * 0.1f;

    Delta.X = FMath::Clamp(Delta.X / MaxRadius, -1.0f, 1.0f);
    Delta.Y = FMath::Clamp(Delta.Y / MaxRadius, -1.0f, 1.0f);

    float Magnitude = Delta.Size();
    if (Magnitude <= Joystick.DeadZone)
    {
        Joystick.CurrentValue = FVector2D::ZeroVector;
    }
    else
    {
        Delta.Normalize();
        Delta *= FMath::Clamp((Magnitude - Joystick.DeadZone) / (1.0f - Joystick.DeadZone), 0.0f, 1.0f);
        Joystick.CurrentValue = Delta;
    }
}

void ULesFightTouchInputProcessor::MapJoystickToMovement(const FVirtualJoystickState& Joystick)
{
    SimulateAxisInput("MoveForward", Joystick.CurrentValue.Y);
    SimulateAxisInput("MoveRight", Joystick.CurrentValue.X);
}
