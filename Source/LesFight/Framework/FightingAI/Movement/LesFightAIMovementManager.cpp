#include "LesFightAIMovementManager.h"
#include "Framework/FightingAI/LesFightAIFighterController.h"

void ULesFightAIMovementManager::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;
    DesiredRange = EAICombatRange::Medium;
    CurrentRange = EAICombatRange::Medium;
    CurrentSpeed = 0.0f;
    bNavigationEnabled = true;
    bIsMoving = false;
    MoveTarget = FVector::ZeroVector;
}

void ULesFightAIMovementManager::UpdateMovement(const FAIPerceptionData& Perception, float DeltaTime)
{
    if (!OwnerController.IsValid() || !bNavigationEnabled)
    {
        return;
    }

    CurrentRange = Perception.CombatRange;

    if (CurrentRange != DesiredRange)
    {
        switch (DesiredRange)
        {
        case EAICombatRange::Close:
            if (CurrentRange == EAICombatRange::Medium || CurrentRange == EAICombatRange::Far)
            {
                CloseDistance();
            }
            break;
        case EAICombatRange::Medium:
            if (CurrentRange == EAICombatRange::Close)
            {
                CreateDistance();
            }
            else if (CurrentRange == EAICombatRange::Far)
            {
                CloseDistance();
            }
            break;
        case EAICombatRange::Far:
            if (CurrentRange == EAICombatRange::Close || CurrentRange == EAICombatRange::Medium)
            {
                CreateDistance();
            }
            break;
        }
    }
    else
    {
        StopMovement();
    }
}

void ULesFightAIMovementManager::SetDesiredRange(EAICombatRange Range)
{
    DesiredRange = Range;
}

EAICombatRange ULesFightAIMovementManager::GetDesiredRange() const
{
    return DesiredRange;
}

void ULesFightAIMovementManager::MoveTowardTarget(float Speed)
{
    if (!OwnerController.IsValid())
    {
        return;
    }

    CurrentSpeed = FMath::Clamp(Speed, 0.0f, MovementSpeed);
    bIsMoving = true;
    OwnerController->MoveTowardTarget(CurrentSpeed);
}

void ULesFightAIMovementManager::RetreatFromTarget(float Speed)
{
    if (!OwnerController.IsValid())
    {
        return;
    }

    CurrentSpeed = FMath::Clamp(Speed, 0.0f, MovementSpeed);
    bIsMoving = true;
    OwnerController->RetreatFromTarget(CurrentSpeed);
}

void ULesFightAIMovementManager::StrafeAroundTarget(float Direction)
{
    if (!OwnerController.IsValid())
    {
        return;
    }

    CurrentSpeed = MovementSpeed * 0.5f;
    bIsMoving = true;
    OwnerController->StrafeAroundTarget(Direction);
}

void ULesFightAIMovementManager::CloseDistance()
{
    MoveTowardTarget(MovementSpeed);
}

void ULesFightAIMovementManager::CreateDistance()
{
    RetreatFromTarget(MovementSpeed);
}

float ULesFightAIMovementManager::GetCurrentSpeed() const
{
    return CurrentSpeed;
}

bool ULesFightAIMovementManager::IsMoving() const
{
    return bIsMoving;
}

void ULesFightAIMovementManager::StopMovement()
{
    CurrentSpeed = 0.0f;
    bIsMoving = false;

    if (OwnerController.IsValid())
    {
        OwnerController->StopMovement();
    }
}

void ULesFightAIMovementManager::SetNavigationEnabled(bool bEnabled)
{
    bNavigationEnabled = bEnabled;

    if (!bEnabled)
    {
        StopMovement();
    }
}
