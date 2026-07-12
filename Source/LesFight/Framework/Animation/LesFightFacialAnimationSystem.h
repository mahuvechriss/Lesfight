#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightFacialAnimationSystem.generated.h"

class ULesFightCharacterAnimationComponent;
class ULesFightAnimBlueprintBase;

UCLASS(Blueprintable)
class ULesFightFacialAnimationSystem : public UObject
{
    GENERATED_BODY()

public:
    ULesFightFacialAnimationSystem();

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent,
        ULesFightAnimationDataAsset* AnimData);

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void Update(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void SetExpression(EFacialExpression Expression, float BlendTime = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void SetBlinkEnabled(bool bEnable) { bBlinkEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void SetEyeTrackingEnabled(bool bEnable) { bEyeTrackingEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void SetLipSyncEnabled(bool bEnable) { bLipSyncEnabled = bEnable; }

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void SetBlinkInterval(float Min, float Max);

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void SetEyeTarget(FVector TargetLocation);

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void TriggerLipSync(float Duration);

    UFUNCTION(BlueprintCallable, Category = "Facial Animation")
    void ResetFacial();

    UFUNCTION(BlueprintPure, Category = "Facial Animation")
    EFacialExpression GetCurrentExpression() const { return CurrentExpression; }

    UFUNCTION(BlueprintPure, Category = "Facial Animation")
    float GetBlinkAlpha() const { return BlinkAlpha; }

    UFUNCTION(BlueprintPure, Category = "Facial Animation")
    FVector GetEyeTarget() const { return EyeTarget; }

    UFUNCTION(BlueprintPure, Category = "Facial Animation")
    float GetLipSyncAlpha() const { return LipSyncAlpha; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    TMap<EFacialExpression, TObjectPtr<UAnimSequence>> ExpressionAnimations;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    EFacialExpression CurrentExpression;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    EFacialExpression TargetExpression;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    float ExpressionBlendTime;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    float ExpressionBlendProgress;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    float BlinkAlpha;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    FVector EyeTarget;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    float LipSyncAlpha;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Facial Animation")
    float BlinkSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Facial Animation")
    float EyeTrackingSpeed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Facial Animation")
    float LipSyncSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    bool bBlinkEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    bool bEyeTrackingEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "Facial Animation")
    bool bLipSyncEnabled;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TWeakObjectPtr<ULesFightAnimBlueprintBase> AnimBP;
    float BlinkTimer;
    float BlinkIntervalMin;
    float BlinkIntervalMax;
    float NextBlinkTime;
    bool bBlinking;
    float LipSyncTimer;

    void UpdateBlinking(float DeltaTime);
    void UpdateEyeTracking(float DeltaTime);
    void UpdateLipSync(float DeltaTime);
    void UpdateExpressionBlend(float DeltaTime);
};
