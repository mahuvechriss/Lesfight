#include "Framework/Release/Documentation/LesFightPlayerManualGenerator.h"
#include "Misc/FileHelper.h"

void ULesFightPlayerManualGenerator::Initialize()
{
	ManualSections.Empty();
}

void ULesFightPlayerManualGenerator::Shutdown()
{
	ManualSections.Empty();
}

FString ULesFightPlayerManualGenerator::GenerateInstallationSection()
{
	FString Section;
	Section += TEXT("# Installation Guide\n\n");
	Section += TEXT("## System Requirements\n\n");
	Section += TEXT("### Minimum:\n");
	Section += TEXT("- OS: Windows 10 64-bit\n");
	Section += TEXT("- CPU: Intel Core i5-8400 or AMD Ryzen 5 2600\n");
	Section += TEXT("- RAM: 8 GB\n");
	Section += TEXT("- GPU: NVIDIA GTX 1060 or AMD RX 580 (6GB VRAM)\n");
	Section += TEXT("- DirectX: Version 12\n");
	Section += TEXT("- Storage: 30 GB available space\n\n");
	Section += TEXT("### Recommended:\n");
	Section += TEXT("- OS: Windows 11 64-bit\n");
	Section += TEXT("- CPU: Intel Core i7-10700 or AMD Ryzen 7 3700X\n");
	Section += TEXT("- RAM: 16 GB\n");
	Section += TEXT("- GPU: NVIDIA RTX 2070 or AMD RX 6700 XT\n");
	Section += TEXT("- DirectX: Version 12 Ultimate\n");
	Section += TEXT("- Storage: 30 GB SSD\n\n");
	Section += TEXT("## Installation Steps\n\n");
	Section += TEXT("1. Download the installer from the official source.\n");
	Section += TEXT("2. Run the installer executable.\n");
	Section += TEXT("3. Follow the on-screen instructions.\n");
	Section += TEXT("4. Choose your installation directory.\n");
	Section += TEXT("5. Select optional components.\n");
	Section += TEXT("6. Complete installation.\n");
	Section += TEXT("7. Launch LesFight from the desktop shortcut or Start Menu.\n");
	return Section;
}

FString ULesFightPlayerManualGenerator::GenerateControlsSection()
{
	FString Section;
	Section += TEXT("# Controls\n\n");
	Section += TEXT("## Keyboard\n\n");
	Section += TEXT("| Action | Key |\n");
	Section += TEXT("|--------|-----|\n");
	Section += TEXT("| Move Left | A |\n");
	Section += TEXT("| Move Right | D |\n");
	Section += TEXT("| Jump/Crouch | W/S |\n");
	Section += TEXT("| Light Attack | J |\n");
	Section += TEXT("| Heavy Attack | K |\n");
	Section += TEXT("| Kick | L |\n");
	Section += TEXT("| Special Move | U |\n");
	Section += TEXT("| Block | Space |\n");
	Section += TEXT("| Dodge | Shift |\n");
	Section += TEXT("| Throw | O |\n");
	Section += TEXT("| Ultimate | I |\n");
	Section += TEXT("| Pause | Escape |\n\n");
	Section += TEXT("## Controller\n\n");
	Section += TEXT("| Action | Button |\n");
	Section += TEXT("|--------|--------|\n");
	Section += TEXT("| Move | Left Stick |\n");
	Section += TEXT("| Light Attack | X (Xbox) / Square (PS) |\n");
	Section += TEXT("| Heavy Attack | Y (Xbox) / Triangle (PS) |\n");
	Section += TEXT("| Kick | A (Xbox) / Cross (PS) |\n");
	Section += TEXT("| Special | B (Xbox) / Circle (PS) |\n");
	Section += TEXT("| Block | Left Trigger |\n");
	Section += TEXT("| Dodge | Right Trigger |\n");
	Section += TEXT("| Throw | RB |\n");
	Section += TEXT("| Ultimate | RT + B |\n");
	Section += TEXT("| Pause | Start |\n");
	return Section;
}

FString ULesFightPlayerManualGenerator::GenerateGameModesSection()
{
	FString Section;
	Section += TEXT("# Game Modes\n\n");
	Section += TEXT("## Arcade Mode\n");
	Section += TEXT("Fight through a series of increasingly difficult AI opponents.\n");
	Section += TEXT("Defeat all opponents to win the championship.\n\n");
	Section += TEXT("## VS Mode\n");
	Section += TEXT("Fight against another player locally on the same machine.\n\n");
	Section += TEXT("## LAN Multiplayer\n");
	Section += TEXT("Connect with other players over a local area network.\n");
	Section += TEXT("One player hosts the game, others join.\n\n");
	Section += TEXT("## Training Mode\n");
	Section += TEXT("Practice your skills against a non-attacking AI opponent.\n");
	Section += TEXT("Test combos and strategies without pressure.\n\n");
	Section += TEXT("## AI Photo-to-Character\n");
	Section += TEXT("Upload a photo and generate a unique AI fighter based on it.\n");
	Section += TEXT("Customize the result and fight as your creation.\n");
	return Section;
}

