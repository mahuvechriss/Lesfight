#include "LesFightMartialArtsManager.h"
#include "Styles/LesFightStyleManager.h"
#include "Styles/LesFightFightingStyle.h"
#include "Stances/LesFightStanceSystem.h"
#include "Movement/LesFightAdvancedMovement.h"
#include "Counters/LesFightCounterSystem.h"
#include "Dodge/LesFightAdvancedDodgeSystem.h"
#include "Combos/LesFightComboExpansionSystem.h"
#include "Environment/LesFightEnvironmentalCombat.h"
#include "Cinematic/LesFightCinematicCombat.h"
#include "Physics/LesFightPhysicsMotion.h"
#include "MotionMatching/LesFightMotionMatchingSystem.h"
#include "AIHooks/LesFightCombatAIHooks.h"
#include "Audio/LesFightMartialArtsAudio.h"
#include "VFX/LesFightMartialArtsVFX.h"
#include "HUD/LesFightMartialArtsHUD.h"
#include "Performance/LesFightMartialArtsPerformance.h"
#include "Testing/LesFightMartialArtsDevTools.h"

ULesFightMartialArtsManager::ULesFightMartialArtsManager()
    : bInitialized(false)
{
}

void ULesFightMartialArtsManager::Initialize()
{
    if (bInitialized) return;

    CreateSubManagers();
    InitializeSubManagers();
    ConfigureFromDataAsset();
    bInitialized = true;

    UE_LOG(LogLesFight, Log, TEXT("MartialArtsManager initialized"));
}

void ULesFightMartialArtsManager::InitializeWithOwner(AActor* InOwner)
{
    OwnerActor = InOwner;
    Initialize();
}

void ULesFightMartialArtsManager::Shutdown()
{
    if (!bInitialized) return;
    Reset();
    bInitialized = false;
}

void ULesFightMartialArtsManager::Tick(float DeltaTime)
{
    if (!bInitialized) return;

    if (StyleManager) StyleManager->Tick(DeltaTime);
    if (StanceSystem) StanceSystem->Tick(DeltaTime);
    if (AdvancedMovement) AdvancedMovement->Tick(DeltaTime);
    if (CounterSystem) CounterSystem->Tick(DeltaTime);
    if (DodgeSystem) DodgeSystem->Tick(DeltaTime);
    if (ComboExpansion) ComboExpansion->Tick(DeltaTime);
    if (EnvironmentSystem) EnvironmentSystem->Tick(DeltaTime);
    if (CinematicSystem) CinematicSystem->Tick(DeltaTime);
    if (PhysicsSystem) PhysicsSystem->Tick(DeltaTime);
    if (MotionMatching) MotionMatching->Tick(DeltaTime);
    if (AIHooks) AIHooks->Tick(DeltaTime);
    if (AudioSystem) AudioSystem->Tick(DeltaTime);
    if (VFXSystem) VFXSystem->Tick(DeltaTime);
    if (HUDSystem) HUDSystem->Tick(DeltaTime);
    if (Performance) Performance->Tick(DeltaTime);
    if (DevTools) DevTools->Tick(DeltaTime);
}

void ULesFightMartialArtsManager::SetDataAsset(ULesFightMartialArtsDataAsset* InDataAsset)
{
    DataAsset = InDataAsset;
    ConfigureFromDataAsset();
}

void ULesFightMartialArtsManager::SetOwner(AActor* InOwnerActor)
{
    OwnerActor = InOwnerActor;
}

UWorld* ULesFightMartialArtsManager::GetWorld() const
{
    if (OwnerActor.IsValid())
    {
        return OwnerActor->GetWorld();
    }
    return nullptr;
}

void ULesFightMartialArtsManager::Reset()
{
    if (StyleManager) StyleManager->ResetToDefault();
    if (StanceSystem) StanceSystem->ResetToNeutral();
    if (AdvancedMovement) AdvancedMovement->Reset();
    if (CounterSystem) CounterSystem->Reset();
    if (DodgeSystem) DodgeSystem->Reset();
    if (ComboExpansion) ComboExpansion->Reset();
    if (EnvironmentSystem) EnvironmentSystem->Reset();
    if (CinematicSystem) CinematicSystem->Reset();
    if (PhysicsSystem) PhysicsSystem->ResetPhysics();
    if (MotionMatching) MotionMatching->Reset();
    if (AudioSystem) AudioSystem->Reset();
    if (VFXSystem) VFXSystem->Reset();
    if (HUDSystem) HUDSystem->Reset();
    if (DevTools) DevTools->ResetDevSettings();

    UE_LOG(LogLesFight, Log, TEXT("MartialArtsManager reset"));
}

