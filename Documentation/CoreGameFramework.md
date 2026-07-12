# LES FIGHT - Module 2: Core Game Framework

## Overview

This document describes the Core Game Framework built on top of the Module 1 foundation. All systems are designed for mobile-first with desktop support, modular, scalable, and production-ready.

## Project Structure Additions

```
Source/LesFight/
  Core/                          - Module 1 base classes (updated)
  Framework/
    Player/                      - Player framework
      LesFightPlayerCharacter    - Player-controlled character with movement/camera
      LesFightCharacterMovementComponent - Custom movement (walk/run/sprint/jump/crouch)
      LesFightCharacterStateMachine     - Centralized character state machine
      LesFightPlayerSpawnManager        - Player spawning system
      LesFightRespawnComponent          - Respawn with delay and count limits
    Camera/                      - Camera framework
      LesFightFollowCameraComponent     - Third-person follow camera with collision
      LesFightLockOnComponent           - Lock-on target system (combat prep)
    Input/                       - Input framework
      LesFightTouchInputProcessor       - Mobile touch input with virtual joysticks
    UI/                          - UI framework
      LesFightUIManager                 - Screen/window management system
    Audio/                       - Audio framework
      LesFightAudioManager              - Centralized audio with channel volumes
    Level/                       - Level management
      LesFightLevelManager              - Level transitions and async loading
  Events/
    LesFightEventManager         - Centralized event system
  Data/
    LesFightCharacterDataAsset   - Character data asset/table definitions
    LesFightArenaDataAsset        - Arena data asset/table definitions
    LesFightDataManager          - Centralized data management
```

## Player Framework

### LesFightPlayerCharacter
- **Extends**: `ALesFightBaseCharacter` (Module 1)
- **Purpose**: Full-featured player-controlled character
- **Key Features**: Input bindings for movement (forward/right), camera (turn/look up), sprint, crouch, jump
- **Uses**: Custom character movement component, follow camera component, lock-on component, state machine
- **Movement**: Delegates to `ULesFightCharacterMovementComponent` for all movement logic

### LesFightCharacterMovementComponent
- **Extends**: `UCharacterMovementComponent`
- **States**: Idle, Walking, Running, Sprinting, Jumping, Falling, Landing, Crouching
- **Speed Tiers**: WalkSpeed (150), RunSpeed (350), SprintSpeed (600), CrouchSpeed (100)
- **Key Features**: Sprint stamina cost, air speed multiplier, landing detection (hard/soft), rotation rate control
- **Integration**: Movement states broadcast via `OnMovementStateChanged` delegate

### LesFightCharacterStateMachine
- **States**: None, Spawning, Idle, Moving, Sprinting, Jumping, Falling, Landing, Crouching, Attacking, Blocking, HitStun, KnockedDown, GettingUp, Dead, Respawning, Cinematic
- **Key Features**: State transition validation, time-in-state tracking, forced state transitions, configurable transition durations
- **Events**: `OnGameplayStateChanged` broadcasts state transitions

### LesFightPlayerSpawnManager
- Manages spawn points and player spawning
- Spawns `ALesFightPlayerCharacter` at configured spawn points
- Automatically possesses the first player
- Tracks active players and spawn point occupancy

### LesFightRespawnComponent
- Configurable respawn delay and maximum respawn count
- States: None, Waiting, Spawning, Complete
- Respawning resets character health and state

## Camera Framework

### LesFightFollowCameraComponent
- **Modes**: Default (300 distance, 90 FOV), Combat (250 distance, faster lag), Cinematic (400 distance, 70 FOV)
- **Key Features**: Smooth interpolation for distance and FOV, camera collision prevention via line tracing, lock-on camera rotation, cinematic presets
- **Lock-On**: When a target is set, camera rotates to face the target with rotation lag
- **Integration**: `ApplyCombatPreset()` ready for combat module, `ApplyCinematicPreset()` for cinematics

### LesFightLockOnComponent
- Configurable range (1000 units), angle (45 degrees), and break range (1500 units)
- Target filtering by class type
- Target cycling with direction support
- Automatic break when target goes out of range

## Input Framework

### LesFightTouchInputProcessor
- **Virtual Joysticks**: Left joystick for movement, right joystick for camera
- **Screen Split**: Left half = movement, Right half = camera
- **Dead Zone**: Configurable joystick dead zone
- **Screen Awareness**: `ConfigureForScreenSize()` for resolution-independent layout
- **Input Simulation**: Simulates axis and action inputs for compatibility with existing input system
- **Platform Check**: `IsTouchSupported()` for runtime mobile detection

