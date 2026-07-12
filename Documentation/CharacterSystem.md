# LES FIGHT - Module 3: Character System

## Overview

This module establishes the complete character architecture for all playable fighters. Every fighter inherits from `ALesFightBaseFighter` which is composed of 8 modular components following composition-over-inheritance principles.

## New Files

```
Source/LesFight/Framework/Character/
  LesFightBaseFighter.h/.cpp              - Base class for all fighters
  LesFightPlayerFighter.h/.cpp            - Player-controlled fighter
  LesFightCharacterDataManager.h/.cpp     - Fighter data registry
  LesFightCharacterStatisticsManager.h/.cpp - Per-fighter stats tracking
  LesFightCharacterLifecycleManager.h/.cpp - Fighter lifecycle management
  Components/
    LesFightHealthComponent.h/.cpp        - Health, damage, death, revive
    LesFightStaminaComponent.h/.cpp       - Stamina consumption/recovery
    LesFightAnimationComponent.h/.cpp     - Animation montage/state control
    LesFightAudioComponent.h/.cpp         - Footstep/voice/breathing audio
    LesFightStatisticsComponent.h/.cpp    - Configurable attribute system
    LesFightAppearanceComponent.h/.cpp    - Mesh/skin/hair/clothing management
    LesFightInteractionComponent.h/.cpp   - World interaction detection
  Data/
    LesFightCharacterData.h               - All data structures & table rows
    LesFightFighterDataAsset.h/.cpp       - Primary data asset for fighters
    LesFightCharacterProgression.h/.cpp   - XP/level/skill tree framework
  Animation/
    LesFightAnimInstance.h/.cpp           - Animation blueprint base
  Selection/
    LesFightCharacterSelectionManager.h/.cpp - Roster/selection backend
```

## Class Hierarchy

```
ALesFightBaseCharacter (Module 1)
  -> ALesFightPlayerCharacter (Module 2)
    -> ALesFightBaseFighter (Module 3)
      -> ALesFightPlayerFighter (Module 3)
```

## Character Attributes (FCharacterTableRow)

| Category | Struct | Key Fields |
|---|---|---|
| Identity | FCharacterIdentity | CharacterID, Name, Nickname, Age, Gender, Biography, Nationality, FightingStyle |
| Physical | FCharacterPhysicalAttributes | Height, Weight, BodyType, MuscleDefinition, Reach, FightingStance |
| Movement | FCharacterMovementAttributes | WalkSpeed, RunSpeed, SprintSpeed, JumpHeight, Acceleration, Deceleration |
| Combat | FCharacterCombatAttributes | Strength, Defense, Agility, Balance, AttackSpeed, ComboAbility |
| Resources | FCharacterResourceAttributes | MaxHealth, MaxStamina, StaminaRecoveryRate, MaxEnergy, RecoverySpeed |
| Animation | FCharacterAnimationReferences | AnimBlueprint, Idle/Walk/Run/Sprint/Jump/Landing/Crouch anims, LocomotionBlendSpace |
| Audio | FCharacterAudioReferences | Footstep/Breathing/HitReaction/Grunt/Taunt sounds, Victory/Defeat voice |
| Cosmetics | FCharacterCosmeticReferences | BaseMesh, SkinMaterials, HairMaterials, ClothingSlots, AccessorySlots, Portraits |
| Progression | FCharacterProgressionData | StartingLevel, ExperienceMultiplier, LevelThresholds, UnlockableAbilities, SkillTreeNodes |

## Components System

### ULesFightHealthComponent
- **Purpose**: Complete health management
- **Functions**: TakeDamage, Heal, Kill, Revive, SetInvulnerable, ResetHealth
- **States**: Alive, Dead, Invulnerable
- **Events**: OnHealthChanged, OnDeath, OnRevived, OnDamageTaken, OnHealingReceived
- **Integration**: `ALesFightBaseFighter` auto-binds OnDeath -> OnFighterDeath

### ULesFightStaminaComponent
- **Purpose**: Stamina resource management
- **Functions**: ConsumeStamina, RecoverStamina, ResetStamina
- **States**: Ready, Recovering, Exhausted, Regenerating
- **Features**: Recovery delay, configurable rate, exhaustion detection
- **Events**: OnStaminaChanged, OnExhausted, OnStaminaRecovered

### ULesFightAnimationComponent
- **Purpose**: Animation state and montage control
- **Functions**: PlayMontage, SetAnimationState, SetBlendSpaceParameter, SetLocomotionValues
- **Placeholders**: TriggerPunchPlaceholder, TriggerKickPlaceholder, TriggerBlockPlaceholder, TriggerHitReactionPlaceholder
- **Events**: OnAnimationStateChanged, OnMontageCompleted

