#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LesFightSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FPlayerProfileData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 PlayerLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalMatchesPlayed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalWins;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalLosses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalPlayTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockedCharacters;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockedCostumes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockedStages;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Achievements;

    FPlayerProfileData()
        : PlayerName(TEXT("Player"))
        , PlayerLevel(1)
        , TotalMatchesPlayed(0)
        , TotalWins(0)
        , TotalLosses(0)
        , TotalPlayTime(0.0f)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterSaveData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CharacterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MatchesPlayed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Wins;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float WinRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockedSkins;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, float> Stats;

    FCharacterSaveData()
        : MatchesPlayed(0)
        , Wins(0)
        , WinRate(0.0f)
    {}
};

USTRUCT(BlueprintType)
struct FMatchStatisticsData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalMatches;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalRounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalDamageDealt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalDamageReceived;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalKOs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalPerfects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalDraws;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalDisconnects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentWinStreak;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 BestWinStreak;

    FMatchStatisticsData()
        : TotalMatches(0)
        , TotalRounds(0)
        , TotalDamageDealt(0.0f)
        , TotalDamageReceived(0.0f)
        , TotalKOs(0)
        , TotalPerfects(0)
        , TotalDraws(0)
        , TotalDisconnects(0)
        , CurrentWinStreak(0)
        , BestWinStreak(0)
    {}
};

UCLASS()
class ULesFightSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    ULesFightSaveGame();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LesFight|Save|Player")
    FPlayerProfileData PlayerProfile;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LesFight|Save|Characters")
    TMap<FName, FCharacterSaveData> CharacterData;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LesFight|Save|Statistics")
    FMatchStatisticsData MatchStatistics;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LesFight|Save|Settings")
    TArray<uint8> SerializedSettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LesFight|Save|Game")
    int32 SaveVersion;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LesFight|Save|Game")
    FDateTime SaveTimestamp;
};
