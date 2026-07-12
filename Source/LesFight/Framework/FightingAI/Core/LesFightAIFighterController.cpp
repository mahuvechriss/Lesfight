#include "LesFightAIFighterController.h"
#include "LesFightAIFighterManager.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"

void ALesFightAIFighterController::Initialize(ULesFightAIFighterManager* InManager)
{
    OwnerManager = InManager;
    bEnabled = false;
    CurrentMode = EAIBehaviorMode::Idle;
}

void ALesFightAIFighterController::PossessFighter(AActor* FighterActor)
{
    ControlledFighter = FighterActor;
}

AActor* ALesFightAIFighterController::GetControlledFighter() const
{
    return ControlledFighter;
}

void ALesFightAIFighterController::SetEnabled(bool bInEnabled)
{
    bEnabled = bInEnabled;
}

bool ALesFightAIFighterController::IsEnabled() const
{
    return bEnabled;
}

void ALesFightAIFighterController::SetTarget(AActor* Target)
{
    CurrentTarget = Target;
}

AActor* ALesFightAIFighterController::GetTarget() const
{
    return CurrentTarget;
}

void ALesFightAIFighterController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bEnabled || !ControlledFighter || !CurrentTarget)
    {
        return;
    }

    for (UObject* Subsystem : Subsystems)
    {
        if (Subsystem)
        {
        }
    }
}
