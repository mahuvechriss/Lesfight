# Module 12: Advanced Audio, Music & Dynamic Sound System

## Overview
The Advanced Audio System provides a comprehensive AAA-quality audio framework for
cinematic martial arts battles. It features dynamic music that responds to combat
intensity, style-specific combat sounds, character voice systems, spatial audio
with reverb zones, cinematic audio moments, and full multiplayer synchronization.

## Architecture

### Directory Structure
```
Framework/Audio/
├── Data/
│   └── LesFightAudioData.h                       Core enums, structs, data asset
├── Core/
│   ├── LesFightAudioManager.h/.cpp               Central audio coordinator
│   ├── LesFightAudioEventSystem.h/.cpp            Event system with cooldowns
│   └── LesFightAudioSettingsManager.h/.cpp        Volume settings persistence
├── Music/
│   ├── LesFightMusicManager.h/.cpp                Music state playback & crossfade
│   ├── LesFightDynamicMusicController.h/.cpp      7-layer intensity system
│   └── LesFightCharacterMusicSystem.h/.cpp        Character themes (entrance/victory/defeat/ultimate)
├── SFX/
│   ├── LesFightSoundEffectManager.h/.cpp          SFX pool (64 max), combat & movement sounds
│   ├── LesFightCombatSoundSystem.h/.cpp           Style-specific combat audio (6 styles)
│   └── LesFightMovementSoundSystem.h/.cpp         Footstep/slide/dodge/landing sounds
├── Voice/
│   ├── LesFightVoiceManager.h/.cpp                Voice line playback (4 concurrent max)
│   ├── LesFightCharacterVoiceSystem.h/.cpp        Character-to-voice-pack assignment
│   └── LesFightAIVoiceSystem.h/.cpp               AI personality-based voice behavior
├── Ambient/
│   ├── LesFightAmbientAudioManager.h/.cpp         15-sound ambient library with crossfade
│   └── LesFightArenaAudioSystem.h/.cpp            Per-arena audio profiles & weather audio
├── Spatial/
│   ├── LesFightSpatialAudioSystem.h/.cpp          3D spatialization, occlusion, doppler
│   └── LesFightReverbZoneSystem.h/.cpp            7 reverb presets, zone enter/exit detection
├── Cinematic/
│   └── LesFightCinematicAudio.h/.cpp              Slow-motion, ultimate, finisher, dramatic silence
├── Effects/
│   └── LesFightAudioEffectsProcessor.h/.cpp       Reverb, EQ, filters, compression
├── Multiplayer/
│   └── LesFightAudioReplication.h/.cpp            Audio state sync, duplicate prevention
├── Performance/
│   └── LesFightAudioPerformance.h/.cpp            Sound pool, quality levels, profiling
├── Testing/
│   └── LesFightAudioDevTools.h/.cpp               Debug mode, benchmarks, audio report
├── Manager/
│   └── LesFightAudioWorldManager.h/.cpp           Top-level orchestrator (21 subsystems)
└── Documentation/
    └── Module12_Documentation.md
```

### Component Diagram
```
ULesFightAudioWorldManager (Orchestrator — 21 subsystems)
├── Core
│   ├── AudioManager — Bus volumes (7 buses), pause/resume, active sound count
│   ├── EventSystem — 200-entry history, cooldowns, listener registry
│   └── SettingsManager — Load/save to AudioSettings.ini, per-bus access
├── Music
│   ├── MusicManager — 14 states (Menu→Defeat), crossfade, BPM range 80-180
│   ├── DynamicController — 7 layers (Rhythm at 0.2 → FX at 1.0), intensity smoothing
│   └── CharacterMusic — 4 default themes, role-aware playback
├── SFX
│   ├── SoundEffectManager — 14 combat + 8 movement sound types, pool of 64
│   ├── CombatSoundSystem — 6 style profiles (Karate=sharp, MuayThai=heavy, etc)
│   └── MovementSoundSystem — 10 terrain footstep libraries, speed-based selection
├── Voice
│   ├── VoiceManager — 4 default packs, 4 concurrent limit, delegates
│   ├── CharacterVoice — 8 voice contexts (taunt→entrance), per-character assignment
│   └── AIVoice — 4 personality voices, frequency-gated taunts, event mapping
├── Ambient
│   ├── AmbientManager — 15 ambient sounds, crossfade transitions, 8 max concurrent
│   └── ArenaAudio — Per-arena profiles, weather audio overlay
├── Spatial
│   ├── SpatialAudio — 3D position, attenuation (100-2000), occlusion, doppler
│   └── ReverbZones — 7 presets, zone enter/exit delegates
├── Cinematic
│   └── CinematicAudio — Slow-motion, ultimate/finisher sequences, dramatic silence
├── Effects
│   └── AudioEffectsProcessor — Reverb, 3-band EQ, LPF/HPF, compression
├── Multiplayer
│   └── AudioReplication — State sync, 0.1s duplicate prevention, queue (50)
├── Performance
│   └── AudioPerformance — 5 quality levels (16-128 sounds), profiling, reports
└── Testing
    └── AudioDevTools — Test sounds, benchmarks, audio stats display
```

