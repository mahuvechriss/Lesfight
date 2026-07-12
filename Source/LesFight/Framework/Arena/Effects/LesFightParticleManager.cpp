#include "Framework/Arena/Effects/LesFightParticleManager.h"

void ULesFightParticleManager::Initialize()
{
    ParticleLibrary.Add(TEXT("Rain"), TEXT("/Game/Effects/Particles/Weather/Rain"));
    ParticleLibrary.Add(TEXT("Snow"), TEXT("/Game/Effects/Particles/Weather/Snow"));
    ParticleLibrary.Add(TEXT("Fog"), TEXT("/Game/Effects/Particles/Weather/Fog"));
    ParticleLibrary.Add(TEXT("Dust"), TEXT("/Game/Effects/Particles/Weather/Dust"));
    ParticleLibrary.Add(TEXT("Leaves"), TEXT("/Game/Effects/Particles/Weather/Leaves"));
    ParticleLibrary.Add(TEXT("Sparks"), TEXT("/Game/Effects/Particles/Combat/Sparks"));
    ParticleLibrary.Add(TEXT("Fire"), TEXT("/Game/Effects/Particles/Combat/Fire"));
    ParticleLibrary.Add(TEXT("Smoke"), TEXT("/Game/Effects/Particles/Combat/Smoke"));
    ParticleLibrary.Add(TEXT("Debris"), TEXT("/Game/Effects/Particles/Combat/Debris"));
    ParticleLibrary.Add(TEXT("Impact_Stone"), TEXT("/Game/Effects/Particles/Impacts/Impact_Stone"));
    ParticleLibrary.Add(TEXT("Impact_Wood"), TEXT("/Game/Effects/Particles/Impacts/Impact_Wood"));
    ParticleLibrary.Add(TEXT("Impact_Metal"), TEXT("/Game/Effects/Particles/Impacts/Impact_Metal"));
    ParticleLibrary.Add(TEXT("Destruction_Small"), TEXT("/Game/Effects/Particles/Destruction/Destruction_Small"));
    ParticleLibrary.Add(TEXT("Destruction_Large"), TEXT("/Game/Effects/Particles/Destruction/Destruction_Large"));
}

void ULesFightParticleManager::SpawnParticleSystem(FName SystemName, FTransform Transform)
{
    if (ActiveCount >= MaxParticles)
    {
        return;
    }

    FString* Path = ParticleLibrary.Find(SystemName);
    if (Path)
    {
        ActiveParticleSystems.Add(*Path);
        ++ActiveCount;
    }
}

void ULesFightParticleManager::DespawnParticleSystem(FName SystemName)
{
    FString* Path = ParticleLibrary.Find(SystemName);
    if (Path)
    {
        ActiveParticleSystems.Remove(*Path);
        --ActiveCount;
    }
}

int32 ULesFightParticleManager::GetActiveParticleCount() const
{
    return ActiveCount;
}

void ULesFightParticleManager::SetMaxParticles(int32 Max)
{
    MaxParticles = Max;
}

int32 ULesFightParticleManager::GetMaxParticles() const
{
    return MaxParticles;
}

void ULesFightParticleManager::PauseAllParticles()
{
    bPaused = true;
}

void ULesFightParticleManager::ResumeAllParticles()
{
    bPaused = false;
}

void ULesFightParticleManager::ClearAllParticles()
{
    ActiveParticleSystems.Empty();
    ActiveCount = 0;
}

void ULesFightParticleManager::PreloadParticleSystem(FName SystemName)
{
    FString* Path = ParticleLibrary.Find(SystemName);
    if (Path)
    {
    }
}
