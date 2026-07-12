#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NiagaraSystem.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightNiagaraEffectManager.generated.h"

class ULesFightVFXWorldManager;

UCLASS(Blueprintable)
class ULesFightNiagaraEffectManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNiagaraEffectManager();

    UFUNCTION(BlueprintCallable)
    void Initialize();

    UFUNCTION(BlueprintCallable)
    void SpawnNiagaraSystem(FName SystemName, FTransform Transform);

    UFUNCTION(BlueprintCallable)
    void SpawnNiagaraAttached(FName SystemName, AActor* AttachActor, FName SocketName);

    UFUNCTION(BlueprintCallable)
    void DespawnNiagaraSystem(FName SystemName);

    UFUNCTION(BlueprintCallable)
    int32 GetActiveNiagaraCount() const;

    UFUNCTION(BlueprintCallable)
    void SetMaxNiagaraSystems(int32 Max);

    UFUNCTION(BlueprintCallable)
    void PreloadNiagaraSystem(FName SystemName);

    UFUNCTION(BlueprintCallable)
    void ReleaseNiagaraSystem(FName SystemName);

    UFUNCTION(BlueprintCallable)
    void ClearAllSystems();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TMap<FName, TSoftObjectPtr<UNiagaraSystem>> NiagaraLibrary;

    UPROPERTY()
    TArray<FName> ActiveSystems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 MaxSystems = 50;

    UPROPERTY()
    TMap<FName, int32> SystemUsageCount;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;
};
