#include "Framework/FightingAI/Perception/LesFightAIPerceptionSystem.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void ULesFightAIPerceptionSystem::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;
}

void ULesFightAIPerceptionSystem::UpdatePerception(AActor* Self, AActor* Target, float DeltaTime)
{
    if (!Self || !Target)
    {
        if (bTargetDetected)
        {
            bTargetDetected = false;
            OnTargetLost.Broadcast();
        }
        return;
    }

    TimeSinceLastUpdate += DeltaTime;
    if (TimeSinceLastUpdate < DetectionUpdateInterval)
    {
        return;
    }
    TimeSinceLastUpdate = 0.0f;

    const FVector SelfLocation = Self->GetActorLocation();
    const FVector TargetLocation = Target->GetActorLocation();
    const FVector SelfForward = Self->GetActorForwardVector();
    const FVector ToTarget = TargetLocation - SelfLocation;
    const float Distance = ToTarget.Size();
    const FVector ToTargetNormalized = ToTarget.GetSafeNormal();

    const float DotProduct = FVector::DotProduct(SelfForward, ToTargetNormalized);
    const float AngleDegrees = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

    CurrentPerception.DetectedPlayerLocation = TargetLocation;
    CurrentPerception.DistanceToPlayer = Distance;
    CurrentPerception.AngleToPlayer = AngleDegrees;

    ACharacter* TargetCharacter = Cast<ACharacter>(Target);
    if (TargetCharacter && TargetCharacter->GetCharacterMovement())
    {
        CurrentPerception.DetectedPlayerVelocity = TargetCharacter->GetCharacterMovement()->Velocity;
    }
    else
    {
        CurrentPerception.DetectedPlayerVelocity = FVector::ZeroVector;
    }

    const bool bInRange = Distance <= DetectionRange;
    const bool bInFOV = AngleDegrees <= (FieldOfView * 0.5f);

    if (bInRange && bInFOV)
    {
        if (!bTargetDetected)
        {
            OnTargetDetected.Broadcast(Target);
        }
        bTargetDetected = true;
        LastDetectionTime = Self->GetWorld() ? Self->GetWorld()->GetTimeSeconds() : 0.0f;
        CurrentPerception.DetectionConfidence = FMath::Min(1.0f, CurrentPerception.DetectionConfidence + DeltaTime * 2.0f);
    }
    else
    {
        CurrentPerception.DetectionConfidence = FMath::Max(0.0f, CurrentPerception.DetectionConfidence - DeltaTime * 0.5f);
        if (CurrentPerception.DetectionConfidence <= 0.0f && bTargetDetected)
        {
            bTargetDetected = false;
            OnTargetLost.Broadcast();
        }
    }

    ACharacter* SelfCharacter = Cast<ACharacter>(Self);
    if (TargetCharacter)
    {
        if (UClass* HealthInterface = TargetCharacter->GetClass()->ImplementsInterface(UHealthInterface::StaticClass()))
        {
            CurrentPerception.PlayerHealthPercent = 1.0f;
        }

        if (UClass* StaminaInterface = TargetCharacter->GetClass()->ImplementsInterface(UStaminaInterface::StaticClass()))
        {
            CurrentPerception.PlayerStaminaPercent = 1.0f;
        }
    }
}

const FAIPerceptionData& ULesFightAIPerceptionSystem::GetCurrentPerception() const
{
    return CurrentPerception;
}

bool ULesFightAIPerceptionSystem::IsTargetDetected() const
{
    return bTargetDetected;
}

float ULesFightAIPerceptionSystem::GetDetectionConfidence() const
{
    return CurrentPerception.DetectionConfidence;
}

void ULesFightAIPerceptionSystem::SetDetectionRange(float Range)
{
    DetectionRange = Range;
}

float ULesFightAIPerceptionSystem::GetDetectionRange() const
{
    return DetectionRange;
}

void ULesFightAIPerceptionSystem::SetFieldOfView(float Degrees)
{
    FieldOfView = Degrees;
}

float ULesFightAIPerceptionSystem::GetFieldOfView() const
{
    return FieldOfView;
}

bool ULesFightAIPerceptionSystem::IsTargetInRange() const
{
    return CurrentPerception.DistanceToPlayer <= DetectionRange;
}

bool ULesFightAIPerceptionSystem::IsTargetInFOV() const
{
    return CurrentPerception.AngleToPlayer <= (FieldOfView * 0.5f);
}

float ULesFightAIPerceptionSystem::GetLastDetectionTime() const
{
    return LastDetectionTime;
}
