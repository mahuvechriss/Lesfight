#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightNetworkPrediction.generated.h"

USTRUCT()
struct FPredictedInput
{
    GENERATED_BODY()

    FName InputAction;
    float InputValue;
    float Timestamp;
    uint32 SequenceNumber;

    FPredictedInput()
        : InputAction(NAME_None)
        , InputValue(0.0f)
        , Timestamp(0.0f)
        , SequenceNumber(0)
    {}
};

USTRUCT()
struct FServerState
{
    GENERATED_BODY()

    FVector Position;
    FRotator Rotation;
    FVector Velocity;
    bool bIsGrounded;
    float Timestamp;
    uint32 LastProcessedInput;

    FServerState()
        : Position(FVector::ZeroVector)
        , Rotation(FRotator::ZeroRotator)
        , Velocity(FVector::ZeroVector)
        , bIsGrounded(true)
        , Timestamp(0.0f)
        , LastProcessedInput(0)
    {}
};

UCLASS(Blueprintable)
class ULesFightNetworkPrediction : public UObject
{
    GENERATED_BODY()

public:
    ULesFightNetworkPrediction();

    void Initialize(ULesFightMultiplayerManager* InManager);
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    void QueueInput(const FName& InputAction, float InputValue);

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    void ReceiveServerState(const FServerState& State);

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    FVector GetPredictedPosition() const { return PredictedPosition; }

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    FRotator GetPredictedRotation() const { return PredictedRotation; }

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    void SetPredictionEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    bool IsPredictionEnabled() const { return bPredictionEnabled; }

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    void ResetPrediction();

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    void SetMaxPredictionFrames(int32 MaxFrames);

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    int32 GetPendingInputCount() const { return PendingInputs.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Network|Prediction")
    void ClearPendingInputs();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    int32 MaxPredictionFrames;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    float ReconciliationThreshold;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration")
    bool bPredictionEnabled;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FVector PredictedPosition;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    FRotator PredictedRotation;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    TArray<FPredictedInput> PendingInputs;

private:
    TWeakObjectPtr<ULesFightMultiplayerManager> MultiplayerManager;
    FServerState LastServerState;
    TArray<FPredictedInput> InputHistory;
    uint32 CurrentSequenceNumber;
    float InputAccumulator;
    bool bPredictionMismatch;

    void ReconcileWithServer(const FServerState& ServerState);
    void PredictNextState(float DeltaTime);
    void ApplyPredictedInput(const FPredictedInput& Input);
    void DetectPredictionMismatch(const FServerState& ServerState);
};
