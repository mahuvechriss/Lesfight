# Module 10: Advanced Fighting AI Opponent System

## Overview
The Advanced Fighting AI Opponent System provides intelligent CPU-controlled fighters
capable of realistic combat behavior, style-specific tactics, adaptive learning,
multiple difficulty levels, and personality-driven decision-making. AI opponents
understand combat situations, react to player actions, and provide challenging
martial arts battles.

## Architecture

### Directory Structure
```
Framework/FightingAI/
├── Data/
│   └── LesFightAIData.h              Core enums, structs, data asset
├── Core/
│   ├── LesFightAIFighterController.h/.cpp    AI controller (AActor)
│   ├── LesFightAIDecisionManager.h/.cpp      Action scoring & selection
│   ├── LesFightAIStateManager.h/.cpp         Behavior state machine
│   ├── LesFightAIBehaviorTree.h/.cpp         Behavior evaluation tree
│   └── LesFightAIBlackboard.h/.cpp           Shared knowledge storage
├── Perception/
│   ├── LesFightAIPerceptionSystem.h/.cpp     Target detection & awareness
│   ├── LesFightAISituationalAwareness.h/.cpp Threat & range analysis
│   ├── LesFightAIAttackRecognizer.h/.cpp     Player attack prediction
│   └── LesFightAIMovementPredictor.h/.cpp    Position prediction
├── Combat/
│   ├── LesFightAIOffensiveManager.h/.cpp     Attack & combo decisions
│   ├── LesFightAIDefensiveManager.h/.cpp     Block, dodge, parry, counter
│   ├── LesFightAIComboSystem.h/.cpp          Combo execution (12+ presets)
│   └── LesFightAICounterSystem.h/.cpp        Counter-attack timing
├── Style/
│   ├── LesFightAIStyleBehavior.h/.cpp       8 fighting style profiles
│   └── LesFightAIDifficultyManager.h/.cpp   5 difficulty presets
├── Learning/
│   ├── LesFightAIAdaptiveLearning.h/.cpp     Player habit analysis
│   └── LesFightAIReactionSystem.h/.cpp       Event-driven reactions
├── Movement/
│   ├── LesFightAIMovementManager.h/.cpp      Distance control & navigation
│   └── LesFightAITacticalAnalyzer.h/.cpp     Tactical positioning
├── Training/
│   └── LesFightAITrainingMode.h/.cpp         Training AI behaviors
├── Boss/
│   └── LesFightAIBossSystem.h/.cpp           Multi-phase boss framework
├── Integration/
│   ├── LesFightAIAnimationHandler.h/.cpp     Animation & montage control
│   ├── LesFightAIAudioHandler.h/.cpp         Voice lines & sound effects
│   └── LesFightAIPerformance.h/.cpp          Update rate & budget control
├── Testing/
│   └── LesFightAIDevTools.h/.cpp             Debug visualization & benchmarks
├── Manager/
│   └── LesFightAIFighterManager.h/.cpp       Top-level orchestrator
└── Documentation/
    └── Module10_Documentation.md
```

### Component Diagram
```
ULesFightAIFighterManager (Orchestrator)
└── Manages N x ULesFightAIFighterController
    ├── Blackboard — Shared knowledge (target pos, health, etc.)
    ├── StateManager — Behavior state machine (Idle→Patrol→Engage→Combat→Retreat→Recovery)
    ├── DecisionManager — Action scoring (14 action types) with difficulty & personality modifiers
    │   └── BehaviorTree — Profile-weighted candidate evaluation
    ├── PerceptionSystem — Detection range/FOV checks, awareness update
    │   ├── SituationalAwareness — Threat level, range classification, arena edge
    │   ├── AttackRecognizer — Player attack prediction with tells
    │   └── MovementPredictor — Position extrapolation with confidence
    ├── OffensiveManager — Attack selection, special/ultimate usage, combo tracking
    ├── DefensiveManager — Block/dodge/parry/counter scoring (4-weight system)
    ├── ComboSystem — Database of 12+ style-specific combo sequences
    ├── CounterSystem — Counter window (0.3s), timing learning, aggression-scaled success
    ├── StyleBehavior — 8 fighting style profiles (Karate, MuayThai, Boxing, etc.)
    ├── DifficultyManager — 5 presets (Easy→Master) with per-stat tuning
    ├── AdaptiveLearning — Player action/combo frequency analysis, strategy adaptation
    ├── ReactionSystem — 18 event→action mappings with configurable delay
    ├── MovementManager — Distance control, approach/retreat/strafe
    ├── TacticalAnalyzer — Arena positioning, corner detection, ideal range
    ├── TrainingMode — 6 training modes (passive, blocking, combo, counter, dodge, full)
    ├── BossSystem — 5-phase boss progression with special abilities
    ├── AnimationHandler — Action/event→animation mapping with blend
    ├── AudioHandler — Voice reactions, taunts, hit/miss/block sounds
    └── Performance — Update rate (20/s default), decision budget (5ms), profiling
```

