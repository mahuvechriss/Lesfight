#include "LesFightBasePawn.h"
#include "Net/UnrealNetwork.h"
#include "LesFight.h"

ALesFightBasePawn::ALesFightBasePawn()
    : MaxHealth(1000.0f)
    , Health(MaxHealth)
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}

void ALesFightBasePawn::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
}

void ALesFightBasePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALesFightBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ALesFightBasePawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
    AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    Health = FMath::Clamp(Health - ActualDamage, 0.0f, MaxHealth);
    return ActualDamage;
}

void ALesFightBasePawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ALesFightBasePawn, Health);
}
