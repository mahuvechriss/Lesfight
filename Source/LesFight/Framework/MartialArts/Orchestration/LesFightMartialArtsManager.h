#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/LesFightMartialArtsData.h"
#include "LesFightMartialArtsManager.generated.h"

UCLASS(Blueprintable)
class ULesFightMartialArtsManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightMartialArtsManager();

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    void InitializeWithOwner(AActor* InOwner);

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    void SetDataAsset(ULesFightMartialArtsDataAsset* DataAsset);

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    void SetOwner(AActor* InOwnerActor);

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightStyleManager* GetStyleManager() const { return StyleManager; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightStanceSystem* GetStanceSystem() const { return StanceSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightAdvancedMovement* GetAdvancedMovement() const { return AdvancedMovement; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightCounterSystem* GetCounterSystem() const { return CounterSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightAdvancedDodgeSystem* GetDodgeSystem() const { return DodgeSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightComboExpansionSystem* GetComboExpansion() const { return ComboExpansion; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightEnvironmentalCombat* GetEnvironmentSystem() const { return EnvironmentSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightCinematicCombat* GetCinematicSystem() const { return CinematicSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightPhysicsMotion* GetPhysicsSystem() const { return PhysicsSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightMotionMatchingSystem* GetMotionMatching() const { return MotionMatching; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightCombatAIHooks* GetAIHooks() const { return AIHooks; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightMartialArtsAudio* GetAudioSystem() const { return AudioSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightMartialArtsVFX* GetVFXSystem() const { return VFXSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightMartialArtsHUD* GetHUDSystem() const { return HUDSystem; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightMartialArtsPerformance* GetPerformance() const { return Performance; }

    UFUNCTION(BlueprintPure, Category = "MartialArts|SubManagers")
    class ULesFightMartialArtsDevTools* GetDevTools() const { return DevTools; }

    UFUNCTION(BlueprintPure, Category = "MartialArts")
    AActor* GetOwnerActor() const { return OwnerActor.Get(); }

    UFUNCTION(BlueprintPure, Category = "MartialArts")
    UWorld* GetWorld() const override;

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    bool IsInitialized() const { return bInitialized; }

    UFUNCTION(BlueprintCallable, Category = "MartialArts")
    void Reset();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightStyleManager> StyleManager;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightStanceSystem> StanceSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightAdvancedMovement> AdvancedMovement;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightCounterSystem> CounterSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightAdvancedDodgeSystem> DodgeSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightComboExpansionSystem> ComboExpansion;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightEnvironmentalCombat> EnvironmentSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightCinematicCombat> CinematicSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightPhysicsMotion> PhysicsSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightMotionMatchingSystem> MotionMatching;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightCombatAIHooks> AIHooks;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightMartialArtsAudio> AudioSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightMartialArtsVFX> VFXSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightMartialArtsHUD> HUDSystem;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightMartialArtsPerformance> Performance;

    UPROPERTY(BlueprintReadOnly, Category = "SubManagers")
    TObjectPtr<class ULesFightMartialArtsDevTools> DevTools;

    UPROPERTY(BlueprintReadOnly, Category = "Configuration")
    TObjectPtr<class ULesFightMartialArtsDataAsset> DataAsset;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bInitialized;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TWeakObjectPtr<AActor> OwnerActor;

private:
    void CreateSubManagers();
    void InitializeSubManagers();
    void ConfigureFromDataAsset();
};