## Dynamic Music System
| Layer | Threshold | Description |
|-------|-----------|-------------|
| Rhythm | 0.2 (Low) | Basic beat, always present |
| Bass | 0.4 (Medium-Low) | Bass line, adds weight |
| Melody | 0.6 (Medium) | Main melody, fight is engaged |
| Harmony | 0.7 (Medium-High) | Harmonic support, pressure building |
| Percussion | 0.8 (High) | Intense drums, combo rewards |
| Vocals | 0.9 (Very High) | Climactic vocals, near victory |
| FX | 1.0 (Maximum) | Full intensity, final moments |

## Music States
| State | BPM | Context |
|-------|-----|---------|
| Menu | 80 | Character select calm |
| ArenaIntro | 90 | Arena showcase |
| FightNeutral | 120 | Balanced combat |
| FightLowIntensity | 100 | Poking, neutral game |
| FightMediumIntensity | 140 | Active exchanges |
| FightHighIntensity | 160 | Pressure, combos |
| FightCritical | 180 | Low health, desperation |
| UltimateReady | 150 | Special meter full |
| Victory | 130 | Winning fanfare |
| Defeat | 70 | Losing theme |

## Fighting Style Audio Profiles
| Style | Impact | Character | Tempo |
|-------|--------|-----------|-------|
| Karate | Sharp snaps | Traditional | Moderate |
| MuayThai | Heavy thuds | Powerful | Slow |
| Boxing | Fast pops | Rhythmic | Fast |
| Taekwondo | Crisp kicks | Light | Fast |
| Judo | Deep thuds | Heavy | Slow |
| Wushu | Swooshes | Acrobatic | Varied |

## Reverb Presets
| Preset | Wet | Decay | PreDelay |
|--------|-----|-------|----------|
| None | 0.0 | 0.0s | 0ms |
| SmallRoom | 0.3 | 0.5s | 10ms |
| MediumRoom | 0.5 | 1.0s | 15ms |
| LargeRoom | 0.6 | 1.8s | 20ms |
| Cathedral | 0.8 | 4.0s | 30ms |
| Arena | 0.6 | 2.5s | 25ms |
| Outdoor | 0.2 | 0.8s | 5ms |
| Underground | 0.7 | 3.0s | 20ms |

## Performance Quality Levels
| Level | Max Sounds | Pool Size | Target |
|-------|-----------|-----------|--------|
| 1 (Low) | 16 | 32 MB | 30 FPS |
| 2 (Medium) | 32 | 64 MB | 45 FPS |
| 3 (High) | 64 | 128 MB | 60 FPS |
| 4 (Epic) | 64 | 256 MB | 60 FPS+ |
| 5 (Cinematic) | 128 | 512 MB | 30 FPS |

## Integration Points
- **Combat System (Module 4)**: CombatSoundSystem hooks into HitDetection for impact sounds
- **Martial Arts (Module 7)**: StyleBehavior maps to style audio profiles
- **Arena (Module 11)**: ArenaAudioSystem reads weather/terrain/arena type for audio environment
- **Character System (Module 3)**: CharacterVoiceSystem uses character ID for voice packs
- **AI Fighter (Module 10)**: AIVoiceSystem uses personality type for voice behavior
- **Animation (Module 5)**: Animation events trigger EAIAnimationEvent mapping to voice/sfx
- **Multiplayer (Module 6)**: AudioReplication syncs essential audio events

## File Count: 46 files (23 .h, 22 .cpp, 1 .md)
