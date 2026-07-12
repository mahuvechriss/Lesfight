#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightCharacterAuraSystem.generated.h"

class ULesFightVFXWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAuraActivated, ECharacterAuraType, Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAuraDeactivated, ECharacterAuraType, Type);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCharacterAuraSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void ActivateAura(ECharacterAuraType Type, AActor* Character);

    UFUNCTION(BlueprintCallable)
    void DeactivateAura(ECharacterAuraType Type);

    UFUNCTION(BlueprintCallable)
    void DeactivateAllAuras();

    UFUNCTION(BlueprintCallable)
    void UpdateAuras(float DeltaTime);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<ECharacterAuraType> GetActiveAuraTypes() const;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsAuraActive(ECharacterAuraType Type) const;

    UFUNCTION(BlueprintCallable)
    void SetAuraColor(FLinearColor Color);

    UFUNCTION(BlueprintCallable)
    void SetAuraIntensity(float Intensity);

    UFUNCTION(BlueprintCallable)
    void SetAuraPulse(bool bPulsating, float Speed);

    UPROPERTY(BlueprintAssignable)
    FOnAuraActivated OnAuraActivated;

    UPROPERTY(BlueprintAssignable)
    FOnAuraDeactivated OnAuraDeactivated;

protected:
    UPROPERTY()
    TMap<ECharacterAuraType, FCharacterAuraDef> AuraDefinitions;

    UPROPERTY()
    TMap<ECharacterAuraType, bool> ActiveAuras;

    UPROPERTY()
    TMap<ECharacterAuraType, float> AuraTimers;

    UPROPERTY()
    float GlobalAuraIntensity = 1.0f;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;

public:
    void Initialize(ULesFightVFXWorldManager* InManager);
};
