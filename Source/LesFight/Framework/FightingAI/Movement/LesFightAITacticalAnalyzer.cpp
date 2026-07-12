#include "LesFightAITacticalAnalyzer.h"
#include "Framework/FightingAI/LesFightAIFighterController.h"

void ULesFightAITacticalAnalyzer::Initialize(ULesFightAIFighterController* InController)
{
    OwnerController = InController;
    RecommendedPosition = FVector::ZeroVector;
    IdealRange = EAICombatRange::Medium;
    TacticalScore = 0.0f;
    bCornered = false;
    bUseArenaEdges = false;
    TacticalNotes.Empty();
}

void ULesFightAITacticalAnalyzer::AnalyzeTactics(const FAIPerceptionData& Perception, FAIDecisionContext& Decision)
{
    if (!OwnerController.IsValid())
    {
        return;
    }

    TacticalNotes.Empty();

    float DistanceToEdge = Perception.DistanceToArenaEdge;
    bool bPlayerAggressive = Perception.bIsPlayerAggressive;
    bool bPlayerDefensive = Perception.bIsPlayerDefensive;
    bool bPlayerCornered = Perception.bIsPlayerCornered;

    bCornered = DistanceToEdge < 150.0f;

    if (DistanceToEdge < 300.0f)
    {
        RecommendedPosition = OwnerController->GetArenaCenter();
        bUseArenaEdges = false;
        TacticalNotes.Add(TEXT("Near arena edge, moving to center"));
    }
    else
    {
        bUseArenaEdges = true;
        RecommendedPosition = OwnerController->GetCurrentPosition();
    }

    if (bPlayerAggressive && bPlayerCornered)
    {
        Decision.RecommendedAction = EAIActionType::CounterAttack;
        TacticalNotes.Add(TEXT("Player is aggressive and cornered, recommend counter"));
    }
    else if (bPlayerDefensive)
    {
        Decision.RecommendedAction = EAIActionType::MeleeAttack;
        TacticalNotes.Add(TEXT("Player is defensive, recommend pressure"));
    }

    EAIFightingStyle Style = OwnerController->GetFightingStyle();

    switch (Style)
    {
    case EAIFightingStyle::Aggressive:
        IdealRange = EAICombatRange::Close;
        TacticalNotes.Add(TEXT("Aggressive style, ideal range is Close"));
        break;
    case EAIFightingStyle::Defensive:
        IdealRange = EAICombatRange::Medium;
        TacticalNotes.Add(TEXT("Defensive style, ideal range is Medium"));
        break;
    case EAIFightingStyle::Ranged:
        IdealRange = EAICombatRange::Far;
        TacticalNotes.Add(TEXT("Ranged style, ideal range is Far"));
        break;
    default:
        IdealRange = EAICombatRange::Medium;
        break;
    }

    TacticalScore = CalculateTacticalScore(Perception, Decision);
    Decision.TacticalScore = TacticalScore;
}

FVector ULesFightAITacticalAnalyzer::GetRecommendedPosition() const
{
    return RecommendedPosition;
}

bool ULesFightAITacticalAnalyzer::ShouldChangeRange() const
{
    return !OwnerController.IsValid() || OwnerController->GetCurrentCombatRange() != IdealRange;
}

EAICombatRange ULesFightAITacticalAnalyzer::GetIdealRange() const
{
    return IdealRange;
}

bool ULesFightAITacticalAnalyzer::IsCornered() const
{
    return bCornered;
}

bool ULesFightAITacticalAnalyzer::ShouldUseArenaEdges() const
{
    return bUseArenaEdges;
}

FVector ULesFightAITacticalAnalyzer::FindAdvantageousPosition() const
{
    if (!OwnerController.IsValid())
    {
        return FVector::ZeroVector;
    }

    FVector PlayerPos = OwnerController->GetPlayerPosition();
    FVector AIPos = OwnerController->GetCurrentPosition();
    FVector Center = OwnerController->GetArenaCenter();

    FVector ToPlayer = (PlayerPos - AIPos).GetSafeNormal();
    FVector LateralDir = FVector::CrossProduct(ToPlayer, FVector::UpVector);

    FVector AdvantagePos = AIPos + LateralDir * 200.0f;

    float DistFromCenter = (AdvantagePos - Center).Size();
    if (DistFromCenter > OwnerController->GetArenaRadius())
    {
        AdvantagePos = Center + (AdvantagePos - Center).GetSafeNormal() * OwnerController->GetArenaRadius() * 0.8f;
    }

    return AdvantagePos;
}

float ULesFightAITacticalAnalyzer::GetTacticalScore() const
{
    return TacticalScore;
}
