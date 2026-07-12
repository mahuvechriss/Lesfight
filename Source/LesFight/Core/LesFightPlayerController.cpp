#include "LesFightPlayerController.h"
#include "LesFightInputManager.h"
#include "LesFightHUD.h"
#include "LesFight.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

ALesFightPlayerController::ALesFightPlayerController()
    : bIsMenuOpen(false)
    , bIsInputEnabled(true)
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.1f;
}

void ALesFightPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalPlayerController())
    {
        InputManager = NewObject<ULesFightInputManager>(this, TEXT("InputManager"));
        if (InputManager)
        {
            InputManager->InitializeInputSystem(this);
        }

        if (DefaultInputMapping)
        {
            UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
            if (Subsystem)
            {
                Subsystem->AddMappingContext(DefaultInputMapping, 0);
            }
        }
    }

    ShowHUD();
}

void ALesFightPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    HideHUD();
    Super::EndPlay(EndPlayReason);
}

void ALesFightPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
    if (EnhancedInput)
    {
        if (MoveAction)
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALesFightPlayerController::HandleMoveInput);
        if (LookAction)
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALesFightPlayerController::HandleLookInput);
        if (MenuAction)
            EnhancedInput->BindAction(MenuAction, ETriggerEvent::Started, this, &ALesFightPlayerController::HandleMenuToggle);
        if (PauseAction)
            EnhancedInput->BindAction(PauseAction, ETriggerEvent::Started, this, &ALesFightPlayerController::HandlePauseGame);
    }
}

void ALesFightPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALesFightPlayerController::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();
}

void ALesFightPlayerController::ShowHUD()
{
    if (!CurrentHUD && HUDClass)
    {
        CurrentHUD = CreateWidget<ULesFightHUD>(this, HUDClass);
        if (CurrentHUD)
        {
            CurrentHUD->AddToViewport();
            UE_LOG(LogLesFightUI, Log, TEXT("HUD created and added to viewport"));
        }
    }
}

void ALesFightPlayerController::HideHUD()
{
    if (CurrentHUD)
    {
        CurrentHUD->RemoveFromParent();
        CurrentHUD = nullptr;
    }
}

void ALesFightPlayerController::ToggleMenu()
{
    bIsMenuOpen = !bIsMenuOpen;
    OnMenuToggled.Broadcast();

    if (bIsMenuOpen)
    {
        SetInputMode(FInputModeGameAndUI());
        SetShowMouseCursor(true);
    }
    else
    {
        SetInputMode(FInputModeGameOnly());
        SetShowMouseCursor(false);
    }
}

void ALesFightPlayerController::SetCameraZoom(float ZoomValue)
{
    if (PlayerCameraManager)
    {
        PlayerCameraManager->SetFOV(ZoomValue);
    }
}

void ALesFightPlayerController::SetInputEnabled(bool bEnabled)
{
    bIsInputEnabled = bEnabled;
    if (InputComponent)
    {
        InputComponent->BlockAllInputs(!bEnabled);
    }
}

void ALesFightPlayerController::HandleMoveInput(const FInputActionValue& Value)
{
    if (!bIsInputEnabled || !GetPawn()) return;

    FVector2D MovementVector = Value.Get<FVector2D>();
    if (GetPawn())
    {
        GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), MovementVector.Y);
        GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), MovementVector.X);
    }
}

void ALesFightPlayerController::HandleLookInput(const FInputActionValue& Value)
{
    if (!bIsInputEnabled) return;

    FVector2D LookVector = Value.Get<FVector2D>();
    AddYawInput(LookVector.X);
    AddPitchInput(LookVector.Y);
}

void ALesFightPlayerController::HandleMenuToggle()
{
    ToggleMenu();
}

void ALesFightPlayerController::HandlePauseGame()
{
    if (GetWorld())
    {
        GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("pause"));
    }
}
