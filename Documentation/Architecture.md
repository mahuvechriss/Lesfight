# LesFight Game - Architecture Documentation

## Overview

This document describes the complete foundation architecture of the next-generation realistic 3D LesFight game built with Unreal Engine 5. The project follows AAA development standards, SOLID principles, and is designed for modular extensibility.

## Project Structure

```
LesFight/
  Config/           - Engine configuration files (.ini)
  Content/          - All game assets organized by category
    Characters/     - Character meshes, materials, textures
    Combat/         - Combat-related assets
    Animation/      - Animation blueprints and sequences
    AI/             - AI behavior trees and controllers
    Multiplayer/    - Multiplayer assets
    UI/             - Widget blueprints and UI assets
    Audio/          - Sound waves, meta sounds, sound cues
    VFX/            - Niagara particle systems and effects
    Maps/           - Level files
    Materials/      - Master and instance materials
    Meshes/         - Static meshes and skeletal meshes
    Textures/       - Texture assets
    Blueprints/     - Blueprint assets
    Data/           - Data tables and curve tables
    Save/           - Save game assets
    Utilities/      - Utility blueprints
  Source/           - All C++ source code
    LesFight/   - Game module
      Core/         - Core framework classes
      Data/         - Data structures and gameplay tags
  Plugins/          - External plugin directory
  Documentation/    - Project documentation
```

## Core Framework Classes

### Game Instance (`LesFightInstance`)
- **Purpose**: Global game manager that persists across levels
- **Responsibilities**: Game initialization, save/load management, online session creation
- **Key Features**: Async save/load, online subsystem integration, settings management
- **Integration Points**: Combat system will register match results here; AI system will access global data

### Game Mode (`LesFightMode`)
- **Purpose**: Manages match flow and game rules
- **Responsibilities**: Player connection tracking, round management, match state machine
- **States**: WaitingForPlayers -> CharacterSelect -> MatchIntro -> RoundActive -> KOResult -> MatchResult
- **Integration Points**: Combat system will trigger state transitions; multiplayer system will override for network play

### Player Controller (`LesFightPlayerController`)
- **Purpose**: Input handling and player-specific view management
- **Responsibilities**: Enhanced Input bindings, HUD management, camera control, menu system
- **Key Features**: Per-player input component, HUD creation, pause/menu toggle
- **Integration Points**: UI system will hook into menu events; combat system will add attack input bindings

### Player State (`LesFightPlayerState`)
- **Purpose**: Per-player data that persists across rounds
- **Responsibilities**: Health tracking, round wins, damage statistics, character selection
- **Replicated**: Full network replication for multiplayer
- **Integration Points**: Character customization will store skin data here

### Game State (`LesFightState`)
- **Purpose**: Global match state replicated to all clients
- **Responsibilities**: Round tracking, match timer, round time remaining
- **Integration Points**: UI system reads state for HUD display

### Base Character (`LesFightBaseCharacter`)
- **Purpose**: Foundation for all player characters
- **Responsibilities**: Character state machine, damage handling, health management, invulnerability
- **States**: Idle, Walking, Running, Jumping, Falling, Attacking, Blocking, HitStun, KnockedDown, GettingUp, Dead
- **Key Features**: Spring arm camera setup, replicated health, event-driven state changes
- **Integration Points**: Combat system will extend with attack montages; animation system will drive state-based blending

### Camera Manager (`LesFightCameraManager`)
- **Purpose**: Modular camera system with multiple modes
- **Modes**: Default, Combat, Cinematic, CharacterSelect, Spectator
- **Key Features**: Smooth interpolation, zoom, collision prevention, dynamic FOV, cinematic transitions
- **Integration Points**: Combat system will activate combat camera mode during fights

### HUD (`LesFightHUD`)
- **Purpose**: Base HUD widget with blueprint-implementable events
- **Events**: Health/rounds/timer updates, combo display, super meter, damage indicators, announcements
- **Integration Points**: All UI widgets will inherit from this base class

### Input Manager (`LesFightInputManager`)
- **Purpose**: Centralized input management system
- **Key Features**: Multiple mapping context support, priority system, device detection, input rebinding
- **Integration Points**: Combat system will register combat-specific input contexts

