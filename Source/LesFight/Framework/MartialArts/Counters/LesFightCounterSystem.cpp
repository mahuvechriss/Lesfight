#include "LesFightCounterSystem.h"
#include "LesFightMartialArtsManager.h"
#include "Engine/World.h"

ULesFightCounterSystem::ULesFightCounterSystem()
    : bCounterWindowOpen(false)
    , OpenCounterType(ECounterType::None)
    , WindowTimer(0.0f)
    , GlobalCounterMultiplier(1.0f)
    , LastCounterAttempt(ECounterType::None)
    , LastCounterTime(0.0f)
    , ConsecutiveCounters(0)
    , bSlowMotionActive(false)
{
}

void ULesFightCounterSystem::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    AvailableCounters = {
        ECounterType::CounterAttack, ECounterType::PerfectCounter,
        ECounterType::CounterGrab, ECounterType::CounterThrow
    };
}

void ULesFightCounterSystem::Tick(float DeltaTime)
{
    if (bCounterWindowOpen)
    {
        WindowTimer -= DeltaTime;
        if (WindowTimer <= 0.0f)
        {
            CloseCounterWindow();
        }
    }
}

bool ULesFightCounterSystem::AttemptCounter(ECounterType CounterType)
{
    if (!bCounterWindowOpen) return false;
    if (!AvailableCounters.Contains(CounterType)) return false;

    LastCounterAttempt = CounterType;
    const FCounterWindowData* Data = CounterDefinitions.Find(CounterType);

    float WindowRemaining = WindowTimer;
    bool bPerfect = IsPerfectCounter(CounterType);

    if (WindowRemaining > 0.0f)
    {
        LastCounterTime = OwnerManager.IsValid() && OwnerManager->GetWorld()
            ? OwnerManager->GetWorld()->GetTimeSeconds() : 0.0f;
        ConsecutiveCounters++;
        bCounterWindowOpen = false;

        if (bPerfect)
        {
            OnPerfectCounter.Broadcast(CounterType);
            if (Data && Data->bTriggersSlowMotion)
            {
                TriggerSlowMotionCounter();
            }
        }

        ProcessCounterResult(CounterType, true);
        return true;
    }

    ProcessCounterResult(CounterType, false);
    return false;
}

void ULesFightCounterSystem::OpenCounterWindow(ECounterType CounterType)
{
    const FCounterWindowData* Data = CounterDefinitions.Find(CounterType);
    if (!Data) return;

    bCounterWindowOpen = true;
    OpenCounterType = CounterType;
    WindowTimer = Data->WindowDuration;
}

void ULesFightCounterSystem::CloseCounterWindow()
{
    bCounterWindowOpen = false;
    OpenCounterType = ECounterType::None;
    WindowTimer = 0.0f;
}

bool ULesFightCounterSystem::CanCounter(ECounterType CounterType) const
{
    return AvailableCounters.Contains(CounterType);
}

float ULesFightCounterSystem::GetCounterWindowRemaining() const
{
    return WindowTimer;
}

float ULesFightCounterSystem::GetCounterDamageMultiplier(ECounterType CounterType) const
{
    const FCounterWindowData* Data = CounterDefinitions.Find(CounterType);
    return Data ? Data->DamageMultiplier * GlobalCounterMultiplier : 1.0f;
}

void ULesFightCounterSystem::SetCounterData(
    const TMap<ECounterType, FCounterWindowData>& Data)
{
    CounterDefinitions = Data;
}

void ULesFightCounterSystem::SetAvailableCounters(const TArray<ECounterType>& Counters)
{
    AvailableCounters = Counters;
}

void ULesFightCounterSystem::TriggerSlowMotionCounter()
{
    if (bSlowMotionActive) return;
    bSlowMotionActive = true;
    OnSlowMotionCounter.Broadcast();

    FTimerHandle Handle;
    if (OwnerManager.IsValid() && OwnerManager->GetWorld())
    {
        OwnerManager->GetWorld()->GetTimerManager().SetTimer(Handle,
            FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                bSlowMotionActive = false;
            }), 1.0f, false);
    }
}

void ULesFightCounterSystem::Reset()
{
    CloseCounterWindow();
    LastCounterAttempt = ECounterType::None;
    ConsecutiveCounters = 0;
    bSlowMotionActive = false;
}

void ULesFightCounterSystem::ProcessCounterResult(ECounterType CounterType, bool bSuccess)
{
    if (bSuccess)
    {
        OnCounterExecuted.Broadcast(CounterType);
        ApplyCounterEffects(CounterType);
    }
    else
    {
        OnCounterFailed.Broadcast(CounterType);
        ConsecutiveCounters = 0;
    }
}

bool ULesFightCounterSystem::IsPerfectCounter(ECounterType CounterType) const
{
    const FCounterWindowData* Data = CounterDefinitions.Find(CounterType);
    return Data && WindowTimer >= (Data->WindowDuration - Data->WindowOpenTime);
}

void ULesFightCounterSystem::ApplyCounterEffects(ECounterType CounterType)
{
}
