# Module 13: Advanced Visual Effects & Cinematic Presentation System

## Overview
The Advanced Visual Effects & Cinematic Presentation System delivers AAA-quality combat
VFX with dynamic impact effects, martial arts style visuals, character auras, motion
trails, slow-motion sequences, ultimate move presentations, post-processing, and
environmental reactions — all optimized for multiplayer and performance scalability.

## Architecture

### Directory Structure
```
Framework/VFX/
├── Data/
│   └── LesFightVFXData.h                       Core enums, structs, data asset
├── Core/
│   ├── LesFightVFXManager.h/.cpp               Central VFX coordinator
│   ├── LesFightNiagaraEffectManager.h/.cpp      Niagara library (23 systems, 50 max)
│   └── LesFightVFXEventSystem.h/.cpp            VFX event system (200 history)
├── Combat/
│   ├── LesFightImpactEffectSystem.h/.cpp        13 impact types with decals
│   ├── LesFightMartialArtsVFX.h/.cpp            6 style visual profiles
│   └── LesFightMotionEffectSystem.h/.cpp        Trails, afterimages, speed lines
├── Character/
│   ├── LesFightCharacterAuraSystem.h/.cpp       5 aura types, style color overrides
│   └── LesFightEnergyEffectSystem.h/.cpp        Waves, shockwaves, projectiles
├── Cinematic/
│   ├── LesFightCinematicEffectManager.h/.cpp    8 event types, ultimate chains
│   ├── LesFightSlowMotionSystem.h/.cpp          Time dilation with enter/hold/exit
│   └── LesFightUltimatePresentation.h/.cpp      4 style ultimate sequences
├── Camera/
│   └── LesFightCameraEffects.h/.cpp             Shake, FOV zoom, rotation effects
├── PostProcessing/
│   └── LesFightPostProcessingManager.h/.cpp     8 presets with smooth transitions
├── Environment/
│   ├── LesFightEnvironmentalVFX.h/.cpp          Dust, debris, water, smoke, weather
│   └── LesFightLightingEffects.h/.cpp           Combat flash, pulse, character glow
├── Multiplayer/
│   └── LesFightVFXReplication.h/.cpp            Event sync, duplicate prevention
├── Performance/
│   └── LesFightVFXPerformance.h/.cpp            4 quality levels, benchmarks
├── Testing/
│   └── LesFightVFXDevTools.h/.cpp               Debug mode, stress tests, reports
├── Manager/
│   └── LesFightVFXWorldManager.h/.cpp           Top-level orchestrator (18 subsystems)
└── Documentation/
    └── Module13_Documentation.md
```

### Component Diagram
```
ULesFightVFXWorldManager (Orchestrator — 18 subsystems)
├── Core
│   ├── VFXManager — Active effects (100 max), global scale, pause/resume
│   ├── NiagaraManager — 23 Niagara entries, 50 max active, usage tracking
│   └── EventSystem — 200-event history, cooldowns, listener registry
├── Combat VFX
│   ├── ImpactEffectSystem — 13 types, decals, normal-aligned spawn
│   ├── MartialArtsVFX — 6 style colors, overrides, Realistic/Fantasy/Cinematic modes
│   └── MotionEffectSystem — 7 trail types, afterimages (5 max), speed lines
├── Character VFX
│   ├── AuraSystem — 5 auras (Power/Ultimate/LowHealth/Victory/Entrance), pulse
│   └── EnergyEffectSystem — 4 wave types, projectiles, impact rings
├── Cinematic
│   ├── CinematicEffectManager — 8 events, 6-stage ultimate chains
│   ├── SlowMotionSystem — Enter/hold/exit phases, priority-based
│   └── UltimatePresentation — 4 style sequences, full camera/VFX choreography
├── Camera
│   └── CameraEffects — 13 impact shake defs, dynamic FOV, rotation
├── PostProcessing
│   └── PostProcessing — 8 presets (Default→Defeat), smooth transitions
├── Environment
│   ├── EnvironmentalVFX — Dust, debris, water, smoke, fire, weather
│   └── LightingEffects — Flash, pulse, character glow
├── Multiplayer
│   └── VFXReplication — Queue (50 max), 0.2s duplicate window
├── Performance
│   └── VFXPerformance — 4 tiers (Low 1K particles → Ultra 50K), benchmarks
└── Testing
    └── VFXDevTools — Stress tests, all-effects preview, reports
```

