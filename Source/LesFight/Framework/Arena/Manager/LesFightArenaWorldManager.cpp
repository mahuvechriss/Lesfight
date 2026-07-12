#include "LesFightArenaWorldManager.h"

#include "Framework/Arena/Data/LesFightArenaDataSystem.h"
#include "Framework/Arena/Selector/LesFightArenaSelector.h"
#include "Framework/Arena/Loader/LesFightArenaLoader.h"
#include "Framework/Arena/Environment/LesFightArenaEnvironmentState.h"
#include "Framework/Arena/Environment/LesFightArenaEnvironmentManager.h"
#include "Framework/Arena/Environment/Weather/LesFightArenaWeatherSystem.h"
#include "Framework/Arena/Environment/Lighting/LesFightArenaLightingSystem.h"
#include "Framework/Arena/Terrain/LesFightArenaTerrainSystem.h"
#include "Framework/Arena/Interaction/LesFightArenaInteractionSystem.h"
#include "Framework/Arena/Interaction/Destruction/LesFightArenaDestructibleObject.h"
#include "Framework/Arena/Interaction/Physics/LesFightArenaPhysicsObject.h"
#include "Framework/Arena/Effects/LesFightArenaEffects.h"
#include "Framework/Arena/Effects/Particles/LesFightArenaParticleManager.h"
#include "Framework/Arena/Effects/Debris/LesFightArenaDebrisSystem.h"
#include "Framework/Arena/Audio/LesFightArenaAudio.h"
#include "Framework/Arena/Camera/LesFightArenaCamera.h"
#include "Framework/Arena/Multiplayer/LesFightArenaReplication.h"
#include "Framework/Arena/Performance/LesFightArenaPerformance.h"
#include "Framework/Arena/Testing/LesFightArenaDevTools.h"

template<typename T>
T* ULesFightArenaWorldManager::CreateSubsystem(TSubclassOf<T> Subclass)
{
    if (!Subclass) return nullptr;

    T* NewSubsystem = NewObject<T>(this, Subclass);
    if (NewSubsystem)
    {
        NewSubsystem->Initialize(this);
    }
    return NewSubsystem;
}

void ULesFightArenaWorldManager::Initialize()
{
    if (bInitialized) return;

    DataSystem = CreateSubsystem(DataSystemClass);
    Selector = CreateSubsystem(SelectorClass);
    Loader = CreateSubsystem(LoaderClass);
    EnvironmentState = CreateSubsystem(EnvironmentStateClass);
    EnvManager = CreateSubsystem(EnvManagerClass);
    WeatherSystem = CreateSubsystem(WeatherSystemClass);
    LightingSystem = CreateSubsystem(LightingSystemClass);
    TerrainSystem = CreateSubsystem(TerrainSystemClass);
    InteractionSystem = CreateSubsystem(InteractionSystemClass);
    DestructibleObject = CreateSubsystem(DestructibleObjectClass);
    PhysicsObject = CreateSubsystem(PhysicsObjectClass);
    ArenaEffects = CreateSubsystem(ArenaEffectsClass);
    ParticleManager = CreateSubsystem(ParticleManagerClass);
    DebrisSystem = CreateSubsystem(DebrisSystemClass);
    ArenaAudio = CreateSubsystem(ArenaAudioClass);
    ArenaCamera = CreateSubsystem(ArenaCameraClass);
    ArenaReplication = CreateSubsystem(ArenaReplicationClass);
    ArenaPerformance = CreateSubsystem(ArenaPerformanceClass);
    ArenaDevTools = CreateSubsystem(ArenaDevToolsClass);

    bInitialized = true;
}

void ULesFightArenaWorldManager::Shutdown()
{
    if (!bInitialized) return;

    if (Loader && Loader->IsArenaLoaded())
    {
        Loader->UnloadArena();
    }

    DataSystem = nullptr;
    Selector = nullptr;
    Loader = nullptr;
    EnvironmentState = nullptr;
    EnvManager = nullptr;
    WeatherSystem = nullptr;
    LightingSystem = nullptr;
    TerrainSystem = nullptr;
    InteractionSystem = nullptr;
    DestructibleObject = nullptr;
    PhysicsObject = nullptr;
    ArenaEffects = nullptr;
    ParticleManager = nullptr;
    DebrisSystem = nullptr;
    ArenaAudio = nullptr;
    ArenaCamera = nullptr;
    ArenaReplication = nullptr;
    ArenaPerformance = nullptr;
    ArenaDevTools = nullptr;

    bInitialized = false;
    CurrentArena = EArenaType::None;
}

void ULesFightArenaWorldManager::Tick(float DeltaTime)
{
    if (!bInitialized) return;

    if (WeatherSystem)
    {
        WeatherSystem->Tick(DeltaTime);
    }

    if (LightingSystem)
    {
        LightingSystem->Tick(DeltaTime);
    }

    if (ArenaEffects)
    {
        ArenaEffects->Tick(DeltaTime);
    }

    if (ParticleManager)
    {
        ParticleManager->Tick(DeltaTime);
    }

    if (DebrisSystem)
    {
        DebrisSystem->Tick(DeltaTime);
    }

    if (ArenaCamera)
    {
        ArenaCamera->Tick(DeltaTime);
    }

    if (ArenaPerformance)
    {
        ArenaPerformance->GetCurrentMetrics();
    }

    if (ArenaReplication)
    {
        ArenaReplication->ProcessPendingUpdates();
    }
}

void ULesFightArenaWorldManager::LoadArena(EArenaType Arena)
{
    if (!bInitialized || !Loader) return;

    if (Loader->IsArenaLoaded())
    {
        Loader->UnloadArena();
    }

    CurrentArena = Arena;
    Loader->LoadArena(Arena);

    if (EnvironmentState)
    {
        EnvironmentState->InitializeForArena(Arena);
    }

    if (EnvManager)
    {
        EnvManager->ApplyEnvironmentState(EnvironmentState);
    }

    if (WeatherSystem)
    {
        WeatherSystem->InitializeForArena(Arena);
    }

    if (LightingSystem)
    {
        LightingSystem->InitializeForArena(Arena);
    }

    if (TerrainSystem)
    {
        TerrainSystem->GenerateTerrain(Arena);
    }

    if (ArenaEffects)
    {
        ArenaEffects->InitializeForArena(Arena);
    }

    if (ArenaAudio)
    {
        ArenaAudio->LoadArenaAudio(Arena);
    }

    if (ArenaCamera)
    {
        ArenaCamera->InitializeForArena(Arena);
    }
}

void ULesFightArenaWorldManager::UnloadArena()
{
    if (!bInitialized || !Loader) return;

    Loader->UnloadArena();
    CurrentArena = EArenaType::None;
}

bool ULesFightArenaWorldManager::IsArenaLoaded() const
{
    return Loader && Loader->IsArenaLoaded() && CurrentArena != EArenaType::None;
}

void ULesFightArenaWorldManager::SelectArena(EArenaType Arena)
{
    if (!bInitialized || !Selector) return;

    CurrentArena = Selector->SelectArena(Arena);
}
