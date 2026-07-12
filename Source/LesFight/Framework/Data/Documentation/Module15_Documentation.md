# Module 15: Save, Progression & Data Management System

## Architecture

The Data Management System is organized into 8 subdirectories under `Framework/Data/`, with `ULesFightDataManager` acting as the master orchestrator coordinating 12 subsystem managers. A modular save system provides platform-level I/O abstraction via `ULesFightSaveManager`, with data integrity ensured through `ULesFightDataSecurity` (FNV-1a checksums) and automatic backup recovery via `ULesFightBackupManager`.

## Directory Structure

```
Framework/Data/
├── Core/               DataManager, SaveManager, BackupManager, DataSecurity, DataTypes
├── Profile/            ProfileManager (8 profiles max)
├── Character/          CharacterDataManager (100 characters max)
├── Progression/        ProgressionManager, UnlockManager, AchievementManager
├── Statistics/         StatisticsManager, MatchHistoryManager (200 entries)
├── Settings/           SettingsManager
├── DevTools/           DataDevTools
└── Documentation/      This file
```

## Data Flow

```
DataManager (orchestrator)
  └─> SaveManager (I/O layer)
        └─> Disk (FPaths::ProjectSavedDir/SaveData/)
              └─> BackupManager (auto 5min, max 10 backups)
```

- `DataManager` coordinates all subsystems and exposes unified save/load/reset interfaces
- `SaveManager` handles file I/O with versioned slots (3 save slots)
- `BackupManager` performs automatic backups every 5 minutes (configurable), keeping a maximum of 10 backups to prevent bloat
- `DataSecurity` validates all reads/writes with FNV-1a checksums, sanitizes player names, and validates profile/character data before saving

## Save File Structure

```
{SavedDir}/SaveData/Slot{0-2}/
├── Profile_{ID}.sav
├── Character_{ID}.sav
├── Settings.sav
├── Statistics.sav
├── Progression.sav
└── MatchHistory.sav
Backups/ -> copies with timestamp prefix
```

## Key Managers (12)

### 1. DataManager
Master orchestrator that coordinates all subsystem managers. Provides unified `SaveAll()`, `LoadAll()`, and `ResetAll()` interfaces. Routes subsystem requests to the appropriate manager.

### 2. SaveManager
File I/O layer handling serialization and deserialization. Supports 3 save slots with versioning. Each slot stores a complete game state snapshot across all categories.

### 3. BackupManager
Automatic backup system running on a configurable interval (default 5 minutes). Detects corruption during backup creation, supports manual and automatic recovery, maintains a maximum of 10 backup copies to prevent storage bloat.

### 4. DataSecurity
Implements FNV-1a checksum generation and verification for all save files. Provides data validation, player name sanitization (profanity filtering, length limits), and an encryption framework ready for future use (not enabled by default).

### 5. ProfileManager
Manages up to 8 player profiles with CRUD operations. Each profile stores player name, avatar path, play statistics, progression data, and associated character IDs.

### 6. CharacterDataManager
Manages up to 100 characters per profile. Supports filtering by fighting style and character type, character duplication, and deletion.

### 7. SettingsManager
Tracks graphics, audio, and control settings with dirty flag detection. Supports `ApplySettings()` and `RevertSettings()` for committing or discarding changes.

### 8. ProgressionManager
Handles player leveling with XP awarded from fights, wins, achievements, and streaks. XP per level = Level * 1000. Features 8 level-up reward tiers granting character slots, style unlocks, titles, currency, and avatars.

### 9. UnlockManager
Manages 30+ unlockables across 10 unlock types (Fighter, FightingStyle, Clothing, Accessory, Arena, Music, SpecialTechnique, CharacterCreatorOption, ColorPalette, Emote). Content is gated by player level and achievement completion.

### 10. AchievementManager
Tracks 21 achievements with per-achievement progress (0.0-1.0). Supports hidden achievements, progress incrementing, and overall completion percentage calculation.

### 11. StatisticsManager
Records comprehensive match statistics including wins/losses/draws, win/loss streaks, highest combo/damage, total KOs/perfects, favorite fighter and style tracking, and total play time.

### 12. MatchHistoryManager
Stores the last 200 match entries in memory (newest first). Supports filtering by arena and opponent, win/loss ratio calculation, and CSV export of the full history.

## Progression System

