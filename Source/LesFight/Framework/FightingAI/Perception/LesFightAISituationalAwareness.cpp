#include "Framework/FightingAI/Perception/LesFightAISituationalAwareness.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"

void ULesFightAISituationalAwareness::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;
}

void ULesFightAISituationalAwareness::UpdateSituation(const FAIPerceptionData& Perception)
{
    SituationLog.Reset();

    if (Perception.DistanceToPlayer < 150.0f)
    {
        RecommendedRange = EAICombatRange::Close;
    }
    else if (Perception.DistanceToPlayer < 400.0f)
    {
        RecommendedRange = EAICombatRange::Medium;
    }
    else
    {
        RecommendedRange = EAICombatRange::Far;
    }

    ArenaEdgeDistance = Perception.DistanceToArenaEdge;

    float ThreatScore = 0.0f;

    float HealthFactor = 1.0f - Perception.PlayerHealthPercent;
    ThreatScore += HealthFactor * 40.0f;

    if (Perception.bPlayerIsAttacking)
    {
        ThreatScore += 30.0f;
    }

    float DistanceFactor = FMath::Clamp(1.0f - (Perception.DistanceToPlayer / 1000.0f), 0.0f, 1.0f);
    ThreatScore += DistanceFactor * 30.0f;

    DangerScore = ThreatScore;

    if (ThreatScore >= 80.0f)
    {
        ThreatLevel = EAIThreatLevel::Critical;
    }
    else if (ThreatScore >= 60.0f)
    {
        ThreatLevel = EAIThreatLevel::High;
    }
    else if (ThreatScore >= 35.0f)
    {
        ThreatLevel = EAIThreatLevel::Medium;
    }
    else if (ThreatScore >= 10.0f)
    {
        ThreatLevel = EAIThreatLevel::Low;
    }
    else
    {
        ThreatLevel = EAIThreatLevel::None;
    }

    SituationLog.Add(FString::Printf(TEXT("Range=%d ThreatScore=%.1f Level=%d"),
        (int32)RecommendedRange, ThreatScore, (int32)ThreatLevel));
}

EAIThreatLevel ULesFightAISituationalAwareness::GetThreatLevel() const
{
    return ThreatLevel;
}

bool ULesFightAISituationalAwareness::IsPlayerAttacking() const
{
    return false;
}

bool ULesFightAISituationalAwareness::IsPlayerVulnerable() const
{
    return false;
}

bool ULesFightAISituationalAwareness::CanPunish() const
{
    return false;
}

EAICombatRange ULesFightAISituationalAwareness::GetRecommendedRange() const
{
    return RecommendedRange;
}

float ULesFightAISituationalAwareness::GetArenaEdgeDistance() const
{
    return ArenaEdgeDistance;
}

bool ULesFightAISituationalAwareness::ShouldRetreat() const
{
    return false;
}

bool ULesFightAISituationalAwareness::ShouldPressure() const
{
    return false;
}
