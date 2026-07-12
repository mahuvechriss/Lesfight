#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIDevTools.generated.h"

class ALesFightAIFighterController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDebugUpdated, FAIDebugSnapshot, Snapshot);

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIDevTools : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void EnableDebugMode(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    bool IsDebugModeEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    FAIDebugSnapshot GetDebugSnapshot() const;

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void VisualizeDecision(const FAIDecisionContext& Decision);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void DisplayBehaviorTree(const TArray<FString>& TreeNodes);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void ShowReactionTiming(float ReactionTime);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void ShowCombatPrediction(const FAIPerceptionData& Perception);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void TestDifficulty(EAIDifficulty Difficulty);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    void RunAIBenchmark(int32 TestIterations);

    UFUNCTION(BlueprintCallable, Category = "AI|DevTools")
    FString GenerateAIReport() const;

    UPROPERTY(BlueprintAssignable, Category = "AI|DevTools")
    FOnDebugUpdated OnDebugUpdated;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|DevTools")
    bool bDebugMode = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|DevTools")
    FAIDebugSnapshot CurrentSnapshot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|DevTools")
    TArray<FAIDebugSnapshot> SnapshotHistory;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|DevTools")
    TMap<FString, float> BenchmarkResults;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|DevTools")
    TArray<FString> DebugLog;

private:
    TWeakObjectPtr<ALesFightAIFighterController> OwnerController;
};
