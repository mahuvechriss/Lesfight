# Module 9: AI Photo-to-Character Generation System

## Overview
The AI Photo-to-Character Generation System enables players to upload their photos and
generate realistic 3D fighter avatars with matching facial features, body proportions,
skin textures, and hair styles. The generated character integrates seamlessly with the
existing combat, animation, martial arts, and multiplayer systems.

## Architecture

### Directory Structure
```
Framework/AIPhotoToCharacter/
├── Data/
│   └── LesFightAIPhotoData.h                 Core enums, structs, data asset
├── Pipeline/
│   ├── LesFightImageUploadSystem.h/.cpp      File upload & validation
│   ├── LesFightImageValidator.h/.cpp         Image quality & face visibility check
│   ├── LesFightImagePreprocessor.h/.cpp      Background removal, color balance, resize
│   └── LesFightAIPipelineManager.h/.cpp      Stage orchestration & progress tracking
├── ComputerVision/
│   ├── LesFightFaceDetector.h/.cpp           Face region detection
│   ├── LesFightLandmarkDetector.h/.cpp       68+ facial landmark detection
│   ├── LesFightFeatureExtractor.h/.cpp       Face proportions, skin tone, expression
│   └── LesFightBodyEstimator.h/.cpp          Height, shoulder width, limb lengths
├── Reconstruction/
│   ├── LesFightFaceReconstructor.h/.cpp      3D face mesh generation from features
│   ├── LesFightBodyReconstructor.h/.cpp      3D body mesh generation from proportions
│   └── LesFightTextureGenerator.h/.cpp       Diffuse, normal, roughness, subsurface maps
├── MeshIntegration/
│   ├── LesFightMeshAdapter.h/.cpp            LOD management, mesh optimization
│   ├── LesFightSkeletonMapper.h/.cpp         Bone weight assignment & skeleton mapping
│   ├── LesFightBlendShapeGenerator.h/.cpp    FACS blend shapes, expressions, visemes
│   └── LesFightHairGenerator.h/.cpp          Hair style detection & reconstruction
├── UserEditing/
│   ├── LesFightAIResultEditor.h/.cpp         Post-generation editing with undo
│   └── LesFightStyleRecommender.h/.cpp       Fighting style & clothing recommendations
├── Privacy/
│   ├── LesFightPrivacyManager.h/.cpp         User consent, retention, anonymization
│   └── LesFightImageStore.h/.cpp             Secure temporary image storage
├── Multiplayer/
│   └── LesFightAICharReplication.h/.cpp      Optimized character data replication
├── Performance/
│   └── LesFightAIPerformance.h/.cpp          Thread count, memory limits, stage timing
├── Testing/
│   └── LesFightAIDevTools.h/.cpp             Pipeline testing, accuracy metrics, reports
├── Integration/
│   └── LesFightAIManager.h/.cpp              Top-level orchestrator (23 subsystems)
└── Documentation/
    └── Module9_Documentation.md
```

### Component Diagram
```
ULesFightAIManager (Orchestrator — 23 subsystems)
├── Pipeline Subsystem
│   ├── UploadSystem — File I/O, extension/size validation
│   ├── Validator — Quality, lighting, face visibility scoring
│   ├── Preprocessor — Background removal, resize, color correction
│   └── PipelineManager — Stage progression, progress tracking
├── Computer Vision
│   ├── FaceDetector — Bounding box detection, confidence scoring
│   ├── LandmarkDetector — 68+ facial landmarks (eyes, nose, mouth, jaw)
│   ├── FeatureExtractor — Face proportions, skin tone, expression, hair
│   └── BodyEstimator — Height, shoulder/chest/waist/hip/limb proportions
├── 3D Reconstruction
│   ├── FaceReconstructor — 5000+ vertex face mesh, morph target mapping
│   ├── BodyReconstructor — 2000+ vertex body mesh, proportion adjustment
│   └── TextureGenerator — Diffuse/normal/roughness/subsurface maps
├── Mesh Integration
│   ├── MeshAdapter — LOD (0-3), triangle optimization, collision
│   ├── SkeletonMapper — Bone weights (1-4 per vertex), skeleton remap
│   ├── BlendShapeGenerator — 52 FACS shapes, 7 expressions, 15 visemes
│   └── HairGenerator — Style mapping, color, physics toggle
├── User Editing
│   ├── AIResultEditor — Post-generation adjustment, undo history (50)
│   └── StyleRecommender — Fighting style, clothing, palette matching
├── Privacy & Security
│   ├── PrivacyManager — Consent, retention (30min), local-only, purge
│   └── ImageStore — GUID-based temp storage, auto-cleanup
├── Multiplayer
│   └── AICharReplication — Optimized preset sync, pending queue (50)
├── Performance
│   └── AIPerformance — Threads, memory, stage timing, platform profiles
└── Dev Tools
    └── AIDevTools — Pipeline testing, accuracy scoring, parameter tuning
```

