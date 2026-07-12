#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LesFightAttackData.h"
#include "LesFightComboData.generated.h"

USTRUCT(BlueprintType)
struct FComboEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AttackID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimingWindow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRequiresCancel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAttackDefinition AttackData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinComboCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString InputSequence;

    FComboEntry()
        : TimingWindow(0.2f)
        , bRequiresCancel(true)
        , MinComboCount(0)
    {}
};

USTRUCT(BlueprintType)
struct FComboDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ComboID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ComboName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FComboEntry> ComboSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TotalDamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ScalingStartingPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MinScaling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsAirCombo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FGameplayTagContainer ComboTags;

    FComboDefinition()
        : TotalDamageMultiplier(1.0f)
        , ScalingStartingPoint(1.0f)
        , MinScaling(0.1f)
        , bIsAirCombo(false)
    {}
};

USTRUCT(BlueprintType)
struct FSpecialMoveDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MoveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MoveName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAttackDefinition AttackData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EnergyCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CooldownTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString InputCommand;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FHitboxShape> Hitboxes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UParticleSystem> CastEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UParticleSystem> HitEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USoundBase> CastSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USoundBase> HitSound;

    FSpecialMoveDefinition()
        : EnergyCost(25.0f)
        , CooldownTime(0.0f)
    {}
};

USTRUCT(BlueprintType)
struct FUltimateMoveDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MoveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MoveName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAttackDefinition AttackData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MeterCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasCinematicCamera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CinematicDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<ULevelSequence> CinematicSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FHitboxShape> Hitboxes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UParticleSystem> StartEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UParticleSystem> HitEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USoundBase> StartSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<USoundBase> HitSound;

    FUltimateMoveDefinition()
        : MeterCost(100.0f)
        , bHasCinematicCamera(false)
        , CinematicDuration(2.0f)
    {}
};

UCLASS(BlueprintType)
class ULesFightCombatDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fighter")
    FName FighterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
    TArray<FAttackDefinition> BasicAttacks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos")
    TArray<FComboDefinition> Combos;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Specials")
    TArray<FSpecialMoveDefinition> SpecialMoves;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimates")
    TArray<FUltimateMoveDefinition> UltimateMoves;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override
    {
        return FPrimaryAssetId(TEXT("CombatData"), FighterID);
    }
};
