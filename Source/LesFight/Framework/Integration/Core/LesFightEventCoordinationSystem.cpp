#include "Framework/Integration/Core/LesFightEventCoordinationSystem.h"

static FCoordinationSequence MakeSequence(FName Name, std::initializer_list<ECoordinationEvent> Events, float Duration = 0.0f)
{
    FCoordinationSequence Seq;
    Seq.SequenceName = Name;
    Seq.Events = TArray<ECoordinationEvent>(Events);
    Seq.TotalDuration = Duration;
    return Seq;
}

void ULesFightEventCoordinationSystem::Initialize()
{
    SequenceRegistry.Empty();
    SequenceCallbacks.Empty();
    ActiveSequence = NAME_None;
    CurrentEventIndex = 0;
    bSequencePlaying = false;
    bPaused = false;
    SequenceTimer = 0.0f;

    RegisterSequence(TEXT("MatchStart"), MakeSequence(TEXT("MatchStart"), {
        ECoordinationEvent::CountdownSequence,
        ECoordinationEvent::CharacterIntro,
        ECoordinationEvent::RoundStart
    }));

    RegisterSequence(TEXT("RoundComplete"), MakeSequence(TEXT("RoundComplete"), {
        ECoordinationEvent::RoundEnd,
        ECoordinationEvent::CountdownSequence,
        ECoordinationEvent::RoundStart
    }));

    RegisterSequence(TEXT("MatchComplete"), MakeSequence(TEXT("MatchComplete"), {
        ECoordinationEvent::MatchEnd,
        ECoordinationEvent::VictorySequence,
        ECoordinationEvent::MatchResult
    }));

    RegisterSequence(TEXT("UltimateMove"), MakeSequence(TEXT("UltimateMove"), {
        ECoordinationEvent::UltimateActivation,
        ECoordinationEvent::CinematicSequence,
        ECoordinationEvent::CountdownSequence
    }));

    RegisterSequence(TEXT("ArenaTransition"), MakeSequence(TEXT("ArenaTransition"), {
        ECoordinationEvent::ArenaTransition,
        ECoordinationEvent::CountdownSequence
    }));
}

void ULesFightEventCoordinationSystem::Shutdown()
{
    StopSequence();
    SequenceRegistry.Empty();
    SequenceCallbacks.Empty();
}

void ULesFightEventCoordinationSystem::PlaySequence(FName SequenceName)
{
    if (!SequenceRegistry.Contains(SequenceName))
    {
        return;
    }

    StopSequence();

    ActiveSequence = SequenceName;
    CurrentEventIndex = 0;
    bSequencePlaying = true;
    bPaused = false;
    SequenceTimer = 0.0f;

    const FCoordinationSequence& Sequence = SequenceRegistry[SequenceName];
    if (Sequence.Events.Num() > 0)
    {
        StartCoordinationEvent(Sequence.Events[0], nullptr);
    }
}

void ULesFightEventCoordinationSystem::RegisterSequence(FName SequenceName, const FCoordinationSequence& Sequence)
{
    SequenceRegistry.Add(SequenceName, Sequence);
}

void ULesFightEventCoordinationSystem::UnregisterSequence(FName SequenceName)
{
    if (ActiveSequence == SequenceName)
    {
        StopSequence();
    }
    SequenceRegistry.Remove(SequenceName);
    SequenceCallbacks.Remove(SequenceName);
}

void ULesFightEventCoordinationSystem::RegisterSequenceCallback(FName SequenceName, ECoordinationEvent Event, FOnSequenceEvent Callback)
{
    if (!SequenceCallbacks.Contains(SequenceName))
    {
        SequenceCallbacks.Add(SequenceName, TMap<ECoordinationEvent, FOnSequenceEvent>());
    }
    SequenceCallbacks[SequenceName].Add(Event, Callback);
}

void ULesFightEventCoordinationSystem::StartCoordinationEvent(ECoordinationEvent Event, UObject* Context)
{
    OnEventTriggered.Broadcast(Event, Context);

    if (!ActiveSequence.IsNone() && SequenceCallbacks.Contains(ActiveSequence))
    {
        const TMap<ECoordinationEvent, FOnSequenceEvent>& Callbacks = SequenceCallbacks[ActiveSequence];
        if (const FOnSequenceEvent* Found = Callbacks.Find(Event))
        {
            if (Found->IsBound())
            {
                Found->Broadcast(Event, Context);
            }
        }
    }

    if (!ActiveSequence.IsNone() && SequenceRegistry.Contains(ActiveSequence))
    {
        const FCoordinationSequence& Sequence = SequenceRegistry[ActiveSequence];
        CurrentEventIndex++;
        if (CurrentEventIndex < Sequence.Events.Num())
        {
            StartCoordinationEvent(Sequence.Events[CurrentEventIndex], Context);
        }
        else
        {
            bSequencePlaying = false;
            ActiveSequence = NAME_None;
        }
    }
}

FName ULesFightEventCoordinationSystem::GetActiveSequence() const
{
    return ActiveSequence;
}

bool ULesFightEventCoordinationSystem::IsSequencePlaying() const
{
    return bSequencePlaying;
}

TArray<FName> ULesFightEventCoordinationSystem::GetAvailableSequences() const
{
    TArray<FName> Names;
    SequenceRegistry.GetKeys(Names);
    return Names;
}

void ULesFightEventCoordinationSystem::PauseSequence()
{
    bPaused = true;
}

void ULesFightEventCoordinationSystem::ResumeSequence()
{
    bPaused = false;
}

void ULesFightEventCoordinationSystem::StopSequence()
{
    ActiveSequence = NAME_None;
    CurrentEventIndex = 0;
    bSequencePlaying = false;
    bPaused = false;
    SequenceTimer = 0.0f;
    PendingEvents.Empty();
}
