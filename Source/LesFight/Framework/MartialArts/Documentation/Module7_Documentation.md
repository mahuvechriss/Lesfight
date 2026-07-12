# Module 7: Martial Arts Combat & Cinematic Movement System

## Overview

Module 7 transforms the existing combat system into a cinematic martial arts experience with 13 fighting styles, 6 stances, 13 advanced movement types, 7 counter types, 6 dodge types, 9 combo expansion types, and full cinematic/ physics/motion-matching support.

---

## Architecture (74 files)

```
Framework/MartialArts/
├── Data/
│   └── LesFightMartialArtsData.h          # 18 enums, 20+ structs, data asset
├── Styles/
│   ├── LesFightFightingStyle.h/.cpp       # Base style class (abstract)
│   └── LesFightStyleManager.h/.cpp        # Style registry, equip/unequip
├── Stances/
│   └── LesFightStanceSystem.h/.cpp        # Stance switching, modifiers
├── Movement/
│   └── LesFightAdvancedMovement.h/.cpp    # Dash, wall run, vault, etc.
├── Counters/
│   └── LesFightCounterSystem.h/.cpp       # Counter windows, perfect counters
├── Dodge/
│   └── LesFightAdvancedDodgeSystem.h/.cpp # Perfect dodge, i-frames
├── Combos/
│   └── LesFightComboExpansionSystem.h/.cpp # Branching, air, wall combos
├── Environment/
│   └── LesFightEnvironmentalCombat.h/.cpp  # Wall bounce, slam, finishers
├── Cinematic/
│   └── LesFightCinematicCombat.h/.cpp      # Slow motion, dynamic camera, ultimates
├── Physics/
│   └── LesFightPhysicsMotion.h/.cpp        # Cloth, hair, momentum, weight
├── MotionMatching/
│   └── LesFightMotionMatchingSystem.h/.cpp # Pose matching, motion warping
├── AIHooks/
│   └── LesFightCombatAIHooks.h/.cpp        # AI decision context, profiles
├── Audio/
│   └── LesFightMartialArtsAudio.h/.cpp     # Style-specific voice/impact/clothing
├── VFX/
│   └── LesFightMartialArtsVFX.h/.cpp       # Trails, dust, shockwaves, auras
├── HUD/
│   └── LesFightMartialArtsHUD.h/.cpp       # Style/stance display, combo counter
├── Performance/
│   └── LesFightMartialArtsPerformance.h/.cpp # LOD, frame budgeting, quality presets
├── Testing/
│   └── LesFightMartialArtsDevTools.h/.cpp   # Debug overlay, style switching, sims
├── Orchestration/
│   └── LesFightMartialArtsManager.h/.cpp    # Top-level orchestrator (16 sub-managers)
└── Documentation/
    └── Module7_Documentation.md             # This file
```

## Core Systems

### 1. Fighting Styles (data-driven via `FStyleAttributes`)
| Style | Damage | Speed | Defense | Signature |
|-------|--------|-------|---------|-----------|
| ShaolinKungFu | 1.1x | 1.1x | 1.0x | Fast strikes, acrobatic kicks |
| WingChun | 1.0x | 1.3x | 1.1x | Close-range chain punches |
| TaiChi | 0.9x | 0.8x | 1.4x | Parry-focused, counter master |
| Wushu | 1.0x | 1.2x | 0.9x | Acrobatic, aerial combos |
| DrunkenFist | 1.2x | 1.0x | 0.8x | Unpredictable, dodge specialist |
| JeetKuneDo | 1.1x | 1.2x | 1.0x | Intercepting, fast counters |
| MuayThai | 1.3x | 0.9x | 1.1x | Heavy strikes, clinch game |
| Taekwondo | 1.1x | 1.3x | 0.9x | High kicks, fast footwork |
| Karate | 1.2x | 1.0x | 1.1x | Strong basics, powerful strikes |
| Judo | 0.9x | 0.9x | 1.3x | Throws, grapples, counters |
| BJJ | 0.8x | 0.8x | 1.5x | Ground game, submissions |
| Boxing | 1.1x | 1.2x | 1.1x | Footwork, head movement, hooks |
| Kickboxing | 1.2x | 1.1x | 1.0x | Balanced striking, combos |

### 2. Stance System (6 stances)
| Stance | Damage | Speed | Defense | Special |
|--------|--------|-------|---------|---------|
| Neutral | 1.0x | 1.0x | 1.0x | Balanced |
| Offensive | 1.2x | 1.0x | 0.8x | +15% combo damage |
| Defensive | 0.8x | 1.0x | 1.3x | +20% counter chance, +20% stamina regen |
| Agile | 0.9x | 1.3x | 1.0x | +30% dodge window |
| Heavy | 1.3x | 0.8x | 1.2x | -30% stamina regen |
| StyleSpecific | 1.1x | 1.1x | 1.1x | Varies per style |

