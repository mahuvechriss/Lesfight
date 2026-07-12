#include "Framework/FightingAI/Integration/LesFightAIAudioHandler.h"
#include "Framework/FightingAI/Core/LesFightAIFighterController.h"

void ULesFightAIAudioHandler::PlayVoiceLine(const FAIDecisionContext& Context)
{
    if (bMuted || !OwnerController.IsValid())
    {
        return;
    }

    FString* FoundLine = VoiceReactions.Find(static_cast<EAIAnimationEvent>(Context.ChosenAction));
    if (FoundLine)
    {
        CurrentVoiceLine = *FoundLine;
        bSpeaking = true;
    }
}

void ULesFightAIAudioHandler::PlayHitSound()
{
    if (!bMuted)
    {
        CurrentVoiceLine = TEXT("Hmph!");
        bSpeaking = true;
    }
}

void ULesFightAIAudioHandler::PlayMissSound()
{
    if (!bMuted)
    {
        CurrentVoiceLine = TEXT("Tch!");
        bSpeaking = true;
    }
}

void ULesFightAIAudioHandler::PlayBlockSound()
{
    if (!bMuted)
    {
        CurrentVoiceLine = TEXT("Tch!");
        bSpeaking = true;
    }
}

void ULesFightAIAudioHandler::PlayTaunt()
{
    if (bMuted || TauntLines.Num() == 0)
    {
        return;
    }

    int32 RandomIndex = FMath::RandRange(0, TauntLines.Num() - 1);
    CurrentVoiceLine = TauntLines[RandomIndex];
    bSpeaking = true;
}

void ULesFightAIAudioHandler::PlayVictorySound()
{
    if (!bMuted)
    {
        CurrentVoiceLine = TEXT("I win.");
        bSpeaking = true;
    }
}

void ULesFightAIAudioHandler::PlayDefeatSound()
{
    if (!bMuted)
    {
        CurrentVoiceLine = TEXT("Good fight.");
        bSpeaking = true;
    }
}

void ULesFightAIAudioHandler::PlayBreathSound(EAIAnimationEvent Event)
{
    if (bMuted)
    {
        return;
    }

    FString* FoundReaction = VoiceReactions.Find(Event);
    if (FoundReaction)
    {
        CurrentVoiceLine = *FoundReaction;
        bSpeaking = true;
    }
}

void ULesFightAIAudioHandler::SetVoicePitch(float Pitch)
{
    VoicePitch = Pitch;
}

void ULesFightAIAudioHandler::SetVoiceVolume(float Volume)
{
    VoiceVolume = Volume;
}

bool ULesFightAIAudioHandler::IsSpeaking() const
{
    return bSpeaking;
}

void ULesFightAIAudioHandler::SetMuted(bool bInMuted)
{
    bMuted = bInMuted;
}

void ULesFightAIAudioHandler::Initialize(ALesFightAIFighterController* InController)
{
    OwnerController = InController;

    VoiceReactions.Empty();
    VoiceReactions.Add(EAIAnimationEvent::AttackStart, TEXT("Hyah!"));
    VoiceReactions.Add(EAIAnimationEvent::AttackHit, TEXT("Hmph!"));
    VoiceReactions.Add(EAIAnimationEvent::AttackMiss, TEXT("Tch!"));
    VoiceReactions.Add(EAIAnimationEvent::ComboStart, TEXT("Take this!"));
    VoiceReactions.Add(EAIAnimationEvent::ComboEnd, TEXT("How's that!"));
    VoiceReactions.Add(EAIAnimationEvent::BlockStart, TEXT("Hmph."));
    VoiceReactions.Add(EAIAnimationEvent::BlockHit, TEXT("Tch!"));
    VoiceReactions.Add(EAIAnimationEvent::DodgeStart, TEXT("Too slow!"));
    VoiceReactions.Add(EAIAnimationEvent::DodgeComplete, TEXT("Hah!"));
    VoiceReactions.Add(EAIAnimationEvent::ParrySuccess, TEXT("Nice try!"));
    VoiceReactions.Add(EAIAnimationEvent::CounterStart, TEXT("My turn!"));
    VoiceReactions.Add(EAIAnimationEvent::CounterHit, TEXT("Gotcha!"));
    VoiceReactions.Add(EAIAnimationEvent::GetHit, TEXT("Ugh!"));
    VoiceReactions.Add(EAIAnimationEvent::Knockdown, TEXT("Ugh!"));
    VoiceReactions.Add(EAIAnimationEvent::GetUp, TEXT("Haa..."));
    VoiceReactions.Add(EAIAnimationEvent::Stunned, TEXT("Ngh..."));
    VoiceReactions.Add(EAIAnimationEvent::RecoverStart, TEXT("Haa..."));
    VoiceReactions.Add(EAIAnimationEvent::RecoverEnd, TEXT("Alright."));
    VoiceReactions.Add(EAIAnimationEvent::Taunt, TEXT("Is that all?"));
    VoiceReactions.Add(EAIAnimationEvent::Victory, TEXT("I win."));
    VoiceReactions.Add(EAIAnimationEvent::Defeat, TEXT("Good fight."));

    TauntLines.Empty();
    TauntLines.Add(TEXT("Is that all?"));
    TauntLines.Add(TEXT("You'll have to try harder!"));
    TauntLines.Add(TEXT("Too slow!"));
    TauntLines.Add(TEXT("Is that your best?"));
    TauntLines.Add(TEXT("Come on, fight me!"));
}
