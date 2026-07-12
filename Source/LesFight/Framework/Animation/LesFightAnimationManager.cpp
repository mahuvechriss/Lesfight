#include "LesFightAnimationManager.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFightBaseFighter.h"
#include "LesFight.h"

ULesFightAnimationManager::ULesFightAnimationManager()
    : CurrentQuality(EAnimationQuality::High)
    , GlobalPlayRate(1.0f)
    , MaxAnimatedCharacters(8)
    , bGlobalPaused(false)
    , SlowMotionTimer(0.0f)
    , SlowMotionDuration(0.0f)
    , OriginalTimeDilation(1.0f)
{
}

void ULesFightAnimationManager::Initialize()
{
    UE_LOG(LogLesFight, Log, TEXT("AnimationManager initialized"));
}

void ULesFightAnimationManager::RegisterCharacter(ALesFightBaseFighter* Fighter)
{
    if (Fighter && !RegisteredFighters.Contains(Fighter))
    {
        RegisteredFighters.Add(Fighter);
        UE_LOG(LogLesFight, Verbose, TEXT("AnimationManager registered fighter: %s"), *Fighter->GetName());
    }
}

void ULesFightAnimationManager::UnregisterCharacter(ALesFightBaseFighter* Fighter)
{
    RegisteredFighters.Remove(Fighter);
}

void ULesFightAnimationManager::SetGlobalAnimationQuality(EAnimationQuality Quality)
{
    CurrentQuality = Quality;
    OnAnimationQualityChanged.Broadcast(Quality);
}

void ULesFightAnimationManager::SetGlobalPlayRate(float Rate)
{
    GlobalPlayRate = FMath::Clamp(Rate, 0.1f, 3.0f);
}

void ULesFightAnimationManager::BroadcastGlobalEvent(FName EventName, AActor* Instigator)
{
    OnGlobalAnimationEvent.Broadcast(EventName, Instigator);
}

void ULesFightAnimationManager::PauseAllAnimations()
{
    bGlobalPaused = true;
    for (ALesFightBaseFighter* Fighter : RegisteredFighters)
    {
        if (Fighter)
        {
            Fighter->CustomTimeDilation = 0.0f;
        }
    }
}

void ULesFightAnimationManager::ResumeAllAnimations()
{
    bGlobalPaused = false;
    for (ALesFightBaseFighter* Fighter : RegisteredFighters)
    {
        if (Fighter)
        {
            Fighter->CustomTimeDilation = 1.0f;
        }
    }
}

void ULesFightAnimationManager::SetSlowMotion(float TimeDilation, float Duration)
{
    SlowMotionTimer = 0.0f;
    SlowMotionDuration = Duration;
    OriginalTimeDilation = TimeDilation;

    for (ALesFightBaseFighter* Fighter : RegisteredFighters)
    {
        if (Fighter)
        {
            Fighter->CustomTimeDilation = TimeDilation;
        }
    }
}
