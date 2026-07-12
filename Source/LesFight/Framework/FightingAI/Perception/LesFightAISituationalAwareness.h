#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAISituationalAwareness.generated.h"

class ALesFightAIFighterController;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAISituationalAwareness : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    void Initialize(ALesFightAIFighterController* InController);

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    void UpdateSituation(const FAIPerceptionData& Perception);

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    EAIThreatLevel GetThreatLevel() const;

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    bool IsPlayerAttacking() const;

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    bool IsPlayerVulnerable() const;

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    bool CanPunish() const;

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    EAICombatRange GetRecommendedRange() const;

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    float GetArenaEdgeDistance() const;

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    bool ShouldRetreat() const;

    UFUNCTION(BlueprintCallable, Category = "AI|SituationalAwareness")
    bool ShouldPressure() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SituationalAwareness")
    EAIThreatLevel ThreatLevel = EAIThreatLevel::None;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SituationalAwareness")
    EAICombatRange RecommendedRange = EAICombatRange::Medium;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SituationalAwareness")
    float ArenaEdgeDistance = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SituationalAwareness")
    float DangerScore = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|SituationalAwareness")
    TArray<FString> SituationLog;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;
};