FString ULesFightPlayerManualGenerator::GenerateCharacterCreationSection()
{
	FString Section;
	Section += TEXT("# Character Creation\n\n");
	Section += TEXT("## Creating a New Character\n\n");
	Section += TEXT("1. Select 'Character Creator' from the main menu.\n");
	Section += TEXT("2. Choose a base template or start from scratch.\n");
	Section += TEXT("3. Customize appearance: face, hair, body type, outfit.\n");
	Section += TEXT("4. Choose a fighting style: Rushdown, Grappler, Zoner, Balanced.\n");
	Section += TEXT("5. Assign stat points: Strength, Speed, Endurance, Technique.\n");
	Section += TEXT("6. Save your character.\n\n");
	Section += TEXT("## AI Photo-to-Character\n\n");
	Section += TEXT("1. Select 'AI Generation' from the character creator.\n");
	Section += TEXT("2. Upload a front-facing photo.\n");
	Section += TEXT("3. AI analyzes the photo and generates a 3D character.\n");
	Section += TEXT("4. Edit the result as needed.\n");
	Section += TEXT("5. Save your AI-generated character.\n");
	return Section;
}

FString ULesFightPlayerManualGenerator::GenerateMultiplayerSection()
{
	FString Section;
	Section += TEXT("# Multiplayer Setup\n\n");
	Section += TEXT("## Hosting a Game\n\n");
	Section += TEXT("1. Go to Multiplayer from the main menu.\n");
	Section += TEXT("2. Select 'Host Game'.\n");
	Section += TEXT("3. Choose match settings (timer, rounds, arena).\n");
	Section += TEXT("4. Wait for players to join.\n");
	Section += TEXT("5. Start the match when ready.\n\n");
	Section += TEXT("## Joining a Game\n\n");
	Section += TEXT("1. Go to Multiplayer from the main menu.\n");
	Section += TEXT("2. Select 'Join Game'.\n");
	Section += TEXT("3. Available LAN games will be listed.\n");
	Section += TEXT("4. Select a game and join.\n");
	Section += TEXT("5. Select your character and ready up.\n");
	return Section;
}

FString ULesFightPlayerManualGenerator::GenerateSettingsSection()
{
	FString Section;
	Section += TEXT("# Settings\n\n");
	Section += TEXT("## Graphics\n\n");
	Section += TEXT("- Resolution: Set display resolution.\n");
	Section += TEXT("- Quality Preset: Ultra, High, Medium, Low.\n");
	Section += TEXT("- VSync: On/Off.\n");
	Section += TEXT("- Anti-aliasing: TAA, FXAA, Off.\n");
	Section += TEXT("- Shadow Quality: Cinematic, High, Medium, Low.\n");
	Section += TEXT("- Texture Quality: Full, High, Medium, Low.\n\n");
	Section += TEXT("## Audio\n\n");
	Section += TEXT("- Master Volume: Overall volume control.\n");
	Section += TEXT("- Music Volume: Background music.\n");
	Section += TEXT("- SFX Volume: Sound effects.\n");
	Section += TEXT("- Voice Volume: Character voice lines.\n\n");
	Section += TEXT("## Controls\n\n");
	Section += TEXT("- Remap all keyboard and controller inputs.\n");
	Section += TEXT("- Adjust dead zones and sensitivity.\n");
	Section += TEXT("- Configure vibration (controller).\n");
	return Section;
}

FString ULesFightPlayerManualGenerator::GenerateFullManual()
{
	FString Full;
	Full += TEXT("# LesFight - Player Manual\n\n");
	Full += TEXT("Welcome to LesFight, the ultimate martial arts fighting game!\n\n");
	Full += TEXT("---\n\n");
	Full += GenerateInstallationSection();
	Full += TEXT("\n---\n\n");
	Full += GenerateControlsSection();
	Full += TEXT("\n---\n\n");
	Full += GenerateGameModesSection();
	Full += TEXT("\n---\n\n");
	Full += GenerateCharacterCreationSection();
	Full += TEXT("\n---\n\n");
	Full += GenerateMultiplayerSection();
	Full += TEXT("\n---\n\n");
	Full += GenerateSettingsSection();
	Full += TEXT("\n---\n\n");
	Full += TEXT("Thank you for playing LesFight!\n");
	return Full;
}

bool ULesFightPlayerManualGenerator::ExportManual(const FString& FilePath)
{
	FString Content = GenerateFullManual();
	return FFileHelper::SaveStringToFile(Content, *FilePath);
}
