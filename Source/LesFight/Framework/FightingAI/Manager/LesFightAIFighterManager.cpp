#include "Framework/FightingAI/Manager/LesFightAIFighterManager.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"
#include "Framework/FightingAI/Integration/LesFightAIAnimationHandler.h"
#include "Framework/FightingAI/Integration/LesFightAIAudioHandler.h"
#include "Framework/FightingAI/Integration/LesFightAIPerformance.h"
#include "Framework/FightingAI/Testing/LesFightAIDevTools.h"

template<typename T>
T* ULesFightAIFighterManager::CreateSubsystem(TSubclassOf<T> Subclass)
{
    if (!Subclass)
    {
        return nullptr;
    }

    T* NewSubsystem = NewObject<T>(this, Subclass);
    return NewSubsystem;
}

void ULesFightAIFighterManager::Initialize()
{
    if (bInitialized)
    {
        return;
    }

    if (!AnimationHandlerClass)
    {
        AnimationHandlerClass = ULesFightAIAnimationHandler::StaticClass();
    }
    AnimationHandler = CreateSubsystem<ULesFightAIAnimationHandler>(AnimationHandlerClass);

    if (!AudioHandlerClass)
    {
        AudioHandlerClass = ULesFightAIAudioHandler::StaticClass();
    }
    AudioHandler = CreateSubsystem<ULesFightAIAudioHandler>(AudioHandlerClass);

    if (!PerformanceClass)
    {
        PerformanceClass = ULesFightAIPerformance::StaticClass();
    }
    Performance = CreateSubsystem<ULesFightAIPerformance>(PerformanceClass);

    if (!DevToolsClass)
    {
        DevToolsClass = ULesFightAIDevTools::StaticClass();
    }
    DevTools = CreateSubsystem<ULesFightAIDevTools>(DevToolsClass);

    bInitialized = true;
}

void ULesFightAIFighterManager::Shutdown()
{
    for (ALesFightAIFighterController* Controller : ActiveControllers)
    {
        if (Controller)
        {
            Controller->SetEnabled(false);
        }
    }

    ActiveControllers.Empty();

    AnimationHandler = nullptr;
    AudioHandler = nullptr;
    Performance = nullptr;
    DevTools = nullptr;

    bInitialized = false;
}

void ULesFightAIFighterManager::Tick(float DeltaTime)
{
    if (!bAllAIEnabled)
    {
        return;
    }

    for (ALesFightAIFighterController* Controller : ActiveControllers)
    {
        if (Controller && Controller->IsEnabled())
        {
            Controller->Tick(DeltaTime);
        }
    }
}

void ULesFightAIFighterManager::RegisterAIController(ALesFightAIFighterController* Controller)
{
    if (!Controller || ActiveControllers.Contains(Controller))
    {
        return;
    }

    ActiveControllers.Add(Controller);
    Controller->Initialize(this);
    Controller->SetEnabled(bAllAIEnabled);
}

void ULesFightAIFighterManager::UnregisterAIController(ALesFightAIFighterController* Controller)
{
    ActiveControllers.Remove(Controller);
}

TArray<ALesFightAIFighterController*> ULesFightAIFighterManager::GetActiveControllers() const
{
    return ActiveControllers;
}

void ULesFightAIFighterManager::SetGlobalDifficulty(EAIDifficulty Difficulty)
{
    GlobalDifficulty = Difficulty;
}

EAIDifficulty ULesFightAIFighterManager::GetGlobalDifficulty() const
{
    return GlobalDifficulty;
}

void ULesFightAIFighterManager::SetGlobalPersonality(EAIPersonalityType Personality)
{
    GlobalPersonality = Personality;
}

void ULesFightAIFighterManager::EnableAllAI(bool bEnabled)
{
    bAllAIEnabled = bEnabled;

    for (ALesFightAIFighterController* Controller : ActiveControllers)
    {
        if (Controller)
        {
            Controller->SetEnabled(bEnabled);
        }
    }
}

int32 ULesFightAIFighterManager::GetAICount() const
{
    return ActiveControllers.Num();
}

ULesFightAIAnimationHandler* ULesFightAIFighterManager::GetAnimationHandler() const
{
    return AnimationHandler;
}

ULesFightAIAudioHandler* ULesFightAIFighterManager::GetAudioHandler() const
{
    return AudioHandler;
}

ULesFightAIPerformance* ULesFightAIFighterManager::GetPerformance() const
{
    return Performance;
}

ULesFightAIDevTools* ULesFightAIFighterManager::GetDevTools() const
{
    return DevTools;
}
