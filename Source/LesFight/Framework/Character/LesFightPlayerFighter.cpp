#include "LesFightPlayerFighter.h"
#include "LesFight.h"
#include "Components/InputComponent.h"

ALesFightPlayerFighter::ALesFightPlayerFighter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , PlayerIndex(-1)
    , bIsLocalPlayer(true)
    , bIsReady(false)
    , DefaultFighterID(NAME_None)
{
    PrimaryActorTick.bCanEverTick = true;
}

void ALesFightPlayerFighter::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogLesFight, Log, TEXT("PlayerFighter spawned for player %d"), PlayerIndex);
}

void ALesFightPlayerFighter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    BindFighterInput();
}

void ALesFightPlayerFighter::ReadyFighter()
{
    bIsReady = true;
    OnPlayerFighterReady.Broadcast(this);
    UE_LOG(LogLesFight, Log, TEXT("PlayerFighter %d is ready"), PlayerIndex);
}

void ALesFightPlayerFighter::UnreadyFighter()
{
    bIsReady = false;
}

void ALesFightPlayerFighter::OnInputDeviceChanged(int32 DeviceID)
{
    UE_LOG(LogLesFight, Verbose, TEXT("PlayerFighter %d input device changed to %d"), PlayerIndex, DeviceID);
}

void ALesFightPlayerFighter::BindFighterInput()
{
    if (!InputComponent) return;

    InputComponent->BindAction("Ready", IE_Pressed, this, &ALesFightPlayerFighter::ReadyFighter);
    InputComponent->BindAction("Taunt", IE_Pressed, this, &ALesFightPlayerFighter::UnreadyFighter);
}
