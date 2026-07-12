#include "LesFightVoiceSelection.h"
#include "LesFightCharCreationManager.h"

ULesFightVoiceSelection::ULesFightVoiceSelection()
    : DefaultVolume(1.0f)
    , MinPitch(0.5f)
    , MaxPitch(2.0f)
    , MinTone(0.5f)
    , MaxTone(2.0f)
{
    CurrentVoiceData.VoicePack = EVoicePack::DefaultMale;
    CurrentVoiceData.Pitch = 1.0f;
    CurrentVoiceData.Tone = 1.0f;

    for (int32 i = 0; i < static_cast<int32>(EVoicePack::MAX); i++)
    {
        UnlockedVoicePacks.Add(static_cast<EVoicePack>(i));
    }
}

void ULesFightVoiceSelection::Initialize(ULesFightCharCreationManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightVoiceSelection::SetVoicePack(EVoicePack Pack)
{
    CurrentVoiceData.VoicePack = Pack;
}

EVoicePack ULesFightVoiceSelection::GetVoicePack() const
{
    return CurrentVoiceData.VoicePack;
}

void ULesFightVoiceSelection::SetPitch(float Pitch)
{
    CurrentVoiceData.Pitch = FMath::Clamp(Pitch, MinPitch, MaxPitch);
}

float ULesFightVoiceSelection::GetPitch() const
{
    return CurrentVoiceData.Pitch;
}

void ULesFightVoiceSelection::SetTone(float Tone)
{
    CurrentVoiceData.Tone = FMath::Clamp(Tone, MinTone, MaxTone);
}

float ULesFightVoiceSelection::GetTone() const
{
    return CurrentVoiceData.Tone;
}

void ULesFightVoiceSelection::PreviewVoice()
{
    OnVoicePreviewComplete.Broadcast(true);
}

void ULesFightVoiceSelection::PreviewTaunt(int32 TauntIndex)
{
}

void ULesFightVoiceSelection::StopPreview()
{
}

void ULesFightVoiceSelection::SetData(const FVoiceSelectionData& Data)
{
    CurrentVoiceData = Data;
}

FVoiceSelectionData ULesFightVoiceSelection::GetData() const
{
    return CurrentVoiceData;
}

TArray<EVoicePack> ULesFightVoiceSelection::GetAvailableVoicePacks() const
{
    return UnlockedVoicePacks;
}

void ULesFightVoiceSelection::SetVolume(float Volume)
{
    CurrentVoiceData.Pitch = FMath::Clamp(Volume, 0.0f, 1.0f);
}

float ULesFightVoiceSelection::GetVolume() const
{
    return CurrentVoiceData.Pitch;
}

void ULesFightVoiceSelection::ResetToDefault()
{
    CurrentVoiceData.VoicePack = EVoicePack::DefaultMale;
    CurrentVoiceData.Pitch = 1.0f;
    CurrentVoiceData.Tone = 1.0f;
}
