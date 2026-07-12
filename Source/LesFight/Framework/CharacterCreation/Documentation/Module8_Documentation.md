# Module 8: Advanced Character Creation & Customization System

## Overview
The Advanced Character Creation & Customization System provides a comprehensive, modular
framework for creating, editing, and customizing fighting game characters. It supports
deep facial morphing, body sculpting, clothing layers, skin detailing, material editing,
voice selection, biography management, save/load, multiplayer replication, and performance
optimization — all orchestrated through a unified manager.

## Architecture

### Directory Structure
```
Framework/CharacterCreation/
├── Data/
│   └── LesFightCharacterCreationData.h/.cpp     Core data types
├── Core/
│   ├── LesFightCharacterCreator.h/.cpp          Create/edit/delete characters
│   ├── LesFightCharacterPreset.h/.cpp           Import/export presets
│   ├── LesFightCharacterRandomizer.h/.cpp       Random generation
│   └── LesFightCharacterPreview.h/.cpp          3D preview with camera controls
├── Face/
│   └── LesFightFaceCustomization.h/.cpp         Face morph targets
├── Hair/
│   └── LesFightHairSystem.h/.cpp               Hair styles, color, physics
├── Body/
│   └── LesFightBodyCustomization.h/.cpp         Body morphs and build types
├── Skin/
│   └── LesFightSkinSystem.h/.cpp               Skin tones, textures, tattoos
├── Clothing/
│   └── LesFightClothingSystem.h/.cpp           Slot-based equipment system
├── Materials/
│   └── LesFightMaterialCustomization.h/.cpp     Per-slot material editing
├── Accessories/
│   └── LesFightAccessorySystem.h/.cpp          Jewelry, headwear, capes
├── Voice/
│   └── LesFightVoiceSelection.h/.cpp           Voice pack & pitch selection
├── Biography/
│   └── LesFightCharacterBiography.h/.cpp        Name, age, backstory
├── Save/
│   └── LesFightCharacterSaveSystem.h/.cpp       Save/load characters
├── UI/
│   └── LesFightCustomizationUI.h/.cpp          Navigation & screen management
├── Multiplayer/
│   └── LesFightCharacterReplication.h/.cpp     Network sync
├── Performance/
│   └── LesFightCharCreationPerformance.h/.cpp   LOD, resolution, profiling
├── Testing/
│   └── LesFightCharCreationDevTools.h/.cpp      Debug overlays, stress tests
└── Integration/
    └── LesFightCharCreationManager.h/.cpp       Top-level orchestrator
```

### Component Diagram
```
LesFightCharCreationManager (Orchestrator)
├── Creator — Create/edit/delete/validate characters
├── PresetSystem — Import/export presets to/from disk
├── Randomizer — Procedural character generation
├── Preview — 3D viewport camera & rotation
├── FaceSystem — 14+ morph targets
├── HairSystem — Styles, color, length, physics
├── BodySystem — Height, build, body morphs
├── SkinSystem — Tone, detail, tattoos, scars
├── ClothingSystem — 12-slot equipment with colors
├── MaterialSystem — Per-slot material properties
├── AccessorySystem — 13 accessory slots
├── VoiceSystem — Voice packs, pitch, tone
├── BiographySystem — Name, age, country, backstory
├── SaveSystem — File I/O for character data
├── UISystem — Screen navigation & history
├── ReplicationSystem — Multiplayer sync
├── PerformanceSystem — Detail levels & FPS
└── DevTools — Debug overlays, stress tests
```

## Key Data Types (LesFightCharacterCreationData.h)
- **Enums**: EFightingStyle (17), EFaceMorphType (18), EHairStyle (12),
  EBodyMorphType (12), ESkinDetail (4), EClothingSlot (12), EAccessorySlot (13),
  EVoicePack (11), ECharacterBuild (4), EPreviewBackground (4),
  ECharacterCreatorMode (2), ETattooPlacement (6)
- **Structs**: FHairCustomizationData, FSkinCustomizationData, FTattooEntry,
  FClothingItemData, FAccessoryData, FVoiceSelectionData, FCharacterBiographyData,
  FCharacterCustomizationPreset (aggregates all subsystems), FMaterialEditState,
  FAccessoryEditState, FReplicatedCharacterData, FValidationResult

## Core Features
1. **Character Creator** — CRUD operations, validation, duplicate detection
2. **Preset System** — Binary serialization with ObjectAndNameAsStringProxyArchive
3. **Randomizer** — Seeded RNG, batch generation, per-category randomization
4. **Preview** — Auto-rotate, zoom, camera reset, background/lighting control
5. **Face Customization** — 18 morph targets, eye color, per-morph range limits
6. **Hair System** — 12 styles, RGB color, length slider, physics toggle
7. **Body Customization** — 12 morphs, height range 140-220cm, build presets
8. **Skin System** — Preset skin tones, 4 detail levels, tattoos (max 10), scars
9. **Clothing System** — 12 body slots, color/pattern, material overrides
10. **Material Editor** — Per-slot base color, metallic, roughness, texture maps
11. **Accessories** — 13 slots, position/rotation/scale, color per accessory
12. **Voice Selection** — 11 voice packs, pitch/tone modulation, preview
13. **Biography** — Name (32 char), nickname, age (16-99), country, backstory (500 char)
14. **Save System** — File-per-character, slot-based bulk save, auto-save
15. **UI** — Screen stack with history (max 20), undo/redo navigation
16. **Replication** — Character data sync for multiplayer, pending queue
17. **Performance** — 0-5 detail levels, dynamic resolution, FPS tracking
18. **Dev Tools** — Debug overlay, morph visualization, stress tests, automation

## Dependencies
- Modules 1-5 (Foundation, Core, Character System, Combat, Animation)
- Module 7 (Martial Arts) for fighting style assignment
- BaseFighter: integrates through CharCreationManager for applying customization
- Module 6 (Network): CharacterReplication hooks into SessionManager for sync

## Integration Points
- **BaseFighter**: CharCreationManager.ApplyCustomization() sets morphs, clothing,
  materials, voice, hair on the fighter pawn
- **Network**: CharacterReplication sends/receives FCharacterCustomizationPreset
  over the network session
- **UI**: CustomizationUI.NavigateTo() connects to the game's main menu system
- **Save**: CharacterSaveSystem reads/writes to the project's Saved directory

## Usage Example
```cpp
// Initialize the character creation system
ULesFightCharCreationManager* CharManager = NewObject<ULesFightCharCreationManager>(this);
CharManager->Initialize();

// Create a new character
FCharacterBiographyData Bio;
Bio.CharacterName = TEXT("Raging Tiger");
Bio.Age = 28;
Bio.Country = TEXT("Japan");
FName CharID = CharManager->GetCreator()->CreateNewCharacter(Bio);

// Customize face
CharManager->GetFaceSystem()->SetMorphValue(EFaceMorphType::JawWidth, 0.8f);
CharManager->GetFaceSystem()->SetEyeColor(FLinearColor::Red);

// Set hair
CharManager->GetHairSystem()->SetHairStyle(EHairStyle::Spiky);
CharManager->GetHairSystem()->SetHairColor(FLinearColor::Yellow);

// Equip clothing
FClothingItemData Gi;
Gi.bEquipped = true;
Gi.PrimaryColor = FLinearColor::White;
CharManager->GetClothingSystem()->EquipItem(EClothingSlot::Torso, Gi);

// Preview and save
CharManager->GetPreview()->ShowPreview(CharID);
CharManager->SaveActiveCharacter();
```

## File Count: 38 files (19 .h, 19 .cpp)
