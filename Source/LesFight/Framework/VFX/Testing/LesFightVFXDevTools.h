#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/VFX/Data/LesFightVFXData.h"
#include "LesFightVFXDevTools.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightVFXDevTools : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void EnableDebugMode(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void PlayTestImpact(EImpactVFXType Type);

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void PlayTestAura(ECharacterAuraType Type);

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void PlayTestMotionTrail(EMotionVFXType Type);

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void TestAllEffects();

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void TestCinematicSequence(ECinematicVFXEvent Event);

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void DisplayVFXStats();

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    void RunVFXStressTest(int32 EffectCount);

    UFUNCTION(BlueprintCallable, Category = "VFX Dev Tools")
    FString GenerateVFXReport() const;

    void Initialize(ULesFightVFXWorldManager* InOwner);

protected:
    UPROPERTY()
    bool bDebugMode;

    UPROPERTY()
    TArray<FString> TestLog;

    UPROPERTY()
    TMap<FString, float> TestResults;

    UPROPERTY()
    int32 MaxLogEntries;

private:
    TWeakObjectPtr<class ULesFightVFXWorldManager> OwnerManager;
};
