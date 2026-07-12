#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LesFightAnimationData.h"
#include "LesFightCinematicAnimationHandler.generated.h"

class ULesFightCharacterAnimationComponent;
class ALevelSequenceActor;
class ULevelSequence;

USTRUCT(BlueprintType)
struct FCinematicAnimData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SequenceID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<ULevelSequence> LevelSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<UAnimMontage> AnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SequenceDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseSlowMotion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SlowMotionFactor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bUseCustomCamera;

    FCinematicAnimData()
        : SequenceID(NAME_None), LevelSequence(nullptr), AnimMontage(nullptr)
        , SequenceDuration(0.0f), bUseSlowMotion(false)
        , SlowMotionFactor(0.5f), bUseCustomCamera(false)
    {}
};

UCLASS(Blueprintable)
class ULesFightCinematicAnimationHandler : public UObject
{
    GENERATED_BODY()

public:
    ULesFightCinematicAnimationHandler();

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void Initialize(ULesFightCharacterAnimationComponent* InComponent);

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void PlayCharacterIntro(FName IntroID);

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void PlayVictoryCelebration(FName VictoryID);

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void PlayDefeatSequence(FName DefeatID);

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void PlayUltimateSequence(FName UltimateID);

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void PlaySlowMotionSequence(float Duration, float TimeDilation = 0.3f);

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void StopCinematicSequence(float BlendOut = 0.5f);

    UFUNCTION(BlueprintCallable, Category = "Cinematic Animation")
    void RegisterCinematicAnim(const FCinematicAnimData& AnimData);

    UFUNCTION(BlueprintPure, Category = "Cinematic Animation")
    bool IsPlayingCinematic() const { return bIsPlaying; }

    UFUNCTION(BlueprintPure, Category = "Cinematic Animation")
    FCinematicAnimData GetCurrentSequence() const { return CurrentSequence; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Cinematic Animation")
    TMap<FName, FCinematicAnimData> CinematicAnimations;

    UPROPERTY(BlueprintReadOnly, Category = "Cinematic Animation")
    FCinematicAnimData CurrentSequence;

    UPROPERTY(BlueprintReadOnly, Category = "Cinematic Animation")
    bool bIsPlaying;

private:
    TWeakObjectPtr<ULesFightCharacterAnimationComponent> AnimComponent;
    TObjectPtr<ALevelSequenceActor> CurrentSequenceActor;

    void PlayLevelSequence(ULevelSequence* Sequence);
    void PlayAnimMontage(UAnimMontage* Montage);
};
