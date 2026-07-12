#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LesFightCharacterData.generated.h"

UENUM(BlueprintType)
enum class EBodyType : uint8
{
    Slim,
    Athletic,
    Muscular,
    Heavy,
    Custom
};

UENUM(BlueprintType)
enum class EFightingStance : uint8
{
    Orthodox,
    Southpaw,
    Custom
};

USTRUCT(BlueprintType)
struct FCharacterIdentity
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FName CharacterID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Nickname;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    int32 Age;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Gender;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Biography;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Nationality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString FightingStyle;

    FCharacterIdentity()
        : Age(25)
        , Gender(TEXT("Male"))
    {}
};

USTRUCT(BlueprintType)
struct FCharacterPhysicalAttributes
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float Height;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    EBodyType BodyType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float MuscleDefinition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    float Reach;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physical")
    EFightingStance FightingStance;

    FCharacterPhysicalAttributes()
        : Height(175.0f)
        , Weight(75.0f)
        , BodyType(EBodyType::Athletic)
        , MuscleDefinition(0.5f)
        , Reach(70.0f)
        , FightingStance(EFightingStance::Orthodox)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterMovementAttributes
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float WalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float RunSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float SprintSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float JumpHeight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CrouchSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Acceleration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Deceleration;

    FCharacterMovementAttributes()
        : WalkSpeed(150.0f)
        , RunSpeed(400.0f)
        , SprintSpeed(650.0f)
        , JumpHeight(600.0f)
        , CrouchSpeed(100.0f)
        , Acceleration(2048.0f)
        , Deceleration(2048.0f)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterCombatAttributes
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Strength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Defense;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Agility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float Balance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float ComboAbility;

    FCharacterCombatAttributes()
        : Strength(1.0f)
        , Defense(1.0f)
        , Agility(1.0f)
        , Balance(1.0f)
        , AttackSpeed(1.0f)
        , ComboAbility(1.0f)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterResourceAttributes
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    float MaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    float MaxStamina;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    float StaminaRecoveryRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    float MaxEnergy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    float EnergyGainRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
    float RecoverySpeed;

    FCharacterResourceAttributes()
        : MaxHealth(1000.0f)
        , MaxStamina(100.0f)
        , StaminaRecoveryRate(15.0f)
        , MaxEnergy(100.0f)
        , EnergyGainRate(5.0f)
        , RecoverySpeed(1.0f)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterAnimationReferences
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimBlueprint> AnimBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimSequence> IdleAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimSequence> WalkAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimSequence> RunAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimSequence> SprintAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimSequence> JumpAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimSequence> LandingAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UAnimSequence> CrouchAnim;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TSoftObjectPtr<UBlendSpace1D> LocomotionBlendSpace;
};

USTRUCT(BlueprintType)
struct FCharacterAudioReferences
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> FootstepSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> BreathingSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> HitReactionSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TSoftObjectPtr<USoundBase> VictoryVoice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TSoftObjectPtr<USoundBase> DefeatVoice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> GruntSounds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TArray<TSoftObjectPtr<USoundBase>> TauntSounds;
};

USTRUCT(BlueprintType)
struct FCharacterCosmeticReferences
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmetics")
    TSoftObjectPtr<USkeletalMesh> BaseMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmetics")
    TArray<TSoftObjectPtr<UMaterialInstance>> SkinMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmetics")
    TArray<TSoftObjectPtr<UMaterialInstance>> HairMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmetics")
    TArray<FName> ClothingSlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmetics")
    TArray<FName> AccessorySlots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cosmetics")
    TArray<TSoftObjectPtr<UTexture2D>> PortraitTextures;
};

USTRUCT(BlueprintType)
struct FCharacterProgressionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
    int32 StartingLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
    float ExperienceMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
    TArray<float> LevelThresholds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
    TArray<FName> UnlockableAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
    TArray<FName> SkillTreeNodes;

    FCharacterProgressionData()
        : StartingLevel(1)
        , ExperienceMultiplier(1.0f)
    {}
};

USTRUCT(BlueprintType)
struct FCharacterTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterIdentity Identity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterPhysicalAttributes Physical;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterMovementAttributes Movement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterCombatAttributes Combat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterResourceAttributes Resources;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterAnimationReferences Animations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterAudioReferences Audio;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterCosmeticReferences Cosmetics;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FCharacterProgressionData Progression;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    bool bIsUnlockedByDefault;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
    FString UnlockCondition;

    FCharacterTableRow()
        : bIsUnlockedByDefault(true)
    {}
};
