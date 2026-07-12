#include "Framework/Audio/Music/LesFightCharacterMusicSystem.h"

void ULesFightCharacterMusicSystem::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    CurrentRole = EFighterMusicRole::Spectator;
    BuildDefaultThemes();
}

void ULesFightCharacterMusicSystem::BuildDefaultThemes()
{
    ThemeSongs.Empty();

    auto AddTheme = [&](const FString& ThemeName, const TArray<FString>& Songs)
    {
        ThemeSongs.Add(FName(*ThemeName), Songs);
    };

    AddTheme(TEXT("WarriorTheme"), {
        TEXT("EpicOrchestral_Intro"),
        TEXT("EpicOrchestral_Loop"),
        TEXT("EpicOrchestral_Climax"),
        TEXT("EpicOrchestral_Victory"),
        TEXT("EpicOrchestral_Defeat")
    });

    AddTheme(TEXT("AssassinTheme"), {
        TEXT("DarkElectronic_Intro"),
        TEXT("DarkElectronic_Loop"),
        TEXT("DarkElectronic_Climax"),
        TEXT("DarkElectronic_Victory"),
        TEXT("DarkElectronic_Defeat")
    });

    AddTheme(TEXT("MasterTheme"), {
        TEXT("Traditional_Intro"),
        TEXT("Traditional_Loop"),
        TEXT("Traditional_Climax"),
        TEXT("Traditional_Victory"),
        TEXT("Traditional_Defeat")
    });

    AddTheme(TEXT("BerserkerTheme"), {
        TEXT("HeavyMetal_Intro"),
        TEXT("HeavyMetal_Loop"),
        TEXT("HeavyMetal_Climax"),
        TEXT("HeavyMetal_Victory"),
        TEXT("HeavyMetal_Defeat")
    });
}

void ULesFightCharacterMusicSystem::RegisterCharacterTheme(FName CharacterID, FName ThemeName)
{
    if (CharacterID.IsNone() || ThemeName.IsNone()) return;
    CharacterThemes.Add(CharacterID, ThemeName);
}

void ULesFightCharacterMusicSystem::PlayEntranceMusic(FName CharacterID)
{
    if (CharacterID.IsNone()) return;
}

void ULesFightCharacterMusicSystem::PlayVictoryMusic(FName CharacterID)
{
    if (CharacterID.IsNone()) return;
}

void ULesFightCharacterMusicSystem::PlayDefeatMusic(FName CharacterID)
{
    if (CharacterID.IsNone()) return;
}

void ULesFightCharacterMusicSystem::PlayUltimateMusic(FName CharacterID)
{
    if (CharacterID.IsNone()) return;
}

void ULesFightCharacterMusicSystem::SetPlayerMusicRole(EFighterMusicRole Role)
{
    CurrentRole = Role;
}

FName ULesFightCharacterMusicSystem::GetCharacterTheme(FName CharacterID) const
{
    const FName* Theme = CharacterThemes.Find(CharacterID);
    return Theme ? *Theme : NAME_None;
}

void ULesFightCharacterMusicSystem::ClearCharacterThemes()
{
    CharacterThemes.Empty();
}