## UI Framework

### LesFightUIManager
- **Screen System**: Manages EGameScreen enum with 12 screen types (Splash, Logo, Loading, MainMenu, Settings, Profile, ArenaSelect, CharacterSelect, Pause, Exit, HUD, TrainingHUD)
- **Widget Management**: Creates/caches/reuses widget instances per screen type
- **History Navigation**: Push/pop screen history for back navigation
- **Notifications**: Overlay notification system with configurable duration
- **Loading Indicator**: Overlay loading spinner
- **Integration**: Blueprint-assignable screen classes via `ScreenClasses` map

## Audio Framework

### LesFightAudioManager
- **Channels**: Master, Music, SFX, Voice, UI, Ambient
- **Features**: Per-channel volume control, mute/unmute, music playback, sound effects at locations
- **Defaults**: Master 1.0, Music 0.8, SFX 1.0, Voice 1.0, UI 0.7, Ambient 0.5
- **Sound Classes**: Mapped to Unreal Engine Sound Classes for proper mixing
- **Persistence**: Save/load audio settings

## Level Management

### LesFightLevelManager
- **Transition System**: Load level with fade in/out, loading screen
- **Methods**: Sync load, async load with streaming levels, unload
- **Convenience**: OpenMainMenu(), OpenTrainingArena(), RestartCurrentLevel()
- **Progress Tracking**: Load progress (0.0-1.0) and loading state
- **Events**: OnLevelLoadStarted, OnLevelLoadComplete, OnLevelUnloadComplete, OnLevelTransitionComplete

## Event System

### LesFightEventManager
- **Event Types**: Generic, Match, UI, Player Action
- **Event Payload**: Structured FEventPayload with type, data object, int, float, string, vector values
- **Listener Management**: Add/remove listeners per event name
- **Logging**: Optional event logging for debugging
- **Pending Events**: Flush system for queued events

## Data Management

### LesFightCharacterDataAsset / LesFightArenaDataAsset
- **Data Tables**: Both structures support FTableRowBase for CSV/JSON data import
- **Character Data**: CharacterID, name, display name, skeletal mesh, anim blueprint, stats, default moves, fighting style, unlock conditions
- **Arena Data**: ArenaID, name, map reference, thumbnail, spawn locations, boundary dimensions, ambient music, environment type, camera overrides, unlock conditions
- **Asset Manager**: PrimaryDataAsset integration for UE5 Asset Manager

### LesFightDataManager
- Loads character and arena data from data tables
- Provides lookup methods by ID
- Tracks loaded assets
- Events for async asset loading

## Mobile Platform Support

- Vulkan (Android) and Metal (iOS) rendering
- Arm64 and x86_64 builds for Android
- Mobile-optimized rendering (skin cache, low-quality lightmaps)
- Touch input via virtual joysticks
- Scaled UI via UIManager
- Performance-optimized (tick intervals, efficient data structures)

## Integration Points

### Module 3 (Character System)
- Extend `ALesFightPlayerCharacter` with character-specific abilities
- Use `FCharacterDataTableRow` for character stats
- State machine `Attacking/Blocking/HitStun` states ready for combat

### Module 4 (Combat System)
- `ULesFightLockOnComponent` for targeting
- Combat camera preset via `ULesFightFollowCameraComponent::ApplyCombatPreset()`
- Input placeholders for light/heavy/special attacks
- State machine states for combat flow

### Module 5 (Animation)
- Movement states drive animation blueprints
- `EMovementState` for blend spaces
- `ECharacterGameplayState` for state machine

### Module 6 (Multiplayer)
- Replication-ready properties
- Spawn manager with player index support
- Online subsystem integration in GameInstance

## Best Practices

1. **Extend, don't modify**: Create child classes rather than editing base classes
2. **Use the Event System**: For loose coupling between systems
3. **Data-Driven**: Use data assets/tables for configurable values
4. **Mobile Testing**: Test touch controls on device early
5. **State Machines**: Use CharacterStateMachine for all character state logic
6. **Camera Modes**: Switch camera presets via FollowCameraComponent
7. **Audio Channels**: Use appropriate channels for different sound types
8. **Screen Navigation**: Use UIManager screen history for consistent back navigation
