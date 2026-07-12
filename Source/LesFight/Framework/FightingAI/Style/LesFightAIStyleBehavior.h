#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIStyleBehavior.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIStyleBehavior : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAIStyleBehavior();

    UFUNCTION(BlueprintCallable)
    void SetStyle(EFightingStyle Style);

    UFUNCTION(BlueprintCallable)
    EFightingStyle GetStyle() const { return CurrentStyle; }

    UFUNCTION(BlueprintCallable)
    FAIStyleBehaviorProfile GetStyleProfile() const { return CurrentProfile; }

    UFUNCTION(BlueprintCallable)
    void ModifyAggression(float Delta);

    UFUNCTION(BlueprintCallable)
    void ModifyDefense(float Delta);

    UFUNCTION(BlueprintCallable)
    FAIStyleBehaviorProfile GetBehaviorForSituation(const FAIPerceptionData& Perception) const;

    UFUNCTION(BlueprintCallable)
    FName GetPreferredCombo() const;

    UFUNCTION(BlueprintCallable)
    FString GetStyleDescription() const;

    UFUNCTION(BlueprintCallable)
    void OverrideProfile(const FAIStyleBehaviorProfile& Profile) { CurrentProfile = Profile; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Style")
    EFightingStyle CurrentStyle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Style")
    FAIStyleBehaviorProfile CurrentProfile;

    UPROPERTY()
    TMap<EFightingStyle, FAIStyleBehaviorProfile> StyleProfiles;

    UPROPERTY()
    TArray<FString> StyleDescriptions;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
