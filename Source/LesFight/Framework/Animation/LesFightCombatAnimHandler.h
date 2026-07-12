#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightCombatAnimHandler.generated.h"

class ULesFightCharacterAnimationComponent;
class ULesFightAnimBlueprintBase;
class ULesFightCombatComponent;

UCLASS(Blueprintable)
class ULesFightCombatAnimHandler : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCombatAnimHandler();

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void PlayAttackAnimation(const FAnimationMontageData& MontageData);

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void PlayBlockAnimation(bool bPerfect = false);

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void PlayDodgeAnimation();

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void PlayThrowAnimation(bool bIsAttacker = true);

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void PlayVictoryAnimation();

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void PlayDefeatAnimation();

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void PlayTauntAnimation(int32 TauntIndex = 0);

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void SetCombatAnimSet(const FCombatAnimSet& AnimSet);

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void StopCombatAnimation(float BlendOut = 0.2f);

    UFUNCTION(BlueprintCallable, Category = "Combat Animation")
    void SetCombatAnimType(ECombatAnimType Type);

    UFUNCTION(BlueprintPure, Category = "Combat Animation")
    ECombatAnimType GetCurrentType() const { return CurrentType; }

    UFUNCTION(BlueprintPure, Category = "Combat Animation")
    bool IsPlayingCombatAnim() const { return bPlayingCombatAnim; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Combat Animation")
    FCombatAnimSet CurrentAnimSet;

    UPROPERTY(BlueprintReadOnly, Category = "Combat Animation")
    ECombatAnimType CurrentType;

    UPROPERTY(BlueprintReadOnly, Category = "Combat Animation")
    bool bPlayingCombatAnim;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<ULesFightAnimBlueprintBase> AnimBP;
    TWeakObjectPtr<ULesFightCombatComponent> CombatComponent;

    UAnimMontage* FindAttackMontage(FName AttackID) const;
};
