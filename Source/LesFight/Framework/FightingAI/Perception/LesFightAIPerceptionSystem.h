#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIPerceptionSystem.generated.h"

class ALesFightAIFighterController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetDetected, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetLost);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIPerceptionSystem : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    void Initialize(ALesFightAIFighterController* InController);

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    void UpdatePerception(AActor* Self, AActor* Target, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    const FAIPerceptionData& GetCurrentPerception() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    bool IsTargetDetected() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    float GetDetectionConfidence() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    void SetDetectionRange(float Range);

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    float GetDetectionRange() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    void SetFieldOfView(float Degrees);

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    float GetFieldOfView() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    bool IsTargetInRange() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    bool IsTargetInFOV() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Perception")
    float GetLastDetectionTime() const;

    UPROPERTY(BlueprintAssignable, Category = "AI|Perception|Events")
    FOnTargetDetected OnTargetDetected;

    UPROPERTY(BlueprintAssignable, Category = "AI|Perception|Events")
    FOnTargetLost OnTargetLost;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
    FAIPerceptionData CurrentPerception;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception")
    float DetectionRange = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception")
    float FieldOfView = 120.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
    float LastDetectionTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Perception")
    float DetectionUpdateInterval = 0.1f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Perception")
    bool bTargetDetected = false;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;
    float TimeSinceLastUpdate = 0.0f;
};
