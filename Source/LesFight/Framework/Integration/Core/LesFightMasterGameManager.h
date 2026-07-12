#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Integration/Core/LesFightIntegrationDataTypes.h"
#include "LesFightMasterGameManager.generated.h"

// Integration subsystem forward declarations
class ULesFightGameFlowController;
class ULesFightSystemCommunicationManager;
class ULesFightEventCoordinationSystem;
class ULesFightLoadingManager;
class ULesFightDependencyManager;
class ULesFightIntegrationTestSuite;
class ULesFightIntegrationDevTools;

// Module manager forward declarations
class ULesFightUIManager;
class ULesFightDataManager;
class ULesFightVFXWorldManager;
class ULesFightAudioWorldManager;
class ULesFightArenaWorldManager;
class ULesFightFightingAIWorldManager;
class ULesFightCharacterWorldManager;
class ULesFightCombatWorldManager;
class ULesFightNetworkWorldManager;
class ULesFightMartialArtsManager;
class ULesFightCharacterCreationWorldManager;
class ULesFightAIPhotoToCharacterWorldManager;
class ULesFightAnimationWorldManager;
class ULesFightSettingsManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameReady);

UCLASS(Blueprintable, BlueprintType)
class LESFIGHT_API ULesFightMasterGameManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Integration|MasterManager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Integration|MasterManager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Integration|MasterManager")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Integration|MasterManager")
    void StartGame();

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager")
    bool IsGameReady() const { return bGameReady; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager")
    FString GetGameVersion() const { return GameVersion; }

    // Integration subsystem getters
    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Subsystems")
    ULesFightGameFlowController* GetGameFlowController() const { return GameFlowController; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Subsystems")
    ULesFightSystemCommunicationManager* GetSystemCommunicationManager() const { return SystemCommunicationManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Subsystems")
    ULesFightEventCoordinationSystem* GetEventCoordinationSystem() const { return EventCoordinationSystem; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Subsystems")
    ULesFightLoadingManager* GetLoadingManager() const { return LoadingManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Subsystems")
    ULesFightDependencyManager* GetDependencyManager() const { return DependencyManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Subsystems")
    ULesFightIntegrationTestSuite* GetIntegrationTestSuite() const { return IntegrationTestSuite; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Subsystems")
    ULesFightIntegrationDevTools* GetIntegrationDevTools() const { return IntegrationDevTools; }

    // Module manager getters
    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightUIManager* GetUIManager() const { return UIManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightDataManager* GetDataManager() const { return DataManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightVFXWorldManager* GetVFXWorldManager() const { return VFXWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightAudioWorldManager* GetAudioManager() const { return AudioWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightArenaWorldManager* GetArenaManager() const { return ArenaWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightFightingAIWorldManager* GetFightingAIManager() const { return FightingAIWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightCharacterWorldManager* GetCharacterManager() const { return CharacterWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightCombatWorldManager* GetCombatManager() const { return CombatWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightNetworkWorldManager* GetNetworkManager() const { return NetworkWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightMartialArtsManager* GetMartialArtsManager() const { return MartialArtsManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightCharacterCreationWorldManager* GetCharacterCreationManager() const { return CharacterCreationWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightAIPhotoToCharacterWorldManager* GetAIPhotoToCharacterManager() const { return AIPhotoToCharacterWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightAnimationWorldManager* GetAnimationManager() const { return AnimationWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightAudioWorldManager* GetAudioSystemManager() const { return AudioWorldManager; }

    UFUNCTION(BlueprintPure, Category = "Integration|MasterManager|Modules")
    ULesFightSettingsManager* GetSettingsManager() const { return SettingsManager; }

    UFUNCTION(BlueprintCallable, Category = "Integration|MasterManager")
    TArray<FString> GetAllModuleStatus();

    UFUNCTION(BlueprintCallable, Category = "Integration|MasterManager")
    void RestartGame();

    UPROPERTY(BlueprintAssignable, Category = "Integration|MasterManager")
    FOnGameReady OnGameReady;

protected:
    // Integration subsystems
    UPROPERTY(VisibleAnywhere, Category = "Integration|Subsystems")
    ULesFightGameFlowController* GameFlowController;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Subsystems")
    ULesFightSystemCommunicationManager* SystemCommunicationManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Subsystems")
    ULesFightEventCoordinationSystem* EventCoordinationSystem;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Subsystems")
    ULesFightLoadingManager* LoadingManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Subsystems")
    ULesFightDependencyManager* DependencyManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Subsystems")
    ULesFightIntegrationTestSuite* IntegrationTestSuite;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Subsystems")
    ULesFightIntegrationDevTools* IntegrationDevTools;

    // Module managers
    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightUIManager* UIManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightDataManager* DataManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightVFXWorldManager* VFXWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightAudioWorldManager* AudioWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightArenaWorldManager* ArenaWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightFightingAIWorldManager* FightingAIWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightCharacterWorldManager* CharacterWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightCombatWorldManager* CombatWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightNetworkWorldManager* NetworkWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightMartialArtsManager* MartialArtsManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightCharacterCreationWorldManager* CharacterCreationWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightAIPhotoToCharacterWorldManager* AIPhotoToCharacterWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightAnimationWorldManager* AnimationWorldManager;

    UPROPERTY(VisibleAnywhere, Category = "Integration|Modules")
    ULesFightSettingsManager* SettingsManager;

    UPROPERTY()
    bool bGameReady = false;

    UPROPERTY()
    bool bInitialized = false;

    // Subsystem class config
    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    TSubclassOf<ULesFightGameFlowController> GameFlowControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    TSubclassOf<ULesFightSystemCommunicationManager> SystemCommunicationManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    TSubclassOf<ULesFightEventCoordinationSystem> EventCoordinationSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    TSubclassOf<ULesFightLoadingManager> LoadingManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    TSubclassOf<ULesFightDependencyManager> DependencyManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    TSubclassOf<ULesFightIntegrationTestSuite> IntegrationTestSuiteClass;

    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    TSubclassOf<ULesFightIntegrationDevTools> IntegrationDevToolsClass;

    UPROPERTY(EditDefaultsOnly, Category = "Integration|Config")
    FString GameVersion = TEXT("1.0.0");

private:
    template<typename T>
    T* CreateSubsystem(TSubclassOf<T> Class, UObject* Outer)
    {
        if (Class)
        {
            return NewObject<T>(Outer, Class);
        }
        return nullptr;
    }
};
