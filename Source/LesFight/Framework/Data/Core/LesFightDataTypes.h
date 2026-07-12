#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LesFightDataTypes.generated.h"

UENUM(BlueprintType)
enum class ESaveResult : uint8
{
	Success    UMETA(DisplayName = "Success"),
	Failed     UMETA(DisplayName = "Failed"),
	Corrupted  UMETA(DisplayName = "Corrupted"),
	Invalid    UMETA(DisplayName = "Invalid"),
	NotFound   UMETA(DisplayName = "Not Found"),
	SlotFull   UMETA(DisplayName = "Slot Full")
};

UENUM(BlueprintType)
enum class EDataCategory : uint8
{
	Profile        UMETA(DisplayName = "Profile"),
	Character      UMETA(DisplayName = "Character"),
	Settings       UMETA(DisplayName = "Settings"),
	Statistics     UMETA(DisplayName = "Statistics"),
	Progression    UMETA(DisplayName = "Progression"),
	MatchHistory   UMETA(DisplayName = "Match History"),
	Achievement    UMETA(DisplayName = "Achievement"),
	Backup         UMETA(DisplayName = "Backup")
};

UENUM(BlueprintType)
enum class EProgressionEvent : uint8
{
	FightCompleted          UMETA(DisplayName = "Fight Completed"),
	AchievementUnlocked     UMETA(DisplayName = "Achievement Unlocked"),
	CharacterCreated        UMETA(DisplayName = "Character Created"),
	LevelUp                 UMETA(DisplayName = "Level Up"),
	UnlockContent           UMETA(DisplayName = "Unlock Content"),
	FirstWin                UMETA(DisplayName = "First Win"),
	WinStreak               UMETA(DisplayName = "Win Streak"),
	MilestoneReached        UMETA(DisplayName = "Milestone Reached")
};

UENUM(BlueprintType)
enum class EUnlockType : uint8
{
	Fighter                  UMETA(DisplayName = "Fighter"),
	FightingStyle            UMETA(DisplayName = "Fighting Style"),
	Clothing                 UMETA(DisplayName = "Clothing"),
	Accessory                UMETA(DisplayName = "Accessory"),
	Arena                    UMETA(DisplayName = "Arena"),
	Music                    UMETA(DisplayName = "Music"),
	SpecialTechnique         UMETA(DisplayName = "Special Technique"),
	CharacterCreatorOption   UMETA(DisplayName = "Character Creator Option"),
	ColorPalette             UMETA(DisplayName = "Color Palette"),
	Emote                    UMETA(DisplayName = "Emote")
};

UENUM(BlueprintType)
enum class EAchievementId : uint8
{
	FirstFight         UMETA(DisplayName = "First Fight"),
	FirstWin           UMETA(DisplayName = "First Win"),
	WinStreak5         UMETA(DisplayName = "Win Streak 5"),
	WinStreak10        UMETA(DisplayName = "Win Streak 10"),
	ComboMaster        UMETA(DisplayName = "Combo Master"),
	UltimateFinisher   UMETA(DisplayName = "Ultimate Finisher"),
	CompleteTutorial   UMETA(DisplayName = "Complete Tutorial"),
	CreateCharacter    UMETA(DisplayName = "Create Character"),
	AIGeneration       UMETA(DisplayName = "AI Generation"),
	ReachLevel10       UMETA(DisplayName = "Reach Level 10"),
	ReachLevel25       UMETA(DisplayName = "Reach Level 25"),
	ReachLevel50       UMETA(DisplayName = "Reach Level 50"),
	PlayOnline         UMETA(DisplayName = "Play Online"),
	WinOnline          UMETA(DisplayName = "Win Online"),
	UnlockAllStyles    UMETA(DisplayName = "Unlock All Styles"),
	UnlockAllArenas    UMETA(DisplayName = "Unlock All Arenas"),
	MaxDamage          UMETA(DisplayName = "Max Damage"),
	PerfectRound       UMETA(DisplayName = "Perfect Round"),
	ComebackVictory    UMETA(DisplayName = "Comeback Victory"),
	VeteranPlayer      UMETA(DisplayName = "Veteran Player"),
	MAX                UMETA(DisplayName = "MAX")
};

UENUM(BlueprintType)
enum class EProgressionRewardType : uint8
{
	XP            UMETA(DisplayName = "XP"),
	Currency      UMETA(DisplayName = "Currency"),
	UnlockItem    UMETA(DisplayName = "Unlock Item"),
	CharacterSlot UMETA(DisplayName = "Character Slot"),
	Title         UMETA(DisplayName = "Title"),
	Avatar        UMETA(DisplayName = "Avatar")
};