### Settings Manager (`LesFightSettingsManager`)
- **Purpose**: Centralized settings management
- **Categories**: Graphics (resolution, quality), Audio (volumes), Gameplay (sensitivity, camera options)
- **Key Features**: Apply/reset/save/load settings, defaults management
- **Integration Points**: All systems will read settings from this manager

### Save System (`LesFightSaveGame`)
- **Purpose**: Persistent game data storage
- **Data**: Player profiles, character data, match statistics, serialized settings
- **Integration Points**: Progression system stores unlockables; character customization stores preferences

### Logging System (`LesFightLogManager`)
- **Purpose**: Centralized logging with level filtering and file output
- **Levels**: Debug, Verbose, Info, Warning, Error, Fatal
- **Key Features**: Static utility methods, file logging with buffer flushing
- **Integration Points**: All modules use this for consistent logging

### Debug Overlay (`LesFightDebugOverlay`)
- **Purpose**: Runtime debugging display
- **Displays**: FPS, frame time, triangle count, draw calls, network status, game state
- **Key Features**: Toggle visibility, console command execution
- **Integration Points**: Toggle-able during development for all modules

### Gameplay Tags (`LesFightplayTags`)
- **Purpose**: Centralized gameplay tag definitions
- **Categories**: State, Combat, Input, Damage, Modifier, Effect
- **Key Features**: Static singleton access, helper functions for tag operations
- **Integration Points**: All modules reference tags for state/action identification

## Input System

The Enhanced Input system is configured with support for:
- Keyboard & Mouse
- Xbox Controller
- PlayStation Controller

Input mapping contexts are organized by priority:
1. UI (highest)
2. Menu
3. Gameplay
4. Combat
5. Debug

Prepared action mappings:
- Movement (2D axis)
- Look (2D axis)
- Light/Medium/Heavy Attack
- Special Move
- Block
- Jump/Dash
- Menu/Pause
- Interaction

## Camera System

Modular camera with the following features:
- Third-person perspective with configurable distance
- Character tracking with smooth interpolation
- Camera lag for cinematic feel
- Dynamic zoom with smooth transitions
- Camera collision prevention via line tracing
- Dynamic FOV adjustment
- Cinematic transition support
- Mode-based settings (Default, Combat, Cinematic)

## Save Architecture

Two-tier save system:
1. **Async Save/Load**: Non-blocking file I/O for game state
2. **Settings Persistence**: Configuration file-based settings storage

Data categories:
- Player Profiles (name, level, stats)
- Character Data (per-character stats, unlocks)
- Match Statistics (aggregate career stats)
- Serialized Settings (graphics, audio, gameplay)

## Future Module Integration

Each future module can integrate cleanly through:

1. **Character System**: Extend `ALesFightBaseCharacter` with character-specific abilities, stats, and animations
2. **Combat System**: Add combat actions via Enhanced Input, manage hit detection, combo system, damage calculations
3. **Animation System**: Drive animation blueprints from character state, implement blend spaces for movement
4. **LAN Multiplayer**: Extend game instance session management, implement player replication
5. **Martial Arts Combat**: Specialize combat actions for martial arts styles
6. **Character Customization**: Store cosmetic data in save system, apply to character mesh
7. **AI Photo-to-Character**: Import texture data, apply to character materials
8. **LesFight AI**: Use AI module classes, implement behavior trees for opponent logic
9. **Arena System**: Create level-specific game modes, environment interactions
10. **Audio System**: Use MetaSounds, trigger from combat events
11. **VFX & Cinematics**: Niagara particle systems, level sequence integration
12. **UI/UX**: Extend HUD class with screens, menus, and widgets
13. **Save & Progression**: Utilize save game structure for unlockables

## Coding Standards

- **Naming**: Classes prefixed with `LesFight`, methods use PascalCase, variables camelCase
- **SOLID**: Single responsibility per class, open for extension, closed for modification
- **Modularity**: Each system is independent and communicates via events/delegates
- **Replication**: All gameplay-relevant data is marked for network replication
- **Documentation**: All public methods have documentation comments
- **Performance**: Tick intervals configured, efficient data structures, async operations

## Performance Considerations

- Tick intervals set to minimize CPU usage (0.1s for controllers, 1.0s for game mode)
- Async save/load operations to prevent frame hitches
- Efficient replication using conditional properties
- Modular architecture allows per-system optimization
- Scalability settings exposed via config files
