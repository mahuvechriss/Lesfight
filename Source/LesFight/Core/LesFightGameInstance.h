#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "LesFightGameInstance.generated.h"

class ULesFightSettingsManager;
class ULesFightSaveGame;
class UInputMappingContext;
class ULesFightUIManager;
class ULesFightAudioManager;
class ULesFightLevelManager;
class ULesFightEventManager;
class ULesFightDataManager;
class ULesFightCharacterDataManager;
class ULesFightCharacterStatisticsManager;
class ULesFightCharacterLifecycleManager;
class ULesFightCharacterSelectionManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameInitializedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadingCompleteDelegate, bool, bSuccess);

UCLASS(Config = Game)
class ULesFightGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    ULesFightGameInstance();

    virtual void Init() override;
    virtual void Shutdown() override;
    virtual void LoadComplete(const float LoadTime, const TArray<FString>& PackageNamesLoaded) override;

    UFUNCTION(BlueprintCallable, Category = "LesFight|Initialization")
    void InitializeGame();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Initialization")
    bool IsGameInitialized() const { return bIsInitialized; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Save")
    void SaveGame();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Save")
    void LoadGame();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Settings")
    ULesFightSettingsManager* GetSettingsManager() const { return SettingsManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|UI")
    ULesFightUIManager* GetUIManager() const { return UIManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Audio")
    ULesFightAudioManager* GetAudioManager() const { return AudioManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Level")
    ULesFightLevelManager* GetLevelManager() const { return LevelManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Events")
    ULesFightEventManager* GetEventManager() const { return EventManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Data")
    ULesFightDataManager* GetDataManager() const { return DataManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    ULesFightCharacterDataManager* GetCharacterDataManager() const { return CharacterDataManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    ULesFightCharacterStatisticsManager* GetCharacterStatsManager() const { return CharacterStatsManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    ULesFightCharacterLifecycleManager* GetCharacterLifecycleManager() const { return CharacterLifecycleManager; }

    UFUNCTION(BlueprintPure, Category = "LesFight|Character")
    ULesFightCharacterSelectionManager* GetCharacterSelectionManager() const { return CharacterSelectionManager; }

    UFUNCTION(BlueprintCallable, Category = "LesFight|Session")
    void CreateOnlineSession(FName SessionName, int32 MaxPlayers);

    UFUNCTION(BlueprintCallable, Category = "LesFight|Session")
    void FindOnlineSessions();

    UFUNCTION(BlueprintCallable, Category = "LesFight|Session")
    void JoinOnlineSession(int32 SessionIndex);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Initialization")
    TObjectPtr<ULesFightSettingsManager> SettingsManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|UI")
    TObjectPtr<ULesFightUIManager> UIManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Audio")
    TObjectPtr<ULesFightAudioManager> AudioManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Level")
    TObjectPtr<ULesFightLevelManager> LevelManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Events")
    TObjectPtr<ULesFightEventManager> EventManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Data")
    TObjectPtr<ULesFightDataManager> DataManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Character")
    TObjectPtr<ULesFightCharacterDataManager> CharacterDataManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Character")
    TObjectPtr<ULesFightCharacterStatisticsManager> CharacterStatsManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Character")
    TObjectPtr<ULesFightCharacterLifecycleManager> CharacterLifecycleManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LesFight|Character")
    TObjectPtr<ULesFightCharacterSelectionManager> CharacterSelectionManager;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Save")
    FString SaveSlotName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Save")
    int32 SaveSlotIndex;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnGameInitializedDelegate OnGameInitialized;

    UPROPERTY(BlueprintAssignable, Category = "LesFight|Events")
    FOnLoadingCompleteDelegate OnLoadingComplete;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LesFight|Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

private:
    bool bIsInitialized;

    UFUNCTION()
    void OnSaveGameLoaded(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedSave);

    UFUNCTION()
    void OnSaveGameWritten(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};