UENUM(BlueprintType)
enum class ESaveSlotUsage : uint8
{
	Free       UMETA(DisplayName = "Free"),
	Active     UMETA(DisplayName = "Active"),
	Corrupted  UMETA(DisplayName = "Corrupted"),
	Backup     UMETA(DisplayName = "Backup"),
	Reserved   UMETA(DisplayName = "Reserved")
};

UENUM(BlueprintType)
enum class EFightingStyle : uint8
{
	Karate        UMETA(DisplayName = "Karate"),
	KungFu        UMETA(DisplayName = "Kung Fu"),
	Boxing        UMETA(DisplayName = "Boxing"),
	MuayThai      UMETA(DisplayName = "Muay Thai"),
	JiuJitsu      UMETA(DisplayName = "Jiu Jitsu"),
	Capoeira      UMETA(DisplayName = "Capoeira"),
	Taekwondo     UMETA(DisplayName = "Taekwondo"),
	Wrestling     UMETA(DisplayName = "Wrestling"),
	Fencing       UMETA(DisplayName = "Fencing"),
	KravMaga      UMETA(DisplayName = "Krav Maga")
};

USTRUCT(BlueprintType)
struct FCharacterAppearanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	TMap<FString, float> FaceSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	TMap<FString, float> BodySettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	TMap<FString, float> HairSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	TArray<FName> ClothingItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	TMap<FString, FString> MaterialOverrides;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	bool bIsAIGenerated = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Appearance")
	FString AISourcePhotoPath;
};

USTRUCT(BlueprintType)
struct FCharacterGameplayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	EFightingStyle Style;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TArray<FName> UnlockedAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TMap<FString, float> CustomStats;
};

USTRUCT(BlueprintType)
struct FCharacterSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FName CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCharacterAppearanceData Appearance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FCharacterGameplayData Gameplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FDateTime CreatedDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FDateTime LastModified;
};

USTRUCT(BlueprintType)
struct FGraphicsSettingsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
	FIntPoint Resolution = FIntPoint(1920, 1080);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
	int32 QualityPreset = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
	int32 TextureQuality = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
	int32 ShadowQuality = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
	int32 EffectsQuality = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
	int32 FrameRateLimit = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
	bool bVSync = false;
};

USTRUCT(BlueprintType)
struct FAudioSettingsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float MasterVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float MusicVolume = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float EffectsVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	float VoiceVolume = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	bool bMuted = false;
};

USTRUCT(BlueprintType)
struct FControlSettingsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	TMap<FName, FKey> KeyBindings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	float ControllerSensitivity = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	bool bVibrationEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	bool bInvertYAxis = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controls")
	int32 ControlScheme = 0;
};

USTRUCT(BlueprintType)
struct FSettingsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FGraphicsSettingsData Graphics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FAudioSettingsData Audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FControlSettingsData Controls;
};

USTRUCT(BlueprintType)
struct FMatchStatisticsData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 Wins = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 Losses = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 Draws = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalFights = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 HighestCombo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 HighestDamage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	float TotalPlayTimeSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	FName FavoriteFighter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	EFightingStyle FavoriteStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalKOs = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 TotalPerfects = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 CurrentWinStreak = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statistics")
	int32 LongestWinStreak = 0;
};

USTRUCT(BlueprintType)
struct FMatchHistoryEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	FDateTime Date;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	FName OpponentName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	bool bWon = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	FName ArenaID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	float DurationSeconds = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	int32 RoundCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	int32 MaxCombo = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	float TotalDamage = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Match History")
	FString FightSummary;
};

USTRUCT(BlueprintType)
struct FProgressionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	int32 PlayerLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	int32 CurrentXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	int32 XPToNextLevel = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	TArray<FName> CompletedAchievements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	TArray<FName> UnlockedItems;
};

USTRUCT(BlueprintType)
struct FAchievementDef
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	EAchievementId ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Achievement")
	bool bHidden = false;
};

USTRUCT(BlueprintType)
struct FProgressionReward
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	EProgressionRewardType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	int32 Amount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
	FName ItemID;
};

USTRUCT(BlueprintType)
struct FPlayerProfileData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FName ProfileID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FText PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FDateTime Created;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FDateTime LastPlayed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	int32 PlayCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FString AvatarPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	TArray<FName> SavedCharacterIDs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FMatchStatisticsData Statistics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FProgressionData Progression;
};
