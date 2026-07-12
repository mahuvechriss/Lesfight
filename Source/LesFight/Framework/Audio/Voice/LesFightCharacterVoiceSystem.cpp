#include "LesFightCharacterVoiceSystem.h"
#include "LesFightVoiceManager.h"
#include "Framework/Audio/Data/LesFightAudioData.h"

void ULesFightCharacterVoiceSystem::AssignVoicePack(FName CharacterID, FName VoicePackName)
{
    CharacterVoiceAssignments.Emplace(CharacterID, VoicePackName);

    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        TArray<FName> Packs = OwnerManager->GetVoiceManager()->GetAvailableVoicePacks();
        for (const FName& Pack : Packs)
        {
            if (Pack == VoicePackName)
            {
                break;
            }
        }
    }
}

void ULesFightCharacterVoiceSystem::PlayCharacterTaunt(FName CharacterID)
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        FName* PackName = CharacterVoiceAssignments.Find(CharacterID);
        FName VoicePack = PackName != nullptr ? *PackName : CharacterID;
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Taunt, VoicePack);
    }
}

void ULesFightCharacterVoiceSystem::PlayCharacterPain(FName CharacterID)
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        FName* PackName = CharacterVoiceAssignments.Find(CharacterID);
        FName VoicePack = PackName != nullptr ? *PackName : CharacterID;
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Pain, VoicePack);
    }
}

void ULesFightCharacterVoiceSystem::PlayCharacterVictory(FName CharacterID)
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        FName* PackName = CharacterVoiceAssignments.Find(CharacterID);
        FName VoicePack = PackName != nullptr ? *PackName : CharacterID;
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Victory, VoicePack);
    }
}

void ULesFightCharacterVoiceSystem::PlayCharacterDefeat(FName CharacterID)
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        FName* PackName = CharacterVoiceAssignments.Find(CharacterID);
        FName VoicePack = PackName != nullptr ? *PackName : CharacterID;
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Defeat, VoicePack);
    }
}

void ULesFightCharacterVoiceSystem::PlayCharacterUltimateCall(FName CharacterID)
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        FName* PackName = CharacterVoiceAssignments.Find(CharacterID);
        FName VoicePack = PackName != nullptr ? *PackName : CharacterID;
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Ultimate, VoicePack);
    }
}

void ULesFightCharacterVoiceSystem::PlayCharacterEntrance(FName CharacterID)
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        FName* PackName = CharacterVoiceAssignments.Find(CharacterID);
        FName VoicePack = PackName != nullptr ? *PackName : CharacterID;
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Entrance, VoicePack);
    }
}

FCharacterVoicePack ULesFightCharacterVoiceSystem::GetCharacterVoicePack(FName CharacterID) const
{
    FName* PackName = CharacterVoiceAssignments.Find(CharacterID);
    if (PackName != nullptr)
    {
        const FCharacterVoicePack* Cached = CachedPacks.Find(*PackName);
        if (Cached != nullptr)
        {
            return *Cached;
        }
    }

    FCharacterVoicePack Empty;
    return Empty;
}

float ULesFightCharacterVoiceSystem::GetCharacterPitch(FName CharacterID) const
{
    const float* Pitch = CharacterPitches.Find(CharacterID);
    return Pitch != nullptr ? *Pitch : 1.0f;
}