### ULesFightAudioComponent
- **Purpose**: Character-specific audio management
- **Functions**: PlayFootstep, PlayBreath, PlayVictoryVoice, PlayDefeatVoice, PlayGrunt, PlayTaunt
- **Features**: Random sound selection, pitch/volume control, voice type enum
- **Integration**: Called from animation notifies for footsteps

### ULesFightStatisticsComponent
- **Purpose**: Configurable attribute system with multipliers
- **Functions**: SetStat, GetStat, ModifyStat, ApplyStatMultiplier, ResetStats
- **Data**: CombatAttributes, MovementAttributes, ResourceAttributes
- **Features**: Stat caching, multiplier stack, runtime modification

### ULesFightAppearanceComponent
- **Purpose**: Visual customization management
- **Functions**: ApplyBaseMesh, ApplySkinMaterial, ApplyHairMaterial, SetClothingSlot, SetAccessorySlot
- **Features**: Dynamic material parameter control, texture parameter setting
- **Events**: OnAppearanceChanged

### ULesFightInteractionComponent
- **Purpose**: World interaction detection
- **Functions**: PerformInteraction, SetDetectionRadius, ScanForInteractables
- **Features**: Closest interactable tracking, detection lost/found events
- **Events**: OnInteractableFound, OnInteractableLost, OnInteractionPerformed

## State Machine Integration

The base fighter uses two state systems:
1. **ECharacterState** (from Module 1 BaseCharacter) - 11 states for animation
2. **ECharacterGameplayState** (from Module 2 StateMachine) - 17 states for gameplay
3. **EFighterLifecycleState** (from Module 3 LifecycleManager) - 7 states for lifecycle

State transitions:
- `ALesFightBaseFighter::OnFighterDeath()` -> Sets Dead state in both systems
- `ALesFightBaseFighter::OnFighterRevive()` -> Resets to Idle
- `OnHealthComponentDeath` -> Auto-calls OnFighterDeath

## Animation System

### ULesFightAnimInstance
- **Locomotion States**: Idle, Walking, Running, Sprinting, Jumping, Falling, Landing, Crouching
- **Parameters**: LocomotionSpeed, LocomotionDirection, bIsInAir, bIsCrouching, bIsSprinting
- **Blend Space Support**: Configurable parameters via SetBlendSpaceParameter
- **Combat Placeholders**: TriggerPunch, TriggerKick, TriggerBlock, TriggerHitReaction, TriggerVictory, TriggerDefeat

## Progression Framework (ULesFightCharacterProgression)
- **Purpose**: XP/Level/Skill tree backend (inactive until later module)
- **Level Curve**: 10 predefined thresholds, then scaling formula
- **Functions**: AddExperience, SetLevel, UnlockAbility, IsAbilityUnlocked
- **Events**: OnLevelUp, OnExperienceGained, OnAbilityUnlocked

## Character Selection Manager
- **Purpose**: Roster management and selection backend
- **Features**: Character list population, per-player selection, lock/unlock, ready confirmation
- **Conflict Prevention**: Prevents duplicate character selection
- **Functions**: SelectCharacter, DeselectCharacter, ConfirmSelection, GetUnlockedCharacters

## Managers

| Manager | Purpose |
|---|---|
| ULesFightCharacterDataManager | Registers/looks up fighter data assets and table rows |
| ULesFightCharacterStatisticsManager | Tracks matches, wins/losses, KOs, win streaks, damage stats |
| ULesFightCharacterLifecycleManager | Tracks fighter lifecycle states, ready/active/defeated/respawning |

## Integration with GameInstance

All new managers are created and initialized in `ULesFightGameInstance::Init()`:
- `CharacterDataManager` - Fighter data registry
- `CharacterStatsManager` - Match statistics tracking
- `CharacterLifecycleManager` - Fighter lifecycle orchestration
- `CharacterSelectionManager` - Roster and selection backend

## Future Integration Points

### Module 4 (Combat System)
- Combat attributes (Strength, Defense, Agility) read from FCharacterCombatAttributes
- AnimationComponent placeholders replaced with real combat montages
- HealthComponent::TakeDamage used for actual combat damage
- StaminaComponent::ConsumeStamina for attack costs

### Module 7 (AI)
- AI reads fighter stats from StatisticsComponent
- AI uses LifecycleManager to track fighter states
- AI selection uses CharacterSelectionManager

### Module 8 (Photo-to-Character)
- AppearanceComponent applies custom textures/materials
- CharacterDataManager registers custom characters
- Identity/Physical attributes generated from photo analysis

### Module 9 (Character Customization)
- AppearanceComponent slot system for clothing/accessories
- Skin/Hair material variants
- Progression system for unlockable cosmetics

## Best Practices

1. **Always use HealthComponent** instead of direct health manipulation
2. **Bind to component events** rather than polling state
3. **Use FighterDataAsset** for defining new characters
4. **Keep components focused** - single responsibility per component
5. **Use lifecycle manager** for tracking fighter state across systems
6. **Animation placeholders** should be replaced when implementing combat
