#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/FightingAI/Data/LesFightAIData.h"
#include "LesFightAIDifficultyManager.generated.h"

UCLASS(Blueprintable)
class LESFIGHT_API ULesFightAIDifficultyManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightAIDifficultyManager();

    UFUNCTION(BlueprintCallable)
    void SetDifficulty(EAIDifficulty Difficulty);

    UFUNCTION(BlueprintCallable)
    EAIDifficulty GetDifficulty() const { return CurrentDifficulty; }

    UFUNCTION(BlueprintCallable)
    FAIDifficultySettings GetSettings() const { return CurrentSettings; }

    UFUNCTION(BlueprintCallable)
    void AdjustForPerformance(float PlayerWinRate);

    UFUNCTION(BlueprintCallable)
    float GetReactionTime() const;

    UFUNCTION(BlueprintCallable)
    float GetBlockChance() const { return CurrentSettings.BlockChance; }

    UFUNCTION(BlueprintCallable)
    float GetDodgeChance() const { return CurrentSettings.DodgeChance; }

    UFUNCTION(BlueprintCallable)
    float GetParryChance() const { return CurrentSettings.ParryChance; }

    UFUNCTION(BlueprintCallable)
    int32 GetMaxComboLength() const { return CurrentSettings.MaxComboLength; }

    UFUNCTION(BlueprintCallable)
    float GetMistakeChance() const { return CurrentSettings.MistakeChance; }

    UFUNCTION(BlueprintCallable)
    FString GetDifficultyName() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Difficulty")
    EAIDifficulty CurrentDifficulty;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Difficulty")
    FAIDifficultySettings CurrentSettings;

    UPROPERTY()
    TMap<EAIDifficulty, FAIDifficultySettings> Presets;

    UPROPERTY()
    float PlayerWinRateTracking;

private:
    TWeakObjectPtr<class ULesFightAIFighterController> OwnerController;
};
