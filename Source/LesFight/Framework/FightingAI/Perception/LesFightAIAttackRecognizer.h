#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIAttackRecognizer.generated.h"

class ALesFightAIFighterController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackRecognized, EAIActionType, AttackType);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIAttackRecognizer : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAIAttackRecognizer();

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    void Initialize(ALesFightAIFighterController* InController);

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    void RecognizeAttack(const FAIPerceptionData& Perception);

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    EAIActionType GetRecognizedAttackType() const;

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    float GetRecognitionConfidence() const;

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    bool IsAttackPredicted() const;

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    float GetPredictedAttackHitTime() const;

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    FString GetAttackTell() const;

    UFUNCTION(BlueprintCallable, Category = "AI|AttackRecognizer")
    void SetRecognitionAccuracy(float Accuracy);

    UPROPERTY(BlueprintAssignable, Category = "AI|AttackRecognizer|Events")
    FOnAttackRecognized OnAttackRecognized;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AttackRecognizer")
    EAIActionType RecognizedAttack = EAIActionType::None;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AttackRecognizer")
    float RecognitionConfidence = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AttackRecognizer")
    float PredictedHitTime = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AttackRecognizer")
    FString AttackTell;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AttackRecognizer")
    bool bAttackPredicted = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|AttackRecognizer")
    float RecognitionAccuracy = 0.8f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AttackRecognizer")
    TMap<EAIActionType, FString> AttackTells;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;
};
