#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightVFXWorldManager.generated.h"

class ULesFightVFXManager;
class ULesFightNiagaraEffectManager;
class ULesFightVFXEventSystem;
class ULesFightImpactEffectSystem;
class ULesFightMartialArtsVFX;
class ULesFightMotionEffectSystem;
class ULesFightCharacterAuraSystem;
class ULesFightEnergyEffectSystem;
class ULesFightCinematicEffectManager;
class ULesFightSlowMotionSystem;
class ULesFightUltimatePresentation;
class ULesFightCameraEffects;
class ULesFightPostProcessingManager;
class ULesFightEnvironmentalVFX;
class ULesFightLightingEffects;
class ULesFightVFXReplication;
class ULesFightVFXPerformance;
class ULesFightVFXDevTools;

UCLASS(Blueprintable, BlueprintType)
class LESFIGHT_API ULesFightVFXWorldManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightVFXManager* GetVFXManager() const { return VFXManager; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightNiagaraEffectManager* GetNiagaraEffectManager() const { return NiagaraEffectManager; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightVFXEventSystem* GetVFXEventSystem() const { return VFXEventSystem; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightImpactEffectSystem* GetImpactEffectSystem() const { return ImpactEffectSystem; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightMartialArtsVFX* GetMartialArtsVFX() const { return MartialArtsVFX; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightMotionEffectSystem* GetMotionEffectSystem() const { return MotionEffectSystem; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightCharacterAuraSystem* GetCharacterAuraSystem() const { return CharacterAuraSystem; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightEnergyEffectSystem* GetEnergyEffectSystem() const { return EnergyEffectSystem; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightCinematicEffectManager* GetCinematicEffectManager() const { return CinematicEffectManager; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightSlowMotionSystem* GetSlowMotionSystem() const { return SlowMotionSystem; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightUltimatePresentation* GetUltimatePresentation() const { return UltimatePresentation; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightCameraEffects* GetCameraEffects() const { return CameraEffects; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightPostProcessingManager* GetPostProcessingManager() const { return PostProcessingManager; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightEnvironmentalVFX* GetEnvironmentalVFX() const { return EnvironmentalVFX; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightLightingEffects* GetLightingEffects() const { return LightingEffects; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightVFXReplication* GetVFXReplication() const { return VFXReplication; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightVFXPerformance* GetVFXPerformance() const { return VFXPerformance; }

    UFUNCTION(BlueprintCallable, Category = "VFX World Manager")
    ULesFightVFXDevTools* GetVFXDevTools() const { return VFXDevTools; }

protected:
    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightVFXManager* VFXManager;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightNiagaraEffectManager* NiagaraEffectManager;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightVFXEventSystem* VFXEventSystem;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightImpactEffectSystem* ImpactEffectSystem;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightMartialArtsVFX* MartialArtsVFX;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightMotionEffectSystem* MotionEffectSystem;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightCharacterAuraSystem* CharacterAuraSystem;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightEnergyEffectSystem* EnergyEffectSystem;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightCinematicEffectManager* CinematicEffectManager;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightSlowMotionSystem* SlowMotionSystem;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightUltimatePresentation* UltimatePresentation;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightCameraEffects* CameraEffects;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightPostProcessingManager* PostProcessingManager;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightEnvironmentalVFX* EnvironmentalVFX;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightLightingEffects* LightingEffects;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightVFXReplication* VFXReplication;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightVFXPerformance* VFXPerformance;

    UPROPERTY(VisibleAnywhere, Category = "Subsystems")
    ULesFightVFXDevTools* VFXDevTools;

    UPROPERTY()
    bool bInitialized;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightVFXManager> VFXManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightNiagaraEffectManager> NiagaraEffectManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightVFXEventSystem> VFXEventSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightImpactEffectSystem> ImpactEffectSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightMartialArtsVFX> MartialArtsVFXClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightMotionEffectSystem> MotionEffectSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightCharacterAuraSystem> CharacterAuraSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightEnergyEffectSystem> EnergyEffectSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightCinematicEffectManager> CinematicEffectManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightSlowMotionSystem> SlowMotionSystemClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightUltimatePresentation> UltimatePresentationClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightCameraEffects> CameraEffectsClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightPostProcessingManager> PostProcessingManagerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightEnvironmentalVFX> EnvironmentalVFXClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightLightingEffects> LightingEffectsClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightVFXReplication> VFXReplicationClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightVFXPerformance> VFXPerformanceClass;

    UPROPERTY(EditDefaultsOnly, Category = "Config")
    TSubclassOf<ULesFightVFXDevTools> VFXDevToolsClass;

private:
    template<typename T>
    T* CreateSubsystem(TSubclassOf<T> Class, UObject* Outer);
};