## AI Pipeline Stages
1. **ImageUpload** — File select, extension/size check, metadata extraction
2. **Validating** — Quality score (0.5-1.0), lighting estimation, face visibility
3. **Preprocessing** — Background removal, color balance, resize (max 1024px)
4. **FaceDetection** — Primary face bounds, confidence threshold (0.7)
5. **LandmarkDetection** — 68 point landmarks, face/eye/lip contours
6. **FeatureExtraction** — 17 facial metrics, skin tone samples, expression
7. **BodyEstimation** — 10 proportion metrics, reference height (175cm default)
8. **FaceReconstruction** — 5000+ vertex mesh, morph target mapping (14+ types)
9. **BodyReconstruction** — 2000+ vertex mesh, proportion-driven morphs
10. **TextureGeneration** — Diffuse/normal/roughness/subsurface maps (up to 4K)
11. **HairGeneration** — Style detection, color extraction, mesh generation
12. **MeshIntegration** — LOD setup, triangle budget, collision generation
13. **SkeletonMapping** — Bone weight auto-assignment, compatibility check
14. **BlendShapeGeneration** — 52 FACS shapes, 7 expressions, 15 visemes
15. **PreviewReady** — Character ready for user review and editing

## Key Data Types
- **Enums**: EAIPipelineStage (18), EImageType (5), EImageQuality (4),
  ELightingCondition (6), EFaceVisibility (4), EAIGenerationQuality (4),
  EFacialExpression (8), EHairDetectionType (12), ESkinDetailLevel (4)
- **Structs**: FImageUploadResult, FFacialLandmarkData (19 landmark fields),
  FFaceFeatureData (17 feature fields), FHairDetectionData, FBodyProportionData,
  F3DFaceReconstructionData, FGeneratedTextureData (9 map types),
  FAICharacterGenerationResult, FAIPipelineProgress, FPrivacySettings,
  FAIDevReportEntry

## Integration Points
- **Character Creation (Module 8)**: AIManager.ApplyResultToCharacter() maps
  AI-generated face morphs, body proportions, hair, and skin to
  FCharacterCustomizationPreset and pushes to CharCreationManager
- **Animation (Module 5)**: Generated blend shapes (52 FACS + 15 visemes)
  plug directly into AnimationManager's facial animation pipeline
- **Martial Arts (Module 7)**: StyleRecommender analyzes photos and recommends
  EFightingStyle, which sets the character's martial arts style
- **Multiplayer (Module 6)**: AICharReplication sends optimized
  FAICharacterGenerationResult (stripped of heavy mesh data) over LAN

## Privacy & Security
- User consent required before any image processing
- All processing local by default (no cloud upload)
- Images stored temporarily (default 30 min retention)
- Auto-delete after generation complete
- GUID-based storage prevents unauthorized access
- Anonymization flag for data collection
- Full purge capability — PurgeAllUserData()

## Performance
- Async processing pipeline with configurable thread count (2-8)
- Memory limit control (default 2GB, up to 4GB on desktop)
- Texture resolution caps (default 2K, max 4K)
- LOD system (0-3) for generated meshes
- Platform-specific profiles (desktop/console/mobile)
- Stage timing tracking and performance reporting

## File Count: 48 files (24 .h, 23 .cpp, 1 .md)
