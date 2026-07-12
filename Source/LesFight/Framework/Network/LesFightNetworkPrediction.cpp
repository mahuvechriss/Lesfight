#include "LesFightNetworkPrediction.h"
#include "LesFightMultiplayerManager.h"

ULesFightNetworkPrediction::ULesFightNetworkPrediction()
    : MaxPredictionFrames(64)
    , ReconciliationThreshold(10.0f)
    , bPredictionEnabled(true)
    , PredictedPosition(FVector::ZeroVector)
    , PredictedRotation(FRotator::ZeroRotator)
    , CurrentSequenceNumber(0)
    , InputAccumulator(0.0f)
    , bPredictionMismatch(false)
{
}

void ULesFightNetworkPrediction::Initialize(ULesFightMultiplayerManager* InManager)
{
    MultiplayerManager = InManager;
    PendingInputs.Empty();
    InputHistory.Empty();
    LastServerState = FServerState();
    CurrentSequenceNumber = 0;
}

void ULesFightNetworkPrediction::Tick(float DeltaTime)
{
    if (!bPredictionEnabled || !MultiplayerManager.IsValid()) return;

    InputAccumulator += DeltaTime;

    if (InputAccumulator >= (1.0f / 60.0f))
    {
        InputAccumulator = 0.0f;
        PredictNextState(1.0f / 60.0f);
    }
}

void ULesFightNetworkPrediction::QueueInput(const FName& InputAction, float InputValue)
{
    if (!bPredictionEnabled) return;

    FPredictedInput Input;
    Input.InputAction = InputAction;
    Input.InputValue = InputValue;
    Input.Timestamp = MultiplayerManager.IsValid() && MultiplayerManager->GetWorld()
        ? MultiplayerManager->GetWorld()->GetTimeSeconds() : 0.0f;
    Input.SequenceNumber = CurrentSequenceNumber++;

    PendingInputs.Add(Input);
    InputHistory.Add(Input);

    if (InputHistory.Num() > MaxPredictionFrames)
    {
        InputHistory.RemoveAt(0);
    }

    ApplyPredictedInput(Input);
}

void ULesFightNetworkPrediction::ReceiveServerState(const FServerState& State)
{
    if (!bPredictionEnabled) return;

    DetectPredictionMismatch(State);
    ReconcileWithServer(State);
    LastServerState = State;
}

void ULesFightNetworkPrediction::SetPredictionEnabled(bool bEnabled)
{
    bPredictionEnabled = bEnabled;
    if (!bEnabled)
    {
        ResetPrediction();
    }
}

void ULesFightNetworkPrediction::ResetPrediction()
{
    PendingInputs.Empty();
    InputHistory.Empty();
    CurrentSequenceNumber = 0;
    bPredictionMismatch = false;
    PredictedPosition = FVector::ZeroVector;
    PredictedRotation = FRotator::ZeroRotator;
}

void ULesFightNetworkPrediction::SetMaxPredictionFrames(int32 MaxFrames)
{
    MaxPredictionFrames = FMath::Clamp(MaxFrames, 8, 256);
}

void ULesFightNetworkPrediction::ClearPendingInputs()
{
    PendingInputs.Empty();
}

void ULesFightNetworkPrediction::ReconcileWithServer(const FServerState& ServerState)
{
    float PositionDiff = FVector::Dist(PredictedPosition, ServerState.Position);
    float RotationDiff = FMath::Abs((PredictedRotation - ServerState.Rotation).Yaw);

    if (PositionDiff > ReconciliationThreshold || RotationDiff > 5.0f)
    {
        PredictedPosition = ServerState.Position;
        PredictedRotation = ServerState.Rotation;
        bPredictionMismatch = true;

        TArray<FPredictedInput> UnprocessedInputs;
        for (const FPredictedInput& Input : InputHistory)
        {
            if (Input.SequenceNumber > ServerState.LastProcessedInput)
            {
                UnprocessedInputs.Add(Input);
            }
        }

        for (const FPredictedInput& Input : UnprocessedInputs)
        {
            ApplyPredictedInput(Input);
        }

        UE_LOG(LogLesFightNetwork, Verbose, TEXT("Reconciliation: pos diff %.1f, %d unprocessed"),
            PositionDiff, UnprocessedInputs.Num());
    }
}

void ULesFightNetworkPrediction::PredictNextState(float DeltaTime)
{
    for (const FPredictedInput& Input : PendingInputs)
    {
        ApplyPredictedInput(Input);
    }
    PendingInputs.Empty();
}

void ULesFightNetworkPrediction::ApplyPredictedInput(const FPredictedInput& Input)
{
    float MoveSpeed = 500.0f;
    float RotateSpeed = 180.0f;

    if (Input.InputAction == FName(TEXT("MoveForward")))
    {
        PredictedPosition += PredictedRotation.Vector() * Input.InputValue * MoveSpeed * 0.016f;
    }
    else if (Input.InputAction == FName(TEXT("MoveRight")))
    {
        PredictedPosition += FRotationMatrix(PredictedRotation).GetScaledAxis(EAxis::Y)
            * Input.InputValue * MoveSpeed * 0.016f;
    }
    else if (Input.InputAction == FName(TEXT("Turn")))
    {
        PredictedRotation.Yaw += Input.InputValue * RotateSpeed * 0.016f;
    }
}

void ULesFightNetworkPrediction::DetectPredictionMismatch(const FServerState& ServerState)
{
    float Diff = FVector::Dist(PredictedPosition, ServerState.Position);
    bPredictionMismatch = Diff > ReconciliationThreshold;
}
