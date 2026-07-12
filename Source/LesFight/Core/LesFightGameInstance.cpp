#include "Core/LesFightGameInstance.h"
#include "Core/LesFightSettingsManager.h"
#include "Core/LesFightSaveGame.h"
#include "Core/LesFightLogManager.h"
#include "Framework/UI/Manager/LesFightUIManager.h"
#include "Framework/Audio/Core/LesFightAudioManager.h"
#include "Framework/Level/LesFightLevelManager.h"
#include "Events/LesFightEventManager.h"
#include "Framework/Data/Core/LesFightDataManager.h"
#include "Framework/Data/Character/LesFightCharacterDataManager.h"
#include "Framework/Character/LesFightCharacterStatisticsManager.h"
#include "Framework/Character/LesFightCharacterLifecycleManager.h"
#include "Framework/Character/Selection/LesFightCharacterSelectionManager.h"
#include "LesFight.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"

ULesFightGameInstance::ULesFightGameInstance()
	: SaveSlotName(TEXT("LesFightSave"))
	, SaveSlotIndex(0)
	, bIsInitialized(false)
{
}

void ULesFightGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogLesFight, Log, TEXT("LesFightGameInstance::Init - Initializing game instance"));

	SettingsManager = NewObject<ULesFightSettingsManager>(this, TEXT("SettingsManager"));
	if (SettingsManager)
	{
		SettingsManager->InitializeSettings();
	}

	UIManager = NewObject<ULesFightUIManager>(this, TEXT("UIManager"));
	AudioManager = NewObject<ULesFightAudioManager>(this, TEXT("AudioManager"));
	LevelManager = NewObject<ULesFightLevelManager>(this, TEXT("LevelManager"));
	EventManager = NewObject<ULesFightEventManager>(this, TEXT("EventManager"));
	DataManager = NewObject<ULesFightDataManager>(this, TEXT("DataManager"));

	CharacterDataManager = NewObject<ULesFightCharacterDataManager>(this, TEXT("CharacterDataManager"));
	CharacterStatsManager = NewObject<ULesFightCharacterStatisticsManager>(this, TEXT("CharacterStatsManager"));
	CharacterLifecycleManager = NewObject<ULesFightCharacterLifecycleManager>(this, TEXT("CharacterLifecycleManager"));
	CharacterSelectionManager = NewObject<ULesFightCharacterSelectionManager>(this, TEXT("CharacterSelectionManager"));

	if (UIManager) UIManager->Initialize();
	if (AudioManager) AudioManager->Initialize();
	if (LevelManager) LevelManager->Initialize();
	if (EventManager) EventManager->Initialize();
	if (DataManager) DataManager->Initialize();
	if (CharacterDataManager) CharacterDataManager->Initialize();
	if (CharacterStatsManager) CharacterStatsManager->Initialize();
	if (CharacterLifecycleManager) CharacterLifecycleManager->Initialize();
	if (CharacterSelectionManager) CharacterSelectionManager->Initialize();

	InitializeGame();
}

void ULesFightGameInstance::Shutdown()
{
	UE_LOG(LogLesFight, Log, TEXT("LesFightGameInstance::Shutdown - Saving game state"));
	SaveGame();
	Super::Shutdown();
}

void ULesFightGameInstance::LoadComplete(const float LoadTime, const TArray<FString>& PackageNamesLoaded)
{
	Super::LoadComplete(LoadTime, PackageNamesLoaded);
	UE_LOG(LogLesFight, Log, TEXT("Load complete in %f seconds"), LoadTime);
	OnLoadingComplete.Broadcast(true);
}

void ULesFightGameInstance::InitializeGame()
{
	if (bIsInitialized)
	{
		UE_LOG(LogLesFight, Warning, TEXT("InitializeGame called but game is already initialized"));
		return;
	}

	UE_LOG(LogLesFight, Log, TEXT("Initializing game systems..."));

	LoadGame();

	bIsInitialized = true;
	OnGameInitialized.Broadcast();

	UE_LOG(LogLesFight, Log, TEXT("Game initialization complete"));
}

void ULesFightGameInstance::SaveGame()
{
	ULesFightSaveGame* SaveGameInstance = Cast<ULesFightSaveGame>(
		UGameplayStatics::CreateSaveGameObject(ULesFightSaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		SaveGameInstance->PlayerProfile.PlayerName = GetLocalPlayers().Num() > 0
			? GetLocalPlayers()[0]->NickName
			: TEXT("Player");

		FAsyncSaveGameToSlotDelegate SaveDelegate;
		SaveDelegate.BindUObject(this, &ULesFightGameInstance::OnSaveGameWritten);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveSlotName, SaveSlotIndex, SaveDelegate);
	}
}

void ULesFightGameInstance::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, SaveSlotIndex))
	{
		FAsyncLoadGameFromSlotDelegate LoadDelegate;
		LoadDelegate.BindUObject(this, &ULesFightGameInstance::OnSaveGameLoaded);
		UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, SaveSlotIndex, LoadDelegate);
	}
	else
	{
		UE_LOG(LogLesFightSave, Log, TEXT("No save game found at slot %s"), *SaveSlotName);
	}
}

void ULesFightGameInstance::OnSaveGameLoaded(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedSave)
{
	ULesFightSaveGame* SaveGameInstance = Cast<ULesFightSaveGame>(LoadedSave);
	if (SaveGameInstance)
	{
		UE_LOG(LogLesFightSave, Log, TEXT("Save game loaded successfully from slot %s"), *SlotName);
	}
}

void ULesFightGameInstance::OnSaveGameWritten(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogLesFightSave, Log, TEXT("Save game written successfully to slot %s"), *SlotName);
	}
	else
	{
		UE_LOG(LogLesFightSave, Error, TEXT("Failed to write save game to slot %s"), *SlotName);
	}
}

void ULesFightGameInstance::CreateOnlineSession(FName SessionName, int32 MaxPlayers)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			FOnlineSessionSettings SessionSettings;
			SessionSettings.bIsLANMatch = false;
			SessionSettings.bShouldAdvertise = true;
			SessionSettings.bUsesPresence = true;
			SessionSettings.NumPublicConnections = MaxPlayers;

			SessionInterface->CreateSession(0, SessionName, SessionSettings);
			UE_LOG(LogLesFightNetwork, Log, TEXT("Creating online session: %s"), *SessionName.ToString());
		}
	}
}

void ULesFightGameInstance::FindOnlineSessions()
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->FindSessions(0, FOnlineSessionSearchRef());
		}
	}
}

void ULesFightGameInstance::JoinOnlineSession(int32 SessionIndex)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
	if (OnlineSub)
	{
		IOnlineSessionPtr SessionInterface = OnlineSub->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->JoinSession(0, FName(TEXT("GameSession")), FOnlineSessionSearchResult());
		}
	}
}
