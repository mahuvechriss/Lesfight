#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIMovementPredictor.generated.h"

class ALesFightAIFighterController;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIMovementPredictor : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|MovementPredictor")
    void Initialize(ALesFightAIFighterController* InController);

    UFUNCTION(BlueprintCallable, Category = "AI|MovementPredictor")
    void PredictMovement(const FAIPerceptionData& Perception);

    UFUNCTION(BlueprintCallable, Category = "AI|MovementPredictor")
    FVector GetPredictedPosition(float TimeAhead) const;

    UFUNCTION(BlueprintCallable, Category = "AI|MovementPredictor")
    float GetPredictionConfidence() const;

    UFUNCTION(BlueprintCallable, Category = "AI|MovementPredictor")
    void SetPredictionHorizon(float Seconds);

    UFUNCTION(BlueprintCallable, Category = "AI|MovementPredictor")
    float GetPredictionHorizon() const;

    UFUNCTION(BlueprintCallable, Category = "AI|MovementPredictor")
    TArray<FVector> PredictPath(float TimeAhead, int32 SamplePoints);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|MovementPredictor")
    TArray<FVector> PredictedPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|MovementPredictor")
    float PredictionHorizon = 1.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|MovementPredictor")
    float PredictionConfidence = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|MovementPredictor")
    FVector LastKnownVelocity = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|MovementPredictor")
    int32 PathSamplePoints = 10;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;

    FVector CachedPredictedPosition;
};
