#include "LesFightAdvancedMovement.h"
#include "LesFightMartialArtsManager.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ULesFightAdvancedMovement::ULesFightAdvancedMovement()
    : bIsMoving(false)
    , CurrentMovement(EAdvancedMovementType::None)
    , CooldownMultiplier(1.0f)
    , MovementTimer(0.0f)
    , WallJumpCount(0)
    , bOnWall(false)
{
}

void ULesFightAdvancedMovement::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    CooldownTimers.Empty();
    MovementTimer = 0.0f;
    WallJumpCount = 0;
}

void ULesFightAdvancedMovement::Tick(float DeltaTime)
{
    if (bIsMoving)
    {
        ProcessMovement(DeltaTime);
    }
    UpdateCooldowns(DeltaTime);
}

bool ULesFightAdvancedMovement::ExecuteMovement(EAdvancedMovementType MovementType)
{
    if (bIsMoving) return false;
    if (!AvailableMovements.Contains(MovementType)) return false;
    if (IsOnCooldown(MovementType)) return false;
    if (!CanExecuteMovement(MovementType)) return false;

    CurrentMovement = MovementType;
    bIsMoving = true;
    MovementTimer = 0.0f;
    OnMovementExecuted.Broadcast(MovementType);

    if (OwnerManager.IsValid())
    {
        ACharacter* Char = Cast<ACharacter>(OwnerManager->GetOuter());
        if (Char)
        {
            UCharacterMovementComponent* MoveComp = Char->GetCharacterMovement();
            if (MoveComp)
            {
                ApplyMovementPhysics(MovementType);
            }
        }
    }

    return true;
}

bool ULesFightAdvancedMovement::CanExecuteMovement(EAdvancedMovementType MovementType) const
{
    switch (MovementType)
    {
    case EAdvancedMovementType::WallRun:
    case EAdvancedMovementType::WallJump:
    case EAdvancedMovementType::WallKick:
        return bOnWall;
    case EAdvancedMovementType::AirDash:
        return true;
    default:
        return true;
    }
}

void ULesFightAdvancedMovement::CancelCurrentMovement()
{
    if (bIsMoving)
    {
        bIsMoving = false;
        CurrentMovement = EAdvancedMovementType::None;
        MovementTimer = 0.0f;
    }
}

void ULesFightAdvancedMovement::SetMovementData(
    const TMap<EAdvancedMovementType, FAdvancedMovementData>& Data)
{
    MovementDefinitions = Data;
}

void ULesFightAdvancedMovement::SetAvailableMovements(
    const TArray<EAdvancedMovementType>& Movements)
{
    AvailableMovements = Movements;
    for (EAdvancedMovementType Mov : Movements)
    {
        if (!CooldownTimers.Contains(Mov))
        {
            CooldownTimers.Add(Mov, 0.0f);
        }
    }
}

float ULesFightAdvancedMovement::GetMovementSpeed(EAdvancedMovementType MovementType) const
{
    const FAdvancedMovementData* Found = MovementDefinitions.Find(MovementType);
    return Found ? Found->Speed : 0.0f;
}

float ULesFightAdvancedMovement::GetMovementDistance(EAdvancedMovementType MovementType) const
{
    const FAdvancedMovementData* Found = MovementDefinitions.Find(MovementType);
    return Found ? Found->Distance : 0.0f;
}

float ULesFightAdvancedMovement::GetMovementDuration(EAdvancedMovementType MovementType) const
{
    const FAdvancedMovementData* Found = MovementDefinitions.Find(MovementType);
    return Found ? Found->Duration : 0.0f;
}

void ULesFightAdvancedMovement::ClearCooldowns()
{
    for (auto& Pair : CooldownTimers)
    {
        Pair.Value = 0.0f;
    }
}

void ULesFightAdvancedMovement::Reset()
{
    bIsMoving = false;
    CurrentMovement = EAdvancedMovementType::None;
    MovementTimer = 0.0f;
    WallJumpCount = 0;
    CooldownTimers.Empty();
}

void ULesFightAdvancedMovement::ProcessMovement(float DeltaTime)
{
    MovementTimer += DeltaTime;
    const FAdvancedMovementData* Data = MovementDefinitions.Find(CurrentMovement);

    if (Data && MovementTimer >= Data->Duration)
    {
        OnMovementFinished();
    }
}

void ULesFightAdvancedMovement::OnMovementFinished()
{
    bIsMoving = false;
    const FAdvancedMovementData* Data = MovementDefinitions.Find(CurrentMovement);
    if (Data && Data->Cooldown > 0.0f)
    {
        CooldownTimers.Add(CurrentMovement, Data->Cooldown * CooldownMultiplier);
    }
    OnMovementCompleted.Broadcast(CurrentMovement);
    CurrentMovement = EAdvancedMovementType::None;
}

void ULesFightAdvancedMovement::ApplyMovementPhysics(EAdvancedMovementType MovementType)
{
}

void ULesFightAdvancedMovement::UpdateCooldowns(float DeltaTime)
{
    TArray<EAdvancedMovementType> Keys;
    CooldownTimers.GetKeys(Keys);
    for (EAdvancedMovementType Key : Keys)
    {
        if (CooldownTimers[Key] > 0.0f)
        {
            CooldownTimers[Key] -= DeltaTime;
            if (CooldownTimers[Key] < 0.0f)
            {
                CooldownTimers[Key] = 0.0f;
            }
        }
    }
}

bool ULesFightAdvancedMovement::IsOnCooldown(EAdvancedMovementType MovementType) const
{
    const float* Cooldown = CooldownTimers.Find(MovementType);
    return Cooldown && *Cooldown > 0.0f;
}
