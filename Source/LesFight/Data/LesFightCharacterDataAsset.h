#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "LesFightCharacterDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float MoveSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float AttackPower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Defense;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float JumpHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float Stamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float SuperMeterGainRate;

    FCharacterStats()
        : Health(1000.0f)
        , MoveSpeed(1.0f)
        , AttackPower(1.0f)
        , Defense(1.0f)
        , JumpHeight(1.0f)
        , Stamina(100.0f)
        , SuperMeterGainRate(1.0f)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterDataTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName CharacterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UAnimBlueprint> AnimBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FCharacterStats BaseStats;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> DefaultMoves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString FightingStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockConditions;
};

UCLASS(BlueprintType)
class ULesFightCharacterDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterDataTableRow CharacterData;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(TEXT("CharacterData"), CharacterData.CharacterID);
    }
};
