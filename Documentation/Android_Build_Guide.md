# LesFight - Android Build Guide

> **Target:** Package LesFight as an Android APK to play on your phone

---

## 📋 Prerequisites Checklist

| # | Step | Done? |
|---|------|-------|
| 1 | Install Unreal Engine 5.4 | ☐ |
| 2 | Install Android Studio | ☐ |
| 3 | Install Android SDK & NDK (via UE5's wizard) | ☐ |
| 4 | Open LesFight in UE5 & compile C++ code | ☐ |
| 5 | Create minimal Blueprints | ☐ |
| 6 | Package for Android as APK | ☐ |
| 7 | Install APK on phone | ☐ |

---

## 🔧 Step 1: Install Unreal Engine 5.4

1. Download & install the **Epic Games Launcher** from [store.epicgames.com](https://store.epicgames.com/)
2. Open the launcher → **Unreal Engine** tab → **Library** section
3. Click the **+** button next to **Engine Versions**
4. Select **5.4** (must match the project's engine version)
5. Click **Install** (download is ~30–40 GB, may take a while)
6. Once installed, launch UE5.4 at least once (it sets up engine files)

---

## 📱 Step 2: Set Up Android Development Environment

### Option A: Use UE5's Built-in Android Setup (Recommended)

1. Open UE5.4 Editor (any project is fine)
2. Go to **Edit → Platform → Android SDK** (or search in Project Settings)
3. Click the **Install Android SDK** button
4. UE will download and configure:
   - Android SDK (latest stable)
   - Android NDK (r25c or compatible)
   - Java/JDK (Temurin or OpenJDK)
   - Android Command Line Tools
   - Android Platform (API 34)
5. Wait for the download to complete (~2–5 GB)

### Option B: Manual Android Studio Setup

If the built-in installer fails:

1. Install **Android Studio** from [developer.android.com/studio](https://developer.android.com/studio)
2. In Android Studio → **SDK Manager** → Install:
   - Android SDK Platform 34
   - Android SDK Build-Tools 34.x.x
   - Android NDK (Side-by-side) → version **25.2.9519653**
   - CMake
3. In UE5 Editor → **Edit → Project Settings → Android SDK**:
   - Set **Location of Android SDK** → `C:\Users\<You>\AppData\Local\Android\Sdk`
   - Set **Location of Android NDK** → path to NDK 25.2.9519653
   - Set **Location of Java/JDK** → `C:\Program Files\Epic Games\UE_5.4\Engine\Extras\Android\OpenJDK`

---

## 🚀 Step 3: Open LesFight in UE5

1. Launch **Unreal Engine 5.4** from the Epic Games Launcher
2. In the Project Browser, click **Browse** and select:
   ```
   H:\Lesfight\LesFight.uproject
   ```
3. When prompted **"The following modules are missing..."** → click **Yes** to rebuild
4. UE5 will compile all **465+ C++ source files** (takes 5–15 minutes the first time)
5. If compilation errors appear, note them and share with me to fix together

> ✅ **Expected:** After compilation, the editor will open with the project loaded.

---

## 🧱 Step 4: Configure Project for Android

### 4.1 — Open Project Settings
Go to **Edit → Project Settings** → scroll down to **Platforms → Android**

### 4.2 — Configure These Settings
| Setting | Value |
|---------|-------|
| **Minimum SDK** | `Android 8.0 (API 26)` |
| **Target SDK** | `Android 14.0 (API 34)` |
| **Build Configuration** | `Shipping` |
| **Architecture** | ✅ ARM64 (untick x86_64 for smaller APK) |
| **Enable Vulkan** | ✅ Checked (already in config) |
| **Enable OpenGLES3** | ✅ Checked (already in config) |

### 4.3 — Package Name
Set **Android Package Name** to something unique, e.g.:
```
com.yourcompany.lesfight
```

### 4.4 — Graphics
Set **Default Graphics Orientation** to `Landscape` (fighting game fits better in landscape)

---

## 🎨 Step 5: Create Minimal Blueprints (Required for Build)

Since the Content folder is empty, you need just enough Blueprints to avoid errors:

### 5.1 — Create a Basic Map
1. Right-click in Content Browser → **Level** → name it `LesFightArena`
2. Place a **Floor** (cube, scale 50x1x50) and a **PlayerStart** actor
3. Add a **Directional Light** and **Sky Light**
4. Save (Ctrl+S)

### 5.2 — Create Game Mode Blueprint
1. Right-click → **Blueprint Class** → choose **ALesFightGameMode** as parent
2. Name it `BP_LesFightGameMode`
3. Open it → **Class Defaults** → set:
   - **Default Pawn Class** → None (or create a simple pawn)
4. Save and compile

### 5.3 — Create Game Instance Blueprint
1. Right-click → **Blueprint Class** → choose **ULesFightGameInstance** as parent
2. Name it `BP_LesFightGameInstance`
3. Save and compile

### 5.4 — Assign Blueprints in Project Settings
Go to **Edit → Project Settings → Maps & Modes**:
- **Default GameMode** → `BP_LesFightGameMode`
- **Game Instance Class** → `BP_LesFightGameInstance`
- **Editor Startup Map** → `LesFightArena`
- **Game Default Map** → `LesFightArena`

---

## 📦 Step 6: Package for Android

### Method 1: Package Project (Simpler)
1. **File → Package Project → Android → Android (ASTC)**
2. Choose a destination folder (e.g., `H:/Lesfight/Build/Android/`)
3. UE5 will compile shaders, package assets, and build the APK
4. Output file: `LesFight-Android-Shipping.apk` (or `.aab`)

### Method 2: Project Launcher (More Control)
1. Go to **Window → Project Launcher**
2. Create a custom launch profile:
   - **Build** → ✅ Build
   - **Cook** → By the book, all maps
   - **Package** → Android → APK (not AAB for direct install)
   - **Deploy** → Do not deploy
3. Click **Run** to start the process

---

## 📲 Step 7: Install on Your Phone

### Option A: Direct APK Install
1. Locate the APK file (in your build output folder)
2. Copy the `.apk` to your Android phone via USB or cloud storage
3. On your phone, open the APK file to install
4. **Enable "Install from unknown sources"** if prompted in Settings

### Option B: USB Debug + Command Line
1. On your phone, enable **Developer Options** and **USB Debugging**
2. Connect phone to PC via USB
3. Open a command prompt and run:
   ```
   adb install H:\Lesfight\Build\Android\LesFight-Android-Shipping.apk
   ```
4. The game will appear in your app drawer as **LesFight**

---

## 🐛 Troubleshooting

### Compilation Errors
If you get C++ errors when opening the project, share the exact error message with me and I'll help fix them.

### Android SDK Not Found
- Double-check the SDK paths in **Project Settings → Android SDK**
- Try running the UE5 Android setup wizard again

### APK Won't Install
- Make sure **Install from Unknown Sources** is allowed
- Try: Settings → Apps → Special Access → Install Unknown Apps

### Game Crashes on Phone
- The Content folder has no actual game assets yet (no meshes, textures, animations)
- You'll need to add character models, animations, UI, and audio
- For a test build, the game should at least show the start screen

---

## 🎯 Quick Reference: Project Structure

| Location | Purpose |
|----------|---------|
| `H:/Lesfight/Source/` | 465 C++ source files (19 modules) |
| `H:/Lesfight/Content/` | Game assets (currently EMPTY) |
| `H:/Lesfight/Config/` | Android/iOS settings pre-configured |
| `H:/Lesfight/Plugins/` | EnhancedInput, OnlineSubsystem, etc. |

---

## 🔜 Next Steps After First Build

- [ ] Download free characters from the UE Marketplace
- [ ] Create UI widgets (main menu, HUD, character select)
- [ ] Set up touch controls for mobile
- [ ] Add test animations for your fighters
- [ ] Enable the AI combat system
- [ ] Test multiplayer over WiFi

---

## 💬 Need Help?

If you hit any errors during the process, open a terminal or take a screenshot of the UE Output Log and share it with me. I'll help you fix any issues!
