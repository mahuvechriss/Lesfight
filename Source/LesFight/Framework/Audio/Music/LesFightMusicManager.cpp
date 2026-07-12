#include "Framework/Audio/Music/LesFightMusicManager.h"

void ULesFightMusicManager::Initialize(ULesFightAudioWorldManager* InOwnerManager)
{
    OwnerManager = InOwnerManager;
    CurrentState = EMusicState::Menu;
    CurrentIntensity = 0.0f;
    MasterMusicVolume = 1.0f;
    bMusicPlaying = false;
    BuildMusicDatabase();
}

void ULesFightMusicManager::BuildMusicDatabase()
{
    MusicDatabase.Empty();

    auto AddState = [&](EMusicState State, const FString& Key, int32 BPM, float Intensity, const FString& Desc)
    {
        FMusicStateData Data;
        Data.State = State;
        Data.ThemeName = FName(*Key);
        Data.Intensity = Intensity;
        Data.TransitionDuration = 1.0f;
        Data.BeatsPerMinute = BPM;
        Data.MusicalKey = Desc;
        MusicDatabase.Add(State, Data);
    };

    AddState(EMusicState::Menu,                   TEXT("CalmMenu"),        80,  0.0f,  TEXT("Calm ambient menu theme - 80bpm"));
    AddState(EMusicState::CharacterSelect,        TEXT("CharacterSelect"), 90,  0.1f,  TEXT("Anticipation theme - 90bpm"));
    AddState(EMusicState::ArenaIntro,             TEXT("ArenaIntro"),      100, 0.2f,  TEXT("Building anticipation - 100bpm"));
    AddState(EMusicState::FightNeutral,           TEXT("FightNeutral"),    120, 0.3f,  TEXT("Balanced fight theme - 120bpm"));
    AddState(EMusicState::FightLowIntensity,      TEXT("FightLow"),        110, 0.2f,  TEXT("Low intensity combat - 110bpm"));
    AddState(EMusicState::FightMediumIntensity,   TEXT("FightMedium"),     140, 0.5f,  TEXT("Medium intensity combat - 140bpm"));
    AddState(EMusicState::FightHighIntensity,     TEXT("FightHigh"),       160, 0.8f,  TEXT("Fast paced combat - 160bpm"));
    AddState(EMusicState::FightCritical,          TEXT("FightCritical"),   180, 1.0f,  TEXT("Critical intensity combat - 180bpm"));
    AddState(EMusicState::PlayerAdvantage,        TEXT("Advantage"),       150, 0.7f,  TEXT("Player advantage theme - 150bpm"));
    AddState(EMusicState::PlayerDisadvantage,     TEXT("Disadvantage"),    130, 0.6f,  TEXT("Player disadvantage theme - 130bpm"));
    AddState(EMusicState::UltimateReady,          TEXT("UltimateReady"),   170, 0.9f,  TEXT("Ultimate ready buildup - 170bpm"));
    AddState(EMusicState::FinalHit,               TEXT("FinalHit"),        200, 1.0f,  TEXT("Final hit climax - 200bpm"));
    AddState(EMusicState::Victory,                TEXT("Victory"),         120, 0.0f,  TEXT("Victory fanfare - 120bpm"));
    AddState(EMusicState::Defeat,                 TEXT("Defeat"),          60,  0.0f,  TEXT("Defeat theme - 60bpm"));
}

void ULesFightMusicManager::PlayMusic(EMusicState State, float FadeDuration)
{
    if (!MusicDatabase.Contains(State)) return;
    CurrentState = State;
    CurrentIntensity = MusicDatabase[State].Intensity;
    bMusicPlaying = true;
}

void ULesFightMusicManager::StopMusic(float FadeDuration)
{
    bMusicPlaying = false;
}

void ULesFightMusicManager::PauseMusic()
{
    bMusicPlaying = false;
}

void ULesFightMusicManager::ResumeMusic()
{
    bMusicPlaying = true;
}

EMusicState ULesFightMusicManager::GetCurrentState() const
{
    return CurrentState;
}

bool ULesFightMusicManager::IsMusicPlaying() const
{
    return bMusicPlaying;
}

void ULesFightMusicManager::SetIntensity(float Intensity)
{
    CurrentIntensity = FMath::Clamp(Intensity, 0.0f, 1.0f);
}

float ULesFightMusicManager::GetIntensity() const
{
    return CurrentIntensity;
}

void ULesFightMusicManager::CrossfadeTo(EMusicState TargetState, float Duration)
{
    if (!MusicDatabase.Contains(TargetState)) return;
    CurrentState = TargetState;
    CurrentIntensity = MusicDatabase[TargetState].Intensity;
}