- **Player Level**: 1-50+ (no hard cap)
- **XP Formula**: XP Required = Level * 1000 (Level 1 = 1000 XP, Level 2 = 2000 XP, etc.)
- **XP Sources**:
  - Fight completed: +50 XP
  - Match victory: +100 XP
  - Achievement unlocked: +500 XP
  - Win streak bonus: +100 XP
- **Level Rewards**:
  | Level | Reward |
  |-------|--------|
  | 1     | None (starting level) |
  | 2     | +1 Character Slot |
  | 5     | Style Unlock |
  | 10    | Title "Level 10" |
  | 15    | 500 Currency |
  | 20    | +1 Character Slot |
  | 25    | Avatar |
  | 30    | 1000 Currency |
  | 50    | Legendary Title |

## Achievement List (21)

| ID | Title | Description | Hidden |
|----|-------|-------------|--------|
| FirstFight | First Bout | Complete your first fight | No |
| FirstWin | First Victory | Win your first match | No |
| WinStreak5 | 5 Win Streak | Win 5 matches in a row | No |
| WinStreak10 | 10 Win Streak | Win 10 matches in a row | Yes |
| ComboMaster | Combo Master | Land a 20+ hit combo | No |
| UltimateFinisher | Ultimate Finisher | Finish a match with an ultimate move | No |
| CompleteTutorial | Student No More | Complete the tutorial | No |
| CreateCharacter | Creator | Create your first character | No |
| AIGeneration | AI Artist | Generate a character with AI | No |
| ReachLevel10 | Getting Started | Reach player level 10 | No |
| ReachLevel25 | Mid Tier | Reach player level 25 | No |
| ReachLevel50 | Veteran Warrior | Reach player level 50 | Yes |
| PlayOnline | Online Warrior | Play your first online match | No |
| WinOnline | Online Champion | Win an online match | No |
| UnlockAllStyles | Style Master | Unlock all fighting styles | Yes |
| UnlockAllArenas | World Traveler | Unlock all arenas | Yes |
| MaxDamage | One Punch | Deal 500+ damage in a single hit | No |
| PerfectRound | Perfect Round | Win a round without taking damage | No |
| ComebackVictory | Comeback Victory | Win from 10% health or less | Yes |
| VeteranPlayer | Veteran | Play 100 matches total | Yes |

## Unlockable Items (30+)

- **Fighters** (12): Karate, Kung Fu, Boxing, Muay Thai, Jiu Jitsu, Capoeira, Taekwondo, Wrestling, Fencing, Krav Maga, Shadow, Champion
- **Clothing** (3): Street Wear, Classic Gi, Armored Gear
- **Arenas** (5): Ancient Dojo, Boxing Ring, Urban Street, Colosseum, Volcano Arena
- **Music** (5): Main Theme, Battle Hymn, Night City, Epic Finale, Champion Anthem
- **Special Techniques** (3): Dragon Punch, Spinning Kick, Shadow Step
- **Character Creator Options** (4): Spiky Hair, Long Hair, Body Tattoos, Facial Scars
- **Color Palettes** (6): Crimson, Ocean, Forest, Royal Gold, Shadow, Midnight

## Security Features

- FNV-1a checksums computed and verified on all save files during read/write operations
- Corruption detection on load triggers automatic backup recovery attempt
- Player name sanitization (profanity filtering, length constraints)
- Profile and character data validation performed before any save operation
- Encryption framework prepared for future activation (not enabled by default)

## Performance Considerations

- Maximum of 8 player profiles to constrain memory and disk usage
- Maximum of 100 characters per profile
- Match history capped at 200 entries (oldest entries trimmed automatically)
- Auto-backup interval configurable (default 5 minutes)
- Maximum 10 backup copies to prevent storage bloat
- DevTools log capped at 500 entries
- 3 save slots for redundancy and data safety

## File Count: 28 files

14 header (.h) + 13 implementation (.cpp) pairs + 1 documentation (.md):
- `Core/` : DataManager.h/.cpp, SaveManager.h/.cpp, BackupManager.h/.cpp, DataSecurity.h/.cpp, DataTypes.h
- `Profile/` : ProfileManager.h/.cpp
- `Character/` : CharacterDataManager.h/.cpp
- `Progression/` : ProgressionManager.h/.cpp, UnlockManager.h/.cpp, AchievementManager.h/.cpp
- `Statistics/` : StatisticsManager.h/.cpp, MatchHistoryManager.h/.cpp
- `Settings/` : SettingsManager.h/.cpp
- `DevTools/` : DataDevTools.h/.cpp
- `Documentation/` : Module15_Documentation.md
