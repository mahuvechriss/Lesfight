#include "LesFightAIVoiceSystem.h"
#include "LesFightVoiceManager.h"
#include "Framework/Audio/Data/LesFightAudioData.h"

ULesFightAIVoiceSystem::ULesFightAIVoiceSystem()
{
    PersonalityVoicePacks.Emplace(EAIPersonalityType::Warrior, FName("AIBrawler"));
    PersonalityVoicePacks.Emplace(EAIPersonalityType::Assassin, FName("AISamurai"));
    PersonalityVoicePacks.Emplace(EAIPersonalityType::Master, FName("AIMaster"));
    PersonalityVoicePacks.Emplace(EAIPersonalityType::Berserker, FName("AIBerserker"));

    PersonalityTaunts.Emplace(EAIPersonalityType::Warrior, TArray<FString>{
        TEXT("You're nothing!"),
        TEXT("Fight me!"),
        TEXT("Is that all you've got?")
    });

    PersonalityTaunts.Emplace(EAIPersonalityType::Assassin, TArray<FString>{
        TEXT("Too slow..."),
        TEXT("I've already won"),
        TEXT("You never saw it coming")
    });

    PersonalityTaunts.Emplace(EAIPersonalityType::Master, TArray<FString>{
        TEXT("You have much to learn"),
        TEXT("Pathetic display"),
        TEXT("I've mastered a thousand styles")
    });

    PersonalityTaunts.Emplace(EAIPersonalityType::Berserker, TArray<FString>{
        TEXT("RAAAAAAGE!"),
        TEXT("I'LL DESTROY YOU!"),
        TEXT("FEEL MY WRATH!")
    });
}

void ULesFightAIVoiceSystem::InitializeForAI(EAIPersonalityType Personality)
{
    AIPersonality = Personality;

    FName* PackName = PersonalityVoicePacks.Find(Personality);
    if (PackName != nullptr)
    {
        AIVoicePackName = *PackName;
    }
}

void ULesFightAIVoiceSystem::PlayAITaunt()
{
    if (!WouldAISpeak() || !OwnerManager.IsValid() || !OwnerManager->GetVoiceManager().IsValid())
    {
        return;
    }

    TArray<FString>* Taunts = PersonalityTaunts.Find(AIPersonality);
    if (Taunts == nullptr || Taunts->Num() == 0)
    {
        return;
    }

    OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Taunt, AIVoicePackName);
}

void ULesFightAIVoiceSystem::PlayAIReaction(EAIAnimationEvent Event)
{
    if (!OwnerManager.IsValid() || !OwnerManager->GetVoiceManager().IsValid())
    {
        return;
    }

    EVoiceContext Context;
    switch (Event)
    {
    case EAIAnimationEvent::HitTaken:
        Context = EVoiceContext::Pain;
        break;
    case EAIAnimationEvent::Block:
        Context = EVoiceContext::Pain;
        break;
    case EAIAnimationEvent::Stagger:
        Context = EVoiceContext::Pain;
        break;
    case EAIAnimationEvent::Knockdown:
        Context = EVoiceContext::Pain;
        break;
    case EAIAnimationEvent::GetUp:
        Context = EVoiceContext::CombatCall;
        break;
    case EAIAnimationEvent::Taunt:
        Context = EVoiceContext::Taunt;
        break;
    default:
        return;
    }

    OwnerManager->GetVoiceManager()->PlayVoiceLine(Context, AIVoicePackName);
}

void ULesFightAIVoiceSystem::PlayAICombatCall()
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::CombatCall, AIVoicePackName);
    }
}

void ULesFightAIVoiceSystem::PlayAIVictory()
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Victory, AIVoicePackName);
    }
}

void ULesFightAIVoiceSystem::PlayAIDefeat()
{
    if (OwnerManager.IsValid() && OwnerManager->GetVoiceManager().IsValid())
    {
        OwnerManager->GetVoiceManager()->PlayVoiceLine(EVoiceContext::Defeat, AIVoicePackName);
    }
}

void ULesFightAIVoiceSystem::SetAIAggression(float InAggression)
{
    Aggression = InAggression;
    TauntFrequency = FMath::Clamp(InAggression * 0.4f, 0.1f, 0.8f);
}

FName ULesFightAIVoiceSystem::GetAIVoicePack() const
{
    return AIVoicePackName;
}

bool ULesFightAIVoiceSystem::WouldAISpeak() const
{
    return FMath::FRand() < TauntFrequency;
}
