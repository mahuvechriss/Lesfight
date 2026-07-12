#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightUltimatePresentation.generated.h"

class ULesFightVFXWorldManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateStarted, FName, CharacterID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUltimateCompleted, FName, CharacterID, bool, bHit);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightUltimatePresentation : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void BeginUltimateSequence(FName CharacterID, AActor* Attacker, AActor* Target);

    UFUNCTION(BlueprintCallable)
    void PlayUltimateAttack(FVector Location);

    UFUNCTION(BlueprintCallable)
    void PlayUltimateImpact(FVector Location, AActor* Target);

    UFUNCTION(BlueprintCallable)
    void EndUltimateSequence();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsUltimatePlaying() const;

    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetUltimateProgress() const;

    UFUNCTION(BlueprintCallable)
    void SetUltimateStyle(EFightingStyle Style);

    UPROPERTY(BlueprintAssignable)
    FOnUltimateStarted OnUltimateStarted;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateCompleted OnUltimateCompleted;

protected:
    UPROPERTY()
    bool bUltimatePlaying = false;

    UPROPERTY()
    float UltimateProgress = 0.0f;

    UPROPERTY()
    EFightingStyle UltimateStyle = EFightingStyle::Karate;

    UPROPERTY()
    FName CurrentCharacterID;

    UPROPERTY()
    TMap<EFightingStyle, TArray<FString>> StyleUltimateEffects;

private:
    TWeakObjectPtr<ULesFightVFXWorldManager> OwnerManager;

public:
    void Initialize(ULesFightVFXWorldManager* InManager);
};
