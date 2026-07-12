# Module 6: LAN Multiplayer & Network Synchronization

## Overview

Module 6 delivers a complete LAN multiplayer system for "LES FIGHT", enabling local area network matches between two players with server-authoritative synchronization, client prediction, and full match lifecycle management.

---

## Architecture

```
Framework/Network/
├── Data/
│   └── LesFightNetworkData.h          # Data structures, enums, asset
├── LesFightMultiplayerManager.h/.cpp  # Top-level orchestrator
├── LesFightSessionManager.h/.cpp      # LAN session lifecycle
├── LesFightConnectionManager.h/.cpp   # Connection monitoring & timeout
├── LesFightMatchManager.h/.cpp        # Round/match lifecycle
├── LesFightNetworkGameMode.h/.cpp     # UE4 GameMode (server authoritative)
├── LesFightNetworkGameState.h/.cpp    # Replicated match state
├── LesFightNetworkPlayerState.h/.cpp  # Replicated player state
├── LesFightNetworkPlayerController.h/.cpp # PlayerController + RPCs
├── LesFightNetworkSyncManager.h/.cpp  # State sync orchestration
├── LesFightReplicationManager.h/.cpp  # Bandwidth-optimized replication
├── LesFightLagCompensation.h/.cpp     # Position snapshot rollback
├── LesFightNetworkPrediction.h/.cpp   # Client-side input prediction
├── LesFightNetworkOptimizer.h/.cpp    # Adaptive bandwidth management
├── LesFightNetworkSecurity.h/.cpp     # Server-side validation & anti-cheat
├── LesFightNetworkDebugger.h/.cpp     # Latency/packet loss simulation
├── LesFightNetworkUI.h/.cpp           # Lobby, host, join, match UI
├── LesFightNetworkAudioSync.h/.cpp    # Networked audio playback
└── LesFightNetworkVFXSync.h/.cpp     # Networked visual effects
```

---

## Core Systems

### 1. Network Architecture (20 files)

- **22 new C++ classes** implementing full multiplayer stack
- **4 updated existing classes** (BaseFighter, CombatComponent, HealthComponent, CharacterAnimationComponent)
- Zero breaking changes to Modules 1-5
- **UE4 OnlineSubsystem** for LAN session discovery

### 2. LAN Sessions

- Host, discover, join, leave, destroy sessions
- LAN-only filtering with `OnlineSubsystem`
- Lobby ready-states (Ready/Loading/Loaded)
- Player + session info structs with full replication

### 3. Combat Synchronization

- **Server-authoritative** combat resolution
- 14 server RPCs (Attack, Block, Dodge, Throw, Special, Ultimate)
- 11 client RPCs (Hit confirmation, miss, combo, health changes)
- Position prediction + server reconciliation
- Lag compensation with time-based rewind validation

### 4. Match Flow

- Wait → CharacterSelect → Countdown → RoundInProgress → RoundEnd → MatchEnd
- `NetworkGameState` replicates: round timer, scores, match state
- `NetworkPlayerState` replicates: wins, ready, character selection, ping, team
- Countdown with events, round history tracking

### 5. Optimization

- `NetworkOptimizer`: adaptive bandwidth (256 Kbps default), packet stats
- `ReplicationManager`: queued replication with rate limiting (60 Hz)
- 3 optimization levels (None/Low/Medium/High)
- Average bandwidth tracking, efficiency metrics

### 6. Security

- Server-side combat action validation (rate limits, damage bounds)
- Position delta checking (500 unit/tick max)
- Suspicion score tracking with threshold alerts
- Per-player security state: actions/sec, violation history

### 7. Debug Tools

- Latency simulation: configurable min/max ms
- Packet loss simulation: configurable percentage
- Frame time history overlay
- Full RPC logging via `LogLesFightNetwork`

### 8. Audio & VFX

- `NetworkAudioSync`: synced sound playback per-player or globally
- `NetworkVFXSync`: synced particle/visual effects with attach/stop

### 9. UI Integration

- `NetworkUI`: screen management (Host, Join, Lobby, Countdown, Summary)
- Delegates for all state changes
- Player list updates, connection quality display

---

## Existing File Modifications

| File | Changes |
|------|---------|
| `BaseFighter.h/.cpp` | `GetLifetimeReplicatedProps`, RPCs (ServerSetPlayerIndex, ClientOnDeath/Revive/RoundStart/RoundEnd), replicated `PlayerIndex`/`OwnerPlayerIndex` |
| `CombatComponent.h/.cpp` | 9 server RPCs, 6 client RPCs, replicated state, `SetIsReplicatedByDefault` |
| `HealthComponent.h/.cpp` | `GetLifetimeReplicatedProps`, replicated `CurrentHealth`/`MaxHealth` |
| `CharacterAnimationComponent.h/.cpp` | 4 server RPCs, 1 client RPC, `SetIsReplicatedByDefault` |
| `LesFight.Build.cs` | Already includes `OnlineSubsystem` + `OnlineSubsystemUtils` |

---

## Testing

1. **Host a game**: `MultiplayerManager->HostGame("TestSession", 2)`
2. **Find games**: `MultiplayerManager->FindLANGames()`
3. **Join a game**: `MultiplayerManager->JoinGame(0)`
4. **Simulate latency**: `NetworkDebugger->SetLatencySimulation(50, 150)`
5. **Simulate packet loss**: `NetworkDebugger->SetPacketLossSimulation(10.0)`
6. **View bandwidth stats**: `NetworkOptimizer->GetBandwidthStats()`
7. **Validate combat**: `NetworkSecurity->ValidateCombatAction(Index, Action)`
8. **Predict input**: `NetworkPrediction->QueueInput("MoveForward", 1.0)`
