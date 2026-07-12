#include "Framework/Integration/Core/LesFightMasterGameManager.h"
#include "Framework/Integration/Core/LesFightGameFlowController.h"
#include "Framework/Integration/Core/LesFightSystemCommunicationManager.h"
#include "Framework/Integration/Core/LesFightDependencyManager.h"
#include "Framework/Integration/Core/LesFightEventCoordinationSystem.h"
#include "Framework/Integration/Core/LesFightLoadingManager.h"
#include "Framework/Integration/Core/LesFightIntegrationTestSuite.h"
#include "Framework/Integration/Core/LesFightIntegrationDevTools.h"
#include "Framework/Data/Core/LesFightDataManager.h"

void ULesFightMasterGameManager::Initialize()
{
    if (bInitialized)
    {
        return;
    }

    // 1. Create all 7 integration subsystems
    GameFlowController = CreateSubsystem(GameFlowControllerClass, this);
    SystemCommunicationManager = CreateSubsystem(SystemCommunicationManagerClass, this);
    EventCoordinationSystem = CreateSubsystem(EventCoordinationSystemClass, this);
    LoadingManager = CreateSubsystem(LoadingManagerClass, this);
    DependencyManager = CreateSubsystem(DependencyManagerClass, this);
    IntegrationTestSuite = CreateSubsystem(IntegrationTestSuiteClass, this);
    IntegrationDevTools = CreateSubsystem(IntegrationDevToolsClass, this);

    if (!DependencyManager || !SystemCommunicationManager || !GameFlowController || !LoadingManager)
    {
        return;
    }

    // 2. Initialize DependencyManager (registers all modules)
    DependencyManager->Initialize();

    // 3. Initialize SystemCommunicationManager
    SystemCommunicationManager->Initialize();

    // 4. Initialize GameFlowController
    GameFlowController->Initialize();

    // 5. Initialize LoadingManager
    LoadingManager->Initialize();

    // 6. Initialize EventCoordinationSystem
    if (EventCoordinationSystem)
    {
        EventCoordinationSystem->Initialize();
    }

    // 7. Resolve init order from DependencyManager
    DependencyManager->RegisterModule(ESystemModule::CoreFramework,     { });
    DependencyManager->RegisterModule(ESystemModule::Character,         { ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::Animation,         { ESystemModule::Character });
    DependencyManager->RegisterModule(ESystemModule::Combat,            { ESystemModule::Character, ESystemModule::Animation });
    DependencyManager->RegisterModule(ESystemModule::Network,           { ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::MartialArts,       { ESystemModule::Character, ESystemModule::Animation });
    DependencyManager->RegisterModule(ESystemModule::CharacterCreation, { ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::AIPhotoToCharacter,{ ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::FightingAI,        { ESystemModule::Character, ESystemModule::Combat });
    DependencyManager->RegisterModule(ESystemModule::Arena,             { ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::Audio,             { ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::VFX,               { ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::UI,                { ESystemModule::CoreFramework });
    DependencyManager->RegisterModule(ESystemModule::DataManager,       { ESystemModule::CoreFramework });

    TArray<ESystemModule> InitOrder = DependencyManager->ResolveInitOrder();

    // 8. Initialize each module in order (stub - actual init delegated to their world managers)
    for (ESystemModule Module : InitOrder)
    {
        DependencyManager->SetModuleReady(Module);
    }

    // 9. Set all modules as ready in DependencyManager
    DependencyManager->ValidateDependencyGraph();

    // 10. Load persistent data via DataManager
    if (DataManager)
    {
        DataManager->LoadAllData(TEXT("DefaultProfile"));
    }

    // 11. Set game ready
    bGameReady = true;
    bInitialized = true;
    OnGameReady.Broadcast();

    // 12. Begin flow
    if (GameFlowController)
    {
        GameFlowController->SetState(EGameFlowState::Loading);
    }
}

void ULesFightMasterGameManager::Shutdown()
{
    if (!bInitialized)
    {
        return;
    }

    if (LoadingManager)
    {
        LoadingManager->Shutdown();
    }

    if (EventCoordinationSystem)
    {
        EventCoordinationSystem->Shutdown();
    }

    if (GameFlowController)
    {
        GameFlowController->Shutdown();
    }

    if (SystemCommunicationManager)
    {
        SystemCommunicationManager->Shutdown();
    }

    if (DependencyManager)
    {
        DependencyManager->Shutdown();
    }

    if (IntegrationTestSuite)
    {
        IntegrationTestSuite->Shutdown();
    }

    if (IntegrationDevTools)
    {
        IntegrationDevTools->Shutdown();
    }

    if (DataManager)
    {
        DataManager->Shutdown();
    }

    bGameReady = false;
    bInitialized = false;
}

void ULesFightMasterGameManager::Tick(float DeltaTime)
{
    if (!bInitialized)
    {
        return;
    }

    if (LoadingManager)
    {
        LoadingManager->Tick(DeltaTime);
    }

    if (SystemCommunicationManager)
    {
        SystemCommunicationManager->Tick(DeltaTime);
    }
}

void ULesFightMasterGameManager::StartGame()
{
    if (!bGameReady)
    {
        return;
    }

    if (GameFlowController)
    {
        GameFlowController->SetState(EGameFlowState::Loading);
    }
}

TArray<FString> ULesFightMasterGameManager::GetAllModuleStatus()
{
    if (DependencyManager)
    {
        return DependencyManager->GetModuleStatus();
    }
    return { };
}

void ULesFightMasterGameManager::RestartGame()
{
    Shutdown();
    Initialize();
}
