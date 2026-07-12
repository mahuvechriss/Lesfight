#include "LesFightCinematicAnimationHandler.h"
#include "LesFightCharacterAnimationComponent.h"
#include "LesFight.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

ULesFightCinematicAnimationHandler::ULesFightCinematicAnimationHandler()
    : bIsPlaying(false)
    , CurrentSequenceActor(nullptr)
{
}

void ULesFightCinematicAnimationHandler::Initialize(
    ULesFightCharacterAnimationComponent* InComponent)
{
    AnimComponent = InComponent;
}

void ULesFightCinematicAnimationHandler::PlayCharacterIntro(FName IntroID)
{
    const FCinematicAnimData* Data = CinematicAnimations.Find(IntroID);
    if (!Data) return;

    CurrentSequence = *Data;
    bIsPlaying = true;

    if (Data->AnimMontage)
    {
        PlayAnimMontage(Data->AnimMontage);
    }
    if (Data->LevelSequence)
    {
        PlayLevelSequence(Data->LevelSequence);
    }

    if (Data->bUseSlowMotion && AnimComponent.IsValid())
    {
        AnimComponent->SetGlobalPlayRate(Data->SlowMotionFactor);
    }
}

void ULesFightCinematicAnimationHandler::PlayVictoryCelebration(FName VictoryID)
{
    PlayCharacterIntro(VictoryID);
}

void ULesFightCinematicAnimationHandler::PlayDefeatSequence(FName DefeatID)
{
    const FCinematicAnimData* Data = CinematicAnimations.Find(DefeatID);
    if (Data && Data->AnimMontage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = Data->AnimMontage;
        MontageData.bEnableRootMotion = false;
        AnimComponent->PlayAnimationMontage(MontageData);
    }
}

void ULesFightCinematicAnimationHandler::PlayUltimateSequence(FName UltimateID)
{
    const FCinematicAnimData* Data = CinematicAnimations.Find(UltimateID);
    if (!Data) return;

    CurrentSequence = *Data;
    bIsPlaying = true;

    if (Data->AnimMontage && AnimComponent.IsValid())
    {
        FAnimationMontageData MontageData;
        MontageData.Montage = Data->AnimMontage;
        MontageData.bEnableRootMotion = true;
        MontageData.bUseMotionWarping = true;
        AnimComponent->PlayAnimationMontage(MontageData);
    }

    if (Data->bUseSlowMotion)
    {
        PlaySlowMotionSequence(Data->SequenceDuration, Data->SlowMotionFactor);
    }
}

void ULesFightCinematicAnimationHandler::PlaySlowMotionSequence(float Duration,
    float TimeDilation)
{
    if (AnimComponent.IsValid())
    {
        AnimComponent->SetGlobalPlayRate(TimeDilation);
        FTimerHandle UnusedHandle;
        AnimComponent->GetWorld()->GetTimerManager().SetTimer(UnusedHandle,
            FTimerDelegate::CreateWeakLambda(this, [this]() {
                if (AnimComponent.IsValid()) AnimComponent->SetGlobalPlayRate(1.0f);
            }), Duration, false);
    }
}

void ULesFightCinematicAnimationHandler::StopCinematicSequence(float BlendOut)
{
    if (AnimComponent.IsValid())
    {
        AnimComponent->StopAnimationMontage(BlendOut);
        AnimComponent->SetGlobalPlayRate(1.0f);
    }

    if (CurrentSequenceActor)
    {
        CurrentSequenceActor->SequencePlayer->Stop();
        CurrentSequenceActor = nullptr;
    }

    bIsPlaying = false;
}

void ULesFightCinematicAnimationHandler::RegisterCinematicAnim(
    const FCinematicAnimData& AnimData)
{
    if (!AnimData.SequenceID.IsNone())
    {
        CinematicAnimations.Add(AnimData.SequenceID, AnimData);
    }
}

void ULesFightCinematicAnimationHandler::PlayLevelSequence(ULevelSequence* Sequence)
{
    if (!Sequence || !AnimComponent.IsValid()) return;

    ALevelSequenceActor* Actor = nullptr;
    ULevelSequencePlayer* Player = ULevelSequencePlayer::CreateLevelSequencePlayer(
        AnimComponent->GetWorld(), Sequence, FMovieSceneSequencePlaybackSettings(), Actor);
    if (Player)
    {
        Player->Play();
        CurrentSequenceActor = Actor;
    }
}

void ULesFightCinematicAnimationHandler::PlayAnimMontage(UAnimMontage* Montage)
{
    if (!Montage || !AnimComponent.IsValid()) return;

    FAnimationMontageData MontageData;
    MontageData.Montage = Montage;
    MontageData.bEnableRootMotion = true;
    AnimComponent->PlayAnimationMontage(MontageData);
}
