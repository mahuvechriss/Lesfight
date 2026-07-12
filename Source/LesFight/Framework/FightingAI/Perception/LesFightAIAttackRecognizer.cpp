#include "Framework/FightingAI/Perception/LesFightAIAttackRecognizer.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"

ULesFightAIAttackRecognizer::ULesFightAIAttackRecognizer()
{
    AttackTells.Add(EAIActionType::LightAttack, TEXT("Telegraph: Quick jab windup"));
    AttackTells.Add(EAIActionType::HeavyAttack, TEXT("Telegraph: Right punch windup"));
    AttackTells.Add(EAIActionType::ComboAttack, TEXT("Telegraph: Rapid stance shift"));
    AttackTells.Add(EAIActionType::SpecialMove, TEXT("Telegraph: Charging energy"));
    AttackTells.Add(EAIActionType::UltimateAttack, TEXT("Telegraph: Massive aura buildup"));
    AttackTells.Add(EAIActionType::Grab, TEXT("Telegraph: Reaching hand"));
    AttackTells.Add(EAIActionType::Throw, TEXT("Telegraph: Rotating grip"));
}

void ULesFightAIAttackRecognizer::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;
}

void ULesFightAIAttackRecognizer::RecognizeAttack(const FAIPerceptionData& Perception)
{
    bAttackPredicted = false;
    RecognizedAttack = EAIActionType::None;
    RecognitionConfidence = 0.0f;
    PredictedHitTime = 0.0f;
    AttackTell.Empty();

    if (Perception.RecentPlayerMoves.Num() == 0)
    {
        return;
    }

    const bool bMovingTowardAI = Perception.DetectedPlayerVelocity.Size() > 10.0f &&
        FVector::DotProduct(Perception.DetectedPlayerVelocity.GetSafeNormal(),
            Perception.DetectedPlayerLocation.GetSafeNormal()) > 0.3f;

    const bool bInAttackRange = Perception.DistanceToPlayer < 300.0f;

    if (!bMovingTowardAI && !bInAttackRange)
    {
        return;
    }

    float BaseConfidence = FMath::FRandRange(0.0f, 1.0f) < RecognitionAccuracy ? 1.0f : 0.0f;
    if (BaseConfidence < 0.5f)
    {
        return;
    }

    const FName LastMove = Perception.RecentPlayerMoves.Last();

    if (LastMove.ToString().Contains(TEXT("Light")) || LastMove.ToString().Contains(TEXT("light")))
    {
        RecognizedAttack = EAIActionType::LightAttack;
        RecognitionConfidence = FMath::FRandRange(0.7f, 0.95f) * RecognitionAccuracy;
        PredictedHitTime = Perception.TimeSinceLastPlayerAttack + 0.3f;
    }
    else if (LastMove.ToString().Contains(TEXT("Heavy")) || LastMove.ToString().Contains(TEXT("heavy")))
    {
        RecognizedAttack = EAIActionType::HeavyAttack;
        RecognitionConfidence = FMath::FRandRange(0.6f, 0.9f) * RecognitionAccuracy;
        PredictedHitTime = Perception.TimeSinceLastPlayerAttack + 0.6f;
    }
    else if (LastMove.ToString().Contains(TEXT("Combo")) || LastMove.ToString().Contains(TEXT("combo")))
    {
        RecognizedAttack = EAIActionType::ComboAttack;
        RecognitionConfidence = FMath::FRandRange(0.5f, 0.8f) * RecognitionAccuracy;
        PredictedHitTime = Perception.TimeSinceLastPlayerAttack + 0.8f;
    }
    else
    {
        RecognizedAttack = EAIActionType::LightAttack;
        RecognitionConfidence = FMath::FRandRange(0.4f, 0.6f) * RecognitionAccuracy;
        PredictedHitTime = Perception.TimeSinceLastPlayerAttack + 0.4f;
    }

    if (const FString* Tell = AttackTells.Find(RecognizedAttack))
    {
        AttackTell = *Tell;
    }

    bAttackPredicted = true;
    OnAttackRecognized.Broadcast(RecognizedAttack);
}

EAIActionType ULesFightAIAttackRecognizer::GetRecognizedAttackType() const
{
    return RecognizedAttack;
}

float ULesFightAIAttackRecognizer::GetRecognitionConfidence() const
{
    return RecognitionConfidence;
}

bool ULesFightAIAttackRecognizer::IsAttackPredicted() const
{
    return bAttackPredicted;
}

float ULesFightAIAttackRecognizer::GetPredictedAttackHitTime() const
{
    return PredictedHitTime;
}

FString ULesFightAIAttackRecognizer::GetAttackTell() const
{
    return AttackTell;
}

void ULesFightAIAttackRecognizer::SetRecognitionAccuracy(float Accuracy)
{
    RecognitionAccuracy = Accuracy;
}
