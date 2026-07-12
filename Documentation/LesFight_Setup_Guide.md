# LesFight - Setup Guide for First Playable Build

## Step 1: Open in Unreal Engine 5.4

1. Launch **Unreal Engine 5.4** from the Epic Games Launcher
2. In the Project Browser, click **Browse** and select `H:/LesFight/LesFight.uproject`
3. When prompted, click **Yes** to rebuild the LesFight module
4. UE5 will compile all 464 C++ files — this may take 5-15 minutes
5. If compilation errors appear, note them and we can fix them

## Step 2: Configure Project Settings (Editor)

Once the project loads in the editor:

1. Go to **Edit → Project Settings**
2. Under **Maps & Modes**:
   - Set **Default GameMode** → `ALesFightGameMode`
   - Set **Editor Startup Map** → Create new or select existing
   - Set **Game Default Map** → Create new or select existing
3. Under **Game Instance** → Set to `ULesFightGameInstance`

## Step 3: Create Required Blueprints

Create these Blueprint subclasses in the Content Browser:

### Characters
- `/Game/Characters/BP_PlayerFighter` → Parent: `ALesFightPlayerFighter`
- `/Game/Characters/BP_AIFighter` → Parent: `ALesFightAIFighter`
- `/Game/Characters/BP_BaseFighter` → Parent: `ALesFightBaseFighter`

### UI
- `/Game/UI/WBP_MainMenu` → Parent: `UUserWidget`
- `/Game/UI/WBP_HUD` → Parent: `ULesFightHUD`
- `/Game/UI/WBP_CharacterSelect` → Parent: `UUserWidget`
- `/Game/UI/WBP_PauseMenu` → Parent: `UUserWidget`
- `/Game/UI/WBP_MatchResult` → Parent: `UUserWidget`

### Input
Create Input Mapping Context:
- `/Game/Input/IMC_Default` → Create Enhanced Input Mapping Context asset
- Add Input Actions: Move, Look, LightAttack, HeavyAttack, Kick, Block, Dodge, Special, Ultimate, Throw, Pause, Menu

### Game Modes
- `/Game/GameModes/BP_LesFightGameMode` → Parent: `ALesFightGameMode`
  - Set Default Pawn Class → `BP_PlayerFighter`
  - Set HUD Class → `WBP_HUD`
  - Set Player Controller Class → `ALesFightPlayerController`

## Step 4: Create a Basic Arena Level

1. Create new level: `/Game/Maps/LesFightArena`
2. Add a floor plane (5000x5000 units)
3. Add lighting (Directional Light + Sky Light)
4. Add a PlayerStart actor
5. Set basic post-processing volume
6. Add arena walls/fence (visual boundaries)

## Step 5: Create Basic Character Mesh

Since there are no character assets yet:
1. Use UE5's **Mannequin** as placeholder
2. Or create a simple box/cylinder character capsule
3. Set up the skeleton with basic socket points
4. Create a simple idle animation

## Step 6: Test the Build

1. Click **Play** in the editor
2. The game should initialize with:
   - Game Instance creating all managers
   - Game Mode starting in `WaitingForPlayers` state
   - Player Controller spawning with HUD
   - Base Character spawning and responding to input
3. If it compiles and runs, we can build on it from there!

## File Architecture Reference

| Directory | Purpose |
|-----------|---------|
| `Source/LesFight/Core/` | Core framework (GameMode, GameInstance, PlayerController, Character) |
| `Source/LesFight/Data/` | Gameplay tags and data assets |
| `Source/LesFight/Events/` | Event manager for system communication |
| `Source/LesFight/Framework/` | 19 module systems (18 completed + Release) |
| `Config/` | INI configuration files |
| `Content/` | **Empty** — needs game assets |

## Module Quick Reference

| Module | System | Key Classes |
|--------|--------|-------------|
| 1 | Core Framework | GameMode, GameInstance, PlayerController, HUD |
| 2 | Player | CharacterMovement, StateMachine, PlayerCharacter |
| 3 | Camera | FollowCamera, LockOnComponent |
| 4 | Input | TouchInput, EnhancedInput management |
| 5 | UI | UIManager, WidgetManager, all screen widgets |
| 6 | Character | Fighter, DataManager, Animation, Selection |
| 7 | Combat | ComboManager, DamageManager, HitDetection, Block, Throw |
| 8 | Animation | AnimationManager, StateMachine, IK, Blending |
| 9 | AI Photo→Char | Photo processing, 3D reconstruction, mesh adapter |
| 10 | Fighting AI | DecisionManager, Perception, CombatAI, Learning |
| 11 | Arena | Environment, Weather, Lighting, Destructibles |
| 12 | Audio | Music, SFX, Voice, Spatial, Ambient |
| 13 | VFX | Niagara, Impact, PostProcessing, Cinematic |
| 14 | UI-Integrated | Settings, HUD, Accessibility, DevTools |
| 15 | Data | Save, Profile, Progression, Statistics |
| 16 | Integration | Dependency, Loading, Event Coordination, GameFlow |
| 17 | Performance | FPS, Memory, Quality, Optimization |
| 18 | QA | BugTracker, TestCases, Automation, Regression |
| 19 | Release | Build, Version, Packaging, Installer |
