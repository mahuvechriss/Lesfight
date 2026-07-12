# Module 14: Advanced UI, Menus & Player Experience System

## Architecture

The UI system is built around a centralized orchestration pattern where `ULesFightUIWorldManager` owns and manages 12 subsystem manager objects, each responsible for a distinct domain of the player experience. All widget classes derive from `UUserWidget` and are Blueprintable, enabling full designer iteration in the Unreal Editor.

### Component Diagram

```
ULesFightUIWorldManager (Orchestrator)
├── UIManager                      Screen stack, menu state routing, input device detection
├── WidgetManager                  Widget creation, caching, pooling (5 per type)
├── ScreenNavigationManager        Navigation history stack, screen transitions
├── MenuStateManager               Finite state machine with validated transition map
├── InputNavigationManager         Keyboard/mouse/gamepad input binding and routing
├── NotificationManager            Toast notification queue (max 10), auto-dismiss timer
├── PopupManager                   Modal popup queue, layered blocking
├── UIAnimationManager             Named animation definitions, timer-driven playback
├── PlayerProfileManager           Player profile CRUD, save/load to disk
├── AccessibilityManager           High contrast, large text, color blind, subtitles, etc.
├── UIDevTools                     Preview mode, navigation testing, performance monitoring
└── UIAnimationSystem              Runtime animation playback on individual widgets
```

## Directory Structure

```
Framework/UI/
├── Data/                         Enums, structs, data asset definitions
│   └── LesFightUIData.h          Shared structs (FUIAccessibilitySettings, FUIAnimationDef,
│                                  FActiveAnimation, FWidgetTestResult, FLocalizationIssue,
│                                  FPerformanceSample) and multicast delegate declarations
├── Manager/                      Core orchestration
│   ├── LesFightUIWorldManager.h  Orchestrator class with 12 subsystem pointers + config TSubclassOf
│   └── LesFightUIWorldManager.cpp Creates all 12 subsystems, delegates Tick to animation/notification
├── MainMenu/                     Main menu widget
├── Profile/                      Player profile widget
├── CharacterSelect/              Character selection grid widget
├── CharacterCreator/             Character creator widget with undo/redo support
├── AIGeneration/                 AI photo-to-character UI
├── Multiplayer/                  Lobby, host, join screens
├── HUD/                          Combat HUD + HUD container
├── PauseMenu/                    Pause menu widget
├── MatchResult/                  Post-match results widget
├── Settings/                     Configuration widgets
│   ├── LesFightSettingsWidget          Tabbed settings base (SwitchTab, Apply/Save/Reset)
│   ├── LesFightGraphicsSettingsWidget  Resolution, quality presets, FPS, V-Sync
│   ├── LesFightAudioSettingsWidget     Master/music/effects/voice volumes, mute, presets
│   └── LesFightControlSettingsWidget   Key rebinding, sensitivity, vibration, Y-axis invert
├── Accessibility/                Accessibility features
│   └── LesFightAccessibilityManager    Central manager broadcasting FOnAccessibilityChanged
├── Animation/                    Animation systems
│   ├── LesFightUIAnimationSystem       Per-widget animation playback with registry
│   └── LesFightUIAnimationManager      (Manager subsystem for animation definitions)
├── DevTools/                     Developer tools
│   └── LesFightUIDevTools              Preview mode, navigation testing, performance monitoring
└── Documentation/                This document
```

## Screen Flow

```
MainMenu
  ├── CharacterSelect
  │     ├── CharacterCreator
  │     │     └── (back)
  │     ├── AIGeneration
  │     │     └── (back)
  │     └── MultiplayerLobby
  │           └── Game
  │                 ├── PauseMenu
  │                 │     ├── Settings
  │                 │     ├── Accessibility
  │                 │     └── (resume)
  │                 └── MatchResult
  │                       └── MainMenu
  ├── Settings
  ├── Accessibility
  └── Profile
```

### State Machine Transitions

The `MenuStateManager` maintains a `ValidTransitions` map that enforces legal state transitions at runtime. Each state enum value maps to a set of allowed destination states. Any transition not in the valid set is rejected and logged.

## Manager Subsystems (12)

### UIManager (ULesFightUIManager)
- Manages the screen stack (max 20 entries)
- Routes input to the topmost active screen
- Detects current input device (keyboard/mouse vs gamepad)
- Pushes, pops, and replaces screens with transition support

### WidgetManager (ULesFightWidgetManager)
- Creates widget instances from class references
- Maintains a widget pool (5 instances per widget type)
- Caches frequently used widgets for reuse
- Destroys widgets when pool exceeds capacity

### ScreenNavigationManager (ULesFightScreenNavigationManager)
- Maintains navigation history as a stack
- Supports forward/backward navigation
- Triggers screen transition animations
- Prevents duplicate screen entries

### MenuStateManager (ULesFightMenuStateManager)
- Finite state machine for menu flow
- Validates all state transitions against a whitelist
- Fires enter/exit events per state
- Logs invalid transition attempts

### InputNavigationManager (ULesFightInputNavigationManager)
- Maps input actions to UI navigation commands
- Supports keyboard, mouse, and gamepad bindings
- Handles focus management between widgets
- Provides action name lookup for rebinding UI

### NotificationManager (ULesFightNotificationManager)
- Queue-based toast notification system
- Auto-dismiss with configurable duration
- Maximum 10 notifications in queue
- Priority-based display ordering

