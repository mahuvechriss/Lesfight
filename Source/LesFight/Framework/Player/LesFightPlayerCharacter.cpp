#include "LesFightPlayerCharacter.h"
#include "LesFightFollowCameraComponent.h"
#include "LesFightLockOnComponent.h"
#include "LesFight.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

ALesFightPlayerCharacter::ALesFightPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<ULesFightCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
    , TurnRateGamepad(45.0f)
    , LookUpRateGamepad(45.0f)
    , InputForward(0.0f)
    , InputRight(0.0f)
    , bJumpHeld(false)
    , bSprintHeld(false)
{
    PrimaryActorTick.bCanEverTick = true;
    bUseControllerRotationYaw = false;

    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->bEnableCameraLag = true;
    CameraBoom->CameraLagSpeed = 10.0f;

    FollowCameraComponent = CreateDefaultSubobject<ULesFightFollowCameraComponent>(TEXT("FollowCameraComponent"));

    LockOnComponent = CreateDefaultSubobject<ULesFightLockOnComponent>(TEXT("LockOnComponent"));

    StateMachine = CreateDefaultSubobject<ULesFightCharacterStateMachine>(TEXT("StateMachine"));
}

void ALesFightPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (FollowCameraComponent)
    {
        FollowCameraComponent->InitializeCamera(this, CameraBoom, FollowCamera);
    }

    UE_LOG(LogLesFight, Log, TEXT("PlayerCharacter initialized: %s"), *GetName());
}

void ALesFightPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (FollowCameraComponent)
    {
        FollowCameraComponent->UpdateCamera(DeltaTime);
    }
}

void ALesFightPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ALesFightPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ALesFightPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &ALesFightPlayerCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &ALesFightPlayerCharacter::LookUp);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALesFightPlayerCharacter::JumpPressed);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ALesFightPlayerCharacter::JumpReleased);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALesFightPlayerCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALesFightPlayerCharacter::StopSprint);
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ALesFightPlayerCharacter::StartCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ALesFightPlayerCharacter::StopCrouch);
}

void ALesFightPlayerCharacter::MoveForward(float Value)
{
    InputForward = Value;
    if (Controller && Value != 0.0f)
    {
        const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ALesFightPlayerCharacter::MoveRight(float Value)
{
    InputRight = Value;
    if (Controller && Value != 0.0f)
    {
        const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ALesFightPlayerCharacter::Turn(float Rate)
{
    if (FollowCameraComponent && FollowCameraComponent->IsLockedOn())
    {
        return;
    }
    AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALesFightPlayerCharacter::LookUp(float Rate)
{
    AddControllerPitchInput(Rate * LookUpRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALesFightPlayerCharacter::StartSprint()
{
    bSprintHeld = true;
    ULesFightCharacterMovementComponent* MovComp = GetLesFightMovement();
    if (MovComp)
    {
        MovComp->SetWantsToSprint(true);
    }
}

void ALesFightPlayerCharacter::StopSprint()
{
    bSprintHeld = false;
    ULesFightCharacterMovementComponent* MovComp = GetLesFightMovement();
    if (MovComp)
    {
        MovComp->SetWantsToSprint(false);
    }
}

void ALesFightPlayerCharacter::StartCrouch()
{
    ULesFightCharacterMovementComponent* MovComp = GetLesFightMovement();
    if (MovComp)
    {
        MovComp->SetWantsToCrouch(true);
    }
}

void ALesFightPlayerCharacter::StopCrouch()
{
    ULesFightCharacterMovementComponent* MovComp = GetLesFightMovement();
    if (MovComp)
    {
        MovComp->SetWantsToCrouch(false);
    }
}

void ALesFightPlayerCharacter::JumpPressed()
{
    bJumpHeld = true;
    Jump();
}

void ALesFightPlayerCharacter::JumpReleased()
{
    bJumpHeld = false;
    StopJumping();
}

void ALesFightPlayerCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    if (StateMachine)
    {
        StateMachine->SetState(ECharacterGameplayState::Landing);
    }
}

ULesFightCharacterMovementComponent* ALesFightPlayerCharacter::GetLesFightMovement() const
{
    return Cast<ULesFightCharacterMovementComponent>(GetCharacterMovement());
}
