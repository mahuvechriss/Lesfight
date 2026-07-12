#include "Framework/Integration/Core/LesFightDependencyManager.h"

void ULesFightDependencyManager::Initialize()
{
    ResetAllModules();

    RegisterModule(ESystemModule::CoreFramework,         {});
    RegisterModule(ESystemModule::Character,             {ESystemModule::CoreFramework});
    RegisterModule(ESystemModule::Combat,                {ESystemModule::CoreFramework, ESystemModule::Character, ESystemModule::Animation});
    RegisterModule(ESystemModule::Animation,             {ESystemModule::CoreFramework, ESystemModule::Character});
    RegisterModule(ESystemModule::Network,               {ESystemModule::CoreFramework});
    RegisterModule(ESystemModule::MartialArts,           {ESystemModule::CoreFramework, ESystemModule::Combat, ESystemModule::Animation});
    RegisterModule(ESystemModule::CharacterCreation,     {ESystemModule::CoreFramework, ESystemModule::Character});
    RegisterModule(ESystemModule::AIPhotoToCharacter,    {ESystemModule::CoreFramework, ESystemModule::Character});
    RegisterModule(ESystemModule::FightingAI,            {ESystemModule::CoreFramework, ESystemModule::Combat, ESystemModule::MartialArts});
    RegisterModule(ESystemModule::Arena,                 {ESystemModule::CoreFramework});
    RegisterModule(ESystemModule::Audio,                 {ESystemModule::CoreFramework});
    RegisterModule(ESystemModule::VFX,                   {ESystemModule::CoreFramework, ESystemModule::Combat});
    RegisterModule(ESystemModule::UI,                    {ESystemModule::CoreFramework, ESystemModule::DataManager});
    RegisterModule(ESystemModule::DataManager,           {ESystemModule::CoreFramework});
}

void ULesFightDependencyManager::Shutdown()
{
    ResetAllModules();
}

void ULesFightDependencyManager::RegisterModule(ESystemModule Module, const TArray<ESystemModule>& Dependencies)
{
    FSystemModuleInfo Info;
    Info.ModuleID = Module;
    Info.ModuleName = FName(*UEnum::GetValueAsString(Module));
    Info.VersionString = TEXT("1.0.0");
    Info.bInitialized = false;
    Info.Dependencies = Dependencies;

    ModuleRegistry.Add(Module, Info);
}

TArray<ESystemModule> ULesFightDependencyManager::ResolveInitOrder()
{
    if (!ValidateDependencyGraph())
    {
        return TArray<ESystemModule>();
    }

    TMap<ESystemModule, int32> InDegree;
    TMap<ESystemModule, TArray<ESystemModule>> AdjacencyList;

    for (const auto& Entry : ModuleRegistry)
    {
        ESystemModule Module = Entry.Key;
        InDegree.Add(Module, 0);
        AdjacencyList.Add(Module, TArray<ESystemModule>());
    }

    for (const auto& Entry : ModuleRegistry)
    {
        ESystemModule Module = Entry.Key;
        for (ESystemModule Dep : Entry.Value.Dependencies)
        {
            if (AdjacencyList.Contains(Dep))
            {
                AdjacencyList[Dep].Add(Module);
                InDegree[Module]++;
            }
        }
    }

    TQueue<ESystemModule> Queue;
    for (const auto& Entry : InDegree)
    {
        if (Entry.Value == 0)
        {
            Queue.Enqueue(Entry.Key);
        }
    }

    TArray<ESystemModule> Result;
    while (!Queue.IsEmpty())
    {
        ESystemModule Current;
        Queue.Dequeue(Current);
        Result.Add(Current);

        for (ESystemModule Neighbor : AdjacencyList[Current])
        {
            InDegree[Neighbor]--;
            if (InDegree[Neighbor] == 0)
            {
                Queue.Enqueue(Neighbor);
            }
        }
    }

    if (Result.Num() != ModuleRegistry.Num())
    {
        return TArray<ESystemModule>();
    }

    InitOrder = Result;
    return Result;
}

bool ULesFightDependencyManager::IsModuleReady(ESystemModule Module) const
{
    return ReadyModules.Contains(Module);
}

void ULesFightDependencyManager::SetModuleReady(ESystemModule Module)
{
    ReadyModules.Add(Module);
    if (ModuleRegistry.Contains(Module))
    {
        ModuleRegistry[Module].bInitialized = true;
    }
    OnModuleReady.Broadcast(Module);
}

TArray<ESystemModule> ULesFightDependencyManager::GetUnresolvedDependencies(ESystemModule Module) const
{
    TArray<ESystemModule> Unresolved;
    if (const FSystemModuleInfo* Info = ModuleRegistry.Find(Module))
    {
        for (ESystemModule Dep : Info->Dependencies)
        {
            if (!ReadyModules.Contains(Dep))
            {
                Unresolved.Add(Dep);
            }
        }
    }
    return Unresolved;
}

bool ULesFightDependencyManager::ValidateDependencyGraph()
{
    TSet<ESystemModule> White;
    TSet<ESystemModule> Gray;
    TSet<ESystemModule> Black;

    for (const auto& Entry : ModuleRegistry)
    {
        White.Add(Entry.Key);
    }

    bool bHasCycle = false;

    TFunction<void(ESystemModule)> Dfs;
    Dfs = [&](ESystemModule Node)
    {
        White.Remove(Node);
        Gray.Add(Node);

        if (const FSystemModuleInfo* Info = ModuleRegistry.Find(Node))
        {
            for (ESystemModule Dep : Info->Dependencies)
            {
                if (Gray.Contains(Dep))
                {
                    bHasCycle = true;
                    return;
                }
                if (White.Contains(Dep))
                {
                    Dfs(Dep);
                    if (bHasCycle) return;
                }
            }
        }

        Gray.Remove(Node);
        Black.Add(Node);
    };

    for (ESystemModule Node : White)
    {
        Dfs(Node);
        if (bHasCycle) break;
    }

    return !bHasCycle;
}

float ULesFightDependencyManager::GetInitProgress() const
{
    if (ModuleRegistry.Num() == 0)
    {
        return 1.0f;
    }
    return static_cast<float>(ReadyModules.Num()) / static_cast<float>(ModuleRegistry.Num());
}

FSystemModuleInfo ULesFightDependencyManager::GetModuleInfo(ESystemModule Module) const
{
    if (const FSystemModuleInfo* Info = ModuleRegistry.Find(Module))
    {
        return *Info;
    }
    return FSystemModuleInfo();
}

TArray<FString> ULesFightDependencyManager::GetModuleStatus() const
{
    TArray<FString> StatusLines;
    for (const auto& Entry : ModuleRegistry)
    {
        FString Line = FString::Printf(TEXT("[%s] %s | Ready: %s | Dependencies: %d"),
            *UEnum::GetValueAsString(Entry.Key),
            *Entry.Value.ModuleName.ToString(),
            ReadyModules.Contains(Entry.Key) ? TEXT("Yes") : TEXT("No"),
            Entry.Value.Dependencies.Num());
        StatusLines.Add(Line);
    }
    return StatusLines;
}

void ULesFightDependencyManager::ResetAllModules()
{
    ModuleRegistry.Empty();
    ReadyModules.Empty();
    InitOrder.Empty();
}
