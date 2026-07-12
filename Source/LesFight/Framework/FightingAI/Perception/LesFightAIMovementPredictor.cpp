#include "Framework/FightingAI/Perception/LesFightAIMovementPredictor.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"

void ULesFightAIMovementPredictor::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;
}

void ULesFightAIMovementPredictor::PredictMovement(const FAIPerceptionData& Perception)
{
    const FVector CurrentPosition = Perception.DetectedPlayerLocation;
    const FVector CurrentVelocity = Perception.DetectedPlayerVelocity;

    LastKnownVelocity = CurrentVelocity;

    const float Speed = CurrentVelocity.Size();
    if (Speed < 1.0f)
    {
        CachedPredictedPosition = CurrentPosition;
        PredictionConfidence = 0.9f;
        return;
    }

    const FVector VelocityDir = CurrentVelocity.GetSafeNormal();
    const float PredictedDistance = Speed * PredictionHorizon;
    CachedPredictedPosition = CurrentPosition + VelocityDir * PredictedDistance;

    const float SpeedFactor = FMath::Clamp(Speed / 600.0f, 0.0f, 1.0f);
    const float TimeFactor = FMath::Clamp(1.0f - (PredictionHorizon / 3.0f), 0.0f, 1.0f);
    PredictionConfidence = SpeedFactor * TimeFactor * 0.9f;

    PredictedPath.Reset();
    const float TimeStep = PredictionHorizon / static_cast<float>(PathSamplePoints);
    for (int32 i = 0; i < PathSamplePoints; ++i)
    {
        const float T = static_cast<float>(i + 1) * TimeStep;
        const float DecayFactor = FMath::Clamp(1.0f - (T / PredictionHorizon) * 0.5f, 0.5f, 1.0f);
        const FVector Point = CurrentPosition + VelocityDir * (Speed * T * DecayFactor);
        PredictedPath.Add(Point);
    }
}

FVector ULesFightAIMovementPredictor::GetPredictedPosition(float TimeAhead) const
{
    if (TimeAhead <= 0.0f)
    {
        return FVector::ZeroVector;
    }

    const float Speed = LastKnownVelocity.Size();
    if (Speed < 1.0f)
    {
        return CachedPredictedPosition;
    }

    const FVector VelocityDir = LastKnownVelocity.GetSafeNormal();
    const float PredictedDistance = Speed * TimeAhead;
    return CachedPredictedPosition + VelocityDir * PredictedDistance;
}

float ULesFightAIMovementPredictor::GetPredictionConfidence() const
{
    return PredictionConfidence;
}

void ULesFightAIMovementPredictor::SetPredictionHorizon(float Seconds)
{
    PredictionHorizon = Seconds;
}

float ULesFightAIMovementPredictor::GetPredictionHorizon() const
{
    return PredictionHorizon;
}

TArray<FVector> ULesFightAIMovementPredictor::PredictPath(float TimeAhead, int32 SamplePoints)
{
    TArray<FVector> Path;
    if (SamplePoints <= 0)
    {
        return Path;
    }

    const float Speed = LastKnownVelocity.Size();
    if (Speed < 1.0f)
    {
        for (int32 i = 0; i < SamplePoints; ++i)
        {
            Path.Add(CachedPredictedPosition);
        }
        return Path;
    }

    const FVector VelocityDir = LastKnownVelocity.GetSafeNormal();
    const float TimeStep = TimeAhead / static_cast<float>(SamplePoints);

    for (int32 i = 0; i < SamplePoints; ++i)
    {
        const float T = static_cast<float>(i + 1) * TimeStep;
        const float DecayFactor = FMath::Clamp(1.0f - (T / TimeAhead) * 0.5f, 0.5f, 1.0f);
        const FVector Point = CachedPredictedPosition + VelocityDir * (Speed * T * DecayFactor);
        Path.Add(Point);
    }

    return Path;
}
