#include "Framework/Audio/Manager/LesFightAudioWorldManager.h"

#include "Framework/Audio/Core/LesFightAudioManager.h"
#include "Framework/Audio/Core/LesFightAudioEventSystem.h"
#include "Framework/Audio/Core/LesFightAudioSettingsManager.h"
#include "Framework/Audio/Music/LesFightMusicManager.h"
#include "Framework/Audio/Music/LesFightDynamicMusicController.h"
#include "Framework/Audio/Music/LesFightCharacterMusicSystem.h"
#include "Framework/Audio/SFX/LesFightSoundEffectManager.h"
#include "Framework/Audio/SFX/LesFightCombatSoundSystem.h"
#include "Framework/Audio/SFX/LesFightMovementSoundSystem.h"
#include "Framework/Audio/Voice/LesFightVoiceManager.h"
#include "Framework/Audio/Voice/LesFightCharacterVoiceSystem.h"
#include "Framework/Audio/Voice/LesFightAIVoiceSystem.h"
#include "Framework/Audio/Ambient/LesFightAmbientAudioManager.h"
#include "Framework/Audio/Ambient/LesFightArenaAudioSystem.h"
#include "Framework/Audio/Spatial/LesFightSpatialAudioSystem.h"
#include "Framework/Audio/Spatial/LesFightReverbZoneSystem.h"
#include "Framework/Audio/Cinematic/LesFightCinematicAudio.h"
#include "Framework/Audio/Effects/LesFightAudioEffectsProcessor.h"
#include "Framework/Audio/Multiplayer/LesFightAudioReplication.h"
#include "Framework/Audio/Performance/LesFightAudioPerformance.h"
#include "Framework/Audio/Testing/LesFightAudioDevTools.h"

template<typename T>
T* ULesFightAudioWorldManager::CreateSubsystem()
{
    T* Subsystem = NewObject<T>(this);
    Subsystem->Initialize(this);
    return Subsystem;
}

void ULesFightAudioWorldManager::Initialize()
{
    if (bInitialized) return;

    AudioManager = CreateSubsystem<ULesFightAudioManager>();
    EventSystem = CreateSubsystem<ULesFightAudioEventSystem>();
    SettingsManager = CreateSubsystem<ULesFightAudioSettingsManager>();
    MusicManager = CreateSubsystem<ULesFightMusicManager>();
    DynamicMusicController = CreateSubsystem<ULesFightDynamicMusicController>();
    CharacterMusicSystem = CreateSubsystem<ULesFightCharacterMusicSystem>();
    SoundEffectManager = CreateSubsystem<ULesFightSoundEffectManager>();
    CombatSoundSystem = CreateSubsystem<ULesFightCombatSoundSystem>();
    MovementSoundSystem = CreateSubsystem<ULesFightMovementSoundSystem>();
    VoiceManager = CreateSubsystem<ULesFightVoiceManager>();
    CharacterVoiceSystem = CreateSubsystem<ULesFightCharacterVoiceSystem>();
    AIVoiceSystem = CreateSubsystem<ULesFightAIVoiceSystem>();
    AmbientAudioManager = CreateSubsystem<ULesFightAmbientAudioManager>();
    ArenaAudioSystem = CreateSubsystem<ULesFightArenaAudioSystem>();
    SpatialAudioSystem = CreateSubsystem<ULesFightSpatialAudioSystem>();
    ReverbZoneSystem = CreateSubsystem<ULesFightReverbZoneSystem>();
    CinematicAudio = CreateSubsystem<ULesFightCinematicAudio>();
    AudioEffectsProcessor = CreateSubsystem<ULesFightAudioEffectsProcessor>();
    AudioReplication = CreateSubsystem<ULesFightAudioReplication>();
    AudioPerformance = CreateSubsystem<ULesFightAudioPerformance>();
    AudioDevTools = CreateSubsystem<ULesFightAudioDevTools>();

    bInitialized = true;
}

void ULesFightAudioWorldManager::Shutdown()
{
    if (!bInitialized) return;

    AudioManager = nullptr;
    EventSystem = nullptr;
    SettingsManager = nullptr;
    MusicManager = nullptr;
    DynamicMusicController = nullptr;
    CharacterMusicSystem = nullptr;
    SoundEffectManager = nullptr;
    CombatSoundSystem = nullptr;
    MovementSoundSystem = nullptr;
    VoiceManager = nullptr;
    CharacterVoiceSystem = nullptr;
    AIVoiceSystem = nullptr;
    AmbientAudioManager = nullptr;
    ArenaAudioSystem = nullptr;
    SpatialAudioSystem = nullptr;
    ReverbZoneSystem = nullptr;
    CinematicAudio = nullptr;
    AudioEffectsProcessor = nullptr;
    AudioReplication = nullptr;
    AudioPerformance = nullptr;
    AudioDevTools = nullptr;

    bInitialized = false;
}

void ULesFightAudioWorldManager::Tick(float DeltaTime)
{
    if (!bInitialized) return;

    if (DynamicMusicController)
    {
        DynamicMusicController->Tick(DeltaTime);
    }

    if (ArenaAudioSystem)
    {
        ArenaAudioSystem->Tick(DeltaTime);
    }

    if (AudioPerformance)
    {
        AudioPerformance->GetCurrentStats();
    }

    if (AudioReplication)
    {
        AudioReplication->ProcessReplicatedEvents();
    }
}
