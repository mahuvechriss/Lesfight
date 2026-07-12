# Module 17: Performance Optimization & Scalability System

## Architecture

The Performance Optimization & Scalability System consists of 16 classes organized across 6 subdirectories under `Framework/Performance/`. The system provides comprehensive performance management including FPS monitoring, memory tracking, quality presets, hardware detection, and specialized optimizers for AI, physics, loading, multiplayer, and dev tools.

## Directory Structure

```
Framework/Performance/
├── Core/
│   ├── LesFightPerformanceDataTypes.h          Enums (6) + Structs (5)
│   ├── LesFightPerformanceManager.h/.cpp       Orchestrator (16 subsystems)
│   ├── LesFightFPSMonitor.h/.cpp               FPS tracking (300 samples), min/max/avg, P1/P5, warnings
│   ├── LesFightMemoryTracker.h/.cpp            Memory tracking, budgets, leak detection, object tracking
│   └── LesFightPerformanceMonitor.h/.cpp       Combined CPU/GPU/Loading/Network/Asset monitoring, overall score
├── Quality/
│   ├── LesFightGraphicsQualityManager.h/.cpp   4 presets (Ultra→Low), CVar-based application
│   ├── LesFightTextureOptimizer.h/.cpp         Texture streaming, pool management, resolution scaling
│   ├── LesFightScalabilitySettings.h/.cpp      Preset save/load, custom presets, global quality
│   └── LesFightHardwareDetector.h/.cpp         Auto-detect hardware, scoring (0-100), recommended level
├── Optimization/
│   ├── LesFightCharacterOptimizer.h/.cpp       LOD bias, culling, instanced materials, skeleton opt
│   ├── LesFightAnimationOptimizer.h/.cpp       Blend rate, IK frequency, LOD blending, max animations
│   ├── LesFightVFXOptimizer.h/.cpp             Max particles/systems, distance culling, screen effects
│   ├── LesFightAudioOptimizer.h/.cpp           Concurrent sounds, streaming, voice channels, spatial audio
│   ├── LesFightAIOptimizer.h/.cpp              Decision frequency, perception rate, BT opt, async pathfinding
│   ├── LesFightPhysicsOptimizer.h/.cpp         Cloth/hair physics, substeps, destructibles, collision complexity
│   └── LesFightLoadingOptimizer.h/.cpp         Async loading, asset preloading, texture pool, load ordering
├── Multiplayer/
│   └── LesFightMultiplayerOptimizer.h/.cpp     Replication frequency, compression, bandwidth, sync rate
├── DevTools/
│   └── LesFightPerformanceDevTools.h/.cpp      Dashboard, frame analysis, stress tests, benchmarks
└── Documentation/
    └── Module17_Documentation.md
```

## Quality Presets

| Feature | Ultra | High | Medium | Low |
|---------|-------|------|--------|-----|
| Resolution Scale | 100% | 100% | 75% | 50% |
| Texture Quality | Full | High | Medium | Low |
| Shadow Quality | Cinematic | High | Medium | Low |
| VFX Quality | Ultra | High | Medium | Low |
| View Distance | 100% | 100% | 75% | 50% |
| Nanite | On | On | On | Off |
| Lumen | On | On | Off | Off |
| Motion Blur | On | On | On | Off |
| SSR | On | On | On | Off |
| Post Processing | On | On | On | Off |

## Hardware Detection Scoring

The hardware detector assigns scores based on system specifications:

| Component | Threshold | Points |
|-----------|-----------|--------|
| CPU Cores | ≥12 / ≥8 / ≥6 / ≥4 | 20 / 15 / 10 / 5 |
| RAM | ≥32GB / ≥16GB / ≥8GB / ≥4GB | 25 / 20 / 10 / 5 |
| GPU Memory | ≥8GB / ≥4GB / ≥2GB | 25 / 15 / 10 |
| Storage Free | ≥100GB / ≥50GB | 10 / 5 |

**Score Thresholds:**
- **70+** → Ultra
- **50+** → High
- **30+** → Medium
- **<30** → Low

## Optimization by Quality Level

### Character

| Level | LOD Bias | Culling | Instanced Materials |
|-------|----------|---------|-------------------|
| Ultra | 0 | Off | No |
| High | 0 | Off | Yes |
| Medium | 1 | On (10000) | Yes |
| Low | 2 | On (5000) | Yes |

### Animation

| Level | Blend Rate | IK Rate | Max Anims | Motion Matching |
|-------|-----------|---------|-----------|----------------|
| Ultra | 60Hz | 60Hz | 10 | On |
| High | 60Hz | 30Hz | 8 | On |
| Medium | 30Hz | 15Hz | 5 | Off |
| Low | 15Hz | 10Hz | 3 | Off |

### VFX

| Level | Max Particles | Max Systems | Screen FX |
|-------|-------------|------------|-----------|
| Ultra | 50,000 | 100 | Enabled |
| High | 20,000 | 50 | Enabled |
| Medium | 5,000 | 25 | Disabled |
| Low | 1,000 | 10 | Disabled |

### Audio

| Level | Concurrent | Voice Channels | Spatial Audio |
|-------|-----------|---------------|---------------|
| Ultra | 64 | 4 | Enabled |
| High | 32 | 2 | Enabled |
| Medium | 16 | 1 | Disabled |
| Low | 8 | 1 | Disabled |

### AI

| Level | Decision Freq | Perception | Max AI | Async Path |
|-------|--------------|------------|--------|-----------|
| Ultra | 60Hz | 60Hz | 8 | On |
| High | 30Hz | 30Hz | 4 | On |
| Medium | 15Hz | 15Hz | 2 | On |
| Low | 10Hz | 10Hz | 2 | Off |

### Physics

| Level | Cloth | Hair | Substeps | Max Destruct | Collision |
|-------|-------|------|----------|-------------|-----------|
| Ultra | On | On | 4 | 20 | Full |
| High | On | On | 2 | 10 | Reduced |
| Medium | Off | On | 1 | 5 | Simplified |
| Low | Off | Off | 1 | 2 | Simplified |

### Multiplayer

| Level | Repl Freq | Bandwidth | Sync Rate | Compression |
|-------|----------|-----------|-----------|------------|
| Ultra | 60Hz | 512Kbps | 30Hz | On |
| High | 30Hz | 256Kbps | 20Hz | On |
| Medium | 15Hz | 128Kbps | 15Hz | On |
| Low | 10Hz | 64Kbps | 10Hz | Off |

## Performance Score Calculation

The overall performance score (0-100) is computed as a weighted average of individual subsystem scores:

| Category | Weight | Formula |
|----------|--------|---------|
| FPS Score | 40% | `min(CurrentFPS / TargetFPS * 100, 100)` |
| CPU Score | 15% | `100 - CPUUsagePercent` |
| GPU Score | 15% | `100 - GPUUsagePercent` |
| Memory Score | 15% | `(1 - CurrentMemoryMB / BudgetMemoryMB) * 100` |
| Loading Score | 10% | `100 - (LoadTimeMs / ExpectedTimeMs) * 100` |
| Network Score | 5% | `100 - (LatencyMs / 100) * 100` |

Each subsystem clamps to 0-100 before weighting.

## File Count

**36 files total** (18 `.h`, 17 `.cpp`, 1 `.md`)
