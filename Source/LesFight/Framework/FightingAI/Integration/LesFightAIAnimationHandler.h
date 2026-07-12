#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIAnimationHandler.generated.h"

class ALesFightAIFighterController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationComplete, FName, AnimationName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimationBlendOut, FName, AnimationName);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIAnimationHandler : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    void PlayAnimation(const FAIDecisionContext& Decision);

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    FName GetCurrentAnimationName() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    bool IsAnimationPlaying() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    float GetAnimationProgress() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    void SetAnimationSpeed(float Speed);

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    void BlendToAnimation(FName AnimationName, float BlendTime);

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    void HandleAnimationEvent(EAIAnimationEvent Event);

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    bool CanPlayAnimation(FName AnimationName) const;

    UFUNCTION(BlueprintCallable, Category = "AI|Animation")
    FName GetMontageSection(FName MontageName) const;

    UPROPERTY(BlueprintAssignable, Category = "AI|Animation")
    FOnAnimationComplete OnAnimationComplete;

    UPROPERTY(BlueprintAssignable, Category = "AI|Animation")
    FOnAnimationBlendOut OnAnimationBlendOut;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Animation")
    FName CurrentAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Animation")
    float AnimationSpeed = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Animation")
    float BlendTime = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Animation")
    TMap<EAIActionType, FName> ActionAnimations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Animation")
    TMap<EAIAnimationEvent, FName> EventAnimations;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Animation")
    bool bAnimationPlaying = false;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;
};
