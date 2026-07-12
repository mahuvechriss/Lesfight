#include "LesFightSlowMotionSystem.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "Framework/VFX/World/LesFightVFXWorldManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void ULesFightSlowMotionSystem::Initialize(ULesFightVFXWorldManager* InManager)
{
    OwnerManager = InManager;

    bSlowMotionActive = false;
    CurrentDilation = 1.0f;
    ElapsedTime = 0.0f;
    bExiting = false;
}

void ULesFightSlowMotionSystem::TriggerSlowMotion(ECinematicVFXEvent Event)
{
    float Dilation = 0.1f;
    float InEnter = 0.2f;
    float InHold = 1.5f;
    float InExit = 0.3f;

    switch (Event)
    {
    case ECinematicVFXEvent::UltimateStart:
        Dilation = 0.05f;
        InEnter = 0.3f;
        InHold = 2.0f;
        InExit = 0.5f;
        break;
    case ECinematicVFXEvent::UltimateHit:
        Dilation = 0.1f;
        InEnter = 0.1f;
        InHold = 0.5f;
        InExit = 0.3f;
        break;
    case ECinematicVFXEvent::FinisherStart:
        Dilation = 0.02f;
        InEnter = 0.4f;
        InHold = 1.0f;
        InExit = 0.6f;
        break;
    default:
        break;
    }

    BeginSlowMotion(Dilation, InEnter, InHold, InExit);
}

void ULesFightSlowMotionSystem::BeginSlowMotion(float Dilation, float InEnterDuration, float InHoldDuration, float InExitDuration)
{
    if (bSlowMotionActive)
    {
        return;
    }

    bSlowMotionActive = true;
    CurrentDilation = 1.0f;
    EnterDuration = InEnterDuration;
    HoldDuration = InHoldDuration;
    ExitDuration = InExitDuration;
    ElapsedTime = 0.0f;
    bExiting = false;

    OnSlowMotionStart.Broadcast();
}

void ULesFightSlowMotionSystem::EndSlowMotion()
{
    if (!bSlowMotionActive)
    {
        return;
    }

    bExiting = true;
    ElapsedTime = 0.0f;
}

void ULesFightSlowMotionSystem::TickSlowMotion(float DeltaTime)
{
    if (!bSlowMotionActive)
    {
        return;
    }

    ElapsedTime += DeltaTime;

    float TargetDilation = 1.0f;

    if (!bExiting)
    {
        float TotalPhase = EnterDuration + HoldDuration;

        if (ElapsedTime <= EnterDuration)
        {
            float Alpha = ElapsedTime / EnterDuration;
            CurrentDilation = FMath::Lerp(1.0f, CurrentDilation, Alpha);
        }
        else if (ElapsedTime <= TotalPhase)
        {
            CurrentDilation = CurrentDilation;
        }
        else
        {
            bExiting = true;
            ElapsedTime = 0.0f;
        }
    }

    if (bExiting)
    {
        float ExitAlpha = FMath::Clamp(ElapsedTime / ExitDuration, 0.0f, 1.0f);
        CurrentDilation = FMath::Lerp(CurrentDilation, 1.0f, ExitAlpha);

        if (ExitAlpha >= 1.0f)
        {
            bSlowMotionActive = false;
            CurrentDilation = 1.0f;
            ElapsedTime = 0.0f;
            bExiting = false;

            OnSlowMotionEnd.Broadcast();
        }
    }

    if (UWorld* World = GetWorld())
    {
        World->SetGlobalTimeDilation(CurrentDilation);
    }
}

bool ULesFightSlowMotionSystem::IsSlowMotionActive() const
{
    return bSlowMotionActive;
}

float ULesFightSlowMotionSystem::GetCurrentDilation() const
{
    return CurrentDilation;
}

void ULesFightSlowMotionSystem::SetSlowMotionPriority(int32 NewPriority)
{
    Priority = NewPriority;
}

float ULesFightSlowMotionSystem::GetSlowMotionProgress() const
{
    if (!bSlowMotionActive)
    {
        return 0.0f;
    }

    float TotalDuration = EnterDuration + HoldDuration + ExitDuration;
    if (TotalDuration <= 0.0f)
    {
        return 1.0f;
    }

    return FMath::Clamp(ElapsedTime / TotalDuration, 0.0f, 1.0f);
}

UWorld* ULesFightSlowMotionSystem::GetWorld() const
{
    if (OwnerManager.IsValid())
    {
        return OwnerManager->GetWorld();
    }
    return nullptr;
}
