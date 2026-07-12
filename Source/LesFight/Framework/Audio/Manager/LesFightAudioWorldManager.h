#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Framework/Audio/Data/LesFightAudioData.h"
#include "LesFightAudioWorldManager.generated.h"

class ULesFightAudioManager;
class ULesFightAudioEventSystem;
class ULesFightAudioSettingsManager;
class ULesFightMusicManager;
class ULesFightDynamicMusicController;
class ULesFightCharacterMusicSystem;
class ULesFightSoundEffectManager;
class ULesFightCombatSoundSystem;
class ULesFightMovementSoundSystem;
class ULesFightVoiceManager;
class ULesFightCharacterVoiceSystem;
class ULesFightAIVoiceSystem;
class ULesFightAmbientAudioManager;
class ULesFightArenaAudioSystem;
class ULesFightSpatialAudioSystem;
class ULesFightReverbZoneSystem;
class ULesFightCinematicAudio;
class ULesFightAudioEffectsProcessor;
class ULesFightAudioReplication;
class ULesFightAudioPerformance;
class ULesFightAudioDevTools;

UCLASS(Blueprintable, BlueprintType)
class ULesFightAudioWorldManager : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Audio|WorldManager")
    void Initialize();

    UFUNCTION(BlueprintCallable, Category = "Audio|WorldManager")
    void Shutdown();

    UFUNCTION(BlueprintCallable, Category = "Audio|WorldManager")
    void Tick(float DeltaTime);

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAudioManager* GetAudioManager() const { return AudioManager; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAudioEventSystem* GetEventSystem() const { return EventSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAudioSettingsManager* GetSettingsManager() const { return SettingsManager; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightMusicManager* GetMusicManager() const { return MusicManager; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightDynamicMusicController* GetDynamicMusicController() const { return DynamicMusicController; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightCharacterMusicSystem* GetCharacterMusicSystem() const { return CharacterMusicSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightSoundEffectManager* GetSoundEffectManager() const { return SoundEffectManager; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightCombatSoundSystem* GetCombatSoundSystem() const { return CombatSoundSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightMovementSoundSystem* GetMovementSoundSystem() const { return MovementSoundSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightVoiceManager* GetVoiceManager() const { return VoiceManager; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightCharacterVoiceSystem* GetCharacterVoiceSystem() const { return CharacterVoiceSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAIVoiceSystem* GetAIVoiceSystem() const { return AIVoiceSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAmbientAudioManager* GetAmbientAudioManager() const { return AmbientAudioManager; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightArenaAudioSystem* GetArenaAudioSystem() const { return ArenaAudioSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightSpatialAudioSystem* GetSpatialAudioSystem() const { return SpatialAudioSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightReverbZoneSystem* GetReverbZoneSystem() const { return ReverbZoneSystem; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightCinematicAudio* GetCinematicAudio() const { return CinematicAudio; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAudioEffectsProcessor* GetAudioEffectsProcessor() const { return AudioEffectsProcessor; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAudioReplication* GetAudioReplication() const { return AudioReplication; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAudioPerformance* GetAudioPerformance() const { return AudioPerformance; }

    UFUNCTION(BlueprintPure, Category = "Audio|WorldManager|Subsystems")
    ULesFightAudioDevTools* GetAudioDevTools() const { return AudioDevTools; }

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager")
    bool bInitialized;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAudioManager> AudioManager;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAudioEventSystem> EventSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAudioSettingsManager> SettingsManager;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightMusicManager> MusicManager;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightDynamicMusicController> DynamicMusicController;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightCharacterMusicSystem> CharacterMusicSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightSoundEffectManager> SoundEffectManager;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightCombatSoundSystem> CombatSoundSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightMovementSoundSystem> MovementSoundSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightVoiceManager> VoiceManager;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightCharacterVoiceSystem> CharacterVoiceSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAIVoiceSystem> AIVoiceSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAmbientAudioManager> AmbientAudioManager;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightArenaAudioSystem> ArenaAudioSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightSpatialAudioSystem> SpatialAudioSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightReverbZoneSystem> ReverbZoneSystem;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightCinematicAudio> CinematicAudio;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAudioEffectsProcessor> AudioEffectsProcessor;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAudioReplication> AudioReplication;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAudioPerformance> AudioPerformance;

    UPROPERTY(BlueprintReadOnly, Category = "Audio|WorldManager|Subsystems")
    TObjectPtr<ULesFightAudioDevTools> AudioDevTools;

private:
    template<typename T>
    T* CreateSubsystem();
};