## Impact Effects
| Type | Scale | Lifetime | Decal | Camera Shake |
|------|-------|----------|-------|-------------|
| LightPunch | 0.5x | 0.5s | Small | 0.3 intensity |
| HeavyPunch | 1.0x | 0.8s | Medium | 0.6 intensity |
| LightKick | 0.6x | 0.5s | Small | 0.4 intensity |
| HeavyKick | 1.1x | 0.8s | Medium | 0.7 intensity |
| SpecialAttack | 1.5x | 1.0s | Large | 0.8 intensity |
| UltimateAttack | 2.0x | 1.5s | Large+ | 1.0 intensity |
| BlockImpact | 0.4x | 0.3s | None | 0.2 intensity |
| Knockdown | 1.2x | 1.0s | None | 0.7 intensity |

## Post-Processing Presets
| Preset | MotionBlur | DOF | Bloom | Vignette | Saturation | Contrast |
|--------|-----------|-----|-------|----------|-----------|----------|
| Default | 0.0 | 0.0 | 0.5 | 0.2 | 1.0 | 1.0 |
| Combat | 0.1 | 0.0 | 0.6 | 0.3 | 1.0 | 1.0 |
| Cinematic | 0.3 | 0.7 | 0.8 | 0.5 | 1.1 | 1.2 |
| SlowMotion | 0.5 | 0.5 | 0.7 | 0.4 | 1.0 | 1.0 |
| Ultimate | 0.4 | 0.3 | 1.0 | 0.6 | 1.2 | 1.3 |
| LowHealth | 0.1 | 0.2 | 0.3 | 0.7 | 0.7 (red) | 0.8 |
| Victory | 0.2 | 0.4 | 1.2 | 0.3 | 1.3 | 1.0 |
| Defeat | 0.3 | 0.5 | 0.2 | 0.6 | 0.5 | 0.7 |

## Style Visual Colors
| Style | Color | Trail Type | Impact Effect |
|-------|-------|------------|---------------|
| Karate | Red | Sharp wind | Quick snap |
| MuayThai | Orange | Heavy | Shockwave ring |
| Boxing | Yellow | Fast pop | Rapid spark |
| Taekwondo | Blue | Swift kick | Crisp burst |
| Judo | Green | Grab | Heavy thud |
| Wushu | Purple | Acrobatic | Energy ribbon |
| Kickboxing | Red | Mixed | Combo trails |
| ShaolinKungFu | Gold | Flowing | Energy wave |

## Performance Quality Levels
| Level | Max Particles | Max Niagara Systems | Target |
|-------|--------------|-------------------|--------|
| Low | 1,000 | 10 | 30 FPS |
| Medium | 5,000 | 25 | 45 FPS |
| High | 20,000 | 50 | 60 FPS |
| Ultra | 50,000 | 100 | 60 FPS+ |

## Integration Points
- **Combat System (Module 4)**: ImpactEffectSystem hooks into HitDetection for hit VFX
- **Martial Arts (Module 7)**: MartialArtsVFX uses EFightingStyle for style-specific visuals
- **Animation (Module 5)**: Motion trails follow attack animations
- **Arena (Module 11)**: EnvironmentalVFX reads weather/terrain for scene effects
- **Camera (Module 11)**: CameraEffects integrate with ArenaCamera for shakes/FOV
- **Audio (Module 12)**: Cinematic effects synchronize with audio timing
- **Character (Modules 3,8)**: Aura systems attach to character meshes
- **Multiplayer (Module 6)**: VFXReplication syncs major events over LAN

## File Count: 40 files (20 .h, 19 .cpp, 1 .md)