### 3. Advanced Movement (13 types)
Dash, AirDash, WallRun, WallJump, WallKick, Vault, Slide, QuickStep, SideStep, BackFlip, FrontFlip, CombatRoll, SprintBurst

Each with configurable: speed, distance, duration, stamina cost, cancel options, cooldown

### 4. Counter System (7 types)
CounterAttack, PerfectCounter, CounterGrab, CounterThrow, CounterKick, CounterPunch, SlowMotionFinish

- Configurable timing windows (open time, duration)
- Perfect counter = first 1/3 of window → slow-motion trigger
- Consecutive counter tracking, damage multipliers (1.5x base)

### 5. Advanced Dodge (6 types)
PerfectDodge, DirectionalDodge, AirDodge, RollingDodge, BackStep, SideEvade

- Per-dodge i-frame duration
- Perfect dodge window (configurable, default 100ms)
- Slow-motion on perfect dodge

### 6. Combo Expansion (9 types)
Branching, AirCombo, Launcher, WallCombo, GroundCombo, CancelCombo, StyleSpecific, UltimateChain

- Chain length limits, chain windows, hit tracking
- Conditional chains (requires launcher, wall, ground)

### 7. Environmental Combat
WallBounce (10 base dmg + stun), WallSlam (20 dmg), EnvironmentalFinisher, ObjectDestruction

- Auto-detection of nearby walls via sphere sweep
- Configurable bounce/slam damage, knockback distance, stun duration

### 8. Cinematic Effects
SlowMotion (0.25x time scale), DynamicCamera (FOV, offset, blend), UltimateCinematic, SignatureMove, DramaticImpact (camera shake + shockwave), VictoryCutscene

### 9. Physics Motion
Cloth, Hair, Accessory, SecondaryMotion, Momentum, BodyWeight, RealisticRecovery

- Configurable settings per simulation type
- Momentum inheritance (50% default), body weight influence, recovery rate

### 10. Motion Matching
4 modes: Disabled, BasicBlending, MotionMatching, PredictiveSelection, FullPipeline

- Configurable blend speed, search radius, max pose matches, warp speed
- Terrain adaptation, directional blending

### 11. AI Hooks
FAICombatDecisionContext: self/target reference, distance, health/stamina/ultimate %, state flags

FCombatAIHooks: preferred style/distance, aggression (5 levels), counter/dodge probabilities, reaction times

### 12. Audio Integration
Style-specific profiles: attack/hit/counter/ultimate/victory/defeat voice sets, impact/clothing/footstep sounds

Configurable voice frequency, cooldown system, exertion-based breathing

### 13. Visual Effects
AttackTrail, ImpactEffect, DodgeTrail, CounterEffect, UltimateEffect, Dust, Shockwave, Aura

4 intensity levels: Realistic, Enhanced, Cinematic, Fantasy
Per-style aura colors (primary/secondary), dynamic lighting, camera shake

### 14. HUD Integration
Style display, stance display, combo counter, counter notifications, ultimate meter, technique indicators, environmental prompts, cinematic overlay, slow-motion indicator, hit notifications, stance modifier display

### 15. Performance
- Quality presets (0-3) controlling LOD distances
- Dynamic LOD system (auto-reduces quality when frame budget exceeded)
- 60 FPS target, configurable per-component budgets
- Active animation/VFX tracking

---

## Integration Points

1. **BaseFighter** should create a `ULesFightMartialArtsManager` sub-object in `CreateComponents()` and call `InitializeWithOwner(this)` in `BeginPlay()`
2. **CombatComponent** should query `StyleManager->GetCurrentAttributes()` for damage/speed modifiers
3. **AnimationComponent** should use `MotionMatching->FindBestPose()` for motion matching
4. **HUD** should bind to `HUDSystem` delegates for UI updates

## Testing Tools

- `DevTools->SwitchFightingStyle(StyleID)` — instant style swap
- `DevTools->DisplayActiveStance()` — log current stance
- `DevTools->TestComboPath({...})` — simulate combo execution
- `DevTools->VisualizeCounterWindows()` — show counter timing
- `DevTools->SetInfiniteStamina(true)` — debug mode
- `DevTools->SetOneHitKO(true)` — debug mode
- `DevTools->SimulatePerfectCounter()` — test counter system
- `DevTools->LogAllStyles()` — dump all style attributes
