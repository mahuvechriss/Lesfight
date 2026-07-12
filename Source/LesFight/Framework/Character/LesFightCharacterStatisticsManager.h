#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightCharacterData.h"
#include "LesFightCharacterStatisticsManager.generated.h"

USTRUCT(BlueprintType)
struct FFighterMatchStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MatchesPlayed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Wins;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Losses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 KOs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Perfects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentWinStreak;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BestWinStreak;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalDamageDealt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalDamageReceived;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalPlayTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WinRate;

    FFighterMatchStats()
        : MatchesPlayed(0), Wins(0), Losses(0), KOs(0), Perfects(0)
        , CurrentWinStreak(0), BestWinStreak(0)
        , TotalDamageDealt(0.0f), TotalDamageReceived(0.0f)
        , TotalPlayTime(0.0f), WinRate(0.0f)
    {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFighterStatsUpdated, FName, CharacterID, const FFighterMatchStats&, Stats);

UCLASS(Blueprintable, Config = Game)
class ULesFightCharacterStatisticsManager : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCharacterStatisticsManager();

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void RecordMatch(FName CharacterID, bool bWon, bool bByKO, bool bPerfect);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void RecordDamage(FName CharacterID, float DamageDealt, float DamageReceived);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void RecordPlayTime(FName CharacterID, float TimeSeconds);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    FFighterMatchStats GetFighterStats(FName CharacterID) const;

    UFUNCTION(BlueprintPure, Category = "Statistics")
    TArray<FName> GetMostPlayedFighters(int32 Count = 5) const;

    UFUNCTION(BlueprintPure, Category = "Statistics")
    TArray<FName> GetHighestWinRateFighters(int32 Count = 5) const;

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void ResetAllStats();

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void ResetFighterStats(FName CharacterID);

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void SaveStats();

    UFUNCTION(BlueprintCallable, Category = "Statistics")
    void LoadStats();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Statistics")
    TMap<FName, FFighterMatchStats> FighterStatsMap;

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnFighterStatsUpdated OnFighterStatsUpdated;

private:
    void UpdateWinRate(FFighterMatchStats& Stats);
};
