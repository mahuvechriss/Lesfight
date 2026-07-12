#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightIntegrationDataTypes.generated.h"

UENUM(BlueprintType)
enum class EGameFlowState : uint8
{
    Init             UMETA(DisplayName = "Init"),
    Loading          UMETA(DisplayName = "Loading"),
    ProfileSelect    UMETA(DisplayName = "ProfileSelect"),
    MainMenu         UMETA(DisplayName = "MainMenu"),
    CharacterSelect  UMETA(DisplayName = "CharacterSelect"),
    CharacterCreator UMETA(DisplayName = "CharacterCreator"),
    AIGeneration     UMETA(DisplayName = "AIGeneration"),
    MatchPrep        UMETA(DisplayName = "MatchPrep"),
    ArenaLoading     UMETA(DisplayName = "ArenaLoading"),
    FightIntro       UMETA(DisplayName = "FightIntro"),
    Fighting         UMETA(DisplayName = "Fighting"),
    RoundEnd         UMETA(DisplayName = "RoundEnd"),
    MatchResult      UMETA(DisplayName = "MatchResult"),
    PauseMenu        UMETA(DisplayName = "PauseMenu"),
    Options          UMETA(DisplayName = "Options"),
    Exiting          UMETA(DisplayName = "Exiting"),
    MAX              UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class ESystemModule : uint8
{
    CoreFramework         UMETA(DisplayName = "CoreFramework"),
    Character             UMETA(DisplayName = "Character"),
    Combat                UMETA(DisplayName = "Combat"),
    Animation             UMETA(DisplayName = "Animation"),
    Network               UMETA(DisplayName = "Network"),
    MartialArts           UMETA(DisplayName = "MartialArts"),
    CharacterCreation     UMETA(DisplayName = "CharacterCreation"),
    AIPhotoToCharacter    UMETA(DisplayName = "AIPhotoToCharacter"),
    FightingAI            UMETA(DisplayName = "FightingAI"),
    Arena                 UMETA(DisplayName = "Arena"),
    Audio                 UMETA(DisplayName = "Audio"),
    VFX                   UMETA(DisplayName = "VFX"),
    UI                    UMETA(DisplayName = "UI"),
    DataManager           UMETA(DisplayName = "DataManager"),
    MAX                   UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class ECoordinationEvent : uint8
{
    MatchStart          UMETA(DisplayName = "MatchStart"),
    RoundStart          UMETA(DisplayName = "RoundStart"),
    RoundEnd            UMETA(DisplayName = "RoundEnd"),
    MatchEnd            UMETA(DisplayName = "MatchEnd"),
    UltimateActivation  UMETA(DisplayName = "UltimateActivation"),
    CharacterIntro      UMETA(DisplayName = "CharacterIntro"),
    VictorySequence     UMETA(DisplayName = "VictorySequence"),
    DefeatSequence      UMETA(DisplayName = "DefeatSequence"),
    ArenaTransition     UMETA(DisplayName = "ArenaTransition"),
    CinematicSequence   UMETA(DisplayName = "CinematicSequence"),
    CountdownSequence   UMETA(DisplayName = "CountdownSequence")
};

UENUM(BlueprintType)
enum class ELoadingPhase : uint8
{
    Prerequisites   UMETA(DisplayName = "Prerequisites"),
    SystemsInit     UMETA(DisplayName = "SystemsInit"),
    AssetLoading    UMETA(DisplayName = "AssetLoading"),
    UIPreparation   UMETA(DisplayName = "UIPreparation"),
    Complete        UMETA(DisplayName = "Complete"),
    Failed          UMETA(DisplayName = "Failed")
};

UENUM(BlueprintType)
enum class EIntegrationTestResult : uint8
{
    Passed  UMETA(DisplayName = "Passed"),
    Failed  UMETA(DisplayName = "Failed"),
    Skipped UMETA(DisplayName = "Skipped"),
    NotRun  UMETA(DisplayName = "NotRun")
};

USTRUCT(BlueprintType)
struct FSystemModuleInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    ESystemModule ModuleID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FName ModuleName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FString VersionString;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    bool bInitialized;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    TArray<ESystemModule> Dependencies;
};

USTRUCT(BlueprintType)
struct FGameFlowStateTransition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    EGameFlowState From;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    EGameFlowState To;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    bool bValid;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FText FailureReason;
};

USTRUCT(BlueprintType)
struct FLoadingTask
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FName TaskName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    float Progress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    ELoadingPhase Phase;

    FLoadingTask()
        : Progress(0.0f)
        , Phase(ELoadingPhase::Prerequisites)
    {
    }
};

USTRUCT(BlueprintType)
struct FCoordinationSequence
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FName SequenceName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    TArray<ECoordinationEvent> Events;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    float TotalDuration;
};

USTRUCT(BlueprintType)
struct FIntegrationTestResult
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FName TestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    EIntegrationTestResult Result;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FText Message;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    float DurationSeconds;
};

USTRUCT(BlueprintType)
struct FSystemEvent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FName EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    ESystemModule SourceModule;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Integration")
    FDateTime Timestamp;
};

class ULesFightDependencyManager;
class ULesFightLoadingManager;
class ULesFightEventCoordinationSystem;
class ULesFightIntegrationSubsystem;
class ULesFightGameFlowManager;
class ULesFightIntegrationTestRunner;
