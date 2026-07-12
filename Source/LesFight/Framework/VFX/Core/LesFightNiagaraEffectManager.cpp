#include "Framework/VFX/Core/LesFightNiagaraEffectManager.h"
#include "Framework/VFX/Core/LesFightVFXWorldManager.h"

ULesFightNiagaraEffectManager::ULesFightNiagaraEffectManager()
{
}

void ULesFightNiagaraEffectManager::Initialize()
{
    NiagaraLibrary.Empty();
    ActiveSystems.Empty();
    SystemUsageCount.Empty();

    NiagaraLibrary.Add(TEXT("Impact_LightPunch"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_LightPunch.NS_Impact_LightPunch"))));
    NiagaraLibrary.Add(TEXT("Impact_HeavyPunch"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_HeavyPunch.NS_Impact_HeavyPunch"))));
    NiagaraLibrary.Add(TEXT("Impact_LightKick"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_LightKick.NS_Impact_LightKick"))));
    NiagaraLibrary.Add(TEXT("Impact_HeavyKick"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_HeavyKick.NS_Impact_HeavyKick"))));
    NiagaraLibrary.Add(TEXT("Impact_Special"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_Special.NS_Impact_Special"))));
    NiagaraLibrary.Add(TEXT("Impact_Ultimate"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_Ultimate.NS_Impact_Ultimate"))));
    NiagaraLibrary.Add(TEXT("Impact_Block"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_Block.NS_Impact_Block"))));
    NiagaraLibrary.Add(TEXT("Impact_Ground"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_Ground.NS_Impact_Ground"))));
    NiagaraLibrary.Add(TEXT("Impact_Wall"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Impact_Wall.NS_Impact_Wall"))));
    NiagaraLibrary.Add(TEXT("Trail_Punch"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Trail_Punch.NS_Trail_Punch"))));
    NiagaraLibrary.Add(TEXT("Trail_Kick"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Trail_Kick.NS_Trail_Kick"))));
    NiagaraLibrary.Add(TEXT("Trail_Dodge"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Trail_Dodge.NS_Trail_Dodge"))));
    NiagaraLibrary.Add(TEXT("Aura_Power"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Aura_Power.NS_Aura_Power"))));
    NiagaraLibrary.Add(TEXT("Aura_UltimateCharge"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Aura_UltimateCharge.NS_Aura_UltimateCharge"))));
    NiagaraLibrary.Add(TEXT("Aura_LowHealth"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Aura_LowHealth.NS_Aura_LowHealth"))));
    NiagaraLibrary.Add(TEXT("Aura_Victory"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Aura_Victory.NS_Aura_Victory"))));
    NiagaraLibrary.Add(TEXT("Dust_Cloud"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Dust_Cloud.NS_Dust_Cloud"))));
    NiagaraLibrary.Add(TEXT("Shockwave"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Shockwave.NS_Shockwave"))));
    NiagaraLibrary.Add(TEXT("Energy_Wave"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Energy_Wave.NS_Energy_Wave"))));
    NiagaraLibrary.Add(TEXT("Sparks"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Sparks.NS_Sparks"))));
    NiagaraLibrary.Add(TEXT("Debris"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Debris.NS_Debris"))));
    NiagaraLibrary.Add(TEXT("Leaves"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Leaves.NS_Leaves"))));
    NiagaraLibrary.Add(TEXT("Rain_Splash"), TSoftObjectPtr<UNiagaraSystem>(FSoftObjectPath(TEXT("/Game/VFX/Niagara/NS_Rain_Splash.NS_Rain_Splash"))));
}

void ULesFightNiagaraEffectManager::SpawnNiagaraSystem(FName SystemName, FTransform Transform)
{
    if (ActiveSystems.Num() >= MaxSystems)
    {
        return;
    }

    TSoftObjectPtr<UNiagaraSystem>* Found = NiagaraLibrary.Find(SystemName);
    if (!Found)
    {
        return;
    }

    ActiveSystems.Add(SystemName);
    int32& Count = SystemUsageCount.FindOrAdd(SystemName);
    Count++;
}

void ULesFightNiagaraEffectManager::SpawnNiagaraAttached(FName SystemName, AActor* AttachActor, FName SocketName)
{
    if (!AttachActor || ActiveSystems.Num() >= MaxSystems)
    {
        return;
    }

    TSoftObjectPtr<UNiagaraSystem>* Found = NiagaraLibrary.Find(SystemName);
    if (!Found)
    {
        return;
    }

    ActiveSystems.Add(SystemName);
    int32& Count = SystemUsageCount.FindOrAdd(SystemName);
    Count++;
}

void ULesFightNiagaraEffectManager::DespawnNiagaraSystem(FName SystemName)
{
    ActiveSystems.Remove(SystemName);

    int32* Count = SystemUsageCount.Find(SystemName);
    if (Count && *Count > 0)
    {
        (*Count)--;
    }
}

int32 ULesFightNiagaraEffectManager::GetActiveNiagaraCount() const
{
    return ActiveSystems.Num();
}

void ULesFightNiagaraEffectManager::SetMaxNiagaraSystems(int32 Max)
{
    MaxSystems = FMath::Max(1, Max);
}

void ULesFightNiagaraEffectManager::PreloadNiagaraSystem(FName SystemName)
{
    TSoftObjectPtr<UNiagaraSystem>* Found = NiagaraLibrary.Find(SystemName);
    if (Found)
    {
        Found->LoadSynchronous();
    }
}

void ULesFightNiagaraEffectManager::ReleaseNiagaraSystem(FName SystemName)
{
    NiagaraLibrary.Remove(SystemName);
    ActiveSystems.Remove(SystemName);
    SystemUsageCount.Remove(SystemName);
}

void ULesFightNiagaraEffectManager::ClearAllSystems()
{
    ActiveSystems.Empty();
    SystemUsageCount.Empty();
}
