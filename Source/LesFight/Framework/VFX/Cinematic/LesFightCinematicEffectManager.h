#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightCinematicEffectManager.generated.h"

class ULesFightVFXWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCinematicVFXEvent, ECinematicVFXEvent, Event);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCinematicEffectManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void PlayCinematicEvent(ECinematicVFXEvent Event, FVector Location, AActor* Character);

    UFUNCTION(BlueprintCallable)
    void PlayRoundStart(FVector Location);

    UFUNCTION(BlueprintCallable)
    void PlayRoundEnd(FVector Location, AActor* Winner);

    UFUNCTION(BlueprintCallable)
    void PlayUltimateSequence(AActor* Attacker, AActor* Target);

    UFUNCTION(BlueprintCallable)
    void PlayFinisherSequence(AActor* Attacker, AActor* Target);

    UFUNCTION(BlueprintCallable)
    void PlayVictoryEffect(AActor* Winner);

    UFUNCTION(BlueprintCallable)
    void SetCinematicMode(bool bEnabled);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsCinematicMode() const;

    UPROPERTY(BlueprintAssignable)
    FOnCinematicVFXEvent OnCinematicVFXEvent;

protected:
    UPROPERTY()
    bool bCinematicMode = false;

    UPROPERTY()
    TMap<ECinematicVFXEvent, TArray<FString>> CinematicEffectPaths;

    UPROPERTY()
    TMap<ECinematicVFXEvent, FCameraEffectDef> CinematicCameraEffects;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;

public:
    void Initialize(ULesFightVFXWorldManager* InManager);
};
