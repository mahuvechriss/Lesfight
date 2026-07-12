#include "LesFightVFXWorldManager.h"

#include "Framework/VFX/Camera/LesFightCameraEffects.h"
#include "Framework/VFX/PostProcessing/LesFightPostProcessingManager.h"
#include "Framework/VFX/Environment/LesFightEnvironmentalVFX.h"
#include "Framework/VFX/Environment/LesFightLightingEffects.h"
#include "Framework/VFX/Multiplayer/LesFightVFXReplication.h"
#include "Framework/VFX/Performance/LesFightVFXPerformance.h"
#include "Framework/VFX/Testing/LesFightVFXDevTools.h"

template<typename T>
T* ULesFightVFXWorldManager::CreateSubsystem(TSubclassOf<T> Class, UObject* Outer)
{
    if (!Class)
    {
        Class = T::StaticClass();
    }
    return NewObject<T>(Outer ? Outer : this, Class);
}

void ULesFightVFXWorldManager::Initialize()
{
    if (bInitialized) return;

    VFXManager = CreateSubsystem<ULesFightVFXManager>(VFXManagerClass, this);
    NiagaraEffectManager = CreateSubsystem<ULesFightNiagaraEffectManager>(NiagaraEffectManagerClass, this);
    VFXEventSystem = CreateSubsystem<ULesFightVFXEventSystem>(VFXEventSystemClass, this);
    ImpactEffectSystem = CreateSubsystem<ULesFightImpactEffectSystem>(ImpactEffectSystemClass, this);
    MartialArtsVFX = CreateSubsystem<ULesFightMartialArtsVFX>(MartialArtsVFXClass, this);
    MotionEffectSystem = CreateSubsystem<ULesFightMotionEffectSystem>(MotionEffectSystemClass, this);
    CharacterAuraSystem = CreateSubsystem<ULesFightCharacterAuraSystem>(CharacterAuraSystemClass, this);
    EnergyEffectSystem = CreateSubsystem<ULesFightEnergyEffectSystem>(EnergyEffectSystemClass, this);
    CinematicEffectManager = CreateSubsystem<ULesFightCinematicEffectManager>(CinematicEffectManagerClass, this);
    SlowMotionSystem = CreateSubsystem<ULesFightSlowMotionSystem>(SlowMotionSystemClass, this);
    UltimatePresentation = CreateSubsystem<ULesFightUltimatePresentation>(UltimatePresentationClass, this);
    CameraEffects = CreateSubsystem<ULesFightCameraEffects>(CameraEffectsClass, this);
    PostProcessingManager = CreateSubsystem<ULesFightPostProcessingManager>(PostProcessingManagerClass, this);
    EnvironmentalVFX = CreateSubsystem<ULesFightEnvironmentalVFX>(EnvironmentalVFXClass, this);
    LightingEffects = CreateSubsystem<ULesFightLightingEffects>(LightingEffectsClass, this);
    VFXReplication = CreateSubsystem<ULesFightVFXReplication>(VFXReplicationClass, this);
    VFXPerformance = CreateSubsystem<ULesFightVFXPerformance>(VFXPerformanceClass, this);
    VFXDevTools = CreateSubsystem<ULesFightVFXDevTools>(VFXDevToolsClass, this);

    VFXManager->Initialize(*this);
    NiagaraEffectManager->Initialize(*this);
    VFXEventSystem->Initialize(*this);
    ImpactEffectSystem->Initialize(*this);
    MartialArtsVFX->Initialize(*this);
    MotionEffectSystem->Initialize(*this);
    CharacterAuraSystem->Initialize(*this);
    EnergyEffectSystem->Initialize(*this);
    CinematicEffectManager->Initialize(*this);
    SlowMotionSystem->Initialize(*this);
    UltimatePresentation->Initialize(*this);
    CameraEffects->Initialize(this);
    PostProcessingManager->Initialize(this);
    EnvironmentalVFX->Initialize(this);
    LightingEffects->Initialize(this);
    VFXReplication->Initialize(this);
    VFXPerformance->Initialize(this);
    VFXDevTools->Initialize(this);

    bInitialized = true;
}

void ULesFightVFXWorldManager::Tick(float DeltaTime)
{
    if (!bInitialized) return;

    if (SlowMotionSystem)
    {
        SlowMotionSystem->UpdateSlowMotion(DeltaTime);
    }

    if (PostProcessingManager)
    {
        PostProcessingManager->UpdatePostProcess(DeltaTime);
    }

    if (CharacterAuraSystem)
    {
        CharacterAuraSystem->UpdateAuras(DeltaTime);
    }

    if (CameraEffects)
    {
    }

    if (VFXPerformance)
    {
    }

    if (VFXReplication)
    {
        VFXReplication->ProcessReplicatedVFX();
    }
}

void ULesFightVFXWorldManager::Shutdown()
{
    if (!bInitialized) return;

    EnvironmentalVFX->ClearEnvironmentalEffects();
    LightingEffects->ResetLighting();
    PostProcessingManager->ResetToDefault();
    CameraEffects->ResetCamera();

    VFXManager = nullptr;
    NiagaraEffectManager = nullptr;
    VFXEventSystem = nullptr;
    ImpactEffectSystem = nullptr;
    MartialArtsVFX = nullptr;
    MotionEffectSystem = nullptr;
    CharacterAuraSystem = nullptr;
    EnergyEffectSystem = nullptr;
    CinematicEffectManager = nullptr;
    SlowMotionSystem = nullptr;
    UltimatePresentation = nullptr;
    CameraEffects = nullptr;
    PostProcessingManager = nullptr;
    EnvironmentalVFX = nullptr;
    LightingEffects = nullptr;
    VFXReplication = nullptr;
    VFXPerformance = nullptr;
    VFXDevTools = nullptr;

    bInitialized = false;
}
