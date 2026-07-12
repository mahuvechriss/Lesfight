#include "LesFightAdvancedDodgeSystem.h"
#include "LesFightMartialArtsManager.h"

ULesFightAdvancedDodgeSystem::ULesFightAdvancedDodgeSystem()
    : bIsDodging(false)
    , CurrentDodge(EAdvancedDodgeType::None)
    , IFrameTimer(0.0f)
    , DodgeTimer(0.0f)
    , StaminaCostMultiplier(1.0f)
    , bPerfectDodgeWindow(false)
    , PerfectDodgeTimer(0.0f)
    , DodgeCooldown(0.0f)
{
}

void ULesFightAdvancedDodgeSystem::Initialize(ULesFightMartialArtsManager* InOwner)
{
    OwnerManager = InOwner;
    AvailableDodges = {
        EAdvancedDodgeType::DirectionalDodge,
        EAdvancedDodgeType::BackStep,
        EAdvancedDodgeType::SideEvade,
        EAdvancedDodgeType::RollingDodge
    };
}

void ULesFightAdvancedDodgeSystem::Tick(float DeltaTime)
{
    if (DodgeCooldown > 0.0f)
    {
        DodgeCooldown -= DeltaTime;
    }

    if (bIsDodging)
    {
        ProcessDodge(DeltaTime);
    }

    if (bPerfectDodgeWindow)
    {
        PerfectDodgeTimer -= DeltaTime;
        if (PerfectDodgeTimer <= 0.0f)
        {
            bPerfectDodgeWindow = false;
        }
    }
}

bool ULesFightAdvancedDodgeSystem::ExecuteDodge(EAdvancedDodgeType DodgeType)
{
    if (bIsDodging) return false;
    if (!AvailableDodges.Contains(DodgeType)) return false;
    if (DodgeCooldown > 0.0f) return false;

    CurrentDodge = DodgeType;
    bIsDodging = true;
    DodgeTimer = 0.0f;

    const FAdvancedDodgeData* Data = DodgeDefinitions.Find(DodgeType);
    if (Data)
    {
        DodgeCooldown = Data->Duration * 1.5f;
        ApplyIFrames();
    }

    if (IsPerfectDodge(DodgeType))
    {
        bPerfectDodgeWindow = true;
        PerfectDodgeTimer = Data ? Data->PerfectDodgeWindow : 0.1f;
        OnPerfectDodge.Broadcast(DodgeType);
    }

    OnDodgeExecuted.Broadcast(DodgeType);
    return true;
}

bool ULesFightAdvancedDodgeSystem::CanDodge(EAdvancedDodgeType DodgeType) const
{
    if (bIsDodging) return false;
    if (DodgeCooldown > 0.0f) return false;
    return AvailableDodges.Contains(DodgeType);
}

void ULesFightAdvancedDodgeSystem::CancelDodge()
{
    if (bIsDodging)
    {
        OnDodgeComplete();
    }
}

void ULesFightAdvancedDodgeSystem::SetDodgeData(
    const TMap<EAdvancedDodgeType, FAdvancedDodgeData>& Data)
{
    DodgeDefinitions = Data;
}

void ULesFightAdvancedDodgeSystem::SetAvailableDodges(
    const TArray<EAdvancedDodgeType>& Dodges)
{
    AvailableDodges = Dodges;
}

float ULesFightAdvancedDodgeSystem::GetDodgeDistance(EAdvancedDodgeType DodgeType) const
{
    const FAdvancedDodgeData* Found = DodgeDefinitions.Find(DodgeType);
    return Found ? Found->Distance : 0.0f;
}

float ULesFightAdvancedDodgeSystem::GetIFrameDuration(EAdvancedDodgeType DodgeType) const
{
    const FAdvancedDodgeData* Found = DodgeDefinitions.Find(DodgeType);
    return Found ? Found->IFrameDuration : 0.0f;
}

float ULesFightAdvancedDodgeSystem::GetPerfectDodgeWindow(EAdvancedDodgeType DodgeType) const
{
    const FAdvancedDodgeData* Found = DodgeDefinitions.Find(DodgeType);
    return Found ? Found->PerfectDodgeWindow : 0.0f;
}

void ULesFightAdvancedDodgeSystem::Reset()
{
    if (bIsDodging) OnDodgeComplete();
    bIsDodging = false;
    CurrentDodge = EAdvancedDodgeType::None;
    IFrameTimer = 0.0f;
    DodgeTimer = 0.0f;
    DodgeCooldown = 0.0f;
    bPerfectDodgeWindow = false;
}

void ULesFightAdvancedDodgeSystem::ProcessDodge(float DeltaTime)
{
    DodgeTimer += DeltaTime;

    if (IFrameTimer > 0.0f)
    {
        IFrameTimer -= DeltaTime;
        if (IFrameTimer <= 0.0f)
        {
            RemoveIFrames();
        }
    }

    const FAdvancedDodgeData* Data = DodgeDefinitions.Find(CurrentDodge);
    if (Data && DodgeTimer >= Data->Duration)
    {
        OnDodgeComplete();
    }
}

void ULesFightAdvancedDodgeSystem::OnDodgeComplete()
{
    bIsDodging = false;
    if (IFrameTimer > 0.0f)
    {
        RemoveIFrames();
    }
    CurrentDodge = EAdvancedDodgeType::None;
}

void ULesFightAdvancedDodgeSystem::ApplyIFrames()
{
    const FAdvancedDodgeData* Data = DodgeDefinitions.Find(CurrentDodge);
    IFrameTimer = Data ? Data->IFrameDuration : 0.2f;
}

void ULesFightAdvancedDodgeSystem::RemoveIFrames()
{
    IFrameTimer = 0.0f;
}

bool ULesFightAdvancedDodgeSystem::IsPerfectDodge(EAdvancedDodgeType DodgeType) const
{
    return false;
}
