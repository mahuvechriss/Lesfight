#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Arena/Data/LesFightArenaData.h"
#include "LesFightParticleManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightParticleManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void SpawnParticleSystem(FName SystemName, FTransform Transform);

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void DespawnParticleSystem(FName SystemName);

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    int32 GetActiveParticleCount() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void SetMaxParticles(int32 MaxParticles);

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    int32 GetMaxParticles() const;

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void PauseAllParticles();

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void ResumeAllParticles();

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void ClearAllParticles();

    UFUNCTION(BlueprintCallable, Category = "Arena|Particles")
    void PreloadParticleSystem(FName SystemName);

protected:
    UPROPERTY()
    TMap<FName, FString> ParticleLibrary;

    UPROPERTY()
    TArray<FString> ActiveParticleSystems;

    UPROPERTY()
    int32 MaxParticles = 500;

    UPROPERTY()
    int32 ActiveCount = 0;

    UPROPERTY()
    bool bPaused = false;

private:
    TWeakObjectPtr<class ULesFightArenaWorldManager> OwnerManager;
};
