#include "LesFightAnimationEventManager.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"
#include "Kismet/GameplayStatics.h"

ULesFightAnimationEventManager::ULesFightAnimationEventManager()
    : EventTimingMultiplier(1.0f)
    , CurrentAnimTime(0.0f)
{
}

void ULesFightAnimationEventManager::Initialize(ULesFightCharacterAnimationComponent* InComponent)
{
    AnimComponent = InComponent;
}

void ULesFightAnimationEventManager::Update(float DeltaTime)
{
    CurrentAnimTime += DeltaTime;

    for (FAnimEventInfo& Event : RegisteredEvents)
    {
        if (!Event.bTriggered && CurrentAnimTime >= Event.EventTime * EventTimingMultiplier)
        {
            Event.bTriggered = true;
            TriggeredEvents.Add(Event.EventName);
            OnAnimEventTriggered.Broadcast(Event.EventName, CurrentAnimTime,
                AnimComponent.IsValid() ? AnimComponent->GetOwner() : nullptr);
        }
    }
}

void ULesFightAnimationEventManager::RegisterEvent(FName EventName, float TriggerTime)
{
    FAnimEventInfo Event;
    Event.EventName = EventName;
    Event.EventTime = TriggerTime;
    RegisteredEvents.Add(Event);
}

void ULesFightAnimationEventManager::RegisterTimedEvent(FName EventName, float TriggerTime,
    float Duration)
{
    FAnimEventInfo Event;
    Event.EventName = EventName;
    Event.EventTime = TriggerTime;
    Event.EventDuration = Duration;
    RegisteredEvents.Add(Event);
}

void ULesFightAnimationEventManager::TriggerEvent(FName EventName)
{
    OnAnimEventTriggered.Broadcast(EventName, CurrentAnimTime,
        AnimComponent.IsValid() ? AnimComponent->GetOwner() : nullptr);
}

void ULesFightAnimationEventManager::TriggerComboWindow(bool bOpen)
{
    TriggerEvent(bOpen ? FName(TEXT("ComboWindowOpen")) : FName(TEXT("ComboWindowClose")));
}

void ULesFightAnimationEventManager::TriggerFootstep()
{
    TriggerEvent(FName(TEXT("Footstep")));
}

void ULesFightAnimationEventManager::TriggerHitEvent(FName HitBone)
{
    TriggerEvent(FName(TEXT("HitImpact")));
}

void ULesFightAnimationEventManager::TriggerSoundEvent(USoundBase* Sound, float Volume)
{
    if (Sound && AnimComponent.IsValid())
    {
        UGameplayStatics::PlaySoundAtLocation(AnimComponent->GetOwner(), Sound,
            AnimComponent->GetOwner()->GetActorLocation(), Volume);
    }
}

void ULesFightAnimationEventManager::TriggerCameraShake(TSubclassOf<UCameraShakeBase> Shake)
{
    if (Shake && AnimComponent.IsValid())
    {
        APlayerController* PC = Cast<APlayerController>(
            AnimComponent->GetOwner()->GetInstigatorController());
        if (PC)
        {
            PC->ClientStartCameraShake(Shake);
        }
    }
}

void ULesFightAnimationEventManager::TriggerEffectEvent(UParticleSystem* Effect, FVector Location)
{
    if (Effect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(AnimComponent->GetOwner()->GetWorld(),
            Effect, Location);
    }
}

void ULesFightAnimationEventManager::ResetAllEvents()
{
    RegisteredEvents.Empty();
    TriggeredEvents.Empty();
    CurrentAnimTime = 0.0f;
}