## AI Pipeline (per controller per tick)
1. **PerceptionSystem.Update()** — Detect target, check range/FOV, update perception data
2. **SituationalAwareness.Update()** — Classify range, compute threat level, check arena
3. **AttackRecognizer.Recognize()** — Predict incoming attack from player movement
4. **MovementPredictor.Predict()** — Estimate future player position
5. **AdaptiveLearning.Analyze()** — Update player habit data if enough observations
6. **DecisionManager.MakeDecision()** — Score all actions → pick best
7. **OffensiveManager/DefensiveManager** — Generate combat-specific decisions
8. **BehaviorTree.Evaluate()** — Apply style/difficulty weighting
9. **ComboSystem/CounterSystem** — Execute combo sequences or counters
10. **ReactionSystem.React()** — Trigger event-driven responses
11. **MovementManager.Update()** — Execute positional movement
12. **AnimationHandler/AudioHandler** — Apply animations & sounds

## Difficulty Presets
| Setting        | Easy   | Normal | Hard   | Expert | Master |
|---------------|--------|--------|--------|--------|--------|
| Reaction Min  | 0.5s   | 0.3s   | 0.2s   | 0.1s   | 0.05s  |
| Reaction Max  | 0.8s   | 0.5s   | 0.3s   | 0.2s   | 0.1s   |
| Block Chance  | 30%    | 50%    | 70%    | 85%    | 95%    |
| Parry Chance  | 10%    | 20%    | 40%    | 60%    | 75%    |
| Max Combo     | 2      | 3      | 4      | 5      | 6      |
| Mistake Chance| 30%    | 15%    | 8%     | 3%     | 1%     |
| Learning Rate | 0.02   | 0.05   | 0.1    | 0.15   | 0.2    |

## Personality Types
| Type      | Aggression | Defense | Risk  | Behavior |
|-----------|-----------|---------|-------|----------|
| Warrior   | 0.9       | 0.3     | 0.8   | High pressure, fearless |
| Assassin  | 0.7       | 0.4     | 0.6   | Fast, evasive, precise |
| Master    | 0.3       | 0.9     | 0.2   | Defensive, counter-focused |
| Berserker | 1.0       | 0.2     | 1.0   | All-out offense, no defense |
| Trickster | 0.6       | 0.5     | 0.7   | Unpredictable, feints |
| Technician| 0.5       | 0.7     | 0.4   | Perfect execution, optimal |
| Brawler   | 0.8       | 0.5     | 0.7   | Close-range pressure |
| Adaptive  | Dynamic   | Dynamic | Dynamic| Learns and adjusts |

## Fighting Style Profiles
| Style     | Aggression | Defense | Counter | Preferred Range | Favorite Actions |
|-----------|-----------|---------|---------|----------------|-----------------|
| Karate    | 0.7       | 0.5     | 0.3     | Medium         | Punches, kicks |
| MuayThai  | 0.8       | 0.4     | 0.2     | Close          | Elbows, knees |
| Boxing    | 0.6       | 0.6     | 0.4     | Close          | Jabs, hooks |
| Taekwondo | 0.5       | 0.5     | 0.6     | Medium         | High kicks |
| Judo      | 0.3       | 0.7     | 0.5     | Grappling      | Throws, grapples |
| Wushu     | 0.6       | 0.5     | 0.5     | Far            | Acrobatic attacks|

## Integration Points
- **Combat System (Module 4)**: AI actions feed into CombatComponent for damage/hit detection
- **Martial Arts (Module 7)**: StyleBehavior maps EFightingStyle to AI behavior profiles
- **Animation (Module 5)**: AnimationHandler drives character animations per action
- **Character Creation (Module 8)**: AI fighters use generated characters via character presets
- **AI Photo-to-Character (Module 9)**: Generated characters can be assigned AI controllers
- **Network (Module 6)**: AI controllers work in multiplayer as locally-controlled AI opponents

## File Count: 54 files (27 .h, 26 .cpp, 1 .md)
