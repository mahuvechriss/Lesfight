#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIPerformance.generated.h"

class ALesFightAIFighterController;

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIPerformance : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void SetMaxAIUpdatesPerSecond(int32 Updates);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    int32 GetMaxAIUpdatesPerSecond() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void SetDecisionBudget(float Milliseconds);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    float GetDecisionBudget() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void OptimizeForMultipleAI(int32 Count);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    FString GetPerformanceReport() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    void EnableProfiling(bool bInEnable);

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    float GetAverageDecisionTime() const;

    UFUNCTION(BlueprintCallable, Category = "AI|Performance")
    float GetPerformanceScore() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Performance")
    int32 MaxUpdatesPerSecond = 20;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Performance")
    float DecisionBudgetMs = 5.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Performance")
    bool bProfiling = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Performance")
    TArray<float> DecisionTimes;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Performance")
    float PerformanceScore = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|Performance")
    TArray<FString> PerformanceLog;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;
};
