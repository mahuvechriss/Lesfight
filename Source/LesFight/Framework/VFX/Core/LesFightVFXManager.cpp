#include "Framework/VFX/Core/LesFightVFXManager.h"
#include "Framework/VFX/Core/LesFightVFXWorldManager.h"

ULesFightVFXManager::ULesFightVFXManager()
{
}

void ULesFightVFXManager::Initialize()
{
    ActiveEffects.Empty();
    bPaused = false;
    bInitialized = true;

    if (OnVFXInitialized.IsBound())
    {
        OnVFXInitialized.Broadcast();
    }
}

void ULesFightVFXManager::PlayEffect(FName EffectName, FVector Location, FRotator Rotation)
{
    if (!bInitialized)
    {
        OnVFXError.Broadcast(TEXT("VFXManager not initialized"));
        return;
    }

    if (ActiveEffects.Num() >= MaxActiveEffects)
    {
        OnVFXError.Broadcast(FString::Printf(TEXT("Max active effects reached: %d"), MaxActiveEffects));
        return;
    }

    ActiveEffects.Add(EffectName, GlobalVFXScale);
}

void ULesFightVFXManager::StopEffect(FName EffectName)
{
    ActiveEffects.Remove(EffectName);
}

void ULesFightVFXManager::StopAllEffects()
{
    ActiveEffects.Empty();
}

void ULesFightVFXManager::PauseAllEffects()
{
    bPaused = true;
}

void ULesFightVFXManager::ResumeAllEffects()
{
    bPaused = false;
}

int32 ULesFightVFXManager::GetActiveEffectCount() const
{
    return ActiveEffects.Num();
}

void ULesFightVFXManager::SetGlobalVFXScale(float Scale)
{
    GlobalVFXScale = FMath::Max(0.0f, Scale);

    for (TPair<FName, float>& Entry : ActiveEffects)
    {
        Entry.Value = GlobalVFXScale;
    }
}

bool ULesFightVFXManager::IsEffectPlaying(FName EffectName) const
{
    return ActiveEffects.Contains(EffectName);
}