void ULesFightMartialArtsManager::CreateSubManagers()
{
    StyleManager = NewObject<ULesFightStyleManager>(this);
    StanceSystem = NewObject<ULesFightStanceSystem>(this);
    AdvancedMovement = NewObject<ULesFightAdvancedMovement>(this);
    CounterSystem = NewObject<ULesFightCounterSystem>(this);
    DodgeSystem = NewObject<ULesFightAdvancedDodgeSystem>(this);
    ComboExpansion = NewObject<ULesFightComboExpansionSystem>(this);
    EnvironmentSystem = NewObject<ULesFightEnvironmentalCombat>(this);
    CinematicSystem = NewObject<ULesFightCinematicCombat>(this);
    PhysicsSystem = NewObject<ULesFightPhysicsMotion>(this);
    MotionMatching = NewObject<ULesFightMotionMatchingSystem>(this);
    AIHooks = NewObject<ULesFightCombatAIHooks>(this);
    AudioSystem = NewObject<ULesFightMartialArtsAudio>(this);
    VFXSystem = NewObject<ULesFightMartialArtsVFX>(this);
    HUDSystem = NewObject<ULesFightMartialArtsHUD>(this);
    Performance = NewObject<ULesFightMartialArtsPerformance>(this);
    DevTools = NewObject<ULesFightMartialArtsDevTools>(this);
}

void ULesFightMartialArtsManager::InitializeSubManagers()
{
    if (StyleManager) { StyleManager->Initialize(this); StyleManager->SetStyleDataAsset(DataAsset); }
    if (StanceSystem) StanceSystem->Initialize(this);
    if (AdvancedMovement) AdvancedMovement->Initialize(this);
    if (CounterSystem) CounterSystem->Initialize(this);
    if (DodgeSystem) DodgeSystem->Initialize(this);
    if (ComboExpansion) ComboExpansion->Initialize(this);
    if (EnvironmentSystem) EnvironmentSystem->Initialize(this);
    if (CinematicSystem) CinematicSystem->Initialize(this);
    if (PhysicsSystem) PhysicsSystem->Initialize(this);
    if (MotionMatching) MotionMatching->Initialize(this);
    if (AIHooks) AIHooks->Initialize(this);
    if (AudioSystem) AudioSystem->Initialize(this);
    if (VFXSystem) VFXSystem->Initialize(this);
    if (HUDSystem) HUDSystem->Initialize(this);
    if (Performance) Performance->Initialize(this);
    if (DevTools) DevTools->Initialize(this);
}

void ULesFightMartialArtsManager::ConfigureFromDataAsset()
{
    if (!DataAsset) return;

    if (StanceSystem) StanceSystem->SetStanceData(DataAsset->StanceDefinitions);
    if (AdvancedMovement) AdvancedMovement->SetMovementData(DataAsset->MovementDefinitions);
    if (CounterSystem) CounterSystem->SetCounterData(DataAsset->CounterDefinitions);
    if (DodgeSystem) DodgeSystem->SetDodgeData(DataAsset->DodgeDefinitions);
    if (ComboExpansion) ComboExpansion->SetExpansionData(DataAsset->ComboDefinitions);
    if (EnvironmentSystem) EnvironmentSystem->SetEnvironmentData(DataAsset->EnvironmentDefinitions);
    if (CinematicSystem) CinematicSystem->SetCinematicData(DataAsset->CinematicDefinitions);
    if (PhysicsSystem) PhysicsSystem->SetPhysicsSettings(DataAsset->PhysicsSettings);
    if (MotionMatching) MotionMatching->SetMotionMatchingSettings(DataAsset->MotionMatchingSettings);

    if (Performance)
    {
        Performance->SetAnimationLOD(DataAsset->AnimationLODDistance);
        Performance->SetPhysicsLOD(DataAsset->PhysicsLODDistance);
        Performance->SetVFXLOD(DataAsset->VFXLODDistance);
    }
}