### PopupManager (ULesFightPopupManager)
- Modal popup queue with layered blocking
- Supports confirm/cancel/dismiss callbacks
- Blocks input to underlying screens while active
- Max 3 stacked popups

### UIAnimationManager (ULesFightUIAnimationManager)
- Stores named animation definitions (FadeIn, FadeOut, SlideIn, SlideOut, ScaleIn, Pulse, Shake)
- Timer-driven animation tick
- Broadcasts PostAnimationEvent on completion
- Global speed multiplier

### PlayerProfileManager (ULesFightPlayerProfileManager)
- Create, read, update, delete player profiles
- Save/load profiles to persistent storage
- Track match history (max 50 entries)
- Player statistics and rankings

### AccessibilityManager (ULesFightAccessibilityManager)
- High contrast mode toggle
- Large text mode toggle
- Color blind mode toggle
- Subtitle enable/disable
- Reduced motion toggle
- UI scale adjustment (0.5x to 2.0x)
- Text scale adjustment (0.5x to 2.0x)
- Language selection framework
- Saves/loads from persistent storage
- Broadcasts FOnAccessibilityChanged on any change

### UIDevTools (ULesFightUIDevTools)
- UI preview mode to test screens in isolation
- Navigation testing with issue reporting
- Widget validity testing
- Localization key coverage testing
- Performance monitoring with frame time sampling
- Test log capped at 500 entries

### UIAnimationSystem (ULesFightUIAnimationSystem)
- Per-widget animation playback at runtime
- Animation registry maps names to FUIAnimationDef
- Supports looping, speed scaling, and pause
- Tracks active animations per widget
- Clean shutdown clears all active animations

## Accessibility Features

| Feature | Range/Options | Default |
|---------|--------------|---------|
| High Contrast | On/Off | Off |
| Large Text | On/Off | Off |
| Color Blind Mode | On/Off | Off |
| Subtitles | On/Off | On |
| Reduced Motion | On/Off | Off |
| UI Scale | 0.5 - 2.0 (0.1 steps) | 1.0 |
| Text Scale | 0.5 - 2.0 (0.1 steps) | 1.0 |
| Language | 9 supported languages | en |

### Supported Languages

| Code | Language |
|------|----------|
| en | English |
| fr | French |
| de | German |
| es | Spanish |
| ja | Japanese |
| ko | Korean |
| zh | Chinese |
| pt | Portuguese |
| ru | Russian |

## Settings Structure

### Graphics Settings (ULesFightGraphicsSettingsWidget)

| Setting | Type | Default | Range |
|---------|------|---------|-------|
| Resolution | FIntPoint | 1920x1080 | 1280x720, 1920x1080, 2560x1440, 3840x2160 |
| Quality Preset | int32 | 2 (High) | 0-4 |
| Texture Quality | int32 | 3 | 0-3 |
| Shadow Quality | int32 | 3 | 0-3 |
| Effects Quality | int32 | 3 | 0-3 |
| Frame Rate Limit | int32 | 60 | 30, 60, 120, 144, Unlimited |
| V-Sync | bool | false | On/Off |

### Audio Settings (ULesFightAudioSettingsWidget)

| Setting | Type | Default | Preset Behavior |
|---------|------|---------|-----------------|
| Master Volume | float | 1.0 | Preset 0: Custom (no change) |
| Music Volume | float | 0.8 | Preset 1 (Headphones): Flat 1.0 all channels |
| Effects Volume | float | 1.0 | Preset 2 (Speakers): Boosted lows (Music 0.7, Effects 0.9, Voice 0.8) |
| Voice Volume | float | 1.0 | Preset 3 (Cinematic): Surround-emphasis (Music 1.0, Effects 0.8, Voice 0.6) |
| Mute | bool | false | Saves current volumes, sets all to 0; unmute restores |

### Control Settings (ULesFightControlSettingsWidget)

Default Key Bindings:

| Action | Key |
|--------|-----|
| MoveUp | W |
| MoveDown | S |
| MoveLeft | A |
| MoveRight | D |
| Jump | SpaceBar |
| Punch | LeftMouseButton |
| Kick | RightMouseButton |
| Block | Q |
| Special | E |
| Ultimate | R |
| Throw | F |
| Pause | Tab |
| Menu | Escape |

Additional settings: Controller sensitivity (0.0-1.0, default 0.5), Vibration (default on), Y-axis invert (default off), Control scheme index (default 0).

## Performance Considerations

| Resource | Limit |
|----------|-------|
| Widget pool per type | 5 |
| Screen navigation stack | 20 |
| Notification queue | 10 |
| Match history | 50 |
| DevTools test log | 500 entries |
| Status effects display | 10 |
| Popup stack depth | 3 |

### Widget Pooling

Each widget type caches up to 5 instances in the WidgetManager pool. When a widget is requested, the pool is checked first before creating a new instance. When a widget is dismissed, it is returned to the pool rather than destroyed. This reduces allocation overhead during heavy screen transitions.

### Animation Performance

The UIAnimationSystem uses a flat `TMap<UUserWidget*, TArray<FActiveAnimation>>` structure for O(1) widget lookup. Each frame, Tick iterates active animations and removes completed ones. The GlobalSpeed multiplier allows bulk slowdown/speedup without modifying individual animation definitions.

### DevTools Monitoring

Performance monitoring samples frame time, widget count, and memory usage each tick while active. Samples are stored in a `TArray<FPerformanceSample>` for post-session analysis. The monitoring flag is checked each frame to avoid overhead when inactive.

## File Count: 58 files (29 .h, 28 .cpp, 1 .md)
