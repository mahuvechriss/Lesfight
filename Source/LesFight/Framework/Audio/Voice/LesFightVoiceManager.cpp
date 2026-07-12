#include "LesFightVoiceManager.h"
#include "Framework/Audio/Data/LesFightAudioData.h"

ULesFightVoiceManager::ULesFightVoiceManager()
{
    FCharacterVoicePack DefaultMale;
    DefaultMale.VoicePackName = FName("DefaultMale");
    DefaultMale.VoiceLines.Emplace(EVoiceContext::Taunt, TArray<FString>{TEXT("Come on!"), TEXT("Is that all?"), TEXT("You can do better!"), TEXT("Not even close!")});
    DefaultMale.VoiceLines.Emplace(EVoiceContext::Pain, TArray<FString>{TEXT("Ugh!"), TEXT("Hngh!"), TEXT("Nngh!"), TEXT("Tch!")});
    DefaultMale.VoiceLines.Emplace(EVoiceContext::Victory, TArray<FString>{TEXT("Too easy"), TEXT("I win"), TEXT("Next!")});
    DefaultMale.VoiceLines.Emplace(EVoiceContext::Defeat, TArray<FString>{TEXT("Good fight"), TEXT("You earned it"), TEXT("Impressive")});
    DefaultMale.VoiceLines.Emplace(EVoiceContext::Ultimate, TArray<FString>{TEXT("This ends now!"), TEXT("Eat this!"), TEXT("FINISH HIM!")});
    DefaultMale.VoiceLines.Emplace(EVoiceContext::CombatCall, TArray<FString>{TEXT("Hyah!"), TEXT("Hmph!"), TEXT("Hah!"), TEXT("Yah!")});
    VoicePacks.Emplace(FName("DefaultMale"), DefaultMale);

    FCharacterVoicePack DefaultFemale;
    DefaultFemale.VoicePackName = FName("DefaultFemale");
    DefaultFemale.VoiceLines.Emplace(EVoiceContext::Taunt, TArray<FString>{TEXT("Is that your best?"), TEXT("Too slow!"), TEXT("Getting tired?")});
    DefaultFemale.VoiceLines.Emplace(EVoiceContext::Pain, TArray<FString>{TEXT("Ah!"), TEXT("Hey!"), TEXT("Ow!")});
    DefaultFemale.VoiceLines.Emplace(EVoiceContext::Victory, TArray<FString>{TEXT("Flawless"), TEXT("Done"), TEXT("Who's next?")});
    DefaultFemale.VoiceLines.Emplace(EVoiceContext::Defeat, TArray<FString>{TEXT("Well played"), TEXT("You win this time"), TEXT("Impressive")});
    DefaultFemale.VoiceLines.Emplace(EVoiceContext::Ultimate, TArray<FString>{TEXT("Say goodnight!"), TEXT("No mercy!"), TEXT("Game over!")});
    DefaultFemale.VoiceLines.Emplace(EVoiceContext::CombatCall, TArray<FString>{TEXT("Hi-yah!"), TEXT("Ha!"), TEXT("Ee-yah!")});
    VoicePacks.Emplace(FName("DefaultFemale"), DefaultFemale);

    FCharacterVoicePack AISamurai;
    AISamurai.VoicePackName = FName("AISamurai");
    AISamurai.VoiceLines.Emplace(EVoiceContext::Taunt, TArray<FString>{TEXT("You dishonor yourself"), TEXT("Pathetic"), TEXT("Face your end")});
    AISamurai.VoiceLines.Emplace(EVoiceContext::Pain, TArray<FString>{TEXT("Impressive..."), TEXT("Tch!"), TEXT("You have skill")});
    AISamurai.VoiceLines.Emplace(EVoiceContext::Victory, TArray<FString>{TEXT("Honor is satisfied"), TEXT("The path is clear"), TEXT("You fought well")});
    AISamurai.VoiceLines.Emplace(EVoiceContext::Defeat, TArray<FString>{TEXT("I am defeated"), TEXT("My journey ends"), TEXT("A worthy opponent")});
    AISamurai.VoiceLines.Emplace(EVoiceContext::Ultimate, TArray<FString>{TEXT("Forgive me!"), TEXT("KIAI!"), TEXT("This is my resolve!")});
    AISamurai.VoiceLines.Emplace(EVoiceContext::CombatCall, TArray<FString>{TEXT("Hya!"), TEXT("Sei!"), TEXT("Toh!")});
    VoicePacks.Emplace(FName("AISamurai"), AISamurai);

    FCharacterVoicePack AIBrawler;
    AIBrawler.VoicePackName = FName("AIBrawler");
    AIBrawler.VoiceLines.Emplace(EVoiceContext::Taunt, TArray<FString>{TEXT("You're nothing!"), TEXT("Fight me!"), TEXT("Stand still!")});
    AIBrawler.VoiceLines.Emplace(EVoiceContext::Pain, TArray<FString>{TEXT("Guh!"), TEXT("Grr!"), TEXT("Lucky shot!")});
    AIBrawler.VoiceLines.Emplace(EVoiceContext::Victory, TArray<FString>{TEXT("BOSS!"), TEXT("Who's the champ?"), TEXT("Too weak!")});
    AIBrawler.VoiceLines.Emplace(EVoiceContext::Defeat, TArray<FString>{TEXT("No way..."), TEXT("Can't be!"), TEXT("I'll be back!")});
    AIBrawler.VoiceLines.Emplace(EVoiceContext::Ultimate, TArray<FString>{TEXT("TIME TO RUMBLE!"), TEXT("THIS IS IT!"), TEXT("GOING ALL OUT!")});
    AIBrawler.VoiceLines.Emplace(EVoiceContext::CombatCall, TArray<FString>{TEXT("RAAH!"), TEXT("HRAAH!"), TEXT("COME ON!")});
    VoicePacks.Emplace(FName("AIBrawler"), AIBrawler);
}

