# LES FIGHT 🔥

A next-generation 3D fighting game built with **Unreal Engine 5.4** - now also available as a **Web Edition**!

---

## 🎮 PLAY NOW (No install needed!)

> **Open on your phone or computer:**

[![PLAY LES FIGHT](https://img.shields.io/badge/🎮-PLAY%20LES%20FIGHT%20NOW!-ff4444?style=for-the-badge&logo=html5)](https://htmlpreview.github.io/?https://raw.githubusercontent.com/mahuvechriss/Lesfight/main/WebGame/index.html)

**Just tap the button above!** Works on any phone or computer browser.

### Touch Controls (Mobile)
| Button | Action |
|--------|--------|
| ◀ ▶ | Move left/right |
| 🛡️ | Block |
| 👊 | Light Punch |
| 💥 | Heavy Punch |
| 🦵 | Light Kick |
| 🦶 | Heavy Kick |
| ⚡ | Special Move (30% Super) |
| 🌟 | Ultimate Move (100% Super) |

### Keyboard Controls (PC)
| Key | Action |
|-----|--------|
| A / D | Move |
| S | Block |
| J | Light Punch |
| K | Heavy Punch |
| L | Light Kick |
| ; / : | Heavy Kick |
| U | Special Move |
| I | Ultimate Move |

---

## 🎯 Features

- ⚔️ **Complete fighting game** with health bars, super meter, and combos
- 🤖 **4 AI difficulty levels**: Easy → Normal → Hard → Expert
- 🏆 **Round system**: Best of 1, 3, or 5 rounds
- 💥 **6 attack types**: Light/Heavy Punch, Light/Heavy Kick, Special, Ultimate
- 🎨 **Animated fighters** with hit reactions, blocking, and KO states
- 🌟 **Particle effects**, screen shake, and sound effects
- 📱 **Touch-optimized** for mobile play
- 🎮 **Keyboard controls** for PC

---

## 🛠️ Unreal Engine 5.4 Project

This repository contains the full C++ source code for the UE5 version of LES FIGHT:

| Module | Files | Description |
|--------|-------|-------------|
| Core | 22 | GameInstance, GameMode, PlayerController, GameState, HUD |
| Combat | 22 | ComboManager, DamageManager, HitDetection, Blocking |
| Animation | 22 | StateMachine, IK, Blending, MotionWarping |
| AI | 25+ | DecisionManager, Perception, CombatAI, Difficulty |
| Audio | 30+ | Music, SFX, Voice, Spatial, Dynamic Music |
| VFX | 18 | Niagara, Impact, PostProcessing, Cinematic |
| Arena | 18 | Environment, Weather, Lighting, Destructibles |
| UI | 30+ | HUD, Menus, Settings, Character Select |
| Network | 20+ | Multiplayer, Replication, Lag Compensation |
| Performance | 16 | FPS Monitor, Memory Tracker, Quality Settings |
| QA | 16 | Automation, Testing, Bug Tracking |
| Release | 14 | Build Manager, Packaging, Versioning |
| **Total** | **716+** | **19 complete modules** |

---

## 📱 Android Build

To build the Android APK, you need **Unreal Engine 5.4** installed:
1. Install UE 5.4 via Epic Games Launcher (requires ~30GB free space)
2. Open `LesFight.uproject` in UE5
3. Set up Android SDK via Project Settings
4. File → Package Project → Android

---

## 📄 License

Free to use and modify.
