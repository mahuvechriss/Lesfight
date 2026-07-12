#include "Framework/Audio/Cinematic/LesFightCinematicAudio.h"

void ULesFightCinematicAudio::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    bCinematicMode = false;
    bSlowMotion = false;
    OriginalTimeDilation = 1.0f;
    CinematicSoundPaths.Empty();
}

void ULesFightCinematicAudio::BeginSlowMotion(float TimeDilation)
{
    if (bSlowMotion) return;
    bSlowMotion = true;
    OriginalTimeDilation = TimeDilation;
    OnCinematicMoment.Broadcast(TEXT("SlowMotion_Begin"));
}

void ULesFightCinematicAudio::EndSlowMotion()
{
    if (!bSlowMotion) return;
    bSlowMotion = false;
    OriginalTimeDilation = 1.0f;
    OnCinematicMoment.Broadcast(TEXT("SlowMotion_End"));
}

void ULesFightCinematicAudio::PlayUltimateAttackSequence(FName AttackerID)
{
    OnCinematicMoment.Broadcast(FString::Printf(TEXT("UltimateAttack_%s"), *AttackerID.ToString()));
}

void ULesFightCinematicAudio::PlayFinisherSequence(FName WinnerID)
{
    OnCinematicMoment.Broadcast(FString::Printf(TEXT("Finisher_%s"), *WinnerID.ToString()));
}

void ULesFightCinematicAudio::PlayDramaticSilence(float Duration)
{
    OnCinematicMoment.Broadcast(FString::Printf(TEXT("DramaticSilence_%.2f"), Duration));
}

void ULesFightCinematicAudio::PlayImpactEmphasis(FVector Location, float Force)
{
    OnCinematicMoment.Broadcast(FString::Printf(TEXT("ImpactEmphasis_%.2f"), Force));
}

void ULesFightCinematicAudio::PlayRoundStartSequence()
{
    OnCinematicMoment.Broadcast(TEXT("RoundStart"));
}

void ULesFightCinematicAudio::PlayRoundEndSequence()
{
    OnCinematicMoment.Broadcast(TEXT("RoundEnd"));
}

void ULesFightCinematicAudio::SetCinematicMode(bool bEnabled)
{
    bCinematicMode = bEnabled;
    OnCinematicMoment.Broadcast(bEnabled ? TEXT("CinematicMode_On") : TEXT("CinematicMode_Off"));
}

bool ULesFightCinematicAudio::IsCinematicMode() const
{
    return bCinematicMode;
}