void ULesFightVoiceManager::PlayVoiceLine(EVoiceContext Context, FName CharacterID)
{
    if (ActiveVoices.Num() >= MaxConcurrentVoices)
    {
        return;
    }

    FCharacterVoicePack* Pack = VoicePacks.Find(CharacterID);
    if (Pack == nullptr)
    {
        Pack = VoicePacks.Find(FName("DefaultMale"));
        if (Pack == nullptr)
        {
            return;
        }
    }

    TArray<FString>* Lines = Pack->VoiceLines.Find(Context);
    if (Lines == nullptr || Lines->Num() == 0)
    {
        return;
    }

    int32 Index = FMath::RandRange(0, Lines->Num() - 1);
    FName LineName = FName(*(*Lines)[Index]);

    ActiveVoices.Add(CharacterID);
    OnVoiceLineStarted.Broadcast(CharacterID, Context);

    if (OwnerManager.IsValid())
    {
        float* Pitch = VoicePitches.Find(CharacterID);
        float FinalPitch = Pitch != nullptr ? *Pitch : 1.0f;
        OwnerManager->PlayVoiceLine(LineName, CharacterID, Context, GlobalVoiceVolume, FinalPitch);
    }
}

void ULesFightVoiceManager::StopVoice()
{
    if (OwnerManager.IsValid())
    {
        OwnerManager->StopVoice();
    }
    ActiveVoices.Empty();
}

bool ULesFightVoiceManager::IsSpeaking() const
{
    return ActiveVoices.Num() > 0;
}

void ULesFightVoiceManager::SetVoicePitch(FName CharacterID, float Pitch)
{
    VoicePitches.Emplace(CharacterID, Pitch);
}

void ULesFightVoiceManager::SetVoiceVolume(float Volume)
{
    GlobalVoiceVolume = Volume;
}

int32 ULesFightVoiceManager::GetActiveVoiceCount() const
{
    return ActiveVoices.Num();
}

void ULesFightVoiceManager::PreloadVoicePack(FName PackName)
{
    if (OwnerManager.IsValid())
    {
        OwnerManager->PreloadVoicePack(PackName);
    }
}

void ULesFightVoiceManager::ClearVoiceCache()
{
    if (OwnerManager.IsValid())
    {
        OwnerManager->ClearVoiceCache();
    }
}

TArray<FName> ULesFightVoiceManager::GetAvailableVoicePacks() const
{
    TArray<FName> Keys;
    VoicePacks.GetKeys(Keys);
    return Keys;
}
