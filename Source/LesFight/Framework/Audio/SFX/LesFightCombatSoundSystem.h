#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightCombatSoundSystem.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightCombatSoundSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    void HandleCombatEvent(ECombatSoundType Event, AActor* Instigator, AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    void HandleImpact(FVector Location, FVector Normal, float Force);

    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    void HandleBlock(AActor* Defender);

    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    void HandleCounter(AActor* Attacker);

    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    void HandleKnockdown(AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    void HandleGetUp(AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    void SetStyleAudioProfile(EFightingStyle Style);

    UFUNCTION(BlueprintCallable, Category = "CombatSFX")
    EFightingStyle GetStyleAudioProfile() const;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "CombatSFX")
    EFightingStyle CurrentStyle;

    UPROPERTY(BlueprintReadWrite, Category = "CombatSFX")
    TMap<EFightingStyle, TMap<ECombatSoundType, FString>> StyleSoundOverrides;

    UPROPERTY(BlueprintReadWrite, Category = "CombatSFX")
    TMap<EFightingStyle, FString> StyleAudioDescriptions;

private:
    TWeakObjectPtr<class ULesFightAudioWorldManager> OwnerManager;
};
