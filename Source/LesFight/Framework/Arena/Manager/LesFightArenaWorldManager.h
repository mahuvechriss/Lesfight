#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightArenaWorldManager.generated.h"

class ULesFightArenaDataSystem;
class ULesFightArenaSelector;
class ULesFightArenaLoader;
class ULesFightArenaEnvironmentState;
class ULesFightArenaEnvironmentManager;
class ULesFightArenaWeatherSystem;
class ULesFightArenaLightingSystem;
class ULesFightArenaTerrainSystem;
class ULesFightArenaInteractionSystem;
class ULesFightArenaDestructibleObject;
class ULesFightArenaPhysicsObject;
class ULesFightArenaEffects;
class ULesFightArenaParticleManager;
class ULesFightArenaDebrisSystem;
class ULesFightArenaAudio;
class ULesFightArenaCamera;
class ULesFightArenaReplication;
class ULesFightArenaPerformance;
class ULesFightArenaDevTools;

UCLASS(Blueprintable, BlueprintType)
class LESFIGHT_API ULesFightArenaWorldManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    void LoadArena(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    void UnloadArena();

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    EArenaType GetCurrentArena() const { return CurrentArena; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    bool IsArenaLoaded() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    void SelectArena(EArenaType Arena);

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaDataSystem* GetDataSystem() const { return DataSystem; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaSelector* GetSelector() const { return Selector; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaLoader* GetLoader() const { return Loader; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaEnvironmentState* GetEnvironmentState() const { return EnvironmentState; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaEnvironmentManager* GetEnvManager() const { return EnvManager; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaWeatherSystem* GetWeatherSystem() const { return WeatherSystem; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaLightingSystem* GetLightingSystem() const { return LightingSystem; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaTerrainSystem* GetTerrainSystem() const { return TerrainSystem; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaInteractionSystem* GetInteractionSystem() const { return InteractionSystem; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaDestructibleObject* GetDestructibleObject() const { return DestructibleObject; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaPhysicsObject* GetPhysicsObject() const { return PhysicsObject; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaEffects* GetArenaEffects() const { return ArenaEffects; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaParticleManager* GetParticleManager() const { return ParticleManager; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaDebrisSystem* GetDebrisSystem() const { return DebrisSystem; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaAudio* GetArenaAudio() const { return ArenaAudio; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaCamera* GetArenaCamera() const { return ArenaCamera; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaReplication* GetArenaReplication() const { return ArenaReplication; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaPerformance* GetArenaPerformance() const { return ArenaPerformance; }

    UFUNCTION(BlueprintCallable, Category = "Arena|Manager")
    ULesFightArenaDevTools* GetArenaDevTools() const { return ArenaDevTools; }

protected:
    UPROPERTY()
    ULesFightArenaDataSystem* DataSystem;

    UPROPERTY()
    ULesFightArenaSelector* Selector;

    UPROPERTY()
    ULesFightArenaLoader* Loader;

    UPROPERTY()
    ULesFightArenaEnvironmentState* EnvironmentState;

    UPROPERTY()
    ULesFightArenaEnvironmentManager* EnvManager;

    UPROPERTY()
    ULesFightArenaWeatherSystem* WeatherSystem;

    UPROPERTY()
    ULesFightArenaLightingSystem* LightingSystem;

    UPROPERTY()
    ULesFightArenaTerrainSystem* TerrainSystem;

    UPROPERTY()
    ULesFightArenaInteractionSystem* InteractionSystem;

    UPROPERTY()
    ULesFightArenaDestructibleObject* DestructibleObject;

    UPROPERTY()
    ULesFightArenaPhysicsObject* PhysicsObject;

    UPROPERTY()
    ULesFightArenaEffects* ArenaEffects;

    UPROPERTY()
    ULesFightArenaParticleManager* ParticleManager;

    UPROPERTY()
    ULesFightArenaDebrisSystem* DebrisSystem;

    UPROPERTY()
    ULesFightArenaAudio* ArenaAudio;

    UPROPERTY()
    ULesFightArenaCamera* ArenaCamera;

    UPROPERTY()
    ULesFightArenaReplication* ArenaReplication;

    UPROPERTY()
    ULesFightArenaPerformance* ArenaPerformance;

    UPROPERTY()
    ULesFightArenaDevTools* ArenaDevTools;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager")
    bool bInitialized = false;

    UPROPERTY()
    EArenaType CurrentArena = EArenaType::None;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaDataSystem> DataSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaSelector> SelectorClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaLoader> LoaderClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaEnvironmentState> EnvironmentStateClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaEnvironmentManager> EnvManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaWeatherSystem> WeatherSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaLightingSystem> LightingSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaTerrainSystem> TerrainSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaInteractionSystem> InteractionSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaDestructibleObject> DestructibleObjectClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaPhysicsObject> PhysicsObjectClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaEffects> ArenaEffectsClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaParticleManager> ParticleManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaDebrisSystem> DebrisSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaAudio> ArenaAudioClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaCamera> ArenaCameraClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaReplication> ArenaReplicationClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaPerformance> ArenaPerformanceClass;

    UPROPERTY(EditDefaultsOnly, Category = "Arena|Manager|Config")
    TSubclassOf<ULesFightArenaDevTools> ArenaDevToolsClass;

private:
    template<typename T>
    T* CreateSubsystem(TSubclassOf<T> Subclass);
};
